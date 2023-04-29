// Math support structs and functions


#ifndef MATHUTILS_H
#define MATHUTILS_H

#include <math.h>
#include <float.h>
// #include <assert.h>
// #include <stdlib.h> 

#define _MATH_BEGIN namespace _math {
#define _MATH_END   }
#define _MATH       ::_math::



_MATH_BEGIN // BEGIN namespace math

constexpr const float PI = 3.14159265358979323846264f;

struct gvector;
struct sq_matrix;

// https://stackoverflow.com/questions/17333/what-is-the-most-effective-way-for-float-and-double-comparison
bool AlmostEqual2sComplement(float A, float B, int maxUlps)    
{    
    // Make sure maxUlps is non-negative and small enough that the    
    // default NAN won't compare as equal to anything.    
    assert(maxUlps > 0 && maxUlps < 4 * 1024 * 1024);    
    int aInt = *(int*)&A;    
    // Make aInt lexicographically ordered as a twos-complement int    
    if (aInt < 0)    
        aInt = 0x80000000 - aInt;    
    // Make bInt lexicographically ordered as a twos-complement int    
    int bInt = *(int*)&B;    
    if (bInt < 0)    
        bInt = 0x80000000 - bInt;    
    int intDiff = abs(aInt - bInt);    
    if (intDiff <= maxUlps)    
        return true;    
    return false;    
}

// geometric vector over a field of real number 
struct gvector {

    // constructor
    gvector (float x = 0, float y = 0) noexcept : Xcoord(x), Ycoord(y) {}

    // copy constructor
    gvector (const gvector& _Right) noexcept = default;

    // move constructor
    gvector (gvector&& _Right) noexcept : Xcoord(_Right.Xcoord), Ycoord(_Right.Ycoord) {
        // ~_Right; // TODO: it's really bad to call destructor explicitly
        _Right.Xcoord = 0;
        _Right.Ycoord = 0;
    }

    // copy assigment
    gvector& operator= (const gvector& _Right) noexcept = default;

    // move assigment
    gvector& operator= (gvector&& _Right) noexcept {
        if (this != &_Right) {
            Xcoord = _Right.Xcoord;
            Ycoord = _Right.Ycoord;

            _Right.Xcoord = 0;
            _Right.Ycoord = 0;
        }

        return *this;
    }

    // destructor 
    ~gvector() noexcept = default;



// arithmetics

    // set gvector values
    void set (float x, float y) noexcept {
        Xcoord = x;
        Ycoord = y;
    }

    // get an opposit gvector
    // TODO: is it possible to get rid of unnecessary assignment or there work a move assignment?
    gvector operator- () noexcept {
        return gvector(-Xcoord, -Ycoord);
    }
    
    // sum of two gvectors
    gvector& operator+= (const gvector& _Right) noexcept {
        Xcoord += _Right.Xcoord;
        Ycoord += _Right.Ycoord;

        return *this;
    }

    // sum of two gvectors
    gvector operator+ (const gvector& _Right) noexcept {
        gvector _Tmp(*this);
        return (_Tmp += _Right);
    }

    // diff of two gvectors
    gvector& operator-= (const gvector& _Right) noexcept {
        Xcoord -= _Right.Xcoord;
        Ycoord -= _Right.Ycoord;

        return *this;
    }

    gvector operator- (const gvector& _Right) noexcept {
        gvector _Tmp(*this);
        return (_Tmp += _Right);
    }

    // mult gvector and a number from field
    gvector operator*= (float M) noexcept {
        Xcoord *= M;
        Ycoord *= M;

        return *this;
    }

    gvector operator* (float M) noexcept {
        gvector _Tmp(*this);
        return (_Tmp *= M);
    }

    // Euclidean norm of gvector 
    float length() const noexcept {
        return sqrtf(Xcoord * Xcoord + Ycoord * Ycoord);
    }



    float Xcoord;
    float Ycoord;
}; 



// matrix two by two over a field of real number
struct sq_matrix {
    
    explicit sq_matrix() {}

    // constructor (the matrix that defines the rotation on a given angle)
    explicit sq_matrix (float angle) noexcept {
        float cos_rot = cosf(angle);
        float sin_rot = sinf(angle);

        gvec1.Xcoord = cos_rot; gvec1.Ycoord = -sin_rot;
        gvec2.Xcoord = sin_rot; gvec2.Ycoord = cos_rot;
    }

    // copy constructor 
    sq_matrix (const sq_matrix&) noexcept = default;

    // move constructor 
    sq_matrix (sq_matrix&&) noexcept = default;

    // construct sq_matrix with two givven gvectors
    sq_matrix (const gvector& _Gvec1, const gvector& _Gvec2) noexcept : gvec1(_Gvec1), gvec2(_Gvec2) {}

    // copy assigment 
    sq_matrix& operator= (const sq_matrix&) noexcept = default;

    // move assigment 
    sq_matrix& operator= (sq_matrix&&) noexcept = default;

    ~sq_matrix() noexcept = default;



// arithmetics

    // transpose matrix  
    sq_matrix transpose() const {
        return sq_matrix (gvector(gvec1.Xcoord, gvec2.Xcoord), gvector(gvec1.Ycoord, gvec2.Ycoord));
    }
    
    // get a determinant of sq_matrix
    float det() const {
        return gvec1.Xcoord * gvec2.Ycoord - gvec1.Ycoord * gvec2.Xcoord;
    }

    // TODO: it doesn't work properly
    bool is_invertible() const {
        return AlmostEqual2sComplement(gvec1.Xcoord * gvec2.Ycoord, gvec1.Ycoord * gvec2.Xcoord, 0);
    } 
    
    // TODO: need implement AXC::VERIFY
    sq_matrix invert() const {
        AXC::VERIFY(this->is_invertible());
        
        float det = this->det();
        sq_matrix invert_matrix;
        // assert( det != 0.0f );
        float det_mult = 1.0f / det;

        invert_matrix.gvec1.Xcoord =  det_mult * gvec2.Ycoord;
        invert_matrix.gvec1.Ycoord = -det_mult * gvec1.Ycoord;

        invert_matrix.gvec2.Xcoord = -det_mult * gvec2.Xcoord;
        invert_matrix.gvec2.Ycoord =  det_mult * gvec1.Xcoord;

        return invert_matrix;
    }



    gvector gvec1;
    gvector gvec2;
};



// dot product of geometric vectors
inline float dot (const gvector& a, const gvector& b) noexcept {
    return a.Xcoord * b.Xcoord + a.Ycoord * b.Ycoord;
}

// cross product of geometric vectors
// return determinant of sq_matrix based on a and b that equal norm of vector [a,b] in 3D
inline float cross (const gvector& a, const gvector& b) noexcept {
    return a.Xcoord * b.Ycoord - a.Ycoord * b.Xcoord;
}

// cross product of geometric vector and number
inline gvector get_normal (const gvector& _gvector) noexcept {
    return gvector(_gvector.Ycoord, -_gvector.Xcoord);
}

// multiplication of gvector-row and sq_matrix
// return a vector-row 1x2
inline gvector operator* (const gvector& gvec, const sq_matrix& mat) noexcept {
    return gvector(
        gvec.Xcoord * mat.gvec1.Xcoord + gvec.Ycoord * mat.gvec1.Ycoord,
        gvec.Xcoord * mat.gvec2.Xcoord + gvec.Ycoord * mat.gvec2.Ycoord 
    );
}

// multiplication of matrix and gvector-column
// return a vector-column 2x1
inline gvector operator* (const sq_matrix& mat, const gvector& gvec) noexcept {
    return gvector(
        mat.gvec1.Xcoord * gvec.Xcoord + mat.gvec2.Xcoord * gvec.Ycoord,
        mat.gvec1.Ycoord * gvec.Xcoord + mat.gvec2.Ycoord * gvec.Ycoord
    );
}

//
// inline gvector operator+ (const gvector& a, const gvector& b) noexcept {
//     return gvector(
//         a.Xcoord + b.Xcoord,
//         a.Ycoord + b.Ycoord
//     );
// }

//
inline gvector operator- (const gvector& a, const gvector& b) noexcept {
    return gvector(
        a.Xcoord - b.Xcoord,
        a.Ycoord - b.Ycoord
    );
} 

// 
inline sq_matrix operator+ (const sq_matrix& a, const sq_matrix& b) noexcept {
    return sq_matrix(
        a.gvec1 + b.gvec1,
        a.gvec2 + b.gvec2
    );
}

//
inline sq_matrix operator* (const sq_matrix& a, const sq_matrix& b) noexcept {
    return sq_matrix(
        a * b.gvec1,
        a * b.gvec2
    );
}

//
inline float sign (float var) noexcept {
    return var > 0.0f ? 1.0f : -1.0f;
} 

inline float abs (float var) noexcept {
    // return fabsf(var);
    return var > 0.0f ? var : -var; 
}

inline gvector abs (const gvector& gvec) noexcept {
    return gvector(
        _MATH abs(gvec.Xcoord),
        _MATH abs(gvec.Ycoord)
    ); 
}

inline sq_matrix abs (const sq_matrix& mat) noexcept {
    return sq_matrix(
        _MATH abs(mat.gvec1),
        _MATH abs(mat.gvec2)
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

#endif
