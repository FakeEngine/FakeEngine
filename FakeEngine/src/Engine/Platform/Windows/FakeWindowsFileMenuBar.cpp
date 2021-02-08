#include "FakePch.h"
#include "FakeWindowsFileMenuBar.h"

FakeWindowsFileMenuBar::FakeWindowsFileMenuBar()
	{
	Menubar = CreateMenu();
	}

FakeWindowsFileMenuBar::~FakeWindowsFileMenuBar()
	{
	}

void FakeWindowsFileMenuBar::AddMenu(const FakeRef<FakeFileMenu> &menu)
	{
	HMENU menuItem = (HMENU)menu->GetMenuHandle();
	AppendMenuW(Menubar, MF_POPUP, (UINT_PTR)menuItem, menu->GetName().W_Str());
	}

void FakeWindowsFileMenuBar::RemoveMenu(const FakeRef<FakeFileMenu> &menu)
	{
	DestroyMenu((HMENU)menu->GetMenuHandle());
	}

void *FakeWindowsFileMenuBar::GetNativeMenuBar()
	{
	return (void*)Menubar;
	}

void *FakeWindowsFileMenuBar::GetNativeMenuBar() const
	{
	return (void*)Menubar;
	}
