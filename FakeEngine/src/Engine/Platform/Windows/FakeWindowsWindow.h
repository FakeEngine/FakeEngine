/*****************************************************************
 * \file   FakeWindowsWindow.h
 * \brief  
 * 
 * \author Can Karka
 * \date   January 2021
 * 
 * Copyright (C) 2021 Can Karka
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *  https://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *********************************************************************/

#pragma once

#include <Windows.h>

#include "Engine/Core/Window/FakeWindow.h"
#include "Engine/Core/Window/FakeFileMenuBar.h"
#include "Engine/Renderer/FakeRenderingContext.h"

#define FAKE_WINDOW_BORDER_WIDTH 5
#define FAKE_WINDOW_MIN_WIDTH 200
#define FAKE_WINDOW_MIN_HEIGHT 200
#define FAKE_TITLEBAR_WIDTH 30

class FakeWindowsWindow : public FakeWindow
	{
	private:

		HWND Window;
		HICON WindowIcon = NULL;
		HCURSOR WindowCursor = NULL;
		FakeRenderingContext *Context;

		FakeRef<FakeFileMenuBar> MenuBar;
	//	std::vector<FakeRef<FakeUIView>> ChildViews;

		struct WNDPlacement
			{
			int32 WindowWidth = 0, WindowHeight = 0;
			WINDOWPLACEMENT Placement;
			};

		enum class WindowStyles : DWORD
			{
			windowed = WS_OVERLAPPEDWINDOW | WS_THICKFRAME | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
			aero_borderless = WS_POPUP | WS_THICKFRAME | WS_CAPTION | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX,
			basic_borderless = WS_POPUP | WS_THICKFRAME | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX
			};

		static WNDPlacement WindowPlacement;

		/**
		 *
		 * Sets all window related events.
		 *
		 */
		static LRESULT CALLBACK OnWindowEvent(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	public:

		/**
		 *
		 * constructor that initializes a new Windows window.
		 *
		 * @param title The title of the Window.
		 * @param width The Width of the Window.
		 * @param height The Height of the Window.
		 */
		FakeWindowsWindow(const FakeString &title, uint32 width, uint32 height);

		/**
		 *
		 * constructor that initializes a new Windows window.
		 *
		 * @param data The WindowData that contains all data needed for the Window.
		 */
		FakeWindowsWindow(const FakeWindowData &data);

		/**
		 *
		 * virtual destructor that destroys the window instance.
		 *
		 */
		virtual ~FakeWindowsWindow();

		/**
		 *
		 * Sets the EventCallbackFunction. The Callback function is automatically being called with the corresponding Event if it occurres.
		 *
		 * @param callback The Callback Event function that should be called if a Event occurres.
		 */
		virtual void SetEventCallbackFn(const FakeEventCallbackFn &callback) override;

		/**
		 *
		 * The SetWindowIcon function should set the Window Icon in the top bar of the window and in the taskbar of the currently running system.
		 *
		 * @param filePath the Path to a Window Icon.
		 */
		virtual void SetWindowIcon(const FakeString &filePath) override;

		/**
		 *
		 * Updates the Window itself (evaluates the Events and swaps the Window buffer) and every child UI element.
		 *
		 * @param ts The current Delta Time.
		 */
		virtual void Flush(FakeTimeStep ts) override;

		/**
		 *
		 * Getter to get the current width of the window.
		 *
		 * @return Returns the Width of the Window.
		 */
		virtual uint32 GetWidth() override;

		/**
		 *
		 * Getter to get the current height of the window.
		 *
		 * @return Returns the Height of the Window.
		 */
		virtual uint32 GetHeight() override;

		/**
		 *
		 * Getter for the actual window handle. The window handle is Windows specific, therefore a void* is being returned.
		 *
		 * @return Returns the actual Window Handle. The Window Handle is Windows specific.
		 */
		virtual void *GetNativeWindow() override;

		/**
		 *
		 * Getter for the actual window handle. The window handle is Windows specific, therefore a void* is being returned.
		 *
		 * @return Returns the actual Window Handle. The Window Handle is Windows specific.
		 */
		virtual void *GetNativeWindow() const override;

		/**
		 *
		 * Getter to get the current width and height of the window.
		 *
		 * @return Returns the Width and the Height of the Window.
		 */
		virtual std::pair<int32, int32> GetWindowDimensions() override;

		/**
		 *
		 * Getter to get the current window position on the clients screen.
		 *
		 * @return Returns the Window x and y position.
		 */
		virtual std::pair<int32, int32> GetWindowPosition() override;

		/**
		 *
		 * Forces the window to close.
		 *
		 */
		virtual void CloseWindow() override;

		/**
		 *
		 * Shows a MessageBox on the screen. It is intended for error messages and warnings directly to the user.
		 *
		 * @param title The WindowTitle of the message box.
		 * @param message The actual message that contains the error message or warning.
		 * @param buttonType The buttons that should be shown to the user.
		 * @param iconType The Icon that should appear right before the message.
		 * @return Returns the buttonID of the button that has been pressed by the user.
		 */
		virtual int32 ShowMessageBox(const FakeString &title, const FakeString &message, FakeWindowMessageButtonType buttonType = FakeWindowMessageButtonType::BTN_NONE, FakeWindowMessageIcons iconType = FakeWindowMessageIcons::ICON_NONE) override;

		/**
		 *
		 * Adds a new Dockable View to the Window class.
		 *
		 * @param view The ChildWindow that is going to be added to the Window.
		 */
	//	virtual void AddChildView(const FakeRef<FakeUIView> &view) override;

		/**
		 *
		 * Removes a Dockable View from the Window class.
		 *
		 * @param view The View that is going to be removed from the Window.
		 */
	//	virtual void RemoveChildView(const FakeRef<FakeUIView> &view) override;

		/**
		 *
		 * Sets a FileMenuBar for the window created by the Client.
		 *
		 * @param bar The FileMenubar that should be used for the MainWindow.
		 */
		virtual void SetMenuBar(const FakeRef<FakeFileMenuBar> &bar) override;

		/**
		 *
		 * Setter to enable or disable V-Sync.
		 *
		 * @param enabled Determines whether V-Sync should be enabled or disabled.
		 */
		virtual void SetVSync(bool enabled) override;

		/**
		 *
		 * Setter to enable or disable the Window.
		 *
		 * @param enabled Determines whether the window should be shown or hidden.
		 */
		virtual void SetVisible(bool enabled) override;

		/**
		 *
		 * Setter to bring up the window or minimize it.
		 *
		 * @param enabled Determines whether the window should get into the foreground to the user or should be minimized.
		 */
		virtual void SetFocus(bool enabled) override;

		/**
		 *
		 * Setter to enable or disable complete fullscreen mode.
		 *
		 * @param enabled Determines whether the application should change to a fullscreen window or to a bordered window.
		 */
		virtual void SetFullscreen(bool enabled) override;

		/**
		 *
		 * Enables the default cursor.
		 *
		 * @attention Here should be added the option to choose a cursor type.
		 */
		virtual void ShowCursor() override;

		/**
		 *
		 * Hides the current enabled cursor.
		 *
		 */
		virtual void HideCursor() override;

		/**
		 *
		 * Sets the window mode to either bordered fullscreen or normal bordered window.
		 *
		 * @param enabled Determines whether the window should be a bordered fullscreen window or a normal bordered window.
		 */
		virtual void Maximize(bool enabled) override;

		/**
		 *
		 * Centers the window dynamically to the clients screen.
		 *
		 */
		virtual void CenterWindow() override;

		/**
		 *
		 * Sets the window title.
		 *
		 * @param title The title that should be appear instead of the current title.
		 */
		virtual void SetTitle(const FakeString &title) override;

		/**
		 *
		 * Getter to get the current V-Sync setting.
		 *
		 * @return Returns true if V-Sync is enabled.
		 */
		virtual bool IsVSyncEnabled() override;

		/**
		 *
		 * Getter to get the current Visibility setting.
		 *
		 * @return Returns true if the window is visible.
		 */
		virtual bool IsVisible() override;

		/**
		 *
		 * Getter to get the current cursor setting.
		 *
		 * @return Returns true if the cursor is hidden.
		 */
		virtual bool IsCursorHidden() override;

		/**
		 *
		 * Getter to get the current focus setting.
		 *
		 * @return Returns true if the window has focus.
		 */
		virtual bool HasFocus() override;

		/**
		 *
		 * Getter to get the current maximized setting.
		 *
		 * @return Returns true if the window is maximized to the clients screen.
		 */
		virtual bool IsMaximized() override;

		/**
		 *
		 * Getter to get the current fullscreen setting.
		 *
		 * @return Returns true if the window is currently in fullscreen mode.
		 */
		virtual bool IsFullscreen() override;

		/**
		 *
		 * Getter to get the current centered setting.
		 *
		 * @return Returns true if the window has been centered to the clients screen.
		 */
		virtual bool IsCentered() override;

		/**
		 *
		 * Getter to get the current title.
		 *
		 * @return Returns the current window title.
		 */
		virtual const FakeString &GetTitle() override;
	};
