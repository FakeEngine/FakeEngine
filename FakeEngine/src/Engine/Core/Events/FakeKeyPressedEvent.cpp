#include "FakePch.h"
#include "FakeKeyPressedEvent.h"

FakeKeyPressedEvent::FakeKeyPressedEvent(int32 keyCode, int32 repeatCount)
	: KeyCode(keyCode), RepeatCount(repeatCount)
	{
	}

int32 FakeKeyPressedEvent::GetRepeatCount() const
	{
	return RepeatCount;
	}

int32 FakeKeyPressedEvent::GetRealKeyCode() const
	{
	return KeyCode;
	}

FakeKeyCode FakeKeyPressedEvent::GetKeyCode() const
	{
	return static_cast<FakeKeyCode>(KeyCode);
	}

FakeString FakeKeyPressedEvent::ToString() const
	{
	return "KeyPressedEvent: " + FakeString::ToString(KeyCode) + " (" + FakeString::ToString(RepeatCount) + " repeats)";
	}
