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
/// \return true if \a A is equals \a B, else false
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

inline float toRadians (float angleDegrees) noexcept {
    return ( PI / 180 ) * angleDegrees;
}

//
inline float sign (float var) noexcept {
    return var > 0.0f ? 1.0f : -1.0f;
} 

//
inline float abs (float var) noexcept {
    // return fabsf(var);
    return var > 0.0f ? var : -var; 
}

//
inline float min (float a, float b) noexcept {
    return a > b ? b : a;
}

//
inline float max (float a, float b) noexcept {
    return a > b ? a : b;
}

//
inline float clamp (float var, float _UpperBound, float _LowerBound) noexcept {
    return _MATH max( _LowerBound, _MATH min(var, _UpperBound) );
}

//
inline float random(float _LowerBound = -1.0f, float _UpperBound = 1.0f) noexcept {
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
