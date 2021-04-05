#include "FakePch.h"
#include "FakeScene.h"

#include "FakeEntity.h"
#include "Components/FakeComponents.h"

FakeScene::FakeScene()
	{
	}

FakeScene::FakeScene(uint32 width, uint32 height)
	: ViewportWidth(width), ViewportHeight(height)
	{
	}

FakeScene::~FakeScene()
	{
	}

FakeEntity FakeScene::CreateEntity(const FakeString &name)
	{
	FakeEntity entity = { Registry.create(), this };
	entity.AddComponent<FakeTransformComponent>();
	auto &tag = entity.AddComponent<FakeTagComponent>();
	tag.Tag = name.IsEmpty() ? "Entity" : name;
	return entity;
	}

void FakeScene::DestroyEntity(FakeEntity entity)
	{
	Registry.destroy(entity);
	}

void FakeScene::OnRenderRuntime(FakeTimeStep ts)
	{
	// TODO:
	// - Update scripts
	// - Update physics
	// - Get Camera instance and it's transform
	// - Render 2D
	// - 
	}

void FakeScene::OnRenderEditor(FakeTimeStep ts)
	{
	OnRenderEditor(ts, GetPrimaryCamera());
	}

void FakeScene::OnRenderEditor(FakeTimeStep ts, FakeCamera &camera)
	{
	// TODO:
	// - Update Physics
	// - Render 2D
	// - 
	}

void FakeScene::OnViewportResize(uint32 width, uint32 height)
	{
	ViewportWidth = width;
	ViewportHeight = height;

	auto view = Registry.view<FakeCameraComponent>();
	for (auto entity : view)
		{
		auto &cameraComponent = view.get<FakeCameraComponent>(entity);
		if (!cameraComponent.FixedAspectRatio)
			{
			cameraComponent.Camera.SetViewport(width, height);
			}
		}
	}

FakeEntity FakeScene::GetPrimaryCameraEntity()
	{
	auto view = Registry.view<FakeCameraComponent>();
	for (auto entity : view)
		{
		const auto &camera = view.get<FakeCameraComponent>(entity);
		if (camera.Primary)
			{
			return FakeEntity{entity, this};
			}
		}

	return {};
	}

FakeCamera &FakeScene::GetPrimaryCamera()
	{
	return GetPrimaryCameraEntity().GetComponent<FakeCameraComponent>().Camera;
	}

template<typename T>
void FakeScene::OnComponentAdded(FakeEntity entity, T &component)
	{
	}

template<>
void FakeScene::OnComponentAdded(FakeEntity entity, FakeTagComponent &component)
	{
	}

template<>
void FakeScene::OnComponentAdded(FakeEntity entity, FakeTransformComponent &component)
	{
	}

template<>
void FakeScene::OnComponentAdded(FakeEntity entity, FakeCameraComponent &component)
	{
	component.Camera.SetViewport(ViewportWidth, ViewportHeight);
	}

template<>
void FakeScene::OnComponentAdded(FakeEntity entity, FakeSpriteComponent &component)
	{
	}

