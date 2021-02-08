#include "FakePch.h"
#include "FakeShader.h"

#include "Engine/Platform/OpenGL/FakeOpenGLShader.h"

FakeRef<FakeShader> FakeShader::Create(const FakeString &filePath)
	{
	#ifdef FAKE_RENDERER_OPENGL
		return FakeRef<FakeOpenGLShader>::Create(filePath);
	#endif
	}

FakeRef<FakeShader> FakeShader::Create(const FakeString &vertexShaderSource, const FakeString &fragmentShaderSource)
	{
	#ifdef FAKE_RENDERER_OPENGL
		return FakeRef<FakeOpenGLShader>::Create(vertexShaderSource, fragmentShaderSource);
	#endif
	}

FakeRef<FakeShader> FakeShader::Create(const FakeString &name, const FakeString &vertexShaderSource, const FakeString &fragmentShaderSource)
	{
	#ifdef FAKE_RENDERER_OPENGL
		return FakeRef<FakeOpenGLShader>::Create(name, vertexShaderSource, fragmentShaderSource);
	#endif
	}

