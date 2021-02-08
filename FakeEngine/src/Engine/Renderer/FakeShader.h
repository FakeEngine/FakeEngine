/*****************************************************************
 * \file   FakeShader.h
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

#include "FakeShaderUniform.h"
#include "Engine/Core/FakeAllocator.h"
#include "Engine/Core/Maths/FakeVector2.h"
#include "Engine/Core/Maths/FakeVector3.h"
#include "Engine/Core/Maths/FakeVector4.h"
#include "Engine/Core/Maths/FakeMatrix2x2.h"
#include "Engine/Core/Maths/FakeMatrix3x3.h"
#include "Engine/Core/Maths/FakeMatrix4x4.h"

enum class FakeUniformType
	{
	None = 0,
	Float, Float2, Float3, Float4,
	Matrix2x2, Matrix3x3, Matrix4x4,
	Int32, Uint32
	};

/**
 * 
 * .
 * 
 */
struct FakeUniformDecl
	{
	FakeUniformType Type;
	std::ptrdiff_t Offset;
	FakeString Name;
	};

/**
 * 
 * .
 * 
 */
struct FakeUniformBuffer
	{
	Byte *Buffer;
	std::vector<FakeUniformDecl> Uniforms;
	};

/**
 * 
 * .
 * 
 */
struct FakeUniformBufferBase
	{
	virtual const Byte *GetBuffer() const = 0;
	virtual const FakeUniformDecl *GetUniforms() const = 0;
	virtual uint32 GetUniformCount() const = 0;
	};

/**
 * 
 * .
 * 
 */
template<uint32 N, uint32 U>
struct FakeUniformBufferDeclaration : public FakeUniformBufferBase
	{
	Byte Buffer[N];
	FakeUniformDecl Uniforms[U];
	std::ptrdiff_t Cursor = 0;
	int32 Index = 0;

	virtual const Byte *GetBuffer() const override { return Buffer; }
	virtual const FakeUniformDecl *GetUniforms() const override { return Uniforms; }
	virtual uint32 GetUniformCount() const override { return U; }

	template<typename T>
	void Push(const FakeString &name, const T &data)
		{
		}

	template<>
	void Push(const FakeString &name, const float &data)
		{
		Uniforms[Index++] = { FakeUniformType::Float, Cursor, Name };
		memcpy(Buffer + Cursor, &data, sizeof(float));
		Cursor += sizeof(float);
		}

	template<>
	void Push(const FakeString &name, const int32 &data)
		{
		Uniforms[Index++] = { FakeUniformType::Int32, Cursor, Name };
		memcpy(Buffer + Cursor, &data, sizeof(int32));
		Cursor += sizeof(int32);
		}

	template<>
	void Push(const FakeString &name, const uint32 &data)
		{
		Uniforms[Index++] = { FakeUniformType::Uint32, Cursor, Name };
		memcpy(Buffer + Cursor, &data, sizeof(uint32));
		Cursor += sizeof(uint32);
		}

	template<>
	void Push(const FakeString &name, const FakeVec2f &data)
		{
		Uniforms[Index++] = { FakeUniformType::Float2, Cursor, Name };
		memcpy(Buffer + Cursor, &data, sizeof(FakeVec2f));
		Cursor += sizeof(FakeVec2f);
		}

	template<>
	void Push(const FakeString &name, const FakeVec3f &data)
		{
		Uniforms[Index++] = { FakeUniformType::Float3, Cursor, Name };
		memcpy(Buffer + Cursor, &data, sizeof(FakeVec3f));
		Cursor += sizeof(FakeVec3f);
		}

	template<>
	void Push(const FakeString &name, const FakeVec4f &data)
		{
		Uniforms[Index++] = { FakeUniformType::Float4, Cursor, Name };
		memcpy(Buffer + Cursor, &data, sizeof(FakeVec4f));
		Cursor += sizeof(FakeVec4f);
		}

	template<>
	void Push(const FakeString &name, const FakeMat2f &data)
		{
		Uniforms[Index++] = { FakeUniformType::Matrix2x2, Cursor, Name };
		memcpy(Buffer + Cursor, &data, sizeof(FakeMat2f));
		Cursor += sizeof(FakeMat2f);
		}

	template<>
	void Push(const FakeString &name, const FakeMat3f &data)
		{
		Uniforms[Index++] = { FakeUniformType::Matrix3x3, Cursor, Name };
		memcpy(Buffer + Cursor, &data, sizeof(FakeMat3f));
		Cursor += sizeof(FakeMat3f);
		}

	template<>
	void Push(const FakeString &name, const FakeMat4f &data)
		{
		Uniforms[Index++] = { FakeUniformType::Matrix4x4, Cursor, Name };
		memcpy(Buffer + Cursor, &data, sizeof(FakeMat4f));
		Cursor += sizeof(FakeMat4f);
		}
	};

 /**
  *
  * This class represents a Shader.
  *
  */
class FAKE_API FakeShader : public FakeRefCounted
	{
	public:
		using FakeShaderReloadedCallback = std::function<void()>;

		/**
		 *
		 * Binds the current Shader instance.
		 *
		 */
		virtual void Bind() const = 0;

		/**
		 *
		 * Unbinds the current Shader instance.
		 *
		 */
		virtual void Unbind() const = 0;

		/**
		 *
		 * Reloads the current Shader.
		 *
		 */
		virtual void Reload() = 0;

		/**
		 *
		 * Returns the current RendererID.
		 *
		 * @return Returns the current RendererID.
		 */
		virtual FakeRendererID GetRendererID() const = 0;

		/**
		 *
		 * Returns the Name of the Shader.
		 *
		 * @return Returns the Name of the Shader.
		 */
		virtual const FakeString &GetName() const = 0;

		/**
		 *
		 * Sets a Reloaded Callback. The function is going to be called if the shaderSource is going to be reloaded.
		 *
		 * @param callback The function that should be called automatically if the shaderSource is going to be reloaded.
		 */
		virtual void AddShaderReloadedCallback(const FakeShaderReloadedCallback &callback) = 0;

		/**
		 * 
		 * .
		 * 
		 * @param uniformBuffer
		 */
		virtual void UploadUniformBuffer(const FakeUniformBufferBase &uniformBuffer) = 0;

		virtual void SetVSMaterialUniformBuffer(FakeAllocator buffer) = 0;
		virtual void SetFSMaterialUniformBuffer(FakeAllocator buffer) = 0;
		virtual const FakeShaderUniformBufferList &GetVSRendererUniforms() const = 0;
		virtual const FakeShaderUniformBufferList &GetFSRendererUniforms() const = 0;
		virtual bool HasVSMaterialUniformBuffer() const = 0;
		virtual bool HasFSMaterialUniformBuffer() const = 0;
		virtual const FakeShaderUniformBufferDeclaration &GetVSMaterialUniformBuffer() const = 0;
		virtual const FakeShaderUniformBufferDeclaration &GetFSMaterialUniformBuffer() const = 0;
		virtual const FakeShaderResourceList &GetResources() const = 0;

		/**
		 *
		 * Sets a Uniform Buffer.
		 *
		 * @param name The Name of the Uniform buffer that should be set.
		 * @param data The actual buffer that should be set.
		 * @param size The size of the buffer that should be set.
		 */
		virtual void SetUniform(const FakeString &name, const void *data, uint32 size) = 0;

		/**
		 *
		 * Sets a Uniform.
		 *
		 * @param name The name of the Uniform that should be set.
		 * @param value The actual value that should be set.
		 */
		virtual void SetUniform(const FakeString &name, float value) = 0;

		/**
		 *
		 * Sets a Uniform.
		 *
		 * @param name The name of the Uniform that should be set.
		 * @param value The actual value that should be set.
		 */
		virtual void SetUniform(const FakeString &name, int32 value) = 0;

		/**
		 *
		 * Sets a Uniform.
		 *
		 * @param name The name of the Uniform that should be set.
		 * @param value The actual value that should be set.
		 */
		virtual void SetUniform(const FakeString &name, const FakeMat2f &value) = 0;

		/**
		 *
		 * Sets a Uniform.
		 *
		 * @param name The name of the Uniform that should be set.
		 * @param value The actual value that should be set.
		 */
		virtual void SetUniform(const FakeString &name, const FakeMat3f &value) = 0;

		/**
		 *
		 * Sets a Uniform.
		 *
		 * @param name The name of the Uniform that should be set.
		 * @param value The actual value that should be set.
		 */
		virtual void SetUniform(const FakeString &name, const FakeMat4f &value) = 0;

		/**
		 *
		 * Sets a Uniform.
		 *
		 * @param name The name of the Uniform that should be set.
		 * @param value The actual value that should be set.
		 */
		virtual void SetUniform(const FakeString &name, const FakeVec2f &value) = 0;

		/**
		 *
		 * Sets a Uniform.
		 *
		 * @param name The name of the Uniform that should be set.
		 * @param value The actual value that should be set.
		 */
		virtual void SetUniform(const FakeString &name, const FakeVec3f &value) = 0;

		/**
		 *
		 * Sets a Uniform.
		 *
		 * @param name The name of the Uniform that should be set.
		 * @param value The actual value that should be set.
		 */
		virtual void SetUniform(const FakeString &name, const FakeVec4f &value) = 0;

		/**
		 *
		 * Sets a Uniform.
		 *
		 * @param name The name of the Uniform that should be set.
		 * @param value The actual value that should be set.
		 */
		virtual void SetUniform(const FakeString &name, const FakeVec2i &value) = 0;

		/**
		 *
		 * Sets a Uniform.
		 *
		 * @param name The name of the Uniform that should be set.
		 * @param value The actual value that should be set.
		 */
		virtual void SetUniform(const FakeString &name, const FakeVec3i &value) = 0;

		/**
		 *
		 * Sets a Uniform.
		 *
		 * @param name The name of the Uniform that should be set.
		 * @param value The actual value that should be set.
		 */
		virtual void SetUniform(const FakeString &name, const FakeVec4i &value) = 0;

		/**
		 *
		 * Sets a Uniform.
		 *
		 * @param name The name of the Uniform that should be set.
		 * @param value The actual value that should be set.
		 * @param size The size of the value that should be set.
		 */
		virtual void SetUniform(const FakeString &name, int32 *value, uint32 size) = 0;

		/**
		 *
		 * Sets a Uniform.
		 *
		 * @param name The name of the Uniform that should be set.
		 * @param value The actual value that should be set.
		 * @param size The size of the value that should be set.
		 */
		virtual void SetUniform(const FakeString &name, float *value, uint32 size) = 0;

		/**
		 *
		 * Sets a Uniform.
		 *
		 * @param name The name of the Uniform that should be set.
		 * @param values The actual values that should be set.
		 * @param count The element count of the values that should be set.
		 */
		virtual void SetUniform(const FakeString &name, const FakeMat4f &values, uint32 count) = 0;

		/**
		 *
		 * Sets a Uniform.
		 *
		 * @param name The name of the Uniform that should be set.
		 * @param v0 The actual values that should be set.
		 * @param v1 The actual values that should be set.
		 */
		virtual void SetUniform(const FakeString &name, int32 v0, int32 v1) = 0;

		/**
		 *
		 * Sets a Uniform.
		 *
		 * @param name The name of the Uniform that should be set.
		 * @param v0 The actual values that should be set.
		 * @param v1 The actual values that should be set.
		 * @param v2 The actual values that should be set.
		 */
		virtual void SetUniform(const FakeString &name, int32 v0, int32 v1, int32 v2) = 0;

		/**
		 *
		 * Sets a Uniform.
		 *
		 * @param name The name of the Uniform that should be set.
		 * @param v0 The actual values that should be set.
		 * @param v1 The actual values that should be set.
		 * @param v2 The actual values that should be set.
		 * @param v3 The actual values that should be set.
		 */
		virtual void SetUniform(const FakeString &name, int32 v0, int32 v1, int32 v2, int32 v3) = 0;

		/**
		 *
		 * Sets a Uniform.
		 *
		 * @param name The name of the Uniform that should be set.
		 * @param v0 The actual values that should be set.
		 * @param v1 The actual values that should be set.
		 */
		virtual void SetUniform(const FakeString &name, float v0, float v1) = 0;

		/**
		 *
		 * Sets a Uniform.
		 *
		 * @param name The name of the Uniform that should be set.
		 * @param v0 The actual values that should be set.
		 * @param v1 The actual values that should be set.
		 * @param v2 The actual values that should be set.
		 */
		virtual void SetUniform(const FakeString &name, float v0, float v1, float v2) = 0;

		/**
		 *
		 * Sets a Uniform.
		 *
		 * @param name The name of the Uniform that should be set.
		 * @param v0 The actual values that should be set.
		 * @param v1 The actual values that should be set.
		 * @param v2 The actual values that should be set.
		 * @param v3 The actual values that should be set.
		 */
		virtual void SetUniform(const FakeString &name, float v0, float v1, float v2, float v3) = 0;

		/**
		 *
		 * Creates a new shader instance. The shader is being created from a file.
		 *
		 * @param filePath The virtual path to the shader.
		 * @return Returns a new shader instance.
		 */
		static FakeRef<FakeShader> Create(const FakeString &filePath);

		/**
		 *
		 * Creates a new shader instance. The shader is being created from strings.
		 *
		 * @param vertexShaderSource The Vertex Shader source.
		 * @param fragmentShaderSource The Fragment Shader source.
		 * @return Returns a new shader instance.
		 */
		static FakeRef<FakeShader> Create(const FakeString &vertexShaderSource, const FakeString &fragmentShaderSource);

		/**
		 *
		 * Creates a new shader instance. The shader is being created from strings.
		 *
		 * @param name The name of the Shader.
		 * @param vertexShaderSource The Vertex Shader source.
		 * @param fragmentShaderSource The Fragment Shader source.
		 * @return Returns a new shader instance.
		 */
		static FakeRef<FakeShader> Create(const FakeString &name, const FakeString &vertexShaderSource, const FakeString &fragmentShaderSource);
	};

