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

#include "FakeMathFunctions.h"

template<typename T>
struct FakeVector2;

template<typename T>
struct FakeVector3;

template<typename T>
struct FakeMatrix4x4;

template<typename T>
struct FakeVector4
	{
	union
		{
		struct
			{
			T X;
			T Y;
			T Z;
			T W;
			};

		T Raw[4];
		};

	static const FakeVector4 Zero;
	static const FakeVector4 One;
	static const FakeVector4 UnitX;
	static const FakeVector4 UnitY;
	static const FakeVector4 UnitZ;
	static const FakeVector4 UnitW;
	static const FakeVector4 Minimum;
	static const FakeVector4 Maximum;

	FakeVector4()
		: X(0), Y(0), Z(0), W(0)
		{		}

	FakeVector4(T xyzw)
		: X(xyzw), Y(xyzw), Z(xyzw), W(xyzw)
		{		}

	FakeVector4(T x, T y, T z, T w)
		: X(x), Y(y), Z(z), W(w)
		{		}

	FakeVector4(const T *xyzw)
		: X(xyzw[0]), Y(xyzw[1]), Z(xyzw[2]), W(xyzw[3])
		{		}

	FakeVector4(const FakeVector2<T> &xy)
		: X(xy.X), Y(xy.Y), Z(0), W(0)
		{		}

	FakeVector4(const FakeVector3<T> &xyz)
		: X(xyz.X), Y(xyz.Y), Z(xyz.Z), W(0)
		{		}

	FakeVector4(const FakeVector4 &other)
		: X(other.X), Y(other.Y), Z(other.Z), W(other.W)
		{		}

	FakeVector4(const FakeVector2<T> &xy, const FakeVector2<T> &zw)
		: X(xy.X), Y(xy.Y), Z(zw.X), W(zw.Y)
		{		}

	FakeVector4(const FakeVector2<T> &xy, T z, T w)
		: X(xy.X), Y(xy.Y), Z(z), W(w)
		{		}

	FakeVector4(const FakeVector3<T> &xyz, T w)
		: X(xyz.X), Y(xyz.Y), Z(xyz.Z), W(w)
		{		}

	FakeString ToString() const
		{
		return FakeString::ToString(X) + ", " + FakeString::ToString(Y) + ", " + FakeString::ToString(Z) + ", " + FakeString::ToString(W);
		}

	bool IsNormalized() const
		{
		return fake_is_one(X * X + Y * Y + Z * Z + W * W);
		}

	bool IsZero() const
		{
		return fake_is_zero(X) && fake_is_zero(Y) && fake_is_zero(Z) && fake_is_zero(W);
		}

	bool IsAnyZero() const
		{
		return fake_is_zero(X) || fake_is_zero(Y) || fake_is_zero(Z) || fake_is_zero(W);
		}

	bool IsOne() const
		{
		return fake_is_one(X) && fake_is_one(Y) && fake_is_one(Z) && fake_is_one(W);
		}

	bool IsAnyOne() const
		{
		return fake_is_one(X) || fake_is_one(Y) || fake_is_one(Z) || fake_is_one(W);
		}

	T Length() const
		{
		return fake_sqrt(X * X + Y * Y + Z * Z + W * W);
		}

	T LengthSquared() const
		{
		return X * X + Y * Y + Z * Z + W * W;
		}

	T InverseLength() const
		{
		return static_cast<T>(1) / Length();
		}

	FakeVector4 GetAbsolute() const
		{
		return FakeVector4(FAKE_ABS(X), FAKE_ABS(Y), FAKE_ABS(Z), FAKE_ABS(W));
		}

	FakeVector4 GetNegative() const
		{
		return FakeVector4(-X, -Y, -Z, -W);
		}

	FakeVector4 GetNormalized() const
		{
		T invLen = InverseLength();
		return FakeVector4(X * invLen, Y * invLen, Z * invLen, W * invLen);
		}

	T AverageArithmetic() const
		{
		return (X + Y + Z + W) * static_cast<T>(0.25);
		}

	T Min() const
		{
		return fake_min(X, Y, Z, W);
		}

	T Max() const
		{
		return fake_max(X, Y, Z, W);
		}

	bool IsNaN() const
		{
		return isnan(X) && isnan(Y) && isnan(Z) && isnan(W);
		}

	bool IsInfinity() const
		{
		return isinf(X) && isinf(Y) && isinf(Z) && isinf(W);
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
			const T invLen = static_cast<T>(1) / length;
			X *= invLen;
			Y *= invLen;
			Z *= invLen;
			W *= invLen;
			}
		}

	void NormalizeFast()
		{
		const T invLen = static_cast<T>(1) / Length();
		X *= invLen;
		Y *= invLen;
		Z *= invLen;
		W *= invLen;
		}

	void Absolute()
		{
		X = FAKE_ABS(X);
		Y = FAKE_ABS(Y);
		Z = FAKE_ABS(Z);
		W = FAKE_ABS(W);
		}

	void Negate()
		{
		X = -X;
		Y = -Y;
		Z = -Z;
		W = -W;
		}

	static bool NearEqual(const FakeVector4 &a, const FakeVector4 &b)
		{
		return fake_near_equal(a.X, b.X) && fake_near_equal(a.Y, b.Y) && fake_near_equal(a.Z, b.Z) && fake_near_equal(a.W, b.W);
		}

	static bool NearEqual(const FakeVector4 &a, const FakeVector4 &b, T epsilon)
		{
		return fake_near_equal(a.X, b.X, epsilon) && fake_near_equal(a.Y, b.Y, epsilon) && fake_near_equal(a.Z, b.Z, epsilon) && fake_near_equal(a.W, b.W, epsilon);
		}

	static void Add(const FakeVector4 &a, const FakeVector4 &b, FakeVector4 &result)
		{
		result.X = a.X + b.X;
		result.Y = a.Y + b.Y;
		result.Z = a.Z + b.Z;
		result.W = a.W + b.W;
		}

	static void Add(const FakeVector4 &a, T b, FakeVector4 &result)
		{
		result.X = a.X + b;
		result.Y = a.Y + b;
		result.Z = a.Z + b;
		result.W = a.W + b;
		}

	static void Subtract(const FakeVector4 &a, const FakeVector4 &b, FakeVector4 &result)
		{
		result.X = a.X - b.X;
		result.Y = a.Y - b.Y;
		result.Z = a.Z - b.Z;
		result.W = a.W - b.W;
		}

	static void Subtract(const FakeVector4 &a, T b, FakeVector4 &result)
		{
		result.X = a.X - b;
		result.Y = a.Y - b;
		result.Z = a.Z - b;
		result.W = a.W - b;
		}

	static void Multiply(const FakeVector4 &a, const FakeVector4 &b, FakeVector4 &result)
		{
		result.X = a.X * b.X;
		result.Y = a.Y * b.Y;
		result.Z = a.Z * b.Z;
		result.W = a.W * b.W;
		}

	static void Multiply(const FakeVector4 &a, T b, FakeVector4 &result)
		{
		result.X = a.X * b;
		result.Y = a.Y * b;
		result.Z = a.Z * b;
		result.W = a.W * b;
		}

	static void Divide(const FakeVector4 &a, const FakeVector4 &b, FakeVector4 &result)
		{
		if (b > static_cast<T>(0))
			{
			result.X = a.X / b.X;
			result.Y = a.Y / b.Y;
			result.Z = a.Z / b.Z;
			result.W = a.W / b.W;
			}
		else
			{
			result.X = static_cast<T>(0);
			result.Y = static_cast<T>(0);
			result.Z = static_cast<T>(0);
			result.W = static_cast<T>(0);
			}
		}

	static void Divide(const FakeVector4 &a, T b, FakeVector4 &result)
		{
		if (b > static_cast<T>(0))
			{
			result.X = a.X / b;
			result.Y = a.Y / b;
			result.Z = a.Z / b;
			result.W = a.W / b;
			}
		else
			{
			result.X = static_cast<T>(0);
			result.Y = static_cast<T>(0);
			result.Z = static_cast<T>(0);
			result.W = static_cast<T>(0);
			}
		}

	static FakeVector4 Add(const FakeVector4 &a, const FakeVector4 &b)
		{
		FakeVector4 result;
		Add(a, b, result);
		return result;
		}

	static FakeVector4 Subtract(const FakeVector4 &a, const FakeVector4 &b)
		{
		FakeVector4 result;
		Subtract(a, b, result);
		return result;
		}

	static FakeVector4 Multiply(const FakeVector4 &a, const FakeVector4 &b)
		{
		FakeVector4 result;
		Multiply(a, b, result);
		return result;
		}

	static FakeVector4 Divide(const FakeVector4 &a, const FakeVector4 &b)
		{
		FakeVector4 result;
		Divide(a, b, result);
		return result;
		}

	static FakeVector4 Add(const FakeVector4 &a, T b)
		{
		FakeVector4 result;
		Add(a, b, result);
		return result;
		}

	static FakeVector4 Subtract(const FakeVector4 &a, T b)
		{
		FakeVector4 result;
		Subtract(a, b, result);
		return result;
		}

	static FakeVector4 Multiply(const FakeVector4 &a, T b)
		{
		FakeVector4 result;
		Multiply(a, b, result);
		return result;
		}

	static FakeVector4 Divide(const FakeVector4 &a, T b)
		{
		FakeVector4 result;
		Divide(a, b, result);
		return result;
		}

	static FakeVector4 Floor(const FakeVector4 &v)
		{
		return FakeVector4(fake_floor(v.X), fake_floor(v.Y), fake_floor(v.Z), fake_floor(v.W));
		}

	static FakeVector4 Round(const FakeVector4 &v)
		{
		return FakeVector4(fake_round(v.X), fake_round(v.Y), fake_round(v.Z), fake_round(v.W));
		}

	static FakeVector4 Ceil(const FakeVector4 &v)
		{
		return FakeVector4(fake_ceil(v.X), fake_ceil(v.Y), fake_ceil(v.Z), fake_ceil(v.W));
		}

	static FakeVector4 Frac(const FakeVector4 &v)
		{
		return FakeVector4(v.X - (int32) v.X, v.Y - (int32) v.Y, v.Z - (int32) v.Z, v.W - (int32) v.W);
		}

	static void Clamp(const FakeVector4 &value, const FakeVector4 &min, const FakeVector4 &max, FakeVector4 &result)
		{
		result.X = FAKE_MIN(FAKE_MAX(value.X, min.X), max.X);
		result.Y = FAKE_MIN(FAKE_MAX(value.Y, min.Y), max.Y);
		result.Z = FAKE_MIN(FAKE_MAX(value.Z, min.Z), max.Z);
		result.W = FAKE_MIN(FAKE_MAX(value.W, min.W), max.W);
		}

	static FakeVector4 Clamp(const FakeVector4 &value, const FakeVector4 &min, const FakeVector4 &max)
		{
		const T x = FAKE_MIN(FAKE_MAX(value.X, min.X), max.X);
		const T y = FAKE_MIN(FAKE_MAX(value.Y, min.Y), max.Y);
		const T z = FAKE_MIN(FAKE_MAX(value.Z, min.Z), max.Z);
		const T w = FAKE_MIN(FAKE_MAX(value.W, min.W), max.W);
		return FakeVector4(x, y, z, w);
		}

	static void Min(const FakeVector4 &a, const FakeVector4 &b, FakeVector4 &result)
		{
		result.X = a.X < b.X ? a.X : b.X;
		result.Y = a.Y < b.Y ? a.Y : b.Y;
		result.Z = a.Z < b.Z ? a.Z : b.Z;
		result.W = a.W < b.W ? a.W : b.W;
		}

	static FakeVector4 Min(const FakeVector4 &a, const FakeVector4 &b)
		{
		return FakeVector4(a.X < b.X ? a.X : b.X, a.Y < b.Y ? a.Y : b.Y, a.Z < b.Z ? a.Z : b.Z, a.W < b.W ? a.W : b.W);
		}

	static void Max(const FakeVector4 &a, const FakeVector4 &b, FakeVector4 &result)
		{
		result.X = a.X > b.X ? a.X : b.X;
		result.Y = a.Y > b.Y ? a.Y : b.Y;
		result.Z = a.Z > b.Z ? a.Z : b.Z;
		result.W = a.W > b.W ? a.W : b.W;
		}

	static FakeVector4 Max(const FakeVector4 &a, const FakeVector4 &b)
		{
		return FakeVector4(a.X > b.X ? a.X : b.X, a.Y > b.Y ? a.Y : b.Y, a.Z > b.Z ? a.Z : b.Z, a.W > b.W ? a.W : b.W);
		}

	static void Lerp(const FakeVector4 &start, const FakeVector4 &end, T amount, FakeVector4 &result)
		{
		result.X = fake_lerp(start.X, end.X, amount);
		result.Y = fake_lerp(start.Y, end.Y, amount);
		result.Z = fake_lerp(start.Z, end.Z, amount);
		result.W = fake_lerp(start.W, end.W, amount);
		}

	static FakeVector4 Lerp(const FakeVector4 &start, const FakeVector4 &end, T amount)
		{
		FakeVector4 result;
		Lerp(start, end, amount, result);
		return result;
		}

	static FakeVector4 Transform(const FakeVector4 &v, const FakeMatrix4x4<T> &m)
		{
		return FakeVector4(
			m.Values[0][0] * v[0] + m.Values[1][0] * v[1] + m.Values[2][0] * v[2] + m.Values[3][0] * v[3],
			m.Values[0][1] * v[0] + m.Values[1][1] * v[1] + m.Values[2][1] * v[2] + m.Values[3][1] * v[3],
			m.Values[0][2] * v[0] + m.Values[1][2] * v[1] + m.Values[2][2] * v[2] + m.Values[3][2] * v[3],
			m.Values[0][3] * v[0] + m.Values[1][3] * v[1] + m.Values[2][3] * v[2] + m.Values[3][3] * v[3]);
		}

	bool operator==(const FakeVector4 &other) const
		{
		return X == other.X && Y == other.Y && Z == other.Z && W == other.W;
		}

	bool operator!=(const FakeVector4 &other) const
		{
		return !(*this == other);
		}

	bool operator<(const FakeVector4 &other) const
		{
		return X < other.X &&Y < other.Y &&Z < other.Z &&W < other.W;
		}

	bool operator<=(const FakeVector4 &other) const
		{
		return X <= other.X && Y <= other.Y && Z <= other.Z && W <= other.W;
		}

	bool operator>(const FakeVector4 &other) const
		{
		return X > other.X && Y > other.Y && Z > other.Z && W > other.W;
		}

	bool operator>=(const FakeVector4 &other) const
		{
		return X >= other.X && Y >= other.Y && Z >= other.Z && W >= other.W;
		}

	bool operator==(T value) const
		{
		return X == value && Y == value && Z == value && W == value;
		}

	bool operator!=(T value) const
		{
		return !(*this == value);
		}

	bool operator<(T value) const
		{
		return X < value &&Y < value &&Z < value &&W < value;
		}

	bool operator<=(T value) const
		{
		return X <= value && Y <= value && Z <= value && W <= value;
		}

	bool operator>(T value) const
		{
		return X > value && Y > value && Z > value && W > value;
		}

	bool operator>=(T value) const
		{
		return X >= value && Y >= value && Z >= value && W >= value;
		}

	FakeVector4 operator-() const
		{
		return FakeVector4(-X, -Y, -Z, -W);
		}

	FakeVector4 operator+(const FakeVector4 &other) const
		{
		return Add(*this, other);
		}

	FakeVector4 operator-(const FakeVector4 &other) const
		{
		return Subtract(*this, other);
		}

	FakeVector4 operator*(const FakeVector4 &other) const
		{
		return Multiply(*this, other);
		}

	FakeVector4 operator/(const FakeVector4 &other) const
		{
		return Divide(*this, other);
		}

	FakeVector4 &operator+=(const FakeVector4 &other)
		{
		*this = Add(*this, other);
		return *this;
		}

	FakeVector4 &operator-=(const FakeVector4 &other)
		{
		*this = Subtract(*this, other);
		return *this;
		}

	FakeVector4 &operator*=(const FakeVector4 &other)
		{
		*this = Multiply(*this, other);
		return *this;
		}

	FakeVector4 &operator/=(const FakeVector4 &other)
		{
		*this = Divide(*this, other);
		return *this;
		}

	FakeVector4 operator+(T scalar) const
		{
		return Add(*this, scalar);
		}

	FakeVector4 operator-(T scalar) const
		{
		return Subtract(*this, scalar);
		}

	FakeVector4 operator*(T scalar) const
		{
		return Multiply(*this, scalar);
		}

	FakeVector4 operator/(T scalar) const
		{
		return Divide(*this, scalar);
		}

	FakeVector4 &operator+=(T scalar)
		{
		*this = Add(*this, scalar);
		return *this;
		}

	FakeVector4 &operator-=(T scalar)
		{
		*this = Subtract(*this, scalar);
		return *this;
		}

	FakeVector4 &operator*=(T scalar)
		{
		*this = Multiply(*this, scalar);
		return *this;
		}

	FakeVector4 &operator/=(T scalar)
		{
		*this = Divide(*this, scalar);
		return *this;
		}

	FakeVector4 &operator++(int)
		{
		++X;
		++Y;
		++Z;
		++W;
		return *this;
		}

	FakeVector4 &operator--(int)
		{
		--X;
		--Y;
		--Z;
		--W;
		return *this;
		}

	FakeVector4 &operator=(const FakeVector4 &other)
		{
		X = other.X;
		Y = other.Y;
		Z = other.Z;
		W = other.W;
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

	friend std::ostream &operator<<(std::ostream &stream, const FakeVector4 &v)
		{
		stream << v.X << ", " << v.Y << ", " << v.Z << ", " << v.W;
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
	return FakeVector4<T>(scalar) - v;
	}

template<typename T>
inline FakeVector4<T> operator*(T scalar, const FakeVector4<T> &v)
	{
	return v * scalar;
	}

template<typename T>
inline FakeVector4<T> operator/(T scalar, const FakeVector4<T> &v)
	{
	return FakeVector4<T>(scalar) / v;
	}

typedef FakeVector4<double> FakeVec4d;
typedef FakeVector4<float> FakeVec4f;
typedef FakeVector4<int32> FakeVec4i;
typedef FakeVector4<short> FakeVec4s;
typedef FakeVector4<long> FakeVec4l;
typedef FakeVector4<bool> FakeVec4b;

