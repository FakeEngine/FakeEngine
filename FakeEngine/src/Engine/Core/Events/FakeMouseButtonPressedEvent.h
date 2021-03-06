/*****************************************************************
 * \file   FakeMouseButtonPressedEvent.h
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

class FAKE_API FakeMouseButtonPressedEvent : public FakeEvent
	{
	private:
		int32 ButtonCode;

	public:

		/**
		 *
		 * The Constructor takes the MouseButtonCode of the pressed button on the mouse.
		 *
		 * @param button The MouseButtonCode of the mouse button that was pressed by the User.
		 */
		FakeMouseButtonPressedEvent(int32 button);

		/**
		 *
		 * Getter to return the MouseButton Code of the pressed Mouse Button.
		 *
		 * @return Returns the ButtonCode of pressed Mouse Button.
		 */
		int32 GetButton() const;

		/**
		 *
		 * This overrides the ToString Method from FakeEvent and returns the Name of the Event and the current Values.
		 *
		 * @return Returns the Event formatted to a String.
		 */
		FakeString ToString() const override;

		FAKE_EVENT_CLASS_TYPE(MouseButtonPressed)
		FAKE_EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	};
