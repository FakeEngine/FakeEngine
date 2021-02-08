/*****************************************************************
 * \file   FakePipeline.h
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

#include "FakeShader.h"
#include "FakeVertexBuffer.h"
#include "FakeIndexBuffer.h"

/**
 *
 * .
 *
 */
struct FAKE_API FakePipelineSpecification
	{
	FakeRef<FakeShader> Shader;
	FakeRef<FakeVertexBuffer> VertexBuffer;
	FakeRef<FakeIndexBuffer> IndexBuffer;
	FakeVertexBufferLayout Layout;
	};

/**
 *
 * This class represents a Pipeline. In OpenGL it additionally handles the creation and destruction of a VertexArray.
 *
 */
class FAKE_API FakePipeline : public FakeRefCounted
	{
	public:

		/**
		 *
		 * default destructor.
		 *
		 */
		virtual ~FakePipeline() = default;

		/**
		 *
		 * Binds the current Pipeline instance.
		 *
		 */
		virtual void Bind() const = 0;

		/**
		 *
		 * Unbinds the current Pipeline instance.
		 *
		 */
		virtual void Unbind() const = 0;

		/**
		 *
		 * Returns the RendererID where the data is bound to.
		 *
		 * @return Returns the RendererID where the data is bound to.
		 */
		virtual FakeRendererID GetRendererID() const = 0;

		/**
		 *
		 * Returns the specified parameters that were used to initialize the Pipeline.
		 *
		 * @return Returns the specified parameters that were used to initialize the Pipeline.
		 */
		virtual FakePipelineSpecification &GetSpecification() = 0;

		/**
		 *
		 * Returns the specified parameters that were used to initialize the Pipeline.
		 *
		 * @return Returns the specified parameters that were used to initialize the Pipeline.
		 */
		virtual const FakePipelineSpecification &GetSpecification() const = 0;

		/**
		 *
		 * Regenerates the hole Pipeline.
		 *
		 */
		virtual void Invalidate() = 0;

		/**
		 *
		 * Creates a new shared instance of a Pipeline.
		 *
		 * @param spec The Parameters that are used to initialize the Pipeline.
		 * @return Returns a new shared instance of a Pipeline.
		 */
		static FakeRef<FakePipeline> Create(const FakePipelineSpecification &spec);
	};

