/*****************************************************************
 * \file   FakeMouseScrolledEvent.h
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

class FAKE_API FakeMouseScrolledEvent : public FakeEvent
	{
	private:
		double MouseX, MouseY;

	public:

		/**
		 *
		 * The Constructor sets the XOffset and YOffset of the mouse wheel if the user scrolls it.
		 *
		 * @param xOffset The amount on the X Axis of the Mouse Wheel if the User slides it to the left or right.
		 * @param yOffset The amount on the Y Axis of the Mouse Wheel if the User scrolls the mouse wheel.
		 */
		FakeMouseScrolledEvent(double xOffset, double yOffset);

		/**
		 *
		 * Getter to return the XOffset of the Mouse Wheel.
		 *
		 * @return Returns the new XOffset of the Mouse Wheel.
		 */
		double GetMouseX() const;

		/**
		 *
		 * Getter to return the YOffset of the Mouse Wheel.
		 *
		 * @return Returns the new YOffset of the Mouse Wheel.
		 */
		double GetMouseY() const;

		/**
		 *
		 * This overrides the ToString Method from FakeEvent and returns the Name of the Event and the current Values.
		 *
		 * @return Returns the Event formatted to a String.
		 */
		FakeString ToString() const override;

		FAKE_EVENT_CLASS_TYPE(MouseScrolled)
		FAKE_EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	};

