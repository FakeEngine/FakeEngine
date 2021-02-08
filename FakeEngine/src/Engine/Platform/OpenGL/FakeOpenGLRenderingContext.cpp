#include "FakePch.h"
#include "FakeOpenGLRenderingContext.h"

#ifdef FAKE_PLATFORM_WINDOWS
	#ifdef FAKE_WINAPI_WINDOWS
		static HDC dc = nullptr;
		static HGLRC rc = nullptr;
	#endif
#endif

FakeOpenGLRenderingContext::FakeOpenGLRenderingContext(FakeWindow *window)
	: Window(window)
	{
	}

FakeOpenGLRenderingContext::~FakeOpenGLRenderingContext()
	{
	#ifdef FAKE_WINAPI_WINDOWS
		ReleaseDC((HWND)Window, dc);
		wglDeleteContext(rc);
	#endif
	}

void FakeOpenGLRenderingContext::Init()
	{
	#ifdef FAKE_WINAPI_WINDOWS
		PIXELFORMATDESCRIPTOR pfd =
			{
			sizeof(PIXELFORMATDESCRIPTOR), // size of this pfd
			1,							   // version number
			PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_TYPE_RGBA,
			24,							   // 24-bit color depth
			0, 0, 0, 0, 0, 0,			   // color bits ignored
			0,							   // no alpha buffer
			0,							   // shift bit ignored
			0,							   // no accumulation buffer
			0, 0, 0, 0,					   // accum bits ignored
			32,							   // 32-bit z-buffer
			0,							   // no stencil buffer
			0,							   // no auxiliary buffer
			PFD_MAIN_PLANE,				   // main layer
			0,							   // reserved
			0, 0, 0						   // layer masks ignored
			};

		dc = GetDC((HWND) Window->GetNativeWindow());
		int pf = ChoosePixelFormat(dc, &pfd);
		SetPixelFormat(dc, pf, &pfd);
		rc = wglCreateContext(dc);

		wglMakeCurrent(dc, rc);
		FAKE_ASSERT(gladLoadGL(), "Failed to load Context!");
	#elif FAKE_WINAPI_GLFW
		glfwMakeContextCurrent((GLFWwindow*) Window->GetNativeWindow());
		FAKE_ASSERT(gladLoadGLLoader((GLADloadproc) glfwGetProcAddress), "Failed to load OpenGL Context!");
	#endif
	}

void FakeOpenGLRenderingContext::SwapBuffers()
	{
	#ifdef FAKE_WINAPI_WINDOWS
		::SwapBuffers(dc);
	#elif FAKE_WINAPI_GLFW
		glfwSwapBuffers((GLFWwindow*) Window->GetNativeWindow());
	#endif
	}

void FakeOpenGLRenderingContext::Resize(uint32 width, uint32 height)
	{
	glViewport(0, 0, width, height);
	}

void FakeOpenGLRenderingContext::SetSwapInterval(bool enabled)
	{
	#ifdef FAKE_WINAPI_WINDOWS
		((BOOL(WINAPI*)(int32))wglGetProcAddress("wglSwapIntervalEXT"))(enabled);
	#elif FAKE_WINAPI_GLFW
		glfwSwapInterval(enabled);
	#endif
	}

void FakeOpenGLRenderingContext::MakeContextCurrent()
	{
	#ifdef FAKE_WINAPI_WINDOWS
		wglMakeCurrent(dc, rc);
	#elif FAKE_WINAPI_GLFW
		glfwMakeContextCurrent((GLFWwindow*) Window->GetNativeWindow());
	#endif
	}

