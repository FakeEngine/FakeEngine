/*****************************************************************
 * \file   FakeOpenGLTexture2D.h
 * \brief  
 * 
 * \author Can Karka
 * \date   February 2021
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
#include "Engine/Renderer/FakeTexture2D.h"

class FAKE_API FakeOpenGLTexture2D : public FakeTexture2D
	{
	private:

		FakeRendererID RendererID = 0;
		FakeAllocator ImageData;
		FakeTextureFormat Format;
		FakeTextureWrap Wrap = FakeTextureWrap::Clamp;
		uint32 Width, Height;
		bool IsHDR = false;
		bool IsLocked = false;
		bool IsLoaded = false;
		FakeString FilePath, Name;

	public:

		/**
		 * 
		 * .
		 * 
		 * @param path
		 * @param srgb
		 * @param wrap
		 */
		FakeOpenGLTexture2D(const FakeString &path, bool srgb = false, FakeTextureWrap wrap = FakeTextureWrap::Clamp);

		/**
		 * 
		 * .
		 * 
		 * @param format
		 * @param width
		 * @param height
		 * @param wrap
		 */
		FakeOpenGLTexture2D(FakeTextureFormat format, uint32 width, uint32 height, FakeTextureWrap wrap = FakeTextureWrap::Clamp);

		/**
		 * 
		 * .
		 * 
		 */
		virtual ~FakeOpenGLTexture2D();

		/**
		 *
		 * Binds the Texture to a specific slot.
		 *
		 * @param slot The Slot the texture should bind to.
		 */
		virtual void Bind(uint32 slot = 0) const override;

		/**
		 *
		 * Unbinds the Texture.
		 *
		 */
		virtual void Unbind() const override;

		/**
		 *
		 * Returns true if the texture has been loaded successfully.
		 *
		 * @return Returns true if the texture has been loaded successfully.
		 */
		virtual bool Loaded() const override;

		/**
		 *
		 * Returns the name of the Texture (either the fileName or a default name).
		 *
		 * @return Returns the name of the Texture (either the fileName or a default name).
		 */
		virtual const FakeString &GetName() const override;

		/**
		 *
		 * Returns the path to the Texture on the disk.
		 *
		 * @return Returns the path to the Texture on the disk.
		 */
		virtual const FakeString &GetPath() const override;

		/**
		 *
		 * Returns the current Format of the Texture instance.
		 *
		 * @return Returns the current Format of the Texture instance.
		 */
		virtual FakeTextureFormat GetFormat() const override;

		/**
		 *
		 * Returns the current Width of the Texture instance.
		 *
		 * @return Returns the current Width of the Texture instance.
		 */
		virtual uint32 GetWidth() const override;

		/**
		 *
		 * Returns the current Height of the Texture instance.
		 *
		 * @return Returns the current Height of the Texture instance.
		 */
		virtual uint32 GetHeight() const override;

		/**
		 *
		 * Returns the current MipLevelCount of the Texture instance.
		 *
		 * @return Returns the current MipLevelCount of the Texture instance.
		 */
		virtual uint32 GetMipLevelCount() const override;

		/**
		 *
		 * Returns the current RendererID of the Texture instance.
		 *
		 * @return Returns the current RendererID of the Texture instance.
		 */
		virtual FakeRendererID GetRendererID() const override;

		/**
		 *
		 * Returns true if the texture instances are equal.
		 *
		 * @param other Another Texture instance to compare to.
		 * @return Returns true if the texture instances are equal.
		 */
		virtual bool operator==(const FakeTexture &other) const override;

		/**
		 *
		 * Returns true if the texture instances are not equal.
		 *
		 * @param other Another Texture instance to compare to.
		 * @return Returns true if the texture instances are not equal.
		 */
		virtual bool operator!=(const FakeTexture &other) const override;

		/**
		 *
		 * Locks the Texture instance.
		 *
		 */
		virtual void Lock() override;

		/**
		 *
		 * Unlocks the Texture instance and re-uploads the texture data to the current specification.
		 *
		 */
		virtual void Unlock() override;

		/**
		 *
		 * Resizes the texture instance to a new width and a height.
		 *
		 * @param width The new width of the Texture.
		 * @param height The new height of the Texture.
		 */
		virtual void Resize(uint32 width, uint32 height) override;

		/**
		 *
		 * Returns the Allocator which contains the raw pixel data. The data can be modified outside of the class.
		 *
		 * @return Returns the Allocator which contains the raw pixel data.
		 */
		virtual FakeAllocator GetWriteableBuffer() override;

		/**
		 *
		 * Sets the pixel data for the current texture instance.
		 *
		 * @param data The pixel data which should be set.
		 * @param size The size of the data which should be set.
		 */
		virtual void SetData(void *data, uint32 size) override;
	};
