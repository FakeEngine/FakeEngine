/*****************************************************************
 * \file   FakeConnection.h
 * \brief  
 * 
 * \author Can Karka
 * \date   February 2021
 * 
 * Copyright (C) 2021 Can Karka
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *  https://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *********************************************************************/

#pragma once

#include "FakeNetAsioInclude.h"

#include "Engine/Core/DataTypes/FakeThreadSafeQueue.h"
#include "FakeMessage.h"

template<typename T>
class FakeServer;

template<typename T>
class FakeConnection : public std::enable_shared_from_this<FakeConnection<T>>
	{
	public:

		enum class Owner
			{
			Server, Client
			};

	protected:

		asio::ip::tcp::socket Socket;
		asio::io_context &Context;

		uint32 ID = 0;
		Owner MessageOwner = Owner::Server;
		FakeMessage<T> TempMessage;

		FakeThreadSafeQueue<FakeMessage<T>> MessagesOut;
		FakeThreadSafeQueue<FakeOwnedMessage<T>> &MessagesIn;

		uint64 HandshakeOut = 0;
		uint64 HandshakeIn = 0;
		uint64 HandshakeCheck = 0;

	private:

		void WriteHeader()
			{
			asio::async_write(Socket, asio::buffer(&MessagesOut.Front().Header, sizeof(FakeMessageHeader<T>)), [this](std::error_code ec, std::size_t length)
				{
				if (!ec)
					{
					if (MessagesOut.Front().Body.size() > 0)
						{
						WriteBody();
						}
					else
						{
						MessagesOut.Dequeue();

						if (!MessagesOut.IsEmpty())
							{
							WriteHeader();
							}
						}
					}
				else
					{
					FAKE_LOG_WARN("[%d] Write Header failed.", ID);
					Socket.close();
					}
				});
			}

		void WriteBody()
			{
			asio::async_write(Socket, asio::buffer(MessagesOut.Front().Body.data(), MessagesOut.Front().Body.size()), [this](std::error_code ec, std::size_t length)
				{
				if (!ec)
					{
					MessagesOut.Dequeue();

					if (!MessagesOut.IsEmpty())
						{
						WriteHeader();
						}
					}
				else
					{
					FAKE_LOG_WARN("[%d] Write Body failed.", ID);
					Socket.close();
					}
				});
			}

		void ReadHeader()
			{
			asio::async_read(Socket, asio::buffer(&TempMessage, sizeof(FakeMessageHeader<T>)), [this](std::error_code ec, std::size_t length)
				{
				if (!ec)
					{
					if (TempMessage.Header.Size > 0)
						{
						TempMessage.Body.resize(TempMessage.Header.Size);
						ReadBody();
						}
					else
						{
						AddToMessageQueue();
						}
					}
				else
					{
					FAKE_LOG_WARN("[%d] Read Header failed.", ID);
					Socket.close();
					}
				});
			}

		void ReadBody()
			{
			asio::async_read(Socket, asio::buffer(TempMessage.Body.data(), TempMessage.Body.size()), [this](std::error_code ec, std::size_t length)
				{
				if (!ec)
					{
					AddToMessageQueue();
					}
				else
					{
					FAKE_LOG_WARN("[%d] Read Body failed.", ID);
					Socket.close();
					}
				});
			}

		void AddToMessageQueue()
			{
			if (MessageOwner == Owner::Server)
				{
				MessagesIn.Enqueue({ this->shared_from_this(), TempMessage });
				}
			else
				{
				MessagesIn.Enqueue({ nullptr, TempMessage });
				}

			ReadHeader();
			}

		uint64 Scramble(uint64 input)
			{
			uint64 out = input ^ 0xDEADBEEFC0DECAFE; // constants should be rotated by a dynamic degree
			out = (out & 0xF0F0F0F0F0F0F0) >> 4 | (out & 0xF0F0F0F0F0F0F0) << 4;
			return out ^ 0xC0DEFACE12345678; // 12345678 could be a version number -> older clients that didn't update would be not functional with the new server anymore
			}

		void WriteValidation()
			{
			asio::async_write(Socket, asio::buffer(&HandshakeOut, sizeof(uint64)), [this](std::error_code ec, std::size_t length)
				{
				if (!ec)
					{
					if (MessageOwner == Owner::Client)
						ReadHeader();
					}
				else
					{
					Socket.close();
					}
				});
			}

		void ReadValidation(FakeServer<T> *server = nullptr)
			{
			asio::async_read(Socket, asio::buffer(&HandshakeIn, sizeof(uint64)), [this, server](std::error_code ec, std::size_t length)
				{
				if (!ec)
					{
					if (MessageOwner == Owner::Server)
						{
						if (HandshakeIn == HandshakeCheck) // Did the client really solve my hard puzzle?
							{
							FAKE_LOG_TRACE("Client validated successfully!");
							server->OnClientValidated(this->shared_from_this());
							ReadHeader();
							}
						else
							{
							// Client failed the puzzle! I knew my puzzles were too hard!
							FAKE_LOG_WARN("Client disconnected (validation failed)");
							Socket.close();

							// Maybe we could increment a counter here and if it reaches a limit we could bann a client from the server?
							}
						}
					else
						{
						// Connection is a Client, so you have to solve the puzzle ... good luck ;-)
						HandshakeOut = Scramble(HandshakeIn);

						// yey, you solved the puzzle! let the server know that you are the hero! :D
						WriteValidation();
						}
					}
				else
					{
					FAKE_LOG_WARN("Client disconnected (ReadValidation)");
					Socket.close();
					}
				});
			}

	public:

		FakeConnection(Owner parent, asio::io_context &context, asio::ip::tcp::socket socket, FakeThreadSafeQueue<FakeOwnedMessage<T>> &messagesIn)
			: Context(context), Socket(std::move(socket)), MessagesIn(messagesIn), MessageOwner(parent)
			{
			if (parent == Owner::Server)
				{
				HandshakeOut = uint64(std::chrono::system_clock::now().time_since_epoch().count());
				HandshakeCheck = Scramble(HandshakeOut);
				}
			else
				{
				HandshakeIn = 0;
				HandshakeOut = 0;
				}
			}

		virtual ~FakeConnection()
			{
			}

		uint32 GetID() const
			{
			return ID;
			}

		void ConnectToServer(const asio::ip::tcp::resolver::results_type &endpoints)
			{
			if (MessageOwner == Owner::Client)
				{
				asio::async_connect(Socket, endpoints, [this](std::error_code ec, asio::ip::tcp::endpoint endpoint)
					{
					if (!ec)
						{
						ReadValidation();
						}
					});
				}
			}

		void ConnectToClient(FakeServer<T> *server, uint32 uid = 0)
			{
			if (MessageOwner == Owner::Server)
				{
				if (Socket.is_open())
					{
					ID = uid;
					WriteValidation();
					ReadValidation(server);
					}
				}
			}

		bool IsConnected() const
			{
			return Socket.is_open();
			}

		void Disconnect()
			{
			if (IsConnected())
				asio::post(Context, [this]() { Socket.close(); });
			}

		void Send(const FakeMessage<T> &msg)
			{
			asio::post(Context, [this, msg]()
				{
				bool writingMsg = !MessagesOut.IsEmpty();
				MessagesOut.Enqueue(msg);

				if (!writingMsg)
					WriteHeader();
				});
			}
	};

