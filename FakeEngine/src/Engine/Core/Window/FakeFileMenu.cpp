#include "FakePch.h"
#include "FakeFileMenu.h"

#include "Engine/Platform/Windows/FakeWindowsFileMenu.h"

FakeRef<FakeFileMenu> FakeFileMenu::Create(const FakeString &name)
	{
	#ifdef FAKE_PLATFORM_WINDOWS
		return FakeRef<FakeWindowsFileMenu>::Create(name);
	#endif
	}

