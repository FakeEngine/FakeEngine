/*****************************************************************
 * \file   FakeVector4.h
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
struct FakeVector3;

template<typename T>
struct FakeMatrix4x4;

/**
 * 
 * Represents a four dimensional mathematical vector.
 * 
 */
template<typename T>
struct FakeVector4
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

			/**
			 * 
			 * The W component.
			 * 
			 */
			T W;
			};

		T Raw[4];
		};

	// Vector with all components equal 0
	static const FakeVector4 Zero;

	// Vector with all components equal 1
	static const FakeVector4 One;

	// Vector X=1, Y=0, Z=0, W=0
	static const FakeVector4 UnitX;

	// Vector X=0, Y=1, Z=0, W=0
	static const FakeVector4 UnitY;

	// Vector X=0, Y=0, Z=1, W=0
	static const FakeVector4 UnitZ;

	// Vector X=0, Y=0, Z=0, W=1
	static const FakeVector4 UnitW;

	// A minimum Vector4
	static const FakeVector4 Minimum;

	// A maximum Vector4
	static const FakeVector4 Maximum;

	/**
	 * 
	 * Empty constructor.
	 * 
	 */
	FakeVector4()
		{
		}

	/**
	 *
	 * constructor.
	 * 
	 * @param xyzw Value to assign to the all components.
	 */
	FakeVector4(T xyzw)
		: X(xyzw), Y(xyzw), Z(xyzw), W(xyzw)
		{
		}

	/**
	 *
	 * constructor.
	 * 
	 * @param x X component value.
	 * @param y Y component value.
	 * @param z Z component value.
	 * @param w W component value.
	 */
	FakeVector4(T x, T y, T z, T w)
		: X(x), Y(y), Z(z), W(w)
		{
		}

	/**
	 *
	 * constructor.
	 * 
	 * @param xyzw X, Y, Z and W components in an array.
	 */
	FakeVector4(const T *xyzw)
		: X(xyzw[0]), Y(xyzw[1]), Z(xyzw[2]), W(xyzw[3])
		{
		}

	/**
	 *
	 * constructor.
	 * 
	 * @param xy Vector2 with X and Y components values.
	 */
	FakeVector4(const FakeVector2<T> &xy)
		: X(xy.X), Y(xy.Y), Z(static_cast<T>(0)), W(static_cast<T>(0))
		{
		}

	/**
	 *
	 * constructor.
	 * 
	 * @param xy Vector2 value.
	 * @param z Z component value.
	 */
	FakeVector4(const FakeVector2<T> &xy, T z)
		: X(xy.X), Y(xy.Y), Z(z), W(static_cast<T>(0))
		{
		}

	/**
	 *
	 * constructor.
	 * 
	 * @param xy Vector2 value.
	 * @param z Z component value.
	 * @param w W component value.
	 */
	FakeVector4(const FakeVector2<T> &xy, T z, T w)
		: X(xy.X), Y(xy.Y), Z(z), W(w)
		{
		}

	/**
	 *
	 * constructor.
	 * 
	 * @param xyz Vector3 value.
	 */
	FakeVector4(const FakeVector3<T> &xyz)
		: X(xyz.X), Y(xyz.Y), Z(xyz.Z), W(static_cast<T>(0))
		{
		}

	/**
	 *
	 * constructor.
	 * 
	 * @param xyz Vector3 value.
	 * @param w W component value.
	 */
	FakeVector4(const FakeVector3<T> &xyz, T w)
		: X(xyz.X), Y(xyz.Y), Z(xyz.Z), W(w)
		{
		}

	/**
	 *
	 * copy constructor.
	 * 
	 * @param xyzw Vector4 value.
	 */
	FakeVector4(const FakeVector4<T> &xyzw)
		: X(xyzw.X), Y(xyzw.Y), Z(xyzw.Z), W(xyzw.W)
		{
		}

	/**
	 * 
	 * Converts the Vector4 to a String.
	 * 
	 * @return Returns the Vector4 as a String.
	 */
	FakeString ToString() const
		{
		return "Vector4(" + FakeString::ToString(X) + ", " + FakeString::ToString(Y) + ", " + FakeString::ToString(Z) + ", " + FakeString::ToString(W) + ")";
		}

	/**
	 * 
	 * Gets a value indicating whether this instance is normalized.
	 * 
	 * @return Returns true if the instance is normalized.
	 */
	bool IsNormalized() const
		{
		return fake_is_one(X * X + Y * Y + Z * Z + W * W);
		}

	/**
	 * 
	 * Gets a value indicating whether this vector is zero.
	 * 
	 * @return Returns true if all elements of the instance are zero.
	 */
	bool IsZero() const
		{
		return fake_is_zero(X) && fake_is_zero(Y) && fake_is_zero(Z) && fake_is_zero(W);
		}

	/**
	 * 
	 * Gets a value indicating whether any vector component is zero.
	 * 
	 * @return Returns true if any element of the instance is zero.
	 */
	bool IsAnyZero() const
		{
		return fake_is_zero(X) || fake_is_zero(Y) || fake_is_zero(Z) || fake_is_zero(W);
		}

	/**
	 * 
	 * Gets a value indicating whether this vector is one.
	 * 
	 * @return Returns true if all elements of the instance is one.
	 */
	bool IsOne() const
		{
		return fake_is_one(X) && fake_is_one(Y) && fake_is_one(Z) && fake_is_one(W);
		}

	/**
	 * 
	 * Calculates length of the vector.
	 * 
	 * @return Returns the length of the vector.
	 */
	T Length() const
		{
		return fake_sqrt(X * X + Y * Y + Z * Z + W * W);
		}

	/**
	 * 
	 * Calculates the squared length of the vector.
	 * 
	 * @return Returns the squared length of the vector.
	 */
	T LengthSquared() const
		{
		return X * X + Y * Y + Z * Z + W * W;
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
	FakeVector4 GetAbsolute() const
		{
		return FakeVector4(FAKE_ABS(X), FAKE_ABS(Y), FAKE_ABS(Z), FAKE_ABS(W));
		}

	/**
	 * 
	 * Returns a new vector with inverted elements.
	 * 
	 * @return Returns a new vector with inverted elements.
	 */
	FakeVector4 GetNegative() const
		{
		return FakeVector4(-X, -Y, -Z, -W);
		}

	/**
	 * 
	 * Returns a new vector with normalized elements.
	 * 
	 * @return Returns a new vector with normalized elements.
	 */
	FakeVector4 GetNormalized() const
		{
		T invLen = InvLength();
		return FakeVector4(X * invLen, Y * invLen, Z * invLen, W * invLen);
		}

	/**
	 * 
	 * Returns the average arithmetic of the vector.
	 * 
	 * @return Returns the average arithmetic of the vector.
	 */
	T AverageArithmetic() const
		{
		return (X + Y + Z + W) * static_cast<T>(0.25);
		}

	/**
	 * 
	 * Returns minimum value of all the components.
	 * 
	 * @return Returns Minimum value.
	 */
	T Min() const
		{
		return fake_min(X, Y, Z, W);
		}

	/**
	 * 
	 * Returns maximum value of all the components.
	 * 
	 * @return Returns Maximum value.
	 */
	T Max() const
		{
		return fake_max(X, Y, Z, W);
		}

	/**
	 * 
	 * Returns true if the elements of the vector are Not a Number.
	 * 
	 * @return Returns true if the elements of the vector are Not a Number.
	 */
	bool IsNaN() const
		{
		return isnan(X) && isnan(Y) && isnan(Z) && isnan(W);
		}

	/**
	 * 
	 * Returns true if the elements of the vector are infinite.
	 * 
	 * @return Returns true if the elements of the vector are infinite.
	 */
	bool IsInfinity() const
		{
		return isinf(X) && isinf(Y) && isinf(Z) && isinf(W);
		}

	/**
	 * 
	 * Returns true if the elements of the vector are NaN or inifinite.
	 * 
	 * @return Returns true if either IsNaN or IsInfinity is true.
	 */
	bool IsNaNOrInfinity() const
		{
		return IsNan() || IsInfinity();
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
			W *= inv;
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
		W *= inv;
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
		W = FAKE_ABS(W);
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
		W = -W;
		}

	/**
	 * 
	 * Returns true if the elements of the vectors are near or equal to each other.
	 * 
	 * @param x The first vector to compare with.
	 * @param y The second vector to compare to.
	 * @return Returns true if the elements of the vectors are near or equal to each other.
	 */
	static bool NearEqual(const FakeVector4 &x, const FakeVector4 &y)
		{
		return fake_near_equal(x.X, y.X) && fake_near_equal(x.Y, y.Y) && fake_near_equal(x.Z, y.Z) && fake_near_equal(x.W, y.W);
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
	static bool NearEqual(const FakeVector4 &x, const FakeVector4 &y, T epsilon)
		{
		return fake_near_equal(x.X, y.X, epsilon) && fake_near_equal(x.Y, y.Y, epsilon) && fake_near_equal(x.Z, y.Z, epsilon) && fake_near_equal(x.W, y.W, epsilon);
		}

	/**
	 * 
	 * Adds the provided vectors in C-Style.
	 * 
	 * @param x The first vector that should be added.
	 * @param y The second vector that should be added.
	 * @param result The result where the addition is stored in.
	 */
	static void Add(const FakeVector4 &x, const FakeVector4 &y, FakeVector4 &result)
		{
		result.X = x.X + y.X;
		result.Y = x.Y + y.Y;
		result.Z = x.Z + y.Z;
		result.W = x.W + y.W;
		}

	/**
	 * 
	 * Adds the provided vector with a scalar in C-Style.
	 * 
	 * @param x The vector that should be added.
	 * @param scalar The scalar that should be added.
	 * @param result The result where the addition is stored in.
	 */
	static void Add(const FakeVector4 &x, T scalar, FakeVector4 &result)
		{
		result.X = x.X + scalar;
		result.Y = x.Y + scalar;
		result.Z = x.Z + scalar;
		result.W = x.W + scalar;
		}

	/**
	 * 
	 * Subtracts the provided vectors in C-Style.
	 * 
	 * @param x The first vector that should be subtracted.
	 * @param y The second vector that should be subtracted.
	 * @param result The result where the subtraction is stored in.
	 */
	static void Subtract(const FakeVector4 &x, const FakeVector4 &y, FakeVector4 &result)
		{
		result.X = x.X - y.X;
		result.Y = x.Y - y.Y;
		result.Z = x.Z - y.Z;
		result.W = x.W - y.W;
		}

	/**
	 * 
	 * Subtracts the provided vector with a scalar in C-Style.
	 * 
	 * @param x The vector that should be subtracted.
	 * @param scalar The scalar that should be subtracted.
	 * @param result The result where the subtraction is stored in.
	 */
	static void Subtract(const FakeVector4 &x, T scalar, FakeVector4 &result)
		{
		result.X = x.X - scalar;
		result.Y = x.Y - scalar;
		result.Z = x.Z - scalar;
		result.W = x.W - scalar;
		}

	/**
	 * 
	 * Multiplies the provided vectors in C-Style.
	 * 
	 * @param x The first vector that should be multiplied.
	 * @param y The second vector that should be multiplied.
	 * @param result The result where the multiplication is stored in.
	 */
	static void Multiply(const FakeVector4 &x, const FakeVector4 &y, FakeVector4 &result)
		{
		result.X = x.X * y.X;
		result.Y = x.Y * y.Y;
		result.Z = x.Z * y.Z;
		result.W = x.W * y.W;
		}

	/**
	 * 
	 * Multiplies the provided vector with the scalar in C-Style.
	 * 
	 * @param x The vector that should be multiplied.
	 * @param scalar The scalar that should be multiplied.
	 * @param result The result where the multiplication is stored in.
	 */
	static void Multiply(const FakeVector4 &x, T scalar, FakeVector4 &result)
		{
		result.X = x.X * scalar;
		result.Y = x.Y * scalar;
		result.Z = x.Z * scalar;
		result.W = x.W * scalar;
		}

	/**
	 * 
	 * Divides the provided vectors in C-Style. If the divisor is less than or equal to 0 the result will be 0.
	 * 
	 * @param x The first vector that should be divided.
	 * @param y The second vector that should be divided.
	 * @param result The result where the division is stored in.
	 */
	static void Divide(const FakeVector4 &x, const FakeVector4 &y, FakeVector4 &result)
		{
		if (y.X > static_cast<T>(0) && y.Y > static_cast<T>(0) && y.Z > static_cast<T>(0) && y.W > static_cast<T>(0))
			{
			result.X = x.X / y.X;
			result.Y = x.Y / y.Y;
			result.Z = x.Z / y.Z;
			result.W = x.W / y.W;
			}
		else
			{
			result.X = static_cast<T>(0);
			result.Y = static_cast<T>(0);
			result.Z = static_cast<T>(0);
			result.W = static_cast<T>(0);
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
	static void Divide(const FakeVector4 &x, T scalar, FakeVector4 &result)
		{
		if (scalar > static_cast<T>(0))
			{
			result.X = x.X / scalar;
			result.Y = x.Y / scalar;
			result.Z = x.Z / scalar;
			result.W = x.W / scalar;
			}
		else
			{
			result.X = static_cast<T>(0);
			result.Y = static_cast<T>(0);
			result.Z = static_cast<T>(0);
			result.W = static_cast<T>(0);
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
	static FakeVector4 Add(const FakeVector4 &x, const FakeVector4 &y)
		{
		FakeVector4 result;
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
	static FakeVector4 Add(const FakeVector4 &x, T scalar)
		{
		FakeVector4 result;
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
	static FakeVector4 Subtract(const FakeVector4 &x, const FakeVector4 &y)
		{
		FakeVector4 result;
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
	static FakeVector4 Subtract(const FakeVector4 &x, T scalar)
		{
		FakeVector4 result;
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
	static FakeVector4 Multiply(const FakeVector4 &x, const FakeVector4 &y)
		{
		FakeVector4 result;
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
	static FakeVector4 Multiply(const FakeVector4 &x, T scalar)
		{
		FakeVector4 result;
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
	static FakeVector4 Divide(const FakeVector4 &x, const FakeVector4 &y)
		{
		FakeVector4 result;
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
	static FakeVector4 Divide(const FakeVector4 &x, T scalar)
		{
		FakeVector4 result;
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
	static FakeVector4 Floor(const FakeVector4 &v)
		{
		return FakeVector4(fake_floor(v.X), fake_floor(v.Y), fake_floor(v.Z), fake_floor(v.W));
		}

	/**
	 * 
	 * Rounds the elements of the vector.
	 * 
	 * @param v The vector which elements should be rounded.
	 * @return Returns a new vector containing the rounded elements.
	 */
	static FakeVector4 Round(const FakeVector4 &v)
		{
		return FakeVector4(fake_round(v.X), fake_round(v.Y), fake_round(v.Z), fake_round(v.W));
		}

	/**
	 * 
	 * Ceils the elements of the vector.
	 * 
	 * @param v The vector which elements should be ceiled.
	 * @return Returns a new vector containing the ceiled elements.
	 */
	static FakeVector4 Ceil(const FakeVector4 &v)
		{
		return FakeVector4(fake_ceil(v.X), fake_ceil(v.Y), fake_ceil(v.Z), fake_ceil(v.W));
		}

	/**
	 * 
	 * Returns the fraction of the provided vector.
	 * 
	 * @param v The vector.
	 * @return Returns the fraction of the provided vector.
	 */
	static FakeVector4 Frac(const FakeVector4 &v)
		{
		return FakeVector4(v.X - (int32)v.X, v.Y - (int32)v.Y, v.Z - (int32)v.Z, v.W - (int32)v.W);
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
	static void Clamp(const FakeVector4 &value, const FakeVector4 &min, const FakeVector4 &max, FakeVector4 &result)
		{
		result.X = FAKE_MIN(FAKE_MAX(value.X, min.X), max.X);
		result.Y = FAKE_MIN(FAKE_MAX(value.Y, min.Y), max.Y);
		result.Z = FAKE_MIN(FAKE_MAX(value.Z, min.Z), max.Z);
		result.W = FAKE_MIN(FAKE_MAX(value.W, min.W), max.W);
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
	static FakeVector4 Clamp(const FakeVector4 &value, const FakeVector4 &min, const FakeVector4 &max)
		{
		T x = FAKE_MIN(FAKE_MAX(value.X, min.X), max.X);
		T y = FAKE_MIN(FAKE_MAX(value.Y, min.Y), max.Y);
		T z = FAKE_MIN(FAKE_MAX(value.Z, min.Z), max.Z);
		T w = FAKE_MIN(FAKE_MAX(value.W, min.W), max.W);
		return FakeVector4(x, y, z, w);
		}

	/**
	 * 
	 * Returns a vector containing the smallest components of the specified vectors in C-Style.
	 * 
	 * @param x The first source vector.
	 * @param y The second source vector.
	 * @param result The result containing the smallest components of the specified vectors.
	 */
	static void Min(const FakeVector4 &x, const FakeVector4 &y, FakeVector4 &result)
		{
		result.X = x.X < y.X ? x.X : y.X;
		result.Y = x.Y < y.Y ? x.Y : y.Y;
		result.Z = x.Z < y.Z ? x.Z : y.Z;
		result.W = x.W < y.W ? x.W : y.W;
		}

	/**
	 * 
	 * Returns a vector containing the smallest components of the specified vectors.
	 * 
	 * @param x The first source vector.
	 * @param y The second source vector.
	 * @return Returns a new vector containing the smallest components of the specified vectors.
	 */
	static FakeVector4 Min(const FakeVector4 &x, const FakeVector4 &y)
		{
		return FakeVector4(x.X < y.X ? x.X : y.X, x.Y < y.Y ? x.Y : y.Y, x.Z < y.Z ? x.Z : y.Z, x.W < y.W ? x.W : y.W);
		}

	/**
	 * 
	 * Returns a vector containing the largest components of the specified vectors in C-Style.
	 * 
	 * @param x The first source vector.
	 * @param y The second source vector.
	 * @param result The result containing the largest components of the specified vectors.
	 */
	static void Max(const FakeVector4 &x, const FakeVector4 &y, FakeVector4 &result)
		{
		result.X = x.X > y.X ? x.X : y.X;
		result.Y = x.Y > y.Y ? x.Y : y.Y;
		result.Z = x.Z > y.Z ? x.Z : y.Z;
		result.W = x.W > y.W ? x.W : y.W;
		}

	/**
	 * 
	 * Returns a vector containing the largest components of the specified vectors.
	 * 
	 * @param x The first source vector.
	 * @param y The second source vector.
	 * @return Returns a vector containing the largest components of the specified vectors.
	 */
	static FakeVector4 Max(const FakeVector4 &x, const FakeVector4 &y)
		{
		return FakeVector4(x.X > y.X ? x.X : y.X, x.Y > y.Y ? x.Y : y.Y, x.Z > y.Z ? x.Z : y.Z, x.W > y.W ? x.W : y.W);
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
	static void Lerp(const FakeVector4 &start, const FakeVector4 &end, T amount, FakeVector4 &result)
		{
		result.X = fake_lerp(start.X, end.X, amount);
		result.Y = fake_lerp(start.Y, end.Y, amount);
		result.Z = fake_lerp(start.Z, end.Z, amount);
		result.W = fake_lerp(start.W, end.W, amount);
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
	static FakeVector4 Lerp(const FakeVector4 &start, const FakeVector4 &end, T amount)
		{
		FakeVector4 result;
		Lerp(start, end, amount, result);
		return result;
		}

	/**
	 * 
	 * Overloaded + operator.
	 * 
	 * @param v The vector that should be added to the current instance.
	 * @return Returns the current instance.
	 */
	FakeVector4 operator+(const FakeVector4 &v) const
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
	FakeVector4 operator-(const FakeVector4 &v) const
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
	FakeVector4 operator*(const FakeVector4 &v) const
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
	FakeVector4 operator/(const FakeVector4 &v) const
		{
		return Divide(*this, v);
		}

	/**
	 * 
	 * Overloaded - operator.
	 * 
	 * @return Returns the negated vector of the current instance.
	 */
	FakeVector4 operator-() const
		{
		return FakeVector4(-X, -Y, -Z, -W);
		}

	/**
	 * 
	 * Overloaded += operator.
	 * 
	 * @param v The vector that should be added.
	 * @return Returns the current instance.
	 */
	FakeVector4 &operator+=(const FakeVector4 &v)
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
	FakeVector4 &operator-=(const FakeVector4 &v)
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
	FakeVector4 &operator*=(const FakeVector4 &v)
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
	FakeVector4 &operator/=(const FakeVector4 &v)
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
	FakeVector4 operator+(T scalar) const
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
	FakeVector4 operator-(T scalar) const
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
	FakeVector4 operator*(T scalar) const
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
	FakeVector4 operator/(T scalar) const
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
	FakeVector4 &operator+=(T scalar)
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
	FakeVector4 &operator-=(T scalar)
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
	FakeVector4 &operator*=(T scalar)
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
	FakeVector4 &operator/=(T scalar)
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
	FakeVector4 &operator++() const
		{
		return FakeVector4(X + static_cast<T>(1), Y + static_cast<T>(1), Z + static_cast<T>(1), W + static_cast<T>(1));
		}

	/**
	 * 
	 * Overloaded -- operator.
	 * 
	 * @return Returns a new vector with all elements decremented by one.
	 */
	FakeVector4 &operator--() const
		{
		return FakeVector4(X - static_cast<T>(1), Y - static_cast<T>(1), Z - static_cast<T>(1), W - static_cast<T>(1));
		}

	/**
	 * 
	 * Returns true if the specified vector is equal to the current instance.
	 * 
	 * @param other The vector that should be compared with the current instance.
	 * @return Returns true if the specified vector is equal to the current instance.
	 */
	bool operator==(const FakeVector4 &other) const
		{
		return X == other.X && Y == other.Y && Z == other.Z && W == other.W;
		}

	/**
	 * 
	 * Returns true if the specified vector is not equal to the current instance.
	 * 
	 * @param other The vector that should be compared with the current instance.
	 * @return Returns true if the specified vector is not equal to the current instance.
	 */
	bool operator!=(const FakeVector4 &other) const
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
	bool operator<(const FakeVector4 &other) const
		{
		return X < other.X && Y < other.Y && Z < other.Z && W < other.W;
		}

	/**
	 * 
	 * Returns true if the specified vector is greater or equal than the current instance.
	 * 
	 * @param other The vector that should be compared with the current instance.
	 * @return Returns true if the specified vector is greater or equal than the current instance.
	 */
	bool operator<=(const FakeVector4 &other) const
		{
		return X <= other.X && Y <= other.Y && Z <= other.Z && W <= other.W;
		}

	/**
	 * 
	 * Returns true if the specified vector is less than the current instance.
	 * 
	 * @param other The vector that should be compared with the current instance.
	 * @return Returns true if the specified vector is less than the current instance.
	 */
	bool operator>(const FakeVector4 &other) const
		{
		return X > other.X && Y > other.Y && Z > other.Z && W > other.W;
		}

	/**
	 * 
	 * Returns true if the specified vector is less or equal than the current instance.
	 * 
	 * @param other The vector that should be compared with the current instance.
	 * @return Returns true if the specified vector is less or equal than the current instance.
	 */
	bool operator>=(const FakeVector4 &other) const
		{
		return X >= other.X && Y >= other.Y && Z >= other.Z && W >= other.W;
		}

	/**
	 * 
	 * Transforms a vector with a transformation matrix.
	 * 
	 * @param v The vector.
	 * @param m The matrix.
	 * @return Returns the transformed vector.
	 */
	static FakeVector4 Transform(const FakeVector4 &v, const FakeMatrix4x4<T> &m)
		{
		return FakeVector4(
			m.Values[0][0] * v[0] + m.Values[1][0] * v[1] + m.Values[2][0] * v[2] + m.Values[3][0] * v[3],
			m.Values[0][1] * v[0] + m.Values[1][1] * v[1] + m.Values[2][1] * v[2] + m.Values[3][1] * v[3],
			m.Values[0][2] * v[0] + m.Values[1][2] * v[1] + m.Values[2][2] * v[2] + m.Values[3][2] * v[3],
			m.Values[0][3] * v[0] + m.Values[1][3] * v[1] + m.Values[2][3] * v[2] + m.Values[3][3] * v[3]);
		}

	/**
	 * 
	 * Copy operator.
	 * 
	 * @param other The instance to copy.
	 * @return Returns the current instance.
	 */
	FakeVector4 &operator=(const FakeVector4 &other)
		{
		X = other.X;
		Y = other.Y;
		Z = other.Z;
		W = other.W;
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
		static T arr[4];
		arr[0] = X;
		arr[1] = Y;
		arr[2] = Z;
		arr[3] = W;
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
		static T arr[4];
		arr[0] = X;
		arr[1] = Y;
		arr[2] = Z;
		arr[3] = W;
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
		FAKE_ASSERT(index < 4);
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
		FAKE_ASSERT(index < 4);
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
	friend std::ostream &operator<<(std::ostream &stream, const FakeVector4 &vector)
		{
		stream << "Vector4(" << vector.X << ", " << vector.Y << ", " << vector.Z << ", " << vector.W << ")";
		return stream;
		}
	};

template<typename T>
const FakeVector4<T> FakeVector4<T>::Zero(static_cast<T>(0));

template<typename T>
const FakeVector4<T> FakeVector4<T>::One(static_cast<T>(1));

template<typename T>
const FakeVector4<T> FakeVector4<T>::UnitX(static_cast<T>(1), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0));

template<typename T>
const FakeVector4<T> FakeVector4<T>::UnitY(static_cast<T>(0), static_cast<T>(1), static_cast<T>(0), static_cast<T>(0));

template<typename T>
const FakeVector4<T> FakeVector4<T>::UnitZ(static_cast<T>(0), static_cast<T>(0), static_cast<T>(1), static_cast<T>(0));

template<typename T>
const FakeVector4<T> FakeVector4<T>::UnitW(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(1));

template<typename T>
const FakeVector4<T> FakeVector4<T>::Minimum(fake_min<T>());

template<typename T>
const FakeVector4<T> FakeVector4<T>::Maximum(fake_max<T>());

template<typename T>
inline FakeVector4<T> operator+(T scalar, const FakeVector4<T> &v)
	{
	return v + scalar;
	}

template<typename T>
inline FakeVector4<T> operator-(T scalar, const FakeVector4<T> &v)
	{
	return FakeVector4(scalar) - v;
	}

template<typename T>
inline FakeVector4<T> operator*(T scalar, const FakeVector4<T> &v)
	{
	return v * scalar;
	}

template<typename T>
inline FakeVector4<T> operator/(T scalar, const FakeVector4<T> &v)
	{
	return FakeVector4(scalar) / v;
	}

typedef FakeVector4<double> FakeVec4d;
typedef FakeVector4<float> FakeVec4f;
typedef FakeVector4<int32> FakeVec4i;
typedef FakeVector4<short> FakeVec4s;
typedef FakeVector4<long> FakeVec4l;
typedef FakeVector4<bool> FakeVec4b;

