/*****************************************************************
 * \file   FakeRenderer2D.h
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

#include "Engine/Core/Maths/FakeMaths.h"
#include "Engine/Renderer/FakeTexture2D.h"

/**
 * 
 * .
 * 
 */
class FakeRenderer2D
	{
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

		/**
		 * 
		 * .
		 * 
		 */
		static void BeginScene();

		/**
		 * 
		 * .
		 * 
		 */
		static void EndScene();

		/**
		 * 
		 * .
		 * 
		 * @param position
		 * @param size
		 * @param rotation
		 * @param color
		 */
		static void DrawQuad(const FakeVec3f &position, const FakeVec2f &size, float rotation, const FakeVec4f &color);
		
		/**
		 * 
		 * .
		 * 
		 * @param position
		 * @param size
		 * @param rotation
		 * @param texture
		 * @param tilingFactor
		 * @param tintColor
		 */
		static void DrawTexture(const FakeVec3f &position, const FakeVec2f &size, float rotation, const FakeRef<FakeTexture2D> &texture, float tilingFactor, const FakeVec4f &tintColor);
	};
