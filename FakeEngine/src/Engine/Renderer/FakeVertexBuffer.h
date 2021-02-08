/*****************************************************************
 * \file   FakeVertexBuffer.h
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

#include "Engine/Renderer/FakeVertexBufferLayout.h"

enum class FakeVertexBufferUsage
	{
	None = 0,
	Static = 1,
	Dynamic = 2
	};

/**
 *
 * This class represents a VertexBuffer.
 *
 */
class FAKE_API FakeVertexBuffer : public FakeRefCounted
	{
	public:

		/**
		 *
		 * default destructor.
		 *
		 */
		virtual ~FakeVertexBuffer() = default;

		/**
		 *
		 * Sets the vertices after a instance has been created.
		 *
		 * @param data The vertices which should be used.
		 * @param size The size of the vertices that are being uploaded.
		 * @param offset The offset in which the vertices should be placed.
		 */
		virtual void SetData(void *data, uint32 size, uint32 offset = 0) = 0;

		/**
		 *
		 * Binds the current VertexBuffer instance.
		 *
		 */
		virtual void Bind() const = 0;

		/**
		 *
		 * Unbinds the current VertexBuffer instance.
		 *
		 */
		virtual void Unbind() const = 0;

		/**
		 *
		 * Returns the Layout used to interpret the Layout of the vertices.
		 *
		 * @return Returns the Layout used to interpret the Layout of the vertices.
		 */
		virtual const FakeVertexBufferLayout &GetLayout() const = 0;

		/**
		 *
		 * Sets the Layout which tells how to interpret the vertices.
		 *
		 * @param layout The layout which tells how to interpret the vertices.
		 */
		virtual void SetLayout(const FakeVertexBufferLayout &layout) = 0;

		/**
		 *
		 * Returns the size of the uploaded vertices.
		 *
		 * @return Returns the size of the uploaded vertices.
		 */
		virtual uint32 GetSize() const = 0;

		/**
		 *
		 * Returns the RendererID where the data is bound to.
		 *
		 * @return Returns the RendererID where the data is bound to.
		 */
		virtual FakeRendererID GetRendererID() const = 0;

		/**
		 *
		 * Creates a new shared VertexBuffer instance.
		 *
		 * @param data The vertices that should be used in the buffer.
		 * @param size The size of the vertices that should be used in the buffer.
		 * @param usage The usage whether the vertices should be interpreted as static or dynamic vertices by the rendering platform.
		 * @return Returns a new shared instance of the VertexBuffer.
		 */
		static FakeRef<FakeVertexBuffer> Create(void *data, uint32 size, FakeVertexBufferUsage usage = FakeVertexBufferUsage::Static);

		/**
		 *
		 * Creates a new shared VertexBuffer instance.
		 *
		 * @param size The size of the vertices that should be used in the buffer.
		 * @param usage The usage whether the vertices should be interpreted as static or dynamic vertices by the rendering platform.
		 * @return Returns a new shared instance of the VertexBuffer.
		 */
		static FakeRef<FakeVertexBuffer> Create(uint32 size, FakeVertexBufferUsage usage = FakeVertexBufferUsage::Dynamic);
	};
