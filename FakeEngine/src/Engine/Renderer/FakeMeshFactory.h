/*****************************************************************
 * \file   FakeMeshFactory.h
 * \brief  
 * 
 * \author Can Karka
 * \date   February 2021
 * 
 * 
 *********************************************************************/

#pragma once

#include "Engine/Core/Maths/FakeMaths.h"
#include "Engine/Renderer/FakeMesh.h"

/**
 * 
 * .
 * 
 */
class FAKE_API FakeMeshFactory
	{
	public:

		/**
		 * 
		 * .
		 * 
		 * @param size
		 * @return 
		 */
		static FakeRef<FakeMesh> Cube(const FakeVec3f &size);

		/**
		 * 
		 * .
		 * 
		 * @param radius
		 * @return 
		 */
		static FakeRef<FakeMesh> Sphere(float radius);

		/**
		 * 
		 * .
		 * 
		 * @param radius
		 * @param height
		 * @return 
		 */
		static FakeRef<FakeMesh> Capsule(float radius, float height);
	};
