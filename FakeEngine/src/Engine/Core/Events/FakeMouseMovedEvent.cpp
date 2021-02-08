#include "FakePch.h"
#include "FakeMouseMovedEvent.h"

FakeMouseMovedEvent::FakeMouseMovedEvent(double x, double y)
	: MouseX(x), MouseY(y)
	{
	}

double FakeMouseMovedEvent::GetMouseX() const
	{
	return MouseX;
	}

double FakeMouseMovedEvent::GetMouseY() const
	{
	return MouseY;
	}

FakeString FakeMouseMovedEvent::ToString() const
	{
	return "MouseMovedEvent: " + FakeString::ToString(MouseX) + ", " + FakeString::ToString(MouseY);
	}

