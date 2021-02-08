/*****************************************************************
 * \file   FakeMouseButtonMovedEvent.h
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
 * The MouseMoved Event is being triggered if the User moves the Mouse.
 *
 */
class FAKE_API FakeMouseMovedEvent : public FakeEvent
	{
	private:
		double MouseX, MouseY;

	public:

		/**
		 *
		 * The Constructor sets the new X and Y Position of the Users Mouse.
		 *
		 * @param x The new X Position of the Mouse on the clients screen.
		 * @param y The new Y Position of the Mouse on the clients screen.
		 */
		FakeMouseMovedEvent(double x, double y);

		/**
		 *
		 * Getter to return the X-Position of the Mouse.
		 *
		 * @return Returns the new X-Position of the Mouse.
		 */
		double GetMouseX() const;

		/**
		 *
		 * Getter to return the Y-Position of the Mouse.
		 *
		 * @return Returns the new Y-Position of the Mouse.
		 */
		double GetMouseY() const;

		/**
		 *
		 * This overrides the ToString Method from FakeEvent and returns the Name of the Event and the current Values.
		 *
		 * @return Returns the Event formatted to a String.
		 */
		FakeString ToString() const override;

		FAKE_EVENT_CLASS_TYPE(MouseMoved)
		FAKE_EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	};

