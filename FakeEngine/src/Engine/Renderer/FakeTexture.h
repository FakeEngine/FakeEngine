/*****************************************************************
 * \file   FakeTexture.h
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

#include "Engine/Core/FakeAllocator.h"

enum class FakeTextureFormat
	{
	None = 0,
	RGB = 1,
	RGBA = 2,
	Float16 = 3
	};

enum class FakeTextureWrap
	{
	None = 0,
	Clamp = 1,
	Repeat = 2
	};

/**
 *
 * This class represents the base interface for a FakeTexture.
 *
 */
class FAKE_API FakeTexture : public FakeRefCounted
	{
	public:

		/**
		 *
		 * default destructor.
		 *
		 */
		virtual ~FakeTexture() = default;

		/**
		 *
		 * Binds the Texture to a specific slot.
		 *
		 * @param slot The Slot the texture should bind to.
		 */
		virtual void Bind(uint32 slot = 0) const = 0;

		/**
		 *
		 * Unbinds the Texture.
		 *
		 */
		virtual void Unbind() const = 0;

		/**
		 *
		 * Returns true if the texture has been loaded successfully.
		 *
		 * @return Returns true if the texture has been loaded successfully.
		 */
		virtual bool Loaded() const = 0;

		/**
		 *
		 * Returns the name of the Texture (either the fileName or a default name).
		 *
		 * @return Returns the name of the Texture (either the fileName or a default name).
		 */
		virtual const FakeString &GetName() const = 0;

		/**
		 *
		 * Returns the path to the Texture on the disk.
		 *
		 * @return Returns the path to the Texture on the disk.
		 */
		virtual const FakeString &GetPath() const = 0;

		/**
		 *
		 * Returns the current Format of the Texture instance.
		 *
		 * @return Returns the current Format of the Texture instance.
		 */
		virtual FakeTextureFormat GetFormat() const = 0;

		/**
		 *
		 * Returns the current Width of the Texture instance.
		 *
		 * @return Returns the current Width of the Texture instance.
		 */
		virtual uint32 GetWidth() const = 0;

		/**
		 *
		 * Returns the current Height of the Texture instance.
		 *
		 * @return Returns the current Height of the Texture instance.
		 */
		virtual uint32 GetHeight() const = 0;

		/**
		 *
		 * Returns the current MipLevelCount of the Texture instance.
		 *
		 * @return Returns the current MipLevelCount of the Texture instance.
		 */
		virtual uint32 GetMipLevelCount() const = 0;

		/**
		 *
		 * Returns the current RendererID of the Texture instance.
		 *
		 * @return Returns the current RendererID of the Texture instance.
		 */
		virtual FakeRendererID GetRendererID() const = 0;

		/**
		 *
		 * Returns true if the texture instances are equal.
		 *
		 * @param other Another Texture instance to compare to.
		 * @return Returns true if the texture instances are equal.
		 */
		virtual bool operator==(const FakeTexture &other) const = 0;

		/**
		 *
		 * Returns true if the texture instances are not equal.
		 *
		 * @param other Another Texture instance to compare to.
		 * @return Returns true if the texture instances are not equal.
		 */
		virtual bool operator!=(const FakeTexture &other) const = 0;

		/**
		 * 
		 * Calculates the bytes per pixel.
		 * 
		 * @param format The Textureformat.
		 * @return Returns the bytes per pixel of the texture format.
		 */
		static uint32 GetBPP(FakeTextureFormat format);

		/**
		 * 
		 * Calculates the miplevel count of a texture.
		 * 
		 * @param width The width of the texture.
		 * @param height The height of the texture.
		 * @return Returns the miplevel count of a texture.
		 */
		static uint32 CalculateMipLevelCount(uint32 width, uint32 height);
	};

