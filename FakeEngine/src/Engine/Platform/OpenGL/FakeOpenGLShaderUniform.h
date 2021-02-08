/*****************************************************************
 * \file   FakeOpenGLShaderUniform.h
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

#include "Engine/Renderer/FakeShaderUniform.h"

/**
 * 
 * .
 * 
 */
class FakeOpenGLResourceDeclaration : public FakeShaderResourceDeclaration
	{
	friend class FakeOpenGLShader;

	public:

		enum class Type
			{
			NONE, TEXTURE2D, TEXTURECUBE
			};

	private:
		
		FakeString Name;
		uint32 Register = 0;
		uint32 Count = 0;
		Type ShaderType;

	public:

		FakeOpenGLResourceDeclaration(Type type, const FakeString &name, uint32 count);

		inline const FakeString &GetName() const override { return Name; }
		inline uint32 GetRegister() const override { return Register; }
		inline uint32 GetCount() const override { return Count; }

		inline Type GetType() const { return ShaderType; }

		static Type StringToType(const FakeString &type);
		static FakeString TypeToString(Type type);
	};

/**
 * 
 * .
 * 
 */
class FakeOpenGLShaderUniformDeclaration : public FakeShaderUniformDeclaration
	{
	friend class FakeOpenGLShader;
	friend class FakeOpenGLShaderUniformDeclaration;
	friend class FakeOpenGLShaderUniformBufferDeclaration;

	public:

		enum class Type
			{
			NONE, FLOAT32, VEC2, VEC3, VEC4, MAT2, MAT3, MAT4, INT32, BOOL, STRUCT
			};

	private:

		FakeString Name;
		uint32 Size;
		uint32 Count;
		uint32 Offset;
		FakeShaderDomain Domain;

		Type ShaderType;
		FakeShaderStruct *Struct;
		mutable int32 Location;

	protected:

		void SetOffset(uint32 offset) override;

	public:

		FakeOpenGLShaderUniformDeclaration(FakeShaderDomain domain, Type type, const FakeString &name, uint32 count = 1);
		FakeOpenGLShaderUniformDeclaration(FakeShaderDomain domain, FakeShaderStruct *uniformStruct, const FakeString &name, uint32 count = 1);

		inline const FakeString &GetName() const override { return Name; }
		inline uint32 GetSize() const override { return Size; }
		inline uint32 GetCount() const override { return Count; }
		inline uint32 GetOffset() const override { return Offset; }

		inline uint32 GetAbsoluteOffset() const { return Struct ? Struct->GetOffset() + Offset : Offset; }
		inline FakeShaderDomain GetDomain() const { return Domain; }
		inline int32 GetLocation() const { return Location; }
		inline Type GetType() const { return ShaderType; }
		inline bool IsArray() const { return Count > 1; }
		inline const FakeShaderStruct &GetShaderUniformStruct() const { FAKE_ASSERT(Struct); return *Struct; }

		static uint32 SizeOfUniformType(Type type);
		static Type StringToType(const FakeString &type);
		static FakeString TypeToString(Type type);
	};

/**
 * 
 * .
 * 
 */
struct FakeOpenGLShaderUniformField
	{
	FakeOpenGLShaderUniformDeclaration::Type Type;
	FakeString Name;
	uint32 Count;
	mutable uint32 Size;
	mutable int32 Location;
	};

/**
 * 
 * .
 * 
 */
class FakeOpenGLShaderUniformBufferDeclaration : public FakeShaderUniformBufferDeclaration
	{
	friend class FakeShader;

	private:

		FakeString Name;
		FakeShaderUniformList Uniforms;
		uint32 Register;
		uint32 Size;
		FakeShaderDomain Domain;

	public:

		FakeOpenGLShaderUniformBufferDeclaration(const FakeString &name, FakeShaderDomain domain);

		void PushUniform(FakeOpenGLShaderUniformDeclaration *uniform);

		inline const FakeString &GetName() const override { return Name; }
		inline uint32 GetRegister() const override { return Register; }
		inline uint32 GetSize() const override { return Size; }
		virtual FakeShaderDomain GetDomain() const { return Domain; }
		inline const FakeShaderUniformList &GetUniformDeclarations() const override { return Uniforms; }

		FakeShaderUniformDeclaration *FindUniform(const FakeString &name);
	};
