/*****************************************************************
 * \file   FakeKeyPressedEvent.h
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

#include "FakeEventsBase.h"

/**
 *
 * The KeyPressed Event is being triggered if the User presses or holds down any key on the Keyboard.
 *
 */
class FakeKeyPressedEvent : public FakeEvent
	{
	private:
		int32 KeyCode;
		int32 RepeatCount;

	public:

		/**
		 *
		 * The Constructor sets the key pressed by the User.
		 *
		 * @param keyCode The KeyCode contains the key which was pressed or held down by the user.
		 * @param repeatCount Determines if a key is being hold down or not.
		 */
		FakeKeyPressedEvent(int32 keyCode, int32 repeatCount);

		/**
		 *
		 * Getter to return the RepeatCount.
		 *
		 * @return Returns the RepeatCount, which determines if the user holds or presses a key.
		 */
		int32 GetRepeatCount() const;

		/**
		 *
		 * Getter to return the KeyCode.
		 *
		 * @return Returns the KeyCode of the Key, which was pressed or hold down by the User.
		 */
		int32 GetRealKeyCode() const;

		/**
		 * 
		 * Getter to return the KeyCode.
		 * 
		 * @return Returns the KeyCode of the Key, which was pressed or hold down by the User.
		 */
		FakeKeyCode GetKeyCode() const;

		/**
		 *
		 * This overrides the ToString Method from FakeEvent and returns the Name of the Event and the current Values.
		 *
		 * @return Returns the Event formatted to a String.
		 */
		FakeString ToString() const override;

		FAKE_EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
		FAKE_EVENT_CLASS_TYPE(KeyPressed)
	};
