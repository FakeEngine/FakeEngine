#include "FakePch.h"
#include "FakeOrthographicCameraController.h"

#include "Engine/Core/Window/FakeInput.h"

bool FakeOrthographicCameraController::OnMouseScrolled(FakeMouseScrolledEvent &e)
	{
	ZoomLevel -= (float)(e.GetMouseY() * 0.25);
	ZoomLevel = std::max(ZoomLevel, 0.25f);
	Camera.SetProjection(-AspectRatio * ZoomLevel, AspectRatio * ZoomLevel, -ZoomLevel, ZoomLevel);
	return false;
	}

bool FakeOrthographicCameraController::OnWindowResized(FakeWindowResizeEvent &e)
	{
	AspectRatio = (float) e.GetWidth() / (float) e.GetHeight();
	Camera.SetProjection(-AspectRatio * ZoomLevel, AspectRatio * ZoomLevel, -ZoomLevel, ZoomLevel);
	return false;
	}

FakeOrthographicCameraController::FakeOrthographicCameraController(float aspectRatio, bool rotation)
	: AspectRatio(aspectRatio), Camera(-AspectRatio * ZoomLevel, AspectRatio * ZoomLevel, -ZoomLevel, ZoomLevel), Rotation(rotation)
	{
	}

void FakeOrthographicCameraController::OnRender(FakeTimeStep ts)
	{
	if (FakeInput::IsKeyPressed(FAKE_KEY_A))
		{
		CameraPosition.X -= fake_cos(fake_radians(CameraRotation)) * CameraTranslationSpeed * ts;
		CameraPosition.Y -= fake_sin(fake_radians(CameraRotation)) * CameraTranslationSpeed * ts;
		}
	else if (FakeInput::IsKeyPressed(FAKE_KEY_D))
		{
		CameraPosition.X += fake_cos(fake_radians(CameraRotation)) * CameraTranslationSpeed * ts;
		CameraPosition.Y += fake_sin(fake_radians(CameraRotation)) * CameraTranslationSpeed * ts;
		}

	if (FakeInput::IsKeyPressed(FAKE_KEY_W))
		{
		CameraPosition.X += -fake_sin(fake_radians(CameraRotation)) * CameraTranslationSpeed * ts;
		CameraPosition.Y += fake_cos(fake_radians(CameraRotation)) * CameraTranslationSpeed * ts;
		}
	else if (FakeInput::IsKeyPressed(FAKE_KEY_S))
		{
		CameraPosition.X -= -fake_sin(fake_radians(CameraRotation)) * CameraTranslationSpeed * ts;
		CameraPosition.Y -= fake_cos(fake_radians(CameraRotation)) * CameraTranslationSpeed * ts;
		}


	if (Rotation)
		{
		if (FakeInput::IsKeyPressed(FAKE_KEY_Q))
			CameraRotation += CameraRotationSpeed * ts;
		else if (FakeInput::IsKeyPressed(FAKE_KEY_E))
			CameraRotation -= CameraRotationSpeed * ts;

		if (CameraRotation > 180.0f)
			CameraRotation -= 360.0f;
		else if (CameraRotation <= -180.0f)
			CameraRotation += 360.0f;

		Camera.SetRotation(CameraRotation);
		}

	Camera.SetPosition(CameraPosition);
	CameraTranslationSpeed = ZoomLevel;
	}

void FakeOrthographicCameraController::OnEvent(FakeEvent &e)
	{
	FakeEventDispatcher dispatcher(e);
	dispatcher.Dispatch<FakeMouseScrolledEvent>(FAKE_BIND_EVENT_FUNCTION(FakeOrthographicCameraController::OnMouseScrolled));
	dispatcher.Dispatch<FakeWindowResizeEvent>(FAKE_BIND_EVENT_FUNCTION(FakeOrthographicCameraController::OnWindowResized));
	}
