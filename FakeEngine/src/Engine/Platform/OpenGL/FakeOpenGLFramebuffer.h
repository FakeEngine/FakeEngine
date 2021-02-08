/*****************************************************************
 * \file   FakeOpenGLFramebuffer.h
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

#include "Engine/Renderer/FakeFramebuffer.h"

/**
 * 
 * .
 * 
 */
class FAKE_API FakeOpenGLFramebuffer : public FakeFramebuffer
	{
	private:

		FakeFramebufferSpecification Specification;
		uint32 RendererID = 0;

		std::vector<FakeFramebufferTextureSpecification> ColorAttachmentSpecification;
		FakeFramebufferTextureSpecification DepthAttachmentSpecification = FakeFramebufferTextureFormat::None;

		std::vector<uint32> ColorAttachmentRendererIDs;
		uint32 DepthAttachmentRendererID = 0;

		void Invalidate();

	public:

		/**
		 * 
		 * .
		 * 
		 * @param spec
		 */
		FakeOpenGLFramebuffer(const FakeFramebufferSpecification &spec);

		/**
		 * 
		 * .
		 * 
		 */
		virtual ~FakeOpenGLFramebuffer();

		/**
		 *
		 * .
		 *
		 */
		virtual void Bind() const override;

		/**
		 *
		 * .
		 *
		 */
		virtual void Unbind() const override;

		/**
		 *
		 * .
		 *
		 * @param width
		 * @param height
		 * @param forceRecreate
		 */
		virtual void Resize(uint32 width, uint32 height) override;

		/**
		 *
		 * .
		 *
		 * @return
		 */
		virtual uint32 GetWidth() const override;

		/**
		 *
		 * .
		 *
		 * @return
		 */
		virtual uint32 GetHeight() const override;

		/**
		 *
		 * .
		 *
		 * @param attachmentIndex
		 * @param x
		 * @param y
		 * @return
		 */
		virtual int32 ReadPixel(uint32 attachmentIndex, int32 x, int32 y) override;

		/**
		 *
		 * .
		 *
		 * @param attachmentIndex
		 * @param value
		 */
		virtual void ClearAttachment(uint32 attachmentIndex, int32 value) override;

		/**
		 *
		 * .
		 *
		 * @param attachmentIndex
		 * @param value
		 */
		virtual void ClearAttachment(uint32 attachmentIndex, float value) override;

		/**
		 *
		 * .
		 *
		 * @return
		 */
		virtual FakeRendererID GetRendererID() const override;

		/**
		 *
		 * .
		 *
		 * @param index
		 * @return
		 */
		virtual FakeRendererID GetColorAttachmentRendererID(int32 index = 0) const override;

		/**
		 *
		 * .
		 *
		 * @return
		 */
		virtual FakeRendererID GetDepthAttachmentRendererID() const override;

		/**
		 *
		 * .
		 *
		 * @return
		 */
		virtual const FakeFramebufferSpecification &GetSpecification() const override;
	};
