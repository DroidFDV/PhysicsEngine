#ifndef SQMATRIX_H
#define SQMATRIX_H


#include "../Math.hpp"
#include "Gvector.hpp"


_ST_BEGIN

using namespace _math;

////////////////////////////////////////////////////////////
/// \brief Utility struct for manipulating
///        2-dimensional vectors. Type of values is float.
///
////////////////////////////////////////////////////////////
// matrix two by two over a field of real number
struct SQmatrix {

    explicit SQmatrix() {}

    // constructor (the matrix that defines the rotation on a given angle)
    // WARNING: angle should be measured in degres, not in radians
    explicit SQmatrix (float angleDegrees) noexcept {
        float angleRadians = _math::toRadians(angleDegrees);
        float cos_rot = cosf(angleRadians);
        float sin_rot = sinf(angleRadians);

        Col1.Xcoord = cos_rot;  Col2.Xcoord = -sin_rot;
        Col1.Ycoord = sin_rot; Col2.Ycoord = cos_rot;
    }

    // copy constructor 
    SQmatrix (const SQmatrix&) noexcept = default;

    // move constructor 
    SQmatrix (SQmatrix&&) noexcept = default;

    // construct SQmatrix with two given gvectors
    SQmatrix (const Gvector& _Gvec1, const Gvector& _Gvec2) noexcept : Col1(_Gvec1), Col2(_Gvec2) {}

    // copy assigment 
    SQmatrix& operator= (const SQmatrix&) noexcept = default;

    // move assigment 
    SQmatrix& operator= (SQmatrix&&) noexcept = default;

    ~SQmatrix() noexcept = default;

    // -- arithmetics --

    //
    SQmatrix& operator+= (const SQmatrix& _Rhs) noexcept {
        Col1 += _Rhs.Col1;
        Col2 += _Rhs.Col2;
        return *this;
    }

    // 
    SQmatrix& operator-= (const SQmatrix& _Rhs) noexcept {
        Col1 -= _Rhs.Col1;
        Col2 -= _Rhs.Col2;
        return *this;
    }

    //
    SQmatrix& operator*= (float _Scal) noexcept {
        Col1 *= _Scal;
        Col2 *= _Scal;
        return *this;
    }

    // -- get specifications--

    // get a determinant of SQmatrix
    float det() const noexcept {
        return Col1.Xcoord * Col2.Ycoord - Col1.Ycoord * Col2.Xcoord;
    }

    //
    bool is_invertible() const noexcept {
        return !( AlmostEqual(this->det(), 0.0f) );
    } 



    Gvector Col1;
    Gvector Col2;
};

// multiplication of matrix and Gvector-Column
// return a vector-Column 2x1
inline Gvector operator* (const SQmatrix& mat, const Gvector& gvec) noexcept {
    return Gvector(
        mat.Col1.Xcoord * gvec.Xcoord + mat.Col2.Xcoord * gvec.Ycoord,
        mat.Col1.Ycoord * gvec.Xcoord + mat.Col2.Ycoord * gvec.Ycoord
    );
}

//
inline SQmatrix operator+ (const SQmatrix& _Lhs, const SQmatrix& _Rhs) noexcept {
    return SQmatrix(
        _Rhs.Col1 + _Lhs.Col1,
        _Rhs.Col2 + _Lhs.Col2
    );

    // SQmatrix _Tmp(_Lhs);
    // return _Tmp += _Rhs;
}

inline SQmatrix operator- (const SQmatrix& _Lhs, const SQmatrix& _Rhs) noexcept {
    return SQmatrix(
        _Rhs.Col1 - _Lhs.Col1,
        _Rhs.Col2 - _Lhs.Col2
    );
}

//
inline SQmatrix operator* (const SQmatrix& sqmatrix, float _Scal) noexcept {
    return SQmatrix(
        sqmatrix.Col1 * _Scal,
        sqmatrix.Col2 * _Scal
    );
}

//
inline SQmatrix operator* (const SQmatrix& a, const SQmatrix& b) noexcept {
    return SQmatrix(
        a * b.Col1,
        a * b.Col2
    );
}

//
inline SQmatrix abs (const SQmatrix& sqmatrix) noexcept {
    return SQmatrix(
        _ST abs(sqmatrix.Col1),
        _ST abs(sqmatrix.Col2)
    );
}

inline SQmatrix invert (const SQmatrix& sqmatrix) { 
    _AXC _VERIFY(sqmatrix.is_invertible(), "invert: det of matrix is 0!" );

    float det = sqmatrix.det();
    SQmatrix invert_matrix;
    float det_mult = 1.0f / det;

    invert_matrix.Col1.Xcoord =  det_mult * sqmatrix.Col2.Ycoord;
    invert_matrix.Col1.Ycoord = -det_mult * sqmatrix.Col1.Ycoord;

    invert_matrix.Col2.Xcoord = -det_mult * sqmatrix.Col2.Xcoord;
    invert_matrix.Col2.Ycoord =  det_mult * sqmatrix.Col1.Xcoord;

    return invert_matrix;
}

// transpose matrix  
inline SQmatrix transpose (const SQmatrix& sqmatrix) noexcept {
    return SQmatrix (Gvector(sqmatrix.Col1.Xcoord, sqmatrix.Col2.Xcoord),
                     Gvector(sqmatrix.Col1.Ycoord, sqmatrix.Col2.Ycoord)
                );
}

_ST_END // END namespace st

#endif // SQMATRIX_H
