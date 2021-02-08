#include "FakePch.h"
#include "FakeMouseButtonPressedEvent.h"

FakeMouseButtonPressedEvent::FakeMouseButtonPressedEvent(int32 button)
	: ButtonCode(button)
	{
	}

int32 FakeMouseButtonPressedEvent::GetButton() const
	{
	return ButtonCode;
	}

FakeString FakeMouseButtonPressedEvent::ToString() const
	{
	return "MouseButtonPressedEvent: " + FakeString::ToString(ButtonCode);
	}
