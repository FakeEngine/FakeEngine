/*****************************************************************
 * \file   FakeMatrix4x4.h
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
#include "FakeMatrix2x2.h"
#include "FakeMatrix3x3.h"

template<typename T>
struct FakeMatrix4x4
	{
	union
		{
		struct
			{
			T M11;
			T M12;
			T M13;
			T M14;

			T M21;
			T M22;
			T M23;
			T M24;

			T M31;
			T M32;
			T M33;
			T M34;

			T M41;
			T M42;
			T M43;
			T M44;
			};

		T Raw[16];
		T Values[4][4];
		};

	static const FakeMatrix4x4 Zero;
	static const FakeMatrix4x4 Identity;

	FakeMatrix4x4()
		{
		M11 = static_cast<T>(0);
		M12 = static_cast<T>(0);
		M13 = static_cast<T>(0);
		M14 = static_cast<T>(0);

		M21 = static_cast<T>(0);
		M22 = static_cast<T>(0);
		M23 = static_cast<T>(0);
		M24 = static_cast<T>(0);

		M31 = static_cast<T>(0);
		M32 = static_cast<T>(0);
		M33 = static_cast<T>(0);
		M34 = static_cast<T>(0);

		M41 = static_cast<T>(0);
		M42 = static_cast<T>(0);
		M43 = static_cast<T>(0);
		M44 = static_cast<T>(0);
		}

	FakeMatrix4x4(T value)
		{
		M11 = value;
		M12 = static_cast<T>(0);
		M13 = static_cast<T>(0);
		M14 = static_cast<T>(0);

		M21 = static_cast<T>(0);
		M22 = value;
		M23 = static_cast<T>(0);
		M24 = static_cast<T>(0);

		M31 = static_cast<T>(0);
		M32 = static_cast<T>(0);
		M33 = value;
		M34 = static_cast<T>(0);

		M41 = static_cast<T>(0);
		M42 = static_cast<T>(0);
		M43 = static_cast<T>(0);
		M44 = value;
		}

	FakeMatrix4x4(T m11, T m12, T m13, T m14, T m21, T m22, T m23, T m24, T m31, T m32, T m33, T m34, T m41, T m42, T m43, T m44)
		{
		M11 = m11;
		M12 = m12;
		M13 = m13;
		M14 = m14;

		M21 = m21;
		M22 = m22;
		M23 = m23;
		M24 = m24;

		M31 = m31;
		M32 = m32;
		M33 = m33;
		M34 = m34;

		M41 = m41;
		M42 = m42;
		M43 = m43;
		M44 = m44;
		}

	FakeMatrix4x4(T values[16])
		{
		M11 = values[0];
		M12 = values[1];
		M13 = values[2];
		M14 = values[3];

		M21 = values[4];
		M22 = values[5];
		M23 = values[6];
		M24 = values[7];

		M31 = values[8];
		M32 = values[9];
		M33 = values[10];
		M34 = values[11];

		M41 = values[12];
		M42 = values[13];
		M43 = values[14];
		M44 = values[15];
		}

	FakeMatrix4x4(T values[4][4])
		{
		M11 = values[0][0];
		M12 = values[1][0];
		M13 = values[2][0];
		M14 = values[3][0];

		M21 = values[0][1];
		M22 = values[1][1];
		M23 = values[2][1];
		M24 = values[3][1];

		M31 = values[0][2];
		M32 = values[1][2];
		M33 = values[2][2];
		M34 = values[3][2];

		M41 = values[0][3];
		M42 = values[1][3];
		M43 = values[2][3];
		M44 = values[3][3];
		}

	FakeMatrix4x4(const FakeVector4<T> &v)
		{
		M11 = v.X;
		M12 = static_cast<T>(0);
		M13 = static_cast<T>(0);
		M14 = static_cast<T>(0);

		M21 = static_cast<T>(0);
		M22 = v.Y;
		M23 = static_cast<T>(0);
		M24 = static_cast<T>(0);

		M31 = static_cast<T>(0);
		M32 = static_cast<T>(0);
		M33 = v.Z;
		M34 = static_cast<T>(0);

		M41 = static_cast<T>(0);
		M42 = static_cast<T>(0);
		M43 = static_cast<T>(0);
		M44 = v.W;
		}

	FakeMatrix4x4(const FakeVector4<T> &v1, const FakeVector4<T> &v2, const FakeVector4<T> &v3, const FakeVector4<T> &v4)
		{
		M11 = v1.X;
		M12 = v1.Y;
		M13 = v1.Z;
		M14 = v1.W;

		M21 = v2.X;
		M22 = v2.Y;
		M23 = v2.Z;
		M24 = v2.W;

		M31 = v3.X;
		M32 = v3.Y;
		M33 = v3.Z;
		M34 = v3.W;

		M41 = v4.X;
		M42 = v4.Y;
		M43 = v4.Z;
		M44 = v4.W;
		}

	FakeMatrix4x4(const FakeMatrix2x2<T> &other)
		{
		M11 = other.M11;
		M12 = other.M12;
		M13 = static_cast<T>(0);
		M14 = static_cast<T>(0);

		M21 = other.M21;
		M22 = other.M22;
		M23 = static_cast<T>(0);
		M24 = static_cast<T>(0);

		M31 = static_cast<T>(0);
		M32 = static_cast<T>(0);
		M33 = static_cast<T>(1);
		M34 = static_cast<T>(0);

		M41 = static_cast<T>(0);
		M42 = static_cast<T>(0);
		M43 = static_cast<T>(0);
		M44 = static_cast<T>(1);
		}

	FakeMatrix4x4(const FakeMatrix3x3<T> &other)
		{
		M11 = other.M11;
		M12 = other.M12;
		M13 = other.M13;
		M14 = static_cast<T>(0);

		M21 = other.M21;
		M22 = other.M22;
		M23 = other.M23;
		M24 = static_cast<T>(0);

		M31 = other.M31;
		M32 = other.M32;
		M33 = other.M33;
		M34 = static_cast<T>(0);

		M41 = static_cast<T>(0);
		M42 = static_cast<T>(0);
		M43 = static_cast<T>(0);
		M44 = static_cast<T>(1);
		}

	FakeMatrix4x4(const FakeMatrix4x4 &other)
		{
		M11 = other.M11;
		M12 = other.M12;
		M13 = other.M13;
		M14 = other.M14;

		M21 = other.M21;
		M22 = other.M22;
		M23 = other.M23;
		M24 = other.M24;

		M31 = other.M31;
		M32 = other.M32;
		M33 = other.M33;
		M34 = other.M34;

		M41 = other.M41;
		M42 = other.M42;
		M43 = other.M43;
		M44 = other.M44;
		}

	FakeString ToString() const
		{
		FakeString result;
		result << M11 << ", " << M12 << ", " << M13 << ", " << M14 << ",\n";
		result << M21 << ", " << M22 << ", " << M23 << ", " << M24 << ",\n";
		result << M31 << ", " << M32 << ", " << M33 << ", " << M34 << ",\n";
		result << M41 << ", " << M42 << ", " << M43 << ", " << M44;
		return result;
		}

	void SetRow(const FakeVector4<T> &values, uint32 index = 0)
		{
		if (index == 0)
			{
			M11 = values.X;
			M12 = values.Y;
			M13 = values.Z;
			M14 = values.W;
			}
		else if (index == 1)
			{
			M21 = values.X;
			M22 = values.Y;
			M23 = values.Z;
			M24 = values.W;
			}
		else if (index == 2)
			{
			M31 = values.X;
			M32 = values.Y;
			M33 = values.Z;
			M34 = values.W;
			}
		else if (index == 3)
			{
			M41 = values.X;
			M42 = values.Y;
			M43 = values.Z;
			M44 = values.W;
			}
		}

	void SetColumn(const FakeVector4<T> &values, uint32 index = 0)
		{
		if (index == 0)
			{
			M11 = values.X;
			M21 = values.Y;
			M31 = values.Z;
			M41 = values.W;
			}
		else if (index == 1)
			{
			M12 = values.X;
			M22 = values.Y;
			M32 = values.Z;
			M42 = values.W;
			}
		else if (index == 2)
			{
			M13 = values.X;
			M23 = values.Y;
			M33 = values.Z;
			M43 = values.W;
			}
		else if (index == 3)
			{
			M14 = values.X;
			M24 = values.Y;
			M34 = values.Z;
			M44 = values.W;
			}
		}

	FakeVector4<T> GetRow(uint32 index = 0)
		{
		if (index == 0)
			{
			return FakeVector4<T>(M11, M12, M13, M14);
			}
		else if (index == 1)
			{
			return FakeVector4<T>(M21, M22, M23, M24);
			}
		else if (index == 2)
			{
			return FakeVector4<T>(M31, M32, M33, M34);
			}
		else if (index == 3)
			{
			return FakeVector4<T>(M41, M42, M43, M44);
			}

		return FakeVector4<T>(static_cast<T>(0));
		}

	FakeVector4<T> GetColumn(uint32 index = 0)
		{
		if (index == 0)
			{
			return FakeVector4<T>(M11, M21, M31, M41);
			}
		else if (index == 1)
			{
			return FakeVector4<T>(M12, M22, M32, M42);
			}
		else if (index == 2)
			{
			return FakeVector4<T>(M13, M23, M33, M43);
			}
		else if (index == 3)
			{
			return FakeVector4<T>(M14, M24, M34, M44);
			}

		return FakeVector4<T>(static_cast<T>(0));
		}

	void SetUpVector(const FakeVector3<T> &value)
		{
		M21 = value.X;
		M22 = value.Y;
		M23 = value.Z;
		}

	FakeVector3<T> GetUpVector() const
		{
		return FakeVector3<T>(M21, M22, M23);
		}

	void SetDownVector(const FakeVector3<T> &value)
		{
		M21 = -value.X;
		M22 = -value.Y;
		M23 = -value.Z;
		}

	FakeVector3<T> GetDownVector() const
		{
		return FakeVector3<T>(-M21, -M22, -M23);
		}

	void SetRightVector(const FakeVector3<T> &value)
		{
		M11 = value.X;
		M12 = value.Y;
		M13 = value.Z;
		}

	FakeVector3<T> GetRightVector() const
		{
		return FakeVector3<T>(M11, M12, M13);
		}

	void SetLeftVector(const FakeVector3<T> &value)
		{
		M11 = -value.X;
		M12 = -value.Y;
		M13 = -value.Z;
		}

	FakeVector3<T> GetLeftVector() const
		{
		return FakeVector3<T>(-M11, -M12, -M13);
		}

	void SetForwardVector(const FakeVector3<T> &value)
		{
		M31 = -value.X;
		M32 = -value.Y;
		M33 = -value.Z;
		}

	FakeVector3<T> GetForwardVector() const
		{
		return FakeVector3<T>(-M31, -M32, -M33);
		}

	void SetBackwardVector(const FakeVector3<T> &value)
		{
		M31 = value.X;
		M32 = value.Y;
		M33 = value.Z;
		}

	FakeVector3<T> GetBackwardVector() const
		{
		return FakeVector3<T>(M31, M32, M33);
		}

	void SetTranslation(const FakeVector3<T> &values)
		{
		M41 = values.X;
		M42 = values.Y;
		M43 = values.Z;
		}

	FakeVector3<T> GetTranslation() const
		{
		return FakeVector3<T>(M41, M42, M43);
		}

	void SetScale(const FakeVector3<T> &values)
		{
		M11 = values.X;
		M22 = values.Y;
		M33 = values.Z;
		}

	FakeVector3<T> GetScale() const
		{
		return FakeVector3<T>(M11, M22, M33);
		}

	bool IsIdentity() const
		{
		return *this == Identity;
		}

	bool IsZero() const
		{
		return *this == Zero;
		}

	T GetDeterminant() const
		{
		const T temp1 = M33 * M44 - M34 * M43;
		const T temp2 = M32 * M44 - M34 * M42;
		const T temp3 = M32 * M43 - M33 * M42;
		const T temp4 = M31 * M44 - M34 * M41;
		const T temp5 = M31 * M43 - M33 * M41;
		const T temp6 = M31 * M42 - M32 * M41;

		return M11 * (M22 * temp1 - M23 * temp2 + M24 * temp3)
			- M12 * (M21 * temp1 - M23 * temp4 + M24 * temp5)
			+ M13 * (M21 * temp2 - M22 * temp4 + M24 * temp6)
			- M14 * (M21 * temp3 - M22 * temp5 + M23 * temp6);
		}

	T GetRotationDeterminant() const
		{
		return
			Values[0][0] * (Values[1][1] * Values[2][2] - Values[1][2] * Values[2][1]) -
			Values[1][0] * (Values[0][1] * Values[2][2] - Values[0][2] * Values[2][1]) +
			Values[2][0] * (Values[0][1] * Values[1][2] - Values[0][2] * Values[1][1]);
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

	/// Removes any scaling from the matrix by performing the normalization (each row magnitude is 1). Does not modify the 4th row with translation vector.
	void NormalizeScale()
		{
		const T scaleX = static_cast<T>(1) / FakeVector3<T>(M11, M21, M31).Length();
		const T scaleY = static_cast<T>(1) / FakeVector3<T>(M12, M22, M32).Length();
		const T scaleZ = static_cast<T>(1) / FakeVector3<T>(M13, M23, M33).Length();

		M11 *= scaleX;
		M21 *= scaleX;
		M31 *= scaleX;

		M12 *= scaleY;
		M22 *= scaleY;
		M32 *= scaleY;

		M13 *= scaleZ;
		M23 *= scaleZ;
		M33 *= scaleZ;
		}

	void Decompose(T &outYaw, T &outPitch, T &outRoll) const
		{
		outPitch = fake_asin(-M32);
		if (fake_cos(outPitch) > static_cast<T>(1e-12))
			{
			outRoll = fake_atan2(M12, M22);
			outYaw = fake_atan2(M31, M33);
			}
		else
			{
			outRoll = fake_atan2(-M21, M11);
			outYaw = static_cast<T>(0);
			}
		}

	void Decompose(FakeVector3<T> &outTranslation, FakeVector3<T> &outScale) const
		{
		// Get the translation
		outTranslation = FakeVector3<T>(M41, M42, M43);

		// Scaling is the length of the rows
		outScale = FakeVector3<T>(
			fake_sqrt(M11 * M11 + M12 * M12 + M13 * M13),
			fake_sqrt(M21 * M21 + M22 * M22 + M23 * M23),
			fake_sqrt(M31 * M31 + M32 * M32 + M33 * M33));
		}

	void Decompose(FakeVector3<T> &outTranslation, FakeQuaternion<T> &outRotation, FakeVector3<T> &outScale)
		{
		FakeMatrix4x4 rotationMatrix;
		Decompose(outTranslation, rotationMatrix, outScale);
		FakeQuaternion<T>::RotationMatrix(rotationMatrix, outRotation);
		}

	void Decompose(FakeVector3<T> &outTranslation, FakeMatrix4x4 &outRotation, FakeVector3<T> &outScale)
		{
		// Get the translation
		outTranslation = FakeVector3<T>(M41, M42, M43);

		// Scaling is the length of the rows
		outScale = FakeVector3<T>(
			fake_sqrt(M11 * M11 + M12 * M12 + M13 * M13),
			fake_sqrt(M21 * M21 + M22 * M22 + M23 * M23),
			fake_sqrt(M31 * M31 + M32 * M32 + M33 * M33));

		// If any of the scaling factors are zero, then the rotation matrix can not exist
		outRotation = Identity;
		if (outScale.IsAnyZero())
			return;

		// Calculate a perfect orthonormal matrix (no reflections)
		const auto at = FakeVector3<T>(M31 / outScale.Z, M32 / outScale.Z, M33 / outScale.Z);
		const auto up = FakeVector3<T>::Cross(at, FakeVector3<T>(M11 / outScale.X, M12 / outScale.X, M13 / outScale.X));
		const auto right = FakeVector3<T>::Cross(up, at);
		outRotation.SetRightVector(right);
		outRotation.SetUpVector(up);
		outRotation.SetBackwardVector(at);

		// In case of reflections
		outScale.X = FakeVector3<T>::Dot(right, GetRightVector()) > static_cast<T>(0) ? outScale.X : -outScale.X;
		outScale.Y = FakeVector3<T>::Dot(up, GetUpVector()) > static_cast<T>(0) ? outScale.Y : -outScale.Y;
		outScale.Z = FakeVector3<T>::Dot(at, GetBackwardVector()) > static_cast<T>(0) ? outScale.Z : -outScale.Z;
		}

	static void Inverse(const FakeMatrix4x4 &m, FakeMatrix4x4 &result)
		{
		const T b0 = m.M31 * m.M42 - m.M32 * m.M41;
		const T b1 = m.M31 * m.M43 - m.M33 * m.M41;
		const T b2 = m.M34 * m.M41 - m.M31 * m.M44;
		const T b3 = m.M32 * m.M43 - m.M33 * m.M42;
		const T b4 = m.M34 * m.M42 - m.M32 * m.M44;
		const T b5 = m.M33 * m.M44 - m.M34 * m.M43;

		const T d11 = m.M22 * b5 + m.M23 * b4 + m.M24 * b3;
		const T d12 = m.M21 * b5 + m.M23 * b2 + m.M24 * b1;
		const T d13 = m.M21 * -b4 + m.M22 * b2 + m.M24 * b0;
		const T d14 = m.M21 * b3 + m.M22 * -b1 + m.M23 * b0;

		T det = m.M11 * d11 - m.M12 * d12 + m.M13 * d13 - m.M14 * d14;
		if (FAKE_ABS(det) <= static_cast<T>(1e-12)) // Matrix is singular
			{
			result = Zero;
			return;
			}

		// Drehmatrix   Spiegel / Drehspiegelmatrix
		if (det == static_cast<T>(1) || det == static_cast<T>(-1)) // Matrix ist orthogonal
			{
			Transpose(m, result);
			return;
			}

		// Inverse of determinant
		det = static_cast<T>(1) / det;

		// Build the actual inverse matrix
		const T a0 = m.M11 * m.M22 - m.M12 * m.M21;
		const T a1 = m.M11 * m.M23 - m.M13 * m.M21;
		const T a2 = m.M14 * m.M21 - m.M11 * m.M24;
		const T a3 = m.M12 * m.M23 - m.M13 * m.M22;
		const T a4 = m.M14 * m.M22 - m.M12 * m.M24;
		const T a5 = m.M13 * m.M24 - m.M14 * m.M23;

		const T d21 = m.M12 * b5 + m.M13 * b4 + m.M14 * b3;
		const T d22 = m.M11 * b5 + m.M13 * b2 + m.M14 * b1;
		const T d23 = m.M11 * -b4 + m.M12 * b2 + m.M14 * b0;
		const T d24 = m.M11 * b3 + m.M12 * -b1 + m.M13 * b0;

		const T d31 = m.M42 * a5 + m.M43 * a4 + m.M44 * a3;
		const T d32 = m.M41 * a5 + m.M43 * a2 + m.M44 * a1;
		const T d33 = m.M41 * -a4 + m.M42 * a2 + m.M44 * a0;
		const T d34 = m.M41 * a3 + m.M42 * -a1 + m.M43 * a0;

		const T d41 = m.M32 * a5 + m.M33 * a4 + m.M34 * a3;
		const T d42 = m.M31 * a5 + m.M33 * a2 + m.M34 * a1;
		const T d43 = m.M31 * -a4 + m.M32 * a2 + m.M34 * a0;
		const T d44 = m.M31 * a3 + m.M32 * -a1 + m.M33 * a0;

		result.M11 = +d11 * det;
		result.M12 = -d21 * det;
		result.M13 = +d31 * det;
		result.M14 = -d41 * det;
		result.M21 = -d12 * det;
		result.M22 = +d22 * det;
		result.M23 = -d32 * det;
		result.M24 = +d42 * det;
		result.M31 = +d13 * det;
		result.M32 = -d23 * det;
		result.M33 = +d33 * det;
		result.M34 = -d43 * det;
		result.M41 = -d14 * det;
		result.M42 = +d24 * det;
		result.M43 = -d34 * det;
		result.M44 = +d44 * det;
		}

	static FakeMatrix4x4 Inverse(const FakeMatrix4x4 &value)
		{
		FakeMatrix4x4 result;
		Inverse(value, result);
		return result;
		}

	static void Transpose(const FakeMatrix4x4 &m, FakeMatrix4x4 &result)
		{
		result.M11 = m.M11;
		result.M12 = m.M21;
		result.M13 = m.M31;
		result.M14 = m.M41;

		result.M21 = m.M12;
		result.M22 = m.M22;
		result.M23 = m.M32;
		result.M24 = m.M42;

		result.M31 = m.M13;
		result.M32 = m.M23;
		result.M33 = m.M33;
		result.M34 = m.M43;

		result.M41 = m.M14;
		result.M42 = m.M24;
		result.M43 = m.M34;
		result.M44 = m.M44;
		}

	static FakeMatrix4x4 Transpose(const FakeMatrix4x4 &m)
		{
		FakeMatrix4x4 result;
		Transpose(*this, m, result);
		return result;
		}

	static void Negate(const FakeMatrix4x4 &m, FakeMatrix4x4 &result)
		{
		result.M11 = -m.M11;
		result.M12 = -m.M12;
		result.M13 = -m.M13;
		result.M14 = -m.M14;

		result.M21 = -m.M21;
		result.M22 = -m.M22;
		result.M23 = -m.M23;
		result.M24 = -m.M24;

		result.M31 = -m.M31;
		result.M32 = -m.M32;
		result.M33 = -m.M33;
		result.M34 = -m.M34;

		result.M41 = -m.M41;
		result.M42 = -m.M42;
		result.M43 = -m.M43;
		result.M44 = -m.M44;
		}

	static FakeMatrix4x4 Negate(const FakeMatrix4x4 &m)
		{
		FakeMatrix4x4 result;
		Negate(m, result);
		return result;
		}

	static void Lerp(const FakeMatrix4x4 &start, const FakeMatrix4x4 &end, T amount, FakeMatrix4x4 &result)
		{
		result.M11 = fake_lerp(start.M11, end.M11, amount);
		result.M12 = fake_lerp(start.M12, end.M12, amount);
		result.M13 = fake_lerp(start.M13, end.M13, amount);
		result.M14 = fake_lerp(start.M14, end.M14, amount);

		result.M21 = fake_lerp(start.M21, end.M21, amount);
		result.M22 = fake_lerp(start.M22, end.M22, amount);
		result.M23 = fake_lerp(start.M23, end.M23, amount);
		result.M24 = fake_lerp(start.M24, end.M24, amount);

		result.M31 = fake_lerp(start.M31, end.M31, amount);
		result.M32 = fake_lerp(start.M32, end.M32, amount);
		result.M33 = fake_lerp(start.M33, end.M33, amount);
		result.M34 = fake_lerp(start.M34, end.M34, amount);

		result.M41 = fake_lerp(start.M41, end.M41, amount);
		result.M42 = fake_lerp(start.M42, end.M42, amount);
		result.M43 = fake_lerp(start.M43, end.M43, amount);
		result.M44 = fake_lerp(start.M44, end.M44, amount);
		}

	static FakeMatrix4x4 Lerp(const FakeMatrix4x4 &start, const FakeMatrix4x4 &end, T amount)
		{
		FakeMatrix4x4 result;
		Lerp(start, end, amount, result);
		return result;
		}

	static void SmoothStep(const FakeMatrix4x4 &start, const FakeMatrix4x4 &end, T amount, FakeMatrix4x4 &result)
		{
		amount = fake_smooth_step(amount);
		Lerp(start, end, amount, result);
		}

	static FakeMatrix4x4 SmoothStep(const FakeMatrix4x4 &start, const FakeMatrix4x4 &end, T amount)
		{
		FakeMatrix4x4 result;
		SmoothStep(start, end, amount, result);
		return result;
		}

	static void Billboard(const FakeVector3<T> &objectPosition, const FakeVector3<T> &cameraPosition, const FakeVector3<T> &cameraUpVector, const FakeVector3<T> &cameraForwardVector, FakeMatrix4x4 &result)
		{
		FakeVector3<T> crossed;
		FakeVector3<T> final;
		FakeVector3<T> difference = cameraPosition - objectPosition;

		const T lengthSq = difference.LengthSquared();
		if (fake_is_zero(lengthSq))
			difference = -cameraForwardVector;
		else
			difference *= static_cast<T>(1) / fake_sqrt(lengthSq);

		FakeVector3<T>::Cross(cameraUpVector, difference, crossed);
		crossed.Normalize();
		FakeVector3<T>::Cross(difference, crossed, final);

		result.M11 = crossed.X;
		result.M12 = crossed.Y;
		result.M13 = crossed.Z;
		result.M14 = static_cast<T>(0);

		result.M21 = final.X;
		result.M22 = final.Y;
		result.M23 = final.Z;
		result.M24 = static_cast<T>(0);

		result.M31 = difference.X;
		result.M32 = difference.Y;
		result.M33 = difference.Z;
		result.M34 = static_cast<T>(0);

		result.M41 = objectPosition.X;
		result.M42 = objectPosition.Y;
		result.M43 = objectPosition.Z;
		result.M44 = static_cast<T>(1);
		}

	static FakeMatrix4x4 Billboard(const FakeVector3<T> &objectPosition, const FakeVector3<T> &cameraPosition, const FakeVector3<T> &cameraUpVector, const FakeVector3<T> &cameraForwardVector)
		{
		FakeMatrix4x4 result;
		Billboard(objectPosition, cameraPosition, cameraUpVector, cameraForwardVector, result);
		return result;
		}

	static void LookAt(const FakeVector3<T> &eye, const FakeVector3<T> &target, const FakeVector3<T> &up, FakeMatrix4x4 &result)
		{
		FakeVector3<T> xAxis, yAxis, zAxis;

		// calculate Z axis
		FakeVector3<T>::Subtract(target, eye, zAxis);
		zAxis.Normalize();

		// calculate X axis
		FakeVector3<T>::Cross(up, zAxis, xAxis);
		xAxis.Normalize();

		// calculate Y axis
		FakeVector3<T>::Cross(zAxis, xAxis, yAxis);

		result = Identity;

		result.M11 = xAxis.X;
		result.M21 = xAxis.Y;
		result.M31 = xAxis.Z;

		result.M12 = yAxis.X;
		result.M22 = yAxis.Y;
		result.M32 = yAxis.Z;

		result.M13 = zAxis.X;
		result.M23 = zAxis.Y;
		result.M33 = zAxis.Z;

		result.M41 = -FakeVector3<T>::Dot(xAxis, eye);
		result.M42 = -FakeVector3<T>::Dot(yAxis, eye);
		result.M43 = -FakeVector3<T>::Dot(zAxis, eye);
		}

	static FakeMatrix4x4 LookAt(const FakeVector3<T> &eye, const FakeVector3<T> &target, const FakeVector3<T> &up)
		{
		FakeMatrix4x4 result;
		LookAt(eye, target, up, result);
		return result;
		}

	static void Ortho(T width, T height, T zNear, T zFar, FakeMatrix4x4 &result)
		{
		const T halfWidth = width * static_cast<T>(0.5);
		const T halfHeight = height * static_cast<T>(0.5);
		OrthoOffCenter(-halfWidth, halfWidth, -halfHeight, halfHeight, zNear, zFar, result);
		}

	static FakeMatrix4x4 Ortho(T width, T height, T zNear, T zFar)
		{
		FakeMatrix4x4 result;
		Ortho(width, height, zNear, zFar, result);
		return result;
		}

	static void OrthoOffCenter(T left, T right, T bottom, T top, T zNear, T zFar, FakeMatrix4x4 &result)
		{
		const T zRange = static_cast<T>(1) / (zFar - zNear);

		result = Identity;
		result.M11 = static_cast<T>(2) / (right - left);
		result.M22 = static_cast<T>(2) / (top - bottom);
		result.M33 = zRange;
		result.M41 = (left + right) / (left - right);
		result.M42 = (top + bottom) / (bottom - top);
		result.M43 = -zNear * zRange;
		}

	static FakeMatrix4x4 OrthoOffCenter(T left, T right, T bottom, T top, T zNear, T zFar)
		{
		FakeMatrix4x4 result;
		OrthoOffCenter(left, right, bottom, top, zNear, zFar, result);
		return result;
		}

	static void Perspective(T width, T height, T zNear, T zFar, FakeMatrix4x4 &result)
		{
		const T halfWidth = width * static_cast<T>(0.5);
		const T halfHeight = height * static_cast<T>(0.5);
		PerspectiveOffCenter(-halfWidth, halfWidth, -halfHeight, halfHeight, zNear, zFar, result);
		}

	static FakeMatrix4x4 Perspective(T width, T height, T zNear, T zFar)
		{
		FakeMatrix4x4 result;
		Perspective(width, height, zNear, zFar, result);
		return result;
		}

	static void PerspectiveOffCenter(T left, T right, T bottom, T top, T zNear, T zFar, FakeMatrix4x4 &result)
		{
		const T zRange = zFar / (zFar - zNear);

		result = Zero;
		result.M11 = static_cast<T>(2) * zNear / (right - left);
		result.M22 = static_cast<T>(2) * zNear / (top - bottom);
		result.M31 = (left + right) / (left - right);
		result.M32 = (top + bottom) / (bottom - top);
		result.M33 = zRange;
		result.M34 = static_cast<T>(1);
		result.M43 = -zNear * zRange;
		}

	static FakeMatrix4x4 PerspectiveOffCenter(T left, T right, T bottom, T top, T zNear, T zFar)
		{
		FakeMatrix4x4 result;
		PerspectiveOffCenter(left, right, bottom, top, zNear, zFar, result);
		return result;
		}

	static void PerspectiveFOV(T fov, T aspectRatio, T zNear, T zFar, FakeMatrix4x4 &result)
		{
		const T yScale = static_cast<T>(1) / fake_tan(fov * static_cast<T>(0.5));
		const T xScale = yScale / aspectRatio;

		const T halfWidth = zNear / xScale;
		const T halfHeight = zNear / yScale;

		PerspectiveOffCenter(-halfWidth, halfWidth, -halfHeight, halfHeight, zNear, zFar, result);
		}

	static FakeMatrix4x4 PerspectiveFOV(T fov, T aspectRatio, T zNear, T zFar)
		{
		FakeMatrix4x4 result;
		PerspectiveFOV(fov, aspectRatio, zNear, zFar, result);
		return result;
		}

	static void Translate(const FakeVector3<T> &translation, FakeMatrix4x4 &result)
		{
		result = Identity;
		result.M41 = translation.X;
		result.M42 = translation.Y;
		result.M43 = translation.Z;
		}

	static FakeMatrix4x4 Translate(const FakeVector3<T> &translation)
		{
		FakeMatrix4x4 result;
		Translate(translation, result);
		return result;
		}

	static void Scale(const FakeVector3<T> &scale, FakeMatrix4x4 &result)
		{
		result = Identity;
		result.M11 = scale.X;
		result.M22 = scale.Y;
		result.M33 = scale.Z;
		}

	static FakeMatrix4x4 Scale(const FakeVector3<T> &scale)
		{
		FakeMatrix4x4 result;
		Scale(scale, result);
		return result;
		}

	static void Scale(T scale, FakeMatrix4x4 &result)
		{
		result = Identity;
		result.M11 = scale;
		result.M22 = scale;
		result.M33 = scale;
		}

	static FakeMatrix4x4 Scale(T scale)
		{
		FakeMatrix4x4 result;
		Scale(scale, result);
		return result;
		}

	static void Rotate(T angle, const FakeVector3<T> &axis, FakeMatrix4x4 &result)
		{
		const T x = axis.X;
		const T y = axis.Y;
		const T z = axis.Z;
		const T cosA = fake_cos(angle);
		const T sinA = fake_sin(angle);
		const T xx = x * x;
		const T yy = y * y;
		const T zz = z * z;
		const T xy = x * y;
		const T xz = x * z;
		const T yz = y * z;

		result = Identity;
		result.M11 = xx + cosA * (static_cast<T>(1) - xx);
		result.M12 = xy - cosA * xy + sinA * z;
		result.M13 = xz - cosA * xz - sinA * y;
		result.M21 = xy - cosA * xy - sinA * z;
		result.M22 = yy + cosA * (static_cast<T>(1) - yy);
		result.M23 = yz - cosA * yz + sinA * x;
		result.M31 = xz - cosA * xz + sinA * y;
		result.M32 = yz - cosA * yz - sinA * x;
		result.M33 = zz + cosA * (static_cast<T>(1) - zz);
		}

	static FakeMatrix4x4 Rotate(T angle, const FakeVector3<T> &axis)
		{
		FakeMatrix4x4 result;
		Rotate(angle, axis, result);
		return result;
		}

	static void Rotate(const FakeQuaternion<T> &rotation, FakeMatrix4x4 &result)
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
		result.M14 = static_cast<T>(0);

		result.M21 = static_cast<T>(2) * (xy - zw);
		result.M22 = static_cast<T>(1) - static_cast<T>(2) * (zz + xx);
		result.M23 = static_cast<T>(2) * (yz + xw);
		result.M24 = static_cast<T>(0);

		result.M31 = static_cast<T>(2) * (zx + yw);
		result.M32 = static_cast<T>(2) * (yz - xw);
		result.M33 = static_cast<T>(1) - static_cast<T>(2) * (yy + xx);
		result.M34 = static_cast<T>(0);

		result.M41 = static_cast<T>(0);
		result.M42 = static_cast<T>(0);
		result.M43 = static_cast<T>(0);
		result.M44 = static_cast<T>(1);
		}

	static FakeMatrix4x4 Rotate(const FakeQuaternion<T> &rotation)
		{
		FakeMatrix4x4 result;
		Rotate(rotation, result);
		return result;
		}

	static void Rotate(T yaw, T pitch, T roll, FakeMatrix4x4 &result)
		{
		FakeQuaternion<T> quaternion;
		FakeQuaternion<T>::RotationEuler(yaw, pitch, roll, quaternion);
		Rotate(quaternion, result);
		}

	static FakeMatrix4x4 Rotate(T yaw, T pitch, T roll)
		{
		FakeMatrix4x4 result;
		Rotate(yaw, pitch, roll, result);
		return result;
		}

	static void RotateX(T angle, FakeMatrix4x4 &result)
		{
		const T cosA = fake_cos(angle);
		const T sinA = fake_sin(angle);

		result = Identity;
		result.M22 = cosA;
		result.M23 = sinA;
		result.M32 = -sinA;
		result.M33 = cosA;
		}

	static FakeMatrix4x4 RotateX(T angle)
		{
		FakeMatrix4x4 result;
		RotateX(angle, result);
		return result;
		}

	static void RotateY(T angle, FakeMatrix4x4 &result)
		{
		const T cosA = fake_cos(angle);
		const T sinA = fake_sin(angle);

		result = Identity;
		result.M11 = cosA;
		result.M13 = -sinA;
		result.M31 = sinA;
		result.M33 = cosA;
		}

	static FakeMatrix4x4 RotateY(T angle)
		{
		FakeMatrix4x4 result;
		RotateY(angle, result);
		return result;
		}

	static void RotateZ(T angle, FakeMatrix4x4 &result)
		{
		const T cosA = fake_cos(angle);
		const T sinA = fake_sin(angle);

		result = Identity;
		result.M11 = cosA;
		result.M12 = sinA;
		result.M21 = -sinA;
		result.M22 = cosA;
		}

	static FakeMatrix4x4 RotateZ(T angle)
		{
		FakeMatrix4x4 result;
		RotateZ(angle, result);
		return result;
		}

	static void Skew(T angle, const FakeVector3<T> &translationVec, const FakeVector3<T> &rotationVec, FakeMatrix4x4 &result)
		{
		// @see http://elckerlyc.ewi.utwente.nl/browser/Elckerlyc/Hmi/HmiMath/src/hmi/math/Mat3f.java
		const T MINIMAL_SKEW_ANGLE = static_cast<T>(0.000001);

		FakeVector3<T> e0 = rotationVec;
		FakeVector3<T> e1;

		FakeVector3<T>::Normalize(translationVec, e1);
		const T rv1 = FakeVector3<T>::Dot(rotationVec, e1);
		e0 += rv1 * e1;

		const T rv0 = FakeVector3<T>::Dot(rotationVec, e0);
		const T cosa = fake_cos(angle);
		const T sina = fake_sin(angle);
		const T rr0 = rv0 * cosa - rv1 * sina;
		const T rr1 = rv0 * sina + rv1 * cosa;

		// FAKE_ASSERT(rr0 >= MINIMAL_SKEW_ANGLE);
		if (rr0 < MINIMAL_SKEW_ANGLE)
			{
			// ASSERT HERE
			std::cerr << "FakeMatrix4x4::Skew Asserted!" << std::endl;
			return;
			}

		const T d = rr1 / rr0 - rv1 / rv0;

		result = Identity;
		result.M11 = d * e1.X * e0.X + static_cast<T>(1);
		result.M12 = d * e1.X * e0.Y;
		result.M13 = d * e1.X * e0.Z;
		result.M21 = d * e1.Y * e0.X;
		result.M22 = d * e1.Y * e0.Y + static_cast<T>(1);
		result.M23 = d * e1.Y * e0.Z;
		result.M31 = d * e1.Z * e0.X;
		result.M32 = d * e1.Z * e0.Y;
		result.M33 = d * e1.Z * e0.Z + static_cast<T>(1);
		}

	static FakeMatrix4x4 Skew(T angle, const FakeVector3<T> &translationVec, const FakeVector3<T> &rotationVec)
		{
		FakeMatrix4x4 result;
		Skew(angle, translationVec, rotationVec, result);
		return result;
		}

	static void Transform(const FakeVector3<T> &translation, const FakeQuaternion<T> &rotation, const FakeVector3<T> &scaling, FakeMatrix4x4 &result)
		{
		// Equivalent to:
		//result =
		//    Matrix.Scale(scaling)
		//  * Matrix.RotateX(rotation.X)
		//  * Matrix.RotateY(rotation.Y)
		//  * Matrix.RotateZ(rotation.Z)
		//  * Matrix.Translate(translation);

		// Rotation
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

		// Position
		result.M41 = translation.X;
		result.M42 = translation.Y;
		result.M43 = translation.Z;

		// Scale
		result.M11 *= scaling.X;
		result.M12 *= scaling.X;
		result.M13 *= scaling.X;
		result.M21 *= scaling.Y;
		result.M22 *= scaling.Y;
		result.M23 *= scaling.Y;
		result.M31 *= scaling.Z;
		result.M32 *= scaling.Z;
		result.M33 *= scaling.Z;

		result.M14 = static_cast<T>(0);
		result.M24 = static_cast<T>(0);
		result.M34 = static_cast<T>(0);
		result.M44 = static_cast<T>(1);
		}

	static FakeMatrix4x4 Transform(const FakeVector3<T> &translation, const FakeQuaternion<T> &rotation, const FakeVector3<T> &scaling)
		{
		FakeMatrix4x4 result;
		Transform(translation, rotation, scaling, result);
		return result;
		}

	static void Transform(const FakeVector3<T> &translation, const FakeQuaternion<T> &rotation, const FakeVector3<T> &rotationCenter, const FakeVector3<T> &scaling, const FakeVector3<T> &scalingCenter, const FakeQuaternion<T> &scalingRotation, FakeMatrix4x4 &result)
		{
		FakeMatrix4x4 sr;
		Rotate(scalingRotation, sr);
		result = Translate(-scalingCenter) * Transpose(sr) * Scale(scaling) * sr * Translate(scalingCenter) * Translate(-rotationCenter) * Rotate(rotation) * Translate(rotationCenter) * Translate(translation);
		}

	static FakeMatrix4x4 Transform(const FakeVector3<T> &translation, const FakeQuaternion<T> &rotation, const FakeVector3<T> &rotationCenter, const FakeVector3<T> &scaling, const FakeVector3<T> &scalingCenter, const FakeQuaternion<T> &scalingRotation)
		{
		FakeMatrix4x4 result;
		Transform(translation, rotation, rotationCenter, scaling, scalingCenter, scalingRotation, result);
		return result;
		}

	static void AffineTransform(const FakeVector3<T> &translation, const FakeQuaternion<T> &rotation, T scaling, FakeMatrix4x4 &result)
		{
		result = Scale(scaling) * Rotate(rotation) * Translate(translation);
		}

	static FakeMatrix4x4 AffineTransform(const FakeVector3<T> &translation, const FakeQuaternion<T> &rotation, T scaling)
		{
		FakeMatrix4x4 result;
		AffineTransform(translation, rotation, scaling, result);
		return result;
		}

	static void AffineTransform(const FakeVector3<T> &translation, const FakeQuaternion<T> &rotation, const FakeVector3<T> &rotationCenter, T scaling, FakeMatrix4x4 &result)
		{
		result = Scale(scaling) * Translate(-rotationCenter) * Rotate(rotation) * Translate(rotationCenter) * Translate(translation);
		}

	static FakeMatrix4x4 AffineTransform(const FakeVector3<T> &translation, const FakeQuaternion<T> &rotation, const FakeVector3<T> &rotationCenter, T scaling)
		{
		FakeMatrix4x4 result;
		AffineTransform(translation, rotation, rotationCenter, scaling, result);
		return result;
		}

	static void AffineTransform2D(const FakeVector2<T> &translation, T rotation, T scaling, FakeMatrix4x4 &result)
		{
		result = Scale({ scaling, scaling, static_cast<T>(1) }) * RotateZ(rotation) * Translate({ translation.X, translation.Y, static_cast<T>(0) });
		}

	static FakeMatrix4x4 AffineTransform2D(const FakeVector2<T> &translation, T rotation, T scaling)
		{
		FakeMatrix4x4 result;
		AffineTransform2D(translation, rotation, scaling, result);
		return result;
		}

	static void AffineTransform2D(const FakeVector2<T> &translation, T rotation, const FakeVector2<T> &rotationCenter, T scaling, FakeMatrix4x4 &result)
		{
		result = Scale({ scaling, scaling, static_cast<T>(1) }) * Translate({ -rotationCenter.X, -rotationCenter.Y, static_cast<T>(0) }) * RotateZ(rotation) * Translate({ rotationCenter.X, rotationCenter.Y, static_cast<T>(0) }) * Translate({ translation.X, translation.Y, static_cast<T>(0) });
		}

	static FakeMatrix4x4 AffineTransform2D(const FakeVector2<T> &tranlation, T rotation, const FakeVector2<T> &translationCenter, T scaling)
		{
		FakeMatrix4x4 result;
		AffineTransform2D(tranlation, rotation, translationCenter, scaling, result);
		return result;
		}

	static void Transform2D(const FakeVector2<T> &translation, T rotation, const FakeVector2<T> &rotationCenter, const FakeVector2<T> &scaling, FakeVector2<T> &scalingCenter, T scalingRotation, FakeMatrix4x4 &result)
		{
		result = Translate({ -scalingCenter.X, -scalingCenter.Y, static_cast<T>(0) }) * RotateZ(-scalingRotation) * Scale({ scaling.X, scaling.Y, static_cast<T>(0) }) * RotateZ(scalingRotation) * Translate({ scalingCenter.X, scalingCenter.Y, static_cast<T>(0) }) * Translate({ -rotationCenter.X, -rotationCenter.Y, static_cast<T>(0) }) * RotateZ(rotation) * Translate({ rotationCenter.X, rotationCenter.Y, static_cast<T>(0) }) * Translate({ translation.X, translation.Y, static_cast<T>(0) });
		result.M33 = static_cast<T>(1);
		result.M44 = static_cast<T>(1);
		}

	static FakeMatrix4x4 Transform2D(const FakeVector2<T> &translation, T rotation, const FakeVector2<T> &rotationCenter, const FakeVector2<T> &scaling, FakeVector2<T> &scalingCenter, T scalingRotation)
		{
		FakeMatrix4x4 result;
		Transform2D(translation, rotation, rotationCenter, scaling, scalingCenter, scalingRotation, result);
		return result;
		}

	static void CreateWorldMatrix(const FakeVector3<T> &position, const FakeVector3<T> &forward, const FakeVector3<T> &up, FakeMatrix4x4 &result)
		{
		FakeVector3<T> vector3, vector31, vector32;

		FakeVector3<T>::Normalize(forward, vector3);
		vector3.Negate();
		FakeVector3<T>::Normalize(FakeVector3<T>::Cross(up, vector3), vector31);
		FakeVector3<T>::Cross(vector3, vector31, vector32);

		result.M11 = vector31.X;
		result.M12 = vector31.Y;
		result.M13 = vector31.Z;
		result.M14 = static_cast<T>(0);

		result.M21 = vector32.X;
		result.M22 = vector32.Y;
		result.M23 = vector32.Z;
		result.M24 = static_cast<T>(0);

		result.M31 = vector3.X;
		result.M32 = vector3.Y;
		result.M33 = vector3.Z;
		result.M34 = static_cast<T>(0);

		result.M41 = position.X;
		result.M42 = position.Y;
		result.M43 = position.Z;
		result.M44 = static_cast<T>(1);
		}

	static FakeMatrix4x4 CreateWorldMatrix(const FakeVector3<T> &position, const FakeVector3<T> &forward, const FakeVector3<T> &up)
		{
		FakeMatrix4x4 result;
		CreateWorldMatrix(position, forward, up, result);
		return result;
		}

	static void CreateFromAxis(T angle, const FakeVector3<T> &axis, FakeMatrix4x4 &result)
		{
		const T x = axis.X;
		const T y = axis.Y;
		const T z = axis.Z;
		const T single = fake_sin(angle);
		const T single1 = fake_cos(angle);
		const T single2 = x * x;
		const T single3 = y * y;
		const T single4 = z * z;
		const T single5 = x * y;
		const T single6 = x * z;
		const T single7 = y * z;

		result.M11 = single2 + single1 * (static_cast<T>(1) - single2);
		result.M12 = single5 - single1 * single5 + single * z;
		result.M13 = single6 - single1 * single6 - single * y;
		result.M14 = static_cast<T>(0);

		result.M21 = single5 - single1 * single5 - single * z;
		result.M22 = single3 + single1 * (static_cast<T>(1) - single3);
		result.M23 = single7 - single1 * single7 + single * x;
		result.M24 = static_cast<T>(0);

		result.M31 = single6 - single1 * single6 + single * y;
		result.M32 = single7 - single1 * single7 - single * x;
		result.M33 = single4 + single1 * (static_cast<T>(1) - single4);
		result.M34 = static_cast<T>(0);

		result.M41 = static_cast<T>(0);
		result.M42 = static_cast<T>(0);
		result.M43 = static_cast<T>(0);
		result.M44 = static_cast<T>(1);
		}

	static FakeMatrix4x4 CreateFromAxis(T angle, const FakeVector3<T> &axis)
		{
		FakeMatrix4x4 result;
		CreateFromAxis(angle, axis, result);
		return result;
		}

	static void Add(const FakeMatrix4x4 &a, const FakeMatrix4x4 &b, FakeMatrix4x4 &result)
		{
		result.M11 = a.M11 + b.M11;
		result.M12 = a.M12 + b.M12;
		result.M13 = a.M13 + b.M13;
		result.M14 = a.M14 + b.M14;

		result.M21 = a.M21 + b.M21;
		result.M22 = a.M22 + b.M22;
		result.M23 = a.M23 + b.M23;
		result.M24 = a.M24 + b.M24;

		result.M31 = a.M31 + b.M31;
		result.M32 = a.M32 + b.M32;
		result.M33 = a.M33 + b.M33;
		result.M34 = a.M34 + b.M34;

		result.M41 = a.M41 + b.M41;
		result.M42 = a.M42 + b.M42;
		result.M43 = a.M43 + b.M43;
		result.M44 = a.M44 + b.M44;
		}

	static void Subtract(const FakeMatrix4x4 &a, const FakeMatrix4x4 &b, FakeMatrix4x4 &result)
		{
		result.M11 = a.M11 - b.M11;
		result.M12 = a.M12 - b.M12;
		result.M13 = a.M13 - b.M13;
		result.M14 = a.M14 - b.M14;

		result.M21 = a.M21 - b.M21;
		result.M22 = a.M22 - b.M22;
		result.M23 = a.M23 - b.M23;
		result.M24 = a.M24 - b.M24;

		result.M31 = a.M31 - b.M31;
		result.M32 = a.M32 - b.M32;
		result.M33 = a.M33 - b.M33;
		result.M34 = a.M34 - b.M34;

		result.M41 = a.M41 - b.M41;
		result.M42 = a.M42 - b.M42;
		result.M43 = a.M43 - b.M43;
		result.M44 = a.M44 - b.M44;
		}

	static void Multiply(const FakeMatrix4x4 &a, const FakeMatrix4x4 &b, FakeMatrix4x4 &result)
		{
		result.M11 = a.M11 * b.M11 + a.M12 * b.M21 + a.M13 * b.M31 + a.M14 * b.M41;
		result.M12 = a.M11 * b.M12 + a.M12 * b.M22 + a.M13 * b.M32 + a.M14 * b.M42;
		result.M13 = a.M11 * b.M13 + a.M12 * b.M23 + a.M13 * b.M33 + a.M14 * b.M43;
		result.M14 = a.M11 * b.M14 + a.M12 * b.M24 + a.M13 * b.M34 + a.M14 * b.M44;

		result.M21 = a.M21 * b.M11 + a.M22 * b.M21 + a.M23 * b.M31 + a.M24 * b.M41;
		result.M22 = a.M21 * b.M12 + a.M22 * b.M22 + a.M23 * b.M32 + a.M24 * b.M42;
		result.M23 = a.M21 * b.M13 + a.M22 * b.M23 + a.M23 * b.M33 + a.M24 * b.M43;
		result.M24 = a.M21 * b.M14 + a.M22 * b.M24 + a.M23 * b.M34 + a.M24 * b.M44;

		result.M31 = a.M31 * b.M11 + a.M32 * b.M21 + a.M33 * b.M31 + a.M34 * b.M41;
		result.M32 = a.M31 * b.M12 + a.M32 * b.M22 + a.M33 * b.M32 + a.M34 * b.M42;
		result.M33 = a.M31 * b.M13 + a.M32 * b.M23 + a.M33 * b.M33 + a.M34 * b.M43;
		result.M34 = a.M31 * b.M14 + a.M32 * b.M24 + a.M33 * b.M34 + a.M34 * b.M44;

		result.M41 = a.M41 * b.M11 + a.M42 * b.M21 + a.M43 * b.M31 + a.M44 * b.M41;
		result.M42 = a.M41 * b.M12 + a.M42 * b.M22 + a.M43 * b.M32 + a.M44 * b.M42;
		result.M43 = a.M41 * b.M13 + a.M42 * b.M23 + a.M43 * b.M33 + a.M44 * b.M43;
		result.M44 = a.M41 * b.M14 + a.M42 * b.M24 + a.M43 * b.M34 + a.M44 * b.M44;
		}

	static void Multiply(const FakeMatrix4x4 &a, T b, FakeMatrix4x4 &result)
		{
		result.M11 = a.M11 * b;
		result.M12 = a.M12 * b;
		result.M13 = a.M13 * b;
		result.M14 = a.M14 * b;

		result.M21 = a.M21 * b;
		result.M22 = a.M22 * b;
		result.M23 = a.M23 * b;
		result.M24 = a.M24 * b;

		result.M31 = a.M31 * b;
		result.M32 = a.M32 * b;
		result.M33 = a.M33 * b;
		result.M34 = a.M34 * b;

		result.M41 = a.M41 * b;
		result.M42 = a.M42 * b;
		result.M43 = a.M43 * b;
		result.M44 = a.M44 * b;
		}

	static void Multiply(const FakeMatrix4x4 &a, const FakeVector4<T> &b, FakeVector4<T> &result)
		{
		result.X = a.Raw[0] * b.X + a.Raw[1] * b.Y + a.Raw[2] * b.Z + a.Raw[3] * b.W;
		result.Y = a.Raw[4] * b.X + a.Raw[5] * b.Y + a.Raw[6] * b.Z + a.Raw[7] * b.W;
		result.Z = a.Raw[8] * b.X + a.Raw[9] * b.Y + a.Raw[10] * b.Z + a.Raw[11] * b.W;
		result.W = a.Raw[12] * b.X + a.Raw[13] * b.Y + a.Raw[14] * b.Z + a.Raw[15] * b.W;
		}

	static void Divide(const FakeMatrix4x4 &a, const FakeMatrix4x4 &b, FakeMatrix4x4 &result)
		{
		FakeMatrix4x4 invertedB;
		FakeMatrix4x4::Inverse(b, invertedB);

		result.M11 = a.M11 * invertedB.M11 + a.M12 * invertedB.M21 + a.M13 * invertedB.M31 + a.M14 * invertedB.M41;
		result.M12 = a.M11 * invertedB.M12 + a.M12 * invertedB.M22 + a.M13 * invertedB.M32 + a.M14 * invertedB.M42;
		result.M13 = a.M11 * invertedB.M13 + a.M12 * invertedB.M23 + a.M13 * invertedB.M33 + a.M14 * invertedB.M43;
		result.M14 = a.M11 * invertedB.M14 + a.M12 * invertedB.M24 + a.M13 * invertedB.M34 + a.M14 * invertedB.M44;

		result.M21 = a.M21 * invertedB.M11 + a.M22 * invertedB.M21 + a.M23 * invertedB.M31 + a.M24 * invertedB.M41;
		result.M22 = a.M21 * invertedB.M12 + a.M22 * invertedB.M22 + a.M23 * invertedB.M32 + a.M24 * invertedB.M42;
		result.M23 = a.M21 * invertedB.M13 + a.M22 * invertedB.M23 + a.M23 * invertedB.M33 + a.M24 * invertedB.M43;
		result.M24 = a.M21 * invertedB.M14 + a.M22 * invertedB.M24 + a.M23 * invertedB.M34 + a.M24 * invertedB.M44;

		result.M31 = a.M31 * invertedB.M11 + a.M32 * invertedB.M21 + a.M33 * invertedB.M31 + a.M34 * invertedB.M41;
		result.M32 = a.M31 * invertedB.M12 + a.M32 * invertedB.M22 + a.M33 * invertedB.M32 + a.M34 * invertedB.M42;
		result.M33 = a.M31 * invertedB.M13 + a.M32 * invertedB.M23 + a.M33 * invertedB.M33 + a.M34 * invertedB.M43;
		result.M34 = a.M31 * invertedB.M14 + a.M32 * invertedB.M24 + a.M33 * invertedB.M34 + a.M34 * invertedB.M44;

		result.M41 = a.M41 * invertedB.M11 + a.M42 * invertedB.M21 + a.M43 * invertedB.M31 + a.M44 * invertedB.M41;
		result.M42 = a.M41 * invertedB.M12 + a.M42 * invertedB.M22 + a.M43 * invertedB.M32 + a.M44 * invertedB.M42;
		result.M43 = a.M41 * invertedB.M13 + a.M42 * invertedB.M23 + a.M43 * invertedB.M33 + a.M44 * invertedB.M43;
		result.M44 = a.M41 * invertedB.M14 + a.M42 * invertedB.M24 + a.M43 * invertedB.M34 + a.M44 * invertedB.M44;
		}

	static void Divide(const FakeMatrix4x4 &a, T b, FakeMatrix4x4 &result)
		{
		result.M11 = a.M11 / b;
		result.M12 = a.M12 / b;
		result.M13 = a.M13 / b;
		result.M14 = a.M14 / b;

		result.M21 = a.M21 / b;
		result.M22 = a.M22 / b;
		result.M23 = a.M23 / b;
		result.M24 = a.M24 / b;

		result.M31 = a.M31 / b;
		result.M32 = a.M32 / b;
		result.M33 = a.M33 / b;
		result.M34 = a.M34 / b;

		result.M41 = a.M41 / b;
		result.M42 = a.M42 / b;
		result.M43 = a.M43 / b;
		result.M44 = a.M44 / b;
		}

	static FakeMatrix4x4 Add(const FakeMatrix4x4 &a, const FakeMatrix4x4 &b)
		{
		FakeMatrix4x4 result;
		Add(a, b, result);
		return result;
		}

	static FakeMatrix4x4 Subtract(const FakeMatrix4x4 &a, const FakeMatrix4x4 &b)
		{
		FakeMatrix4x4 result;
		Subtract(a, b, result);
		return result;
		}

	static FakeMatrix4x4 Multiply(const FakeMatrix4x4 &a, const FakeMatrix4x4 &b)
		{
		FakeMatrix4x4 result;
		Multiply(a, b, result);
		return result;
		}

	static FakeMatrix4x4 Divide(const FakeMatrix4x4 &a, const FakeMatrix4x4 &b)
		{
		FakeMatrix4x4 result;
		Divide(a, b, result);
		return result;
		}

	static FakeVector4<T> Multiply(const FakeMatrix4x4 &a, const FakeVector4<T> &b)
		{
		FakeVector4<T> result;
		Multiply(a, b, result);
		return result;
		}

	static FakeMatrix4x4 Multiply(const FakeMatrix4x4 &a, T b)
		{
		FakeMatrix4x4 result;
		Multiply(a, b, result);
		return result;
		}

	static FakeMatrix4x4 Divide(const FakeMatrix4x4 &a, T b)
		{
		FakeMatrix4x4 result;
		Divide(a, b, result);
		return result;
		}

	bool operator==(const FakeMatrix4x4 &other) const
		{
		return M11 == other.M11
			&& M12 == other.M12
			&& M13 == other.M13
			&& M14 == other.M14
			&& M21 == other.M21
			&& M22 == other.M22
			&& M23 == other.M23
			&& M24 == other.M24
			&& M31 == other.M31
			&& M32 == other.M32
			&& M33 == other.M33
			&& M34 == other.M34
			&& M41 == other.M41
			&& M42 == other.M42
			&& M43 == other.M43
			&& M44 == other.M44;
		}

	bool operator!=(const FakeMatrix4x4 &other) const
		{
		return !(*this == other);
		}

	bool operator<(const FakeMatrix4x4 &other) const
		{
		return M11 < other.M11
			&&M12 < other.M12
			&&M13 < other.M13
			&&M14 < other.M14
			&&M21 < other.M21
			&&M22 < other.M22
			&&M23 < other.M23
			&&M24 < other.M24
			&&M31 < other.M31
			&&M32 < other.M32
			&&M33 < other.M33
			&&M34 < other.M34
			&&M41 < other.M41
			&&M42 < other.M42
			&&M43 < other.M43
			&&M44 < other.M44;
		}

	bool operator<=(const FakeMatrix4x4 &other) const
		{
		return M11 <= other.M11
			&& M12 <= other.M12
			&& M13 <= other.M13
			&& M14 <= other.M14
			&& M21 <= other.M21
			&& M22 <= other.M22
			&& M23 <= other.M23
			&& M24 <= other.M24
			&& M31 <= other.M31
			&& M32 <= other.M32
			&& M33 <= other.M33
			&& M34 <= other.M34
			&& M41 <= other.M41
			&& M42 <= other.M42
			&& M43 <= other.M43
			&& M44 <= other.M44;
		}

	bool operator>(const FakeMatrix4x4 &other) const
		{
		return M11 > other.M11
			&& M12 > other.M12
			&& M13 > other.M13
			&& M14 > other.M14
			&& M21 > other.M21
			&& M22 > other.M22
			&& M23 > other.M23
			&& M24 > other.M24
			&& M31 > other.M31
			&& M32 > other.M32
			&& M33 > other.M33
			&& M34 > other.M34
			&& M41 > other.M41
			&& M42 > other.M42
			&& M43 > other.M43
			&& M44 > other.M44;
		}

	bool operator>=(const FakeMatrix4x4 &other) const
		{
		return M11 >= other.M11
			&& M12 >= other.M12
			&& M13 >= other.M13
			&& M14 >= other.M14
			&& M21 >= other.M21
			&& M22 >= other.M22
			&& M23 >= other.M23
			&& M24 >= other.M24
			&& M31 >= other.M31
			&& M32 >= other.M32
			&& M33 >= other.M33
			&& M34 >= other.M34
			&& M41 >= other.M41
			&& M42 >= other.M42
			&& M43 >= other.M43
			&& M44 >= other.M44;
		}

	FakeMatrix4x4 operator-() const
		{
		return FakeMatrix4x4(-M11, -M12, -M13, -M14, -M21, -M22, -M23, -M24, -M31, -M32, -M33, -M34, -M41, -M42, -M43, -M44);
		}

	FakeMatrix4x4 operator+(const FakeMatrix4x4 &other) const
		{
		FakeMatrix4x4 result;
		Add(*this, other, result);
		return result;
		}

	FakeMatrix4x4 operator-(const FakeMatrix4x4 &other) const
		{
		FakeMatrix4x4 result;
		Subtract(*this, other, result);
		return result;
		}

	FakeMatrix4x4 operator*(const FakeMatrix4x4 &other) const
		{
		FakeMatrix4x4 result;
		Multiply(*this, other, result);
		return result;
		}

	FakeMatrix4x4 operator/(const FakeMatrix4x4 &other) const
		{
		FakeMatrix4x4 result;
		Divide(*this, other, result);
		return result;
		}

	FakeVector4<T> operator*(const FakeVector4<T> &vector) const
		{
		FakeVector4<T> result;
		Multiply(*this, vector, result);
		return result;
		}

	FakeMatrix4x4 operator*(T scalar) const
		{
		FakeMatrix4x4 result;
		Multiply(*this, scalar, result);
		return result;
		}

	FakeMatrix4x4 operator/(T scalar) const
		{
		FakeMatrix4x4 result;
		Divide(*this, scalar, result);
		return result;
		}

	FakeMatrix4x4 &operator+=(const FakeMatrix4x4 &other)
		{
		Add(*this, other, *this);
		return *this;
		}

	FakeMatrix4x4 &operator-=(const FakeMatrix4x4 &other)
		{
		Subtract(*this, other, *this);
		return *this;
		}

	FakeMatrix4x4 &operator*=(const FakeMatrix4x4 &other)
		{
		Multiply(*this, other, *this);
		return *this;
		}

	FakeMatrix4x4 &operator/=(const FakeMatrix4x4 &other)
		{
		Divide(*this, other, *this);
		return *this;
		}

	FakeVector4<T> &operator*=(const FakeVector4<T> &vector)
		{
		FakeVector4<T> result;
		Multiply(*this, vector, result);
		return result;
		}

	FakeMatrix4x4 &operator*=(T scalar)
		{
		Multiply(*this, scalar, *this);
		return *this;
		}

	FakeMatrix4x4 &operator/=(T scalar)
		{
		Divide(*this, scalar, *this);
		return *this;
		}

	FakeMatrix4x4 &operator++(int)
		{
		++M11;
		++M12;
		++M13;
		++M14;
		++M21;
		++M22;
		++M23;
		++M24;
		++M31;
		++M32;
		++M33;
		++M34;
		++M41;
		++M42;
		++M43;
		++M44;
		return *this;
		}

	FakeMatrix4x4 &operator--(int)
		{
		--M11;
		--M12;
		--M13;
		--M14;
		--M21;
		--M22;
		--M23;
		--M24;
		--M31;
		--M32;
		--M33;
		--M34;
		--M41;
		--M42;
		--M43;
		--M44;
		return *this;
		}

	FakeMatrix4x4 &operator=(const FakeMatrix4x4 &other)
		{
		M11 = other.M11;
		M12 = other.M12;
		M13 = other.M13;
		M14 = other.M14;

		M21 = other.M21;
		M22 = other.M22;
		M23 = other.M23;
		M24 = other.M24;

		M31 = other.M31;
		M32 = other.M32;
		M33 = other.M33;
		M34 = other.M34;

		M41 = other.M41;
		M42 = other.M42;
		M43 = other.M43;
		M44 = other.M44;
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
		if (index > 0 && index < 16)
			{
			return Raw[index];
			}

		// Index out of bounds, return -1
		static T falseVal = static_cast<T>(-1);
		return falseVal;
		}

	const T &operator[](uint32 index) const
		{
		if (index > 0 && index < 16)
			{
			return Raw[index];
			}

		// Index out of bounds, return -1
		static T falseVal = static_cast<T>(-1);
		return falseVal;
		}

	friend std::ostream &operator<<(std::ostream &stream, const FakeMatrix4x4 &m)
		{
		stream << m.M11 << ", " << m.M12 << ", " << m.M13 << ", " << m.M14 << ",\n";
		stream << m.M21 << ", " << m.M22 << ", " << m.M23 << ", " << m.M24 << ",\n";
		stream << m.M31 << ", " << m.M32 << ", " << m.M33 << ", " << m.M34 << ",\n";
		stream << m.M41 << ", " << m.M42 << ", " << m.M43 << ", " << m.M44 << ",\n";
		return stream;
		}
	};

template<typename T>
const FakeMatrix4x4<T> FakeMatrix4x4<T>::Zero(static_cast<T>(0));

template<typename T>
const FakeMatrix4x4<T> FakeMatrix4x4<T>::Identity(static_cast<T>(1));

typedef FakeMatrix4x4<double> FakeMat4d;
typedef FakeMatrix4x4<float> FakeMat4f;
typedef FakeMatrix4x4<int32> FakeMat4i;
typedef FakeMatrix4x4<long> FakeMat4l;
typedef FakeMatrix4x4<short> FakeMat4s;
typedef FakeMatrix4x4<bool> FakeMat4b;

