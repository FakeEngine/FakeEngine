/*****************************************************************
 * \file   FakeRenderingContext.h
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

#include "Engine/Core/FakeCore.h"

 /**
  *
  * The Rendering Context is the bridge between Window and graphics rendering.
  * Therefore you will find RenderingContextes only in window API specific implementations.
  *
  */
class FAKE_API FakeRenderingContext
	{
	public:

		/**
		 *
		 * Virtual Destructor to provide any extending class with the possibility to destroy it's allocated storage.
		 *
		 */
		virtual ~FakeRenderingContext() = default;

		/**
		 *
		 * Initializes the Context.
		 *
		 */
		virtual void Init() = 0;

		/**
		 *
		 * Swaps the WindowBuffer after each frame.
		 *
		 */
		virtual void SwapBuffers() = 0;

		/**
		 *
		 * Resizes the Rendering region to the desired width and height.
		 *
		 * @param width The new width of the rendering region.
		 * @param height The new height of the rendering region.
		 */
		virtual void Resize(uint32 width, uint32 height) = 0;

		/**
		 *
		 * Function to enable/disable V-Sync.
		 *
		 * @param enabled Determines if V-Sync should be enabled or disabled.
		 */
		virtual void SetSwapInterval(bool enabled) = 0;

		/**
		 *
		 * If the render target changed this function can switch the rendering target back to the current context.
		 *
		 */
		virtual void MakeContextCurrent() = 0;
	};
