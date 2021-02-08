#include "FakePch.h"
#include "FakeWindowsWindow.h"

#include <windowsx.h>
#include <stb_image.h>

#include "Engine/Utils/FakeWindowHelperUtils.h"
#include "Engine/Core/Window/FakeCursor.h"
#include "Engine/Platform/OpenGL/FakeOpenGLRenderingContext.h"

FakeWindowsWindow::WNDPlacement FakeWindowsWindow::WindowPlacement;

LRESULT FakeWindowsWindow::OnWindowEvent(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
	switch (msg)
		{
		case WM_CLOSE:
			{
			FakeWindowData *data = reinterpret_cast<FakeWindowData*>(GetWindowLongPtrW(hWnd, GWLP_USERDATA));
			if (data)
				{
				FakeWindowCloseEvent e;
				data->EventFn(e);
				}

			// Always return to the WIN32 API that the Window should not close because the Engine itself should manage that and not the API.
			return 0;
			}

		case WM_SIZE:
			{
			FakeWindowData *data = reinterpret_cast<FakeWindowData*>(GetWindowLongPtrW(hWnd, GWLP_USERDATA));
			if (data)
				{
				RECT windowRect;
				uint32 width;
				uint32 height;
				GetWindowRect(hWnd, &windowRect);

				// check if the window was minized
				if (windowRect.right < 0 || windowRect.bottom < 0)
					{
					width = 0;
					height = 0;
					data->Width = 0;
					data->Height = 0;
					}
				else
					{
					width = windowRect.right - windowRect.left;
					height = windowRect.bottom - windowRect.top;
					data->Width = width;
					data->Height = height;
					}

				FakeWindowResizeEvent e(width, height);
				if (data->EventFn != NULL)
					data->EventFn(e);
				}
			break;
			}

		case WM_MOUSEMOVE:
			{
			FakeWindowData *data = reinterpret_cast<FakeWindowData*>(GetWindowLongPtrW(hWnd, GWLP_USERDATA));
			if (data)
				{
				double xPos = (double) GET_X_LPARAM(lParam);
				double yPos = (double) GET_Y_LPARAM(lParam);

				FakeMouseMovedEvent e(xPos, yPos);
				data->EventFn(e);
				}
			break;
			}

		case WM_MOUSEWHEEL:
			{
			FakeWindowData *data = reinterpret_cast<FakeWindowData*>(GetWindowLongPtrW(hWnd, GWLP_USERDATA));
			if (data)
				{
				FakeMouseScrolledEvent e(0.0, (double)((short)HIWORD(wParam)) / (double)WHEEL_DELTA);
				data->EventFn(e);
				}
			break;
			}

		case WM_LBUTTONDOWN:
			{
			FakeWindowData *data = reinterpret_cast<FakeWindowData*>(GetWindowLongPtrW(hWnd, GWLP_USERDATA));
			if (data)
				{
				FakeMouseButtonPressedEvent e(static_cast<int>(FAKE_MOUSE_BUTTON_LEFT));
				data->EventFn(e);
				}
			break;
			}

		case WM_LBUTTONUP:
			{
			FakeWindowData *data = reinterpret_cast<FakeWindowData*>(GetWindowLongPtrW(hWnd, GWLP_USERDATA));
			if (data)
				{
				FakeMouseButtonReleasedEvent e(static_cast<int>(FAKE_MOUSE_BUTTON_LEFT));
				data->EventFn(e);
				}
			break;
			}

		case WM_RBUTTONDOWN:
			{
			FakeWindowData *data = reinterpret_cast<FakeWindowData*>(GetWindowLongPtrW(hWnd, GWLP_USERDATA));
			if (data)
				{
				FakeMouseButtonPressedEvent e(static_cast<int>(FAKE_MOUSE_BUTTON_RIGHT));
				data->EventFn(e);
				}
			break;
			}

		case WM_RBUTTONUP:
			{
			FakeWindowData *data = reinterpret_cast<FakeWindowData*>(GetWindowLongPtrW(hWnd, GWLP_USERDATA));
			if (data)
				{
				FakeMouseButtonReleasedEvent e(static_cast<int>(FAKE_MOUSE_BUTTON_RIGHT));
				data->EventFn(e);
				}
			break;
			}

		case WM_MBUTTONDOWN:
			{
			FakeWindowData *data = reinterpret_cast<FakeWindowData*>(GetWindowLongPtrW(hWnd, GWLP_USERDATA));
			if (data)
				{
				FakeMouseButtonPressedEvent e(static_cast<int>(FAKE_MOUSE_BUTTON_MIDDLE));
				data->EventFn(e);
				}
			break;
			}

		case WM_MBUTTONUP:
			{
			FakeWindowData *data = reinterpret_cast<FakeWindowData*>(GetWindowLongPtrW(hWnd, GWLP_USERDATA));
			if (data)
				{
				FakeMouseButtonReleasedEvent e(static_cast<int>(FAKE_MOUSE_BUTTON_MIDDLE));
				data->EventFn(e);
				}
			break;
			}

		case WM_CHAR:
			{
			FakeWindowData *data = reinterpret_cast<FakeWindowData*>(GetWindowLongPtrW(hWnd, GWLP_USERDATA));
			if (data)
				{
				FakeKeyTypedEvent e(fake_window_helper_windows_to_fake((int) wParam));
				data->EventFn(e);
				}
			break;
			}

		case WM_KEYDOWN:
			{
			FakeWindowData *data = reinterpret_cast<FakeWindowData*>(GetWindowLongPtrW(hWnd, GWLP_USERDATA));
			if (data)
				{
				int repeat = (int) (HIWORD(lParam) & KF_REPEAT) ? 1 : 0;
				FakeKeyPressedEvent e(fake_window_helper_windows_to_fake((int) wParam), repeat);
				data->EventFn(e);
				}
			break;
			}

		case WM_KEYUP:
			{
			FakeWindowData *data = reinterpret_cast<FakeWindowData*>(GetWindowLongPtrW(hWnd, GWLP_USERDATA));
			if (data)
				{
				FakeKeyReleasedEvent e(fake_window_helper_windows_to_fake((int) wParam));
				data->EventFn(e);
				}
			break;
			}

		case WM_COMMAND:
			{
			FakeWindowData *data = reinterpret_cast<FakeWindowData*>(GetWindowLongPtrW(hWnd, GWLP_USERDATA));
			if (data)
				{
				WORD eventID = LOWORD(wParam);
				FakeFileMenuEvent e((int32)eventID, FakeFileMenuType::FileMenu);
				data->EventFn(e);
				}

			return 0;
			}

		case WM_SETCURSOR:
			{
			FakeCursor::ActivateCursor(FakeCursor::GetActiveCursor());
			break;
			}

		case WM_SIZING:
			{
			FakeWindowData *data = reinterpret_cast<FakeWindowData*>(GetWindowLongPtrW(hWnd, GWLP_USERDATA));
			int32 edge = (int32)wParam;
			RECT *area = (RECT*)lParam;



			return true;
			}

		case WM_DROPFILES:
			{
			// TODO: NEEDS TESTING !!
			HDROP drop = (HDROP) wParam;
			POINT pt;
			int32 i;

			const int32 count = DragQueryFileW(drop, 0xffffffff, NULL, 0);
			FakeString *paths = new FakeString[count];

			DragQueryPoint(drop, &pt);

			for (i = 0; i < count; ++i)
				{
				const UINT length = DragQueryFileW(drop, i, NULL, 0);
				WCHAR *buffer = (WCHAR*)calloc((size_t)length + 1, sizeof(WCHAR));

				DragQueryFileW(drop, i, buffer, length + 1);
				paths[i] = FakeString(buffer);

				free(buffer);
				}

			for (i = 0; i < count; ++i)
				std::cout << paths[i] << std::endl;

			delete[] paths;
			DragFinish(drop);
			return 0;
			}

		case WM_GETMINMAXINFO:
			{
			LRESULT result = DefWindowProc(hWnd, msg, wParam, lParam);
			MINMAXINFO *minMax = reinterpret_cast<MINMAXINFO*>(lParam);
			minMax->ptMinTrackSize.x = FAKE_WINDOW_MIN_WIDTH;
			minMax->ptMinTrackSize.y = FAKE_WINDOW_MIN_HEIGHT;
			break;
			}

		/*
		case WM_NCCALCSIZE:
			{
			if (wParam)
				{
				NCCALCSIZE_PARAMS *params = reinterpret_cast<NCCALCSIZE_PARAMS *>(lParam);
				params->rgrc[0].bottom += FAKE_WINDOW_BORDER_WIDTH; // rgrc[0] is what makes this work, don't know what others (rgrc[1], rgrc[2]) do, but why not change them all?
				params->rgrc[0].right += FAKE_WINDOW_BORDER_WIDTH;
				params->rgrc[1].bottom += FAKE_WINDOW_BORDER_WIDTH;
				params->rgrc[1].right += FAKE_WINDOW_BORDER_WIDTH;
				params->rgrc[2].bottom += FAKE_WINDOW_BORDER_WIDTH;
				params->rgrc[2].right += FAKE_WINDOW_BORDER_WIDTH;
				return 0;
				}
			return DefWindowProc(hWnd, msg, wParam, lParam);
			}

		case WM_NCHITTEST:
			{
			RECT WindowRect;
			int32 x, y;

			GetWindowRect(hWnd, &WindowRect);
			x = GET_X_LPARAM(lParam) - WindowRect.left;
			y = GET_Y_LPARAM(lParam) - WindowRect.top;

			if (x >= FAKE_WINDOW_BORDER_WIDTH && x <= WindowRect.right - WindowRect.left - FAKE_WINDOW_BORDER_WIDTH && y >= FAKE_WINDOW_BORDER_WIDTH && y <= FAKE_TITLEBAR_WIDTH)
				return HTCAPTION;
			else if (x < FAKE_WINDOW_BORDER_WIDTH && y < FAKE_WINDOW_BORDER_WIDTH)
				return HTTOPLEFT;
			else if (x > WindowRect.right - WindowRect.left - FAKE_WINDOW_BORDER_WIDTH && y < FAKE_WINDOW_BORDER_WIDTH)
				return HTTOPRIGHT;
			else if (x > WindowRect.right - WindowRect.left - FAKE_WINDOW_BORDER_WIDTH && y > WindowRect.bottom - WindowRect.top - FAKE_WINDOW_BORDER_WIDTH)
				return HTBOTTOMRIGHT;
			else if (x < FAKE_WINDOW_BORDER_WIDTH && y > WindowRect.bottom - WindowRect.top - FAKE_WINDOW_BORDER_WIDTH)
				return HTBOTTOMLEFT;
			else if (x < FAKE_WINDOW_BORDER_WIDTH)
				return HTLEFT;
			else if (y < FAKE_WINDOW_BORDER_WIDTH)
				return HTTOP;
			else if (x > WindowRect.right - WindowRect.left - FAKE_WINDOW_BORDER_WIDTH)
				return HTRIGHT;
			else if (y > WindowRect.bottom - WindowRect.top - FAKE_WINDOW_BORDER_WIDTH)
				return HTBOTTOM;
			else
				return HTCLIENT;
			break;
			}
		*/
		}

	return DefWindowProc(hWnd, msg, wParam, lParam);
	}

FakeWindowsWindow::FakeWindowsWindow(const FakeString &title, uint32 width, uint32 height)
	{
	Data.Title = title;
	Data.Width = width;
	Data.Height = height;

	SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE);
	WindowCursor = LoadCursor(NULL, IDC_ARROW);
	WindowIcon = LoadIcon(NULL, IDI_APPLICATION);

	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hbrBackground = (HBRUSH) COLOR_WINDOW;
	wc.hCursor = WindowCursor;
	wc.hIcon = WindowIcon;
	wc.hIconSm = WindowIcon;
	wc.hInstance = NULL;
	wc.lpszClassName = L"FakeEngineClass";
	wc.lpszMenuName = L"FakeEngineClassMenu";
	wc.style = NULL;
	wc.lpfnWndProc = &FakeWindowsWindow::OnWindowEvent;
	FAKE_ASSERT(RegisterClassExW(&wc), "Window could not be registered!");

	DWORD dwExStyle = 0;
	DWORD dwStyle = 0;
	if (Data.Style == FakeWindowStyle::Borderless)
		{
		dwStyle = WS_POPUP | WS_VISIBLE;
		dwExStyle = WS_EX_APPWINDOW;
		}
	else if (Data.Style == FakeWindowStyle::Normal)
		{
		dwExStyle = WS_EX_OVERLAPPEDWINDOW;
		dwStyle = WS_OVERLAPPED ^ WS_THICKFRAME;
		}

	Window = CreateWindowExW(dwExStyle, L"FakeEngineClass", Data.Title.W_Str(), dwStyle, 0, 0, Data.Width, Data.Height, NULL, NULL, NULL, &Data);
	FAKE_ASSERT(Window, "Window could not be created!");

	SetWindowLongPtrW(Window, GWLP_USERDATA, (DWORD_PTR)&Data);

	#ifdef FAKE_RENDERER_OPENGL
		Context = new FakeOpenGLRenderingContext(this);
		Context->Init();
	#endif

	if (Data.Centered)
		CenterWindow();

	Maximize(Data.Maximized);
	SetFullscreen(Data.Fullscreen);
	SetVSync(Data.VSync);
	SetVisible(Data.Visible);
	SetFocus(Data.HasFocus);

	ShowWindow(Window, SW_SHOW);
	UpdateWindow(Window);
	}

FakeWindowsWindow::FakeWindowsWindow(const FakeWindowData &data)
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

	SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE);
	WindowCursor = LoadCursor(NULL, IDC_ARROW);
	WindowIcon = LoadIcon(NULL, IDI_APPLICATION);

	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hbrBackground = (HBRUSH) COLOR_WINDOW;
	wc.hCursor = WindowCursor;
	wc.hIcon = WindowIcon;
	wc.hIconSm = WindowIcon;
	wc.hInstance = NULL;
	wc.lpszClassName = L"FakeEngineClass";
	wc.lpszMenuName = L"FakeEngineClassMenu";
	wc.style = NULL;
	wc.lpfnWndProc = &FakeWindowsWindow::OnWindowEvent;
	FAKE_ASSERT(RegisterClassExW(&wc), "Window could not be registered!");

	DWORD dwExStyle = 0;
	DWORD dwStyle = 0;
	if (Data.Style == FakeWindowStyle::Borderless)
		{
		dwStyle = WS_POPUP | WS_VISIBLE;
		dwExStyle = WS_EX_APPWINDOW;
		}
	else if (Data.Style == FakeWindowStyle::Normal)
		{
		dwExStyle = WS_EX_OVERLAPPEDWINDOW;
		dwStyle = WS_OVERLAPPED ^ WS_THICKFRAME;
		}

	Window = CreateWindowExW(dwExStyle, L"FakeEngineClass", Data.Title.W_Str(), dwStyle, 0, 0, Data.Width, Data.Height, NULL, NULL, NULL, &Data);
	FAKE_ASSERT(Window, "Window could not be created!");

	SetWindowLongPtrW(Window, GWLP_USERDATA, (DWORD_PTR)&Data);

	#ifdef FAKE_RENDERER_OPENGL
		Context = new FakeOpenGLRenderingContext(this);
		Context->Init();
	#endif

	if (Data.Centered)
		CenterWindow();

	Maximize(Data.Maximized);
	SetFullscreen(Data.Fullscreen);
	SetVSync(Data.VSync);
	SetVisible(Data.Visible);
	SetFocus(Data.HasFocus);

	ShowWindow(Window, SW_SHOW);
	UpdateWindow(Window);
	}

FakeWindowsWindow::~FakeWindowsWindow()
	{
	if (Context)
		delete Context;

	if (Window)
		DestroyWindow(Window);
	}

void FakeWindowsWindow::SetEventCallbackFn(const FakeEventCallbackFn &callback)
	{
	Data.EventFn = callback;
	}

void FakeWindowsWindow::SetWindowIcon(const FakeString &filePath)
	{
	FAKE_LOG_INFO("Loading Window Icon: %s", *filePath);
	HANDLE hIcon = LoadImageW(0, filePath.W_Str(), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
	if (hIcon)
		{
		// Change both icons to the same icon handle.
		SendMessageW(Window, WM_SETICON, ICON_SMALL, (LPARAM) hIcon);
		SendMessageW(Window, WM_SETICON, ICON_BIG, (LPARAM) hIcon);

		// This will ensure that the application icon gets changed too.
		SendMessageW(GetWindow(Window, GW_OWNER), WM_SETICON, ICON_SMALL, (LPARAM) hIcon);
		SendMessageW(GetWindow(Window, GW_OWNER), WM_SETICON, ICON_BIG, (LPARAM) hIcon);
		}
	}

void FakeWindowsWindow::Flush(FakeTimeStep ts)
	{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	while (PeekMessageW(&msg, NULL, NULL, NULL, PM_REMOVE) > 0)
		{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
		}

	Context->SwapBuffers();

	/*
	for (int i = 0; i < ChildViews.size(); ++i)
		ChildViews[i]->OnRender(ts);
	*/
	}

uint32 FakeWindowsWindow::GetWidth()
	{
	return Data.Width;
	}

uint32 FakeWindowsWindow::GetHeight()
	{
	return Data.Height;
	}

void *FakeWindowsWindow::GetNativeWindow()
	{
	return Window;
	}

void *FakeWindowsWindow::GetNativeWindow() const
	{
	return Window;
	}

std::pair<int32, int32> FakeWindowsWindow::GetWindowDimensions()
	{
	HDC windowHDC = GetDC(Window);
	int32 width = GetDeviceCaps(windowHDC, DESKTOPHORZRES);
	int32 height = GetDeviceCaps(windowHDC, DESKTOPVERTRES);
	return { width, height };
	}

std::pair<int32, int32> FakeWindowsWindow::GetWindowPosition()
	{
	RECT windowRect;
	GetWindowRect(Window, &windowRect);
	return { windowRect.left, windowRect.top };
	}

void FakeWindowsWindow::CloseWindow()
	{
	FakeWindowCloseEvent e;
	Data.EventFn(e);
	PostQuitMessage(0);
	}

int32 FakeWindowsWindow::ShowMessageBox(const FakeString &title, const FakeString &message, FakeWindowMessageButtonType buttonType, FakeWindowMessageIcons iconType)
	{
	uint32 iconFlags;
	uint32 buttonFlags;

	switch (buttonType)
		{
		case FakeWindowMessageButtonType::BTN_ABORT_RETRY_IGNORE:
			iconFlags = MB_ABORTRETRYIGNORE;
			break;

		case FakeWindowMessageButtonType::BTN_CANCEL_TRY_CONTINUE:
			iconFlags = MB_CANCELTRYCONTINUE;
			break;

		case FakeWindowMessageButtonType::BTN_HELP:
			iconFlags = MB_HELP;
			break;

		case FakeWindowMessageButtonType::BTN_OK:
			iconFlags = MB_OK;
			break;

		case FakeWindowMessageButtonType::BTN_OK_CANCEL:
			iconFlags = MB_OKCANCEL;
			break;

		case FakeWindowMessageButtonType::BTN_RETRY_CANCEL:
			iconFlags = MB_RETRYCANCEL;
			break;

		case FakeWindowMessageButtonType::BTN_YES_NO:
			iconFlags = MB_YESNO;
			break;

		case FakeWindowMessageButtonType::BTN_YES_NO_CANCEL:
			iconFlags = MB_YESNOCANCEL;
			break;

		default:
			iconFlags = MB_YESNO;
			break;
		}

	switch (iconType)
		{
		case FakeWindowMessageIcons::ICON_ERROR:
			buttonFlags = MB_ICONERROR;
			break;

		case FakeWindowMessageIcons::ICON_INFORMATION:
			buttonFlags = MB_ICONINFORMATION;
			break;

		case FakeWindowMessageIcons::ICON_QUESTION:
			buttonFlags = MB_ICONQUESTION;
			break;

		case FakeWindowMessageIcons::ICON_WARNING:
			buttonFlags = MB_ICONWARNING;
			break;

		default:
			buttonFlags = MB_ICONINFORMATION;
			break;
		}

	return MessageBoxW(Window, message.W_Str(), title.W_Str(), iconFlags | buttonFlags);
	}

/*

void FakeWindowsWindow::AddChildView(const FakeRef<FakeUIView> &view)
	{
	ChildViews.push_back(view);
	}

void FakeWindowsWindow::RemoveChildView(const FakeRef<FakeUIView> &view)
	{
	std::vector<FakeRef<FakeUIView>>::iterator it = std::find(ChildViews.begin(), ChildViews.end(), view);
	if (it != ChildViews.end())
		ChildViews.erase(it);
	}
*/

void FakeWindowsWindow::SetMenuBar(const FakeRef<FakeFileMenuBar> &bar)
	{
	MenuBar = bar;
	SetMenu(Window, (HMENU)MenuBar->GetNativeMenuBar());
	}

void FakeWindowsWindow::SetVSync(bool enabled)
	{
	Data.VSync = enabled;
	Context->SetSwapInterval(enabled);
	}

void FakeWindowsWindow::SetVisible(bool enabled)
	{
	Data.Visible = enabled;
	ShowWindow(Window, enabled);
	}

void FakeWindowsWindow::SetFocus(bool enabled)
	{
	Data.HasFocus = enabled;
	if (enabled)
		::SetFocus(Window);
	else
		ShowWindow(Window, SW_MINIMIZE);
	}

void FakeWindowsWindow::SetFullscreen(bool enabled)
	{
	Data.Fullscreen = enabled;
	if (enabled)
		{
		auto [width, height] = GetWindowDimensions();

		GetWindowPlacement(Window, &WindowPlacement.Placement);
		WindowPlacement.WindowWidth = width;
		WindowPlacement.WindowHeight = height;

		SetWindowLongPtrW(Window, GWL_EXSTYLE, WS_EX_APPWINDOW | WS_EX_TOPMOST);
		SetWindowLongPtrW(Window, GWL_STYLE, WS_POPUP | WS_VISIBLE);
		SetWindowPos(Window, HWND_TOPMOST, 0, 0, width, height, SWP_SHOWWINDOW);

		ShowWindow(Window, SW_MAXIMIZE);
		UpdateWindow(Window);
		}
	else
		{
		SetWindowPlacement(Window, &WindowPlacement.Placement);
		SetWindowLongPtrW(Window, GWL_EXSTYLE, WS_EX_OVERLAPPEDWINDOW);
		SetWindowLongPtrW(Window, GWL_STYLE, WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME);

		ShowWindow(Window, true);
		UpdateWindow(Window);
		}
	}

void FakeWindowsWindow::ShowCursor()
	{
	Data.CursorEnabled = true;
	SetCursor(WindowCursor);
	::ShowCursor(true);
	}

void FakeWindowsWindow::HideCursor()
	{
	Data.CursorEnabled = false;
	SetCursor(NULL);
	::ShowCursor(false);
	}

void FakeWindowsWindow::Maximize(bool enabled)
	{
	Data.Maximized = enabled;
	if (enabled)
		ShowWindow(Window, SW_MAXIMIZE);
	else
		ShowWindow(Window, true);
	}

void FakeWindowsWindow::CenterWindow()
	{
	Data.Centered = true;

	RECT windowRect;
	GetWindowRect(Window, &windowRect);

	int32 xPos = (GetSystemMetrics(SM_CXSCREEN) - windowRect.right) / 2;
	int32 yPos = (GetSystemMetrics(SM_CYSCREEN) - windowRect.bottom) / 2;
	SetWindowPos(Window, 0, xPos, yPos, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
	}

void FakeWindowsWindow::SetTitle(const FakeString &title)
	{
	Data.Title = title;
	SetWindowTextW(Window, title.W_Str());
	}

bool FakeWindowsWindow::IsVSyncEnabled()
	{
	return Data.VSync;
	}

bool FakeWindowsWindow::IsVisible()
	{
	return Data.Visible;
	}

bool FakeWindowsWindow::IsCursorHidden()
	{
	return !Data.CursorEnabled;
	}

bool FakeWindowsWindow::HasFocus()
	{
	return Data.HasFocus;
	}

#undef IsMaximized
bool FakeWindowsWindow::IsMaximized()
	{
	return Data.Maximized;
	}
#define IsMaximized(hWnd) IsZoomed(hWnd)

bool FakeWindowsWindow::IsFullscreen()
	{
	return Data.Fullscreen;
	}

bool FakeWindowsWindow::IsCentered()
	{
	return Data.Centered;
	}

const FakeString &FakeWindowsWindow::GetTitle()
	{
	return Data.Title;
	}
