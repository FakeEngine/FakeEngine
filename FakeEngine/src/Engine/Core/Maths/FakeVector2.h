/*****************************************************************
 * \file   FakeVector2.h
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
struct FakeVector3;

template<typename T>
struct FakeVector4;

/**
 * 
 * Represents a two dimensional mathematical vector.
 * 
 */
template<typename T>
struct FakeVector2
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
			};

		T Raw[2];
		};

	// Vector with all components equal 0
	static const FakeVector2 Zero;

	// Vector with all components equal 1
	static const FakeVector2 One;

	// Vector X=1, Y=0
	static const FakeVector2 UnitX;

	// Vector X=0, Y=1
	static const FakeVector2 UnitY;

	// A minimum Vector2
	static const FakeVector2 Minimum;

	// A maximum Vector2
	static const FakeVector2 Maximum;

	/**
	 * 
	 * Empty constructor.
	 * 
	 */
	FakeVector2()
		{
		}

	/**
	 * 
	 * constructor.
	 * 
	 * @param xy
	 */
	FakeVector2(T xy)
		: X(xy), Y(xy)
		{
		}

	/**
	 * 
	 * constructor.
	 * 
	 * @param x
	 * @param y
	 */
	FakeVector2(T x, T y)
		: X(x), Y(y)
		{
		}

	/**
	 * 
	 * copy constructor.
	 * 
	 * @param other
	 */
	FakeVector2(const FakeVector2 &other)
		: X(other.X), Y(other.Y)
		{
		}

	/**
	 * 
	 * constructor.
	 * 
	 * @param other
	 */
	FakeVector2(const FakeVector3<T> &other)
		: X(other.X), Y(other.Y)
		{
		}

	/**
	 * 
	 * constructor.
	 * 
	 * @param other
	 */
	FakeVector2(const FakeVector4<T> &other)
		: X(other.X), Y(other.Y)
		{
		}

	/**
	 * 
	 * Converts the vector to a String.
	 * 
	 * @return Returns the vector as a String.
	 */
	FakeString ToString() const
		{
		return "Vector2(" + FakeString::ToString(X) + ", " + FakeString::ToString(Y) + ")";
		}

	/**
	 * 
	 * Gets a value indicating whether this instance is normalized.
	 * 
	 * @return Returns true if the instance is normalized.
	 */
	bool IsNormalized() const
		{
		return fake_is_one(X * X + Y * Y);
		}

	/**
	 * 
	 * Gets a value indicating whether this vector is zero.
	 * 
	 * @return Returns true if all elements of the instance are zero.
	 */
	bool IsZero() const
		{
		return fake_is_zero(X) && fake_is_zero(Y);
		}

	/**
	 * 
	 * Gets a value indicating whether any vector component is zero.
	 * 
	 * @return Returns true if any element of the instance is zero.
	 */
	bool IsAnyZero() const
		{
		return fake_is_zero(X) || fake_is_zero(Y);
		}

	/**
	 * 
	 * Gets a value indicating whether this vector is one.
	 * 
	 * @return Returns true if all elements of the instance is one.
	 */
	bool IsOne() const
		{
		return fake_is_one(X) && fake_is_one(Y);
		}

	/**
	 * 
	 * Calculates length of the vector.
	 * 
	 * @return Returns the length of the vector.
	 */
	T Length() const
		{
		return fake_sqrt(X * X + Y * Y);
		}

	/**
	 * 
	 * Calculates the squared length of the vector.
	 * 
	 * @return Returns the squared length of the vector.
	 */
	T LengthSquared() const
		{
		return X * X + Y * Y;
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
	FakeVector2 GetAbsolute() const
		{
		return FakeVector2(FAKE_ABS(X), FAKE_ABS(Y));
		}

	/**
	 * 
	 * Returns a new vector with inverted elements.
	 * 
	 * @return Returns a new vector with inverted elements.
	 */
	FakeVector2 GetNegative() const
		{
		return FakeVector2(-X, -Y);
		}

	/**
	 * 
	 * Returns a new vector with normalized elements.
	 * 
	 * @return Returns a new vector with normalized elements.
	 */
	FakeVector2 GetNormalized() const
		{
		T invLen = InvLength();
		return FakeVector2(X * invLen, Y * invLen);
		}

	/**
	 * 
	 * Returns the average arithmetic of the vector.
	 * 
	 * @return Returns the average arithmetic of the vector.
	 */
	T AverageArithmetic() const
		{
		return (X + Y) * static_cast<T>(0.5);
		}

	/**
	 * 
	 * Returns minimum value of all the components.
	 * 
	 * @return Returns Minimum value.
	 */
	T Min() const
		{
		return fake_min(X, Y);
		}

	/**
	 * 
	 * Returns maximum value of all the components.
	 * 
	 * @return Returns Maximum value.
	 */
	T Max() const
		{
		return fake_max(X, Y);
		}

	/**
	 *
	 * Returns true if the elements of the vector are Not a Number.
	 *
	 * @return Returns true if the elements of the vector are Not a Number.
	 */
	bool IsNaN() const
		{
		return isnan(X) && isnan(Y);
		}

	/**
	 *
	 * Returns true if the elements of the vector are infinite.
	 *
	 * @return Returns true if the elements of the vector are infinite.
	 */
	bool IsInfinity() const
		{
		return isinf(X) && isinf(Y);
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
		}

	/**
	 * 
	 * Returns true if the elements of the vectors are near or equal to each other.
	 * 
	 * @param x The first vector to compare with.
	 * @param y The second vector to compare to.
	 * @return Returns true if the elements of the vectors are near or equal to each other.
	 */
	static bool NearEqual(const FakeVector2 &x, const FakeVector2 &y)
		{
		return fake_near_equal(x.X, y.X) && fake_near_equal(y.X, y.Y);
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
	static bool NearEqual(const FakeVector2 &x, const FakeVector2 &y, T epsilon)
		{
		return fake_near_equal(x.X, x.Y, epsilon) && fake_near_equal(y.X, y.Y, epsilon);
		}

	/**
	 * 
	 * Adds the provided vectors in C-Style.
	 * 
	 * @param y The first vector that should be added.
	 * @param x The second vector that should be added.
	 * @param result The result where the addition is stored in.
	 */
	static void Add(const FakeVector2 &x, const FakeVector2 &y, FakeVector2 &result)
		{
		result.X = x.X + y.X;
		result.Y = x.Y + y.Y;
		}

	/**
	 * 
	 * Adds the provided vector with a scalar in C-Style.
	 * 
	 * @param x The vector that should be added.
	 * @param scalar The scalar that should be added.
	 * @param result The result where the addition is stored in.
	 */
	static void Add(const FakeVector2 &x, T scalar, FakeVector2 &result)
		{
		result.X = x.X + scalar;
		result.Y = x.Y + scalar;
		}

	/**
	 * 
	 * Subtracts the provided vectors in C-Style.
	 * 
	 * @param x The first vector that should be subtracted.
	 * @param y The second vector that should be subtracted.
	 * @param result The result where the subtraction is stored in.
	 */
	static void Subtract(const FakeVector2 &x, const FakeVector2 &y, FakeVector2 &result)
		{
		result.X = x.X - y.X;
		result.Y = x.Y - y.Y;
		}

	/**
	 * 
	 * Subtracts the provided vector with a scalar in C-Style.
	 * 
	 * @param x The vector that should be subtracted.
	 * @param scalar The scalar that should be subtracted.
	 * @param result The result where the subtraction is stored in.
	 */
	static void Subtract(const FakeVector2 &x, T scalar, FakeVector2 &result)
		{
		result.X = x.X - scalar;
		result.Y = x.Y - scalar;
		}

	/**
	 * 
	 * Multiplies the provided vectors in C-Style.
	 * 
	 * @param x The first vector that should be multiplied.
	 * @param y The second vector that should be multiplied.
	 * @param result The result where the multiplication is stored in.
	 */
	static void Multiply(const FakeVector2 &x, const FakeVector2 &y, FakeVector2 &result)
		{
		result.X = x.X * y.X;
		result.Y = x.Y * y.Y;
		}

	/**
	 * 
	 * Multiplies the provided vector with the scalar in C-Style.
	 * 
	 * @param x The vector that should be multiplied.
	 * @param scalar The scalar that should be multiplied.
	 * @param result The result where the multiplication is stored in.
	 */
	static void Multiply(const FakeVector2 &x, T scalar, FakeVector2 &result)
		{
		result.X = x.X * scalar;
		result.Y = x.Y * scalar;
		}

	/**
	 * 
	 * Divides the provided vectors in C-Style. If the divisor is less than or equal to 0 the result will be 0.
	 * 
	 * @param x The first vector that should be divided.
	 * @param y The second vector that should be divided.
	 * @param result The result where the division is stored in.
	 */
	static void Divide(const FakeVector2 &x, const FakeVector2 &y, FakeVector2 &result)
		{
		if (y.X > static_cast<T>(0) && y.Y > static_cast<T>(0))
			{
			result.X = x.X / y.X;
			result.Y = x.Y / y.Y;
			}
		else
			{
			result.X = static_cast<T>(0);
			result.Y = static_cast<T>(0);
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
	static void Divide(const FakeVector2 &x, T scalar, FakeVector2 &result)
		{
		if (scalar > static_cast<T>(0))
			{
			result.X = x.X / scalar;
			result.Y = x.Y / scalar;
			}
		else
			{
			result.X = static_cast<T>(0);
			result.Y = static_cast<T>(0);
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
	static FakeVector2 Add(const FakeVector2 &x, const FakeVector2 &y)
		{
		FakeVector2 result;
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
	static FakeVector2 Add(const FakeVector2 &x, T scalar)
		{
		FakeVector2 result;
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
	static FakeVector2 Subtract(const FakeVector2 &x, const FakeVector2 &y)
		{
		FakeVector2 result;
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
	static FakeVector2 Subtract(const FakeVector2 &x, T scalar)
		{
		FakeVector2 result;
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
	static FakeVector2 Multiply(const FakeVector2 &x, const FakeVector2 &y)
		{
		FakeVector2 result;
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
	static FakeVector2 Multiply(const FakeVector2 &x, T scalar)
		{
		FakeVector2 result;
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
	static FakeVector2 Divide(const FakeVector2 &x, const FakeVector2 &y)
		{
		FakeVector2 result;
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
	static FakeVector2 Divide(const FakeVector2 &x, T scalar)
		{
		FakeVector2 result;
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
	static FakeVector2 Floor(const FakeVector2 &v)
		{
		return FakeVector2(fake_floor(v.X), fake_floor(v.Y));
		}

	/**
	 * 
	 * Rounds the elements of the vector.
	 * 
	 * @param v The vector which elements should be rounded.
	 * @return Returns a new vector containing the rounded elements.
	 */
	static FakeVector2 Round(const FakeVector2 &v)
		{
		return FakeVector2(fake_round(v.X), fake_round(v.Y));
		}

	/**
	 * 
	 * Ceils the elements of the vector.
	 * 
	 * @param v The vector which elements should be ceiled.
	 * @return Returns a new vector containing the ceiled elements.
	 */
	static FakeVector2 Ceil(const FakeVector2 &v)
		{
		return FakeVector2(fake_ceil(v.X), fake_ceil(v.Y));
		}

	/**
	 * 
	 * Returns the fraction of the provided vector.
	 * 
	 * @param v The vector.
	 * @return Returns the fraction of the provided vector.
	 */
	static FakeVector2 Frac(const FakeVector2 &v)
		{
		return FakeVector2(v.X - (int32)v.X, v.Y - (int32)v.Y);
		}

	/**
	 * 
	 * Restricts a value to be within a specified range in C-Style.
	 * 
	 * @param value The value to clamp.
	 * @param min The minimum value.
	 * @param max The maximum value.
	 * @param result result The result where the clamped values are stored in.
	 */
	static void Clamp(const FakeVector2 &value, const FakeVector2 &min, const FakeVector2 &max, FakeVector2 &result)
		{
		result.X = FAKE_MIN(FAKE_MAX(value.X, min.X), max.X);
		result.Y = FAKE_MIN(FAKE_MAX(value.Y, min.Y), max.Y);
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
	static FakeVector2 Clamp(const FakeVector2 &value, const FakeVector2 &min, const FakeVector2 &max)
		{
		T x = FAKE_MIN(FAKE_MAX(value.X, min.X), max.X);
		T y = FAKE_MIN(FAKE_MAX(value.Y, min.Y), max.Y);
		return FakeVector2(x, y);
		}

	/**
	 * 
	 * Calculates the distance between two vectors.
	 * 
	 * @param value1 The first vector.
	 * @param value2 The second vector.
	 * @return Returns the distance between the two vectors.
	 */
	static T Distance(const FakeVector2 &value1, const FakeVector2 &value2)
		{
		const T x = value1.X - value2.X;
		const T y = value1.Y - value2.Y;
		return fake_sqrt(x * x + y * y);
		}

	/**
	 * 
	 * Calculates the squared distance between two vectors.
	 * 
	 * @param value1 The first vector.
	 * @param value2 The second vector.
	 * @return Returns the squared distance between the two vectors.
	 */
	static T DistanceSquared(const FakeVector2 &value1, const FakeVector2 &value2)
		{
		const T x = value1.X - value2.X;
		const T y = value1.Y - value2.Y;
		return x * x + y * y;
		}

	/**
	 *
	 * Dot product with another vector.
	 *
	 * @param x The first vector.
	 * @param y The second vector.
	 * @return Returns the dot product of the provided vectors.
	 */
	static T Dot(const FakeVector2 &x, const FakeVector2 &y)
		{
		return x.X * y.X + x.Y * y.Y;
		}

	/**
	 *
	 * Calculates the cross product of two vectors.
	 *
	 * @param x The first vector.
	 * @param y The second vector.
	 * @return Returns the cross product of the provided vectors.
	 */
	static T Cross(const FakeVector2 &x, const FakeVector2 &y)
		{
		return x.X * y.X - x.Y * y.Y;
		}

	/**
	 * 
	 * Returns a vector containing the smallest components of the specified vectors in C-Style.
	 * 
	 * @param x The first source vector.
	 * @param y The second source vector.
	 * @param result The result containing the smallest components of the specified vectors.
	 */
	static void Min(const FakeVector2 &x, const FakeVector2 &y, FakeVector2 &result)
		{
		result.X = x.X < y.X ? x.X : y.X;
		result.Y = x.Y < y.Y ? x.Y : y.Y;
		}

	/**
	 * 
	 * Returns a vector containing the smallest components of the specified vectors.
	 * 
	 * @param x The first source vector.
	 * @param y The second source vector.
	 * @return Returns a new vector containing the smallest components of the specified vectors.
	 */
	static FakeVector2 Min(const FakeVector2 &x, const FakeVector2 &y)
		{
		return FakeVector2(x.X < y.X ? x.X : y.X, x.Y < y.Y ? x.Y : y.Y);
		}

	/**
	 * 
	 * Returns a vector containing the largest components of the specified vectors in C-Style.
	 * 
	 * @param x The first source vector.
	 * @param y The second source vector.
	 * @param result The result containing the largest components of the specified vectors.
	 */
	static void Max(const FakeVector2 &x, const FakeVector2 &y, FakeVector2 &result)
		{
		result.X = x.X > y.X ? x.X : y.X;
		result.Y = x.Y > y.Y ? x.Y : y.Y;
		}

	/**
	 * 
	 * Returns a vector containing the largest components of the specified vectors.
	 * 
	 * @param x The first source vector.
	 * @param y The second source vector.
	 * @return Returns a vector containing the largest components of the specified vectors.
	 */
	static FakeVector2 Max(const FakeVector2 &x, const FakeVector2 &y)
		{
		return FakeVector2(x.X > y.X ? x.X : y.X, x.Y > y.Y ? x.Y : y.Y);
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
	static void Lerp(const FakeVector2 &start, const FakeVector2 &end, T amount, FakeVector2 &result)
		{
		result.X = fake_lerp(start.X, end.X, amount);
		result.Y = fake_lerp(start.Y, end.Y, amount);
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
	static FakeVector2 Lerp(const FakeVector2 &start, const FakeVector2 &end, T amount)
		{
		FakeVector2 result;
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
	FakeVector2 operator+(const FakeVector2 &v) const
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
	FakeVector2 operator-(const FakeVector2 &v) const
		{
		return Subtract(*this, v);
		}

	/**
	 * 
	 * Overloaded * operator.
	 * 
	 * @param v The vector that should be multiplied with the current instance.
	 * @return Returns the current instance.
	 */
	FakeVector2 operator*(const FakeVector2 &v) const
		{
		return Multiply(*this, v);
		}

	/**
	 * 
	 * Overloaded / operator.
	 * 
	 * @param v The vector that should be divided from the current instance.
	 * @return Returns the current instance.
	 */
	FakeVector2 operator/(const FakeVector2 &v) const
		{
		return Divide(*this, v);
		}

	/**
	 * 
	 * Overloaded - operator.
	 * 
	 * @return Returns the negated vector of the current instance.
	 */
	FakeVector2 operator-() const
		{
		return FakeVector2(-X, -Y);
		}

	/**
	 * 
	 * Overloaded ^ operator (Cross product).
	 * 
	 * @param v The vector that should be crossed with the current instance.
	 * @return Returns the current instance crossed with the specified vector.
	 */
	T operator^(const FakeVector2 &v) const
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
	T operator|(const FakeVector2 &v) const
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
	FakeVector2 &operator+=(const FakeVector2 &v)
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
	FakeVector2 &operator-=(const FakeVector2 &v)
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
	FakeVector2 &operator*=(const FakeVector2 &v)
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
	FakeVector2 &operator/=(const FakeVector2 &v)
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
	FakeVector2 operator+(T scalar) const
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
	FakeVector2 operator-(T scalar) const
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
	FakeVector2 operator*(T scalar) const
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
	FakeVector2 operator/(T scalar) const
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
	FakeVector2 &operator+=(T scalar)
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
	FakeVector2 &operator-=(T scalar)
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
	FakeVector2 &operator*=(T scalar)
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
	FakeVector2 &operator/=(T scalar)
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
	FakeVector2 &operator++() const
		{
		return FakeVector2(X + static_cast<T>(1), Y + static_cast<T>(1));
		}

	/**
	 *
	 * Overloaded -- operator.
	 *
	 * @return Returns a new vector with all elements decremented by one.
	 */
	FakeVector2 &operator--() const
		{
		return FakeVector2(X - static_cast<T>(1), Y - static_cast<T>(1));
		}

	/**
	 * 
	 * Returns true if the specified vector is equal to the current instance.
	 * 
	 * @param other The vector that should be compared with the current instance.
	 * @return Returns true if the specified vector is equal to the current instance.
	 */
	bool operator==(const FakeVector2 &other) const
		{
		return X == other.X && Y == other.Y;
		}

	/**
	 * 
	 * Returns true if the specified vector is not equal to the current instance.
	 * 
	 * @param other The vector that should be compared with the current instance.
	 * @return Returns true if the specified vector is not equal to the current instance.
	 */
	bool operator!=(const FakeVector2 &other) const
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
	bool operator<(const FakeVector2 &other) const
		{
		return X < other.X && Y < other.Y;
		}

	/**
	 * 
	 * Returns true if the specified vector is greater or equal than the current instance.
	 * 
	 * @param other The vector that should be compared with the current instance.
	 * @return Returns true if the specified vector is greater or equal than the current instance.
	 */
	bool operator<=(const FakeVector2 &other) const
		{
		return X <= other.X && Y <= other.Y;
		}

	/**
	 * 
	 * Returns true if the specified vector is less than the current instance.
	 * 
	 * @param other The vector that should be compared with the current instance.
	 * @return Returns true if the specified vector is less than the current instance.
	 */
	bool operator>(const FakeVector2 &other) const
		{
		return X > other.X && Y > other.Y;
		}

	/**
	 * 
	 * Returns true if the specified vector is less or equal than the current instance.
	 * 
	 * @param other The vector that should be compared with the current instance.
	 * @return Returns true if the specified vector is less or equal than the current instance.
	 */
	bool operator>=(const FakeVector2 &other) const
		{
		return X >= other.X && Y >= other.Y;
		}

	/**
	 * 
	 * Copy operator.
	 * 
	 * @param other The instance to copy.
	 * @return Returns the current instance.
	 */
	FakeVector2 &operator=(const FakeVector2 &other)
		{
		X = other.X;
		Y = other.Y;
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
		static T arr[2];
		arr[0] = X;
		arr[1] = Y;
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
		static T arr[2];
		arr[0] = X;
		arr[1] = Y;
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
		FAKE_ASSERT(index < 2);
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
		FAKE_ASSERT(index < 2);
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
	friend std::ostream &operator<<(std::ostream &stream, const FakeVector2 &vector)
		{
		stream << "Vector2(" << vector.X << ", " << vector.Y << ")";
		return stream;
		}
	};

template<typename T>
const FakeVector2<T> FakeVector2<T>::Zero(static_cast<T>(0));

template<typename T>
const FakeVector2<T> FakeVector2<T>::One(static_cast<T>(1));

template<typename T>
const FakeVector2<T> FakeVector2<T>::UnitX(static_cast<T>(1), static_cast<T>(0));

template<typename T>
const FakeVector2<T> FakeVector2<T>::UnitY(static_cast<T>(0), static_cast<T>(1));

template<typename T>
const FakeVector2<T> FakeVector2<T>::Minimum(fake_min<T>());

template<typename T>
const FakeVector2<T> FakeVector2<T>::Maximum(fake_max<T>());

template<typename T>
inline FakeVector2<T> operator+(T scalar, const FakeVector2<T> &v)
	{
	return v + scalar;
	}

template<typename T>
inline FakeVector2<T> operator-(T scalar, const FakeVector2<T> &v)
	{
	return FakeVector2(scalar) - v;
	}

template<typename T>
inline FakeVector2<T> operator*(T scalar, const FakeVector2<T> &v)
	{
	return v * scalar;
	}

template<typename T>
inline FakeVector2<T> operator/(T scalar, const FakeVector2<T> &v)
	{
	return FakeVector2(scalar) / v;
	}

typedef FakeVector2<double> FakeVec2d;
typedef FakeVector2<float> FakeVec2f;
typedef FakeVector2<int32> FakeVec2i;
typedef FakeVector2<short> FakeVec2s;
typedef FakeVector2<long> FakeVec2l;
typedef FakeVector2<bool> FakeVec2b;

