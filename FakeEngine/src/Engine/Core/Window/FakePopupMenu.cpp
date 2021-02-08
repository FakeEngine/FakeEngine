#include "FakePch.h"
#include "FakePopupMenu.h"

#include "Engine/Platform/Windows/FakeWindowsPopupMenu.h"

FakeRef<FakePopupMenu> FakePopupMenu::Create(const FakeString &name)
	{
	#ifdef FAKE_PLATFORM_WINDOWS
		return FakeRef<FakeWindowsPopupMenu>::Create(name);
	#endif
	}

