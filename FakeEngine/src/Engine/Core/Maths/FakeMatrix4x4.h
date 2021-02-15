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

#include "Engine/Core/Maths/FakeMathFunctions.h"
#include "Engine/Core/Maths/FakeVector2.h"
#include "Engine/Core/Maths/FakeVector3.h"
#include "Engine/Core/Maths/FakeVector4.h"
#include "Engine/Core/Maths/FakeMatrix2x2.h"
#include "Engine/Core/Maths/FakeMatrix3x3.h"

template<typename T>
struct FakeQuaternion;

template<typename T>
struct FAKE_API FakeMatrix4x4
	{

	union
		{
		struct
			{
			/**
			 * 
			 * Value at row 1 column 1 of the matrix.
			 * 
			 */
			T M11;

			/**
			 * 
			 * Value at row 1 column 2 of the matrix.
			 * 
			 */
			T M12;
			
			/**
			 * 
			 * Value at row 1 column 3 of the matrix.
			 * 
			 */
			T M13;
			
			/**
			 * 
			 * Value at row 1 column 4 of the matrix.
			 * 
			 */
			T M14;
			
			/**
			 * 
			 * Value at row 2 column 1 of the matrix.
			 * 
			 */
			T M21;
			
			/**
			 * 
			 * Value at row 2 column 2 of the matrix.
			 * 
			 */
			T M22;
			
			/**
			 * 
			 * Value at row 2 column 3 of the matrix.
			 * 
			 */
			T M23;
			
			/**
			 * 
			 * Value at row 2 column 4 of the matrix.
			 * 
			 */
			T M24;
			
			/**
			 * 
			 * Value at row 3 column 1 of the matrix.
			 * 
			 */
			T M31;
			
			/**
			 * 
			 * Value at row 3 column 2 of the matrix.
			 * 
			 */
			T M32;
			
			/**
			 * 
			 * Value at row 3 column 3 of the matrix.
			 * 
			 */
			T M33;
			
			/**
			 * 
			 * Value at row 3 column 4 of the matrix.
			 * 
			 */
			T M34;
			
			/**
			 * 
			 * Value at row 4 column 1 of the matrix.
			 * 
			 */
			T M41;
			
			/**
			 * 
			 * Value at row 4 column 2 of the matrix.
			 * 
			 */
			T M42;
			
			/**
			 * 
			 * Value at row 4 column 3 of the matrix.
			 * 
			 */
			T M43;
			
			/**
			 * 
			 * Value at row 4 column 4 of the matrix.
			 * 
			 */
			T M44;
			};

		T Values[4][4];
		T Raw[16];
		};

	// A matrix with all of its components set to zero.
	static const FakeMatrix4x4 Zero;

	// The identity matrix.
	static const FakeMatrix4x4 Identity;

	/**
	 * 
	 * .
	 * 
	 */
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

	/**
	 * 
	 * .
	 * 
	 * @param value
	 */
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

	/**
	 * 
	 * .
	 * 
	 * @param m11
	 * @param m12
	 * @param m13
	 * @param m14
	 * @param m21
	 * @param m22
	 * @param m23
	 * @param m24
	 * @param m31
	 * @param m32
	 * @param m33
	 * @param m34
	 * @param m41
	 * @param m42
	 * @param m43
	 * @param m44
	 */
	FakeMatrix4x4(T m11, T m12, T m13, T m14, T m21, T m22, T m23, T m24, T m31, T m32, T m33, T m34, T m41, T m42, T m43, T m44)
		: M11(m11), M12(m12), M13(m13), M14(m14), M21(m21), M22(m22), M23(m23), M24(m24), M31(m31), M32(m32), M33(m33), M34(m34), M41(m41), M42(m42), M43(m43), M44(m44)
		{
		}

	/**
	 * 
	 * constructor.
	 * 
	 * @param values stack based array.
	 */
	FakeMatrix4x4(T values[16])
		{
		memcpy(Raw, values, 16 * sizeof(T));
		}

	/**
	 * 
	 * constructor.
	 * 
	 * @param values 2 dimensional array.
	 */
	FakeMatrix4x4(T values[4][4])
		{
		memcpy(Raw, values, 16 * sizeof(T));
		}

	/**
	 * 
	 * constructor.
	 * 
	 * @param other 2x2 Matrix.
	 */
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
		M33 = static_cast<T>(0);
		M34 = static_cast<T>(0);

		M41 = static_cast<T>(0);
		M42 = static_cast<T>(0);
		M43 = static_cast<T>(0);
		M44 = static_cast<T>(0);
		}

	/**
	 * 
	 * constructor.
	 * 
	 * @param other 3x3 Matrix.
	 */
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
		M44 = static_cast<T>(0);
		}

	/**
	 * 
	 * copy constructor.
	 * 
	 * @param The Matrix to copy.
	 */
	FakeMatrix4x4(const FakeMatrix4x4&) = default;

	/**
	 * 
	 * Converts the matrix to a String.
	 * 
	 * @return Returns the matrix as a String.
	 */
	FakeString ToString() const
		{
		FakeString result;
		result << M11 << ", " << M12 << ", " << M13 << ", " << M14 << ",\n";
		result << M21 << ", " << M22 << ", " << M23 << ", " << M24 << ",\n";
		result << M31 << ", " << M32 << ", " << M33 << ", " << M34 << ",\n";
		result << M41 << ", " << M42 << ", " << M43 << ", " << M44 << "\n";
		return result;
		}

	/**
	 * 
	 * Gets the up vector of the matrix (elements are M21, M22, M23).
	 * 
	 * @return Returns the up vector of the matrix.
	 */
	FakeVector3<T> GetUpVector() const
		{
		return FakeVector3<T>(M21, M22, M23);
		}

	/**
	 * 
	 * Gets the down vector of the matrix (elements are -M21, -M22, -M23).
	 * 
	 * @return Returns the down vector of the matrix.
	 */
	FakeVector3<T> GetDownVector() const
		{
		return FakeVector3<T>(-M21, -M22, -M23);
		}

	/**
	 * 
	 * Gets the right vector of the matrix (elements are M11, M12, M13).
	 * 
	 * @return Returns the right vector of the matrix.
	 */
	FakeVector3<T> GetRightVector() const
		{
		return FakeVector3<T>(M11, M12, M13);
		}

	/**
	 * 
	 * Gets the left vector of the matrix (elements are -M11, -M12, -M13).
	 * 
	 * @return Returns the left vector of the matrix.
	 */
	FakeVector3<T> GetLeftVector() const
		{
		return FakeVector3<T>(-M11, -M12, -M13);
		}

	/**
	 * 
	 * Gets the forward vector of the matrix (elements are -M31, -M32, -M33).
	 * 
	 * @return Returns the forward vector of the matrix.
	 */
	FakeVector3<T> GetForwardVector() const
		{
		return FakeVector3<T>(-M31, -M32, -M33);
		}

	/**
	 * 
	 * Gets the backward vector of the matrix (elements are M31, M32, M33).
	 * 
	 * @return Returns the backward vector of the matrix.
	 */
	FakeVector3<T> GetBackwardVector() const
		{
		return FakeVector3<T>(M31, M32, M33);
		}

	/**
	 * 
	 * Sets the up vector of the matrix (elements which are going to be set are M21, M22, M23).
	 * 
	 * @param value The values to set.
	 */
	void SetUpVector(const FakeVector3<T> &value)
		{
		M21 = value.X;
		M22 = value.Y;
		M23 = value.Z;
		}

	/**
	 * 
	 * Sets the down vector of the matrix (elements which are going to be set are -M21, -M22, -M23).
	 * 
	 * @param value The values to set.
	 */
	void SetDownVector(const FakeVector3<T> &value)
		{
		M21 = -value.X;
		M22 = -value.Y;
		M23 = -value.Z;
		}

	/**
	 * 
	 * Sets the right vector of the matrix (elements which are going to be set are M11, M12, M13).
	 * 
	 * @param value The values to set.
	 */
	void SetRightVector(const FakeVector3<T> &value)
		{
		M11 = value.X;
		M12 = value.Y;
		M13 = value.Z;
		}

	/**
	 * 
	 * Sets the left vector of the matrix (elements which are going to be set are -M11, -M12, -M13).
	 * 
	 * @param value The values to set.
	 */
	void SetLeftVector(const FakeVector3<T> &value)
		{
		M11 = -value.X;
		M12 = -value.Y;
		M13 = -value.Z;
		}

	/**
	 * 
	 * Sets the forward vector of the matrix (elements which are going to be set are -M31, -M32, -M33).
	 * 
	 * @param value The values to set.
	 */
	void SetForwardVector(const FakeVector3<T> &value)
		{
		M31 = -value.X;
		M32 = -value.Y;
		M33 = -value.Z;
		}

	/**
	 * 
	 * Sets the backward vector of the matrix (elements which are going to be set are M31, M32, M33).
	 * 
	 * @param value The values to set.
	 */
	void SetBackwardVector(const FakeVector3<T> &value)
		{
		M31 = value.X;
		M32 = value.Y;
		M33 = value.Z;
		}

	/**
	 * 
	 * Gets the row at the specified index.
	 * 
	 * @param index The index at which the values should be returned. Defaulted to 0 -> First row.
	 * @return Returns the row at the specified index.
	 */
	FakeVector4<T> GetRow(uint32 index = 0) const
		{
		FakeVector4<T> result;

		if (index == 0)
			{
			// Returns first row
			result = FakeVector4<T>(M11, M12, M13, M14);
			}
		else if (index == 1)
			{
			// Returns second row
			result = FakeVector4<T>(M21, M22, M23, M24);
			}
		else if (index == 2)
			{
			// Returns third row
			result = FakeVector4<T>(M31, M32, M33, M34);
			}
		else if (index == 3)
			{
			// Returns fourth row
			result = FakeVector4<T>(M41, M42, M43, M44);
			}
		else
			{
			// Returns 0 vector
			result = FakeVector4<T>::Zero;
			}

		return result;
		}

	/**
	 * 
	 * Sets the row at the specified index.
	 * 
	 * @param values The values which should be set in the matrix.
	 * @param index The index at which the values should be set. Defaulted to 0 -> first row.
	 */
	void SetRow(const FakeVector4<T> &values, uint32 index = 0)
		{
		if (index == 0)
			{
			// Sets first row
			M11 = values.X;
			M12 = values.Y;
			M13 = values.Z;
			M14 = values.W;
			}
		else if (index == 1)
			{
			// Sets second row
			M21 = values.X;
			M22 = values.Y;
			M23 = values.Z;
			M24 = values.W;
			}
		else if (index == 2)
			{
			// Sets third row
			M31 = values.X;
			M32 = values.Y;
			M33 = values.Z;
			M34 = values.W;
			}
		else if (index == 3)
			{
			// Sets fourth row
			M41 = values.X;
			M42 = values.Y;
			M43 = values.Z;
			M44 = values.W;
			}
		}

	/**
	 * 
	 * Gets the column at the specified index.
	 * 
	 * @param index The index at which the values should be returned. Defaulted to 0 -> First column.
	 * @return Returns the column at the specified index.
	 */
	FakeVector4<T> GetColumn(uint32 index = 0)
		{
		FakeVector4<T> result;

		if (index == 0)
			{
			// Gets first column
			result = FakeVector4<T>(M11, M21, M31, M41);
			}
		else if (index == 1)
			{
			// Gets second column
			result = FakeVector4<T>(M12, M22, M32, M42);
			}
		else if (index == 2)
			{
			// Gets third column
			result = FakeVector4<T>(M13, M23, M33, M43);
			}
		else if (index == 3)
			{
			// Gets fourth column
			result = FakeVector4<T>(M14, M24, M34, M44);
			}
		else
			{
			// Returns 0 vector
			result = FakeVector4<T>::Zero;
			}

		return result;
		}

	/**
	 * 
	 * Sets the column at the specified index.
	 * 
	 * @param values The values which should be set in the matrix.
	 * @param index The index at which the values should be set. Defaulted to 0 -> first column.
	 */
	void SetColumn(const FakeVector4<T> &values, uint32 index = 0)
		{
		if (index == 0)
			{
			// Sets first column
			M11 = values.X;
			M21 = values.Y;
			M31 = values.Z;
			M41 = values.W;
			}
		else if (index == 1)
			{
			// Sets second column
			M12 = values.X;
			M22 = values.Y;
			M32 = values.Z;
			M42 = values.W;
			}
		else if (index == 2)
			{
			// Sets third column
			M13 = values.X;
			M23 = values.Y;
			M33 = values.Z;
			M43 = values.W;
			}
		else if (index == 3)
			{
			// Sets fourth column
			M14 = values.X;
			M24 = values.Y;
			M34 = values.Z;
			M44 = values.W;
			}
		}

	/**
	 * 
	 * Gets the translation of the matrix (elements are M41, M42, M43).
	 * 
	 * @return Returns the translation values of the matrix.
	 */
	FakeVector3<T> GetTranslation() const
		{
		return FakeVector3<T>(M41, M42, M43);
		}

	/**
	 * 
	 * Sets the translation of the matrix (elements are M41, M42, M43).
	 * 
	 * @param values The transformation values which should be set.
	 */
	void SetTranslation(const FakeVector3<T> &values)
		{
		M41 = values.X;
		M42 = values.Y;
		M43 = values.Z;
		}

	/**
	 * 
	 * Gets the scale of the matrix (elements are M11, M22, M33).
	 * 
	 * @return Returns the scale of the matrix.
	 */
	FakeVector3<T> GetScale() const
		{
		return FakeVector3<T>(M11, M22, M33);
		}

	/**
	 * 
	 * Sets the scale of the matrix (elements are M11, M22, M33).
	 * 
	 * @param values The scale values which should be set.
	 */
	void SetScale(const FakeVector3<T> &values)
		{
		M11 = values.X;
		M22 = values.Y;
		M33 = values.Z;
		}

	/**
	 * 
	 * Gets a value indicating whether this instance is an identity matrix.
	 * 
	 * @return Returns true if the current instance is a identity matrix - otherwise false.
	 */
	bool IsIdentity() const
		{
		return *this == Identity;
		}

	/**
	 * 
	 * Calculates the determinant of the matrix.
	 * 
	 * @return Returns the determinant of the matrix.
	 */
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

	/**
	 * 
	 * Calculates determinant of the rotation 3x3 matrix.
	 * 
	 * @return Returns the determinant of the 3x3 matrix.
	 */
	T GetRotDeterminant() const
		{
		return
			Values[0][0] * (Values[1][1] * Values[2][2] - Values[1][2] * Values[2][1]) -
			Values[1][0] * (Values[0][1] * Values[2][2] - Values[0][2] * Values[2][1]) +
			Values[2][0] * (Values[0][1] * Values[1][2] - Values[0][2] * Values[1][1]);
		}

	/**
	 * 
	 * Overrides the values of the current instance with the inverse of it.
	 * 
	 */
	void Inverse()
		{
		Inverse(*this, *this);
		}

	/**
	 * 
	 * Overrides the values of the current instance with the transpose of it.
	 * 
	 */
	void Transpose()
		{
		Transpose(*this, *this);
		}

	/**
	 * 
	 * Removes any scaling from the matrix by performing the normalization (each row magnitude is 1). Does not modify the 4th row with translation vector.
	 * 
	 */
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

	/**
	 * 
	 * Decomposes a rotation matrix with the specified yaw, pitch, roll.
	 * 
	 * @param outYaw The result yaw (in radians).
	 * @param outPitch The result pitch (in radians).
	 * @param outRoll The result roll (in radians).
	 */
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

	/**
	 * 
	 * Decomposes a matrix into a translation and scale.
	 * @warning This method is designed to decompose an SRT transformation matrix only.
	 * 
	 * @param outTranslation The result translation.
	 * @param outScale The result scale.
	 */
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

	/**
	 * 
	 * Decomposes a matrix into a translation, rotation, and scale.
	 * @warning This method is designed to decompose an SRT transformation matrix only.
	 * 
	 * @param outTranslation The result translation.
	 * @param outRotation The result rotation.
	 * @param outScale The result scale.
	 */
	void Decompose(FakeVector3<T> &outTranslation, FakeQuaternion<T> &outRotation, FakeVector3<T> &outScale)
		{
		FakeMatrix4x4 rotationMatrix;
		Decompose(outTranslation, rotationMatrix, outScale);
		FakeQuaternion<T>::RotationMatrix(rotationMatrix, outRotation);
		}

	/**
	 * 
	 * Decomposes a matrix into a translation, rotation, and scale.
	 * @warning This method is designed to decompose an SRT transformation matrix only.
	 * 
	 * @param outTranslation The result translation.
	 * @param outRotation The result rotation.
	 * @param outScale The result scale.
	 */
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

		// Calculate an perfect orthonormal matrix (no reflections)
		const auto at = FakeVector3<T>(M31 / outScale.Z, M32 / outScale.Z, M33 / outScale.Z);
		const auto up = FakeVector3<T>::Cross(at, FakeVector3<T>(M11 / outScale.X, M12 / outScale.X, M13 / outScale.X));
		const auto right = FakeVector3<T>::Cross(up, at);
		outRotation.SetRightVector(right);
		outRotation.SetUpVector(up);
		outRotation.SetBackwardVector(at);

		// In case of reflections
		scale.X = FakeVector3<T>::Dot(right, GetRightVector()) > static_cast<T>(0) ? outScale.X : -outScale.X;
		scale.Y = FakeVector3<T>::Dot(up, GetUpVector()) > static_cast<T>(0) ? outScale.Y : -outScale.Y;
		scale.Z = FakeVector3<T>::Dot(at, GetBackwardVector()) > static_cast<T>(0) ? outScale.Z : -outScale.Z;
		}

	/**
	 * 
	 * Calculates the sum of two matrices.
	 * 
	 * @param left The first matrix to add.
	 * @param right The second matrix to add.
	 * @param result The result containing the sum of the two matrices.
	 */
	static void Add(const FakeMatrix4x4 &left, const FakeMatrix4x4 &right, FakeMatrix4x4 &result)
		{
		result.M11 = left.M11 + right.M11;
		result.M12 = left.M12 + right.M12;
		result.M13 = left.M13 + right.M13;
		result.M14 = left.M14 + right.M14;
		result.M21 = left.M21 + right.M21;
		result.M22 = left.M22 + right.M22;
		result.M23 = left.M23 + right.M23;
		result.M24 = left.M24 + right.M24;
		result.M31 = left.M31 + right.M31;
		result.M32 = left.M32 + right.M32;
		result.M33 = left.M33 + right.M33;
		result.M34 = left.M34 + right.M34;
		result.M41 = left.M41 + right.M41;
		result.M42 = left.M42 + right.M42;
		result.M43 = left.M43 + right.M43;
		result.M44 = left.M44 + right.M44;
		}

	/**
	 * 
	 * Calculates the difference between two matrices.
	 * 
	 * @param left The first matrix to subtract.
	 * @param right The second matrix to subtract.
	 * @param result The result containing the difference of the two matrices.
	 */
	static void Subtract(const FakeMatrix4x4 &left, const FakeMatrix4x4 &right, FakeMatrix4x4 &result)
		{
		result.M11 = left.M11 - right.M11;
		result.M12 = left.M12 - right.M12;
		result.M13 = left.M13 - right.M13;
		result.M14 = left.M14 - right.M14;
		result.M21 = left.M21 - right.M21;
		result.M22 = left.M22 - right.M22;
		result.M23 = left.M23 - right.M23;
		result.M24 = left.M24 - right.M24;
		result.M31 = left.M31 - right.M31;
		result.M32 = left.M32 - right.M32;
		result.M33 = left.M33 - right.M33;
		result.M34 = left.M34 - right.M34;
		result.M41 = left.M41 - right.M41;
		result.M42 = left.M42 - right.M42;
		result.M43 = left.M43 - right.M43;
		result.M44 = left.M44 - right.M44;
		}

	/**
	 * 
	 * Calculates the product of two matrices.
	 * 
	 * @param left The first matrix to multiply.
	 * @param right The second matrix to multiply.
	 * @param result The result containing the multiplication of the two matrices.
	 */
	static void Multiply(const FakeMatrix4x4 &left, const FakeMatrix4x4 &right, FakeMatrix4x4 &result)
		{
		result.M11 = left.M11 * right.M11 + left.M12 * right.M21 + left.M13 * right.M31 + left.M14 * right.M41;
		result.M12 = left.M11 * right.M12 + left.M12 * right.M22 + left.M13 * right.M32 + left.M14 * right.M42;
		result.M13 = left.M11 * right.M13 + left.M12 * right.M23 + left.M13 * right.M33 + left.M14 * right.M43;
		result.M14 = left.M11 * right.M14 + left.M12 * right.M24 + left.M13 * right.M34 + left.M14 * right.M44;
		result.M21 = left.M21 * right.M11 + left.M22 * right.M21 + left.M23 * right.M31 + left.M24 * right.M41;
		result.M22 = left.M21 * right.M12 + left.M22 * right.M22 + left.M23 * right.M32 + left.M24 * right.M42;
		result.M23 = left.M21 * right.M13 + left.M22 * right.M23 + left.M23 * right.M33 + left.M24 * right.M43;
		result.M24 = left.M21 * right.M14 + left.M22 * right.M24 + left.M23 * right.M34 + left.M24 * right.M44;
		result.M31 = left.M31 * right.M11 + left.M32 * right.M21 + left.M33 * right.M31 + left.M34 * right.M41;
		result.M32 = left.M31 * right.M12 + left.M32 * right.M22 + left.M33 * right.M32 + left.M34 * right.M42;
		result.M33 = left.M31 * right.M13 + left.M32 * right.M23 + left.M33 * right.M33 + left.M34 * right.M43;
		result.M34 = left.M31 * right.M14 + left.M32 * right.M24 + left.M33 * right.M34 + left.M34 * right.M44;
		result.M41 = left.M41 * right.M11 + left.M42 * right.M21 + left.M43 * right.M31 + left.M44 * right.M41;
		result.M42 = left.M41 * right.M12 + left.M42 * right.M22 + left.M43 * right.M32 + left.M44 * right.M42;
		result.M43 = left.M41 * right.M13 + left.M42 * right.M23 + left.M43 * right.M33 + left.M44 * right.M43;
		result.M44 = left.M41 * right.M14 + left.M42 * right.M24 + left.M43 * right.M34 + left.M44 * right.M44;
		}

	/**
	 * 
	 * Scales a matrix by the given value.
	 * 
	 * @param left The matrix to scale.
	 * @param right The amount by which to scale.
	 * @param result The result containing the scaled matrix.
	 */
	static void Multiply(const FakeMatrix4x4 &left, T right, FakeMatrix4x4 &result)
		{
		result.M11 = left.M11 * right;
		result.M12 = left.M12 * right;
		result.M13 = left.M13 * right;
		result.M14 = left.M14 * right;
		result.M21 = left.M21 * right;
		result.M22 = left.M22 * right;
		result.M23 = left.M23 * right;
		result.M24 = left.M24 * right;
		result.M31 = left.M31 * right;
		result.M32 = left.M32 * right;
		result.M33 = left.M33 * right;
		result.M34 = left.M34 * right;
		result.M41 = left.M41 * right;
		result.M42 = left.M42 * right;
		result.M43 = left.M43 * right;
		result.M44 = left.M44 * right;
		}

	/**
	 * 
	 * Calculates the quotient of two matrices.
	 * 
	 * @param left The first matrix to divide.
	 * @param right The second matrix to divide.
	 * @param result The result containing the quotient of the two matrices.
	 */
	static void Divide(const FakeMatrix4x4 &left, const FakeMatrix4x4 &right, FakeMatrix4x4 &result)
		{
		// TODO: check if any is zero in right

		result.M11 = left.M11 / right.M11;
		result.M12 = left.M12 / right.M12;
		result.M13 = left.M13 / right.M13;
		result.M14 = left.M14 / right.M14;
		result.M21 = left.M21 / right.M21;
		result.M22 = left.M22 / right.M22;
		result.M23 = left.M23 / right.M23;
		result.M24 = left.M24 / right.M24;
		result.M31 = left.M31 / right.M31;
		result.M32 = left.M32 / right.M32;
		result.M33 = left.M33 / right.M33;
		result.M34 = left.M34 / right.M34;
		result.M41 = left.M41 / right.M41;
		result.M42 = left.M42 / right.M42;
		result.M43 = left.M43 / right.M43;
		result.M44 = left.M44 / right.M44;
		}

	/**
	 * 
	 * Scales a matrix by the given value.
	 * 
	 * @param left The matrix to scale.
	 * @param right The amount by which to scale.
	 * @param result The result containing the scaled matrix.
	 */
	static void Divide(const FakeMatrix4x4 &left, T right, FakeMatrix4x4 &result)
		{
		FAKE_ASSERT(!fake_is_zero(right));
		const T inv = static_cast<T>(1) / right;

		result.M11 = left.M11 * inv;
		result.M12 = left.M12 * inv;
		result.M13 = left.M13 * inv;
		result.M14 = left.M14 * inv;
		result.M21 = left.M21 * inv;
		result.M22 = left.M22 * inv;
		result.M23 = left.M23 * inv;
		result.M24 = left.M24 * inv;
		result.M31 = left.M31 * inv;
		result.M32 = left.M32 * inv;
		result.M33 = left.M33 * inv;
		result.M34 = left.M34 * inv;
		result.M41 = left.M41 * inv;
		result.M42 = left.M42 * inv;
		result.M43 = left.M43 * inv;
		result.M44 = left.M44 * inv;
		}

	/**
	 * 
	 * Negates a matrix.
	 * 
	 * @param value The matrix to be negated.
	 * @param result The result where the negated matrix is stored.
	 */
	static void Negate(const FakeMatrix4x4 &value, FakeMatrix4x4 &result)
		{
		result.M11 = -value.M11;
		result.M12 = -value.M12;
		result.M13 = -value.M13;
		result.M14 = -value.M14;
		result.M21 = -value.M21;
		result.M22 = -value.M22;
		result.M23 = -value.M23;
		result.M24 = -value.M24;
		result.M31 = -value.M31;
		result.M32 = -value.M32;
		result.M33 = -value.M33;
		result.M34 = -value.M34;
		result.M41 = -value.M41;
		result.M42 = -value.M42;
		result.M43 = -value.M43;
		result.M44 = -value.M44;
		}

	/**
	 * 
	 * Calculates the sum of two matrices.
	 * 
	 * @param left The first matrix to add.
	 * @param right The second matrix to add.
	 * @return Returns the sum of the two matrices.
	 */
	static FakeMatrix4x4 Add(const FakeMatrix4x4 &left, const FakeMatrix4x4 &right)
		{
		FakeMatrix4x4 result;
		Add(left, right, result);
		return result;
		}

	/**
	 * 
	 * Calculates the difference between two matrices.
	 * 
	 * @param left The first matrix to subtract.
	 * @param right The second matrix to subtract.
	 * @return Returns the difference of the two matrices.
	 */
	static FakeMatrix4x4 Subtract(const FakeMatrix4x4 &left, const FakeMatrix4x4 &right)
		{
		FakeMatrix4x4 result;
		Subtract(left, right, result);
		return result;
		}

	/**
	 * 
	 * Calculates the product of two matrices.
	 * 
	 * @param left The first matrix to multiply.
	 * @param right The second matrix to multiply.
	 * @return Returns the multiplication of the two matrices.
	 */
	static FakeMatrix4x4 Multiply(const FakeMatrix4x4 &left, const FakeMatrix4x4 &right)
		{
		FakeMatrix4x4 result;
		Multiply(left, right, result);
		return result;
		}

	/**
	 * 
	 * Scales a matrix by the given value.
	 * 
	 * @param left The matrix to scale.
	 * @param right The amount by which to scale.
	 * @return Returns the scaled matrix.
	 */
	static FakeMatrix4x4 Multiply(const FakeMatrix4x4 &left, T right)
		{
		FakeMatrix4x4 result;
		Multiply(left, right, result);
		return result;
		}

	/**
	 * 
	 * Calculates the quotient of two matrices.
	 * 
	 * @param left The first matrix to divide.
	 * @param right The second matrix to divide.
	 * @return Returns the quotient of the two matrices.
	 */
	static FakeMatrix4x4 Divide(const FakeMatrix4x4 &left, const FakeMatrix4x4 &right)
		{
		FakeMatrix4x4 result;
		Divide(left, right, result);
		return result;
		}

	/**
	 * 
	 * Scales a matrix by the given value.
	 * 
	 * @param left The matrix to scale.
	 * @param right The amount by which to scale.
	 * @return Returns the scaled matrix.
	 */
	static FakeMatrix4x4 Divide(const FakeMatrix4x4 &left, T right)
		{
		FakeMatrix4x4 result;
		Divide(left, right, result);
		return result;
		}

	/**
	 * 
	 * Negates a matrix.
	 * 
	 * @param value The matrix to be negated.
	 * @return Returns the negated matrix.
	 */
	static FakeMatrix4x4 Negate(const FakeMatrix4x4 &value)
		{
		FakeMatrix4x4 result;
		Negate(value, result);
		return result;
		}

	/**
	 * 
	 * Calculates the inverse of the specified matrix.
	 * 
	 * @param value The matrix whose inverse is to be calculated.
	 * @param result The result where the inverted matrix is stored in.
	 */
	static void Inverse(const FakeMatrix4x4 &value, FakeMatrix4x4 &result)
		{
		const T b0 = value.M31 * value.M42 - value.M32 * value.M41;
		const T b1 = value.M31 * value.M43 - value.M33 * value.M41;
		const T b2 = value.M34 * value.M41 - value.M31 * value.M44;
		const T b3 = value.M32 * value.M43 - value.M33 * value.M42;
		const T b4 = value.M34 * value.M42 - value.M32 * value.M44;
		const T b5 = value.M33 * value.M44 - value.M34 * value.M43;

		const T d11 = value.M22 *  b5 + value.M23 *  b4 + value.M24 * b3;
		const T d12 = value.M21 *  b5 + value.M23 *  b2 + value.M24 * b1;
		const T d13 = value.M21 * -b4 + value.M22 *  b2 + value.M24 * b0;
		const T d14 = value.M21 *  b3 + value.M22 * -b1 + value.M23 * b0;

		T det = value.M11 * d11 - value.M12 * d12 + value.M13 * d13 - value.M14 * d14;
		if (FAKE_ABS(det) <= static_cast<T>(1e-12))
			{
			result = Zero;
			return;
			}

		// Inverse of determinant
		det = static_cast<T>(1) / det;

		// Build the actual inverse matrix
		const T a0 = value.M11 * value.M22 - value.M12 * value.M21;
		const T a1 = value.M11 * value.M23 - value.M13 * value.M21;
		const T a2 = value.M14 * value.M21 - value.M11 * value.M24;
		const T a3 = value.M12 * value.M23 - value.M13 * value.M22;
		const T a4 = value.M14 * value.M22 - value.M12 * value.M24;
		const T a5 = value.M13 * value.M24 - value.M14 * value.M23;

		const T d21 = value.M12 *  b5 + value.M13 *  b4 + value.M14 * b3;
		const T d22 = value.M11 *  b5 + value.M13 *  b2 + value.M14 * b1;
		const T d23 = value.M11 * -b4 + value.M12 *  b2 + value.M14 * b0;
		const T d24 = value.M11 *  b3 + value.M12 * -b1 + value.M13 * b0;

		const T d31 = value.M42 *  a5 + value.M43 *  a4 + value.M44 * a3;
		const T d32 = value.M41 *  a5 + value.M43 *  a2 + value.M44 * a1;
		const T d33 = value.M41 * -a4 + value.M42 *  a2 + value.M44 * a0;
		const T d34 = value.M41 *  a3 + value.M42 * -a1 + value.M43 * a0;

		const T d41 = value.M32 *  a5 + value.M33 *  a4 + value.M34 * a3;
		const T d42 = value.M31 *  a5 + value.M33 *  a2 + value.M34 * a1;
		const T d43 = value.M31 * -a4 + value.M32 *  a2 + value.M34 * a0;
		const T d44 = value.M31 *  a3 + value.M32 * -a1 + value.M33 * a0;

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

	/**
	 * 
	 * Calculates the inverse of the specified matrix.
	 * 
	 * @param value The matrix whose inverse is to be calculated.
	 * @return Returns the inverted matrix.
	 */
	static FakeMatrix4x4 Inverse(const FakeMatrix4x4 &value)
		{
		FakeMatrix4x4 result;
		Inverse(value, result);
		returnr result;
		}

	/**
	 * 
	 * Calculates the transpose of the specified matrix.
	 * 
	 * @param value The matrix whose transpose is to be calculated.
	 * @param result The result where the transposed matrix is stored.
	 */
	static void Transpose(const FakeMatrix4x4 &value, FakeMatrix4x4 &result)
		{
		FakeMatrix4x4 temp;
		temp.M11 = value.M11;
		temp.M12 = value.M21;
		temp.M13 = value.M31;
		temp.M14 = value.M41;
		temp.M21 = value.M12;
		temp.M22 = value.M22;
		temp.M23 = value.M32;
		temp.M24 = value.M42;
		temp.M31 = value.M13;
		temp.M32 = value.M23;
		temp.M33 = value.M33;
		temp.M34 = value.M43;
		temp.M41 = value.M14;
		temp.M42 = value.M24;
		temp.M43 = value.M34;
		temp.M44 = value.M44;
		result = temp;
		}

	/**
	 * 
	 * Calculates the transpose of the specified matrix.
	 * 
	 * @param value The matrix whose transpose is to be calculated.
	 * @return Returns the transposed matrix.
	 */
	static FakeMatrix4x4 Transpose(const FakeMatrix4x4 &value)
		{
		FakeMatrix4x4 result;
		result.M11 = value.M11;
		result.M12 = value.M21;
		result.M13 = value.M31;
		result.M14 = value.M41;
		result.M21 = value.M12;
		result.M22 = value.M22;
		result.M23 = value.M32;
		result.M24 = value.M42;
		result.M31 = value.M13;
		result.M32 = value.M23;
		result.M33 = value.M33;
		result.M34 = value.M43;
		result.M41 = value.M14;
		result.M42 = value.M24;
		result.M43 = value.M34;
		result.M44 = value.M44;
		return result;
		}

	/**
	 * 
	 * Performs a linear interpolation between two matrices.
	 * 
	 * @param start The start matrix.
	 * @param end The end matrix.
	 * @param amount Value between 0 and 1 indicating the weight of end.
	 * @param result The result where the interpolated matrix is stored in.
	 */
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

	/**
	 * 
	 * Performs a linear interpolation between two matrices.
	 * 
	 * @param start The start matrix.
	 * @param end The end matrix.
	 * @param amount Value between 0 and 1 indicating the weight of end.
	 * @return Returns the interpolated matrix.
	 */
	static FakeMatrix4x4 Lerp(const FakeMatrix4x4 &start, const FakeMatrix4x4 &end, T amount)
		{
		FakeMatrix4x4 result;
		Lerp(start, end, amount, result);
		return result;
		}

	/**
	 * 
	 * Performs a cubic interpolation between two matrices.
	 * 
	 * @param start The start matrix.
	 * @param end The end matrix.
	 * @param amount Value between 0 and 1 indicating the weight of end.
	 * @param result The result where the interpolated matrix is stored in.
	 */
	static void SmoothStep(const FakeMatrix4x4 &start, const FakeMatrix4x4 &end, T amount, FakeMatrix4x4 &result)
		{
		amount = fake_smooth_step(amount);
		Lerp(start, end, amount, result);
		}

	/**
	 * 
	 * Performs a cubic interpolation between two matrices.
	 * 
	 * @param start The start matrix.
	 * @param end The end matrix.
	 * @param amount Value between 0 and 1 indicating the weight of end.
	 * @return Returns the interpolated matrix.
	 */
	static FakeMatrix4x4 SmoothStep(const FakeMatrix4x4 &start, const FakeMatrix4x4 &end, T amount)
		{
		amount = fake_smooth_step(amount);
		return Lerp(start, end, amount);
		}

	/**
	 * 
	 * Creates a left-handed spherical billboard that rotates around a specified object position.
	 * 
	 * @param objectPosition The position of the object around which the billboard will rotate.
	 * @param cameraPosition The position of the camera.
	 * @param cameraUpVector The up vector of the camera.
	 * @param cameraForwardVector The forward vector of the camera.
	 * @param result The result containing the spherical billboard projection.
	 */
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

	/**
	 * 
	 * Creates a left-handed spherical billboard that rotates around a specified object position.
	 * 
	 * @param objectPosition The position of the object around which the billboard will rotate.
	 * @param cameraPosition The position of the camera.
	 * @param cameraUpVector The up vector of the camera.
	 * @param cameraForwardVector The forward vector of the camera.
	 * @return Returns the spherical billboard projection.
	 */
	static FakeMatrix4x4 Billboard(const FakeVector3<T> &objectPosition, const FakeVector3<T> &cameraPosition, const FakeVector3<T> &cameraUpVector, const FakeVector3<T> &cameraForwardVector)
		{
		FakeMatrix4x4 result;
		Billboard(objectPosition, cameraPosition, cameraUpVector, cameraForwardVector, result);
		return result;
		}
	
	/**
	 * 
	 * Creates a left-handed, look-at matrix.
	 * 
	 * @param eye The position of the viewer's eye (mostly camera position).
	 * @param target The camera look-at target (mostly object position).
	 * @param up The camera's up vector.
	 * @param result The result containing the lookAt projection.
	 */
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

	/**
	 * 
	 * Creates a left-handed, look-at matrix.
	 * 
	 * @param eye The position of the viewer's eye (mostly camera position).
	 * @param target The camera look-at target (mostly object position).
	 * @param up The camera's up vector.
	 * @return Returns the lookAt projection.
	 */
	static FakeMatrix4x4 LookAt(const FakeVector3<T> &eye, const FakeVector3<T> &target, const FakeVector3<T> &up)
		{
		FakeMatrix4x4 result;
		LookAt(eye, target, up, result);
		return result;
		}

	/**
	 * 
	 * Creates a left-handed, orthographic projection matrix.
	 * 
	 * @param width The width of the render-region.
	 * @param height The height of the render-region.
	 * @param zNear The minimum z-value of the render-region.
	 * @param zFar The maximum z-value of the render-region.
	 * @param result The result containing the orthographic projection.
	 */
	static void Ortho(T width, T height, T zNear, T zFar, FakeMatrix4x4 &result)
		{
		const T halfWidth = width * static_cast<T>(0.5);
		const T halfHeight = height * static_cast<T>(0.5);
		OrthoOffCenter(-halfWidth, halfWidth, -halfHeight, halfHeight, zNear, zFar, result);
		}

	/**
	 * 
	 * Creates a left-handed, orthographic projection matrix.
	 * 
	 * @param width The width of the render-region.
	 * @param height The height of the render-region.
	 * @param zNear The minimum z-value of the render-region.
	 * @param zFar The maximum z-value of the render-region.
	 * @return Returns the orthographic projection.
	 */
	static FakeMatrix4x4 Ortho(T width, T height, T zNear, T zFar)
		{
		FakeMatrix4x4 result;
		const T halfWidth = width * static_cast<T>(0.5);
		const T halfHeight = height * static_cast<T>(0.5);
		OrthoOffCenter(-halfWidth, halfWidth, -halfHeight, halfHeight, zNear, zFar, result);
		return result;
		}

	/**
	 * 
	 * Creates a left-handed, customized orthographic projection matrix.
	 * 
	 * @param left The minimum x-value of the render-region.
	 * @param right The maximum x-value of the render-region.
	 * @param bottom The minimum y-value of the render-region.
	 * @param top The maximum y-value of the render-region.
	 * @param zNear The minimum z-value of the render-region.
	 * @param zFar The maximum z-value of the render-region.
	 * @param result The result containing the orthographic projection.
	 */
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

	/**
	 * 
	 * Creates a left-handed, customized orthographic projection matrix.
	 * 
	 * @param left The minimum x-value of the render-region.
	 * @param right The maximum x-value of the render-region.
	 * @param bottom The minimum y-value of the render-region.
	 * @param top The maximum y-value of the render-region.
	 * @param zNear The minimum z-value of the render-region.
	 * @param zFar The maximum z-value of the render-region.
	 * @return Returns the orthographic projection.
	 */
	static FakeMatrix4x4 OrthoOffCenter(T left, T right, T bottom, T top, T zNear, T zFar)
		{
		FakeMatrix4x4 result;
		OrthoOffCenter(left, right, bottom, top, zNear, zFar, result);
		return result;
		}

	/**
	 * 
	 * Creates a left-handed, perspective projection matrix.
	 * 
	 * @param width The width of the render-region.
	 * @param height The height of the render-region.
	 * @param zNear The minimum z-value of the render-region.
	 * @param zFar The maximum z-value of the render-region.
	 * @param result The result containing the perspective projection.
	 */
	static void Perspective(T width, T height, T zNear, T zFar, FakeMatrix4x4 &result)
		{
		const T halfWidth = width * static_cast<T>(0.5);
		const T halfHeight = height * static_cast<T>(0.5);
		PerspectiveOffCenter(-halfWidth, halfWidth, -halfHeight, halfHeight, zNear, zFar, result);
		}

	/**
	 * 
	 * Creates a left-handed, perspective projection matrix.
	 * 
	 * @param width The width of the render-region.
	 * @param height The height of the render-region.
	 * @param zNear The minimum z-value of the render-region.
	 * @param zFar The maximum z-value of the render-region.
	 * @return Returns the perspective projection.
	 */
	static FakeMatrix4x4 Perspective(T width, T height, T zNear, T zFar)
		{
		FakeMatrix4x4 result;
		const T halfWidth = width * static_cast<T>(0.5);
		const T halfHeight = height * static_cast<T>(0.5);
		PerspectiveOffCenter(-halfWidth, halfWidth, -halfHeight, halfHeight, zNear, zFar, result);
		return result;
		}

	/**
	 * 
	 * Creates a left-handed, customized orthographic projection matrix.
	 * 
	 * @param left The minimum x-value of the render-region.
	 * @param right The maximum x-value of the render-region
	 * @param bottom The minimum y-value of the render-region
	 * @param top The maximum y-value of the render-region
	 * @param zNear The minimum z-value of the render-region
	 * @param zFar The maximum z-value of the render-region
	 * @param result The result containing the perspective projection.
	 */
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

	/**
	 * 
	 * Creates a left-handed, customized orthographic projection matrix.
	 * 
	 * @param left The minimum x-value of the render-region
	 * @param right The maximum x-value of the render-region
	 * @param bottom The minimum y-value of the render-region
	 * @param top The maximum y-value of the render-region
	 * @param zNear The minimum z-value of the render-region
	 * @param zFar The maximum z-value of the render-region
	 * @return Returns the perspective projection.
	 */
	static FakeMatrix4x4 PerspectiveOffCenter(T left, T right, T bottom, T top, T zNear, T zFar)
		{
		FakeMatrix4x4 result;
		PerspectiveOffCenter(left, right, bottom, top, zNear, zFar, result);
		return result;
		}

	/**
	 * 
	 * Creates a left-handed, perspective projection matrix based on a field of view.
	 * 
	 * @param fov The field of view.
	 * @param aspectRatio The aspect ratio of the window (window width / window height).
	 * @param zNear The minimum z-value of the render-region.
	 * @param zFar The maximum z-value of the render-region.
	 * @param result The result containing the perspective projection.
	 */
	static void PerspectiveFOV(T fov, T aspectRatio, T zNear, T zFar, FakeMatrix4x4 &result)
		{
		const T yScale = static_cast<T>(1) / fake_tan(fov * static_cast<T>(0.5));
		const T xScale = yScale / aspectRatio;

		const T halfWidth = zNear / xScale;
		const T halfHeight = zNear / yScale;

		PerspectiveOffCenter(-halfWidth, halfWidth, -halfHeight, halfHeight, zNear, zFar, result);
		}

	/**
	 * 
	 * Creates a left-handed, perspective projection matrix based on a field of view.
	 * 
	 * @param fov The field of view.
	 * @param aspectRatio The aspect ratio of the window (window width / window height).
	 * @param zNear The minimum z-value of the render-region.
	 * @param zFar The maximum z-value of the render-region.
	 * @return Returns the perspective projection.
	 */
	static FakeMatrix4x4 PerspectiveFOV(T fov, T aspectRatio, T zNear, T zFar)
		{
		FakeMatrix4x4 result;
		PerspectiveFOV(fov, aspectRatio, zNear, zFar, result);
		return result;
		}

	/**
	 * 
	 * Creates a translation matrix.
	 * 
	 * @param translation The translation which should be applied.
	 * @param result The result containing the translation matrix.
	 */
	static void Translate(const FakeVector3<T> &translation, FakeMatrix4x4 &result)
		{
		result = Identity;
		result.M41 = translation.X;
		result.M42 = translation.Y;
		result.M43 = translation.Z;
		}

	/**
	 * 
	 * Creates a translation matrix.
	 * 
	 * @param translation The translation which should be applied.
	 * @return Returns the translation matrix.
	 */
	static FakeMatrix4x4 Translate(const FakeVector3<T> &translation)
		{
		FakeMatrix4x4 result;
		Translate(translation, result);
		return result;
		}

	/**
	 * 
	 * Creates a scale matrix.
	 * 
	 * @param scale The scale which should be applied.
	 * @param result The result containing the scale matrix.
	 */
	static void Scale(const FakeVector3<T> &scale, FakeMatrix4x4 &result)
		{
		result = Identity;
		result.M11 = scale.X;
		result.M22 = scale.Y;
		result.M33 = scale.Z;
		}

	/**
	 * 
	 * Creates a scale matrix.
	 * 
	 * @param scale The scale which should be applied.
	 * @return Returns the scale matrix.
	 */
	static FakeMatrix4x4 Scale(const FakeVector3<T> &scale)
		{
		FakeMatrix4x4 result;
		Scale(scale, result);
		return result;
		}

	/**
	 * 
	 * Creates a scale matrix.
	 * 
	 * @param scale The scale which should be applied.
	 * @param result The result containing the scale matrix.
	 */
	static void Scale(T scale, FakeMatrix4x4 &result)
		{
		result = Identity;
		result.M11 = scale;
		result.M22 = scale;
		result.M33 = scale;
		}

	/**
	 * 
	 * Creates a scale matrix.
	 * 
	 * @param scale The scale which should be applied.
	 * @return Returns the scale matrix.
	 */
	static FakeMatrix4x4 Scale(T scale)
		{
		FakeMatrix4x4 result;
		Scale(scale, result);
		return result;
		}

	/**
	 * 
	 * Creates a matrix that rotates around an arbitrary axis.
	 * 
	 * @param angle The angle of rotation in radians. Angles are measured clockwise when looking along the rotation axis toward the origin.
	 * @param axis The axis around which to rotate. This parameter is assumed to be normalized.
	 * @param result The result containing the rotation matrix.
	 */
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

	/**
	 * 
	 * Creates a matrix that rotates around an arbitrary axis.
	 * 
	 * @param angle The angle of rotation in radians. Angles are measured clockwise when looking along the rotation axis toward the origin.
	 * @param axis The axis around which to rotate. This parameter is assumed to be normalized.
	 * @return Returns the rotation matrix.
	 */
	static FakeMatrix4x4 Rotate(T angle, const FakeVector3<T> &axis)
		{
		FakeMatrix4x4 result;
		Rotate(angle, axis, result);
		return result;
		}

	/**
	 * 
	 * Creates a rotation matrix from a quaternion.
	 * 
	 * @param rotation The quaternion to use to build the matrix.
	 * @param result The result containing the rotation matrix.
	 */
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

	/**
	 * 
	 * Creates a rotation matrix from a quaternion.
	 * 
	 * @param rotation The quaternion to use to build the matrix.
	 * @return Returns the rotation matrix.
	 */
	static FakeMatrix4x4 Rotate(const FakeQuaternion<T> &rotation)
		{
		FakeMatrix4x4 result;
		Rotate(rotation, result);
		return result;
		}

	/**
	 * 
	 * Creates a rotation matrix using Euler angles.
	 * 
	 * @param yaw The yaw component of the euler angles.
	 * @param pitch The pitch component of the euler angles.
	 * @param roll The roll component of the euler angles.
	 * @param result The result containing the rotation matrix.
	 */
	static void Rotate(T yaw, T pitch, T roll, FakeMatrix4x4 &result)
		{
		FakeQuaternion<T> quaternion;
		FakeQuaternion<T>::RotationEuler(yaw, pitch, roll, quaternion);
		Rotate(quaternion, result);
		}

	/**
	 * 
	 * Creates a rotation matrix using Euler angles.
	 * 
	 * @param yaw The yaw component of the euler angles.
	 * @param pitch The pitch component of the euler angles.
	 * @param roll The roll component of the euler angles.
	 * @return Returns the rotation matrix.
	 */
	static FakeMatrix4x4 Rotate(T yaw, T pitch, T roll)
		{
		FakeMatrix4x4 result;
		Rotate(yaw, pitch, roll, result);
		return result;
		}

	/**
	 * 
	 * Creates a rotation matrix using a specified angle and applying it to the X-Axis.
	 * 
	 * @param angle The angle of rotation in radians. Angles are measured clockwise when looking along the rotation axis toward the origin.
	 * @param result Returns the rotation matrix.
	 */
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

	/**
	 * 
	 * Creates a rotation matrix using a specified angle and applying it to the X-Axis.
	 * 
	 * @param angle The angle of rotation in radians. Angles are measured clockwise when looking along the rotation axis toward the origin.
	 * @return Returns the rotation matrix.
	 */
	static FakeMatrix4x4 RotateX(T angle)
		{
		FakeMatrix4x4 result;
		RotateX(angle, result);
		return result;
		}

	/**
	 * 
	 * Creates a rotation matrix using a specified angle and applying it to the Y-Axis.
	 * 
	 * @param angle The angle of rotation in radians. Angles are measured clockwise when looking along the rotation axis toward the origin.
	 * @param result Returns the rotation matrix.
	 */
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

	/**
	 * 
	 * Creates a rotation matrix using a specified angle and applying it to the Y-Axis.
	 * 
	 * @param angle The angle of rotation in radians. Angles are measured clockwise when looking along the rotation axis toward the origin.
	 * @return Returns the rotation matrix.
	 */
	static FakeMatrix4x4 RotateY(T angle)
		{
		FakeMatrix4x4 result;
		RotateY(angle, result);
		return result;
		}

	/**
	 * 
	 * Creates a rotation matrix using a specified angle and applying it to the Z-Axis.
	 * 
	 * @param angle The angle of rotation in radians. Angles are measured clockwise when looking along the rotation axis toward the origin.
	 * @param result Returns the rotation matrix.
	 */
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

	/**
	 * 
	 * Creates a rotation matrix using a specified angle and applying it to the Z-Axis.
	 * 
	 * @param angle The angle of rotation in radians. Angles are measured clockwise when looking along the rotation axis toward the origin.
	 * @return Returns the rotation matrix.
	 */
	static FakeMatrix4x4 RotateZ(T angle)
		{
		FakeMatrix4x4 result;
		RotateZ(angle, result);
		return result;
		}

	/**
	 * 
	 * Creates a skew/shear matrix by means of a translation vector, a rotation vector, and a rotation angle.
	 * 
	 * @param angle The rotation angle.
	 * @param translationVec The translation vector.
	 * @param rotationVec The rotation vector.
	 * @param result The result containing the created skew/shear matrix.
	 */
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

		FAKE_ASSERT(rr0 >= MINIMAL_SKEW_ANGLE);

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

	/**
	 * 
	 * Creates a skew/shear matrix by means of a translation vector, a rotation vector, and a rotation angle.
	 * 
	 * @param angle The rotation angle.
	 * @param translationVec The translation vector.
	 * @param rotationVec The rotation vector.
	 * @return Returns the created skew/shear matrix.
	 */
	static FakeMatrix4x4 Skew(T angle, const FakeVector3<T> &translationVec, const FakeVector3<T> &rotationVec)
		{
		FakeMatrix4x4 result;
		Skew(angle, translationVec, rotationVec, result);
		return result;
		}

	/**
	 * 
	 * Creates a matrix that contains both the X, Y and Z rotation, as well as scaling and translation.
	 * 
	 * @param translation The translation.
	 * @param rotation The angle of rotation in radians. Angles are measured clockwise when looking along the rotation axis toward the origin.
	 * @param scaling The scaling.
	 * @param result The result containing the transformation matrix.
	 */
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

	/**
	 * 
	 * Creates a transformation matrix.
	 * 
	 * @param translation The translation factor of the transformation.
	 * @param rotation The rotation of the transformation.
	 * @param rotationCenter The center of the rotation.
	 * @param scaling The scaling factor.
	 * @param scalingCenter The center point of the scaling operation.
	 * @param scalingRotation The scaling rotation amount.
	 * @param result The result containing the transformation matrix.
	 */
	static void Transform(const FakeVector3<T> &translation, const FakeQuaternion<T> &rotation, const FakeVector3<T> &rotationCenter, const FakeVector3<T> &scaling, const FakeVector3<T> &scalingCenter, const FakeQuaternion<T> &scalingRotation, FakeMatrix4x4 &result)
		{
		FakeMatrix4x4 sr;
		Rotate(scalingRotation, sr);
		result = Translate(-scalingCenter) * Transpose(sr) * Scale(scaling) * sr * Translate(scalingCenter) * Translate(-rotationCenter) * Rotate(rotation) * Translate(rotationCenter) * Translate(translation);
		}

	/**
	 * 
	 * Creates a 3D affine transformation matrix.
	 * 
	 * @param translation The translation factor of the transformation.
	 * @param rotation The rotation of the transformation.
	 * @param scaling The scaling factor.
	 * @param result The result containing the affine transformation matrix.
	 */
	static void AffineTransform(const FakeVector3<T> &translation, const FakeQuaternion<T> &rotation, T scaling, FakeMatrix4x4 &result)
		{
		result = Scale(scaling) * Rotate(rotation) * Translate(translation);
		}

	/**
	 * 
	 * Creates a 3D affine transformation matrix.
	 * 
	 * @param translation The translation factor of the transformation.
	 * @param rotation The rotation of the transformation.
	 * @param rotationCenter The center of the rotation.
	 * @param scaling The scaling factor.
	 * @param result The result containing the affine transformation matrix.
	 */
	static void AffineTransform(const FakeVector3<T> &translation, const FakeQuaternion<T> &rotation, const FakeVector3<T> &rotationCenter, T scaling, FakeMatrix4x4 &result)
		{
		result = Scale(scaling) * Translate(-rotationCenter) * Rotate(rotation) * Translate(rotationCenter) * Translate(translation);
		}

	/**
	 * 
	 * Creates a 2D affine transformation matrix.
	 * 
	 * @param translation The translation factor of the transformation.
	 * @param rotation The rotation of the transformation.
	 * @param scaling The scaling factor.
	 * @param result The result containing the affine 2D transformation matrix.
	 */
	static void AffineTransform2D(const FakeVector2<T> &translation, T rotation, T scaling, FakeMatrix4x4 &result)
		{
		result = Scale({ scaling, scaling, static_cast<T>(1) }) * RotateZ(rotation) * Translate({ translation.X, translation.Y, static_cast<T>(0) });
		}

	/**
	 * 
	 * Creates a 2D affine transformation matrix.
	 * 
	 * @param translation The translation factor of the transformation.
	 * @param rotation The rotation of the transformation.
	 * @param rotationCenter The center of the rotation.
	 * @param scaling The scaling factor.
	 * @param result The result containing the affine 2D transformation matrix.
	 */
	static void AffineTransform2D(const FakeVector2<T> &translation, T rotation, const FakeVector2<T> &rotationCenter, T scaling, FakeMatrix4x4 &result)
		{
		result = Scale({ scaling, scaling, static_cast<T>(1) }) * Translate({ -rotationCenter.X, -rotationCenter.Y, static_cast<T>(0) }) * RotateZ(rotation) * Translate({ rotationCenter.X, rotationCenter.Y, static_cast<T>(0) }) * Translate({ translation.X, translation.Y, static_cast<T>(0) });
		}

	/**
	 * 
	 * Creates a 2D transformation matrix.
	 * 
	 * @param translation The translation factor of the transformation.
	 * @param rotation The rotation of the transformation.
	 * @param rotationCenter The center of the rotation.
	 * @param scaling The scaling factor.
	 * @param scalingCenter The center point of the scaling operation.
	 * @param scalingRotation The scaling rotation amount.
	 * @param result The result containing the 2D transformation matrix.
	 */
	static void Transform2D(const FakeVector2<T> &translation, T rotation, const FakeVector2<T> &rotationCenter, const FakeVector2<T> &scaling, FakeVector2<T> &scalingCenter, T scalingRotation, FakeMatrix4x4 &result)
		{
		result = Translate({ -scalingCenter.X, -scalingCenter.Y, static_cast<T>(0) }) * RotateZ(-scalingRotation) * Scale({ scaling.X, scaling.Y, static_cast<T>(0) }) * RotateZ(scalingRotation) * Translate({ scalingCenter.X, scalingCenter.Y, static_cast<T>(0) }) * Translate({ -rotationCenter.X, -rotationCenter.Y, static_cast<T>(0) }) * RotateZ(rotation) * Translate({ rotationCenter.X, rotationCenter.Y, static_cast<T>(0) }) * Translate({ translation.X, translation.Y, static_cast<T>(0) });
		result.M33 = static_cast<T>(1);
		result.M44 = static_cast<T>(1);
		}

	/**
	 * 
	 * Creates a world matrix with the specified parameters.
	 * 
	 * @param position The position of the object. This value is used in translation operations.
	 * @param forward The forward direction of the object.
	 * @param up The upward direction of the object - normally (0, 1, 0).
	 * @param result Returns created world matrix.
	 */
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

	/**
	 * 
	 * Creates a new Matrix that rotates around an arbitrary vector.
	 * 
	 * @param position The position of the object. This value is used in translation operations.
	 * @param forward The forward direction of the object.
	 * @param up The upward direction of the object - normally (0, 1, 0).
	 * @return Returns created world matrix.
	 */
	static FakeMatrix4x4 CreateWorldMatrix(const FakeVector3<T> &position, const FakeVector3<T> &forward, const FakeVector3<T> &up)
		{
		FakeMatrix4x4 result;
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

		return result;
		}

	/**
	 * 
	 * Creates a new Matrix that rotates around an arbitrary vector.
	 * 
	 * @param axis The axis to rotate around.
	 * @param angle The angle to rotate around the vector.
	 * @param result The result containing the matrix that rotates around an arbitrary vector.
	 */
	static void CreateFromAxis(const FakeVector3<T> &axis, T angle, FakeMatrix4x4 &result)
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

	/**
	 * 
	 * Creates a new Matrix that rotates around an arbitrary vector.
	 * 
	 * @param axis The axis to rotate around.
	 * @param angle The angle to rotate around the vector.
	 * @return Returns a matrix that rotates around an arbitrary vector.
	 */
	static FakeMatrix4x4 CreateFromAxis(const FakeVector3<T> &axis, T angle)
		{
		FakeMatrix4x4 result;

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

		return result;
		}

	/**
	 * 
	 * Overloaded + operator.
	 * 
	 * @param other The Matrix to add.
	 * @return Returns the current matrix instance containing the sum of the addition.
	 */
	FakeMatrix4x4 operator+(const FakeMatrix4x4 &other) const
		{
		FakeMatrix4x4 result;
		Add(*this, other, result);
		return result;
		}

	/**
	 * 
	 * Overloaded - operator.
	 * 
	 * @param other The matrix to subtract.
	 * @return Returns the current matrix instance containing the difference of the subtraction.
	 */
	FakeMatrix4x4 operator-(const FakeMatrix4x4 &other) const
		{
		FakeMatrix4x4 result;
		Subtract(*this, other, result);
		return result;
		}

	/**
	 * 
	 * Overloaded * operator.
	 * 
	 * @param other The Matrix to multiply.
	 * @return Returns the current matrix instance containing the multiplication.
	 */
	FakeMatrix4x4 operator*(const FakeMatrix4x4 &other) const
		{
		FakeMatrix4x4 result;
		Multiply(*this, other, result);
		return result;
		}

	/**
	 * 
	 * Overloaded * operator.
	 * 
	 * @param scalar The scalar to multiply.
	 * @return Returns the current matrix instance containing the multiplication.
	 */
	FakeMatrix4x4 operator*(T scalar) const
		{
		FakeMatrix4x4 result;
		Multiply(*this, scalar, result);
		return result;
		}

	/**
	 * 
	 * Overloaded / operator.
	 * 
	 * @param other The matrix to divide.
	 * @return Returns the current matrix instance containing the division.
	 */
	FakeMatrix4x4 operator/(const FakeMatrix4x4 &other) const
		{
		FakeMatrix4x4 result;
		Divide(*this, other, result);
		return result;
		}

	/**
	 * 
	 * Overloaded / operator.
	 * 
	 * @param scalar The scalar to divide.
	 * @return Returns the current matrix instance containing the division.
	 */
	FakeMatrix4x4 operator/(T scalar) const
		{
		FakeMatrix4x4 result;
		Divide(*this, scalar, result);
		return result;
		}

	/**
	 * 
	 * Overloaded += operator.
	 * 
	 * @param other The matrix to add.
	 * @return Returns the current matrix instance containing the sum of the addition.
	 */
	FakeMatrix4x4 &operator+=(const FakeMatrix4x4 &other)
		{
		Add(*this, other, *this);
		return *this;
		}

	/**
	 * 
	 * Overloaded -= operator.
	 * 
	 * @param other The matrix to subtract.
	 * @return Returns the current matrix instance containing the difference of the subtraction.
	 */
	FakeMatrix4x4 &operator-=(const FakeMatrix4x4 &other)
		{
		Subtract(*this, other, *this);
		return *this;
		}

	/**
	 * 
	 * Overloaded *= operator.
	 * 
	 * @param other The matrix to multiply.
	 * @return Returns the current matrix instance containing the multiplication.
	 */
	FakeMatrix4x4 &operator*=(const FakeMatrix4x4 &other)
		{
		Multiply(*this, other, *this);
		return *this;
		}

	/**
	 * 
	 * Overloaded *= operator.
	 * 
	 * @param scalar The scalar to multiply.
	 * @return Returns the current matrix instance containing the multiplication.
	 */
	FakeMatrix4x4 &operator*=(T scalar)
		{
		Multiply(*this, scalar, *this);
		return *this;
		}

	/**
	 * 
	 * Overloaded /= operator.
	 * 
	 * @param other The Matrix to divide.
	 * @return Returns the current matrix instance containing the division.
	 */
	FakeMatrix4x4 &operator/=(const FakeMatrix4x4 &other)
		{
		Divide(*this, other, *this);
		return *this;
		}

	/**
	 * 
	 * Overloaded /= operator.
	 * 
	 * @param scalar The scalar to divide.
	 * @return Returns the current matrix instance containing the division.
	 */
	FakeMatrix4x4 &operator/=(T scalar)
		{
		Divide(*this, scalar, *this);
		return *this;
		}

	/**
	 * 
	 * Overloaded == operator.
	 * 
	 * @param other The matrix to compare.
	 * @return Returns true if the matrices are identical - otherwise false.
	 */
	bool operator==(const FakeMatrix4x4 &other) const
		{
		return
			fake_near_equal(M11, other.M11) &&
			fake_near_equal(M12, other.M12) &&
			fake_near_equal(M13, other.M13) &&
			fake_near_equal(M14, other.M14) &&
			fake_near_equal(M21, other.M21) &&
			fake_near_equal(M22, other.M22) &&
			fake_near_equal(M23, other.M23) &&
			fake_near_equal(M24, other.M24) &&
			fake_near_equal(M31, other.M31) &&
			fake_near_equal(M32, other.M32) &&
			fake_near_equal(M33, other.M33) &&
			fake_near_equal(M34, other.M34) &&
			fake_near_equal(M41, other.M41) &&
			fake_near_equal(M42, other.M42) &&
			fake_near_equal(M43, other.M43) &&
			fake_near_equal(M44, other.M44);
		}

	/**
	 * 
	 * Overloaded != operator.
	 * 
	 * @param other The matrix to compare.
	 * @return Returns true if the matrices are not identical - otherwise false.
	 */
	bool operator!=(const FakeMatrix4x4 &other) const
		{
		return !(*this == other);
		}

	/**
	 * 
	 * Overloaded < operator.
	 * 
	 * @param other The matrix to compare.
	 * @return Returns true if the provided matrix is greater than the current instance - otherwise false.
	 */
	bool operator<(const FakeMatrix4x4 &other) const
		{
		return
			M11 < other.M11 &&
			M12 < other.M12 &&
			M13 < other.M13 &&
			M14 < other.M14 &&
			M21 < other.M21 &&
			M22 < other.M22 &&
			M23 < other.M23 &&
			M24 < other.M24 &&
			M31 < other.M31 &&
			M32 < other.M32 &&
			M33 < other.M33 &&
			M34 < other.M34 &&
			M41 < other.M41 &&
			M42 < other.M42 &&
			M43 < other.M43 &&
			M44 < other.M44;
		}

	/**
	 * 
	 * Overloaded <= operator.
	 * 
	 * @param other The matrix to compare.
	 * @return Returns true if the provided matrix is greater or equal to the current instance - otherwise false.
	 */
	bool operator<=(const FakeMatrix4x4 &other) const
		{
		return
			M11 <= other.M11 &&
			M12 <= other.M12 &&
			M13 <= other.M13 &&
			M14 <= other.M14 &&
			M21 <= other.M21 &&
			M22 <= other.M22 &&
			M23 <= other.M23 &&
			M24 <= other.M24 &&
			M31 <= other.M31 &&
			M32 <= other.M32 &&
			M33 <= other.M33 &&
			M34 <= other.M34 &&
			M41 <= other.M41 &&
			M42 <= other.M42 &&
			M43 <= other.M43 &&
			M44 <= other.M44;
		}

	/**
	 * 
	 * Overloaded > operator.
	 * 
	 * @param other The matrix to compare.
	 * @return Returns true if the provided matrix is less than the current instance - otherwise false.
	 */
	bool operator>(const FakeMatrix4x4 &other) const
		{
		return
			M11 > other.M11 &&
			M12 > other.M12 &&
			M13 > other.M13 &&
			M14 > other.M14 &&
			M21 > other.M21 &&
			M22 > other.M22 &&
			M23 > other.M23 &&
			M24 > other.M24 &&
			M31 > other.M31 &&
			M32 > other.M32 &&
			M33 > other.M33 &&
			M34 > other.M34 &&
			M41 > other.M41 &&
			M42 > other.M42 &&
			M43 > other.M43 &&
			M44 > other.M44;
		}

	/**
	 * 
	 * Overloaded >= operator.
	 * 
	 * @param other The matrix to compare.
	 * @return Returns true if the provided matrix is less or equal to the current instance - otherwise false.
	 */
	bool operator>=(const FakeMatrix4x4 &other) const
		{
		return
			M11 >= other.M11 &&
			M12 >= other.M12 &&
			M13 >= other.M13 &&
			M14 >= other.M14 &&
			M21 >= other.M21 &&
			M22 >= other.M22 &&
			M23 >= other.M23 &&
			M24 >= other.M24 &&
			M31 >= other.M31 &&
			M32 >= other.M32 &&
			M33 >= other.M33 &&
			M34 >= other.M34 &&
			M41 >= other.M41 &&
			M42 >= other.M42 &&
			M43 >= other.M43 &&
			M44 >= other.M44;
		}

	/**
	 *
	 * copy operator.
	 *
	 * @param The Matrix to copy.
	 * @return Returns the copied instance.
	 */
	FakeMatrix4x4 &operator=(const FakeMatrix4x4 &other)
		{
		for (uint32 i = 0; i < 16; ++i)
			{
			Raw[i] = other.Raw[i];
			}

		return *this;
		}

	/**
	 *
	 * Overloaded dereferncing operator to get the matrix data as an array.
	 *
	 * @return Returns an array filled with the content of the matrix.
	 */
	T *operator*()
		{
		static T arr[16];

		for (int32 i = 0; i < 16; ++i)
			arr[i] = Raw[i];

		return arr;
		}

	/**
	 *
	 * Overloaded dereferncing operator to get the matrix data as an array.
	 *
	 * @return Returns an array filled with the content of the matrix.
	 */
	const T *operator*() const
		{
		static T arr[16];

		for (int32 i = 0; i < 16; ++i)
			arr[i] = Raw[i];

		return arr;
		}

	/**
	 *
	 * Overloaded Array Indexing operator to access the content of the matrix directly like an array.
	 *
	 * @param index The index where the matrix instance should be accessed.
	 * @return Returns the content at the specified index.
	 */
	T &operator[](uint32 index)
		{
		FAKE_ASSERT(index < 16);
		return Raw[index];
		}

	/**
	 *
	 * Overloaded Array Indexing operator to access the content of the matrix directly like an array.
	 *
	 * @param index The index where the matrix instance should be accessed.
	 * @return Returns the content at the specified index.
	 */
	const T &operator[](uint32 index) const
		{
		FAKE_ASSERT(index < 16);
		return Raw[index];
		}

	/**
	 * 
	 * Overloaded << operator to print the Matrix into a output stream.
	 * 
	 * @param stream The output stream.
	 * @param matrix The matrix to print.
	 * @return Returns the modified output stream.
	 */
	friend std::ostream &operator<<(std::ostream &stream, const FakeMatrix4x4 &matrix)
		{
		stream << matrix.M11 << ", " << matrix.M12 << ", " << matrix.M13 << ", " << matrix.M14 << ",\n";
		stream << matrix.M21 << ", " << matrix.M22 << ", " << matrix.M23 << ", " << matrix.M24 << ",\n";
		stream << matrix.M31 << ", " << matrix.M32 << ", " << matrix.M33 << ", " << matrix.M34 << ",\n";
		stream << matrix.M41 << ", " << matrix.M42 << ", " << matrix.M43 << ", " << matrix.M44;
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

