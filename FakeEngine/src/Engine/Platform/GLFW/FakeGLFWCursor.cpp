#include "FakePch.h"
#include "Engine/Core/Window/FakeCursor.h"

#ifdef FAKE_PLATFORM_WINDOWS

#ifdef FAKE_WINAPI_GLFW

#include <GLFW/glfw3.h>

static void _set_cursor(int cursorCode)
	{
	GLFWcursor *cursor = glfwCreateStandardCursor(cursorCode);
	glfwSetCursor((GLFWwindow *) FakeApplication::Get().GetWindow().GetNativeWindow(), cursor);
		}

static FakeCursorType ActiveCursor = FakeCursorType::Arrow;
static std::unordered_map<FakeCursorType, int> CursorNameMappings =
	{
		{ FakeCursorType::Arrow, GLFW_ARROW_CURSOR },
		{ FakeCursorType::Cross, GLFW_CROSSHAIR_CURSOR },
		{ FakeCursorType::Hand,	 GLFW_HAND_CURSOR },
		{ FakeCursorType::IBeam, GLFW_IBEAM_CURSOR }
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
