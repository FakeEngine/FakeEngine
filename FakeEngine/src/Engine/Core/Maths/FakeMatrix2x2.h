/*****************************************************************
 * \file   FakeMatrix2x2.h
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
#include "FakeVector2.h"
#include "FakeVector3.h"
#include "FakeVector4.h"

template<typename T>
struct FakeMatrix2x2
	{
	union
		{
		struct
			{
			T M11;
			T M12;
			T M21;
			T M22;
			};

		T Raw[4];
		T Values[2][2];
		};

	static const FakeMatrix2x2 Zero;
	static const FakeMatrix2x2 Identity;

	FakeMatrix2x2()
		{
		M11 = static_cast<T>(0);
		M12 = static_cast<T>(0);
		M21 = static_cast<T>(0);
		M22 = static_cast<T>(0);
		}

	FakeMatrix2x2(T value)
		{
		M11 = value;
		M12 = static_cast<T>(0);
		M21 = static_cast<T>(0);
		M22 = value;
		}

	FakeMatrix2x2(T m11, T m12, T m21, T m22)
		{
		M11 = m11;
		M12 = m12;
		M21 = m21;
		M22 = m22;
		}

	FakeMatrix2x2(T values[4])
		{
		M11 = values[0];
		M12 = values[1];
		M21 = values[2];
		M22 = values[3];
		}

	FakeMatrix2x2(T values[2][2])
		{
		M11 = values[0][0];
		M12 = values[1][0];
		M21 = values[0][1];
		M22 = values[1][1];
		}

	FakeMatrix2x2(const FakeVector2<T> &v1, const FakeVector2<T> &v2)
		{
		M11 = v1.X;
		M12 = v1.Y;
		M21 = v2.X;
		M22 = v2.Y;
		}

	FakeMatrix2x2(const FakeVector2<T> &v)
		{
		M11 = v.X;
		M12 = static_cast<T>(0);
		M21 = static_cast<T>(0);
		M22 = v.Y;
		}

	FakeMatrix2x2(const FakeVector3<T> &v)
		{
		M11 = v.X;
		M12 = static_cast<T>(0);
		M21 = static_cast<T>(0);
		M22 = v.Y;
		}

	FakeMatrix2x2(const FakeVector2<T> &v, T m21, T m22)
		{
		M11 = v.X;
		M12 = v.Y;
		M21 = m21;
		M22 = m22;
		}

	FakeMatrix2x2(const FakeVector3<T> &v, T m22)
		{
		M11 = v.X;
		M12 = v.Y;
		M21 = v.Z;
		M22 = m22;
		}

	FakeMatrix2x2(const FakeVector4<T> &v)
		{
		M11 = v.X;
		M12 = v.Y;
		M21 = v.Z;
		M22 = v.W;
		}

	FakeMatrix2x2(const FakeMatrix2x2 &other)
		{
		M11 = other.M11;
		M12 = other.M12;
		M21 = other.M21;
		M22 = other.M22;
		}

	FakeString ToString() const
		{
		FakeString result;
		result << M11 << ", " << M12 << ",\n";
		result << M21 << ", " << M22;
		return result;
		}

	void SetRow(const FakeVector2<T> &values, uint32 index = 0)
		{
		if (index == 0)
			{
			M11 = values.X;
			M12 = values.Y;
			}
		else if (index == 1)
			{
			M21 = values.X;
			M22 = values.Y;
			}
		}

	void SetColumn(const FakeVector2<T> &values, uint32 index = 0)
		{
		if (index == 0)
			{
			M11 = values.X;
			M21 = values.Y;
			}
		else if (index == 1)
			{
			M12 = values.X;
			M22 = values.Y;
			}
		}

	FakeVector2<T> GetRow(uint32 index = 0)
		{
		if (index == 0)
			{
			return FakeVector2<T>(M11, M12);
			}
		else if (index == 1)
			{
			return FakeVector2<T>(M21, M22);
			}

		return FakeVector2<T>(static_cast<T>(0));
		}

	FakeVector2<T> GetColumn(uint32 index = 0)
		{
		if (index == 0)
			{
			return FakeVector2<T>(M11, M21);
			}
		else if (index == 1)
			{
			return FakeVector2<T>(M12, M22);
			}

		return FakeVector2<T>(static_cast<T>(0));
		}

	bool IsZero() const
		{
		return *this == Zero;
		}

	bool IsIdentity() const
		{
		return *this == Identity;
		}

	T GetDeterminant() const
		{
		return (M11 * M22) - (M12 * M21);
		}

	void Inverse()
		{
		Inverse(*this, *this);
		}

	void Transpose()
		{
		Transpose(*this, *this);
		}

	void Negate()
		{
		Negate(*this, *this);
		}

	static void Inverse(const FakeMatrix2x2 &m, FakeMatrix2x2 &result)
		{
		T determinant = (m.M11 * m.M22) - (m.M12 * m.M21);
		if (FAKE_ABS(determinant) < FAKE_ZERO_TOLERANCE)
			{
			result = Zero;
			return;
			}

		T invDet = static_cast<T>(1) / determinant;
		result.M11 = +m.M22 * invDet;
		result.M12 = -m.M12 * invDet;
		result.M21 = -m.M21 * invDet;
		result.M22 = +m.M11 * invDet;
		}

	static FakeMatrix2x2 Inverse(const FakeMatrix2x2 &m)
		{
		FakeMatrix2x2 result;
		Inverse(m, result);
		return result;
		}

	static void Transpose(const FakeMatrix2x2 &m, FakeMatrix2x2 &result)
		{
		result.M11 = m.M11;
		result.M12 = m.M21;
		result.M21 = m.M12;
		result.M22 = m.M22;
		}

	static FakeMatrix2x2 Transpose(const FakeMatrix2x2 &m)
		{
		FakeMatrix2x2 result;
		Transpose(m, result);
		return result;
		}

	static void Negate(const FakeMatrix2x2 &m, FakeMatrix2x2 &result)
		{
		result.M11 = -m.M11;
		result.M12 = -m.M12;
		result.M21 = -m.M21;
		result.M22 = -m.M22;
		}

	static FakeMatrix2x2 Negate(const FakeMatrix2x2 &m)
		{
		FakeMatrix2x2 result;
		Negate(m, result);
		return result;
		}

	static void Add(const FakeMatrix2x2 &a, const FakeMatrix2x2 &b, FakeMatrix2x2 &result)
		{
		result.M11 = a.M11 + b.M11;
		result.M12 = a.M12 + b.M12;
		result.M21 = a.M21 + b.M21;
		result.M22 = a.M22 + b.M22;
		}

	static void Subtract(const FakeMatrix2x2 &a, const FakeMatrix2x2 &b, FakeMatrix2x2 &result)
		{
		result.M11 = a.M11 - b.M11;
		result.M12 = a.M12 - b.M12;
		result.M21 = a.M21 - b.M21;
		result.M22 = a.M22 - b.M22;
		}

	static void Multiply(const FakeMatrix2x2 &a, const FakeMatrix2x2 &b, FakeMatrix2x2 &result)
		{
		result.M11 = a.M11 * b.M11;
		result.M12 = a.M12 * b.M21;
		result.M21 = a.M21 * b.M12;
		result.M22 = a.M22 * b.M22;
		}

	static void Multiply(const FakeMatrix2x2 &a, T b, FakeMatrix2x2 &result)
		{
		result.M11 = a.M11 * b;
		result.M12 = a.M12 * b;
		result.M21 = a.M21 * b;
		result.M22 = a.M22 * b;
		}

	static void Divide(const FakeMatrix2x2 &a, const FakeMatrix2x2 &b, FakeMatrix2x2 &result)
		{
		// build Inverse of b and multiply
		FakeMatrix2x2 invertedB;
		FakeMatrix2x2::Inverse(b, invertedB);

		result.M11 = a.M11 * invertedB.M11;
		result.M12 = a.M12 * invertedB.M21;
		result.M21 = a.M21 * invertedB.M12;
		result.M22 = a.M22 * invertedB.M22;
		}

	static void Divide(const FakeMatrix2x2 &a, T b, FakeMatrix2x2 &result)
		{
		if (b > FAKE_ZERO_TOLERANCE)
			{
			result.M11 = a.M11 / b;
			result.M12 = a.M12 / b;
			result.M21 = a.M21 / b;
			result.M22 = a.M22 / b;
			}
		else
			{
			result = Zero;
			}
		}

	static FakeMatrix2x2 Add(const FakeMatrix2x2 &a, const FakeMatrix2x2 &b)
		{
		FakeMatrix2x2 result;
		Add(a, b, result);
		return  result;
		}

	static FakeMatrix2x2 Subtract(const FakeMatrix2x2 &a, const FakeMatrix2x2 &b)
		{
		FakeMatrix2x2 result;
		Subtract(a, b, result);
		return  result;
		}

	static FakeMatrix2x2 Multiply(const FakeMatrix2x2 &a, const FakeMatrix2x2 &b)
		{
		FakeMatrix2x2 result;
		Multiply(a, b, result);
		return  result;
		}

	static FakeMatrix2x2 Divide(const FakeMatrix2x2 &a, const FakeMatrix2x2 &b)
		{
		FakeMatrix2x2 result;
		Divide(a, b, result);
		return  result;
		}

	static FakeMatrix2x2 Multiply(const FakeMatrix2x2 &a, T b)
		{
		FakeMatrix2x2 result;
		Multiply(a, b, result);
		return  result;
		}

	static FakeMatrix2x2 Divide(const FakeMatrix2x2 &a, T b)
		{
		FakeMatrix2x2 result;
		Divide(a, b, result);
		return  result;
		}

	bool operator==(const FakeMatrix2x2 &other) const
		{
		return M11 == other.M11
			&& M12 == other.M12
			&& M21 == other.M21
			&& M22 == other.M22;
		}

	bool operator!=(const FakeMatrix2x2 &other) const
		{
		return !(*this == other);
		}

	bool operator<(const FakeMatrix2x2 &other) const
		{
		return M11 < other.M11
			&&M12 < other.M12
			&&M21 < other.M21
			&&M22 < other.M22;
		}

	bool operator<=(const FakeMatrix2x2 &other) const
		{
		return M11 <= other.M11
			&& M12 <= other.M12
			&& M21 <= other.M21
			&& M22 <= other.M22;
		}

	bool operator>(const FakeMatrix2x2 &other) const
		{
		return M11 > other.M11
			&& M12 > other.M12
			&& M21 > other.M21
			&& M22 > other.M22;
		}

	bool operator>=(const FakeMatrix2x2 &other) const
		{
		return M11 >= other.M11
			&& M12 >= other.M12
			&& M21 >= other.M21
			&& M22 >= other.M22;
		}

	FakeMatrix2x2 operator-() const
		{
		return FakeMatrix2x2(-M11, -M12, -M21, -M22);
		}

	FakeMatrix2x2 operator+(const FakeMatrix2x2 &other) const
		{
		FakeMatrix2x2 result;
		Add(*this, other, result);
		return result;
		}

	FakeMatrix2x2 operator-(const FakeMatrix2x2 &other) const
		{
		FakeMatrix2x2 result;
		Subtract(*this, other, result);
		return result;
		}

	FakeMatrix2x2 operator*(const FakeMatrix2x2 &other) const
		{
		FakeMatrix2x2 result;
		Multiply(*this, other, result);
		return result;
		}

	FakeMatrix2x2 operator/(const FakeMatrix2x2 &other) const
		{
		FakeMatrix2x2 result;
		Divide(*this, other, result);
		return result;
		}

	FakeMatrix2x2 operator*(T scalar) const
		{
		FakeMatrix2x2 result;
		Multiply(*this, scalar, result);
		return result;
		}

	FakeMatrix2x2 operator/(T scalar) const
		{
		FakeMatrix2x2 result;
		Divide(*this, scalar, result);
		return result;
		}

	FakeMatrix2x2 &operator+=(const FakeMatrix2x2 &other)
		{
		Add(*this, other, *this);
		return *this;
		}

	FakeMatrix2x2 &operator-=(const FakeMatrix2x2 &other)
		{
		Subtract(*this, other, *this);
		return *this;
		}

	FakeMatrix2x2 &operator*=(const FakeMatrix2x2 &other)
		{
		Multiply(*this, other, *this);
		return *this;
		}

	FakeMatrix2x2 &operator/=(const FakeMatrix2x2 &other)
		{
		Divide(*this, other, *this);
		return *this;
		}

	FakeMatrix2x2 &operator*=(T scalar)
		{
		Multiply(*this, scalar, *this);
		return *this;
		}

	FakeMatrix2x2 &operator/=(T scalar)
		{
		Divide(*this, scalar, *this);
		return *this;
		}

	FakeMatrix2x2 &operator++(int)
		{
		++M11;
		++M12;
		++M21;
		++M22;
		return *this;
		}

	FakeMatrix2x2 &operator--(int)
		{
		--M11;
		--M12;
		--M21;
		--M22;
		return *this;
		}

	FakeMatrix2x2 &operator=(const FakeMatrix2x2 &other)
		{
		M11 = other.M11;
		M12 = other.M12;
		M21 = other.M21;
		M22 = other.M22;
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
		if (index > 0 && index < 4)
			{
			return Raw[index];
			}

		// Index out of bounds, return -1
		static T falseVal = static_cast<T>(-1);
		return falseVal;
		}

	const T &operator[](uint32 index) const
		{
		if (index > 0 && index < 4)
			{
			return Raw[index];
			}

		// Index out of bounds, return -1
		static T falseVal = static_cast<T>(-1);
		return falseVal;
		}

	friend std::ostream &operator<<(std::ostream &stream, const FakeMatrix2x2 &m)
		{
		stream << m.M11 << ", " << m.M12 << ",\n";
		stream << m.M21 << ", " << m.M22;
		return stream;
		}
	};

template<typename T>
const FakeMatrix2x2<T> FakeMatrix2x2<T>::Zero(static_cast<T>(0));

template<typename T>
const FakeMatrix2x2<T> FakeMatrix2x2<T>::Identity(static_cast<T>(1));

typedef FakeMatrix2x2<double> FakeMat2d;
typedef FakeMatrix2x2<float> FakeMat2f;
typedef FakeMatrix2x2<int32> FakeMat2i;
typedef FakeMatrix2x2<short> FakeMat2s;
typedef FakeMatrix2x2<long> FakeMat2l;
typedef FakeMatrix2x2<bool> FakeMat2b;

