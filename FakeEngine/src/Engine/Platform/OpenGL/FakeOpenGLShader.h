/*****************************************************************
 * \file   FakeOpenGLShader.h
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

#include "Engine/Core/FakeAllocator.h"
#include "Engine/Renderer/FakeShader.h"
#include "FakeOpenGLShaderUniform.h"

/**
 * 
 * .
 * 
 */
class FakeOpenGLShader : public FakeShader
	{
	private:

		FakeRendererID RendererID = 0;
		bool Loaded = false;
		bool IsCompute = false;

		FakeString Name = "Undefined";
		FakeString AssetPath;
		std::unordered_map<GLenum, std::string> ShaderSources;
		std::vector<FakeShaderReloadedCallback> ShaderReloadedCallbacks;
		std::unordered_map<std::string, int32> UniformLocations;

		FakeShaderUniformBufferList VSRendererUniformBuffers;
		FakeShaderUniformBufferList FSRendererUniformBuffers;
		FakeRef<FakeOpenGLShaderUniformBufferDeclaration> VSMaterialUniformBuffer;
		FakeRef<FakeOpenGLShaderUniformBufferDeclaration> FSMaterialUniformBuffer;
		FakeShaderResourceList Resources;
		FakeShaderStructList Structs;

	private:

		void Load(const FakeString &source, bool shouldPreProccess = true);
		std::unordered_map<GLenum, std::string> PreProcess(const FakeString &source);
		int32 GetUniformLocation(const FakeString &name) const;

		void Parse();
		void ParseUniform(const FakeString &statement, FakeShaderDomain domain);
		void ParseUniformStruct(const FakeString &block, FakeShaderDomain domain);
		FakeShaderStruct *FindStruct(const FakeString &name);

		void ResolveUniforms();
		void CompileAndUploadShader();

		void ResolveAndSetUniforms(const FakeRef<FakeOpenGLShaderUniformBufferDeclaration> &decl, FakeAllocator buffer);
		void ResolveAndSetUniform(FakeOpenGLShaderUniformDeclaration *uniform, FakeAllocator buffer);
		void ResolveAndSetUniformArray(FakeOpenGLShaderUniformDeclaration *uniform, FakeAllocator buffer);
		void ResolveAndSetUniformField(const FakeOpenGLShaderUniformDeclaration &field, Byte *data, int32_t offset);

		void UploadUniformInt(uint32 location, int32 value);
		void UploadUniformInt2(uint32 location, const FakeVec2i &values);
		void UploadUniformInt3(uint32 location, const FakeVec3i &values);
		void UploadUniformInt4(uint32 location, const FakeVec4i &values);
		void UploadUniformIntArray(uint32 location, int32 *values, int32 count);

		void UploadUniformFloat(uint32 location, float value);
		void UploadUniformFloat2(uint32 location, const FakeVec2f &values);
		void UploadUniformFloat3(uint32 location, const FakeVec3f &values);
		void UploadUniformFloat4(uint32 location, const FakeVec4f &values);
		void UploadUniformFloatArray(uint32 location, float *values, int32 count);

		void UploadUniformMat2(uint32 location, const FakeMat2f &values);
		void UploadUniformMat3(uint32 location, const FakeMat3f &values);
		void UploadUniformMat4(uint32 location, const FakeMat4f &values);
		void UploadUniformMat4Array(uint32 location, const FakeMat4f &values, uint32 count);

		void UploadUniformStruct(FakeOpenGLShaderUniformDeclaration *uniform, Byte *buffer, uint32 offset);
		void UploadUniformStruct(const FakeString &name, const void *data, uint32 size);

		void UploadUniformInt(const FakeString &name, int32 value);
		void UploadUniformInt2(const FakeString &name, const FakeVec2i &values);
		void UploadUniformInt3(const FakeString &name, const FakeVec3i &values);
		void UploadUniformInt4(const FakeString &name, const FakeVec4i &values);
		void UploadUniformIntArray(const FakeString &name, int32 *values, uint32 count);

		void UploadUniformFloat(const FakeString &name, float value);
		void UploadUniformFloat2(const FakeString &name, const FakeVec2f &value);
		void UploadUniformFloat3(const FakeString &name, const FakeVec3f &value);
		void UploadUniformFloat4(const FakeString &name, const FakeVec4f &value);
		void UploadUniformFloatArray(const FakeString &name, float *values, uint32 count);

		void UploadUniformMat2(const FakeString &name, const FakeMat2f &value);
		void UploadUniformMat3(const FakeString &name, const FakeMat3f &value);
		void UploadUniformMat4(const FakeString &name, const FakeMat4f &value);
		void UploadUniformMat4Array(const FakeString &name, const FakeMat4f &values, uint32 count);

	public:

		FakeOpenGLShader() = default;
		FakeOpenGLShader(const FakeString &filePath);
		FakeOpenGLShader(const FakeString &vertexSrc, const FakeString &fragmentSrc);
		FakeOpenGLShader(const FakeString &name, const FakeString &vertexSrc, const FakeString &fragmentSrc);

		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual void Reload() override;

		virtual FakeRendererID GetRendererID() const override { return RendererID; }
		virtual const FakeString &GetName() const override { return Name; }
		virtual void AddShaderReloadedCallback(const FakeShaderReloadedCallback &callback) override { ShaderReloadedCallbacks.push_back(callback); }
		virtual void UploadUniformBuffer(const FakeUniformBufferBase &uniformBuffer) override;

		virtual void SetVSMaterialUniformBuffer(FakeAllocator buffer) override;
		virtual void SetFSMaterialUniformBuffer(FakeAllocator buffer) override;
		virtual const FakeShaderUniformBufferList &GetVSRendererUniforms() const override { return VSRendererUniformBuffers; }
		virtual const FakeShaderUniformBufferList &GetFSRendererUniforms() const override { return FSRendererUniformBuffers; }
		virtual bool HasVSMaterialUniformBuffer() const override { return (bool)VSMaterialUniformBuffer; }
		virtual bool HasFSMaterialUniformBuffer() const override { return (bool)FSMaterialUniformBuffer; }
		virtual const FakeShaderUniformBufferDeclaration &GetVSMaterialUniformBuffer() const override { return *VSMaterialUniformBuffer; }
		virtual const FakeShaderUniformBufferDeclaration &GetFSMaterialUniformBuffer() const override { return *FSMaterialUniformBuffer; }
		virtual const FakeShaderResourceList &GetResources() const override { return Resources; }

		virtual void SetUniform(const FakeString &name, const void *data, uint32 size) override;
		virtual void SetUniform(const FakeString &name, float value) override;
		virtual void SetUniform(const FakeString &name, int32 value) override;
		virtual void SetUniform(const FakeString &name, const FakeMat2f &value) override;
		virtual void SetUniform(const FakeString &name, const FakeMat3f &value) override;
		virtual void SetUniform(const FakeString &name, const FakeMat4f &value) override;
		virtual void SetUniform(const FakeString &name, const FakeVec2f &value) override;
		virtual void SetUniform(const FakeString &name, const FakeVec3f &value) override;
		virtual void SetUniform(const FakeString &name, const FakeVec4f &value) override;
		virtual void SetUniform(const FakeString &name, const FakeVec2i &value) override;
		virtual void SetUniform(const FakeString &name, const FakeVec3i &value) override;
		virtual void SetUniform(const FakeString &name, const FakeVec4i &value) override;
		virtual void SetUniform(const FakeString &name, int32 *value, uint32 size) override;
		virtual void SetUniform(const FakeString &name, float *value, uint32 size) override;
		virtual void SetUniform(const FakeString &name, const FakeMat4f &values, uint32 count) override;
		virtual void SetUniform(const FakeString &name, int32 v0, int32 v1) override;
		virtual void SetUniform(const FakeString &name, int32 v0, int32 v1, int32 v2) override;
		virtual void SetUniform(const FakeString &name, int32 v0, int32 v1, int32 v2, int32 v3) override;
		virtual void SetUniform(const FakeString &name, float v0, float v1) override;
		virtual void SetUniform(const FakeString &name, float v0, float v1, float v2) override;
		virtual void SetUniform(const FakeString &name, float v0, float v1, float v2, float v3) override;
	};
