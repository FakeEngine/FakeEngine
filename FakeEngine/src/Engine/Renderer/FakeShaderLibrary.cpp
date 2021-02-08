#include "FakePch.h"
#include "FakeShaderLibrary.h"

FakeShaderLibrary::FakeShaderLibrary()
	{
	}

FakeShaderLibrary::~FakeShaderLibrary()
	{
	}

void FakeShaderLibrary::Add(const FakeRef<FakeShader> &shader)
	{
	auto &name = shader->GetName();
	FAKE_ASSERT(Shaders.find(*name) == Shaders.end());
	Shaders[*name] = shader;
	}

void FakeShaderLibrary::Load(const FakeString &path)
	{
	auto shader = FakeRef<FakeShader>(FakeShader::Create(path));
	auto &name = shader->GetName();
	FAKE_ASSERT(Shaders.find(*name) == Shaders.end());
	Shaders[*name] = shader;
	}

void FakeShaderLibrary::Load(const FakeString &name, const FakeString &path)
	{
	FAKE_ASSERT(Shaders.find(*name) == Shaders.end());
	Shaders[*name] = FakeRef<FakeShader>(FakeShader::Create(path));
	}

const FakeRef<FakeShader> &FakeShaderLibrary::Get(const FakeString &name) const
	{
	FAKE_ASSERT(Shaders.find(*name) != Shaders.end());
	return Shaders.at(*name);
	}

