/*****************************************************************
 * \file   FakeEntity.h
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
#include "FakeScene.h"

/**
 * 
 * .
 * 
 */
class FakeEntity
	{
	private:
		FakeScene *Scene = nullptr;
		entt::entity EntityHandle{ entt::null };

	public:

		FakeEntity() = default;
		FakeEntity(entt::entity handle, FakeScene *scene);
		FakeEntity(const FakeEntity&) = default;

		template<typename T, typename... Args>
		T &AddComponent(Args&&... args)
			{
			FAKE_ASSERT(!HasComponent<T>());
			T &component = Scene->Registry.emplace<T>(EntityHandle, std::forward<Args>(args)...);
			Scene->OnComponentAdded<T>(*this, component);
			return component;
			}

		template<typename T>
		T &GetComponent()
			{
			FAKE_ASSERT(HasComponent<T>());
			return Scene->Registry.get<T>(EntityHandle);
			}

		template<typename T>
		bool HasComponent()
			{
			return Scene->Registry.has<T>(EntityHandle);
			}

		template<typename T>
		void RemoveComponent()
			{
			FAKE_ASSERT(HasComponent<T>());
			Scene->Registry.remove<T>(EntityHandle);
			}

		operator bool() const
			{
			return EntityHandle != entt::null;
			}

		operator entt::entity() const
			{
			return EntityHandle;
			}

		operator uint32() const
			{
			return (uint32)EntityHandle;
			}

		bool operator==(const FakeEntity &other) const
			{
			return EntityHandle == other.EntityHandle && Scene == other.Scene;
			}

		bool operator!=(const FakeEntity &other) const
			{
			return !(*this == other);
			}
	};
