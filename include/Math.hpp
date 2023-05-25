// Math support structs and functions


#ifndef MATHUTILS_H
#define MATHUTILS_H

#include <math.h>
#include <float.h>
#include "Utils.hpp"
// #include <assert.h>
// #include <stdlib.h> 

#define _MATH_BEGIN namespace _math {
#define _MATH_END   }
#define _MATH       ::_math::



_MATH_BEGIN // BEGIN namespace math

constexpr const float   PI       = 3.14159265358979323846264f;
static    const int32_t kMaxUlps = 5;
constexpr const bool    _INLINE_FLAG = 1;

struct Gvector;
struct SQmatrix;


// https://stackoverflow.com/questions/17333/what-is-the-most-effective-way-for-float-and-double-comparison
inline bool _AlmostEqual(float A, float B, int maxUlps = kMaxUlps) //  Ulps - Units in the Last Place
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

// geometric vector over a field of real number 
struct Gvector {

    // constructor
    explicit Gvector (float x = 0, float y = 0) noexcept : Xcoord(x), Ycoord(y) {}

    // copy constructor
    Gvector (const Gvector& _Right) noexcept = default;

    // move constructor
    Gvector (Gvector&& _Right) noexcept : Xcoord(_Right.Xcoord), Ycoord(_Right.Ycoord) {
        // ~_Right; // TODO: it's really bad to call destructor explicitly
        _Right.Xcoord = 0;
        _Right.Ycoord = 0;
    }

    // copy assigment
    Gvector& operator= (const Gvector& _Right) noexcept = default;

    // move assigment
    Gvector& operator= (Gvector&& _Right) noexcept {
        if (this != &_Right) {
            Xcoord = _Right.Xcoord;
            Ycoord = _Right.Ycoord;

            _Right.Xcoord = 0;
            _Right.Ycoord = 0;
        }

        return *this;
    }

    // destructor 
    ~Gvector() noexcept = default;



// arithmetics

    // set Gvector values
    void set (float x, float y) noexcept {
        Xcoord = x;
        Ycoord = y;
    }

    // get an opposit Gvector
    // TODO: is it possible to get rid of unnecessary assignment or there work a move assignment?
    Gvector operator- () const noexcept {
        return Gvector(-Xcoord, -Ycoord);
    }
    
    // sum of two gvectors
    Gvector& operator+= (const Gvector& _Right) noexcept {
        Xcoord += _Right.Xcoord;
        Ycoord += _Right.Ycoord;
        return *this;
    }

    // diff of two gvectors
    Gvector& operator-= (const Gvector& _Right) noexcept {
        Xcoord -= _Right.Xcoord;
        Ycoord -= _Right.Ycoord;
        return *this;
    }

    // mult Gvector and a number from field
    Gvector operator*= (float _Const) noexcept {
        Xcoord *= _Const;
        Ycoord *= _Const;
        return *this;
    }


#if !_INLINE_FLAG

    // sum of two gvectors
    Gvector operator+ (const Gvector& _Right) const noexcept {
        Gvector _Tmp(*this);
        return (_Tmp += _Right);
    }

    Gvector operator- (const Gvector& _Right) const noexcept {
        Gvector _Tmp(*this);
        return (_Tmp += _Right);
    }
    
    Gvector operator* (float _Const) const noexcept {
        Gvector _Tmp(*this);
        return (_Tmp *= _Const);
    }

#endif // !_INLINE_FLAG 

    // Euclidean norm of Gvector
    // WARNING: sqrtf() is expensive, better to use square norm
    float norm() const noexcept {
        return sqrtf(Xcoord * Xcoord + Ycoord * Ycoord);
    }



    float Xcoord;
    float Ycoord;
}; 



// matrix two by two over a field of real number
struct SQmatrix {
    
    explicit SQmatrix() {}

    // constructor (the matrix that defines the rotation on a given angle)
    // WARNING: angle should be measured in degres, not in radians
    explicit SQmatrix (float angle) noexcept {
        float cos_rot = cosf(angle);
        float sin_rot = sinf(angle);

        col1.Xcoord = cos_rot; col1.Ycoord = -sin_rot;
        col2.Xcoord = sin_rot; col2.Ycoord = cos_rot;
    }

    // copy constructor 
    SQmatrix (const SQmatrix&) noexcept = default;

    // move constructor 
    SQmatrix (SQmatrix&&) noexcept = default;

    // construct SQmatrix with two givven gvectors
    SQmatrix (const Gvector& _Gvec1, const Gvector& _Gvec2) noexcept : col1(_Gvec1), col2(_Gvec2) {}

    // copy assigment 
    SQmatrix& operator= (const SQmatrix&) noexcept = default;

    // move assigment 
    SQmatrix& operator= (SQmatrix&&) noexcept = default;

    ~SQmatrix() noexcept = default;



// transformations

    // transpose matrix  
    SQmatrix transpose() const noexcept {
        return SQmatrix (Gvector(col1.Xcoord, col2.Xcoord), Gvector(col1.Ycoord, col2.Ycoord));
    }
    
    // get a determinant of SQmatrix
    float det() const noexcept {
        return col1.Xcoord * col2.Ycoord - col1.Ycoord * col2.Xcoord;
    }

    bool is_invertible() const noexcept {
        return !( _AlmostEqual(this->det(), 0) );
    } 
    
    SQmatrix invert() const { 
        _AXC _VERIFY(this->is_invertible(), "invert: det of matrix is 0!" );
        
        float det = this->det();
        SQmatrix invert_matrix;
        float det_mult = 1.0f / det;

        invert_matrix.col1.Xcoord =  det_mult * col2.Ycoord;
        invert_matrix.col1.Ycoord = -det_mult * col1.Ycoord;

        invert_matrix.col2.Xcoord = -det_mult * col2.Xcoord;
        invert_matrix.col2.Ycoord =  det_mult * col1.Xcoord;

        return invert_matrix;
    }


#if !_INLINE_FLAG 

// arithmetics

    SQmatrix operator+ (const SQmatrix& _Right) const noexcept {
        return SQmatrix(
            this->col1 + _Right.col1,
            this->col2 + _Right.col2
        );
    }

    SQmatrix operator- (const SQmatrix& _Right) const noexcept {
        return SQmatrix(
            this->col1 - _Right.col1,
            this->col2 - _Right.col2
        );
    }

    Gvector operator* (const Gvector& gvec) const noexcept {
        return Gvector(
            this->col1.Xcoord * gvec.Xcoord + this->col2.Xcoord * gvec.Ycoord,
            this->col1.Ycoord * gvec.Xcoord + this->col2.Ycoord * gvec.Ycoord
        );
    }

    SQmatrix operator* (const SQmatrix& _Right) const noexcept {
        return SQmatrix(
            *this * _Right.col1,
            *this * _Right.col2
        );
    }

#endif // !_INLINE_FLAG
    
    
    Gvector col1;
    Gvector col2;
};



// dot product of geometric vectors
inline float dot (const Gvector& a, const Gvector& b) noexcept {
    return a.Xcoord * b.Xcoord + a.Ycoord * b.Ycoord;
}

// cross product of geometric vectors
// return determinant of SQmatrix based on a and b that equal norm of vector [a,b] in 3D
inline float cross (const Gvector& a, const Gvector& b) noexcept {
    return a.Xcoord * b.Ycoord - a.Ycoord * b.Xcoord;
}

// cross product of geometric vector and number
inline Gvector get_normal (const Gvector& _gvec) noexcept {
    return Gvector(_gvec.Ycoord, -_gvec.Xcoord);
}

// WARNING: expensive
inline Gvector normalize (const Gvector& _gvec) noexcept {
    float length = _gvec.norm();
    return Gvector(_gvec.Xcoord / length, _gvec.Ycoord / length);
}

// WARNING: expensive
inline float get_angle (const Gvector& a, const Gvector& b) noexcept {
    return dot(normalize(a), normalize(b));
}

#if _INLINE_FLAG
// multiplication of Gvector-row and SQmatrix
// return a vector-row 1x2
inline Gvector operator* (const Gvector& gvec, const SQmatrix& mat) const noexcept {
    return Gvector(
        gvec.Xcoord * mat.col1.Xcoord + gvec.Ycoord * mat.col1.Ycoord,
        gvec.Xcoord * mat.col2.Xcoord + gvec.Ycoord * mat.col2.Ycoord 
    );
}

// multiplication of matrix and Gvector-column
// return a vector-column 2x1
inline Gvector operator* (const SQmatrix& mat, const Gvector& gvec) const noexcept {
    return Gvector(
        mat.col1.Xcoord * gvec.Xcoord + mat.col2.Xcoord * gvec.Ycoord,
        mat.col1.Ycoord * gvec.Xcoord + mat.col2.Ycoord * gvec.Ycoord
    );
}

//
inline Gvector operator+ (const Gvector& a, const Gvector& b) const noexcept {
    return Gvector(
        a.Xcoord + b.Xcoord,
        a.Ycoord + b.Ycoord
    );
}

//
inline Gvector operator- (const Gvector& a, const Gvector& b) const noexcept {
    return Gvector(
        a.Xcoord - b.Xcoord,
        a.Ycoord - b.Ycoord
    );
} 

inline Gvector operator* (float _Const, const Gvector& gvec) const noexcept {
    return Gvector(
        gvec.Xcoord * _Const,
        gvec.Ycoord * _Const
    );
}

// 
inline SQmatrix operator+ (const SQmatrix& a, const SQmatrix& b) const noexcept {
    return SQmatrix(
        a.col1 + b.col1,
        a.col2 + b.col2
    );
}

inline SQmatrix operator- (const SQmatrix& a, const SQmatrix& b) const noexcept {
    return SQmatrix(
        a.col1 - b.col1,
        a.col2 - b.col2
    );
}

//
inline SQmatrix operator* (float _Const, const SQmatrix& sqmarix) const noexcept {
    return SQmatrix(
        col1 * _Const,
        col2 * _Const
    );
}

//
inline SQmatrix operator* (const SQmatrix& a, const SQmatrix& b) const noexcept {
    return SQmatrix(
        a * b.col1,
        a * b.col2
    );
}

#endif // _INLINE_FLAG


//
inline float sign (float var) noexcept {
    return var > 0.0f ? 1.0f : -1.0f;
} 

inline float abs (float var) noexcept {
    // return fabsf(var);
    return var > 0.0f ? var : -var; 
}

inline Gvector abs (const Gvector& gvec) noexcept {
    return Gvector(
        _MATH abs(gvec.Xcoord),
        _MATH abs(gvec.Ycoord)
    ); 
}

inline SQmatrix abs (const SQmatrix& sqmatrix) noexcept {
    return SQmatrix(
        _MATH abs(sqmatrix.col1),
        _MATH abs(sqmatrix.col2)
    );
}

inline float min (float a, float b) noexcept {
    return a > b ? b : a;
}

inline float max (float a, float b) noexcept {
    return a > b ? a : b;
}

inline float clamp (float var, float _UpperBound, float _LowerBound) noexcept {
    return _MATH max( _LowerBound, _MATH min(var, _UpperBound) );
}

inline float random(float _LowerBound = -1.0f, float _UpperBound = 1.0f) noexcept {
    float result = (float) rand();
    result /= RAND_MAX;
    result = (_UpperBound - _LowerBound) * result + _LowerBound;
    return result;
} 

_MATH_END // END namespace math

#endif // MATHUTILS_H
