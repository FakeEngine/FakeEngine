/*****************************************************************
 * \file   FakeFramebufferPool.h
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

#include "FakeFramebuffer.h"

/**
 * 
 * .
 * 
 */
class FakeFramebufferPool final
	{
	private:

		std::vector<FakeRef<FakeFramebuffer>> FramebufferPool;
		static FakeFramebufferPool *Instance;

	public:

		/**
		 * 
		 * .
		 * 
		 * @param maxFBs
		 */
		FakeFramebufferPool(uint32 maxFBs = 32);

		/**
		 * 
		 * .
		 * 
		 */
		~FakeFramebufferPool();

		/**
		 * 
		 * .
		 * 
		 * @return 
		 */
		std::weak_ptr<FakeFramebuffer> AllocateBuffer();

		/**
		 * 
		 * .
		 * 
		 * @param framebuffer
		 */
		void Add(const FakeRef<FakeFramebuffer> &framebuffer);

		/**
		 * 
		 * .
		 * 
		 * @return 
		 */
		std::vector<FakeRef<FakeFramebuffer>> &GetAll();

		/**
		 * 
		 * .
		 * 
		 * @return 
		 */
		const std::vector<FakeRef<FakeFramebuffer>> &GetAll() const;

		/**
		 * 
		 * .
		 * 
		 * @return 
		 */
		static FakeFramebufferPool *GetGlobal();
	};
