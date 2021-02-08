#include "FakePch.h"
#include "Engine/Core/Window/FakeInput.h"

#include "Engine/Utils/FakeWindowHelperUtils.h"
#include "Engine/Core/FakeApplication.h"

#ifdef FAKE_PLATFORM_WINDOWS

#ifdef FAKE_WINAPI_WINDOWS
#include <Windows.h>

bool FakeInput::IsKeyPressed(FakeKeyCode keyCode)
	{
	return (GetKeyState(fake_window_helper_fake_to_windows(keyCode)) & 0x8000);
	}

bool FakeInput::IsMouseButtonPressed(FakeMouseButtonCode buttonCode)
	{
	if (buttonCode == FakeMouseButtonCode::BUTTON_LEFT) return (GetKeyState(VK_LBUTTON) & 0x8000);
	else if (buttonCode == FakeMouseButtonCode::BUTTON_RIGHT) return (GetKeyState(VK_RBUTTON) & 0x8000);
	else if (buttonCode == FakeMouseButtonCode::BUTTON_MIDDLE) return (GetKeyState(VK_MBUTTON) & 0x8000);

	return false;
	}

std::pair<double, double> FakeInput::GetMousePosition()
	{
	HWND window = static_cast<HWND>(FakeApplication::Get().GetWindow().GetNativeWindow());
	int32 width = (int32)FakeApplication::Get().GetWindow().GetWidth();
	int32 height = (int32)FakeApplication::Get().GetWindow().GetHeight();

	POINT pos;
	GetCursorPos(&pos);

	if (window)
		ScreenToClient(window, &pos);

	if (pos.x > width)
		pos.x = (LONG)width;
	else if (pos.x < 0L)
		pos.x = 0L;

	if (pos.y > height)
		pos.y = (LONG)height;
	else if (pos.y < 0L)
		pos.y = 0L;

	return { (double)pos.x, (double)pos.y };
	}

std::pair<double, double> FakeInput::GetAbsoluteMousePosition()
	{
	POINT pos;
	GetCursorPos(&pos);

	return { (double)pos.x, (double)pos.y };
	}

double FakeInput::GetMouseX()
	{
	auto [x, y] = GetMousePosition();
	return x;
	}

double FakeInput::GetMouseY()
	{
	auto [x, y] = GetMousePosition();
	return y;
	}

double FakeInput::GetAbsoluteMouseX()
	{
	auto [x, y] = GetAbsoluteMousePosition();
	return x;
	}

double FakeInput::GetAbsoluteMouseY()
	{
	auto [x, y] = GetAbsoluteMousePosition();
	return y;
	}

#endif

#endif
