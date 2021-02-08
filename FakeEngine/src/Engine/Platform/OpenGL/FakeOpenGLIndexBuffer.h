/*****************************************************************
 * \file   FakeOpenGLIndexBuffer.h
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

#include "Engine/Renderer/FakeIndexBuffer.h"

class FAKE_API FakeOpenGLIndexBuffer : public FakeIndexBuffer
	{
	private:

		FakeRendererID RendererID = 0;
		uint32 Size;
		FakeAllocator LocalData;

	public:

		/**
		 * 
		 * .
		 * 
		 * @param data
		 * @param size
		 */
		FakeOpenGLIndexBuffer(void *data, uint32 size);

		/**
		 * 
		 * .
		 * 
		 * @param size
		 */
		FakeOpenGLIndexBuffer(uint32 size);

		/**
		 * 
		 * .
		 * 
		 */
		virtual ~FakeOpenGLIndexBuffer();

		/**
		 * 
		 * .
		 * 
		 * @param data
		 * @param size
		 * @param offset
		 */
		virtual void SetData(void *data, uint32 size, uint32 offset = 0) override;

		/**
		 *
		 * Binds the current IndexBuffer instance.
		 *
		 */
		virtual void Bind() const override;

		/**
		 *
		 * Unbinds the current IndexBuffer instance.
		 *
		 */
		virtual void Unbind() const override;

		/**
		 *
		 * Returns the element count of the uploaded indices.
		 *
		 * @return Returns the element count of the uploaded indices.
		 */
		virtual uint32 GetCount() const override;

		/**
		 *
		 * Returns the size of the uploaded indices.
		 *
		 * @return Returns the size of the uploaded indices.
		 */
		virtual uint32 GetSize() const override;

		/**
		 *
		 * Returns the RendererID where the data is bound to.
		 *
		 * @return Returns the RendererID where the data is bound to.
		 */
		virtual FakeRendererID GetRendererID() const override;
	};
