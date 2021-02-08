#pragma once

#include <Fake.h>

enum class MessageType
	{
	Ping
	};

class Client : public FakeClient<MessageType>
	{
	public:

		void SendPing()
			{
			FakeMessage<MessageType> msg;
			msg.Header.ID = MessageType::Ping;

			std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();
			msg << timeNow;

			Send(msg);
			}
	};

class ClientLayer : public FakeLayer
	{
	private:
		Client c;

	public:

		virtual void OnAttach() override
			{
			c.Connect("127.0.0.1", 60000);
			}

		virtual void OnDetach() override
			{
			}

		virtual void OnEvent(FakeEvent &e) override
			{
			}

		virtual void OnRender(FakeTimeStep ts) override
			{
			if (FakeInput::IsKeyPressed(FakeKeyCode::P))
				{
				c.SendPing();
				}

			if (!c.GetAllIncomingMessages().IsEmpty())
				{
				auto msg = c.GetAllIncomingMessages().Front().Message;
				c.GetAllIncomingMessages().Dequeue();

				switch (msg.Header.ID)
					{
					case MessageType::Ping:
						{
						std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();
						std::chrono::system_clock::time_point timeThen;
						msg >> timeThen;

						double pingTime = std::chrono::duration<double>(timeNow - timeThen).count();
						FAKE_LOG_TRACE("PING: %f", pingTime);
						break;
						}
					}
				}
			}
	};
