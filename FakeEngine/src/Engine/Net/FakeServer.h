/*****************************************************************
 * \file   FakeServer.h
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

#include <deque>

#include "FakeNetAsioInclude.h"

#include "Engine/Core/DataTypes/FakeThreadSafeQueue.h"
#include "FakeMessage.h"
#include "FakeConnection.h"

template<typename T>
class FakeServer
	{
	protected:

		FakeThreadSafeQueue<FakeOwnedMessage<T>> MessagesIn;
		std::deque<std::shared_ptr<FakeConnection<T>>> Connections;
		asio::io_context Context;
		std::thread Thread;

		asio::ip::tcp::acceptor AsioAcceptor = nullptr;
		uint32 IDCounter = 10000;

		virtual bool OnClientConnected(std::shared_ptr<FakeConnection<T>> client)
			{
			return false;
			}

		virtual void OnClientDisconnected(std::shared_ptr<FakeConnection<T>> client)
			{
			}

		virtual void OnMessage(std::shared_ptr<FakeConnection<T>> client, FakeMessage<T> &msg)
			{
			}

	public:

		virtual void OnClientValidated(std::shared_ptr<FakeConnection<T>> client)
			{
			}

	public:

		FakeServer() = default;

		FakeServer(uint16 port)
			: AsioAcceptor(Context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port))
			{
			}

		virtual ~FakeServer()
			{
			Stop();
			}

		bool Start()
			{
			try
				{
				WaitForClientConnection();
				Thread = std::thread([this]() { Context.run(); });
				}
			catch (std::exception &e)
				{
				FAKE_LOG_ERROR("Exception: %s", e.what());
				}

			FAKE_LOG_TRACE("Server started!");
			return true;
			}

		void Stop()
			{
			Context.stop();

			if (Thread.joinable())
				Thread.join();

			FAKE_LOG_TRACE("Server stopped!");
			}

		void WaitForClientConnection()
			{
			// Prime context with an instruction to wait until a socket connects. This
			// is the purpose of an "acceptor" object. It will provide a unique socket
			// for each incoming connection attempt

			AsioAcceptor.async_accept([this](std::error_code ec, asio::ip::tcp::socket socket)
				{
				if (!ec)
					{
					FAKE_LOG_TRACE("[SERVER] New Connection: %s:%d", socket.remote_endpoint().address().to_string().c_str(), socket.remote_endpoint().port());

					std::shared_ptr<FakeConnection<T>> newconn =
						std::make_shared<FakeConnection<T>>(FakeConnection<T>::Owner::Server,
							Context, std::move(socket), MessagesIn);

					if (OnClientConnected(newconn))
						{
						Connections.push_back(std::move(newconn));
						Connections.back()->ConnectToClient(this, IDCounter++);

						FAKE_LOG_TRACE("[%d] Connection Approved!", Connections.back()->GetID());
						}
					else
						{
						FAKE_LOG_WARN("[-----] Connection Denied");
						}
					}
				else
					{
					FAKE_LOG_ERROR("[SERVER] New Connection Error: %s", ec.message().c_str());
					}

				WaitForClientConnection();
				});
			}

		void MessageClient(std::shared_ptr<FakeConnection<T>> client, const FakeMessage<T> &msg)
			{
			if (client && client->IsConnected())
				{
				client->Send(msg);
				}
			else
				{
				OnClientDisconnected(client);
				client.reset();

				Connections.erase(
					std::remove(Connections.begin(), Connections.end(), client), Connections.end());
				}
			}

		void MessageAllClients(const FakeMessage<T> &msg, std::shared_ptr<FakeConnection<T>> ignoreClient = nullptr)
			{
			bool invalidClientExists = false;

			for (auto &client : Connections)
				{
				if (client && client->IsConnected())
					{
					if (client != ignoreClient)
						client->Send(msg);
					}
				else
					{
					OnClientDisconnected(client);
					client.reset();
					invalidClientExists = true;
					}
				}

			if (invalidClientExists)
				Connections.erase(
					std::remove(Connections.begin(), Connections.end(), nullptr), Connections.end());
			}

		void StartListening()
			{
			while (1)
				Listen(-1, true);
			}

		void Listen(size_t maxMessages = -1, bool wait = false)
			{
			if (wait) MessagesIn.Wait();

			size_t messageCount = 0;
			while (messageCount < maxMessages && !MessagesIn.IsEmpty())
				{
				auto msg = MessagesIn.Front();
				MessagesIn.Dequeue();

				OnMessage(msg.Remote, msg.Message);
				messageCount++;
				}
			}
	};

