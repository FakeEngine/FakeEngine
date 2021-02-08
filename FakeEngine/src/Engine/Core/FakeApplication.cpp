#include "FakePch.h"
#include "FakeApplication.h"

#include "Engine/Core/FakeTimer.h"
#include "Engine/Core/FakeVirtualFileSystem.h"
#include "Engine/Renderer/FakeRenderer.h"
#include "Engine/Renderer/FakeFramebufferPool.h"

FakeApplication *FakeApplication::Self = nullptr;

bool FakeApplication::OnWindowClose(const FakeWindowCloseEvent &e)
	{
	Running = false;
	return true;
	}

bool FakeApplication::OnWindowResize(const FakeWindowResizeEvent &e)
	{
	if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
		Minimized = true;
		return false;
		}

	Minimized = false;

	// Resize rendering viewport
	FakeRenderer::SetViewport(e.GetWidth(), e.GetHeight());

	// Resize all framebuffers
	auto &fbs = FakeFramebufferPool::GetGlobal()->GetAll();
	for (auto &fb : fbs)
		{
		if (!fb->GetSpecification().NoResize)
			fb->Resize(e.GetWidth(), e.GetHeight());
		}

	return true;
	}

FakeApplication::FakeApplication()
	{
	FAKE_ASSERT(!Self, "Application already exists!");
	Self = this;

	// Virtuelles Dateisystem initialisieren
	FakeVirtualFileSystem::Init();
	}

FakeApplication::FakeApplication(const FakeString &title, uint32 width, uint32 height)
	{
	FAKE_ASSERT(!Self, "Application already exists!");
	Self = this;
	EnableRendering = true;

	// Fenster erstellen
	Window = FakeWindow::Create(title, width, height);
	Window->SetEventCallbackFn(FAKE_BIND_EVENT_FUNCTION(FakeApplication::OnEvent));
	Window->SetVSync(false);

	// Virtuelles Dateisystem initialisieren
	FakeVirtualFileSystem::Init();

	// Renderer erstellen
	FakeRenderer::Init();
	FakeRenderer::Render();
	}

FakeApplication::~FakeApplication()
	{
	if (EnableRendering)
		FakeRenderer::Shutdown();

	FakeVirtualFileSystem::Shutdown();
	}

void FakeApplication::PushLayer(FakeLayer *layer)
	{
	LayerStack.PushLayer(layer);
	layer->OnAttach();
	}

void FakeApplication::PopLayer(FakeLayer *layer)
	{
	LayerStack.PopLayer(layer);
	layer->OnDetach();
	}

void FakeApplication::PushOverlay(FakeLayer *overlay)
	{
	LayerStack.PushOverlay(overlay);
	overlay->OnAttach();
	}

void FakeApplication::PopOverlay(FakeLayer *overlay)
	{
	LayerStack.PopOverlay(overlay);
	overlay->OnDetach();
	}

void FakeApplication::OnEvent(FakeEvent &e)
	{
	FakeEventDispatcher dispatcher(e);
	dispatcher.Dispatch<FakeWindowCloseEvent>(FAKE_BIND_EVENT_FUNCTION(FakeApplication::OnWindowClose));
	dispatcher.Dispatch<FakeWindowResizeEvent>(FAKE_BIND_EVENT_FUNCTION(FakeApplication::OnWindowResize));

	for (auto it = LayerStack.end(); it != LayerStack.begin();)
		{
		(*--it)->OnEvent(e);
		if (e.Handled)
			break;
		}
	}

void FakeApplication::Run()
	{
	OnInit();

	double t = 0.0;
	while (Running)
		{
		if (EnableRendering)
			{
			FakeRenderer::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
			FakeRenderer::Clear();
			}

		if (-1.0 == InitialTime)
			{
			InitialTime = FakeTimer::GetTime();
			}

		double currentTime = FakeTimer::GetTime();
		ElapsedTime = (currentTime - InitialTime) / 1000000.0;
		FakeTimeStep ts = (ElapsedTime - FrameTime) * 1000.0;
		FrameTime = ElapsedTime;

		if (!Minimized && EnableRendering)
			{
			for (FakeLayer *layer : LayerStack)
				{
				layer->OnRender(ts);
				}

			FakeRenderer::Render();
			}

		if (EnableRendering)
			{
			Window->Flush(ts);
			++FrameCounter;

			if (ElapsedTime - t > 1.0)
				{
				FrameCounter = 0;
				t += 1.0;
				}
			}
		}

	OnShutdown();
	}

void FakeApplication::CloseApplication()
	{
	Running = false;
	}

FakeApplication &FakeApplication::Get()
	{
	return *Self;
	}

FakeWindow &FakeApplication::GetWindow()
	{
	return *Window;
	}

