#include "FakePch.h"
#include "FakeFileMenuBar.h"

#include "Engine/Platform/Windows/FakeWindowsFileMenuBar.h"

FakeRef<FakeFileMenuBar> FakeFileMenuBar::Create()
	{
	#ifdef FAKE_PLATFORM_WINDOWS
		return FakeRef<FakeWindowsFileMenuBar>::Create();
	#endif
	}

