#include "FakePch.h"
#include "FakeKeyReleasedEvent.h"

FakeKeyReleasedEvent::FakeKeyReleasedEvent(int keyCode)
	: KeyCode(keyCode)
	{
	}

int32 FakeKeyReleasedEvent::GetKeyCode() const
	{
	return KeyCode;
	}

FakeString FakeKeyReleasedEvent::ToString() const
	{
	return "KeyReleasedEvent: " + FakeString::ToString(KeyCode);
	}

