#include "FakePch.h"
#include "Engine/Core/Window/FakeCursor.h"

#ifdef FAKE_PLATFORM_WINDOWS

#ifdef FAKE_WINAPI_WINDOWS
#include <Windows.h>

static void _set_cursor(LPCWSTR cursor)
	{
	SetCursor(LoadCursorW(NULL, cursor));
	}

static FakeCursorType ActiveCursor = FakeCursorType::Arrow;
static std::unordered_map<FakeCursorType, LPCWSTR> CursorNameMappings =
	{
		{ FakeCursorType::AppStarting,	IDC_APPSTARTING },
		{ FakeCursorType::Arrow,		IDC_ARROW },
		{ FakeCursorType::Cross,		IDC_CROSS },
		{ FakeCursorType::Hand,			IDC_HAND },
		{ FakeCursorType::Help,			IDC_HELP },
		{ FakeCursorType::IBeam,		IDC_IBEAM },
		{ FakeCursorType::No,			IDC_NO },
		{ FakeCursorType::SizeAll,		IDC_SIZEALL },
		{ FakeCursorType::SizeNESW,		IDC_SIZENESW },
		{ FakeCursorType::SizeNS,		IDC_SIZENS },
		{ FakeCursorType::SizeNWE,		IDC_SIZENWSE },
		{ FakeCursorType::SizeWE,		IDC_SIZEWE },
		{ FakeCursorType::UpArrow,		IDC_UPARROW },
		{ FakeCursorType::Wait,			IDC_WAIT },
	};

void FakeCursor::ActivateCursor(FakeCursorType type)
	{
	if (type != FakeCursorType::None)
		_set_cursor(CursorNameMappings[type]);
	}

void FakeCursor::SetCursor(FakeCursorType type)
	{
	ActiveCursor = type;
	}

FakeCursorType FakeCursor::GetActiveCursor()
	{
	return ActiveCursor;
	}

#endif


#endif
