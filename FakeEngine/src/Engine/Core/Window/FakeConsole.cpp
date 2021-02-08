#include "FakePch.h"
#include "FakeConsole.h"

#include "Engine/Platform/Windows/FakeWindowsConsole.h"

FakeRef<FakeConsole> FakeConsole::Create()
	{
	#ifdef FAKE_PLATFORM_WINDOWS
		return FakeRef<FakeWindowsConsole>::Create();
	#endif
	}
