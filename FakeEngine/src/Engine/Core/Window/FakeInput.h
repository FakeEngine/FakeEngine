/*****************************************************************
 * \file   FakeInput.h
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
#include "Engine/Core/Defines/FakeKeyCodes.h"

/**
 *
 * The Input class is a cross-platform API which can be used to interact with the current Input devices.
 *
 * @note for now the Input class can only interact with a Keyboard and Mouse Input but Joysticks and Controllers will be added soon.
 *
 */
class FAKE_API FakeInput
	{
	public:

		/**
		 *
		 * takes a key and returns whether the key is pressed or not. This functions returns true if the key is pressed or hold down.
		 *
		 * @param keyCode The Key which should be checked (you can use the provided macros e.g. FAKE_KEY_LEFT_CONTROL)
		 * @return Returns true if the Key has been pressed.
		 */
		static bool IsKeyPressed(FakeKeyCode keyCode);

		/**
		 *
		 * takes a Mouse Button and returns if the button is pressed or not.
		 *
		 * @param buttonCode The Button which should be checked (you can use the provided macros e.g. FAKE_MOUSE_BUTTON_LEFT)
		 * @return Returns true if the Mouse Button has been pressed.
		 */
		static bool IsMouseButtonPressed(FakeMouseButtonCode buttonCode);

		/**
		 *
		 * This function returns the current Mouse Position relative to the Main Window.
		 *
		 * @return Returns the Mouse Position relative to the window in a pair.
		 */
		static std::pair<double, double> GetMousePosition();

		/**
		 *
		 * This function returns the current Mouse Position relative to the Clients screen.
		 *
		 * @return Returns the Mouse Position relative to the Clients Screen in a pair.
		 */
		static std::pair<double, double> GetAbsoluteMousePosition();

		/**
		 *
		 * This function returns the current X Position of the Mouse relative to the Main Window.
		 *
		 * @return Returns the Mouse X Position relative to the window.
		 */
		static double GetMouseX();

		/**
		 *
		 * This function returns the current Y Position of the Mouse relative to the Main Window.
		 *
		 * @return Returns the Mouse Y Position relative to the window.
		 */
		static double GetMouseY();

		/**
		 *
		 * This function returns the current X Position of the Mouse relative to the clients screen.
		 *
		 * @return Returns the Mouse X Position relative to the Clients Screen.
		 */
		static double GetAbsoluteMouseX();

		/**
		 *
		 * This function returns the current Y Position of the Mouse relative to the clients screen.
		 *
		 * @return Returns the Mouse Y Position relative to the Clients Screen.
		 */
		static double GetAbsoluteMouseY();
	};
