/*****************************************************************
 * \file   FakeMathFunctions.h
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

#include <math.h>

#define FAKE_PI 3.1415926535897932f
#define FAKE_TWO_PI 6.28318530718f
#define FAKE_PI_INV 0.31830988618f
#define FAKE_PI_OVER_2 1.57079632679f
#define FAKE_PI_OVER_4 0.78539816339f
#define FAKE_PI_HALF FAKE_PI_OVER_2

 // The value for which all absolute numbers smaller than are considered equal to zero.
#define FAKE_ZERO_TOLERANCE 1e-6f

/**
 * 
 * Converts degrees into radians.
 * 
 * @param degrees The degrees that should be converted to radians.
 * @return Returns the converted radians.
 */
template<typename T>
static T fake_radians(T degrees)
	{
	return degrees * static_cast<T>(FAKE_PI * 180.0f);
	}

/**
 * 
 * Converts radians into degrees.
 * 
 * @param radians The radians that should be converted to degrees.
 * @return Returns the converted degrees.
 */
template<typename T>
static T fake_degrees(T radians)
	{
	return radians * static_cast<T>(180.0f / FAKE_PI);
	}

/**
 * 
 * Returns the minimum value of a specific type.
 * 
 * @return Returns the minimum value of a specific type.
 */
template<typename T>
static T fake_min()
	{
	return std::numeric_limits<T>::min();
	}

/**
 * 
 * Returns the maximum value of a specific type.
 * 
 * @return Returns the maximum value of a specific type.
 */
template<typename T>
static T fake_max()
	{
	return std::numeric_limits<T>::max();
	}

/**
 * 
 * Builds the faculty of any number.
 * 
 * @param num The number from which the faculty should be build.
 * @return Returns the faculty of a given number.
 */
template<typename T>
static T fake_faculty(T num)
	{
	T ret = static_cast<T>(1);
	T i;

	for (i = ret; i <= num; ++i)
		ret *= i;

	return ret;
	}

/**
 * 
 * The pow function multiplies a value x times with itself.
 * 
 * ### Example
 * <b>fake_pow(4, 2);</b> would translate into the equation: 4 * 4 = 16 -> 16 would be returned.
 * 
 * @param basis The basis that should get multiplied with itself.
 * @param potenz The amount that the basis should get multiplied.
 * @return Returns the basis multiplied potenz times.
 */
template<typename T>
static T fake_pow(T basis, uint32 potenz)
	{
	if (static_cast<T>(0) == potenz)
		return static_cast<T>(1);

	T ret = basis;
	uint32 i;

	for (i = 0; i < potenz; ++i)
		ret *= basis;

	return ret;
	}

/**
 * 
 * Calculates the square root of x.
 * 
 * @param x The value where the square root should be built from.
 * @return Returns the square root number.
 */
template<typename T>
static FAKE_FORCE_INLINE T fake_sqrt(T x)
	{
	// HINT: fake_sqrt returns wrong values if ints are provided as argument
	T ret = static_cast<T>(1);
	uint32 i;

	for (i = 0; i <= 10; ++i)
		ret -= (ret * ret - x) / (static_cast<T>(2) * ret);

	return ret;
	}

/**
 * 
 * .
 * 
 * @param value
 * @param alignment
 * @return 
 */
template<typename T>
static T fake_divide_by_multiple(T value, T alignment)
	{
	T mask = alignment - 1;
	return (T)((value + mask) / alignment);
	}

/**
 * 
 * Divides two integers and rounds up.
 * 
 * @param dividend The Dividend.
 * @param divisor The Divisor.
 * @return Returns the rounded division result.
 */
template<typename T>
static FAKE_FORCE_INLINE T fake_divide_and_round_up(T dividend, T divisor)
	{
	return (dividend + divisor - 1) / divisor;
	}

/**
 * 
 * Divides two integers and rounds down.
 * 
 * @param dividend The Dividend.
 * @param divisor The Divisor.
 * @return Returns the rounded division result.
 */
template<typename T>
static FAKE_FORCE_INLINE T fake_divide_and_round_down(T dividend, T divisor)
	{
	return dividend / divisor;
	}

/**
 * 
 * Checks if value is inside a given range.
 * 
 * @param value The value to check.
 * @param min The minimum value.
 * @param max The maximum value.
 * @return Returns true if the given value is in the given range.
 */
template<typename T>
static bool fake_is_in_range(const T value, const T min, const T max)
	{
	return value >= min && value <= max;
	}

/**
 * 
 * Checks if value is not inside a given range.
 * 
 * @param value The value to check.
 * @param min The minimum value.
 * @param max The maximum value.
 * @return Returns true if the given value is not in the given range.
 */
template<typename T>
static bool fake_is_not_in_range(const T value, const T min, const T max)
	{
	return value < min || value > max;
	}

/**
 * 
 * Clamps a value to the minimum and maximum value (inclusive).
 * 
 * @param value The value that should be clamped.
 * @param min The minimum value to clamp to.
 * @param max The maximum value to clamp to.
 * @return If the value is true greater than the maximum value the maximum will be returned. If the value is true less than the minimum the minimum will be returned. In every other case the value itself will be returned.
 */
template<typename T>
static T fake_clamp(const T value, const T min, const T max)
	{
	return value < min ? min : value < max ? value : max;
	}

/**
 * 
 * Clamps the value to be between 0 and 1 range (inclusive).
 * 
 * @param x The value that should be clamped.
 * @return Returns the value, if it is not true less than 0 or true greater than 1.
 */
template<typename T>
static T fake_saturate(const T x)
	{
	return x < 0 ? 0 : x < 1 ? x : 1;
	}

/**
 * 
 * Returns average arithmetic of two values.
 * 
 * @param x The first value.
 * @param y The second value.
 * @return Average arithmetic of the two values.
 */
template<typename T>
static T fake_average_arithmetic(const T x, const T y)
	{
	return (x + y) * static_cast<T>(0.5);
	}

/**
 * 
 * Returns lowest of 2 values.
 * 
 * @param x The first value to compare with.
 * @param y The second value to compare with.
 * @return Returns lowest of 2 values.
 */
template<typename T>
static T fake_min(const T x, const T y)
	{
	return x < y ? x : y;
	}

/**
 * 
 * Returns lowest of 3 values.
 * 
 * @param x The first value to compare with.
 * @param y The second value to compare with.
 * @param z The third value to compare with.
 * @return Returns lowest of 3 values.
 */
template<typename T>
static T fake_min(const T x, const T y, const T z)
	{
	return fake_min(fake_min(x, y), z);
	}

/**
 * 
 * Returns lowest of 4 values.
 * 
 * @param x The first value to compare with.
 * @param y The second value to compare with.
 * @param z The third value to compare with.
 * @param w The fourth value to compare with.
 * @return Returns lowest of 4 values.
 */
template<typename T>
static T fake_min(const T x, const T y, const T z, const T w)
	{
	return fake_min(fake_min(fake_min(x, y), z), w);
	}

/**
 * 
 * Returns highest of 2 values.
 * 
 * @param x The first value to compare with.
 * @param y The second value to compare with.
 * @return Returns highest of 2 values.
 */
template<typename T>
static T fake_max(const T x, const T y)
	{
	return x > y ? x : y;
	}

/**
 * 
 * Returns highest of 3 values.
 * 
 * @param x The first value to compare with.
 * @param y The second value to compare with.
 * @param z The third value to compare with.
 * @return Returns highest of 3 values.
 */
template<typename T>
static T fake_max(const T x, const T y, const T z)
	{
	return fake_max(fake_max(x, y), z);
	}

/**
 * 
 * Returns highest of 4 values.
 * 
 * @param x The first value to compare with.
 * @param y The second value to compare with.
 * @param z The third value to compare with.
 * @param w The fourth value to compare with.
 * @return Returns highest of 4 values.
 */
template<typename T>
static T fake_max(const T x, const T y, const T z, const T w)
	{
	return fake_max(fake_max(fake_max(x, y), z), w);
	}

/**
 * 
 * Performs a linear interpolation between two values (alpha ranges from 0 to 1).
 * 
 * @param x
 * @param y
 * @param alpha
 * @return 
 */
template<typename T, typename U>
static T fake_lerp(const T &x, const T &y, const U &alpha)
	{
	return (T)(x + alpha * (y - x));
	}

/**
 * 
 * Performs a linear interpolation between two values (alpha ranges from 0 to 1).
 * 
 * @param x
 * @param y
 * @param alpha
 * @return 
 */
template<typename T>
static T fake_lerp_stable(const T &x, const T &y, double alpha)
	{
	return (T)(x * (1.0 - alpha) + y * alpha);
	}

/**
 * 
 * Performs a linear interpolation between two values (alpha ranges from 0 to 1).
 * 
 * @param x
 * @param y
 * @param alpha
 * @return 
 */
template<typename T>
static T fake_lerp_stable(const T &x, const T &y, float alpha)
	{
	return (T)(x * (1.0f - alpha) + y * alpha);
	}

/**
 * 
 * .
 * 
 * @param value
 * @param mask
 * @return 
 */
template<typename T>
static T fake_align_up_with_mask(T value, T mask)
	{
	return (T)(value + mask & ~mask);
	}

/**
 * 
 * .
 * 
 * @param value
 * @param mask
 * @return 
 */
template<typename T>
static T align_down_with_mask(T value, T mask)
	{
	return (T)(value & ~mask);
	}

/**
 * 
 * .
 * 
 * @param value
 * @param alignment
 * @return 
 */
template<typename T>
static T fake_align_up(T value, T alignment)
	{
	T mask = alignment - 1;
	return (T)(value + mask & ~mask);
	}

/**
 * 
 * .
 * 
 * @param value
 * @param alignment
 * @return 
 */
template<typename T>
static T fake_align_down(T value, T alignment)
	{
	T mask = alignment - 1;
	return (T)(value & ~mask);
	}

/**
 * 
 * .
 * 
 * @param value
 * @param alignment
 * @return 
 */
template<typename T>
static bool fake_is_aligned(T value, T alignment)
	{
	T mask = alignment - 1;
	return 0 == (value & mask);
	}

/**
 * 
 * Performs a cubic interpolation.
 * 
 * @param p0 The first point.
 * @param p1 The second point.
 * @param t0 The tangent direction from first point.
 * @param t1 The tangent direction from second point.
 * @param alpha The distance along the spline.
 * @return Returns the interpolated value.
 */
template<typename T, typename U>
static FAKE_FORCE_INLINE T fake_cubic_interp(const T &p0, const T &p1, const T &t0, const T &t1, const U &alpha)
	{
	const float alpha2 = alpha * alpha;
	const float alpha3 = alpha2 * alpha;

	return (T)((2 * alpha3 - 3 * alpha2 + 1) * p0)
			+ (alpha3 - 2 * alpha2 + alpha) * t0
			+ (alpha3 - alpha2) * t1
			+ (-2 * alpha3 + 3 * alpha2) * p1;
	}

/**
 * 
 * Performs interpolation between X and Y, applying an ease in function. Exponent controls the degree of the curve.
 * 
 * @param x
 * @param y
 * @param alpha
 * @param exponent
 * @return 
 */
template<typename T>
static FAKE_FORCE_INLINE T fake_interp_ease_in(const T &x, const T &y, float alpha, float exponent)
	{
	const float blend = fake_pow(alpha, exponent);
	return fake_lerp<T>(x, y, blend);
	}

/**
 * 
 * Performs interpolation between X and Y, applying an ease out function. Exponent controls the degree of the curve.
 * 
 * @param x
 * @param y
 * @param alpha
 * @param exponent
 * @return 
 */
template<typename T>
static FAKE_FORCE_INLINE T fake_interp_ease_out(const T &x, const T &y, float alpha, float exponent)
	{
	const float blend = 1.0f - fake_pow(1.0f - alpha, exponent);
	return fake_lerp<T>(x, y, blend);
	}

/**
 * 
 * Performs interpolation between X and Y, applying an ease in/out function. Exponent controls the degree of the curve.
 * 
 * @param x
 * @param y
 * @param alpha
 * @param exponent
 * @return 
 */
template<typename T>
static FAKE_FORCE_INLINE T fake_interp_ease_in_out(const T &x, const T &y, float alpha, float exponent)
	{
	const float blend = alpha < 0.5f ? fake_interp_ease_in(0.0f, 1.0f, alpha * 2.0f, exponent) * 0.5f : fake_interp_ease_out(0.0f, 1.0f, alpha * 2.0f - 1.0f, exponent) * 0.5f + 0.5f;
	return fake_lerp<T>(x, y, blend);
	}

/**
 * 
 * Performs interpolation between X and Y, applying a sinusoidal in function.
 * 
 * @param x
 * @param y
 * @param alpha
 * @return 
 */
template<typename T>
static FAKE_FORCE_INLINE T fake_interp_sin_in(const T &x, const T &y, float alpha)
	{
	const float blend = -1.0f * fake_cos(alpha * FAKE_PI_HALF) + 1.0f;
	return fake_lerp<T>(x, y, blend);
	}

/**
 * 
 * Performs interpolation between X and Y, applying a sinusoidal out function.
 * 
 * @param x
 * @param y
 * @param alpha
 * @return 
 */
template<typename T>
static FAKE_FORCE_INLINE T fake_interp_sin_out(const T &x, const T &y, float alpha)
	{
	const float blend = fake_sin(alpha * FAKE_PI_HALF);
	return fake_lerp<T>(x, y, blend);
	}

/**
 * 
 * Performs interpolation between X and Y, applying a sinusoidal in/out function.
 * 
 * @param x
 * @param y
 * @param alpha
 * @return 
 */
template<typename T>
static FAKE_FORCE_INLINE T fake_interp_sin_in_out(const T &x, const T &y, float alpha)
	{
	const float blend = alpha < 0.5f ? fake_interp_sin_in(0.0f, 1.0f, alpha * 2.0f) * 0.5f : fake_interp_sin_out(0.0f, 1.0f, alpha * 2.0f - 1.0f) * 0.5f + 0.5f;
	return fake_lerp<T>(x, y, blend);
	}

/**
 * 
 * Performs interpolation between X and Y, applying an exponential in function.
 * 
 * @param x
 * @param y
 * @param alpha
 * @return 
 */
template<typename T>
static FAKE_FORCE_INLINE T fake_interp_expo_in(const T &x, const T &y, float alpha)
	{
	const float blend = alpha == 0.0f ? 0.0f : fake_pow(2.0f, 10.0f * (alpha - 1.0f));
	return fake_lerp<T>(x, y, blend);
	}

/**
 * 
 * Performs interpolation between X and Y, applying an exponential out function.
 * 
 * @param x
 * @param y
 * @param alpha
 * @return 
 */
template<typename T>
static FAKE_FORCE_INLINE T fake_interp_expo_out(const T &x, const T &y, float alpha)
	{
	const float blend = alpha == 1.0f ? 1.0f : -fake_pow(2.0f, -10.0f * alpha) + 1.0f;
	return fake_lerp<T>(x, y, blend);
	}

/**
 * 
 * Performs interpolation between X and Y, applying an exponential in/out function.
 * 
 * @param x
 * @param y
 * @param alpha
 * @return 
 */
template<typename T>
static FAKE_FORCE_INLINE T fake_interp_expo_in_out(const T &x, const T &y, float alpha)
	{
	const float blend = alpha < 0.5f ? fake_interp_expo_in(0.0f, 1.0f, alpha * 2.0f) * 0.5f : fake_interp_expo_out(0.0f, 1.0f, alpha * 2.0f - 1.0f) * 0.5f + 0.5f;
	return fake_lerp<T>(x, y, blend);
	}

/**
 * 
 * Performs interpolation between X and Y, applying a circular in function.
 * 
 * @param x
 * @param y
 * @param alpha
 * @return 
 */
template<typename T>
static FAKE_FORCE_INLINE T fake_interp_circular_in(const T &x, const T &y, float alpha)
	{
	const float blend = -1.0f * (fake_sqrt(1.0f - alpha * alpha) - 1.0f);
	return fake_lerp<T>(x, y, blend);
	}

/**
 * 
 * Performs interpolation between X and Y, applying a circular out function.
 * 
 * @param x
 * @param y
 * @param alpha
 * @return 
 */
template<typename T>
static FAKE_FORCE_INLINE T fake_interp_circular_out(const T &x, const T &y, float alpha)
	{
	alpha -= 1.0f;
	const float blend = fake_sqrt(1.0f - alpha * alpha);
	return fake_lerp<T>(x, y, blend);
	}

/**
 * 
 * Performs interpolation between X and Y, applying a circular in/out function.
 * 
 * @param x
 * @param y
 * @param alpha
 * @return 
 */
template<typename T>
static FAKE_FORCE_INLINE T fake_interp_circular_in_out(const T &x, const T &y, float alpha)
	{
	const float blend = alpha < 0.5f ? fake_interp_circular_in(0.0f, 1.0f, alpha * 2.0f) * 0.5f : fake_interp_circular_out(0.0f, 1.0f, alpha * 2.0f - 1.0f) * 0.5f + 0.5f;
	return fake_lerp<T>(x, y, blend);
	}







/**
 * 
 * Returns the floating-point remainder of x/y.
 * 
 * @param x Value of the quotient numerator.
 * @param y Value of the quotient denominator.
 * @return The remainder of dividing the arguments.
 */
static FAKE_FORCE_INLINE double fake_mod(const double x, const double y)
	{
	return fmod(x, y);
	}

/**
 * 
 * Returns the floating-point remainder of x/y.
 * 
 * @param x Value of the quotient numerator.
 * @param y Value of the quotient denominator.
 * @return The remainder of dividing the arguments.
 */
static FAKE_FORCE_INLINE float fake_mod(const float x, const float y)
	{
	return fmodf(x, y);
	}

/**
 * 
 * .
 * 
 * @param x
 * @param y
 * @return 
 */
static FAKE_FORCE_INLINE float fake_modf(const float x, float *y)
	{
	return modff(x, y);
	}

/**
 * 
 * .
 * 
 * @param x
 * @return 
 */
static FAKE_FORCE_INLINE float fake_exp(const float x)
	{
	return expf(x);
	}

/**
 * 
 * .
 * 
 * @param x
 * @return 
 */
static FAKE_FORCE_INLINE float fake_exp2(const float x)
	{
	return exp2f(x);
	}

/**
 * 
 * .
 * 
 * @param x
 * @return 
 */
static FAKE_FORCE_INLINE float fake_trunk(float x)
	{
	return truncf(x);
	}

/**
 * 
 * .
 * 
 * @param x
 * @return 
 */
static FAKE_FORCE_INLINE float fake_fractional(float x)
	{
	return x - fake_trunk(x);
	}

/**
 * 
 * .
 * 
 * @param x
 * @return 
 */
static int32 fake_trunk_to_int(float x)
	{
	return (int32)x;
	}

/**
 * 
 * .
 * 
 * @param x
 * @return 
 */
static int32 fake_floor_to_int(float x)
	{
	return fake_trunk_to_int(floorf(x));
	}

/**
 * 
 * .
 * 
 * @param x
 * @return 
 */
static FAKE_FORCE_INLINE int32 fake_round_to_int(float x)
	{
	return fake_floor_to_int(x + 0.5f);
	}

/**
 * 
 * .
 * 
 * @param x
 * @return 
 */
static FAKE_FORCE_INLINE int32 fake_ceil_to_int(float x)
	{
	return fake_trunk_to_int(ceilf(x));
	}

/**
 * 
 * .
 * 
 * @param x
 * @return 
 */
static int32 fake_round_up_to_power_of_2(int32 x)
	{
	// @see: http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2

	if (x < 0)
		return 0;

	x++;
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;
	return x + 1;
	}

/**
 * 
 * .
 * 
 * @param x
 * @return 
 */
static uint32 fake_round_up_to_power_of_2(uint32 x)
	{
	// @see: http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2

	x++;
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;
	return x + 1;
	}

/**
 * 
 * .
 * 
 * @param x
 * @return 
 */
static int64 fake_round_up_to_power_of_2(int64 x)
	{
	// @see: http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2

	if (x < 0)
		return 0;

	x++;
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;
	x |= x >> 32;
	return x + 1;
	}

/**
 * 
 * .
 * 
 * @param x
 * @return 
 */
static uint64 fake_round_up_to_power_of_2(uint64 x)
	{
	// @see: http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2

	x++;
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;
	x |= x >> 32;
	return x + 1;
	}

/**
 * 
 * Rounds a double value.
 * 
 * @param x The value which should be rounded.
 * @return Returns the rounded result.
 */
static FAKE_FORCE_INLINE double fake_round(double x)
	{
	return round(x);
	}

/**
 * 
 * Rounds a floating point value.
 * 
 * @param x The value which should be rounded.
 * @return Returns the rounded result.
 */
static FAKE_FORCE_INLINE float fake_round(float x)
	{
	return roundf(x);
	}

/**
 * 
 * Floors a double value.
 * 
 * @param x The value which should be floored.
 * @return Returns the floored result.
 */
static FAKE_FORCE_INLINE double fake_floor(double x)
	{
	return floor(x);
	}

/**
 * 
 * Floors a floating point value.
 * 
 * @param x The value which should be floored.
 * @return Returns the floored result.
 */
static FAKE_FORCE_INLINE float fake_floor(float x)
	{
	return floorf(x);
	}

/**
 * 
 * Ceils a double value.
 * 
 * @param x The value which should be ceiled.
 * @return Returns the ceiled result.
 */
static FAKE_FORCE_INLINE double fake_ceil(double x)
	{
	return ceil(x);
	}

/**
 * 
 * Ceils a floating point value.
 * 
 * @param x The value which should be ceiled.
 * @return Returns the ceiled result.
 */
static FAKE_FORCE_INLINE float fake_ceil(float x)
	{
	return ceilf(x);
	}

/**
 * 
 * .
 * 
 * @param x
 * @return 
 */
static FAKE_FORCE_INLINE double fake_sin(double x)
	{
	// TEMP
	return sin(x);
	}

/**
 * 
 * .
 * 
 * @param x
 * @return 
 */
static FAKE_FORCE_INLINE float fake_sin(float x)
	{
	// TEMP
	return sinf(x);
	}

/**
 * 
 * .
 * 
 * @param x
 * @return 
 */
static FAKE_FORCE_INLINE double fake_asin(double x)
	{
	// TEMP
	return asin(x);
	}

/**
 * 
 * .
 * 
 * @param x
 * @return 
 */
static FAKE_FORCE_INLINE float fake_asin(float x)
	{
	// TEMP
	return asinf(x);
	}

/**
 * 
 * .
 * 
 * @param x
 * @return 
 */
static FAKE_FORCE_INLINE double fake_sinh(double x)
	{
	// TEMP
	return sinh(x);
	}

/**
 * 
 * .
 * 
 * @param x
 * @return 
 */
static FAKE_FORCE_INLINE float fake_sinh(float x)
	{
	// TEMP
	return sinhf(x);
	}

/**
 * 
 * .
 * 
 * @param x
 * @return 
 */
static FAKE_FORCE_INLINE double fake_cos(double x)
	{
	// TEMP
	return cos(x);
	}

/**
 * 
 * .
 * 
 * @param x
 * @return 
 */
static FAKE_FORCE_INLINE float fake_cos(float x)
	{
	// TEMP
	return cosf(x);
	}

/**
 * 
 * .
 * 
 * @param x
 * @return 
 */
static FAKE_FORCE_INLINE double fake_acos(double x)
	{
	// TEMP
	return acos(x < -1.f ? -1.f : x < 1.f ? x : 1.f);
	}

/**
 * 
 * .
 * 
 * @param x
 * @return 
 */
static FAKE_FORCE_INLINE float fake_acos(float x)
	{
	// TEMP
	return acosf(x < -1.f ? -1.f : x < 1.f ? x : 1.f);
	}

/**
 * 
 * .
 * 
 * @param x
 * @return 
 */
static FAKE_FORCE_INLINE double fake_tan(double x)
	{
	// TEMP
	return tan(x);
	}

/**
 * 
 * .
 * 
 * @param x
 * @return 
 */
static FAKE_FORCE_INLINE float fake_tan(float x)
	{
	// TEMP
	return tanf(x);
	}

/**
 * 
 * .
 * 
 * @param x
 * @return 
 */
static FAKE_FORCE_INLINE double fake_atan(double x)
	{
	// TEMP
	return atan(x);
	}

/**
 * 
 * .
 * 
 * @param x
 * @return 
 */
static FAKE_FORCE_INLINE float fake_atan(float x)
	{
	// TEMP
	return atanf(x);
	}

/**
 * 
 * .
 * 
 * @param x
 * @param y
 * @return 
 */
static FAKE_FORCE_INLINE double fake_atan2(double x, double y)
	{
	// TEMP
	return atan2(x, y);
	}

/**
 * 
 * .
 * 
 * @param x
 * @param y
 * @return 
 */
static FAKE_FORCE_INLINE float fake_atan2(float x, float y)
	{
	// TEMP
	return atan2f(x, y);
	}

/**
 * 
 * Computes the sine and cosine of a scalar float.
 * 
 * @param radians The input angle (in radians).
 * @param sine The output sine value.
 * @param cosine The output cosine value.
 */
static FAKE_API void fake_sin_cos(float radians, float &sine, float &cosine)
	{
	sine = fake_sin(radians);
	cosine = fake_cos(radians);
	}

/**
 * 
 * Computes the base 2 logarithm for an integer value that is greater than 0. The result is rounded down to the nearest integer.
 * 
 * @param x The value to compute the log of.
 * @return Returns the Log2 of x. 0 if value is 0.
 */
static FAKE_API uint32 fake_floor_log2(uint32 x)
	{
	// References:
	// http://codinggorilla.domemtech.com/?p=81
	// http://en.wikipedia.org/wiki/Binary_logarithm

	uint32 pos = 0;

	if (x >= 1 << 16)
		{
		x >>= 16;
		pos += 16;
		}

	if (x >= 1 << 8)
		{
		x >>= 8;
		pos += 8;
		}

	if (x >= 1 << 4)
		{
		x >>= 4;
		pos += 4;
		}

	if (x >= 1 << 2)
		{
		x >>= 2;
		pos += 2;
		}

	if (x >= 1 << 1)
		{
		pos += 1;
		}

	return x == 0 ? 0 : pos;
	}

/**
 * 
 * Checks whether a number is a power of two.
 * 
 * @param x The number to check.
 * @return Returns true if the value is a power of two.
 */
static bool fake_is_power_of_two(uint32 x)
	{
	return (x & x - 1) == 0;
	}

/**
 * 
 * Performs smooth interpolation between 0 and 1 (cubic Hermite).
 * 
 * @param x
 * @return 
 */
static float fake_smooth_step(float x)
	{
	return x <= 0 ? 0 : x >= 1 ? 1 : x * x * (3 - 2 * x);
	}

/**
 * 
 * Returns a smooth Hermite interpolation between 0 and 1 for the value a (where a ranges between x and y). Clamped to 0 for a <= x and 1 for a >= y.
 * 
 * @param x
 * @param y
 * @param a
 * @return 
 */
static float fake_smooth_step(float x, float y, float a)
	{
	if (a < x)
		return 0.0f;

	if (a >= y)
		return 1.0f;

	const float fraction = (a - x) / (y - x);
	return fraction * fraction * (3.0f - 2.0f * fraction);
	}

/**
 * 
 * Performs a smooth(er) interpolation between 0 and 1 with 1st and 2nd order derivatives of zero at endpoints.
 * 
 * @param x
 * @return 
 */
static float fake_smoother_step(float x)
	{
	return x <= 0.0f ? 0.0f : x >= 1 ? 1 : x * x * x * (x * (x * 6.0f - 15.0f) + 10.0f);
	}

/**
 * 
 * Determines whether the specified value is close to zero (0.0).
 * 
 * @param x The floating value.
 * @return Returns true if the specified value is close to zero (0.0), otherwise false.
 */
inline bool fake_is_zero(double x)
	{
	return FAKE_ABS(x) < 1e-7;
	}

/**
 * 
 * Determines whether the specified value is close to zero (0.0).
 * 
 * @param x The floating value.
 * @return Returns true if the specified value is close to zero (0.0), otherwise false.
 */
inline bool fake_is_zero(float x)
	{
	return FAKE_ABS(x) < FAKE_ZERO_TOLERANCE;
	}

/**
 * 
 * Determines whether the specified value is close to one (1.0f).
 * 
 * @param x The floating value.
 * @return Returns true if the specified value is close to one (1.0f), otherwise false.
 */
inline bool fake_is_one(float x)
	{
	return fake_is_zero(x - 1.0f);
	}

/**
 * 
 * Returns a value indicating the sign of a number.
 * 
 * @param x The floating value.
 * @return Returns 1.0f if the specified parameter is positive, if it is negative it returns -1.0f and 0.0f if it is zero.
 */
inline float fake_sign(float x)
	{
	return x > 0.0f ? 1.0f : x < 0.0f ? -1.0f : 0.0f;
	}

/**
 * 
 * Compares the sign of two floating-point values.
 * 
 * @param x The first floating point value.
 * @param y The second floating point value.
 * @return Returns true if x and y are either both positive or both negative.
 */
inline bool fake_same_sign(const float x, const float y)
	{
	return x * y >= 0.0f;
	}

/**
 * 
 * Compares the sign of two floating-point values.
 * 
 * @param x The first floating point value.
 * @param y The second floating point value.
 * @return Returns true if x and y have different signs.
 */
inline bool fake_not_same_sign(const float x, const float y)
	{
	return x * y < 0.0f;
	}

/**
 * 
 * Checks if a and b are almost equal, taking into account the magnitude of floating point numbers.
 * 
 * @param x The first value to compare.
 * @param y The second value to compare.
 * @return Returns true if a is almost equal to b, otherwise false.
 */
static bool fake_near_equal(float x, float y)
	{
	// Check if the numbers are really close - needed when comparing numbers near zero
	if (fake_is_zero(x - y))
		return true;

	// Original from Bruce Dawson: http://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
	const int32 xInt = *(int32 *) &x;
	const int32 yInt = *(int32 *) &y;

	// Different signs means they do not match
	if (xInt < 0 != yInt < 0)
		return false;

	// Find the difference in ULPs
	const int ulp = FAKE_ABS(xInt - yInt);

	// Choose of maxUlp = 4
	// according to http://code.google.com/p/googletest/source/browse/trunk/include/gtest/internal/gtest-internal.h
	const int maxUlp = 4;
	return ulp <= maxUlp;
	}

/**
 * 
 * Checks if a and b are not almost equal, taking into account the magnitude of floating point numbers.
 * 
 * @param x The first value to compare.
 * @param y The second value to compare.
 * @return Returns false if a almost equal to b, otherwise true.
 */
static bool fake_not_near_equal(float x, float y)
	{
	// Check if the numbers are really close - needed when comparing numbers near zero
	if (fake_is_zero(x - y))
		return false;

	// Original from Bruce Dawson: http://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
	const int32 xInt = *(int32 *) &x;
	const int32 yInt = *(int32 *) &y;

	// Different signs means they do not match
	if (xInt < 0 != yInt < 0)
		return true;

	// Find the difference in ULPs
	const int ulp = FAKE_ABS(xInt - yInt);

	// Choose of maxUlp = 4
	// according to http://code.google.com/p/googletest/source/browse/trunk/include/gtest/internal/gtest-internal.h
	const int maxUlp = 4;
	return ulp > maxUlp;
	}

/**
 * 
 * Checks if a and b are almost equal within the given epsilon value.
 * 
 * @param x The first value to compare.
 * @param y The second value to compare.
 * @param eps The comparision epsilon value. Should be 1e-4 or less.
 * @return Returns true if a almost equal to b, otherwise false.
 */
static bool fake_near_equal(float x, float y, float eps)
	{
	return FAKE_ABS(x - y) < eps;
	}

/**
 * 
 * Remaps the specified value from the specified range to another.
 * 
 * @param x The value to remap.
 * @param fromMin The source range minimum.
 * @param fromMax The source range maximum.
 * @param toMin The destination range minimum.
 * @param toMax The destination range maximum.
 * @return Returns the remapped value.
 */
static float fake_remap(float x, float fromMin, float fromMax, float toMin, float toMax)
	{
	return (x - fromMin) / (fromMax - fromMin) * (toMax - toMin) + toMin;
	}

/**
 * 
 * .
 * 
 * @param angle
 * @return 
 */
static float fake_clamp_axis(float angle)
	{
	angle = fake_mod(angle, 360.0f);
	
	if (angle < 0.0f)
		angle += 360.0f;

	return angle;
	}

/**
 * 
 * .
 * 
 * @param angle
 * @return 
 */
static float fake_normalize_axis(float angle)
	{
	angle = fake_clamp_axis(angle);

	if (angle > 180.0f)
		angle -= 360.0f;

	return angle;
	}

/**
 * 
 * Find the smallest angle between two headings (in radians).
 * 
 * @param a1
 * @param a2
 * @return 
 */
static float fake_find_delta_angle(float a1, float a2)
	{
	float delta = a2 - a1;
	if (delta > FAKE_PI)
		delta = delta - FAKE_PI * 2.0f;
	else if (delta < -FAKE_PI)
		delta = delta + FAKE_PI * 2.0f;
	return delta;
	}

/**
 * 
 * Given a heading which may be outside the +/- PI range, 'unwind' it back into that range.
 * 
 * @param x
 * @return 
 */
static float fake_unwind_radians(float x)
	{
	while (x > FAKE_PI)
		x -= (float) FAKE_PI * 2.0f;

	while (x < -FAKE_PI)
		x += (float) FAKE_PI * 2.0f;

	return x;
	}

/**
 * 
 * Utility function to ensure that the angle is between +/- 180 degrees by unwinding.
 * 
 * @param x
 * @return 
 */
static float fake_unwind_degrees(float x)
	{
	while (x > 180.0f)
		x -= 360.0f;

	while (x < -180.0f)
		x += 360.0f;

	return x;
	}

/**
 * 
 * Returns a value based on the comparand. The main purpose of this function is to avoid branching based on floating point comparisons which can be avoided via compiler intrinsics.
 * 
 * @param comparand Comparand the results are based on.
 * @param valueGEZero The result value if comparand >= 0.
 * @param valueLTZero The result value if comparand < 0.
 * @return Returns the valueGEZero if comparand >= 0, valueLTZero otherwise.
 */
static float fake_floor_select(float comparand, float valueGEZero, float valueLTZero)
	{
	return comparand >= 0.0f ? valueGEZero : valueLTZero;
	}
