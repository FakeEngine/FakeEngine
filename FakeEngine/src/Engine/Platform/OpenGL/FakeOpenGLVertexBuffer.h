/*****************************************************************
 * \file   FakeOpenGLVertexBuffer.h
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

#include "Engine/Renderer/FakeVertexBuffer.h"
#include "Engine/Core/FakeAllocator.h"

/**
 * 
 * .
 * 
 */
class FakeOpenGLVertexBuffer : public FakeVertexBuffer
	{
	private:
		
		FakeRendererID RendererID = 0;
		uint32 Size;
		FakeVertexBufferUsage Usage;
		FakeVertexBufferLayout Layout;
		FakeAllocator LocalData;

	public:

		FakeOpenGLVertexBuffer(void *data, uint32 size, FakeVertexBufferUsage usage = FakeVertexBufferUsage::Static);
		FakeOpenGLVertexBuffer(uint32 size, FakeVertexBufferUsage usage = FakeVertexBufferUsage::Dynamic);
		virtual ~FakeOpenGLVertexBuffer();

		virtual void SetData(void *data, uint32 size, uint32 offset = 0) override;
		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual const FakeVertexBufferLayout &GetLayout() const override { return Layout; }
		virtual void SetLayout(const FakeVertexBufferLayout &layout) override { Layout = layout; }

		virtual uint32 GetSize() const override { return Size; }
		virtual FakeRendererID GetRendererID() const override { return RendererID; }

	};
