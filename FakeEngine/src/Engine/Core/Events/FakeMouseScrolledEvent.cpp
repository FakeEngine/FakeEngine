#include "FakePch.h"
#include "FakeMouseScrolledEvent.h"

FakeMouseScrolledEvent::FakeMouseScrolledEvent(double xOffset, double yOffset)
	: MouseX(xOffset), MouseY(yOffset)
	{
	}

double FakeMouseScrolledEvent::GetMouseX() const
	{
	return MouseX;
	}

double FakeMouseScrolledEvent::GetMouseY() const
	{
	return MouseY;
	}

FakeString FakeMouseScrolledEvent::ToString() const
	{
	return "MouseScrolledEvent: " + FakeString::ToString(MouseX) + ", " + FakeString::ToString(MouseY);
	}

