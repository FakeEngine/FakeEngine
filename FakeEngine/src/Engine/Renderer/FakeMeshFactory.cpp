#include "FakePch.h"
#include "FakeMeshFactory.h"

FakeRef<FakeMesh> FakeMeshFactory::Cube(const FakeVec3f &size)
	{
	return FakeRef<FakeMesh>();
	}

FakeRef<FakeMesh> FakeMeshFactory::Sphere(float radius)
	{
	return FakeRef<FakeMesh>();
	}

FakeRef<FakeMesh> FakeMeshFactory::Capsule(float radius, float height)
	{
	return FakeRef<FakeMesh>();
	}
