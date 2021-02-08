/*****************************************************************
 * \file   FakeRendererAPI.h
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

#include "Engine/Core/Maths/FakeVector4.h"

enum class FakeRendererAPIType
	{
	OpenGL = 0,
	DirectX11,
	DirectX12,
	Vulkan,
	Metal,

	None = OpenGL,
	};

enum class FakePrimitiveType
	{
	None = 0,
	Triangles,
	Lines
	};

/**
 * 
 * .
 * 
 */
struct FakeRenderAPICapabilities
	{
	FakeString Vendor;
	FakeString Renderer;
	FakeString Version;

	int32 MaxSamples = 0;
	int32 MaxTextureUnits = 0;
	float MaxAnisotropy = 0.0f;
	};

/**
 * 
 * .
 * 
 */
class FakeRendererAPI
	{
	private:
		static FakeRendererAPIType CurrentRendererAPI;

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
		static void Clear();

		/**
		 * 
		 * .
		 * 
		 * @param r
		 * @param g
		 * @param b
		 * @param a
		 */
		static void SetClearColor(float r, float g, float b, float a);

		/**
		 * 
		 * .
		 * 
		 * @param color
		 */
		static void SetClearColor(const FakeVec4f &color);

		/**
		 * 
		 * .
		 * 
		 * @param count
		 * @param type
		 * @param depthTest
		 */
		static void DrawIndexed(uint32 count, FakePrimitiveType type, bool depthTest = true);

		/**
		 * 
		 * .
		 * 
		 * @param width
		 * @param height
		 */
		static void SetViewport(uint32 width, uint32 height);

		/**
		 * 
		 * .
		 * 
		 * @param thickness
		 */
		static void SetLineThickness(float thickness);

		/**
		 * 
		 * .
		 * 
		 * @return 
		 */
		static FakeRenderAPICapabilities &GetCapabilities()
			{
			static FakeRenderAPICapabilities caps;
			return caps;
			}

		/**
		 * 
		 * .
		 * 
		 * @param type
		 */
		static void SetCurrent(FakeRendererAPIType type)
			{
			CurrentRendererAPI = type;
			}

		/**
		 * 
		 * .
		 * 
		 * @return 
		 */
		static FakeRendererAPIType Current()
			{
			return CurrentRendererAPI;
			}
	};
