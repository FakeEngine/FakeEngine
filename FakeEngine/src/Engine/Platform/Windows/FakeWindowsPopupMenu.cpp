#include "FakePch.h"
#include "FakeWindowsPopupMenu.h"

#include "Engine/Core/Window/FakeInput.h"

FakeWindowsPopupMenu::FakeWindowsPopupMenu(const FakeString &name)
	: Name(name)
	{
	PopupMenu = CreatePopupMenu();
	}

FakeWindowsPopupMenu::~FakeWindowsPopupMenu()
	{
	}

void FakeWindowsPopupMenu::AddMenuItem(const FakeRef<FakePopupMenuItem> &item)
	{
	LastPosition += item->Position;
	if (item->Visible)
		InsertMenuW(PopupMenu, item->Position, MF_BYPOSITION | MF_STRING | MNS_NOTIFYBYPOS, item->ID, item->Name.W_Str());
	else
		InsertMenuW(PopupMenu, item->Position, MF_BYPOSITION | MF_STRING | MNS_NOTIFYBYPOS | MF_GRAYED, item->ID, item->Name.W_Str());
	}

void FakeWindowsPopupMenu::AddMenuItem(const FakeString &name, int32 id, int32 position, bool visible)
	{
	LastPosition += position;
	if (visible)
		InsertMenuW(PopupMenu, position, MF_BYPOSITION | MF_STRING | MNS_NOTIFYBYPOS, id, name.W_Str());
	else
		InsertMenuW(PopupMenu, position, MF_BYPOSITION | MF_STRING | MNS_NOTIFYBYPOS | MF_GRAYED, id, name.W_Str());
	}

void FakeWindowsPopupMenu::AddSeperator()
	{
	InsertMenuW(PopupMenu, LastPosition + 1, MF_SEPARATOR, 0, NULL);
	}

void FakeWindowsPopupMenu::AddSubMenu(const FakeRef<FakePopupMenu> &other)
	{
	HMENU item = (HMENU) other->GetPopupMenuHandle();
	InsertMenuW(PopupMenu, LastPosition + 1, MF_STRING | MF_POPUP | MNS_NOTIFYBYPOS, (UINT_PTR) item, other->GetName().W_Str());
	}

void FakeWindowsPopupMenu::Show()
	{
	if (FakeInput::IsMouseButtonPressed(FakeMouseButtonCode::BUTTON_RIGHT))
		{
		HWND window = GetActiveWindow();
		SetForegroundWindow(window);

		POINT p;
		GetCursorPos(&p);

		TrackPopupMenuEx(PopupMenu, TPM_RIGHTBUTTON | TPM_RECURSE, p.x, p.y, window, NULL);
		}
	}

void *FakeWindowsPopupMenu::GetPopupMenuHandle()
	{
	return (void*)PopupMenu;
	}

void *FakeWindowsPopupMenu::GetPopupMenuHandle() const
	{
	return (void*)PopupMenu;
	}

FakeString &FakeWindowsPopupMenu::GetName()
	{
	return Name;
	}

const FakeString &FakeWindowsPopupMenu::GetName() const
	{
	return Name;
	}
