#include "FakePch.h"
#include "FakeEditorCamera.h"

#include "Engine/Core/Window/FakeInput.h"

FakeEditorCamera::FakeEditorCamera(const FakeMat4f &projectionMatrix)
	: ProjectionMatrix(projectionMatrix)
	{
	Rotation = FakeVec3f(90.0f, 0.0f, 0.0f);
	FocalPoint = FakeVec3f(0.0f);

	FakeVec3f position = { -5, 5, 5 };
	Distance = FakeVec3f::Distance(position, FocalPoint);

	Yaw = 3.0f * FAKE_PI / 4.0f;
	Pitch = FAKE_PI / 4.0f;

	UpdateCameraView();
	}

void FakeEditorCamera::Focus()
	{
	}

void FakeEditorCamera::OnRender(FakeTimeStep ts)
	{
	if (FakeInput::IsKeyPressed(FakeKeyCode::LEFT_ALT))
		{
		const FakeVec2f &mouse{ (float)FakeInput::GetMouseX(), (float)FakeInput::GetMouseY() };
		FakeVec2f delta = (mouse - InitialMousePosition) * 0.003f;
		InitialMousePosition = mouse;

		if (FakeInput::IsMouseButtonPressed(FakeMouseButtonCode::BUTTON_MIDDLE))
			MousePan(delta);
		else if (FakeInput::IsMouseButtonPressed(FakeMouseButtonCode::BUTTON_LEFT))
			MouseRotate(delta);
		else if (FakeInput::IsMouseButtonPressed(FakeMouseButtonCode::BUTTON_RIGHT))
			MouseZoom(delta.Y);
		}

	UpdateCameraView();
	}

void FakeEditorCamera::OnEvent(FakeEvent &e)
	{
	FakeEventDispatcher dispatcher(e);
	dispatcher.Dispatch<FakeMouseScrolledEvent>(FAKE_BIND_EVENT_FUNCTION(FakeEditorCamera::OnMouseScrolled));
	}

FakeVec3f FakeEditorCamera::GetUpDirection()
	{
	return GetOrientation() * FakeVec3f(0.0f, 1.0f, 0.0f);
	}

FakeVec3f FakeEditorCamera::GetRightDirection()
	{
	return GetOrientation() * FakeVec3f(1.0f, 0.0f, 0.0f);
	}

FakeVec3f FakeEditorCamera::GetForwardDirection()
	{
	return GetOrientation() * FakeVec3f(0.0f, 0.0f, -1.0f);
	}

FakeQuatf FakeEditorCamera::GetOrientation() const
	{
	return FakeQuatf(FakeVec3f(-Pitch, -Yaw, 0.0f));
	}

void FakeEditorCamera::UpdateCameraView()
	{
	Position = CalculatePosition();

	FakeQuatf orientation = GetOrientation();
	Rotation = orientation.GetEuler() * (180.0f / FAKE_PI);
	ViewMatrix = FakeMat4f::Translate(Position) * FakeQuatf::ToMatrix4(orientation);
	ViewMatrix.Inverse();
	}

FakeVec3f FakeEditorCamera::CalculatePosition()
	{
	return FocalPoint - GetForwardDirection() * Distance;
	}

bool FakeEditorCamera::OnMouseScrolled(const FakeMouseScrolledEvent &e)
	{
	float delta = (float)e.GetMouseY() * 0.1f;
	MouseZoom(delta);
	UpdateCameraView();
	return false;
	}

void FakeEditorCamera::MousePan(const FakeVec2f &delta)
	{
	auto [xSpeed, ySpeed] = GetPanSpeed();
	FocalPoint += -GetRightDirection() * delta.X * xSpeed * Distance;
	FocalPoint += GetUpDirection() * delta.Y * ySpeed * Distance;
	}

void FakeEditorCamera::MouseRotate(const FakeVec2f &delta)
	{
	float yawSign = GetUpDirection().Y < 0 ? -1.0f : 1.0f;
	Yaw += yawSign * delta.X * GetRotationSpeed();
	Pitch += delta.Y * GetRotationSpeed();
	}

void FakeEditorCamera::MouseZoom(float delta)
	{
	Distance -= delta * GetZoomSpeed();
	if (Distance < 1.0f)
		{
		FocalPoint += GetForwardDirection();
		Distance = 1.0f;
		}
	}

std::pair<float, float> FakeEditorCamera::GetPanSpeed() const
	{
	float x = std::min(ViewportWidth / 1000.0f, 2.4f); // max = 2.4f
	float xFactor = 0.0366f * (x * x) - 0.1778f * x + 0.3021f;

	float y = std::min(ViewportHeight / 1000.0f, 2.4f); // max = 2.4f
	float yFactor = 0.0366f * (y * y) - 0.1778f * y + 0.3021f;

	return { xFactor, yFactor };
	}

float FakeEditorCamera::GetRotationSpeed() const
	{
	return 0.8f;
	}

float FakeEditorCamera::GetZoomSpeed() const
	{
	float distance = Distance * 0.2f;
	distance = std::max(distance, 0.0f);

	float speed = distance * distance;
	speed = std::min(speed, 100.0f); // max speed = 100

	return speed;
	}
