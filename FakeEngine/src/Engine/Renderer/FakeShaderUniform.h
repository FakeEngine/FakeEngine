/*****************************************************************
 * \file   FakeShaderUniform.h
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

#include "FakePch.h"

enum class FakeShaderDomain
	{
	None = 0,
	Vertex,
	Fragment
	};

/**
 * 
 * .
 * 
 */
class FakeShaderUniformDeclaration
	{
	friend class FakeShader;
	friend class FakeOpenGLShader;
	friend class FakeShaderStruct;

	protected:

		virtual void SetOffset(uint32 offset) = 0;

	public:

		virtual const FakeString &GetName() const = 0;
		virtual uint32 GetSize() const = 0;
		virtual uint32 GetCount() const = 0;
		virtual uint32 GetOffset() const = 0;
		virtual FakeShaderDomain GetDomain() const = 0;
	};

typedef std::vector<FakeShaderUniformDeclaration*> FakeShaderUniformList;

/**
 * 
 * .
 * 
 */
class FakeShaderUniformBufferDeclaration : public FakeRefCounted
	{
	public:

		virtual const FakeString &GetName() const = 0;
		virtual uint32 GetRegister() const = 0;
		virtual uint32 GetSize() const = 0;
		virtual const FakeShaderUniformList &GetUniformDeclarations() const = 0;

		virtual FakeShaderUniformDeclaration *FindUniform(const FakeString &name) = 0;
	};

typedef std::vector<FakeShaderUniformBufferDeclaration*> FakeShaderUniformBufferList;

/**
 * 
 * .
 * 
 */
class FakeShaderStruct
	{
	friend class FakeShader;

	private:

		FakeString Name;
		std::vector<FakeShaderUniformDeclaration*> Fields;
		uint32 Size;
		uint32 Offset;

	public:

		FakeShaderStruct(const FakeString &name)
			: Name(name), Size(0), Offset(0)
			{
			}

		void AddField(FakeShaderUniformDeclaration *field)
			{
			Size += field->GetSize();
			uint32 offset = 0;

			if (Fields.size())
				{
				FakeShaderUniformDeclaration *prev = Fields.back();
				offset = prev->GetOffset() + prev->GetSize();
				}

			field->SetOffset(offset);
			Fields.push_back(field);
			}

		inline void SetOffset(uint32 offset) { Offset = offset; }
		inline const FakeString &GetName() { return Name; }
		inline const std::vector<FakeShaderUniformDeclaration*> &GetFields() const { return Fields; }
		inline uint32 GetSize() const { return Size; }
		inline uint32 GetOffset() const { return Offset; }
	};

typedef std::vector<FakeShaderStruct*> FakeShaderStructList;

/**
 * 
 * .
 * 
 */
class FakeShaderResourceDeclaration
	{
	public:

		virtual const FakeString &GetName() const = 0;
		virtual uint32 GetRegister() const = 0;
		virtual uint32 GetCount() const = 0;
	};

typedef std::vector<FakeShaderResourceDeclaration*> FakeShaderResourceList;
