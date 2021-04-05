/*****************************************************************
 * \file   FakeScene.h
 * \brief  
 * 
 * \author Can Karka
 * \date   February 2021
 * 
 * Copyright (C) 2021 Can Karka
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *  https://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *********************************************************************/

#pragma once

#include <entt/entt.hpp>
#include "Engine/Core/FakeTimeStep.h"
#include "FakeCamera.h"

class FakeEntity;

/**
 * 
 * .
 * 
 */
class FAKE_API FakeScene
	{
	private:
		entt::registry Registry;
		uint32 ViewportWidth = 0;
		uint32 ViewportHeight = 0;

		friend class FakeEntity;

		template<typename T>
		void OnComponentAdded(FakeEntity entity, T &component);

	public:

		FakeScene();
		FakeScene(uint32 width, uint32 height);
		~FakeScene();

		FakeEntity CreateEntity(const FakeString &name = "");
		void DestroyEntity(FakeEntity entity);

		void OnRenderRuntime(FakeTimeStep ts);
		void OnRenderEditor(FakeTimeStep ts);
		void OnRenderEditor(FakeTimeStep ts, FakeCamera &camera);
		void OnViewportResize(uint32 width, uint32 height);

		FakeEntity GetPrimaryCameraEntity();
		FakeCamera &GetPrimaryCamera();
	};
