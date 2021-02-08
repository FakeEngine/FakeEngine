#include "FakePch.h"
#include "FakeKeyTypedEvent.h"

FakeKeyTypedEvent::FakeKeyTypedEvent(int keyCode)
	: KeyCode(keyCode)
	{
	}

int32 FakeKeyTypedEvent::GetKeyCode() const
	{
	return KeyCode;
	}

FakeString FakeKeyTypedEvent::ToString() const
	{
	return "KeyTypedEvent: " + FakeString::ToString(KeyCode);
	}
