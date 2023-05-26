// Math support structs and functions


#ifndef MATH_H
#define MATH_H


#include <math.h>
#include <float.h>
#include <type_traits>
#include <vector>

#include "Utils.hpp"
// #include <assert.h>
// #include <stdlib.h> 


#define _MATH_BEGIN namespace _math {
#define _MATH_END   }
#define _MATH       ::_math::



_MATH_BEGIN // BEGIN namespace math

constexpr const float   PI       = 3.14159265358979323846264f;
static    const int32_t kMaxUlps = 5;



// https://stackoverflow.com/questions/17333/what-is-the-most-effective-way-for-float-and-double-comparison
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



// geometric vector over a field of real number 
struct Gvector {

    // constructor
    Gvector (float x = 0.0f, float y = 0.0f) noexcept : Xcoord(x), Ycoord(y) {}

    // copy constructor
    Gvector (const Gvector& _Other) noexcept = default;

    // move constructor
    Gvector (Gvector&& _Other) noexcept : Xcoord(_Other.Xcoord), Ycoord(_Other.Ycoord) {
        // ~_Right; // TODO: it's really bad to call destructor explicitly
        _Other.Xcoord = 0.0f;
        _Other.Ycoord = 0.0f;
    }

    // copy assigment
    Gvector& operator= (const Gvector& _Rhs) noexcept = default;

    // move assigment
    Gvector& operator= (Gvector&& _Rhs) noexcept {
        if (this != &_Rhs) {
            Xcoord = _Rhs.Xcoord;
            Ycoord = _Rhs.Ycoord;

            _Rhs.Xcoord = 0.0f;
            _Rhs.Ycoord = 0.0f;
        }

        return *this;
    }

    // destructor 
    ~Gvector() noexcept = default;


    // set Gvector values
    void set (float x, float y) noexcept {
        Xcoord = x;
        Ycoord = y;
    }

// -- arithmetics -- 
    
    // get an opposit Gvector
    Gvector operator- () const noexcept {
        return Gvector(-Xcoord, -Ycoord);
    }
    
    // sum of two gvectors
    Gvector& operator+= (const Gvector& _Rhs) noexcept {
        Xcoord += _Rhs.Xcoord;
        Ycoord += _Rhs.Ycoord;
        return *this;
    }

    // diff of two gvectors
    Gvector& operator-= (const Gvector& _Rhs) noexcept {
        Xcoord -= _Rhs.Xcoord;
        Ycoord -= _Rhs.Ycoord;
        return *this;
    }

    // mult Gvector and a number from field
    Gvector& operator*= (float _Const) noexcept {
        Xcoord *= _Const;
        Ycoord *= _Const;
        return *this;
    }

    // Euclidean norm of Gvector
    // WARNING: sqrtf() is expensive, better to use square norm
    float norm() const noexcept {
        return sqrtf(Xcoord * Xcoord + Ycoord * Ycoord);
    }
    
    //
    bool is_null() const noexcept {
        return AlmostEqual(Xcoord, Ycoord);
    }

    float Xcoord;
    float Ycoord;
}; 

//
inline Gvector operator+ (const Gvector& _Rhs, const Gvector& _Lhs) noexcept {
    return Gvector(_Rhs.Xcoord + _Lhs.Xcoord, _Rhs.Ycoord + _Lhs.Ycoord);
}

//
inline Gvector operator- (const Gvector& _Rhs, const Gvector& _Lhs) noexcept {
    return Gvector(_Rhs.Xcoord - _Lhs.Xcoord, _Rhs.Ycoord - _Lhs.Ycoord);
}

// 
inline Gvector operator* (const Gvector& _Rhs, const Gvector& _Lhs) noexcept {
    return Gvector(_Rhs.Xcoord * _Lhs.Xcoord, _Rhs.Ycoord * _Lhs.Ycoord);
}

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
inline Gvector get_normal (const Gvector& gvec) noexcept {
    return Gvector(gvec.Ycoord, -gvec.Xcoord);
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



// matrix two by two over a field of real number
struct SQmatrix {
    
    explicit SQmatrix() {}

    // constructor (the matrix that defines the rotation on a given angle)
    // WARNING: angle should be measured in degres, not in radians
    explicit SQmatrix (float angle) noexcept {
        float cos_rot = cosf(angle);
        float sin_rot = sinf(angle);

        col1.Xcoord = cos_rot;  col2.Xcoord = sin_rot;
        col1.Ycoord = -sin_rot; col2.Ycoord = cos_rot;
    }

    // copy constructor 
    SQmatrix (const SQmatrix&) noexcept = default;

    // move constructor 
    SQmatrix (SQmatrix&&) noexcept = default;

    // construct SQmatrix with two given gvectors
    SQmatrix (const Gvector& _Gvec1, const Gvector& _Gvec2) noexcept : col1(_Gvec1), col2(_Gvec2) {}

    // copy assigment 
    SQmatrix& operator= (const SQmatrix&) noexcept = default;

    // move assigment 
    SQmatrix& operator= (SQmatrix&&) noexcept = default;

    ~SQmatrix() noexcept = default;

// -- arithmetics --
    
    //
    SQmatrix& operator+= (const SQmatrix& _Rhs) noexcept {
        col1 += _Rhs.col1;
        col2 += _Rhs.col2;
        return *this;
    }
    
    // 
    SQmatrix& operator-= (const SQmatrix& _Rhs) noexcept {
        col1 -= _Rhs.col1;
        col2 -= _Rhs.col2;
        return *this;
    }

    //
    SQmatrix& operator*= (float _Const) noexcept {
        col1 *= _Const;
        col2 *= _Const;
        return *this;
    }

// -- get specifications--
 
    // get a determinant of SQmatrix
    float det() const noexcept {
        return col1.Xcoord * col2.Ycoord - col1.Ycoord * col2.Xcoord;
    }
    
    //
    bool is_invertible() const noexcept {
        return !( AlmostEqual(this->det(), 0.0f) );
    } 
    
    
    
    Gvector col1;
    Gvector col2;
};

// multiplication of matrix and Gvector-column
// return a vector-column 2x1
inline Gvector operator* (const SQmatrix& mat, const Gvector& gvec) noexcept {
    return Gvector(
        mat.col1.Xcoord * gvec.Xcoord + mat.col2.Xcoord * gvec.Ycoord,
        mat.col1.Ycoord * gvec.Xcoord + mat.col2.Ycoord * gvec.Ycoord
    );
}

//
inline SQmatrix operator+ (const SQmatrix& _Lhs, const SQmatrix& _Rhs) noexcept {
    return SQmatrix(
        _Rhs.col1 + _Lhs.col1,
        _Rhs.col2 + _Lhs.col2
    );

    // SQmatrix _Tmp(_Lhs);
    // return _Tmp += _Rhs;
}

inline SQmatrix operator- (const SQmatrix& _Lhs, const SQmatrix& _Rhs) noexcept {
    return SQmatrix(
        _Rhs.col1 - _Lhs.col1,
        _Rhs.col2 - _Lhs.col2
    );
}

//
inline SQmatrix operator* (const SQmatrix& sqmatrix, float _Const) noexcept {
    return SQmatrix(
        sqmatrix.col1 * _Const,
        sqmatrix.col2 * _Const
    );
}

//
inline SQmatrix operator* (const SQmatrix& a, const SQmatrix& b) noexcept {
    return SQmatrix(
        a * b.col1,
        a * b.col2
    );
}

//
inline SQmatrix invert (const SQmatrix& sqmatrix) { 
        _AXC _VERIFY(sqmatrix.is_invertible(), "invert: det of matrix is 0!" );
        
        float det = sqmatrix.det();
        SQmatrix invert_matrix;
        float det_mult = 1.0f / det;

        invert_matrix.col1.Xcoord =  det_mult * sqmatrix.col2.Ycoord;
        invert_matrix.col1.Ycoord = -det_mult * sqmatrix.col1.Ycoord;

        invert_matrix.col2.Xcoord = -det_mult * sqmatrix.col2.Xcoord;
        invert_matrix.col2.Ycoord =  det_mult * sqmatrix.col1.Xcoord;

        return invert_matrix;
}

// transpose matrix  
inline SQmatrix transpose (const SQmatrix& sqmatrix) noexcept {
        return SQmatrix (Gvector(sqmatrix.col1.Xcoord, sqmatrix.col2.Xcoord),
                         Gvector(sqmatrix.col1.Ycoord, sqmatrix.col2.Ycoord)
                         );
}



struct Point {
   
    Point (float x = 0.0f, float y = 0.0f) noexcept : Coords(x,y) {}
    
    Point (const Gvector& gvector) noexcept : Coords(gvector) {}

    Point& set (float x, float y) noexcept {
        Coords.Xcoord = x;
        Coords.Ycoord = y;
        return *this;
    }

    //
    Point rotate (const Point& Origin, float Angle) const noexcept {
        SQmatrix RotMatrix(Angle);
        return Point( (RotMatrix * (Coords - Origin.Coords)) + Origin.Coords);
    }

    //
    Point rotate (const Point& Origin, const SQmatrix& RotMatrix) const noexcept {
        return Point( (RotMatrix * (Coords - Origin.Coords)) + Origin.Coords);
    }



    Gvector Coords;
};



struct Line {

    Line (const Point& a, Point& b) noexcept : 
        begin(a),
        end(b),
        direction(end.Coords.Xcoord - begin.Coords.Xcoord, end.Coords.Ycoord - end.Coords.Ycoord)
    {}

    // TODO: check correctness of the DirVector (!= 0) within template
    // mb create a struct null_vector??
    // Line (const Point& a, const Gvector& DirVector) :
    //     begin(a),
    // {}

    // TODO check DirVector != 0
    Line (const Gvector& DirVector) : 
        begin(0,0),
        end(DirVector.Xcoord, DirVector.Xcoord),
        direction(DirVector) 
    {}

    Line rotate (const Point& Origin, float angle) noexcept {
        SQmatrix RotMatrix(angle);
        Point _Begin ( begin.rotate(Origin, RotMatrix) );
        Point _End ( end.rotate(Origin, RotMatrix) );

        return Line (_Begin, _End);
    }

    Point   begin;
    Point   end;
    Gvector direction; 
};



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
inline Gvector abs (const Gvector& gvec) noexcept {
    return Gvector(
        _MATH abs(gvec.Xcoord),
        _MATH abs(gvec.Ycoord)
    ); 
}

//
inline SQmatrix abs (const SQmatrix& sqmatrix) noexcept {
    return SQmatrix(
        _MATH abs(sqmatrix.col1),
        _MATH abs(sqmatrix.col2)
    );
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
