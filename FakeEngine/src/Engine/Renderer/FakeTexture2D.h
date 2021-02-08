/*****************************************************************
 * \file   FakeTexture2D.h
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
 * This class represents a standard ImageTexture.
 * 
 */
class FakeTexture2D : public FakeTexture
	{
	public:

		/**
		 *
		 * Locks the Texture instance.
		 *
		 */
		virtual void Lock() = 0;

		/**
		 *
		 * Unlocks the Texture instance and re-uploads the texture data to the current specification.
		 *
		 */
		virtual void Unlock() = 0;

		/**
		 *
		 * Resizes the texture instance to a new width and a height.
		 *
		 * @param width The new width of the Texture.
		 * @param height The new height of the Texture.
		 */
		virtual void Resize(uint32 width, uint32 height) = 0;

		/**
		 *
		 * Returns the Allocator which contains the raw pixel data. The data can be modified outside of the class.
		 *
		 * @return Returns the Allocator which contains the raw pixel data.
		 */
		virtual FakeAllocator GetWriteableBuffer() = 0;

		/**
		 *
		 * Sets the pixel data for the current texture instance.
		 *
		 * @param data The pixel data which should be set.
		 * @param size The size of the data which should be set.
		 */
		virtual void SetData(void *data, uint32 size) = 0;

		/**
		 *
		 * Creates a new Texture by using a filepath from the disk.
		 *
		 * @param path The virtual path to a Texture on the disk.
		 * @param srgb Whether the Texture is a SRGB Texture or not.
		 * @param wrap The Wrapping mode the Texture should have.
		 * @return Returns a new Texture by using a filepath from the disk.
		 */
		static FakeRef<FakeTexture2D> Create(const FakeString &path, bool srgb = false, FakeTextureWrap wrap = FakeTextureWrap::Clamp);

		/**
		 *
		 * Creates a new Texture.
		 *
		 * @param format The Format the Texture should have.
		 * @param width The Width the Texture should have.
		 * @param height The Height the Texture should have.
		 * @param wrap The Wrapping mode the Texture should have.
		 * @return Returns a new Texture.
		 */
		static FakeRef<FakeTexture2D> Create(FakeTextureFormat format, uint32 width, uint32 height, FakeTextureWrap wrap = FakeTextureWrap::Clamp);
	};

