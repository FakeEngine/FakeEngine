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
		CameraPosition.x -= cos(glm::radians(CameraRotation)) * CameraTranslationSpeed * (float)ts;
		CameraPosition.y -= sin(glm::radians(CameraRotation)) * CameraTranslationSpeed * (float)ts;
		}
	else if (FakeInput::IsKeyPressed(FAKE_KEY_D))
		{
		CameraPosition.x += cos(glm::radians(CameraRotation)) * CameraTranslationSpeed * (float) ts;
		CameraPosition.y += sin(glm::radians(CameraRotation)) * CameraTranslationSpeed * (float) ts;
		}

	if (FakeInput::IsKeyPressed(FAKE_KEY_W))
		{
		CameraPosition.x += -sin(glm::radians(CameraRotation)) * CameraTranslationSpeed * (float) ts;
		CameraPosition.y += cos(glm::radians(CameraRotation)) * CameraTranslationSpeed * (float)ts;
		}
	else if (FakeInput::IsKeyPressed(FAKE_KEY_S))
		{
		CameraPosition.x -= -sin(glm::radians(CameraRotation)) * CameraTranslationSpeed * (float) ts;
		CameraPosition.y -= cos(glm::radians(CameraRotation)) * CameraTranslationSpeed * (float)ts;
		}

	if (Rotation)
		{
		if (FakeInput::IsKeyPressed(FAKE_KEY_Q))
			CameraRotation += CameraRotationSpeed * (float) ts;
		if (FakeInput::IsKeyPressed(FAKE_KEY_E))
			CameraRotation -= CameraRotationSpeed * (float) ts;

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