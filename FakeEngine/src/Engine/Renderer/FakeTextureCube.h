/*****************************************************************
 * \file   FakeTextureCube.h
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

#include "Engine/Renderer/FakeTexture.h"

/**
 * 
 * This class represents a CubeTexture (used for HDR Environments).
 * 
 */
class FakeTextureCube : public FakeTexture
	{
	public:

		/**
		 *
		 * Creates a new Texture by using a filepath from the disk.
		 *
		 * @param path The virtual path to a Texture on the disk.
		 * @return Returns a new Texture by using a filepath from the disk.
		 */
		static FakeRef<FakeTextureCube> Create(const FakeString &path);

		/**
		 *
		 * Creates a new Texture.
		 *
		 * @param format The Format the Texture should have.
		 * @param width The Width the Texture should have.
		 * @param height The Height the Texture should have.
		 * @return Returns a new Texture.
		 */
		static FakeRef<FakeTextureCube> Create(FakeTextureFormat format, uint32 width, uint32 height);
	};
