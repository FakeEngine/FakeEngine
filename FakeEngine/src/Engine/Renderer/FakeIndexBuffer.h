/*****************************************************************
 * \file   FakeIndexBuffer.h
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

 /**
  *
  * This class represents a IndexBuffer used to hold the indices provided by the Client and to upload them to the currently used rendering api.
  *
  */
class FAKE_API FakeIndexBuffer : public FakeRefCounted
	{
	public:

		/**
		 *
		 * default destructor.
		 *
		 */
		virtual ~FakeIndexBuffer() = default;

		/**
		 *
		 * Sets the indices after a instance has been created.
		 *
		 * @param data The inidices which should be used.
		 * @param size The size of the indices that are being uploaded.
		 * @param offset The offset in which the indices should be placed.
		 */
		virtual void SetData(void *data, uint32 size, uint32 offset = 0) = 0;

		/**
		 *
		 * Binds the current IndexBuffer instance.
		 *
		 */
		virtual void Bind() const = 0;

		/**
		 *
		 * Unbinds the current IndexBuffer instance.
		 *
		 */
		virtual void Unbind() const = 0;

		/**
		 *
		 * Returns the element count of the uploaded indices.
		 *
		 * @return Returns the element count of the uploaded indices.
		 */
		virtual uint32 GetCount() const = 0;

		/**
		 *
		 * Returns the size of the uploaded indices.
		 *
		 * @return Returns the size of the uploaded indices.
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
		 * Creates a new shared IndexBuffer instance.
		 *
		 * @param data The indices that should be used in the buffer.
		 * @param size The size of the indices that should be used in the buffer.
		 * @return Returns a new shared instance of the IndexBuffer.
		 */
		static FakeRef<FakeIndexBuffer> Create(void *data, uint32 size);

		/**
		 *
		 * Creates a new shared IndexBuffer instance.
		 *
		 * @param size The size of the indices that should be used in the buffer.
		 * @return Returns a new shared instance of the IndexBuffer.
		 */
		static FakeRef<FakeIndexBuffer> Create(uint32 size);
	};

