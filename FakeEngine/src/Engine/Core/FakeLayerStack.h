/*****************************************************************
 * \file   FakeLayerStack.h
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

#include "Engine/Core/FakeLayer.h"

class FAKE_API FakeLayerStack
	{
	private:
		std::vector<FakeLayer*> Layers;
		uint32 LayerInsertIndex = 0;

	public:

		/**
		 *
		 * Constructs a new Layerstack.
		 *
		 */
		FakeLayerStack();

		/**
		 *
		 * Destroys every Layer in the LayerStack.
		 *
		 */
		virtual ~FakeLayerStack();

		/**
		 *
		 * Adds a new Layer to the LayerStack.
		 *
		 * @param layer The Layer which should be added to the LayerStack.
		 */
		void PushLayer(FakeLayer *layer);

		/**
		 *
		 * Removes a Layer from the LayerStack.
		 *
		 * @param layer The Layer which should be added to the LayerStack.
		 */
		void PopLayer(FakeLayer *layer);

		/**
		 *
		 * Adds a new Overlay to the LayerStack.
		 *
		 * @param overlay The Overlay which should be added to the LayerStack.
		 */
		void PushOverlay(FakeLayer *overlay);

		/**
		 *
		 * Removes a Overlay from the LayerStack.
		 *
		 * @param overlay The Overlay which should be added to the LayerStack.
		 */
		void PopOverlay(FakeLayer *overlay);

		/**
		 *
		 * This function returns a std::iterator to the first Element of the LayerStack.
		 *
		 * @return Returns the first Element of the LayerStack.
		 */
		std::vector<FakeLayer *>::iterator begin();

		/**
		 *
		 * This function returns a std::iterator to the last Element of the LayerStack.
		 *
		 * @return Returns the last Element of the LayerStack.
		 */
		std::vector<FakeLayer *>::iterator end();

		/**
		 *
		 * This function returns a std::iterator to the first Element of the LayerStack.
		 *
		 * @return Returns the first Element of the LayerStack.
		 */
		std::vector<FakeLayer *>::const_iterator begin() const;

		/**
		 *
		 * This function returns a std::iterator to the last Element of the LayerStack.
		 *
		 * @return Returns the last Element of the LayerStack.
		 */
		std::vector<FakeLayer *>::const_iterator end() const;
	};

