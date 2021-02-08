/*****************************************************************
 * \file   FakeOpenGLRenderingContext.h
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

#include <glad/glad.h>

#include "Engine/Renderer/FakeRenderingContext.h"
#include "Engine/Core/Window/FakeWindow.h"

#ifdef FAKE_PLATFORM_WINDOWS

#ifdef FAKE_WINAPI_WINDOWS
	#include <Windows.h>
#elif FAKE_WINAPI_GLFW
	#include <GLFW/glfw3.h>
#endif

#endif

 /**
  *
  * This class represents a OpenGL specific Rendering Context.
  * A rendering context is like a connector between rendering and the RenderWindow.
  *
  */
class FAKE_API FakeOpenGLRenderingContext : public FakeRenderingContext
	{
	private:
		FakeWindow *Window = nullptr;

	public:

		/**
		 *
		 * constructor that initializes the Window.
		 *
		 * @param window The Window that should be used with the Rendering Context.
		 */
		FakeOpenGLRenderingContext(FakeWindow *window);

		/**
		 *
		 * default destructor.
		 *
		 */
		virtual ~FakeOpenGLRenderingContext();

		/**
		 *
		 * Initializes the OpenGL Context.
		 *
		 */
		virtual void Init() override;

		/**
		 *
		 * Swaps the rendering buffers after each frame.
		 *
		 */
		virtual void SwapBuffers() override;

		/**
		 *
		 * Resizes the Rendering context to a new width and height.
		 *
		 * @param width The new Width of the Rendering Context.
		 * @param height The new Height of the Rendering Context.
		 */
		virtual void Resize(uint32 width, uint32 height) override;

		/**
		 *
		 * Sets whether V-Sync should be enabled or not.
		 *
		 * @param enabled Determines whether V-Sync should be enabled or disabled.
		 */
		virtual void SetSwapInterval(bool enabled) override;

		/**
		 *
		 * Re-Enables the Rendering Context for the current Window.
		 *
		 */
		virtual void MakeContextCurrent() override;
	};
