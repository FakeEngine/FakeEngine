/*****************************************************************
 * \file   FakeEventsBase.h
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

#include "FakePch.h"

enum class FakeEventType
	{
	None = 0,
	WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoves, FileMenu,
	AppTick, AppUpdate, AppRender,
	KeyPressed, KeyReleased, KeyTyped,
	MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

enum FakeEventCategory
	{
	None = 0,
	EventCategoryApplication = FAKE_BIT(0),
	EventCategoryInput = FAKE_BIT(1),
	EventCategoryKeyboard = FAKE_BIT(2),
	EventCategoryMouse = FAKE_BIT(3),
	EventCategoryMouseButton = FAKE_BIT(4),
	};

template<typename T>
using FakeEventFn = std::function<bool(T&)>;

#define FAKE_EVENT_CLASS_TYPE(type) static FakeEventType GetStaticType() { return FakeEventType::##type; }\
	virtual FakeEventType GetEventType() const override { return GetStaticType(); }\
	virtual const char *GetName() const override { return #type; }

#define FAKE_EVENT_CLASS_CATEGORY(type) virtual int GetCategoryFlags() const override { return type; }

/**
 *
 * This class represents the base Event class.
 *
 */
class FAKE_API FakeEvent
	{
	friend class FakeEventDispatcher;

	public:
		bool Handled = false; /**< Indicates whether the Event has been handled or not. */

		/**
		 *
		 *  Is going to be implemented by the actual Events.
		 *
		 * @return Returns the correct EventType after it gets implemented by the subclass.
		 */
		virtual FakeEventType GetEventType() const = 0;

		/**
		 *
		 * * Is going to be implemented by the actual Events.
		 *
		 * @return Returns the Name of the Event after it gets implemented by the subclass.
		 */
		virtual const char *GetName() const = 0;

		/**
		 *
		 * Is going to be implemented by the actual Events.
		 *
		 * @return Returns the CategoryFlags of the Event after it gets implemented by the subclass.
		 */
		virtual int GetCategoryFlags() const = 0;

		/**
		 *
		 * Converts the Name of the Event to a String.
		 *
		 * @return New FakeString with the Name of the correct EventName.
		 */
		virtual FakeString ToString() const;

		/**
		 *
		 * Tells if the provided EventCategory is set in the implementing EventSubClass.
		 *
		 * @param c the Category which should be checked whether it is part of the EventSubClass.
		 * @return Returns true if the Category is a part of the EventCategories.
		 */
		bool IsInCategory(FakeEventCategory c);
	};

/**
 *
 * The EventDispatcher registers particular Events and calls the Functions which will be passed as arguments.
 *
 * ### Usage
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
 * FakeEventDispatcher dispatcher(<some Event>);
 * dispatcher.Dispatch<Some Event Type>(std::bind(&callbackFunc, this, std::placeholders::_1));
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
class FAKE_API FakeEventDispatcher
	{
	private:
		FakeEvent &Event;

	public:

		/**
		 *
		 * The Constructor takes a Event and stores it so that the Dispatch function can use this Event Instance.
		 *
		 * @param e The Event which should be listened for
		 */
		FakeEventDispatcher(FakeEvent &e)
			: Event(e)
			{
			}

		/**
		 *
		 * Dispatches an Event.
		 *
		 * @param func The Function that should be called with the corresponding EventType as the Argument.
		 * @return Returns true if the EventType is the same as the Template EventType provided in the <> braces.
		 */
		template<typename T, typename F>
		bool Dispatch(const F &func)
			{
			if (Event.GetEventType() == T::GetStaticType())
				{
				Event.Handled = func(static_cast<T &>(Event));
				return true;
				}

			return false;
			}
	};
