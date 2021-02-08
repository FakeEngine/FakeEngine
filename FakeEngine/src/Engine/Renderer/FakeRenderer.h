/*****************************************************************
 * \file   FakeRenderer.h
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

#include "FakeRenderCommandQueue.h"
#include "FakeRenderPass.h"
#include "FakeRendererAPI.h"
#include "FakeShaderLibrary.h"

/**
 * 
 * .
 * 
 */
class FakeRenderer
	{
	private:

		/**
		 * 
		 * .
		 * 
		 * @return 
		 */
		static FakeRenderCommandQueue &GetRenderCommandQueue();

	public:

		/**
		 * 
		 * .
		 * 
		 */
		static void Init();
		
		/**
		 * 
		 * .
		 * 
		 */
		static void Shutdown();
		
		// TODO: Move to RenderCommands
		static void Clear();
		static void SetClearColor(float r, float g, float b, float a);
		static void SetClearColor(const FakeVec4f &color);
		static void SetLineThickness(float thickness);
		static void DrawIndexed(uint32 count, FakePrimitiveType type, bool depthTest = true);
		static void SetViewport(uint32 width, uint32 height);

		/**
		 * 
		 * .
		 * 
		 */
		static void Render();

		/**
		 * 
		 * .
		 * 
		 * @param renderPass
		 * @param shouldClear
		 */
		static void BeginRenderPass(FakeRef<FakeRenderPass> renderPass, bool shouldClear = true);
		
		/**
		 * 
		 * .
		 * 
		 */
		static void EndRenderPass();

		static FakeShaderLibrary &GetShaderLibrary();

		/**
		 * 
		 * .
		 * 
		 * @param func
		 */
		template<typename Func>
		static void Submit(Func &&func)
			{
			auto renderCmd = [](void *ptr)
				{
				auto pFunc = (Func*)ptr;
				(*pFunc)();
				pFunc->~Func();
				};

			auto storageBuffer = GetRenderCommandQueue().Allocate(renderCmd, sizeof(func));
			new (storageBuffer) Func(std::forward<Func>(func));
			}
	};
