/*****************************************************************
 * \file   FakeOpenGLPipeline.h
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
#include "Engine/Renderer/FakePipeline.h"

/**
 * 
 * .
 * 
 */
class FAKE_API FakeOpenGLPipeline : public FakePipeline
	{
	private:

		FakePipelineSpecification Specification;
		FakeRendererID RendererID;

	public:

		/**
		 * 
		 * .
		 * 
		 * @param spec
		 */
		FakeOpenGLPipeline(const FakePipelineSpecification &spec);

		/**
		 * 
		 * .
		 * 
		 */
		virtual ~FakeOpenGLPipeline();

		/**
		 *
		 * Binds the current Pipeline instance.
		 *
		 */
		virtual void Bind() const override;

		/**
		 *
		 * Unbinds the current Pipeline instance.
		 *
		 */
		virtual void Unbind() const override;

		/**
		 *
		 * Returns the RendererID where the data is bound to.
		 *
		 * @return Returns the RendererID where the data is bound to.
		 */
		virtual FakeRendererID GetRendererID() const override;

		/**
		 *
		 * Returns the specified parameters that were used to initialize the Pipeline.
		 *
		 * @return Returns the specified parameters that were used to initialize the Pipeline.
		 */
		virtual FakePipelineSpecification &GetSpecification() override;

		/**
		 *
		 * Returns the specified parameters that were used to initialize the Pipeline.
		 *
		 * @return Returns the specified parameters that were used to initialize the Pipeline.
		 */
		virtual const FakePipelineSpecification &GetSpecification() const override;

		/**
		 *
		 * Regenerates the hole Pipeline.
		 *
		 */
		virtual void Invalidate() override;
	};

