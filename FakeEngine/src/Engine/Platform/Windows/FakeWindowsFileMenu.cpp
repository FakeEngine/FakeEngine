#include "FakePch.h"
#include "FakeWindowsFileMenu.h"

FakeWindowsFileMenu::FakeWindowsFileMenu(const FakeString &name)
	: Name(name)
	{
	Menu = CreateMenu();
	}

FakeWindowsFileMenu::~FakeWindowsFileMenu()
	{
	}

void FakeWindowsFileMenu::AddMenuItem(const FakeRef<FakeFileMenuItem> &item)
	{
	if (item->Visible)
		AppendMenuW(Menu, MF_STRING, item->ID, item->Name.W_Str());
	else
		AppendMenuW(Menu, MF_STRING | MF_GRAYED, item->ID, item->Name.W_Str());
	}

void FakeWindowsFileMenu::AddMenuItem(const FakeFileMenuItem &item)
	{
	if (item.Visible)
		AppendMenuW(Menu, MF_STRING, item.ID, item.Name.W_Str());
	else
		AppendMenuW(Menu, MF_STRING | MF_GRAYED, item.ID, item.Name.W_Str());
	}

void FakeWindowsFileMenu::AddMenuItem(const FakeString &name, int32 id, bool visible)
	{
	FakeFileMenuItem item;
	item.Name = name;
	item.ID = id;
	item.Visible = visible;
	item.Seperator = false;

	if (item.Visible)
		AppendMenuW(Menu, MF_STRING, item.ID, item.Name.W_Str());
	else
		AppendMenuW(Menu, MF_STRING | MF_GRAYED, item.ID, item.Name.W_Str());
	}

void FakeWindowsFileMenu::AddSubMenu(const FakeRef<FakeFileMenu> &other)
	{
	HMENU menuItem = (HMENU) other->GetMenuHandle();
	AppendMenuW(Menu, MF_POPUP, (UINT_PTR) menuItem, other->GetName().W_Str());
	}

void FakeWindowsFileMenu::AddMenuSeperator()
	{
	AppendMenuW(Menu, MF_SEPARATOR, 0, NULL);
	}

void *FakeWindowsFileMenu::GetMenuHandle()
	{
	return (void*)Menu;
	}

void *FakeWindowsFileMenu::GetMenuHandle() const
	{
	return (void*)Menu;
	}

FakeString &FakeWindowsFileMenu::GetName()
	{
	return Name;
	}

const FakeString &FakeWindowsFileMenu::GetName() const
	{
	return Name;
	}

bool FakeWindowsFileMenu::EnableMenuItem(int32 id, bool enabled)
	{
	if (enabled)
		return ::EnableMenuItem(Menu, id, MF_ENABLED);
	else
		return ::EnableMenuItem(Menu, id, MF_GRAYED);
	}
