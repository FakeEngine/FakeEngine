/*****************************************************************
 * \file   FakeFramebuffer.h
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

#include "Engine/Core/Maths/FakeVector4.h"

enum class FakeFramebufferTextureFormat
	{
	None			= 0,

	RGBA8			= 1,
	RGBA16F			= 2,
	RGBA32F			= 3,
	RG32F			= 4,
	RED_INTEGER		= 5,

	DEPTH32F		= 6,
	DEPTH24STENCIL8 = 7,

	DEPTH			= DEPTH24STENCIL8
	};

/**
 * 
 * .
 * 
 */
struct FAKE_API FakeFramebufferTextureSpecification
	{
	/**
	 * 
	 * default constructor.
	 * 
	 */
	FakeFramebufferTextureSpecification() = default;

	/**
	 * 
	 * .
	 * 
	 * @param format
	 */
	FakeFramebufferTextureSpecification(FakeFramebufferTextureFormat format)
		: Format(format)
		{
		}

	FakeFramebufferTextureFormat Format;
	};

/**
 * 
 * .
 * 
 */
struct FAKE_API FakeFramebufferAttachmentSpecification
	{
	/**
	 * 
	 * default constructor.
	 * 
	 */
	FakeFramebufferAttachmentSpecification() = default;

	/**
	 * 
	 * .
	 * 
	 * @param attachments
	 */
	FakeFramebufferAttachmentSpecification(const std::initializer_list<FakeFramebufferTextureSpecification> &attachments)
		: Attachments(attachments)
		{
		}

	std::vector<FakeFramebufferTextureSpecification> Attachments;
	};

/**
 * 
 * .
 * 
 */
struct FAKE_API FakeFramebufferSpecification
	{
	uint32 Width = 1280;
	uint32 Height = 720;
	FakeFramebufferAttachmentSpecification Attachments;
	uint32 Samples = 1;

	FakeVec4f ClearColor = { 0.0f, 0.0f, 0.0f, 1.0f };

	// TODO: Needs Scale
	bool NoResize = false;

	// SwapChainTarget = Screen buffer (i.e. no Framebuffer)
	bool SwapChainTarget = false;
	};

/**
 * 
 * .
 * 
 */
class FAKE_API FakeFramebuffer : public FakeRefCounted
	{
	public:

		/**
		 * 
		 * .
		 * 
		 */
		virtual ~FakeFramebuffer() {}

		/**
		 * 
		 * .
		 * 
		 */
		virtual void Bind() const = 0;

		/**
		 * 
		 * .
		 * 
		 */
		virtual void Unbind() const = 0;

		/**
		 * 
		 * .
		 * 
		 * @param width
		 * @param height
		 */
		virtual void Resize(uint32 width, uint32 height) = 0;

		/**
		 * 
		 * .
		 * 
		 * @return 
		 */
		virtual uint32 GetWidth() const = 0;

		/**
		 * 
		 * .
		 * 
		 * @return 
		 */
		virtual uint32 GetHeight() const = 0;

		/**
		 * 
		 * .
		 * 
		 * @param attachmentIndex
		 * @param x
		 * @param y
		 * @return 
		 */
		virtual int32 ReadPixel(uint32 attachmentIndex, int32 x, int32 y) = 0;

		/**
		 * 
		 * .
		 * 
		 * @param attachmentIndex
		 * @param value
		 */
		virtual void ClearAttachment(uint32 attachmentIndex, int32 value) = 0;

		/**
		 * 
		 * .
		 * 
		 * @param attachmentIndex
		 * @param value
		 */
		virtual void ClearAttachment(uint32 attachmentIndex, float value) = 0;

		/**
		 * 
		 * .
		 * 
		 * @return 
		 */
		virtual FakeRendererID GetRendererID() const = 0;

		/**
		 * 
		 * .
		 * 
		 * @param index
		 * @return 
		 */
		virtual FakeRendererID GetColorAttachmentRendererID(int32 index = 0) const = 0;

		/**
		 * 
		 * .
		 * 
		 * @return 
		 */
		virtual FakeRendererID GetDepthAttachmentRendererID() const = 0;

		/**
		 * 
		 * .
		 * 
		 * @return 
		 */
		virtual const FakeFramebufferSpecification &GetSpecification() const = 0;

		/**
		 * 
		 * .
		 * 
		 * @param spec
		 * @return 
		 */
		static FakeRef<FakeFramebuffer> Create(const FakeFramebufferSpecification &spec);
	};

