/*****************************************************************
 * \file   FakeVector3.h
 * \brief
 *
 * \author Can Karka
 * \date   January 2021
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

#include "FakeMathFunctions.h"

template<typename T>
struct FakeVector2;

template<typename T>
struct FakeVector4;

template<typename T>
struct FakeMatrix4x4;

template<typename T>
struct FakeQuaternion;

template<typename T>
struct FakeVector3
	{
	union
		{
		struct
			{
			T X;
			T Y;
			T Z;
			};

		T Raw[3];
		};

	static const FakeVector3 Zero;
	static const FakeVector3 One;
	static const FakeVector3 Half;
	static const FakeVector3 UnitX;
	static const FakeVector3 UnitY;
	static const FakeVector3 UnitZ;
	static const FakeVector3 Up;
	static const FakeVector3 Down;
	static const FakeVector3 Left;
	static const FakeVector3 Right;
	static const FakeVector3 Forward;
	static const FakeVector3 Backward;
	static const FakeVector3 Minimum;
	static const FakeVector3 Maximum;

	FakeVector3()
		: X(0), Y(0), Z(0)
		{
		}

	FakeVector3(T xyz)
		: X(xyz), Y(xyz), Z(xyz)
		{
		}

	FakeVector3(T x, T y, T z)
		: X(x), Y(y), Z(z)
		{
		}

	FakeVector3(const T *xyz)
		: X(xyz[0]), Y(xyz[1]), Z(xyz[2])
		{
		}

	FakeVector3(const FakeVector2<T> &xy, T z)
		: X(xy.X), Y(xy.Y), Z(z)
		{
		}

	FakeVector3(const FakeVector2<T> &xy)
		: X(xy.X), Y(xy.Y), Z(0)
		{
		}

	FakeVector3(const FakeVector3 &other)
		: X(other.X), Y(other.Y), Z(other.Z)
		{
		}

	FakeVector3(const FakeVector4<T> &xyzw)
		: X(xyzw.X), Y(xyzw.Y), Z(xyzw.Z)
		{
		}

	FakeString ToString() const
		{
		return FakeString::ToString(X) + ", " + FakeString::ToString(Y) + ", " + FakeString::ToString(Z);
		}

	bool IsNormalized() const
		{
		return fake_is_one(X * X + Y * Y + Z * Z);
		}

	bool IsZero() const
		{
		return fake_is_zero(X) && fake_is_zero(Y) && fake_is_zero(Z);
		}

	bool IsAnyZero() const
		{
		return fake_is_zero(X) || fake_is_zero(Y) || fake_is_zero(Z);
		}

	bool IsOne() const
		{
		return fake_is_one(X) && fake_is_one(Y) && fake_is_one(Z);
		}

	bool IsAnyOne() const
		{
		return fake_is_one(X) || fake_is_one(Y) || fake_is_one(Z);
		}

	T Length() const
		{
		return fake_sqrt(X * X + Y * Y + Z * Z);
		}

	T LengthSquared() const
		{
		return X * X + Y * Y + Z * Z;
		}

	T InverseLength() const
		{
		return static_cast<T>(1) / Length();
		}

	FakeVector3 GetAbsolute() const
		{
		return FakeVector3(FAKE_ABS(X), FAKE_ABS(Y), FAKE_ABS(Z));
		}

	FakeVector3 GetNegative() const
		{
		return FakeVector3(-X, -Y, -Z);
		}

	FakeVector3 GetNormalized() const
		{
		T invLen = InverseLength();
		return FakeVector3(X * invLen, Y * invLen, Z * invLen);
		}

	static void Normalize(const FakeVector3 &value, FakeVector3 &result)
		{
		T invLen = value.InverseLength();
		result.X = value.X * invLen;
		result.Y = value.Y * invLen;
		result.Z = value.Z * invLen;
		}

	T AverageArithmetic() const
		{
		return (X + Y + Z) * static_cast<T>(0.333333334);
		}

	T Min() const
		{
		return fake_min(X, Y, Z);
		}

	T Max() const
		{
		return fake_max(X, Y, Z);
		}

	bool IsNaN() const
		{
		return isnan(X) && isnan(Y) && isnan(Z);
		}

	bool IsInfinity() const
		{
		return isinf(X) && isinf(Y) && isinf(Z);
		}

	bool IsNaNOrInfinity() const
		{
		return IsNaN() || IsInfinity();
		}

	void Normalize()
		{
		const T length = Length();
		if (!fake_is_zero(length))
			{
			const T inv = static_cast<T>(1) / length;
			X *= inv;
			Y *= inv;
			Z *= inv;
			}
		}

	void NormalizeFast()
		{
		const T inv = static_cast<T>(1) / Length();
		X *= inv;
		Y *= inv;
		Z *= inv;
		}

	void Absolute()
		{
		X = FAKE_ABS(X);
		Y = FAKE_ABS(Y);
		Z = FAKE_ABS(Z);
		}

	void Negate()
		{
		X = -X;
		Y = -Y;
		Z = -Z;
		}

	void UnwindEuler()
		{
		X = fake_unwind_degrees(X);
		Y = fake_unwind_degrees(Y);
		Z = fake_unwind_degrees(Z);
		}

	static bool NearEqual(const FakeVector3 &a, const FakeVector3 &b)
		{
		return fake_near_equal(a.X, b.X) && fake_near_equal(a.Y, b.Y) && fake_near_equal(a.Z, b.Z);
		}

	static bool NearEqual(const FakeVector3 &a, const FakeVector3 &b, T epsilon)
		{
		return fake_near_equal(a.X, b.X, epsilon) && fake_near_equal(a.Y, b.Y, epsilon) && fake_near_equal(a.Z, b.Z, epsilon);
		}

	static void Add(const FakeVector3 &a, const FakeVector3 &b, FakeVector3 &result)
		{
		result.X = a.X + b.X;
		result.Y = a.Y + b.Y;
		result.Z = a.Z + b.Z;
		}

	static void Add(const FakeVector3 &a, T b, FakeVector3 &result)
		{
		result.X = a.X + b;
		result.Y = a.Y + b;
		result.Z = a.Z + b;
		}

	static void Subtract(const FakeVector3 &a, const FakeVector3 &b, FakeVector3 &result)
		{
		result.X = a.X - b.X;
		result.Y = a.Y - b.Y;
		result.Z = a.Z - b.Z;
		}

	static void Subtract(const FakeVector3 &a, T b, FakeVector3 &result)
		{
		result.X = a.X - b;
		result.Y = a.Y - b;
		result.Z = a.Z - b;
		}

	static void Multiply(const FakeVector3 &a, const FakeVector3 &b, FakeVector3 &result)
		{
		result.X = a.X * b.X;
		result.Y = a.Y * b.Y;
		result.Z = a.Z * b.Z;
		}

	static void Multiply(const FakeVector3 &a, T b, FakeVector3 &result)
		{
		result.X = a.X * b;
		result.Y = a.Y * b;
		result.Z = a.Z * b;
		}

	static void Divide(const FakeVector3 &a, const FakeVector3 &b, FakeVector3 &result)
		{
		if (b > static_cast<T>(0))
			{
			result.X = a.X / b.X;
			result.Y = a.Y / b.Y;
			result.Z = a.Z / b.Z;
			}
		else
			{
			result.X = static_cast<T>(0);
			result.Y = static_cast<T>(0);
			result.Z = static_cast<T>(0);
			}
		}

	static void Divide(const FakeVector3 &a, T b, FakeVector3 &result)
		{
		if (b > static_cast<T>(0))
			{
			result.X = a.X / b;
			result.Y = a.Y / b;
			result.Z = a.Z / b;
			}
		else
			{
			result.X = static_cast<T>(0);
			result.Y = static_cast<T>(0);
			result.Z = static_cast<T>(0);
			}
		}

	static FakeVector3 Add(const FakeVector3 &a, const FakeVector3 &b)
		{
		FakeVector3 result;
		Add(a, b, result);
		return result;
		}

	static FakeVector3 Subtract(const FakeVector3 &a, const FakeVector3 &b)
		{
		FakeVector3 result;
		Subtract(a, b, result);
		return result;
		}

	static FakeVector3 Multiply(const FakeVector3 &a, const FakeVector3 &b)
		{
		FakeVector3 result;
		Multiply(a, b, result);
		return result;
		}

	static FakeVector3 Divide(const FakeVector3 &a, const FakeVector3 &b)
		{
		FakeVector3 result;
		Divide(a, b, result);
		return result;
		}

	static FakeVector3 Add(const FakeVector3 &a, T b)
		{
		FakeVector3 result;
		Add(a, b, result);
		return result;
		}

	static FakeVector3 Subtract(const FakeVector3 &a, T b)
		{
		FakeVector3 result;
		Subtract(a, b, result);
		return result;
		}

	static FakeVector3 Multiply(const FakeVector3 &a, T b)
		{
		FakeVector3 result;
		Multiply(a, b, result);
		return result;
		}

	static FakeVector3 Divide(const FakeVector3 &a, T b)
		{
		FakeVector3 result;
		Divide(a, b, result);
		return result;
		}

	static FakeVector3 Floor(const FakeVector3 &v)
		{
		return FakeVector3(fake_floor(v.X), fake_floor(v.Y), fake_floor(v.Z));
		}

	static FakeVector3 Round(const FakeVector3 &v)
		{
		return FakeVector3(fake_round(v.X), fake_round(v.Y), fake_round(v.Z));
		}

	static FakeVector3 Ceil(const FakeVector3 &v)
		{
		return FakeVector3(fake_ceil(v.X), fake_ceil(v.Y), fake_ceil(v.Z));
		}

	static FakeVector3 Frac(const FakeVector3 &v)
		{
		return FakeVector3(v.X - (int32) v.X, v.Y - (int32) v.Y, v.Z - (int32) v.Z);
		}

	static void Clamp(const FakeVector3 &value, const FakeVector3 &min, const FakeVector3 &max, FakeVector3 &result)
		{
		result.X = FAKE_MIN(FAKE_MAX(value.X, min.X), max.X);
		result.Y = FAKE_MIN(FAKE_MAX(value.Y, min.Y), max.Y);
		result.Z = FAKE_MIN(FAKE_MAX(value.Z, min.Z), max.Z);
		}

	static FakeVector3 Clamp(const FakeVector3 &value, const FakeVector3 &min, const FakeVector3 &max)
		{
		const T x = FAKE_MIN(FAKE_MAX(value.X, min.X), max.X);
		const T y = FAKE_MIN(FAKE_MAX(value.Y, min.Y), max.Y);
		const T z = FAKE_MIN(FAKE_MAX(value.Z, min.Z), max.Z);
		return FakeVector3(x, y, z);
		}

	static T Distance(const FakeVector3 &a, const FakeVector3 &b)
		{
		const T x = a.X - b.X;
		const T y = a.Y - b.Y;
		const T z = a.Z - b.Z;
		return fake_sqrt(x * x + y * y + z * z);
		}

	static T DistanceSquared(const FakeVector3 &a, const FakeVector3 &b)
		{
		const T x = a.X - b.X;
		const T y = a.Y - b.Y;
		const T z = a.Z - b.Z;
		return x * x + y * y + z * z;
		}

	static T ScalarProduct(const FakeVector3 &a, const FakeVector3 &b)
		{
		return a.X * b.X + a.Y * b.Y + a.Z * b.Z;
		}

	static T Dot(const FakeVector3 &a, const FakeVector3 &b)
		{
		return a.X * b.X + a.Y * b.Y + a.Z * b.Z;
		}

	static void Cross(const FakeVector3 &a, const FakeVector3 &b, FakeVector3 &result)
		{
		result.X = a.Y * b.Z - a.Z * b.Y;
		result.Y = a.Z * b.X - a.X * b.Z;
		result.Z = a.X * b.Y - a.Y * b.X;
		}

	static FakeVector3 Cross(const FakeVector3 &a, const FakeVector3 &b)
		{
		FakeVector3 result;
		Cross(a, b, result);
		return result;
		}

	static void Min(const FakeVector3 &a, const FakeVector3 &b, FakeVector3 &result)
		{
		result.X = a.X < b.X ? a.X : b.X;
		result.Y = a.Y < b.Y ? a.Y : b.Y;
		result.Z = a.Z < b.Z ? a.Z : b.Z;
		}

	static FakeVector3 Min(const FakeVector3 &a, const FakeVector3 &b)
		{
		return FakeVector3(a.X < b.X ? a.X : b.X, a.Y < b.Y ? a.Y : b.Y, a.Z < b.Z ? a.Z : b.Z);
		}

	static void Max(const FakeVector3 &a, const FakeVector3 &b, FakeVector3 &result)
		{
		result.X = a.X > b.X ? a.X : b.X;
		result.Y = a.Y > b.Y ? a.Y : b.Y;
		result.Z = a.Z > b.Z ? a.Z : b.Z;
		}

	static FakeVector3 Max(const FakeVector3 &a, const FakeVector3 &b)
		{
		return FakeVector3(a.X > b.X ? a.X : b.X, a.Y > b.Y ? a.Y : b.Y, a.Z > b.Z ? a.Z : b.Z);
		}

	static void Lerp(const FakeVector3 &start, const FakeVector3 &end, T amount, FakeVector3 &result)
		{
		result.X = fake_lerp(start.X, end.X, amount);
		result.Y = fake_lerp(start.Y, end.Y, amount);
		result.Z = fake_lerp(start.Z, end.Z, amount);
		}

	static FakeVector3 Lerp(const FakeVector3 &start, const FakeVector3 &end, T amount)
		{
		FakeVector3 result;
		Lerp(start, end, amount, result);
		return result;
		}

	static void SmoothStep(const FakeVector3 &start, const FakeVector3 &end, T amount, FakeVector3 &result)
		{
		amount = fake_smooth_step(amount);
		Lerp(start, end, amount, result);
		}

	static FakeVector3 SmoothStep(const FakeVector3 &start, const FakeVector3 &end, T amount)
		{
		FakeVector3 result;
		SmoothStep(start, end, amount, result);
		return result;
		}

	/// Hermite Spline-Interpolation
	static void Hermite(const FakeVector3 &value1, const FakeVector3 &value2, const FakeVector3 &tangent1, const FakeVector3 &tangent2, T amount, FakeVector3 &result)
		{
		const T squared = amount * amount;
		const T cubed = amount * squared;
		const T part1 = static_cast<T>(2) * cubed - static_cast<T>(3) * squared + static_cast<T>(1);
		const T part2 = static_cast<T>(-2) * cubed + static_cast<T>(3) * squared;
		const T part3 = cubed - static_cast<T>(2) * squared + amount;
		const T part4 = cubed - squared;

		result.X = value1.X * part1 + value2.X * part2 + tangent1.X * part3 + tangent2.X * part4;
		result.Y = value1.Y * part1 + value2.Y * part2 + tangent1.Y * part3 + tangent2.Y * part4;
		result.Z = value1.Z * part1 + value2.Z * part2 + tangent1.Z * part3 + tangent2.Z * part4;
		}

	/// Returns the reflection of a vector off a surface that has the specified normal
	static void Reflect(const FakeVector3 &vector, const FakeVector3 &normal, FakeVector3 &result)
		{
		const T dot = vector.X * normal.X + vector.Y * normal.Y + vector.Z * normal.Z;
		result.X = vector.X - static_cast<T>(2) * dot * normal.X;
		result.Y = vector.Y - static_cast<T>(2) * dot * normal.Y;
		result.Z = vector.Z - static_cast<T>(2) * dot * normal.Z;
		}

	/// Transforms a 3D vector by the given Quaternion rotation
	static void Transform(const FakeVector3 &vector, const FakeQuaternion<T> &rotation, FakeVector3 &result)
		{
		const T x = rotation.X + rotation.X;
		const T y = rotation.Y + rotation.Y;
		const T z = rotation.Z + rotation.Z;
		const T wx = rotation.W * x;
		const T wy = rotation.W * y;
		const T wz = rotation.W * z;
		const T xx = rotation.X * x;
		const T xy = rotation.X * y;
		const T xz = rotation.X * z;
		const T yy = rotation.Y * y;
		const T yz = rotation.Y * z;
		const T zz = rotation.Z * z;

		result.X = vector.X * (static_cast<T>(1) - yy - zz) + vector.Y * (xy - wz) + vector.Z * (xz + wy);
		result.Y = vector.X * (xy + wz) + vector.Y * (static_cast<T>(1) - xx - zz) + vector.Z * (yz - wx);
		result.Z = vector.X * (xz - wy) + vector.Y * (yz + wx) + vector.Z * (static_cast<T>(1) - xx - yy);
		}

	static FakeVector3 Transform(const FakeVector3 &vector, const FakeQuaternion<T> &rotation)
		{
		FakeVector3 result;
		Transform(vector, rotation, result);
		return result;
		}

	/// Transforms a 3D vector by the given matrix
	static void Transform(const FakeVector3 &vector, const FakeMatrix4x4<T> &transform, FakeVector3 &result)
		{
		result.X = vector.X * transform.M11 + vector.Y * transform.M21 + vector.Z * transform.M31 + transform.M41;
		result.Y = vector.X * transform.M12 + vector.Y * transform.M22 + vector.Z * transform.M32 + transform.M42;
		result.Z = vector.X * transform.M13 + vector.Y * transform.M23 + vector.Z * transform.M33 + transform.M43;
		}

	static FakeVector3 Transform(const FakeVector3 &vector, const FakeMatrix4x4<T> &transform)
		{
		FakeVector3 result;
		Transform(vector, transform, result);
		return result;
		}

	/// Transforms 3D vectors by the given matrix
	static void Transform(const FakeVector3 *vectors, const FakeMatrix4x4<T> &transform, int32 vectorsCount, FakeVector3 *results)
		{
		for (int32 i = 0; i < vectorsCount; ++i)
			{
			Transform(vectors[i], transform, results[i]);
			}
		}

	/// Performs a coordinate transformation using the given matrix
	static void TransformCoordinate(const FakeVector3 &coordinate, const FakeMatrix4x4<T> &transform, FakeVector3 &result)
		{
		FakeVector4<T> vector;
		vector.X = coordinate.X * transform.M11 + coordinate.Y * transform.M21 + coordinate.Z * transform.M31 + transform.M41;
		vector.Y = coordinate.X * transform.M12 + coordinate.Y * transform.M22 + coordinate.Z * transform.M32 + transform.M42;
		vector.Z = coordinate.X * transform.M13 + coordinate.Y * transform.M23 + coordinate.Z * transform.M33 + transform.M43;
		vector.W = static_cast<T>(1) / (coordinate.X * transform.M14 + coordinate.Y * transform.M24 + coordinate.Z * transform.M34 + transform.M44);

		result.X = vector.X * vector.W;
		result.Y = vector.Y * vector.W;
		result.Z = vector.Z * vector.W;
		}

	/// Performs a normal transformation using the given matrix
	static void TransformNormal(const FakeVector3 &normal, const FakeMatrix4x4<T> &transform, FakeVector3 &result)
		{
		result.X = normal.X * transform.M11 + normal.Y * transform.M21 + normal.Z * transform.M31;
		result.Y = normal.X * transform.M12 + normal.Y * transform.M22 + normal.Z * transform.M32;
		result.Z = normal.X * transform.M13 + normal.Y * transform.M23 + normal.Z * transform.M33;
		}

	/// Projects a vector onto another vector.
	static FakeVector3 Project(const FakeVector3 &vector, const FakeVector3 &onNormal)
		{
		const T sqrMag = Dot(onNormal, onNormal);
		if (sqrMag < FAKE_ZERO_TOLERANCE)
			return Zero;

		return onNormal * Dot(vector, onNormal) / sqrMag;
		}

	/// Projects a vector onto a plane defined by a normal orthogonal to the plane.
	static FakeVector3 ProjectOnPlane(const FakeVector3 &vector, const FakeVector3 &planeNormal)
		{
		return vector - Project(vector, planeNormal);
		}

	/// Projects a 3D vector from object space into screen space
	static void Project(const FakeVector3 &vector, T x, T y, T width, T height, T minZ, T maxZ, const FakeMatrix4x4<T> &worldViewProjection, FakeVector3 &result)
		{
		FakeVector3 v;
		TransformCoordinate(vector, worldViewProjection, v);

		result.X = (static_cast<T>(1) + v.X) * static_cast<T>(0.5) * width + x;
		result.Y = (static_cast<T>(1) - v.Y) * static_cast<T>(0.5) * height + y;
		result.Z = v.Z * (maxZ - minZ) + minZ;
		}

	static FakeVector3 Project(const FakeVector3 &vector, T x, T y, T width, T height, T minZ, T maxZ, const FakeMatrix4x4<T> &worldViewProjection)
		{
		FakeVector3 result;
		Project(vector, x, y, width, height, minZ, maxZ, worldViewProjection, result);
		return result;
		}

	/// Projects a 3D vector from screen space into object space
	static void Unproject(const FakeVector3 &vector, T x, T y, T width, T height, T minZ, T maxZ, const FakeMatrix4x4<T> &worldViewProjection, FakeVector3 &result)
		{
		FakeMatrix4x4<T> matrix;
		FakeMatrix4x4::Invert(worldViewProjection, matrix);

		const FakeVector3 v = FakeVector3(
				(vector.X - x) / width * static_cast<T>(2) - static_cast<T>(1),
			-((vector.Y - y) / height * static_cast<T>(2) - static_cast<T>(1)),
				(vector.Z - minZ) / (maxZ - minZ));

		TransformCoordinate(v, matrix, result);
		}

	static FakeVector3 Unproject(const FakeVector3 &vector, T x, T y, T width, T height, T minZ, T maxZ, const FakeMatrix4x4<T> &worldViewProjection)
		{
		FakeVector3 result;
		Unproject(vector, x, y, width, height, minZ, maxZ, worldViewProjection, result);
		return result;
		}

	/// Creates an orthonormal basis from a basis with at least two orthogonal vectors.
	static void CreateOrthoNormalBasis(FakeVector3 &xAxis, FakeVector3 &yAxis, FakeVector3 &zAxis)
		{
		xAxis -= (xAxis | zAxis) / (zAxis | zAxis) * zAxis;
		yAxis -= (yAxis | zAxis) / (zAxis | zAxis) * zAxis;

		if (xAxis.LengthSquared() < FAKE_ZERO_TOLERANCE)
			xAxis = yAxis ^ zAxis;
		if (yAxis.LengthSquared() < FAKE_ZERO_TOLERANCE)
			yAxis = xAxis ^ zAxis;

		xAxis.Normalize();
		yAxis.Normalize();
		zAxis.Normalize();
		}

	/// Finds the best arbitrary axis vectors to represent U and V axes of a plane, by using this vector as the normal of the plane.
	void FindBestAxisVectors(FakeVector3 &firstAxis, FakeVector3 &secondAxis) const
		{
		const T absX = FAKE_ABS(X);
		const T absY = FAKE_ABS(Y);
		const T absZ = FAKE_ABS(Z);

		if (absZ > absX && absZ > absY)
			firstAxis = FakeVector3(1, 0, 0);
		else
			firstAxis = FakeVector3(0, 0, 1);

		firstAxis = (firstAxis - *this * (firstAxis | *this)).GetNormalized();
		secondAxis = firstAxis ^ *this;
		}

	/// Calculates the area of the triangle.
	static T TriangleArea(const FakeVector3 &v0, const FakeVector3 &v1, const FakeVector3 &v2)
		{
		return (v2 - v0 ^ v1 - v0).Length() * static_cast<T>(0.5);
		}

	bool operator==(const FakeVector3 &other) const
		{
		return X == other.X && Y == other.Y && Z == other.Z;
		}

	bool operator!=(const FakeVector3 &other) const
		{
		return !(*this == other);
		}

	bool operator<(const FakeVector3 &other) const
		{
		return X < other.X &&Y < other.Y &&Z < other.Z;
		}

	bool operator<=(const FakeVector3 &other) const
		{
		return X <= other.X && Y <= other.Y && Z <= other.Z;
		}

	bool operator>(const FakeVector3 &other) const
		{
		return X > other.X && Y > other.Y && Z > other.Z;
		}

	bool operator>=(const FakeVector3 &other) const
		{
		return X >= other.X && Y >= other.Y && Z >= other.Z;
		}

	bool operator==(T value) const
		{
		return X == value && Y == value && Z == value;
		}

	bool operator!=(T value) const
		{
		return !(*this == value);
		}

	bool operator<(T value) const
		{
		return X < value &&Y < value &&Z < value;
		}

	bool operator<=(T value) const
		{
		return X <= value && Y <= value && Z <= value;
		}

	bool operator>(T value) const
		{
		return X > value && Y > value && Z > value;
		}

	bool operator>=(T value) const
		{
		return X >= value && Y >= value && Z >= value;
		}

	FakeVector3 operator-() const
		{
		return FakeVector3(-X, -Y, -Z);
		}

	T operator^(const FakeVector3 &other) const
		{
		return Cross(*this, other);
		}

	T operator|(const FakeVector3 &other) const
		{
		return Dot(*this, other);
		}

	FakeVector3 operator+(const FakeVector3 &other) const
		{
		return Add(*this, other);
		}

	FakeVector3 operator-(const FakeVector3 &other) const
		{
		return Subtract(*this, other);
		}

	FakeVector3 operator*(const FakeVector3 &other) const
		{
		return Multiply(*this, other);
		}

	FakeVector3 operator/(const FakeVector3 &other) const
		{
		return Divide(*this, other);
		}

	FakeVector3 &operator+=(const FakeVector3 &other)
		{
		*this = Add(*this, other);
		return *this;
		}

	FakeVector3 &operator-=(const FakeVector3 &other)
		{
		*this = Subtract(*this, other);
		return *this;
		}

	FakeVector3 &operator*=(const FakeVector3 &other)
		{
		*this = Multiply(*this, other);
		return *this;
		}

	FakeVector3 &operator/=(const FakeVector3 &other)
		{
		*this = Divide(*this, other);
		return *this;
		}

	FakeVector3 operator+(T scalar) const
		{
		return Add(*this, scalar);
		}

	FakeVector3 operator-(T scalar) const
		{
		return Subtract(*this, scalar);
		}

	FakeVector3 operator*(T scalar) const
		{
		return Multiply(*this, scalar);
		}

	FakeVector3 operator/(T scalar) const
		{
		return Divide(*this, scalar);
		}

	FakeVector3 &operator+=(T scalar)
		{
		*this = Add(*this, scalar);
		return *this;
		}

	FakeVector3 &operator-=(T scalar)
		{
		*this = Subtract(*this, scalar);
		return *this;
		}

	FakeVector3 &operator*=(T scalar)
		{
		*this = Multiply(*this, scalar);
		return *this;
		}

	FakeVector3 &operator/=(T scalar)
		{
		*this = Divide(*this, scalar);
		return *this;
		}

	FakeVector3 &operator++(int)
		{
		++X;
		++Y;
		++Z;
		return *this;
		}

	FakeVector3 &operator--(int)
		{
		--X;
		--Y;
		--Z;
		return *this;
		}

	FakeVector3 &operator=(const FakeVector3 &other)
		{
		X = other.X;
		Y = other.Y;
		Z = other.Z;
		return *this;
		}

	T *operator*()
		{
		return Raw;
		}

	const T *operator*() const
		{
		return Raw;
		}

	T &operator[](uint32 index)
		{
		return *((T *) this + index);
		}

	const T &operator[](uint32 index) const
		{
		return *((T *) this + index);
		}

	friend std::ostream &operator<<(std::ostream &stream, const FakeVector3 &v)
		{
		stream << v.X << ", " << v.Y << ", " << v.Z;
		return stream;
		}
	};

template<typename T>
const FakeVector3<T> FakeVector3<T>::Zero(static_cast<T>(0));

template<typename T>
const FakeVector3<T> FakeVector3<T>::One(static_cast<T>(1));

template<typename T>
const FakeVector3<T> FakeVector3<T>::Half(static_cast<T>(0.5));

template<typename T>
const FakeVector3<T> FakeVector3<T>::UnitX(static_cast<T>(1), static_cast<T>(0), static_cast<T>(0));

template<typename T>
const FakeVector3<T> FakeVector3<T>::UnitY(static_cast<T>(0), static_cast<T>(1), static_cast<T>(0));

template<typename T>
const FakeVector3<T> FakeVector3<T>::UnitZ(static_cast<T>(0), static_cast<T>(0), static_cast<T>(1));

template<typename T>
const FakeVector3<T> FakeVector3<T>::Up(static_cast<T>(0), static_cast<T>(1), static_cast<T>(0));

template<typename T>
const FakeVector3<T> FakeVector3<T>::Down(static_cast<T>(0), static_cast<T>(-1), static_cast<T>(0));

template<typename T>
const FakeVector3<T> FakeVector3<T>::Left(static_cast<T>(-1), static_cast<T>(0), static_cast<T>(0));

template<typename T>
const FakeVector3<T> FakeVector3<T>::Right(static_cast<T>(1), static_cast<T>(0), static_cast<T>(0));

template<typename T>
const FakeVector3<T> FakeVector3<T>::Forward(static_cast<T>(0), static_cast<T>(0), static_cast<T>(1));

template<typename T>
const FakeVector3<T> FakeVector3<T>::Backward(static_cast<T>(0), static_cast<T>(0), static_cast<T>(-1));

template<typename T>
const FakeVector3<T> FakeVector3<T>::Minimum(fake_min<T>());

template<typename T>
const FakeVector3<T> FakeVector3<T>::Maximum(fake_max<T>());

template<typename T>
inline FakeVector3<T> operator+(T scalar, const FakeVector3<T> &v)
	{
	return v + scalar;
	}

template<typename T>
inline FakeVector3<T> operator-(T scalar, const FakeVector3<T> &v)
	{
	return FakeVector3<T>(scalar) - v;
	}

template<typename T>
inline FakeVector3<T> operator*(T scalar, const FakeVector3<T> &v)
	{
	return v * scalar;
	}

template<typename T>
inline FakeVector3<T> operator/(T scalar, const FakeVector3<T> &v)
	{
	return FakeVector3<T>(scalar) / v;
	}

typedef FakeVector3<double> FakeVec3d;
typedef FakeVector3<float> FakeVec3f;
typedef FakeVector3<int32> FakeVec3i;
typedef FakeVector3<short> FakeVec3s;
typedef FakeVector3<long> FakeVec3l;
typedef FakeVector3<bool> FakeVec3b;

