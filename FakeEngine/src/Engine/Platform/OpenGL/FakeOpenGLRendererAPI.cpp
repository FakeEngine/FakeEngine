#include "FakePch.h"
#include "Engine/Renderer/FakeRendererAPI.h"

#ifdef FAKE_RENDERER_OPENGL

#include <glad/glad.h>

static void OpenGLLogMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
	{
	switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:
			FAKE_LOG_ERROR("[OpenGL Debug HIGH] %s", message);
			FAKE_ASSERT(false, "GL_DEBUG_SEVERITY_HIGH");
			break;

		case GL_DEBUG_SEVERITY_MEDIUM:
			FAKE_LOG_WARN("[OpenGL Debug MEDIUM] %s", message);
			break;

		case GL_DEBUG_SEVERITY_LOW:
			FAKE_LOG_INFO("[OpenGL Debug LOW] %s", message);
			break;

		case GL_DEBUG_SEVERITY_NOTIFICATION:
		//	FAKE_LOG_TRACE("[OpenGL Debug NOTIFICATION] %s", message);
			break;
		}
	}

void FakeRendererAPI::Init()
	{
	glDebugMessageCallback(OpenGLLogMessage, nullptr);
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	glFrontFace(GL_CCW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_MULTISAMPLE);
	glEnable(GL_STENCIL_TEST);

	auto &caps = FakeRendererAPI::GetCapabilities();
	caps.Vendor = (const char *) glGetString(GL_VENDOR);
	caps.Renderer = (const char *) glGetString(GL_RENDERER);
	caps.Version = (const char *) glGetString(GL_VERSION);

	glGetIntegerv(GL_MAX_SAMPLES, &caps.MaxSamples);
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY, &caps.MaxAnisotropy);

	glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &caps.MaxTextureUnits);

	GLenum error = glGetError();
	while (error != GL_NO_ERROR)
		{
		FAKE_LOG_ERROR("OpenGL Error %d", error);
		error = glGetError();
		}

	}

void FakeRendererAPI::Shutdown()
	{

	}

void FakeRendererAPI::Clear()
	{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

void FakeRendererAPI::SetClearColor(float r, float g, float b, float a)
	{
	glClearColor(r, g, b, a);
	}


void FakeRendererAPI::SetClearColor(const FakeVec4f &color)
	{
	glClearColor(color.X, color.Y, color.Z, color.W);
	}

void FakeRendererAPI::DrawIndexed(uint32 count, FakePrimitiveType type, bool depthTest)
	{
	if (!depthTest)
		glDisable(GL_DEPTH_TEST);

	GLenum glPrimitiveType = 0;
	switch (type)
		{
		case FakePrimitiveType::Triangles:
			glPrimitiveType = GL_TRIANGLES;
			break;

		case FakePrimitiveType::Lines:
			glPrimitiveType = GL_LINES;
			break;
		}

	// The actual render call
	glDrawElements(glPrimitiveType, count, GL_UNSIGNED_INT, nullptr);

	if (!depthTest)
		glEnable(GL_DEPTH_TEST);
	}

void FakeRendererAPI::SetViewport(uint32 width, uint32 height)
	{
	glViewport(0, 0, width, height);
	}

void FakeRendererAPI::SetLineThickness(float thickness)
	{
	glLineWidth(thickness);
	}

#endif
