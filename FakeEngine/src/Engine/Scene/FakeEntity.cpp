#include "FakePch.h"
#include "FakeEntity.h"

FakeEntity::FakeEntity(entt::entity handle, FakeScene *scene)
    : EntityHandle(handle), Scene(scene)
    {
    }
