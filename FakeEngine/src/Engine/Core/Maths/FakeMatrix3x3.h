/*****************************************************************
 * \file   FakeMatrix3x3.h
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
struct FakeQuaternion;

template<typename T>
struct FakeMatrix3x3
	{
	union
		{
		struct
			{
			T M11;
			T M12;
			T M13;

			T M21;
			T M22;
			T M23;

			T M31;
			T M32;
			T M33;
			};

		T Raw[9];
		T Values[3][3];
		};

	static const FakeMatrix3x3 Zero;
	static const FakeMatrix3x3 Identity;

	FakeMatrix3x3()
		{
		M11 = static_cast<T>(0);
		M12 = static_cast<T>(0);
		M13 = static_cast<T>(0);

		M21 = static_cast<T>(0);
		M22 = static_cast<T>(0);
		M23 = static_cast<T>(0);

		M31 = static_cast<T>(0);
		M32 = static_cast<T>(0);
		M33 = static_cast<T>(0);
		}

	FakeMatrix3x3(T value)
		{
		M11 = value;
		M12 = static_cast<T>(0);
		M13 = static_cast<T>(0);

		M21 = static_cast<T>(0);
		M22 = value;
		M23 = static_cast<T>(0);

		M31 = static_cast<T>(0);
		M32 = static_cast<T>(0);
		M33 = value;
		}

	FakeMatrix3x3(T m11, T m12, T m13, T m21, T m22, T m23, T m31, T m32, T m33)
		{
		M11 = m11;
		M12 = m12;
		M13 = m13;

		M21 = m21;
		M22 = m22;
		M23 = m23;

		M31 = m31;
		M32 = m32;
		M33 = m33;
		}

	FakeMatrix3x3(T values[9])
		{
		M11 = values[0];
		M12 = values[1];
		M13 = values[2];

		M21 = values[3];
		M22 = values[4];
		M23 = values[5];

		M31 = values[6];
		M32 = values[7];
		M33 = values[8];
		}

	FakeMatrix3x3(T values[3][3])
		{
		M11 = values[0][0];
		M12 = values[1][0];
		M13 = values[2][0];

		M21 = values[0][1];
		M22 = values[1][1];
		M23 = values[2][1];

		M31 = values[0][2];
		M32 = values[1][2];
		M33 = values[2][2];
		}

	FakeMatrix3x3(const FakeVector3<T> &v1, const FakeVector3<T> &v2, const FakeVector3<T> &v3)
		{
		M11 = v1.X;
		M12 = v1.Y;
		M13 = v1.Z;

		M21 = v2.X;
		M22 = v2.Y;
		M23 = v2.Z;

		M31 = v3.X;
		M32 = v3.Y;
		M33 = v3.Z;
		}

	FakeMatrix3x3(const FakeVector3<T> &v1, const FakeVector3<T> &v2, T m31, T m32, T m33)
		{
		M11 = v1.X;
		M12 = v1.Y;
		M13 = v1.Z;

		M21 = v2.X;
		M22 = v2.Y;
		M23 = v2.Z;

		M31 = m31;
		M32 = m32;
		M33 = m33;
		}

	FakeMatrix3x3(const FakeVector3<T> &v1, T m21, T m22, T m23, T m31, T m32, T m33)
		{
		M11 = v1.X;
		M12 = v1.Y;
		M13 = v1.Z;

		M21 = m21;
		M22 = m22;
		M23 = m23;

		M31 = m31;
		M32 = m32;
		M33 = m33;
		}

	FakeMatrix3x3(const FakeMatrix2x2<T> &other)
		{
		M11 = other.M11;
		M12 = other.M12;
		M13 = static_cast<T>(0);

		M21 = other.M21;
		M22 = other.M22;
		M23 = static_cast<T>(0);

		M31 = static_cast<T>(0);
		M32 = static_cast<T>(0);
		M33 = static_cast<T>(1);
		}

	FakeMatrix3x3(const FakeMatrix3x3 &other)
		{
		M11 = other.M11;
		M12 = other.M12;
		M13 = other.M13;

		M21 = other.M21;
		M22 = other.M22;
		M23 = other.M23;

		M31 = other.M31;
		M32 = other.M32;
		M33 = other.M33;
		}

	FakeString ToString() const
		{
		FakeString result;
		result << M11 << ", " << M12 << ", " << M13 << ",\n";
		result << M21 << ", " << M22 << ", " << M23 << ",\n";
		result << M31 << ", " << M32 << ", " << M33;
		return result;
		}

	void SetRow(const FakeVector3<T> &values, uint32 index = 0)
		{
		if (index == 0)
			{
			M11 = values.X;
			M12 = values.Y;
			M13 = values.Z;
			}
		else if (index == 1)
			{
			M21 = values.X;
			M22 = values.Y;
			M23 = values.Z;
			}
		else if (index == 2)
			{
			M31 = values.X;
			M32 = values.Y;
			M33 = values.Z;
			}
		}

	void SetColumn(const FakeVector3<T> &values, uint32 index = 0)
		{
		if (index == 0)
			{
			M11 = values.X;
			M21 = values.Y;
			M31 = values.Z;
			}
		else if (index == 1)
			{
			M12 = values.X;
			M22 = values.Y;
			M32 = values.Z;
			}
		else if (index == 2)
			{
			M13 = values.X;
			M23 = values.Y;
			M33 = values.Z;
			}
		}

	FakeVector3<T> GetRow(uint32 index = 0)
		{
		if (index == 0)
			{
			return FakeVector3<T>(M11, M12, M13);
			}
		else if (index == 1)
			{
			return FakeVector3<T>(M21, M22, M23);
			}
		else if (index == 2)
			{
			return FakeVector3<T>(M31, M32, M33);
			}

		return FakeVector3<T>(static_cast<T>(0));
		}

	FakeVector3<T> GetColumn(uint32 index = 0)
		{
		if (index == 0)
			{
			return FakeVector3<T>(M11, M21, M31);
			}
		else if (index == 1)
			{
			return FakeVector3<T>(M12, M22, M32);
			}
		else if (index == 2)
			{
			return FakeVector3<T>(M13, M23, M33);
			}

		return FakeVector3<T>(static_cast<T>(0));
		}

	void SetScaleVector(const FakeVector3<T> &values)
		{
		M11 = values.X;
		M22 = values.Y;
		M33 = values.Z;
		}

	FakeVector3<T> GetScaleVector() const
		{
		return FakeVector3<T>(M11, M22, M33);
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
		return (M11 * M22 * M33) + (M12 * M23 * M31) + (M13 * M21 * M32) - (M13 * M22 * M31) - (M12 * M21 * M33) - (M11 * M23 * M32);
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

	static void Inverse(const FakeMatrix3x3 &m, FakeMatrix3x3 &result)
		{
		const T d11 = m.M22 * m.M33 + m.M23 * -m.M32;
		const T d12 = m.M21 * m.M33 + m.M23 * -m.M31;
		const T d13 = m.M21 * m.M32 + m.M22 * -m.M31;

		T det = m.M11 * d11 - m.M12 * d12 + m.M13 * d13;
		if (FAKE_ABS(det) < FAKE_ZERO_TOLERANCE)
			{
			result = Zero;
			return;
			}

		det = static_cast<T>(1) / det;

		const T d21 = m.M12 * m.M33 + m.M13 * -m.M32;
		const T d22 = m.M11 * m.M33 + m.M13 * -m.M31;
		const T d23 = m.M11 * m.M32 + m.M12 * -m.M31;

		const T d31 = m.M12 * m.M23 - m.M13 * m.M22;
		const T d32 = m.M11 * m.M23 - m.M13 * m.M21;
		const T d33 = m.M11 * m.M22 - m.M12 * m.M21;

		result.M11 = +d11 * det;
		result.M12 = -d21 * det;
		result.M13 = +d31 * det;

		result.M21 = -d12 * det;
		result.M22 = +d22 * det;
		result.M23 = -d32 * det;

		result.M31 = +d13 * det;
		result.M32 = -d23 * det;
		result.M33 = +d33 * det;
		}

	static FakeMatrix3x3 Inverse(const FakeMatrix3x3 &m)
		{
		FakeMatrix3x3 result;
		Inverse(m, result);
		return result;
		}

	static void Transpose(const FakeMatrix3x3 &m, FakeMatrix3x3 &result)
		{
		result.M11 = m.M11;
		result.M12 = m.M21;
		result.M13 = m.M31;

		result.M21 = m.M12;
		result.M22 = m.M22;
		result.M23 = m.M32;

		result.M31 = m.M13;
		result.M32 = m.M23;
		result.M33 = m.M33;
		}

	static FakeMatrix3x3 Transpose(const FakeMatrix3x3 &m)
		{
		FakeMatrix3x3 result;
		Transpose(m, result);
		return result;
		}

	static void Negate(const FakeMatrix3x3 &m, FakeMatrix3x3 &result)
		{
		result.M11 = -m.M11;
		result.M12 = -m.M12;
		result.M13 = -m.M13;

		result.M21 = -m.M21;
		result.M22 = -m.M22;
		result.M23 = -m.M23;

		result.M31 = -m.M31;
		result.M32 = -m.M32;
		result.M33 = -m.M33;
		}

	static FakeMatrix3x3 Negate(const FakeMatrix3x3 &m)
		{
		FakeMatrix3x3 result;
		Negate(m, result);
		return result;
		}

	static void Translate2D(const FakeVector2<T> &translation, FakeMatrix3x3 &result)
		{
		result.M11 = static_cast<T>(1);
		result.M12 = static_cast<T>(0);
		result.M13 = static_cast<T>(0);

		result.M21 = static_cast<T>(0);
		result.M22 = static_cast<T>(1);
		result.M23 = static_cast<T>(0);

		result.M31 = translation.X;
		result.M32 = translation.Y;
		result.M33 = static_cast<T>(1);
		}

	static FakeMatrix3x3 Translate2D(const FakeVector2<T> &translation)
		{
		FakeMatrix3x3 result;
		Translate2D(translation, result);
		return result;
		}

	static void TransformPoint(const FakeVector2<T> &point, const FakeMatrix3x3 &transform, FakeVector2<T> &result)
		{
		result.X = point.X * transform.M11 + point.Y * transform.M21 + transform.M31;
		result.Y = point.X * transform.M12 + point.Y * transform.M22 + transform.M32;
		}

	static FakeVector2<T> TransformPoint(const FakeVector2<T> &point, const FakeMatrix3x3 &transform)
		{
		FakeVector2<T> result;
		TransformPoint(point, transform, result);
		return result;
		}

	static void TransformVector(const FakeVector2<T> &vector, const FakeMatrix3x3 &transform, FakeVector2<T> &result)
		{
		result.X = vector.X * transform.M11 + vector.Y * transform.M21;
		result.Y = vector.X * transform.M12 + vector.Y * transform.M22;
		}

	static FakeVector2<T> TransformVector(const FakeVector2<T> &vector, const FakeMatrix3x3 &transform)
		{
		FakeVector2<T> result;
		TransformVector(vector, transform, result);
		return result;
		}

	static void Rotate(const FakeQuaternion<T> &rotation, FakeMatrix3x3 &result)
		{
		const T xx = rotation.X * rotation.X;
		const T yy = rotation.Y * rotation.Y;
		const T zz = rotation.Z * rotation.Z;
		const T xy = rotation.X * rotation.Y;
		const T zw = rotation.Z * rotation.W;
		const T zx = rotation.Z * rotation.X;
		const T yw = rotation.Y * rotation.W;
		const T yz = rotation.Y * rotation.Z;
		const T xw = rotation.X * rotation.W;

		result.M11 = static_cast<T>(1) - static_cast<T>(2) * (yy + zz);
		result.M12 = static_cast<T>(2) * (xy + zw);
		result.M13 = static_cast<T>(2) * (zx - yw);

		result.M21 = static_cast<T>(2) * (xy - zw);
		result.M22 = static_cast<T>(1) - static_cast<T>(2) * (zz + xx);
		result.M23 = static_cast<T>(2) * (yz + xw);

		result.M31 = static_cast<T>(2) * (zx + yw);
		result.M32 = static_cast<T>(2) * (yz - xw);
		result.M33 = static_cast<T>(1) - static_cast<T>(2) * (yy + xx);
		}

	static FakeMatrix3x3 Rotate(const FakeQuaternion<T> &rotation)
		{
		FakeMatrix3x3 result;
		Rotate(rotation, result);
		return result;
		}

	static void Add(const FakeMatrix3x3 &a, const FakeMatrix3x3 &b, FakeMatrix3x3 &result)
		{
		result.M11 = a.M11 + b.M11;
		result.M12 = a.M12 + b.M12;
		result.M13 = a.M13 + b.M13;

		result.M21 = a.M21 + b.M21;
		result.M22 = a.M22 + b.M22;
		result.M23 = a.M23 + b.M23;

		result.M31 = a.M31 + b.M31;
		result.M32 = a.M32 + b.M32;
		result.M33 = a.M33 + b.M33;
		}

	static void Subtract(const FakeMatrix3x3 &a, const FakeMatrix3x3 &b, FakeMatrix3x3 &result)
		{
		result.M11 = a.M11 - b.M11;
		result.M12 = a.M12 - b.M12;
		result.M13 = a.M13 - b.M13;

		result.M21 = a.M21 - b.M21;
		result.M22 = a.M22 - b.M22;
		result.M23 = a.M23 - b.M23;

		result.M31 = a.M31 - b.M31;
		result.M32 = a.M32 - b.M32;
		result.M33 = a.M33 - b.M33;
		}

	static void Multiply(const FakeMatrix3x3 &a, const FakeMatrix3x3 &b, FakeMatrix3x3 &result)
		{
		result.M11 = a.M11 * b.M11 + a.M12 * b.M21 + a.M13 * b.M31;
		result.M12 = a.M11 * b.M12 + a.M12 * b.M22 + a.M13 * b.M32;
		result.M13 = a.M11 * b.M13 + a.M12 * b.M23 + a.M13 * b.M33;

		result.M21 = a.M21 * b.M11 + a.M22 * b.M21 + a.M23 * b.M31;
		result.M22 = a.M21 * b.M12 + a.M22 * b.M22 + a.M23 * b.M32;
		result.M23 = a.M21 * b.M13 + a.M22 * b.M23 + a.M23 * b.M33;

		result.M31 = a.M31 * b.M11 + a.M32 * b.M21 + a.M33 * b.M31;
		result.M32 = a.M31 * b.M12 + a.M32 * b.M22 + a.M33 * b.M32;
		result.M33 = a.M31 * b.M13 + a.M32 * b.M23 + a.M33 * b.M33;
		}

	static void Multiply(const FakeMatrix3x3 &a, T b, FakeMatrix3x3 &result)
		{
		result.M11 = a.M11 * b;
		result.M12 = a.M12 * b;
		result.M13 = a.M13 * b;

		result.M21 = a.M21 * b;
		result.M22 = a.M22 * b;
		result.M23 = a.M23 * b;

		result.M31 = a.M31 * b;
		result.M32 = a.M32 * b;
		result.M33 = a.M33 * b;
		}

	static void Divide(const FakeMatrix3x3 &a, const FakeMatrix3x3 &b, FakeMatrix3x3 &result)
		{
		FakeMatrix3x3 invertedB;
		FakeMatrix3x3::Inverse(b, invertedB);

		result.M11 = a.M11 * invertedB.M11 + a.M12 * invertedB.M21 + a.M13 * invertedB.M31;
		result.M12 = a.M11 * invertedB.M12 + a.M12 * invertedB.M22 + a.M13 * invertedB.M32;
		result.M13 = a.M11 * invertedB.M13 + a.M12 * invertedB.M23 + a.M13 * invertedB.M33;

		result.M21 = a.M21 * invertedB.M11 + a.M22 * invertedB.M21 + a.M23 * invertedB.M31;
		result.M22 = a.M21 * invertedB.M12 + a.M22 * invertedB.M22 + a.M23 * invertedB.M32;
		result.M23 = a.M21 * invertedB.M13 + a.M22 * invertedB.M23 + a.M23 * invertedB.M33;

		result.M31 = a.M31 * invertedB.M11 + a.M32 * invertedB.M21 + a.M33 * invertedB.M31;
		result.M32 = a.M31 * invertedB.M12 + a.M32 * invertedB.M22 + a.M33 * invertedB.M32;
		result.M33 = a.M31 * invertedB.M13 + a.M32 * invertedB.M23 + a.M33 * invertedB.M33;
		}

	static void Divide(const FakeMatrix3x3 &a, T b, FakeMatrix3x3 &result)
		{
		if (b > FAKE_ZERO_TOLERANCE)
			{
			result.M11 = a.M11 / b;
			result.M12 = a.M12 / b;
			result.M13 = a.M13 / b;

			result.M21 = a.M21 / b;
			result.M22 = a.M22 / b;
			result.M23 = a.M23 / b;

			result.M31 = a.M31 / b;
			result.M32 = a.M32 / b;
			result.M33 = a.M33 / b;
			}
		else
			{
			result = Zero;
			}
		}

	static FakeMatrix3x3 Add(const FakeMatrix3x3 &a, const FakeMatrix3x3 &b)
		{
		FakeMatrix3x3 result;
		Add(a, b, result);
		return result;
		}

	static FakeMatrix3x3 Subtract(const FakeMatrix3x3 &a, const FakeMatrix3x3 &b)
		{
		FakeMatrix3x3 result;
		Subtract(a, b, result);
		return result;
		}

	static FakeMatrix3x3 Multiply(const FakeMatrix3x3 &a, const FakeMatrix3x3 &b)
		{
		FakeMatrix3x3 result;
		Multiply(a, b, result);
		return result;
		}

	static FakeMatrix3x3 Divide(const FakeMatrix3x3 &a, const FakeMatrix3x3 &b)
		{
		FakeMatrix3x3 result;
		Divide(a, b, result);
		return result;
		}

	static FakeMatrix3x3 Multiply(const FakeMatrix3x3 &a, T b)
		{
		FakeMatrix3x3 result;
		Multiply(a, b, result);
		return result;
		}

	static FakeMatrix3x3 Divide(const FakeMatrix3x3 &a, T b)
		{
		FakeMatrix3x3 result;
		Divide(a, b, result);
		return result;
		}

	bool operator==(const FakeMatrix3x3 &other) const
		{
		return M11 == other.M11
			&& M12 == other.M12
			&& M13 == other.M13
			&& M21 == other.M21
			&& M22 == other.M22
			&& M23 == other.M23
			&& M31 == other.M31
			&& M32 == other.M32
			&& M33 == other.M33;
		}

	bool operator!=(const FakeMatrix3x3 &other) const
		{
		return !(*this == other);
		}

	bool operator<(const FakeMatrix3x3 &other) const
		{
		return M11 < other.M11
			&&M12 < other.M12
			&&M13 < other.M13
			&&M21 < other.M21
			&&M22 < other.M22
			&&M23 < other.M23
			&&M31 < other.M31
			&&M32 < other.M32
			&&M33 < other.M33;
		}

	bool operator<=(const FakeMatrix3x3 &other) const
		{
		return M11 <= other.M11
			&& M12 <= other.M12
			&& M13 <= other.M13
			&& M21 <= other.M21
			&& M22 <= other.M22
			&& M23 <= other.M23
			&& M31 <= other.M31
			&& M32 <= other.M32
			&& M33 <= other.M33;
		}

	bool operator>(const FakeMatrix3x3 &other) const
		{
		return M11 > other.M11
			&& M12 > other.M12
			&& M13 > other.M13
			&& M21 > other.M21
			&& M22 > other.M22
			&& M23 > other.M23
			&& M31 > other.M31
			&& M32 > other.M32
			&& M33 > other.M33;
		}

	bool operator>=(const FakeMatrix3x3 &other) const
		{
		return M11 >= other.M11
			&& M12 >= other.M12
			&& M13 >= other.M13
			&& M21 >= other.M21
			&& M22 >= other.M22
			&& M23 >= other.M23
			&& M31 >= other.M31
			&& M32 >= other.M32
			&& M33 >= other.M33;
		}

	FakeMatrix3x3 operator-() const
		{
		return FakeMatrix3x3(-M11, -M12, -M13, -M21, -M22, -M23, -M31, -M32, -M33);
		}

	FakeMatrix3x3 operator+(const FakeMatrix3x3 &other) const
		{
		FakeMatrix3x3 result;
		Add(*this, other, result);
		return result;
		}

	FakeMatrix3x3 operator-(const FakeMatrix3x3 &other) const
		{
		FakeMatrix3x3 result;
		Subtract(*this, other, result);
		return result;
		}

	FakeMatrix3x3 operator*(const FakeMatrix3x3 &other) const
		{
		FakeMatrix3x3 result;
		Multiply(*this, other, result);
		return result;
		}

	FakeMatrix3x3 operator/(const FakeMatrix3x3 &other) const
		{
		FakeMatrix3x3 result;
		Divide(*this, other, result);
		return result;
		}

	FakeMatrix3x3 operator*(T scalar) const
		{
		FakeMatrix3x3 result;
		Multiply(*this, scalar, result);
		return result;
		}

	FakeMatrix3x3 operator/(T scalar) const
		{
		FakeMatrix3x3 result;
		Divide(*this, scalar, result);
		return result;
		}

	FakeMatrix3x3 &operator+=(const FakeMatrix3x3 &other)
		{
		Add(*this, other, *this);
		return *this;
		}

	FakeMatrix3x3 &operator-=(const FakeMatrix3x3 &other)
		{
		Subtract(*this, other, *this);
		return *this;
		}

	FakeMatrix3x3 &operator*=(const FakeMatrix3x3 &other)
		{
		Multiply(*this, other, *this);
		return *this;
		}

	FakeMatrix3x3 &operator/=(const FakeMatrix3x3 &other)
		{
		Divide(*this, other, *this);
		return *this;
		}

	FakeMatrix3x3 &operator*=(T scalar)
		{
		Multiply(*this, scalar, *this);
		return *this;
		}

	FakeMatrix3x3 &operator/=(T scalar)
		{
		Divide(*this, scalar, *this);
		return *this;
		}

	FakeMatrix3x3 &operator++(int)
		{
		++M11;
		++M12;
		++M13;
		++M21;
		++M22;
		++M23;
		++M31;
		++M32;
		++M33;
		return *this;
		}

	FakeMatrix3x3 &operator--(int)
		{
		--M11;
		--M12;
		--M13;
		--M21;
		--M22;
		--M23;
		--M31;
		--M32;
		--M33;
		return *this;
		}

	FakeMatrix3x3 &operator=(const FakeMatrix3x3 &other)
		{
		M11 = other.M11;
		M12 = other.M12;
		M13 = other.M13;

		M21 = other.M21;
		M22 = other.M22;
		M23 = other.M23;

		M31 = other.M31;
		M32 = other.M32;
		M33 = other.M33;
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
		if (index > 0 && index < 9)
			{
			return Raw[index];
			}

		// Index out of bounds, return -1
		static T falseVal = static_cast<T>(-1);
		return falseVal;
		}

	const T &operator[](uint32 index) const
		{
		if (index > 0 && index < 9)
			{
			return Raw[index];
			}

		// Index out of bounds, return -1
		static T falseVal = static_cast<T>(-1);
		return falseVal;
		}

	friend std::ostream &operator<<(std::ostream &stream, const FakeMatrix3x3 &m)
		{
		stream << m.M11 << ", " << m.M12 << ", " << m.M13 << ",\n";
		stream << m.M21 << ", " << m.M22 << ", " << m.M23 << ",\n";
		stream << m.M31 << ", " << m.M32 << ", " << m.M33;
		return stream;
		}
	};

template<typename T>
const FakeMatrix3x3<T> FakeMatrix3x3<T>::Zero(static_cast<T>(0));

template<typename T>
const FakeMatrix3x3<T> FakeMatrix3x3<T>::Identity(static_cast<T>(1));

typedef FakeMatrix3x3<double> FakeMat3d;
typedef FakeMatrix3x3<float> FakeMat3f;
typedef FakeMatrix3x3<int32> FakeMat3i;
typedef FakeMatrix3x3<long> FakeMat3l;
typedef FakeMatrix3x3<short> FakeMat3s;
typedef FakeMatrix3x3<bool> FakeMat3b;

