#include "FakePch.h"
#include "FakeWindowResizeEvent.h"

FakeWindowResizeEvent::FakeWindowResizeEvent(uint32 w, uint32 h)
	: Width(w), Height(h)
	{
	}

uint32 FakeWindowResizeEvent::GetWidth() const
	{
	return Width;
	}

uint32 FakeWindowResizeEvent::GetHeight() const
	{
	return Height;
	}

FakeString FakeWindowResizeEvent::ToString() const
	{
	return "WindowResizeEvent: " + FakeString::ToString(Width) + ", " + FakeString::ToString(Height);
	}

