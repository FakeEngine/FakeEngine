/*****************************************************************
 * \file   FakeLayer.h
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

#include "Engine/Core/Events/FakeEventsBase.h"
#include "Engine/Core/FakeTimeStep.h"
#include "Engine/Core/FakeCore.h"
#include "Engine/Core/DataTypes/FakeString.h"

class FAKE_API FakeLayer
	{
	private:
		FakeString DebugName;

	public:

		/**
		 *
		 * Constructs a new Instance of the Layer and stores just the name of your Layer.
		 *
		 * @param debugName A Name for the Layer to be able to identify a particular Layer.
		 */
		FakeLayer(const FakeString &debugName = "DefaultLayer");

		/**
		 *
		 * default destructor.
		 *
		 */
		virtual ~FakeLayer();

		/**
		 *
		 * Getter for the DebugName of the Layer.
		 *
		 * @return The DebugName of the Layer as a FakeString.
		 */
		const FakeString &GetName();

		/**
		 *
		 * It is automatically called, if the Layer gets registered in your main Class which extends from FakeApplication.
		 *
		 * @note This Method is intended to load and initialize custom game data.
		 */
		virtual void OnAttach();

		/**
		 *
		 * It is automatically called, if the Layer gets destroyed by the FakeApplication and therefore removed from the LayerStack.
		 *
		 * @note The Method is intended to destroy or unload custom game data.
		 */
		virtual void OnDetach();

		/**
		 *
		 * It is automatically called once a frame by the Engine and should be used to update the game data.
		 *
		 * @param ts The DeltaTime calculated by the Application.
		 * @note The FakeTimeStep class can be used like a double.
		 */
		virtual void OnRender(FakeTimeStep ts);

		/**
		 *
		 * It is automatically called if a Event occurrs, which is not handled yet.
		 *
		 * @note Your Layer can register to be notified by any EventType using the FakeEventDispatcher.
		 *
		 * @param e The Event which occurred and is not handled yet.
		 */
		virtual void OnEvent(FakeEvent &e);
	};
