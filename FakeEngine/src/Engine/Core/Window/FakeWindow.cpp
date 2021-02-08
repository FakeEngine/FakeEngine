#include "FakePch.h"
#include "FakeWindow.h"

#include "Engine/Platform/Windows/FakeWindowsWindow.h"
#include "Engine/Platform/GLFW/FakeGLFWWindow.h"

Scope<FakeWindow> FakeWindow::Create(const FakeString &title, uint32 width, uint32 height)
	{
	#ifdef FAKE_PLATFORM_WINDOWS
		#ifdef FAKE_WINAPI_WINDOWS
			return CreateScope<FakeWindowsWindow>(title, width, height);
		#elif FAKE_WINAPI_GLFW
			return CreateScope<FakeGLFWWindow>(title, width, height);
		#endif
	#else
		return nullptr;
	#endif
	}

Scope<FakeWindow> FakeWindow::Create(const FakeWindowData &data)
	{
	#ifdef FAKE_PLATFORM_WINDOWS
		#ifdef FAKE_WINAPI_WINDOWS
			return CreateScope<FakeWindowsWindow>(data);
		#elif FAKE_WINAPI_GLFW
			return CreateScope<FakeGLFWWindow>(data);
		#endif
	#else
		return nullptr;
	#endif
	}

