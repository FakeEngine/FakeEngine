/*****************************************************************
 * \file   FakeWindow.h
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

#include "Engine/Core/FakeCore.h"
#include "Engine/Core/FakeTimeStep.h"
#include "Engine/Core/Events/FakeEvents.h"
#include "Engine/Core/Window/FakeFileMenuBar.h"

using FakeEventCallbackFn = std::function<void(FakeEvent&)>;

enum class FakeWindowStyle
	{
	Normal = 0,
	Borderless
	};

/**
 *
 * The WindowData Struct will be cross shared over every Window API.
 * It contains the Window Properties which can be controlled by the User.
 *
 */
struct FAKE_API FakeWindowData
	{
	FakeString Title = "Fake Engine";
	uint32 Width = 1280, Height = 720;
	bool Centered = true, Fullscreen = false, Maximized = false, VSync = true, Visible = true, HasFocus = true, CursorEnabled = true;
	FakeWindowStyle Style = FakeWindowStyle::Normal;
	FakeEventCallbackFn EventFn;
	};

enum class FakeWindowMessageButtonType
	{
	BTN_NONE = 0,
	BTN_ABORT_RETRY_IGNORE,
	BTN_CANCEL_TRY_CONTINUE,
	BTN_HELP,
	BTN_OK,
	BTN_OK_CANCEL,
	BTN_RETRY_CANCEL,
	BTN_YES_NO,
	BTN_YES_NO_CANCEL
	};

enum class FakeWindowMessageIcons
	{
	ICON_NONE = 0,
	ICON_WARNING,
	ICON_QUESTION,
	ICON_INFORMATION,
	ICON_ERROR
	};

/**
 *
 * The Window Class is the base Interface for every window Implementation.
 * Every Window API must implement every virtual function inside this class.
 *
 */
class FAKE_API FakeWindow : public FakeRefCounted
	{
	protected:
		FakeWindowData Data;

	public:

		/**
		 *
		 * default constructor.
		 *
		 */
		FakeWindow() = default;

		/**
		 *
		 * Virtual Destructor to provide any extending class with the possibility to destroy it's allocated storage.
		 *
		 */
		virtual ~FakeWindow() = default;

		/**
		 *
		 * Sets the EventCallbackFunction. The Callback function is automatically being called with the corresponding Event if it occurres.
		 *
		 * @param callback The Callback Event function that should be called if a Event occurres.
		 */
		virtual void SetEventCallbackFn(const FakeEventCallbackFn &callback) = 0;

		/**
		 *
		 * The SetWindowIcon function should set the Window Icon in the top bar of the window and in the taskbar of the currently running system.
		 *
		 * @param filePath the Path to a Window Icon.
		 */
		virtual void SetWindowIcon(const FakeString &filePath) = 0;

		/**
		 *
		 * Updates the Window itself (evaluates the Events and swaps the Window buffer) and every child UI element.
		 *
		 * @param ts The current Delta Time.
		 */
		virtual void Flush(FakeTimeStep ts) = 0;

		/**
		 *
		 * Getter to get the current width of the window.
		 *
		 * @return Returns the Width of the Window.
		 */
		virtual uint32 GetWidth() = 0;

		/**
		 *
		 * Getter to get the current height of the window.
		 *
		 * @return Returns the Height of the Window.
		 */
		virtual uint32 GetHeight() = 0;

		/**
		 *
		 * Getter for the actual window handle. The window handle will always be api specific, therefore a void* is being returned.
		 *
		 * @return Returns the actual Window Handle. The Window Handle is API specific.
		 */
		virtual void *GetNativeWindow() = 0;

		/**
		 *
		 * Getter for the actual window handle. The window handle will always be api specific, therefore a void* is being returned.
		 *
		 * @return Returns the actual Window Handle. The Window Handle is API specific.
		 */
		virtual void *GetNativeWindow() const = 0;

		/**
		 *
		 * Getter to get the current width and height of the window.
		 *
		 * @return Returns the Width and the Height of the Window.
		 */
		virtual std::pair<int32, int32> GetWindowDimensions() = 0;

		/**
		 *
		 * Getter to get the current window position on the clients screen.
		 *
		 * @return Returns the Window x and y position.
		 */
		virtual std::pair<int32, int32> GetWindowPosition() = 0;

		/**
		 *
		 * Forces the window to close.
		 *
		 */
		virtual void CloseWindow() = 0;

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
		virtual int ShowMessageBox(const FakeString &title, const FakeString &message, FakeWindowMessageButtonType buttonType = FakeWindowMessageButtonType::BTN_NONE, FakeWindowMessageIcons iconType = FakeWindowMessageIcons::ICON_NONE) = 0;

		/**
		 *
		 * Adds a new Dockable view to the Window class.
		 *
		 * @param view The ChildWindow that is going to be added to the Window.
		 */
	//	virtual void AddChildView(const FakeRef<FakeUIView> &view) = 0;

		/**
		 *
		 * Removes a Dockable Window from the Window class.
		 *
		 * @param view The View that is going to be removed from the Window.
		 */
	//	virtual void RemoveChildView(const FakeRef<FakeUIView> &view) = 0;

		/**
		 *
		 * Sets a FileMenuBar for the window created by the Client.
		 *
		 * @param bar The FileMenubar that should be used for the MainWindow.
		 */
		virtual void SetMenuBar(const FakeRef<FakeFileMenuBar> &bar) = 0;

		/**
		 *
		 * Setter to enable or disable V-Sync.
		 *
		 * @param enabled Determines whether V-Sync should be enabled or disabled.
		 */
		virtual void SetVSync(bool enabled) = 0;

		/**
		 *
		 * Setter to enable or disable the Window.
		 *
		 * @param enabled Determines whether the window should be shown or hidden.
		 */
		virtual void SetVisible(bool enabled) = 0;

		/**
		 *
		 * Setter to bring up the window or minimize it.
		 *
		 * @param enabled Determines whether the window should get into the foreground to the user or should be minimized.
		 */
		virtual void SetFocus(bool enabled) = 0;

		/**
		 *
		 * Setter to enable or disable complete fullscreen mode.
		 *
		 * @param enabled Determines whether the application should change to a fullscreen window or to a bordered window.
		 */
		virtual void SetFullscreen(bool enabled) = 0;

		/**
		 *
		 * Enables the default cursor.
		 *
		 * @attention Here should be added the option to choose a cursor type.
		 */
		virtual void ShowCursor() = 0;

		/**
		 *
		 * Hides the current enabled cursor.
		 *
		 */
		virtual void HideCursor() = 0;

		/**
		 *
		 * Sets the window mode to either bordered fullscreen or normal bordered window.
		 *
		 * @param enabled Determines whether the window should be a bordered fullscreen window or a normal bordered window.
		 */
		virtual void Maximize(bool enabled) = 0;

		/**
		 *
		 * Centers the window dynamically to the clients screen.
		 *
		 */
		virtual void CenterWindow() = 0;

		/**
		 *
		 * Sets the window title.
		 *
		 * @param title The title that should be appear instead of the current title.
		 */
		virtual void SetTitle(const FakeString &title) = 0;

		/**
		 *
		 * Getter to get the current V-Sync setting.
		 *
		 * @return Returns true if V-Sync is enabled.
		 */
		virtual bool IsVSyncEnabled() = 0;

		/**
		 *
		 * Getter to get the current Visibility setting.
		 *
		 * @return Returns true if the window is visible.
		 */
		virtual bool IsVisible() = 0;

		/**
		 *
		 * Getter to get the current cursor setting.
		 *
		 * @return Returns true if the cursor is hidden.
		 */
		virtual bool IsCursorHidden() = 0;

		/**
		 *
		 * Getter to get the current focus setting.
		 *
		 * @return Returns true if the window has focus.
		 */
		virtual bool HasFocus() = 0;

		/**
		 *
		 * Getter to get the current maximized setting.
		 *
		 * @return Returns true if the window is maximized to the clients screen.
		 */
		virtual bool IsMaximized() = 0;

		/**
		 *
		 * Getter to get the current fullscreen setting.
		 *
		 * @return Returns true if the window is currently in fullscreen mode.
		 */
		virtual bool IsFullscreen() = 0;

		/**
		 *
		 * Getter to get the current centered setting.
		 *
		 * @return Returns true if the window has been centered to the clients screen.
		 */
		virtual bool IsCentered() = 0;

		/**
		 *
		 * Getter to get the current title.
		 *
		 * @return Returns the current window title.
		 */
		virtual const FakeString &GetTitle() = 0;

		/**
		 *
		 * Creates a new Instance of the Window.
		 *
		 * @param title The Title that the window should have.
		 * @param width The width that the window should have.
		 * @param height The height that the window should have.
		 * @return Returns a new Window Instance.
		 */
		static Scope<FakeWindow> Create(const FakeString &title, uint32 width, uint32 height);

		/**
		 *
		 * Creates a new Instance of the Window.
		 *
		 * @param data The data that should override the default Window settings.
		 * @return Returns a new Window Instance.
		 */
		static Scope<FakeWindow> Create(const FakeWindowData &data);
	};
