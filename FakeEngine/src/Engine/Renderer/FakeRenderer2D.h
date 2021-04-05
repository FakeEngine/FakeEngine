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

class FakeRenderer2D
	{
	private:

		static void FlushAndReset();
		static void FlushAndResetLines();

	public:

		struct Statistics
			{
			uint32 DrawCalls = 0;
			uint32 QuadCount = 0;
			uint32 LineCount = 0;

			uint32 GetTotalVertexCount()
				{
				return QuadCount * 4 + LineCount * 2;
				}

			uint32 GetTotalIndexCount()
				{
				return QuadCount * 6 + LineCount * 2;
				}
			};

		static void Init();
		static void Shutdown();

		static void BeginScene(const FakeVec2f &viewport, bool depthTest = true);
		static void BeginScene(const FakeMat4f &viewProjection, bool depthTest = true);
		static void EndScene();

		static void Flush();
		static void ResetStats();
		static Statistics GetStats();

		static void DrawQuad(const FakeMat4f &transform, const FakeVec4f &color);
		static void DrawQuad(const FakeVec2f &position, const FakeVec2f &size, const FakeVec4f &color);
		static void DrawQuad(const FakeVec3f &position, const FakeVec2f &size, const FakeVec4f &color);

		static void DrawTexture(const FakeMat4f &transform, const FakeRef<FakeTexture2D> &texture, float tilingFactor = 1.0f, const FakeVec4f &tintColor = FakeVec4f(1.0f, 1.0f, 1.0f, 1.0f));
		static void DrawTexture(const FakeVec2f &position, const FakeVec2f &size, const FakeRef<FakeTexture2D> &texture, float tilingFactor = 1.0f, const FakeVec4f &tintColor = FakeVec4f(1.0f, 1.0f, 1.0f, 1.0f));
		static void DrawTexture(const FakeVec3f &position, const FakeVec2f &size, const FakeRef<FakeTexture2D> &texture, float tilingFactor = 1.0f, const FakeVec4f &tintColor = FakeVec4f(1.0f, 1.0f, 1.0f, 1.0f));
	};
