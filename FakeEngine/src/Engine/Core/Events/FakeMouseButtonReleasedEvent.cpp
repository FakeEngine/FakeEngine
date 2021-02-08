#include "FakePch.h"
#include "FakeMouseButtonReleasedEvent.h"

FakeMouseButtonReleasedEvent::FakeMouseButtonReleasedEvent(int32 button)
	: ButtonCode(button)
	{
	}

int32 FakeMouseButtonReleasedEvent::GetButton() const
	{
	return ButtonCode;
	}

FakeString FakeMouseButtonReleasedEvent::ToString() const
	{
	return "MouseButtonReleasedEvent: " + FakeString::ToString(ButtonCode);
	}

