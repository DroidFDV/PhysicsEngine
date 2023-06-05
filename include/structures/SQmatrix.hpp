#ifndef SQMATRIX_H
#define SQMATRIX_H


#include "../Math.hpp"
#include "Gvector.hpp"


_ST_BEGIN
using namespace _math;


////////////////////////////////////////////////////////////
///  Utility struct to present matrix 2x2 over real number
///  field
///
////////////////////////////////////////////////////////////
struct SQmatrix {
    
    ////////////////////////////////////////////////////////////
    /// Default constructor
    ///
    ////////////////////////////////////////////////////////////
    explicit SQmatrix() noexcept = default;

    ////////////////////////////////////////////////////////////
    /// Constructor of rotation matrix
    ///
    /// \param angleDegrees rotarion angle in degrees
    ////////////////////////////////////////////////////////////
    explicit SQmatrix (float angleDegrees) noexcept {
        float angleRadians = _math::toRadians(angleDegrees);
        float cos_rot = cosf(angleRadians);
        float sin_rot = sinf(angleRadians);

        Col1.Xcoord = cos_rot;  Col2.Xcoord = -sin_rot;
        Col1.Ycoord = sin_rot; Col2.Ycoord = cos_rot;
    }

    ////////////////////////////////////////////////////////////
    /// Copy constructor
    ///
    //////////////////////////////////////////////////////////// 
    SQmatrix (const SQmatrix&) noexcept = default;

    ////////////////////////////////////////////////////////////
    /// Move constructor
    ///
    ////////////////////////////////////////////////////////////
    SQmatrix (SQmatrix&&) noexcept = default;

    ////////////////////////////////////////////////////////////
    /// Construct matrix through given vectors as columns
    ///
    /// \param _Gvec1 first column
    /// \param _Gvec2 second column
    ////////////////////////////////////////////////////////////
    SQmatrix (const Gvector& _Gvec1, const Gvector& _Gvec2) noexcept : Col1(_Gvec1), Col2(_Gvec2) {}

    ////////////////////////////////////////////////////////////
    /// Copy assignment
    ///
    ////////////////////////////////////////////////////////////
    SQmatrix& operator= (const SQmatrix&) noexcept = default;

    ////////////////////////////////////////////////////////////
    /// Move constructor
    ///
    //////////////////////////////////////////////////////////// 
    SQmatrix& operator= (SQmatrix&&) noexcept = default;
    
    ////////////////////////////////////////////////////////////
    /// Destructor
    ///
    ////////////////////////////////////////////////////////////
    ~SQmatrix() noexcept = default;

    ////////////////////////////////////////////////////////////
    /// \brief Overload of binary operator+= 
    ///
    /// This operator performs a memberwise addition of both matrix,
    /// and assigns the result to *this.
    ///
    /// \param _Rhs Right operand (a matrix) 
    ////////////////////////////////////////////////////////////
    SQmatrix& operator+= (const SQmatrix& _Rhs) noexcept {
        Col1 += _Rhs.Col1;
        Col2 += _Rhs.Col2;
        return *this;
    }

    ////////////////////////////////////////////////////////////
    /// \brief Overload of binary operator-= 
    ///
    /// This operator performs a memberwise subtraction of both matrix,
    /// and assigns the result to *this.
    ///
    /// \param _Rhs Right operand (a matrix) 
    /// \return *this
    ////////////////////////////////////////////////////////////
    SQmatrix& operator-= (const SQmatrix& _Rhs) noexcept {
        Col1 -= _Rhs.Col1;
        Col2 -= _Rhs.Col2;
        return *this;
    }

    ////////////////////////////////////////////////////////////
    /// \brief Overload of binary operator*= 
    ///
    /// This operator performs a memberwise multiplication of matrix
    /// and scalar value, then assigns the result to *this.
    ///
    /// \param _Scla Right operand (a scalar value)
    /// \return *this
    ////////////////////////////////////////////////////////////
    SQmatrix& operator*= (float _Scal) noexcept {
        Col1 *= _Scal;
        Col2 *= _Scal;
        return *this;
    }

    ////////////////////////////////////////////////////////////
    /// Calculate the determinant of matrix 
    ///
    /// \return determinant of matrix
    ////////////////////////////////////////////////////////////
    float det() const noexcept {
        return Col1.Xcoord * Col2.Ycoord - Col1.Ycoord * Col2.Xcoord;
    }

    ////////////////////////////////////////////////////////////
    /// Check is matrix an invertible 
    ///
    /// \return if det != 0 return det, else 0
    ////////////////////////////////////////////////////////////
    float is_invertible() const noexcept {
        float det = this->det();
        return ( AlmostEqual(det, 0.0f) ? 0 : det);
    } 

    ////////////////////////////////////////////////////////////
    /// Member data
    ////////////////////////////////////////////////////////////
    Gvector Col1;
    Gvector Col2;
};

    ////////////////////////////////////////////////////////////
    /// \relates SQmatrix
    /// \brief Multiplication of matrix 2x2 and vector 2x1 
    ///
    /// This operator performs multiplication of matrix
    /// and vector.
    ///
    /// \param mat  Right operand (a matrix)
    /// \param gvec Left operand (a vector)
    /// \return new resulting vector 2x1 
    ////////////////////////////////////////////////////////////
inline Gvector operator* (const SQmatrix& mat, const Gvector& gvec) noexcept {
    return Gvector(
        mat.Col1.Xcoord * gvec.Xcoord + mat.Col2.Xcoord * gvec.Ycoord,
        mat.Col1.Ycoord * gvec.Xcoord + mat.Col2.Ycoord * gvec.Ycoord
    );
}

////////////////////////////////////////////////////////////
/// \relates SQmatrix
/// \brief Overload of binary operator+
///
/// This operator performs a memberwise addition of both 
/// matrices
///
/// \param _Lhs Left operand (a matrix)
/// \param _Rhs Right operand (a matrix)
/// \return Memberwise addition of both marices 
////////////////////////////////////////////////////////////
inline SQmatrix operator+ (const SQmatrix& _Lhs, const SQmatrix& _Rhs) noexcept {
    return SQmatrix(
        _Rhs.Col1 + _Lhs.Col1,
        _Rhs.Col2 + _Lhs.Col2
    );

    // SQmatrix _Tmp(_Lhs);
    // return _Tmp += _Rhs;
}

////////////////////////////////////////////////////////////
/// \relates SQmatrix
/// \brief Overload of binary operator-
///
/// This operator performs a memberwise subtracion of both 
/// matrices
///
/// \param _Lhs Left operand (a matrix)
/// \param _Rhs Right operand (a matrix)
/// \return Memberwise subtracion of both marices 
////////////////////////////////////////////////////////////
inline SQmatrix operator- (const SQmatrix& _Lhs, const SQmatrix& _Rhs) noexcept {
    return SQmatrix(
        _Rhs.Col1 - _Lhs.Col1,
        _Rhs.Col2 - _Lhs.Col2
    );
}

////////////////////////////////////////////////////////////
/// \relates SQmatrix
/// \brief Overload of binary operator*
///
/// This operator performs multiplication of matrix and 
/// scalar value
///
/// \param sqmatrix Left operand (a matrix)
/// \param _Scal    Right operand (a scalar value)
/// \return Mubtracion of matrix and scalar value 
////////////////////////////////////////////////////////////
inline SQmatrix operator* (const SQmatrix& sqmatrix, float _Scal) noexcept {
    return SQmatrix(
        sqmatrix.Col1 * _Scal,
        sqmatrix.Col2 * _Scal
    );
}

////////////////////////////////////////////////////////////
/// \relates SQmatrix
/// \brief Overload of binary operator*
///
/// This operator performs multiplication of both matrices
///
/// \param a Left operand (a matrix)
/// \param b Right operand (a matrix)
/// \return Mubtracion of matrix and matrix
////////////////////////////////////////////////////////////
inline SQmatrix operator* (const SQmatrix& a, const SQmatrix& b) noexcept {
    return SQmatrix(
        a * b.Col1,
        a * b.Col2
    );
}

////////////////////////////////////////////////////////////
/// \relates SQmatrix
/// \brief Absolute matrix
///
/// \param sqmatrix matrix
/// \return Matrix with abs coeffs 
////////////////////////////////////////////////////////////
inline SQmatrix abs (const SQmatrix& sqmatrix) noexcept {
    return SQmatrix(
        _ST abs(sqmatrix.Col1),
        _ST abs(sqmatrix.Col2)
    );
}

////////////////////////////////////////////////////////////
/// \relates SQmatrix
/// \brief Calculate invetred matrix to given 
///
/// \param sqmatrix matrix to invert 
/// \return New inverted matrix
////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////
/// \relates SQmatrix
/// \brief Transpose matrix
///
/// \param sqmatrix matrix to transpose
/// \return new transposed matrix 
//////////////////////////////////////////////////////////// 
inline SQmatrix transpose (const SQmatrix& sqmatrix) noexcept {
    return SQmatrix (Gvector(sqmatrix.Col1.Xcoord, sqmatrix.Col2.Xcoord),
                     Gvector(sqmatrix.Col1.Ycoord, sqmatrix.Col2.Ycoord)
                );
}


_ST_END // END namespace st

#endif // SQMATRIX_H
