#include "FakePch.h"
#include "FakeMathFunctions.h"

#include "Engine/Core/Maths/FakeVector3.h"

/**
 *
 * Rotates position about the given axis by the given angle, in radians, and returns the offset to position.
 *
 * @param normalizedRotationAxis
 * @param angle
 * @param positionOnAxis
 * @param position
 * @return
 */
static FakeVec3f fake_rotate_about_axis(const FakeVec3f &normalizedRotationAxis, float angle, const FakeVec3f &positionOnAxis, const FakeVec3f &position)
	{
	// Project position onto the rotation axis and find the closest point on the axis to Position
	const FakeVec3f closestPointOnAxis = positionOnAxis + normalizedRotationAxis * FakeVec3f::Dot(normalizedRotationAxis, position - positionOnAxis);

	// Construct orthogonal axes in the plane of the rotation
	const FakeVec3f axisU = position - closestPointOnAxis;
	const FakeVec3f axisV = FakeVec3f::Cross(normalizedRotationAxis, axisU);

	float sinAngle, cosAngle;
	fake_sin_cos(angle, sinAngle, cosAngle);

	// Rotate using the orthogonal axes
	const FakeVec3f rotation = axisU * cosAngle + axisV * sinAngle;

	// Reconstruct the rotated world space position
	const FakeVec3f rotatedPosition = closestPointOnAxis + rotation;

	// Convert from position to a position offset
	return rotatedPosition - position;
	}

/**
 *
 * .
 *
 * @param v
 * @return
 */
static FakeVec3f fake_extract_larges_component(const FakeVec3f &v)
	{
	FakeVec3f a(0.0f);
	a.X = FAKE_ABS(v.X);
	a.Y = FAKE_ABS(v.Y);
	a.Z = FAKE_ABS(v.Z);

	if (a.X > a.Y)
		{
		if (a.X > a.Z)
			{
			return FakeVec3f(v.X > 0.0f ? 1.0f : -1.0f, 0.0f, 0.0f);
			}
		}
	else
		{
		if (a.Y > a.Z)
			{
			return FakeVec3f(0.0f, v.Y > 0.0f ? 1.0f : -1.0f, 0.0f);
			}
		}

	return FakeVec3f(0.0f, 0.0f, v.Z > 0.0f ? 1.0f : -1.0f);
	}
