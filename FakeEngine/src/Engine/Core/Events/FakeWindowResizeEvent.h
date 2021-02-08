/*****************************************************************
 * \file   FakeWindowResizeEvent.h
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
 * The FakeWindowResize Event is being triggered if the Window gets resized in any way.
 *
 * @attention If the Window gets minimized The Resize Event will return a width and a height of 0.
 *
 */
class FakeWindowResizeEvent : public FakeEvent
	{
	private:
		uint32 Width, Height;

	public:

		/**
		 *
		 * Constructs the WindowResize Event which can be passed as a parameter then.
		 *
		 * @param w The new Width of the window
		 * @param h The new Height of the window
		 */
		FakeWindowResizeEvent(uint32 w, uint32 h);

		/**
		 *
		 * Getter to return the new Width of the Window.
		 *
		 * @return Returns the new Width of the Window
		 */
		uint32 GetWidth() const;

		/**
		 *
		 * Getter to return the new Height of the Window.
		 *
		 * @return Returns the new Height of the Window
		 */
		uint32 GetHeight() const;

		/**
		 *
		 * This overrides the ToString Method from FakeEvent and returns the Name of the Event and the current Values.
		 *
		 * @return Returns the Event formatted to a String.
		 */
		FakeString ToString() const override;

		FAKE_EVENT_CLASS_TYPE(WindowResize)
		FAKE_EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
