/*****************************************************************
 * \file   FakeWindowCloseEvent.h
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
 * The Window Close Event is being triggered if the Close button is pressed or if the Application shuts itself down.
 *
 */
class FakeWindowCloseEvent : public FakeEvent
	{
	public:

		/**
		 *
		 * Constructs the WindowClose Event which can be passed as a parameter then.
		 *
		 */
		FakeWindowCloseEvent();

		/**
		 *
		 * This overrides the ToString Method from FakeEvent and returns the Name of the Event.
		 *
		 * @return Returns the Event formatted to a String
		 */
		FakeString ToString() const override;

		FAKE_EVENT_CLASS_TYPE(WindowClose)
		FAKE_EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

