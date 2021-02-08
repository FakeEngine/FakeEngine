#include "FakePch.h"
#include "FakeFileDialogue.h"

#include "Engine/Platform/Windows/FakeWindowsFileDialogue.h"

void FakeFileDialogue::SetFilter(FakeFileDialogueFilter filter)
	{
	Filter = filter;
	}

FakeRef<FakeFileDialogue> FakeFileDialogue::Create()
	{
	#ifdef FAKE_PLATFORM_WINDOWS
		return FakeRef<FakeWindowsFileDialogue>::Create();
	#endif
	}

