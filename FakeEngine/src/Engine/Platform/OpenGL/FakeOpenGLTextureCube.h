/*****************************************************************
 * \file   FakeOpenGLTextureCube.h
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
#include "Engine/Renderer/FakeTextureCube.h"

/**
 * 
 * .
 * 
 */
class FAKE_API FakeOpenGLTextureCube : public FakeTextureCube
	{
	private:

		FakeRendererID RendererID = 0;
		FakeTextureFormat Format;
		uint32 Width, Height;
		FakeString FilePath, Name;
		FakeAllocator ImageData;
		bool IsLoaded = false;

	public:

		/**
		 * 
		 * .
		 * 
		 * @param path
		 */
		FakeOpenGLTextureCube(const FakeString &path);

		/**
		 * 
		 * .
		 * 
		 * @param format
		 * @param width
		 * @param height
		 */
		FakeOpenGLTextureCube(FakeTextureFormat format, uint32 width, uint32 height);

		/**
		 * 
		 * .
		 * 
		 */
		virtual ~FakeOpenGLTextureCube();

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
	};
