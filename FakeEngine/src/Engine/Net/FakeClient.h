/*****************************************************************
 * \file   FakeClient.h
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
#include "FakeConnection.h"

template<typename T>
class FakeClient
	{
	protected:

		asio::io_context Context;
		std::thread Thread;
		std::unique_ptr<FakeConnection<T>> Connection;

	private:

		FakeThreadSafeQueue<FakeOwnedMessage<T>> MessagesIn;

	public:

		FakeClient()
			{
			}

		virtual ~FakeClient()
			{
			Disconnect();
			}

		bool Connect(const FakeString &host, const uint16 port)
			{
			try
				{
				asio::ip::tcp::resolver resolver(Context);
				asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(*host, std::to_string(port));

				Connection = std::make_unique<FakeConnection<T>>(FakeConnection<T>::Owner::Client, Context, asio::ip::tcp::socket(Context), MessagesIn);
				Connection->ConnectToServer(endpoints);
				Thread = std::thread([this]() { Context.run(); });
				}
			catch (std::exception &e)
				{
				FAKE_LOG_ERROR("Exception: %s", e.what());
				return false;
				}

			return true;
			}

		bool IsConnected() const
			{
			if (Connection)
				return Connection->IsConnected();

			return false;
			}

		void Disconnect()
			{
			if (IsConnected())
				Connection->Disconnect();

			Context.stop();

			if (Thread.joinable())
				Thread.join();

			Connection.release();
			}

		void Send(const FakeMessage<T> &msg)
			{
			if (IsConnected())
				Connection->Send(msg);
			}

		FakeThreadSafeQueue<FakeOwnedMessage<T>> &GetAllIncomingMessages()
			{
			return MessagesIn;
			}
	};
