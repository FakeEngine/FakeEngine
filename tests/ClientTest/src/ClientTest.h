#pragma once

#include <Fake.h>

#include "Client.h"

class ClientTest : public FakeApplication
	{
	public:

		ClientTest()
			: FakeApplication("FakeEngine ClientTest", 1280, 720)
			{
			}

		virtual void OnInit() override
			{
			PushLayer(new ClientLayer());
			}

		virtual void OnShutdown() override
			{
			}
	};

