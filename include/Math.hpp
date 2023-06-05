////////////////////////////////////////////////////////////
/// Utils provide base structures with simple and robust
/// implementation.
/// 
/// Presented structures: 
///     Gvector
///     SQmatrix
///     Point
///     Line
///
////////////////////////////////////////////////////////////


#ifndef MATH_H
#define MATH_H


#include "Utils.hpp"
#include "float.h"
#include "vector"
#include "cmath"

#define _MATH_BEGIN namespace _math {
#define _MATH_END   }
#define _MATH       ::_math::


_MATH_BEGIN // BEGIN namespace _math

constexpr const float   PI       = 3.1415926535f;
static    const int32_t kMaxUlps = 4;


////////////////////////////////////////////////////////////
/// \brief Compare two scalar value by maxUlps
///
/// https://stackoverflow.com/questions/17333/what-is-the
/// -most-effective-way-for-float-and-double-comparison
///
/// \param A first operand (a scalar value)
/// \param b second operand (a scalar value)
/// 
/// \return True if \a A is equals \a B, else false
///
////////////////////////////////////////////////////////////
inline bool AlmostEqual (float A, float B, int maxUlps = kMaxUlps) //  Ulps - Units in the Last Place
{    
    _AXC _VERIFY(maxUlps > 0 && maxUlps < 4 * 1024 * 1024, "_AlmostEqual: invalid maxUlps");

    int aInt = *(int*)&A;    
    if (aInt < 0) // Make aInt lexicographically ordered as a twos-complement int    
        aInt = 0x80000000 - aInt;    

    int bInt = *(int*)&B;    
    if (bInt < 0) // Make bInt lexicographically ordered as a twos-complement int    
        bInt = 0x80000000 - bInt;    

    int intDiff = abs(aInt - bInt);    
    if (intDiff <= maxUlps)    
        return true;

    return false;    
}

////////////////////////////////////////////////////////////
/// Convertion degrees to radians
/// 
/// \param angleDegrees angle to convert in degrees
/// \return Angle to convert in radians
////////////////////////////////////////////////////////////
inline float toRadians (float angleDegrees) noexcept {
    return ( PI / 180 ) * angleDegrees;
}

////////////////////////////////////////////////////////////
/// Sign of value
/// 
/// \param value
/// \return If value > 0 return 1, else -1
////////////////////////////////////////////////////////////
inline float sign (float value) noexcept {
    return value > 0.0f ? 1.0f : -1.0f;
} 

////////////////////////////////////////////////////////////
/// Abs of value
/// 
/// \param value
/// \return If value > 0 return value, else -value
////////////////////////////////////////////////////////////
inline float abs (float value) noexcept {
    // return fabsf(value);
    return value > 0.0f ? value : -value; 
}

////////////////////////////////////////////////////////////
/// Calculate min of two given values
/// 
/// \param a value 1
/// \param b value 2
/// \return If a > b return b, else a
////////////////////////////////////////////////////////////
inline float min (float a, float b) noexcept {
    return a > b ? b : a;
}

////////////////////////////////////////////////////////////
/// Calculate max of two given values
/// 
/// \param a value 1
/// \param b value 2
/// \return If a > b return a, else b
////////////////////////////////////////////////////////////
inline float max (float a, float b) noexcept {
    return a > b ? a : b;
}

////////////////////////////////////////////////////////////
/// Averages the value
/// 
/// \param value to be averaged
/// \param _UpperBound upper bound
/// \param _LowerBound lower bound
/// \return If value > _UpperBound > _LowerBound return 
///         _UpperBound, If _UpperBound > value > _LowerBound
///         return value, else return _LowerBound
////////////////////////////////////////////////////////////
inline float clamp (float value, float _UpperBound, float _LowerBound) noexcept {
    return _MATH max( _LowerBound, _MATH min(value, _UpperBound) );
}

////////////////////////////////////////////////////////////
/// Randomizer
/// 
/// \param _UpperBound upper bound
/// \param _LowerBound lower bound
/// \return Random value between _LowerBound and _UpperBound
////////////////////////////////////////////////////////////
inline float random (float _LowerBound = -1.0f, float _UpperBound = 1.0f) noexcept {
    float result = (float) rand();
    result /= RAND_MAX;
    result = (_UpperBound - _LowerBound) * result + _LowerBound;
    return result;
} 

_MATH_END // END namespace math


#endif // MATH_H
////////////////////////////////////////////////////////////
/// \defgroup math Mathematical Library
///
/// Math support functions
///
////////////////////////////////////////////////////////////
