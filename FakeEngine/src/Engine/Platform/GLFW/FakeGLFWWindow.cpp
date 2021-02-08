#include "FakePch.h"
#include "FakeGLFWWindow.h"

#include <stb_image.h>

#include "Engine/Platform/OpenGL/FakeOpenGLRenderingContext.h"

static bool GLFWInitialized = false;

static void GLFWErrorCallback(int32 error, const char *desc)
	{
	FAKE_LOG_ERROR("GLFW ERROR: %s (ErrorCode: %d)", desc, error);
	}

void FakeGLFWWindow::SetWindowEvents()
	{
	// Window Resize Event
	glfwSetWindowSizeCallback(Window, [](GLFWwindow *window, int32 width, int32 height)
		{
		FakeWindowData &data = *(FakeWindowData*) glfwGetWindowUserPointer(window);
		FakeWindowResizeEvent e(width, height);

		data.Width = width;
		data.Height = height;
		data.EventFn(e);
		});

	// Window Close Event
	glfwSetWindowCloseCallback(Window, [](GLFWwindow *window)
		{
		FakeWindowData &data = *(FakeWindowData*) glfwGetWindowUserPointer(window);
		FakeWindowCloseEvent e;
		data.EventFn(e);
		});

	// Key Events
	glfwSetCharCallback(Window, [](GLFWwindow *window, uint32 keyCode)
		{
		FakeWindowData &data = *(FakeWindowData*) glfwGetWindowUserPointer(window);
		FakeKeyTypedEvent e((int32)keyCode);
		data.EventFn(e);
		});

	glfwSetKeyCallback(Window, [](GLFWwindow *window, int32 key, int32 scanCode, int32 action, int32 mods)
		{
		FakeWindowData &data = *(FakeWindowData*) glfwGetWindowUserPointer(window);
		switch (action)
			{
			case GLFW_PRESS:
				{
				FakeKeyPressedEvent e(key, 0);
				data.EventFn(e);
				break;
				}

			case GLFW_RELEASE:
				{
				FakeKeyReleasedEvent e(key);
				data.EventFn(e);
				break;
				}

			case GLFW_REPEAT:
				{
				FakeKeyPressedEvent e(key, 1);
				data.EventFn(e);
				break;
				}
			}
		});

	// Mouse Events
	glfwSetMouseButtonCallback(Window, [](GLFWwindow *window, int32 button, int32 action, int32 mods)
		{
		FakeWindowData &data = *(FakeWindowData*) glfwGetWindowUserPointer(window);
		switch (action)
			{
			case GLFW_PRESS:
				{
				FakeMouseButtonPressedEvent e(button);
				data.EventFn(e);
				break;
				}

			case GLFW_RELEASE:
				{
				FakeMouseButtonReleasedEvent e(button);
				data.EventFn(e);
				break;
				}
			}
		});

	// Mouse Scroll Event
	glfwSetScrollCallback(Window, [](GLFWwindow *window, double xOffset, double yOffset)
		{
		FakeWindowData &data = *(FakeWindowData*) glfwGetWindowUserPointer(window);
		FakeMouseScrolledEvent e(xOffset, yOffset);
		data.EventFn(e);
		});

	// Mouse Position Event
	glfwSetCursorPosCallback(Window, [](GLFWwindow *window, double xPos, double yPos)
		{
		FakeWindowData &data = *(FakeWindowData*) glfwGetWindowUserPointer(window);
		FakeMouseMovedEvent e(xPos, yPos);
		data.EventFn(e);
		});
	}

FakeGLFWWindow::FakeGLFWWindow(const FakeString &title, uint32 width, uint32 height)
	{
	Data.Title = title;
	Data.Width = width;
	Data.Height = height;

	if (!GLFWInitialized)
		{
		GLFWInitialized = true;
		FAKE_ASSERT(glfwInit(), "GLFW could not be initialized!");
		glfwSetErrorCallback(GLFWErrorCallback);
		}

	if (Data.Style == FakeWindowStyle::Borderless)
		glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

	Window = glfwCreateWindow((int) Data.Width, (int) Data.Height, *Data.Title, NULL, NULL);

	#ifdef FAKE_RENDERER_OPENGL
		Context = new FakeOpenGLRenderingContext(this);
		Context->Init();
	#endif

	glfwSetWindowUserPointer(Window, &Data);
	SetWindowEvents();

	// Set Default Width and Height
	Placement.WindowWidth = Data.Width;
	Placement.WindowHeight = Data.Height;

	if (Data.Centered)
		CenterWindow();

	Maximize(Data.Maximized);
	SetFullscreen(Data.Fullscreen);
	SetVSync(Data.VSync);
	SetVisible(Data.Visible);
	SetFocus(Data.HasFocus);
	}

FakeGLFWWindow::FakeGLFWWindow(const FakeWindowData &data)
	{
	Data.Title = data.Title;
	Data.Width = data.Width;
	Data.Height = data.Height;
	Data.Centered = data.Centered;
	Data.CursorEnabled = data.CursorEnabled;
	Data.EventFn = data.EventFn;
	Data.Fullscreen = data.Fullscreen;
	Data.HasFocus = data.HasFocus;
	Data.Maximized = data.Maximized;
	Data.Visible = data.Visible;
	Data.VSync = data.VSync;

	if (!GLFWInitialized)
		{
		GLFWInitialized = true;
		FAKE_ASSERT(glfwInit(), "GLFW could not be initialized!");
		glfwSetErrorCallback(GLFWErrorCallback);
		}

	if (Data.Style == FakeWindowStyle::Borderless)
		glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

	Window = glfwCreateWindow((int) Data.Width, (int) Data.Height, *Data.Title, NULL, NULL);

	#ifdef FAKE_RENDERER_OPENGL
		Context = new FakeOpenGLRenderingContext(this);
		Context->Init();
	#endif

	glfwSetWindowUserPointer(Window, &Data);
	SetWindowEvents();

	// Set Default Width and Height
	Placement.WindowWidth = Data.Width;
	Placement.WindowHeight = Data.Height;

	if (Data.Centered)
		CenterWindow();

	Maximize(Data.Maximized);
	SetFullscreen(Data.Fullscreen);
	SetVSync(Data.VSync);
	SetVisible(Data.Visible);
	SetFocus(Data.HasFocus);
	}

FakeGLFWWindow::~FakeGLFWWindow()
	{
	if (Context)
		delete Context;

	if (Window)
		glfwDestroyWindow(Window);
	}

void FakeGLFWWindow::SetEventCallbackFn(const FakeEventCallbackFn &callback)
	{
	Data.EventFn = callback;
	}

void FakeGLFWWindow::SetWindowIcon(const FakeString &filePath)
	{
	FAKE_LOG_INFO("Loading Window Icon: %s", *filePath);

	int32 width, height;
	stbi_set_flip_vertically_on_load(1);
	stbi_uc *img = stbi_load(*filePath, &width, &height, 0, 4);

	GLFWimage icons[1];
	icons[0].width = width;
	icons[0].height = height;
	icons[0].pixels = img;

	glfwSetWindowIcon(Window, 1, icons);
	stbi_image_free(icons[0].pixels);
	}

void FakeGLFWWindow::Flush(FakeTimeStep ts)
	{
	glfwPollEvents();
	Context->SwapBuffers();

	//for (int i = 0; i < ChildViews.size(); ++i)
	//	ChildViews[i]->OnRender(ts);
	}

uint32 FakeGLFWWindow::GetWidth()
	{
	return Data.Width;
	}

uint32 FakeGLFWWindow::GetHeight()
	{
	return Data.Height;
	}

void *FakeGLFWWindow::GetNativeWindow()
	{
	return Window;
	}

void *FakeGLFWWindow::GetNativeWindow() const
	{
	return Window;
	}

std::pair<int32, int32> FakeGLFWWindow::GetWindowDimensions()
	{
	const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	return { mode->width, mode->height };
	}

std::pair<int32, int32> FakeGLFWWindow::GetWindowPosition()
	{
	int32 monitorX, monitorY;
	glfwGetMonitorPos(glfwGetPrimaryMonitor(), &monitorX, &monitorY);
	return { monitorX, monitorY };
	}

void FakeGLFWWindow::CloseWindow()
	{
	FakeWindowCloseEvent e;
	Data.EventFn(e);
	glfwDestroyWindow(Window);
	}

int32 FakeGLFWWindow::ShowMessageBox(const FakeString &title, const FakeString &message, FakeWindowMessageButtonType buttonType, FakeWindowMessageIcons iconType)
	{
	FAKE_ASSERT(false, "This API does not support Message Boxes!");
	return -1;
	}

/*
void FakeGLFWWindow::AddChildView(const FakeRef<FakeUIView> &view)
	{
	ChildViews.push_back(view);
	}

void FakeGLFWWindow::RemoveChildView(const FakeRef<FakeUIView> &view)
	{
	std::vector<FakeRef<FakeUIView>>::iterator it = std::find(ChildViews.begin(), ChildViews.end(), view);
	if (it != ChildViews.end())
		ChildViews.erase(it);
	}
*/

void FakeGLFWWindow::SetMenuBar(const FakeRef<FakeFileMenuBar> &bar)
	{
	FAKE_ASSERT(false, "This API does not support Message Boxes!");
	}

void FakeGLFWWindow::SetVSync(bool enabled)
	{
	Data.VSync = enabled;
	Context->SetSwapInterval(enabled);
	}

void FakeGLFWWindow::SetVisible(bool enabled)
	{
	Data.Visible = enabled;
	if (enabled)
		glfwShowWindow(Window);
	else
		glfwHideWindow(Window);
	}

void FakeGLFWWindow::SetFocus(bool enabled)
	{
	Data.HasFocus = enabled;
	if (enabled)
		glfwFocusWindow(Window);
	else
		glfwRestoreWindow(Window);
	}

void FakeGLFWWindow::SetFullscreen(bool enabled)
	{
	Data.Fullscreen = enabled;

	if (enabled)
		{
		// backup window position and window size
		glfwGetWindowPos(Window, &Placement.WindowPosX, &Placement.WindowPosY);
		glfwGetWindowSize(Window, &Placement.WindowWidth, &Placement.WindowHeight);

		// get resolution of monitor
		const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

		// switch to full screen
		glfwSetWindowMonitor(Window, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, 0);
		}
	else
		{
		// restore last window size and position
		glfwSetWindowMonitor(Window, nullptr, Placement.WindowPosX, Placement.WindowPosY, Placement.WindowWidth, Placement.WindowHeight, 0);
		}
	}

void FakeGLFWWindow::ShowCursor()
	{
	Data.CursorEnabled = true;
	glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

void FakeGLFWWindow::HideCursor()
	{
	Data.CursorEnabled = false;
	glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

void FakeGLFWWindow::Maximize(bool enabled)
	{
	Data.Maximized = enabled;
	if (enabled)
		glfwMaximizeWindow(Window);
	else
		glfwRestoreWindow(Window);
	}

void FakeGLFWWindow::CenterWindow()
	{
	Data.Centered = true;

	GLFWmonitor *monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode *mode = glfwGetVideoMode(monitor);

	int32 monitorX, monitorY;
	glfwGetMonitorPos(monitor, &monitorX, &monitorY);

	int32 width, height;
	glfwGetWindowSize(Window, &width, &height);

	int32 windowXPos = monitorX + (mode->width - width) / 2;
	int32 windowYPos = monitorY + (mode->height - height) / 2;
	glfwSetWindowPos(Window, windowXPos, windowYPos);
	Placement.WindowPosX = windowXPos;
	Placement.WindowPosY = windowYPos;
	}

void FakeGLFWWindow::SetTitle(const FakeString &title)
	{
	Data.Title = title;
	glfwSetWindowTitle(Window, *title);
	}

bool FakeGLFWWindow::IsVSyncEnabled()
	{
	return Data.VSync;
	}

bool FakeGLFWWindow::IsVisible()
	{
	return Data.Visible;
	}

bool FakeGLFWWindow::IsCursorHidden()
	{
	return !Data.CursorEnabled;
	}

bool FakeGLFWWindow::HasFocus()
	{
	return Data.HasFocus;
	}

bool FakeGLFWWindow::IsMaximized()
	{
	return Data.Maximized;
	}

bool FakeGLFWWindow::IsFullscreen()
	{
	return Data.Fullscreen;
	}

bool FakeGLFWWindow::IsCentered()
	{
	return Data.Centered;
	}

const FakeString &FakeGLFWWindow::GetTitle()
	{
	return Data.Title;
	}
