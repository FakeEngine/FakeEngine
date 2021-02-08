#include "FakePch.h"
#include "FakeOpenGLShaderUniform.h"

// ================================================================================================================================
// FakeOpenGLResourceDeclaration
// ================================================================================================================================

FakeOpenGLResourceDeclaration::FakeOpenGLResourceDeclaration(Type type, const FakeString &name, uint32 count)
	: ShaderType(type), Name(name), Count(count)
	{
	}

FakeOpenGLResourceDeclaration::Type FakeOpenGLResourceDeclaration::StringToType(const FakeString &type)
	{
	if (type == "sampler2D")    return Type::TEXTURE2D;
	if (type == "sampler2DMS")  return Type::TEXTURE2D;
	if (type == "samplerCube")  return Type::TEXTURECUBE;

	return Type::NONE;

	}

FakeString FakeOpenGLResourceDeclaration::TypeToString(Type type)
	{
	switch (type)
		{
		case Type::TEXTURE2D:	return "sampler2D";
		case Type::TEXTURECUBE:	return "samplerCube";
		}

	return "Invalid Type";
	}

// ================================================================================================================================
// FakeOpenGLShaderUniformDeclaration
// ================================================================================================================================

void FakeOpenGLShaderUniformDeclaration::SetOffset(uint32 offset)
	{
	if (ShaderType == FakeOpenGLShaderUniformDeclaration::Type::STRUCT)
		Struct->SetOffset(offset);

	Offset = offset;
	}

FakeOpenGLShaderUniformDeclaration::FakeOpenGLShaderUniformDeclaration(FakeShaderDomain domain, Type type, const FakeString &name, uint32 count)
	: ShaderType(type), Struct(nullptr), Domain(domain), Name(name), Count(count)
	{
	Size = SizeOfUniformType(type) * count;
	}

FakeOpenGLShaderUniformDeclaration::FakeOpenGLShaderUniformDeclaration(FakeShaderDomain domain, FakeShaderStruct *uniformStruct, const FakeString &name, uint32 count)
	: Struct(uniformStruct), ShaderType(FakeOpenGLShaderUniformDeclaration::Type::STRUCT), Domain(domain), Name(name), Count(count)
	{
	Size = Struct->GetSize() * count;
	}

uint32 FakeOpenGLShaderUniformDeclaration::SizeOfUniformType(Type type)
	{
	switch (type)
		{
		case FakeOpenGLShaderUniformDeclaration::Type::BOOL:       return 1;
		case FakeOpenGLShaderUniformDeclaration::Type::INT32:      return 4;
		case FakeOpenGLShaderUniformDeclaration::Type::FLOAT32:    return 4;
		case FakeOpenGLShaderUniformDeclaration::Type::VEC2:       return 4 * 2;
		case FakeOpenGLShaderUniformDeclaration::Type::VEC3:       return 4 * 3;
		case FakeOpenGLShaderUniformDeclaration::Type::VEC4:       return 4 * 4;
		case FakeOpenGLShaderUniformDeclaration::Type::MAT2:       return 4 * 2 * 2;
		case FakeOpenGLShaderUniformDeclaration::Type::MAT3:       return 4 * 3 * 3;
		case FakeOpenGLShaderUniformDeclaration::Type::MAT4:       return 4 * 4 * 4;
		}

	return 0;
	}

FakeOpenGLShaderUniformDeclaration::Type FakeOpenGLShaderUniformDeclaration::StringToType(const FakeString &type)
	{
	if (type == "int")      return Type::INT32;
	if (type == "bool")     return Type::BOOL;
	if (type == "float")    return Type::FLOAT32;
	if (type == "vec2")     return Type::VEC2;
	if (type == "vec3")     return Type::VEC3;
	if (type == "vec4")     return Type::VEC4;
	if (type == "mat2")     return Type::MAT2;
	if (type == "mat3")     return Type::MAT3;
	if (type == "mat4")     return Type::MAT4;

	return Type::NONE;
	}

FakeString FakeOpenGLShaderUniformDeclaration::TypeToString(Type type)
	{
	switch (type)
		{
		case FakeOpenGLShaderUniformDeclaration::Type::INT32:      return "int32";
		case FakeOpenGLShaderUniformDeclaration::Type::BOOL:       return "bool";
		case FakeOpenGLShaderUniformDeclaration::Type::FLOAT32:    return "float";
		case FakeOpenGLShaderUniformDeclaration::Type::VEC2:       return "vec2";
		case FakeOpenGLShaderUniformDeclaration::Type::VEC3:       return "vec3";
		case FakeOpenGLShaderUniformDeclaration::Type::VEC4:       return "vec4";
		case FakeOpenGLShaderUniformDeclaration::Type::MAT2:       return "mat2";
		case FakeOpenGLShaderUniformDeclaration::Type::MAT3:       return "mat3";
		case FakeOpenGLShaderUniformDeclaration::Type::MAT4:       return "mat4";
		}

	return "Invalid Type";
	}

// ================================================================================================================================
// FakeOpenGLShaderUniformBufferDeclaration
// ================================================================================================================================

FakeOpenGLShaderUniformBufferDeclaration::FakeOpenGLShaderUniformBufferDeclaration(const FakeString &name, FakeShaderDomain domain)
	: Name(name), Domain(domain), Size(0), Register(0)
	{
	}

void FakeOpenGLShaderUniformBufferDeclaration::PushUniform(FakeOpenGLShaderUniformDeclaration *uniform)
	{
	uint32 offset = 0;
	if (Uniforms.size())
		{
		FakeOpenGLShaderUniformDeclaration *prev = (FakeOpenGLShaderUniformDeclaration*)Uniforms.back();
		offset = prev->GetOffset() + prev->GetSize();
		}

	uniform->SetOffset(offset);
	Size += uniform->GetSize();
	Uniforms.push_back(uniform);
	}

FakeShaderUniformDeclaration *FakeOpenGLShaderUniformBufferDeclaration::FindUniform(const FakeString &name)
	{
	for (FakeShaderUniformDeclaration *uniform : Uniforms)
		{
		if (uniform->GetName() == name)
			return uniform;
		}

	return nullptr;
	}

