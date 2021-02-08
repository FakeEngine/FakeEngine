#pragma once

#include <Fake.h>

enum class MessageType
	{
	Ping
	};

class Server : public FakeServer<MessageType>
	{
	public:

		Server(uint16 port)
			: FakeServer(port)
			{
			}

		virtual bool OnClientConnected(std::shared_ptr<FakeConnection<MessageType>> client)
			{
			return true;
			}

		virtual void OnClientDisconnected(std::shared_ptr<FakeConnection<MessageType>> client)
			{
			}

		virtual void OnMessage(std::shared_ptr<FakeConnection<MessageType>> client, FakeMessage<MessageType> &msg)
			{
			if (msg.Header.ID == MessageType::Ping)
				{
				client->Send(msg);
				}
			}

		virtual void OnClientValidated(std::shared_ptr<FakeConnection<MessageType>> client)
			{
			}
	};

