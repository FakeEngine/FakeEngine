#include "FakePch.h"
#include "Engine/Core/Window/FakeInput.h"

#include "Engine/Core/FakeApplication.h"

#ifdef FAKE_PLATFORM_WINDOWS

#ifdef FAKE_WINAPI_GLFW
#include <GLFW/glfw3.h>

bool FakeInput::IsKeyPressed(FakeKeyCode keyCode)
	{
	GLFWwindow *window = static_cast<GLFWwindow*>(FakeApplication::Get().GetWindow().GetNativeWindow());
	int32 state = glfwGetKey(window, static_cast<int>(keyCode));
	return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

bool FakeInput::IsMouseButtonPressed(FakeMouseButtonCode buttonCode)
	{
	GLFWwindow *window = static_cast<GLFWwindow*>(FakeApplication::Get().GetWindow().GetNativeWindow());
	int32 state = glfwGetMouseButton(window, static_cast<int>(buttonCode));
	return state == GLFW_PRESS;
	}

std::pair<double, double> FakeInput::GetMousePosition()
	{
	GLFWwindow *window = static_cast<GLFWwindow*>(FakeApplication::Get().GetWindow().GetNativeWindow());

	double xPos, yPos;
	glfwGetCursorPos(window, &xPos, &yPos);

	uint32 width = FakeApplication::Get().GetWindow().GetWidth();
	uint32 height = FakeApplication::Get().GetWindow().GetHeight();

	if (xPos > width)
		xPos = width;
	else if (xPos < 0.0)
		xPos = 0.0;

	if (yPos > height)
		yPos = height;
	else if (yPos < 0.0)
		yPos = 0.0;

	return { xPos, yPos };
	}

std::pair<double, double> FakeInput::GetAbsoluteMousePosition()
	{
	GLFWwindow *window = static_cast<GLFWwindow*>(FakeApplication::Get().GetWindow().GetNativeWindow());

	double xPos, yPos;
	glfwGetCursorPos(window, &xPos, &yPos);

	return { xPos, yPos };
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
