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

#include "Engine/Core/Maths/FakeMathFunctions.h"

template<typename T>
struct FakeVector2;

template<typename T>
struct FakeVector4;

template<typename T>
struct FakeMatrix4x4;

template<typename T>
struct FakeQuaternion;

/**
 * 
 * Represents a three dimensional mathematical vector.
 * 
 */
template<typename T>
struct FAKE_API FakeVector3
	{

	union
		{
		struct
			{
			/**
			 * 
			 * The X component.
			 * 
			 */
			T X;

			/**
			 * 
			 * The Y component.
			 * 
			 */
			T Y;

			/**
			 * 
			 * The Z component.
			 * 
			 */
			T Z;
			};

		// Raw Values
		T Raw[3];
		};


	// Vector with all components equal zero (0, 0, 0)
	static const FakeVector3 Zero;
		
	// Vector with all components equal one (1, 1, 1)
	static const FakeVector3 One;
		
	// Vector with all components equal half (0.5, 0.5, 0.5)
	static const FakeVector3 Half;
		
	// The X unit vector (1, 0, 0)
	static const FakeVector3 UnitX;
		
	// The Y unit vector (0, 1, 0)
	static const FakeVector3 UnitY;
		
	// The Z unit vector (0, 0, 1)
	static const FakeVector3 UnitZ;
		
	// A unit vector designating up (0, 1, 0)
	static const FakeVector3 Up;
		
	// A unit vector designating down (0, -1, 0)
	static const FakeVector3 Down;
		
	// A unit vector designating a (-1, 0, 0)
	static const FakeVector3 Left;
		
	// A unit vector designating b (1, 0, 0)
	static const FakeVector3 Right;
		
	// A unit vector designating forward in a a-handed coordinate system (0, 0, 1)
	static const FakeVector3 Forward;
		
	// A unit vector designating backward in a a-handed coordinate system (0, 0, -1)
	static const FakeVector3 Backward;
		
	// A minimum Vector3
	static const FakeVector3 Minimum;
		
	// A maximum Vector3
	static const FakeVector3 Maximum;


	/**
	 * 
	 * Empty constructor.
	 * 
	 */
	FakeVector3()
		{
		}

	/**
	 * 
	 * constructor.
	 * 
	 * @param xyz Value to assign to the all components.
	 */
	FakeVector3(T xyz)
		: X(xyz), Y(xyz), Z(xyz)
		{
		}

	/**
	 * 
	 * constructor.
	 * 
	 * @param x X component value.
	 * @param y Y component value.
	 * @param z Z component value.
	 */
	FakeVector3(T x, T y, T z)
		: X(x), Y(y), Z(z)
		{
		}

	/**
	 * 
	 * constructor.
	 * 
	 * @param xyz X, Y and Z components in an array.
	 */
	FakeVector3(const T *xyz)
		: X(xyz[0]), Y(xyz[1]), Z(xyz[2])
		{
		}

	/**
	 * 
	 * constructor.
	 * 
	 * @param xy Vector2 with X and Y components values.
	 * @param z Z component value.
	 */
	FakeVector3(const FakeVector2<T> &xy, T z)
		: X(xy.X), Y(xy.Y), Z(z)
		{
		}

	/**
	 * 
	 * constructor.
	 * 
	 * @param xy Vector2 value.
	 */
	FakeVector3(const FakeVector2<T> &xy)
		: X(xy.X), Y(xy.Y), Z(0)
		{
		}

	/**
	 * 
	 * copy constructor.
	 * 
	 * @param xyz Vector3 value.
	 */
	FakeVector3(const FakeVector3 &xyz)
		: X(xyz.X), Y(xyz.Y), Z(xyz.Z)
		{
		}

	/**
	 * 
	 * constructor.
	 * 
	 * @param xyzw Vector4 value.
	 */
	FakeVector3(const FakeVector4<T> &xyzw)
		: X(xyzw.X), Y(xyzw.Y), Z(xyzw.Z)
		{
		}

	/**
	 * 
	 * Converts the vector to a String.
	 * 
	 * @return Returns the vector as a String.
	 */
	FakeString ToString()
		{
		return "Vector3(" + FakeString::ToString(X) + ", " + FakeString::ToString(Y) + ", " + FakeString::ToString(Z) + ")";
		}

	/**
	 * 
	 * Gets a value indicating whether this instance is normalized.
	 * 
	 * @return Returns true if the instance is normalized.
	 */
	bool IsNormalized() const
		{
		return fake_is_one(X * X + Y * Y + Z * Z);
		}

	/**
	 * 
	 * Gets a value indicating whether this vector is zero.
	 * 
	 * @return Returns true if all elements of the instance are zero.
	 */
	bool IsZero() const
		{
		return fake_is_zero(X) && fake_is_zero(Y) && fake_is_zero(Z);
		}

	/**
	 * 
	 * Gets a value indicating whether any vector component is zero.
	 * 
	 * @return Returns true if any element of the instance is zero.
	 */
	bool IsAnyZero() const
		{
		return fake_is_zero(X) || fake_is_zero(Y) || fake_is_zero(Z);
		}

	/**
	 * 
	 * Gets a value indicating whether this vector is one.
	 * 
	 * @return Returns true if all elements of the instance is one.
	 */
	bool IsOne() const
		{
		return fake_is_one(X) && fake_is_one(Y) && fake_is_one(Z);
		}

	/**
	 * 
	 * Calculates length of the vector.
	 * 
	 * @return Returns the length of the vector.
	 */
	T Length() const
		{
		return fake_sqrt(X * X + Y * Y + Z * Z);
		}

	/**
	 * 
	 * Calculates the squared length of the vector.
	 * 
	 * @return Returns the squared length of the vector.
	 */
	T LengthSquared() const
		{
		return X * X + Y * Y + Z * Z;
		}

	/**
	 * 
	 * Calculates inverted length of the vector (1 / Length()).
	 * 
	 * @return Returns the inverted length of the vector.
	 */
	T InvLength() const
		{
		return static_cast<T>(1) / Length();
		}

	/**
	 * 
	 * Returns a new vector with only positive elements.
	 * 
	 * @return Returns a new vector with only positive elements.
	 */
	FakeVector3 GetAbsolute() const
		{
		return FakeVector3(FAKE_ABS(X), FAKE_ABS(Y), FAKE_ABS(Z));
		}

	/**
	 * 
	 * Returns a new vector with inverted elements.
	 * 
	 * @return Returns a new vector with inverted elements.
	 */
	FakeVector3 GetNegative() const
		{
		return FakeVector3(-X, -Y, -Z);
		}

	/**
	 * 
	 * Returns a new vector with normalized elements.
	 * 
	 * @return Returns a new vector with normalized elements.
	 */
	FakeVector3 GetNormalized() const
		{
		T invLen = InvLength();
		return FakeVector3(X * invLen, Y * invLen, Z * invLen);
		}

	/**
	 * 
	 * .
	 * 
	 * @param value
	 * @param result
	 */
	static void Normalize(const FakeVector3 &value, FakeVector3 &result)
		{
		T invLen = value.InvLength();
		result.X = value.X * invLen;
		result.Y = value.Y * invLen;
		result.Z = value.Z * invLen;
		}

	/**
	 * 
	 * Returns the average arithmetic of the vector.
	 * 
	 * @return Returns the average arithmetic of the vector.
	 */
	T AverageArithmetic() const
		{
		return (X + Y + Z) * static_cast<T>(0.333333334);
		}

	/**
	 * 
	 * Returns minimum value of all the components.
	 * 
	 * @return Returns Minimum value.
	 */
	T Min() const
		{
		return fake_min(X, Y, Z);
		}

	/**
	 * Returns maximum value of all the components.
	 * 
	 * @return Returns Maximum value.
	 */
	T Max() const
		{
		return fake_max(X, Y, Z);
		}

	/**
	 * 
	 * Returns true if the elements of the vector are Not a Number.
	 * 
	 * @return Returns true if the elements of the vector are Not a Number.
	 */
	bool IsNaN() const
		{
		return isnan(X) && isnan(Y) && isnan(Z);
		}

	/**
	 * 
	 * Returns true if the elements of the vector are infinite.
	 * 
	 * @return Returns true if the elements of the vector are infinite.
	 */
	bool IsInfinity() const
		{
		return isinf(X) && isinf(Y) && isinf(Z);
		}

	/**
	 * 
	 * Returns true if the elements of the vector are NaN or inifinite.
	 * 
	 * @return Returns true if either IsNaN or IsInfinity is true.
	 */
	bool IsNaNOrInfinity() const
		{
		return IsNaN() || IsInfinity();
		}

	/**
	 * 
	 * Performs vector normalization (scales vector up to unit length).
	 * 
	 */
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

	/**
	 * 
	 * Performs fast vector normalization (scales vector up to unit length).
	 * 
	 */
	void NormalizeFast()
		{
		const T inv = static_cast<T>(1) / Length();
		X *= inv;
		Y *= inv;
		Z *= inv;
		}

	/**
	 * 
	 * Sets all vector components to the absolute values.
	 * 
	 */
	void Absolute()
		{
		X = FAKE_ABS(X);
		Y = FAKE_ABS(Y);
		Z = FAKE_ABS(Z);
		}

	/**
	 * 
	 * Negates all components of that vector.
	 * 
	 */
	void Negate()
		{
		X = -X;
		Y = -Y;
		Z = -Z;
		}

	/**
	 * 
	 * When this vector contains Euler angles (degrees), ensure that angles are between +/-180.
	 * 
	 */
	void UnwindEuler()
		{
		X = fake_unwind_degrees(X);
		Y = fake_unwind_degrees(Y);
		Z = fake_unwind_degrees(Z);
		}

	/**
	 * 
	 * Returns true if the elements of the vectors are near or equal to each other.
	 * 
	 * @param x The first vector to compare with.
	 * @param y The second vector to compare to.
	 * @return Returns true if the elements of the vectors are near or equal to each other.
	 */
	static bool NearEqual(const FakeVector3 &x, const FakeVector3 &y)
		{
		return fake_near_equal(a.X, b.X) && fake_near_equal(a.Y, b.Y) && fake_near_equal(a.Z, b.Z);
		}

	/**
	 * 
	 * Returns true if the elements of the vectors are near or equal to each other (using the provided epsilon).
	 * 
	 * @param x The first vector to compare with.
	 * @param y The second vector to compare to.
	 * @param epsilon The epsilon that should be used.
	 * @return Returns true if the elements of the vectors are near or equal to each other (using the provided epsilon).
	 */
	static bool NearEqual(const FakeVector3 &x, const FakeVector3 &y, T epsilon)
		{
		return fake_near_equal(a.X, b.X, epsilon) && fake_near_equal(a.Y, b.Y, epsilon) && fake_near_equal(a.Z, b.Z, epsilon);
		}

	/**
	 * 
	 * Adds the provided vectors in C-Style.
	 * 
	 * @param x The first vector that should be added.
	 * @param y The second vector that should be added.
	 * @param result The result where the addition is stored in.
	 */
	static void Add(const FakeVector3 &x, const FakeVector3 &y, FakeVector3 &result)
		{
		result.X = x.X + y.X;
		result.Y = x.Y + y.Y;
		result.Z = x.Z + y.Z;
		}

	/**
	 * 
	 * Adds the provided vector with a scalar in C-Style.
	 * 
	 * @param x The vector that should be added.
	 * @param scalar The scalar that should be added.
	 * @param result The result where the addition is stored in.
	 */
	static void Add(const FakeVector3 &x, T scalar, FakeVector3 &result)
		{
		result.X = x.X + scalar;
		result.Y = x.Y + scalar;
		result.Z = x.Z + scalar;
		}

	/**
	 * 
	 * Subtracts the provided vectors in C-Style.
	 * 
	 * @param x The first vector that should be subtracted.
	 * @param y The second vector that should be subtracted.
	 * @param result The result where the subtraction is stored in.
	 */
	static void Subtract(const FakeVector3 &x, const FakeVector3 &y, FakeVector3 &result)
		{
		result.X = x.X - y.X;
		result.Y = x.Y - y.Y;
		result.Z = x.Z - y.Z;
		}

	/**
	 * 
	 * Subtracts the provided vector with a scalar in C-Style.
	 * 
	 * @param x The vector that should be subtracted.
	 * @param scalar The scalar that should be subtracted.
	 * @param result The result where the subtraction is stored in.
	 */
	static void Subtract(const FakeVector3 &x, T scalar, FakeVector3 &result)
		{
		result.X = x.X - scalar;
		result.Y = x.Y - scalar;
		result.Z = x.Z - scalar;
		}

	/**
	 * 
	 * Multiplies the provided vectors in C-Style.
	 * 
	 * @param x The first vector that should be multiplied.
	 * @param y The second vector that should be multiplied.
	 * @param result The result where the multiplication is stored in.
	 */
	static void Multiply(const FakeVector3 &x, const FakeVector3 &y, FakeVector3 &result)
		{
		result.X = x.X * y.X;
		result.Y = x.Y * y.Y;
		result.Z = x.Z * y.Z;
		}

	/**
	 * 
	 * Multiplies the provided vector with the scalar in C-Style.
	 * 
	 * @param x The vector that should be multiplied.
	 * @param scalar The scalar that should be multiplied.
	 * @param result The result where the multiplication is stored in.
	 */
	static void Multiply(const FakeVector3 &x, T scalar, FakeVector3 &result)
		{
		result.X = x.X * scalar;
		result.Y = x.Y * scalar;
		result.Z = x.Z * scalar;
		}

	/**
	 * 
	 * Divides the provided vectors in C-Style. If the divisor is less than or equal to 0 the result will be 0.
	 * 
	 * @param x The first vector that should be divided.
	 * @param y The second vector that should be divided.
	 * @param result The result where the division is stored in.
	 */
	static void Divide(const FakeVector3 &x, const FakeVector3 &y, FakeVector3 &result)
		{
		if (y.X > static_cast<T>(0) && y.Y > static_cast<T>(0) && y.Z > static_cast<T>(0))
			{
			result.X = x.X / y.X;
			result.Y = x.Y / y.Y;
			result.Z = x.Z / y.Z;
			}
		else
			{
			result.X = static_cast<T>(0);
			result.Y = static_cast<T>(0);
			result.Z = static_cast<T>(0);
			}
		}

	/**
	 * 
	 * Divides the provided vector and scalar in C-Style. If the divisor is less than or equal to 0 the result will be 0.
	 * 
	 * @param x The vector that should be divided.
	 * @param scalar The scalar that should be divided.
	 * @param result The result where the division is stored in.
	 */
	static void Divide(const FakeVector3 &x, T scalar, FakeVector3 &result)
		{
		if (scalar > static_cast<T>(0))
			{
			result.X = x.X / scalar;
			result.Y = x.Y / scalar;
			result.Z = x.Z / scalar;
			}
		else
			{
			result.X = static_cast<T>(0);
			result.Y = static_cast<T>(0);
			result.Z = static_cast<T>(0);
			}
		}

	/**
	 * 
	 * Adds the provided vectors.
	 * 
	 * @param x The first vector that should be added.
	 * @param y The second vector that should be added.
	 * @return Returns a new vector containing the result of the addition.
	 */
	static FakeVector3 Add(const FakeVector3 &x, const FakeVector3 &y)
		{
		FakeVector3 result;
		Add(x, y, result);
		return result;
		}

	/**
	 * 
	 * Adds the provided vector with the scalar.
	 * 
	 * @param x The vector that should be added.
	 * @param scalar The scalar that should be added.
	 * @return Returns a new vector containing the result of the addition.
	 */
	static FakeVector3 Add(const FakeVector3 &x, T scalar)
		{
		FakeVector3 result;
		Add(x, scalar, result);
		return result;
		}

	/**
	 * 
	 * Subtracts the provided vectors.
	 * 
	 * @param x The first vector that should be subtracted.
	 * @param y The second vector that should be subtracted.
	 * @return Returns a new vector containing the result of the subtraction.
	 */
	static FakeVector3 Subtract(const FakeVector3 &x, const FakeVector3 &y)
		{
		FakeVector3 result;
		Subtract(x, y, result);
		return result;
		}

	/**
	 * 
	 * Subtracts the provided vector with the scalar.
	 * 
	 * @param x The vector that should be subtracted.
	 * @param scalar The scalar that should be subtracted.
	 * @return Returns a new vector containing the result of the subtraction.
	 */
	static FakeVector3 Subtract(const FakeVector3 &x, T scalar)
		{
		FakeVector3 result;
		Subtract(x, scalar, result);
		return result;
		}

	/**
	 * 
	 * Multiplies the provided vectors.
	 * 
	 * @param x The first vector that should be multiplied.
	 * @param y The second vector that should be multiplied.
	 * @return Returns a new vector containing the result of the multiplication.
	 */
	static FakeVector3 Multiply(const FakeVector3 &x, const FakeVector3 &y)
		{
		FakeVector3 result;
		Multiply(x, y, result);
		return result;
		}

	/**
	 * 
	 * Multiplies the provided vector with the scalar.
	 * 
	 * @param x The vector that should be multiplied.
	 * @param scalar The scalar that should be multiplied.
	 * @return Returns a new vector containing the result of the multiplication.
	 */
	static FakeVector3 Multiply(const FakeVector3 &x, T scalar)
		{
		FakeVector3 result;
		Multiply(x, scalar, result);
		return result;
		}

	/**
	 * 
	 * Divides the provided vectors.
	 * 
	 * @param x The first vector that should be divided.
	 * @param y The second vector that should be divided.
	 * @return Returns a new vector containing the result of the division.
	 */
	static FakeVector3 Divide(const FakeVector3 &x, const FakeVector3 &y)
		{
		FakeVector3 result;
		Divide(x, y, result);
		return result;
		}

	/**
	 * 
	 * Divides the provided vector with the scalar.
	 * 
	 * @param x The vector that should be divided.
	 * @param scalar The scalar that should be divided.
	 * @return Returns a new vector containing the result of the division.
	 */
	static FakeVector3 Divide(const FakeVector3 &x, T scalar)
		{
		FakeVector3 result;
		Divide(x, scalar, result);
		return result;
		}

	/**
	 * 
	 * Floors the elements of the vector.
	 * 
	 * @param v The vector which elements should be floored.
	 * @return Returns a new vector containing the floored elements.
	 */
	static FakeVector3 Floor(const FakeVector3 &v)
		{
		return FakeVector3(fake_floor(v.X), fake_floor(v.Y), fake_floor(v.Z));
		}

	/**
	 * 
	 * Rounds the elements of the vector.
	 * 
	 * @param v The vector which elements should be rounded.
	 * @return Returns a new vector containing the rounded elements.
	 */
	static FakeVector3 Round(const FakeVector3 &v)
		{
		return FakeVector3(fake_round(v.X), fake_round(v.Y), fake_round(v.Z));
		}

	/**
	 * 
	 * Ceils the elements of the vector.
	 * 
	 * @param v The vector which elements should be ceiled.
	 * @return Returns a new vector containing the ceiled elements.
	 */
	static FakeVector3 Ceil(const FakeVector3 &v)
		{
		return FakeVector3(fake_ceil(v.X), fake_ceil(v.Y), fake_ceil(v.Z));
		}

	/**
	 * 
	 * Returns the fraction of the provided vector.
	 * 
	 * @param v The vector.
	 * @return Returns the fraction of the provided vector.
	 */
	static FakeVector3 Frac(const FakeVector3 &v)
		{
		return FakeVector3(v.X - (int32)v.X, v.Y - (int32)v.Y, v.Z - (int32)v.Z);
		}

	/**
	 * 
	 * Returns the scalar product of two vectors.
	 * 
	 * @param x The first vector.
	 * @param y The second vector.
	 * @return Returns the scalar product from the provided vectors.
	 */
	static T ScalarProduct(const FakeVector3 &x, const FakeVector3 &y)
		{
		return x.X * y.X + x.Y * y.Y + x.Z * y.Z;
		}

	/**
	 *
	 * Restricts a value to be within a specified range in C-Style.
	 *
	 * @param value The value to clamp.
	 * @param min The minimum value.
	 * @param max The maximum value.
	 * @param result The result where the clamped values are stored in.
	 */
	static void Clamp(const FakeVector3 &value, const FakeVector3 &min, const FakeVector3 &max, FakeVector3 &result)
		{
		result.X = FAKE_MIN(FAKE_MAX(value.X, min.X), max.X);
		result.Y = FAKE_MIN(FAKE_MAX(value.Y, min.Y), max.Y);
		result.Z = FAKE_MIN(FAKE_MAX(value.Z, min.Z), max.Z);
		}

	/**
	 * 
	 * Restricts a value to be within a specified range.
	 * 
	 * @param value The value to clamp.
	 * @param min The minimum value.
	 * @param max The maximum value.
	 * @return Returns clamped value.
	 */
	static FakeVector3 Clamp(const FakeVector3 &value, const FakeVector3 &min, const FakeVector3 &max)
		{
		T x = FAKE_MIN(FAKE_MAX(value.X, min.X), max.X);
		T y = FAKE_MIN(FAKE_MAX(value.Y, min.Y), max.Y);
		T z = FAKE_MIN(FAKE_MAX(value.Z, min.Z), max.Z);
		return FakeVector3(x, y, z);
		}

	/**
	 * 
	 * Calculates the distance between two vectors.
	 * 
	 * @param value1 The first vector.
	 * @param value2 The second vector.
	 * @return Returns the distance between the two vectors.
	 */
	static T Distance(const FakeVector3 &value1, const FakeVector3 &value2)
		{
		const T x = value1.X - value2.X;
		const T y = value1.Y - value2.Y;
		const T z = value1.Z - value2.Z;
		return fake_sqrt(x * x + y * y + z * z);
		}

	/**
	 * 
	 * Calculates the squared distance between two vectors.
	 * 
	 * @param value1 The first vector.
	 * @param value2 The second vector.
	 * @return Returns the squared distance between the two vectors.
	 */
	static T DistanceSquared(const FakeVector3 &value1, const FakeVector3 &value2)
		{
		const T x = value1.X - value2.X;
		const T y = value1.Y - value2.Y;
		const T z = value1.Z - value2.Z;
		return x * x + y * y + z * z;
		}

	/**
	 * 
	 * Dot product with another vector.
	 * 
	 * @param x The first vector.
	 * @param y The second vector.
	 * @return Returns the dot product of the provided vectors.
	 */
	static T Dot(const FakeVector3 &x, const FakeVector3 &y)
		{
		return x.X * y.X + x.Y * y.Y + x.Z * y.Z;
		}

	/**
	 * 
	 * Calculates the cross product of two vectors.
	 * 
	 * @param x First source vector.
	 * @param y Second source vector.
	 * @param result When the method completes, contains the cross product of the two vectors.
	 */
	static void Cross(const FakeVector3 &x, const FakeVector3 &y, FakeVector3 &result)
		{
		result.X = x.Y * y.Z - x.Z * y.Y;
		result.Y = x.Z * y.X - x.X * y.Z;
		result.Z = x.X * y.Y - x.Y * y.X;
		}

	/**
	 * 
	 * Calculates the cross product of two vectors.
	 * 
	 * @param x First source vector.
	 * @param y Second source vector.
	 * @return Returns a new vector containing the cross product of the two vectors.
	 */
	static FakeVector3 Cross(const FakeVector3 &x, const FakeVector3 &y)
		{
		FakeVector3 result;
		Cross(x, y, result);
		return result;
		}

	/**
	 * 
	 * Returns a vector containing the smallest components of the specified vectors in C-Style.
	 * 
	 * @param x The first source vector.
	 * @param y The second source vector.
	 * @param result The result containing the smallest components of the specified vectors.
	 */
	static void Min(const FakeVector3 &x, const FakeVector3 &y, FakeVector3 &result)
		{
		result.X = x.X < y.X ? x.X : y.X;
		result.Y = x.Y < y.Y ? x.Y : y.Y;
		result.Z = x.Z < y.Z ? x.Z : y.Z;
		}

	/**
	 * 
	 * Returns a vector containing the smallest components of the specified vectors.
	 * 
	 * @param x The first source vector.
	 * @param y The second source vector.
	 * @return Returns a new vector containing the smallest components of the specified vectors.
	 */
	static FakeVector3 Min(const FakeVector3 &x, const FakeVector3 &y)
		{
		return FakeVector3(x.X < y.X ? x.X : y.X, x.Y < y.Y ? x.Y : y.Y, x.Z < y.Z ? x.Z : y.Z);
		}

	/**
	 * 
	 * Returns a vector containing the largest components of the specified vectors in C-Style.
	 * 
	 * @param x The first source vector.
	 * @param y The second source vector.
	 * @param result The result containing the largest components of the specified vectors.
	 */
	static void Max(const FakeVector3 &x, const FakeVector3 &y, FakeVector3 &result)
		{
		result.X = x.X > y.X ? x.X : y.X;
		result.Y = x.Y > y.Y ? x.Y : y.Y;
		result.Z = x.Z > y.Z ? x.Z : y.Z;
		}

	/**
	 * 
	 * Returns a vector containing the largest components of the specified vectors.
	 * 
	 * @param x The first source vector.
	 * @param y The second source vector.
	 * @return Returns a vector containing the largest components of the specified vectors.
	 */
	static FakeVector3 Max(const FakeVector3 &x, const FakeVector3 &y)
		{
		return FakeVector3(x.X > y.X ? x.X : y.X, x.Y > y.Y ? x.Y : y.Y, x.Z > y.Z ? x.Z : y.Z);
		}

	/**
	 * 
	 * Performs a linear interpolation between two vectors in C-Style.
	 * 
	 * @param start The start vector.
	 * @param end The end vector.
	 * @param amount Value between 0 and 1 indicating the weight of end.
	 * @param result The result containing the linear interpolation.
	 */
	static void Lerp(const FakeVector3 &start, const FakeVector3 &end, T amount, FakeVector3 &result)
		{
		result.X = fake_lerp(start.X, end.X, amount);
		result.Y = fake_lerp(start.Y, end.Y, amount);
		result.Z = fake_lerp(start.Z, end.Z, amount);
		}

	/**
	 * 
	 * Performs a linear interpolation between two vectors.
	 * 
	 * @param start The start vector.
	 * @param end The end vector.
	 * @param amount Value between 0 and 1 indicating the weight of end.
	 * @return Returns a new vector containing the linear interpolation of the two vectors.
	 */
	static FakeVector3 Lerp(const FakeVector3 &start, const FakeVector3 &end, T amount)
		{
		FakeVector3 result;
		Lerp(start, end, amount, result);
		return result;
		}

	/**
	 * 
	 * Performs a cubic interpolation between two vectors in C-Style.
	 * 
	 * @param start The start vector.
	 * @param end The end vector.
	 * @param amount Value between 0 and 1 indicating the weight of end.
	 * @param result The result containing the cubic interpolation of the two vectors.
	 */
	static void SmoothStep(const FakeVector3 &start, const FakeVector3 &end, T amount, FakeVector3 &result)
		{
		amount = fake_smooth_step(amount);
		Lerp(start, end, amount, result);
		}

	/**
	 * 
	 * Performs a cubic interpolation between two vectors.
	 * 
	 * @param start The start vector.
	 * @param end The end vector.
	 * @param amount Value between 0 and 1 indicating the weight of end.
	 * @return Returns a new vector containing the cubic interpolation of the two vectors.
	 */
	static FakeVector3 SmoothStep(const FakeVector3 &start, const FakeVector3 &end, T amount)
		{
		FakeVector3 result;
		SmoothStep(start, end, amount, result);
		return result;
		}

	/**
	 * 
	 * Performs a Hermite spline interpolation in C-Style.
	 * 
	 * @param value1 First source position vector.
	 * @param value2 Second source position vector.
	 * @param tangent1 First source tangent vector.
	 * @param tangent2 Second source tangent vector.
	 * @param amount Weighting factor.
	 * @param result The result containing the hermite spline interpolation.
	 */
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

	/**
	 * 
	 * Returns the reflection of a vector off a surface that has the specified normal in C-Style.
	 * 
	 * @param vector The source vector.
	 * @param normal Normal of the surface.
	 * @param result The result containing the reflection of a vector.
	 */
	static void Reflect(const FakeVector3 &vector, const FakeVector3 &normal, FakeVector3 &result)
		{
		const T dot = vector.X * normal.X + vector.Y * normal.Y + vector.Z * normal.Z;
		result.X = vector.X - static_cast<T>(2) * dot * normal.X;
		result.Y = vector.Y - static_cast<T>(2) * dot * normal.Y;
		result.Z = vector.Z - static_cast<T>(2) * dot * normal.Z;
		}

	/**
	 * 
	 * Overloaded + operator.
	 * 
	 * @param v The vector that should be added to the current instance.
	 * @return Returns the current instance.
	 */
	FakeVector3 operator+(const FakeVector3 &v) const
		{
		return Add(*this, v);
		}

	/**
	 * 
	 * Overloaded - operator.
	 * 
	 * @param v The vector that should be subtracted from the current instance.
	 * @return Returns the current instance.
	 */
	FakeVector3 operator-(const FakeVector3 &v) const
		{
		return Subtract(*this, v);
		}

	/**
	 * 
	 * Overloaded * operator.
	 * 
	 * @param v The vector that should be multiplied.
	 * @return Returns the current instance.
	 */
	FakeVector3 operator*(const FakeVector3 &v) const
		{
		return Multiply(*this, v);
		}

	/**
	 * 
	 * Overloaded / operator.
	 * 
	 * @param v The vector that should be divided.
	 * @return Returns the current instance.
	 */
	FakeVector3 operator/(const FakeVector3 &v) const
		{
		return Divide(*this, v);
		}

	/**
	 * 
	 * Overloaded - operator.
	 * 
	 * @return Returns the negated vector of the current instance.
	 */
	FakeVector3 operator-() const
		{
		return FakeVector3(-X, -Y, -Z);
		}

	/**
	 * 
	 * Overloaded ^ operator (Cross product).
	 * 
	 * @param v The vector that should be crossed with the current instance.
	 * @return Returns the current instance crossed with the specified vector.
	 */
	FakeVector3 operator^(const FakeVector3 &v) const
		{
		return Cross(*this, v);
		}

	/**
	 * 
	 * Overloaded | operator (Dot product).
	 * 
	 * @param v The vector that should be used for the dot product with the current instance.
	 * @return Returns the current instance with the dot product.
	 */
	FakeVector3 operator|(const FakeVector3 &v) const
		{
		return Dot(*this, v);
		}

	/**
	 * 
	 * Overloaded += operator.
	 * 
	 * @param v The vector that should be added.
	 * @return Returns the current instance.
	 */
	FakeVector3 &operator+=(const FakeVector3 &v)
		{
		*this = Add(*this, v);
		return *this;
		}

	/**
	 * 
	 * Overloaded -= operator.
	 * 
	 * @param v The vector that should be subtracted.
	 * @return Returns the current instance.
	 */
	FakeVector3 &operator-=(const FakeVector3 &v)
		{
		*this = Subtract(*this, v);
		return *this;
		}

	/**
	 * 
	 * Overloaded *= operator.
	 * 
	 * @param v The vector that should be multiplied.
	 * @return Returns the current instance.
	 */
	FakeVector3 &operator*=(const FakeVector3 &v)
		{
		*this = Multiply(*this, v);
		return *this;
		}

	/**
	 * 
	 * Overloaded /= operator.
	 * 
	 * @param v The vector that should be divided.
	 * @return Returns the current instance.
	 */
	FakeVector3 &operator/=(const FakeVector3 &v)
		{
		*this = Divide(*this, v);
		return *this;
		}

	/**
	 * 
	 * Overloaded + operator.
	 * 
	 * @param scalar The scalar that should be added.
	 * @return Returns a new vector containing the result of the addition.
	 */
	FakeVector3 operator+(T scalar) const
		{
		return Add(*this, scalar);
		}

	/**
	 * 
	 * Overloaded - operator.
	 * 
	 * @param scalar The scalar that should be subtracted.
	 * @return Returns a new vector containing the result of the subtraction.
	 */
	FakeVector3 operator-(T scalar) const
		{
		return Subtract(*this, scalar);
		}

	/**
	 * 
	 * Overloaded * operator.
	 * 
	 * @param scalar The scalar that should be multiplied.
	 * @return Returns a new vector containing the result of the multiplication.
	 */
	FakeVector3 operator*(T scalar) const
		{
		return Multiply(*this, scalar);
		}

	/**
	 * 
	 * Overloaded / operator.
	 * 
	 * @param scalar The scalar that should be divided.
	 * @return Returns a new vector containing the result of the division.
	 */
	FakeVector3 operator/(T scalar) const
		{
		return Divide(*this, scalar);
		}

	/**
	 * 
	 * Overloaded += operator.
	 * 
	 * @param scalar The scalar that should be added.
	 * @return Returns a new vector containing the result of the addition.
	 */
	FakeVector3 &operator+=(T scalar)
		{
		*this = Add(*this, scalar);
		return *this;
		}

	/**
	 * 
	 * Overloaded -= operator.
	 * 
	 * @param scalar The scalar that should be subtracted.
	 * @return Returns a new vector containing the result of the subtraction.
	 */
	FakeVector3 &operator-=(T scalar)
		{
		*this = Subtract(*this, scalar);
		return *this;
		}

	/**
	 * 
	 * Overloaded *= operator.
	 * 
	 * @param scalar The scalar that should be multiplied.
	 * @return Returns a new vector containing the result of the multiplication.
	 */
	FakeVector3 &operator*=(T scalar)
		{
		*this = Multiply(*this, scalar);
		return *this;
		}

	/**
	 * 
	 * Overloaded /= operator.
	 * 
	 * @param scalar The scalar that should be divided.
	 * @return Returns a new vector containing the result of the division.
	 */
	FakeVector3 &operator/=(T scalar)
		{
		*this = Divide(*this, scalar);
		return *this;
		}

	/**
	 *
	 * Overloaded ++ operator.
	 *
	 * @return Returns a new vector with all elements incremented by one.
	 */
	FakeVector3 &operator++() const
		{
		return FakeVector3(X + static_cast<T>(1), Y + static_cast<T>(1), Z + static_cast<T>(1));
		}

	/**
	 *
	 * Overloaded -- operator.
	 *
	 * @return Returns a new vector with all elements decremented by one.
	 */
	FakeVector3 &operator--() const
		{
		return FakeVector3(X - static_cast<T>(1), Y - static_cast<T>(1), Z - static_cast<T>(1));
		}

	/**
	 * 
	 * Returns true if the specified vector is equal to the current instance.
	 * 
	 * @param other The vector that should be compared with the current instance.
	 * @return Returns true if the specified vector is equal to the current instance.
	 */
	bool operator==(const FakeVector3 &other) const
		{
		return X == other.X && Y == other.Y && Z == other.Z;
		}

	/**
	 * 
	 * Returns true if the specified vector is not equal to the current instance.
	 * 
	 * @param other The vector that should be compared with the current instance.
	 * @return Returns true if the specified vector is not equal to the current instance.
	 */
	bool operator!=(const FakeVector3 &other) const
		{
		return !(*this == other);
		}

	/**
	 * 
	 * Returns true if the specified vector is greater than the current instance.
	 * 
	 * @param other The vector that should be compared with the current instance.
	 * @return Returns true if the specified vector is greater than the current instance.
	 */
	bool operator<(const FakeVector3 &other) const
		{
		return X < other.X && Y < other.Y && Z < other.Z;
		}

	/**
	 * 
	 * Returns true if the specified vector is greater or equal than the current instance.
	 * 
	 * @param other The vector that should be compared with the current instance.
	 * @return Returns true if the specified vector is greater or equal than the current instance.
	 */
	bool operator<=(const FakeVector3 &other) const
		{
		return X <= other.X && Y <= other.Y && Z <= other.Z;
		}

	/**
	 * 
	 * Returns true if the specified vector is less than the current instance.
	 * 
	 * @param other The vector that should be compared with the current instance.
	 * @return Returns true if the specified vector is less than the current instance.
	 */
	bool operator>(const FakeVector3 &other) const
		{
		return X > other.X && Y > other.Y && Z > other.Z;
		}

	/**
	 * 
	 * Returns true if the specified vector is less or equal than the current instance.
	 * 
	 * @param other The vector that should be compared with the current instance.
	 * @return Returns true if the specified vector is less or equal than the current instance.
	 */
	bool operator>=(const FakeVector3 &other) const
		{
		return X >= other.X && Y >= other.Y && Z >= other.Z;
		}

	/**
	 * 
	 * Transforms a 3D vector by the given Quaternion rotation in C-Style.
	 * 
	 * @param vector The vector to rotate
	 * @param rotation The Quaternion rotation to apply
	 * @param result The result containing the transformed vector.
	 */
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

	/**
	 * 
	 * Transforms a 3D vector by the given Quaternion rotation.
	 * 
	 * @param vector The vector to rotate
	 * @param rotation The Quaternion rotation to apply
	 * @return Returns the transformed Vector3.
	 */
	static FakeVector3 Transform(const FakeVector3 &vector, const FakeQuaternion<T> &rotation)
		{
		FakeVector3 result;
		Transform(vector, rotation, result);
		return result;
		}

	/**
	 * 
	 * Transforms a 3D vector by the given matrix in C-Style.
	 * 
	 * @param vector The source vector.
	 * @param transform The transformation matrix.
	 * @param result The result containing the transformed vector.
	 */
	static void Transform(const FakeVector3 &vector, const FakeMatrix4x4<T> &transform, FakeVector3 &result)
		{
		result.X = vector.X * transform.M11 + vector.Y * transform.M21 + vector.Z * transform.M31 + transform.M41;
		result.Y = vector.X * transform.M12 + vector.Y * transform.M22 + vector.Z * transform.M32 + transform.M42;
		result.Z = vector.X * transform.M13 + vector.Y * transform.M23 + vector.Z * transform.M33 + transform.M43;
		}

	/**
	 * 
	 * Transforms a 3D vector by the given matrix.
	 * 
	 * @param vector The source vector.
	 * @param transform The transformation matrix.
	 * @return Returns transformed Vector.
	 */
	static FakeVector3 Transform(const FakeVector3 &vector, const FakeMatrix4x4<T> &transform)
		{
		FakeVector3 result;
		Transform(vector, transform, result);
		return result;
		}

	/**
	 * 
	 * Transforms 3D vectors by the given matrix in C-Style.
	 * 
	 * @param vectors The source vectors.
	 * @param transform The transformation matrix.
	 * @param vectorsCount Amount of vectors to transform.
	 * @param results The result containing the transformed vectors.
	 */
	static void Transform(const FakeVector3 *vectors, const FakeMatrix4x4<T> &transform, int32 vectorsCount, FakeVector3 *results)
		{
		for (int32 i = 0; i < vectorsCount; ++i)
			{
			Transform(vectors[i], transform, results[i]);
			}
		}

	/**
	 * 
	 * Performs a coordinate transformation using the given matrix in C-Style.
	 * 
	 * @param coordinate The coordinate vector to transform.
	 * @param transform The transformation matrix.
	 * @param result The result containing the transformed coordinates in a vector.
	 */
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

	/**
	 * 
	 * Performs a normal transformation using the given matrix in C-Style.
	 * 
	 * @param normal The normal vector to transform.
	 * @param transform The transformation matrix.
	 * @param result The result containing the normal transformation in a vector.
	 */
	static void TransformNormal(const FakeVector3 &normal, const FakeMatrix4x4<T> &transform, FakeVector3 &result)
		{
		result.X = normal.X * transform.M11 + normal.Y * transform.M21 + normal.Z * transform.M31;
		result.Y = normal.X * transform.M12 + normal.Y * transform.M22 + normal.Z * transform.M32;
		result.Z = normal.X * transform.M13 + normal.Y * transform.M23 + normal.Z * transform.M33;
		}

	/**
	 * 
	 * Projects a vector onto another vector.
	 * 
	 * @param vector The vector to project.
	 * @param onNormal The projection normal vector.
	 * @return Returns the projected vector.
	 */
	static FakeVector3 Project(const FakeVector3 &vector, const FakeVector3 &onNormal)
		{
		const T sqrMag = Dot(onNormal, onNormal);
		if (sqrMag < FAKE_ZERO_TOLERANCE)
			return Zero;

		return onNormal * Dot(vector, onNormal) / sqrMag;
		}

	/**
	 * 
	 * Projects a vector onto a plane defined by a normal orthogonal to the plane.
	 * 
	 * @param vector The vector to project.
	 * @param planeNormal The plane normal vector.
	 * @return Returns the projected vector.
	 */
	static FakeVector3 ProjectOnPlane(const FakeVector3 &vector, const FakeVector3 &planeNormal)
		{
		return vector - Project(vector, planeNormal);
		}

	/**
	 * 
	 * Projects a 3D vector from object space into screen space in C-Style.
	 * 
	 * @param vector The vector to project.
	 * @param x The X position of the viewport.
	 * @param y The Y position of the viewport.
	 * @param width The width of the viewport.
	 * @param height The height of the viewport.
	 * @param minZ The minimum depth of the viewport.
	 * @param maxZ The maximum depth of the viewport.
	 * @param worldViewProjection The combined world-view-projection matrix.
	 * @param result The result containing the projected vector.
	 */
	static void Project(const FakeVector3 &vector, T x, T y, T width, T height, T minZ, T maxZ, const FakeMatrix4x4<T> &worldViewProjection, FakeVector3 &result)
		{
		FakeVector3 v;
		TransformCoordinate(vector, worldViewProjection, v);

		result.X = (static_cast<T>(1) + v.X) * static_cast<T>(0.5) * width + x;
		result.Y = (static_cast<T>(1) - v.Y) * static_cast<T>(0.5) * height + y;
		result.Z = v.Z * (maxZ - minZ) + minZ;
		}

	/**
	 * 
	 * Projects a 3D vector from object space into screen space.
	 * 
	 * @param vector The vector to project.
	 * @param x The X position of the viewport.
	 * @param y The Y position of the viewport.
	 * @param width The width of the viewport.
	 * @param height The height of the viewport.
	 * @param minZ The minimum depth of the viewport.
	 * @param maxZ The maximum depth of the viewport.
	 * @param worldViewProjection The combined world-view-projection matrix.
	 * @return Returns the vector in screen space.
	 */
	static FakeVector3 Project(const FakeVector3 &vector, T x, T y, T width, T height, T minZ, T maxZ, const FakeMatrix4x4<T> &worldViewProjection)
		{
		FakeVector3 result;
		Project(vector, x, y, width, height, minZ, maxZ, worldViewProjection, result);
		return result;
		}

	/**
	 * 
	 * Projects a 3D vector from screen space into object space in C-Style.
	 * 
	 * @param vector The vector to project.
	 * @param x The X position of the viewport.
	 * @param y The Y position of the viewport.
	 * @param width The width of the viewport.
	 * @param height The height of the viewport.
	 * @param minZ The minimum depth of the viewport.
	 * @param maxZ The maximum depth of the viewport.
	 * @param worldViewProjection The combined world-view-projection matrix.
	 * @param result The result containing the unprojected vector.
	 */
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

	/**
	 * 
	 * Projects a 3D vector from screen space into object space.
	 * 
	 * @param vector The vector to project.
	 * @param x The X position of the viewport.
	 * @param y The Y position of the viewport.
	 * @param width The width of the viewport.
	 * @param height The height of the viewport.
	 * @param minZ The minimum depth of the viewport.
	 * @param maxZ The maximum depth of the viewport.
	 * @param worldViewProjection The combined world-view-projection matrix.
	 * @return Returns the vector in object space.
	 */
	static FakeVector3 Unproject(const FakeVector3 &vector, T x, T y, T width, T height, T minZ, T maxZ, const FakeMatrix4x4<T> &worldViewProjection)
		{
		FakeVector3 result;
		Unproject(vector, x, y, width, height, minZ, maxZ, worldViewProjection, result);
		return result;
		}

	/**
	 * 
	 * Creates an orthonormal basis from a basis with at least two orthogonal vectors.
	 * 
	 * @param xAxis The X Axis.
	 * @param yAxis The Y Axis.
	 * @param zAxis The Z Axis.
	 */
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

	/**
	 * 
	 * Finds the best arbitrary axis vectors to represent U and V axes of a plane, by using this vector as the normal of the plane.
	 * 
	 * @param firstAxis The reference to first axis.
	 * @param secondAxis The reference to second axis.
	 */
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

	/**
	 * 
	 * Calculates the area of the triangle.
	 * 
	 * @param v0 The first triangle vertex.
	 * @param v1 The second triangle vertex.
	 * @param v2 The third triangle vertex.
	 * @return Returns the triangle area.
	 */
	static T TriangleArea(const FakeVector3 &v0, const FakeVector3 &v1, const FakeVector3 &v2)
		{
		return (v2 - v0 ^ v1 - v0).Length() * static_cast<T>(0.5);
		}

	/**
	 * 
	 * Copy operator.
	 * 
	 * @param other The instance to copy.
	 * @return Returns the current instance.
	 */
	FakeVector3 &operator=(const FakeVector3 &other)
		{
		X = other.X;
		Y = other.Y;
		Z = other.Z;
		return *this;
		}

	/**
	 * 
	 * Overloaded dereferncing operator to get the vector data as an array.
	 * 
	 * @return Returns an array filled with the vectors content.
	 */
	T *operator*()
		{
		static T arr[3];
		arr[0] = X;
		arr[1] = Y;
		arr[2] = Z;
		return arr;
		}

	/**
	 * 
	 * Overloaded dereferncing operator to get the vector data as an array.
	 * 
	 * @return Returns an array filled with the vectors content.
	 */
	const T *operator*() const
		{
		static T arr[3];
		arr[0] = X;
		arr[1] = Y;
		arr[2] = Z;
		return arr;
		}

	/**
	 * 
	 * Overloaded Array Indexing operator to access the content of the vector directly like an array.
	 * 
	 * @param index The index where the vector instance should be accessed.
	 * @return Returns the content at the specified index.
	 */
	T &operator[](uint32 index)
		{
		FAKE_ASSERT(index < 3);
		return *((T*)this + index);
		}

	/**
	 * 
	 * Overloaded Array Indexing operator to access the content of the vector directly like an array.
	 * 
	 * @param index The index where the vector instance should be accessed.
	 * @return Returns the content at the specified index.
	 */
	const T &operator[](uint32 index) const
		{
		FAKE_ASSERT(index < 3);
		return *((T*)this + index);
		}

	/**
	 * 
	 * Overloaded << operator to print the Vector into a output stream.
	 * 
	 * @param stream The output stream.
	 * @param vector The vector to print.
	 * @return Returns the modified output stream.
	 */
	friend std::ostream &operator<<(std::ostream &stream, const FakeVector3 &vector)
		{
		stream << "Vector3(" << vector.X << ", " << vector.Y << ", " << vector.Z << ")";
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
	return FakeVector3(scalar) - v;
	}

template<typename T>
inline FakeVector3<T> operator*(T scalar, const FakeVector3<T> &v)
	{
	return v * scalar;
	}

template<typename T>
inline FakeVector3<T> operator/(T scalar, const FakeVector3<T> &v)
	{
	return FakeVector3(scalar) / v;
	}

typedef FakeVector3<double> FakeVec3d;
typedef FakeVector3<float> FakeVec3f;
typedef FakeVector3<int32> FakeVec3i;
typedef FakeVector3<short> FakeVec3s;
typedef FakeVector3<long> FakeVec3l;
typedef FakeVector3<bool> FakeVec3b;

