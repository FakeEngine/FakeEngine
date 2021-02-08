/*****************************************************************
 * \file   FakeKeyReleasedEvent.h
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
 * The KeyReleased Event is being triggered if the User releases a Key after he pressed it or hold it down.
 *
 */
class FAKE_API FakeKeyReleasedEvent : public FakeEvent
	{
	private:
		int32 KeyCode;

	public:

		/**
		 *
		 * The Constructor sets the KeyCode of the Key that was released by the User.
		 *
		 * @param keyCode The KeyCode of the Key that was released by the User.
		 */
		FakeKeyReleasedEvent(int keyCode);

		/**
		 *
		 * Getter to return the KeyCode.
		 *
		 * @return Returns the KeyCode of the Key, which was pressed or hold down by the User.
		 *
		 */
		int32 GetKeyCode() const;

		/**
		 *
		 * This overrides the ToString Method from FakeEvent and returns the Name of the Event and the current Values.
		 *
		 * @return Returns the Event formatted to a String.
		 */
		FakeString ToString() const override;

		FAKE_EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
		FAKE_EVENT_CLASS_TYPE(KeyReleased)
	};

