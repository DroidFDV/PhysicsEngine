#ifndef SQMATRIX_H
#define SQMATRIX_H

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
    SQmatrix& operator*= (float _Scal) noexcept {
        col1 *= _Scal;
        col2 *= _Scal;
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
inline SQmatrix operator* (const SQmatrix& sqmatrix, float _Scal) noexcept {
    return SQmatrix(
        sqmatrix.col1 * _Scal,
        sqmatrix.col2 * _Scal
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

_ST_END // END namespace st

#endif // SQMATRIX_H
