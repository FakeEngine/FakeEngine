#include "FakePch.h"
#include "FakeFileMenuEvent.h"

FakeFileMenuEvent::FakeFileMenuEvent(int id, FakeFileMenuType type)
	: ID(id), Type(type)
	{
	}

int32 FakeFileMenuEvent::GetID() const
	{
	return ID;
	}

FakeFileMenuType FakeFileMenuEvent::GetType() const
	{
	return Type;
	}

FakeString FakeFileMenuEvent::ToString() const
	{
	return "FileMenuEvent: " + FakeString((Type == FakeFileMenuType::FileMenu ? "FileMenu" : "PopupMenu")) + ":" + FakeString::ToString(ID);
	}

