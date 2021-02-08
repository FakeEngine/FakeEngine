#include "Sandbox.h"

FakeApplication *fake_create_app()
	{
	return new Sandbox("FakeEngine Sandbox", 1280, 720);
	}

