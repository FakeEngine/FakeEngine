#pragma once

#include <Fake.h>

#include "Server.h"

class ServerTest : public FakeApplication
	{
	public:

		ServerTest()
			{
			}

		virtual void OnInit() override
			{
			Server s(60000);
			s.Start();
			s.StartListening();
			}

		virtual void OnShutdown() override
			{
			}
	};

