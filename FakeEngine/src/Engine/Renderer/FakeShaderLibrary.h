/*****************************************************************
 * \file   FakeShaderLibrary.h
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

/**
 * 
 * .
 * 
 */
class FakeShaderLibrary : public FakeRefCounted
	{
	private:

		// we can't use FakeString here because the FakeString is currently missing a hash function implementation to use it as a key in std's libs.
		std::unordered_map<std::string, FakeRef<FakeShader>> Shaders;

	public:

		/**
		 * 
		 * .
		 * 
		 */
		FakeShaderLibrary();

		/**
		 * 
		 * .
		 * 
		 */
		~FakeShaderLibrary();

		/**
		 * 
		 * .
		 * 
		 * @param shader
		 */
		void Add(const FakeRef<FakeShader> &shader);

		/**
		 * 
		 * .
		 * 
		 * @param path
		 */
		void Load(const FakeString &path);

		/**
		 * 
		 * .
		 * 
		 * @param name
		 * @param path
		 */
		void Load(const FakeString &name, const FakeString &path);

		/**
		 * 
		 * .
		 * 
		 * @param name
		 * @return 
		 */
		const FakeRef<FakeShader> &Get(const FakeString &name) const;
	};
