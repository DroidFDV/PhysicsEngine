#ifndef GVECTOR_H
#define GVECTOR_H


#include "../Math.hpp"
#include <SFML/Graphics.hpp>


#define _ST_BEGIN namespace _st {
#define _ST_END   }
#define _ST       ::_st::

_ST_BEGIN
using namespace _math;

////////////////////////////////////////////////////////////
/// \brief Utility struct for manipulating
///        2-dimensional vectors. Type of values is float.
///
////////////////////////////////////////////////////////////
struct Gvector {

    using value_type = float;
     
    ////////////////////////////////////////////////////////////
    /// \brief Default constructor the vector from its coordinates
    ///
    /// \param x Xcoord 
    /// \param y Ycoord 
    ///
    ////////////////////////////////////////////////////////////
    Gvector (float x = 0.0f, float y = 0.0f) noexcept : Xcoord(x), Ycoord(y) {}

    ////////////////////////////////////////////////////////////
    /// \brief Construct the vector from another one
    ///
    /// \param _Other Gvector to convert
    ///
    ////////////////////////////////////////////////////////////
    Gvector (const Gvector& _Other) noexcept = default;
 
    ////////////////////////////////////////////////////////////
    /// \brief Copy assigment constructor
    ///
    /// \param _Rhs Gvector to copy assigment
    ///
    ////////////////////////////////////////////////////////////
    Gvector& operator= (const Gvector& _Rhs) noexcept {
        Xcoord = _Rhs.Xcoord;
        Ycoord = _Rhs.Ycoord;
        return *this;
    }

    ////////////////////////////////////////////////////////////
    /// \brief User-defined type conversation from _st::Gvector
    ///        to sf::Vector2f
    ///
    /// \return New sf::Vector2f with coords Xcoord, Ycoord
    ////////////////////////////////////////////////////////////
    operator sf::Vector2f() const {
        return sf::Vector2f{Xcoord, Ycoord};
    }

    ////////////////////////////////////////////////////////////
    /// \brief Function to set or change vector coordinates
    ///
    /// \param x new Xcoord coordinate
    /// \param y new Ycoord coordinate
    ///
    /// \return Reference to vector with new coordinates values
    ///
    ////////////////////////////////////////////////////////////
    Gvector& set (float x, float y) noexcept {
        Xcoord = x;
        Ycoord = y;
        return *this;
    }

    ////////////////////////////////////////////////////////////
    /// \brief Calculates the norm of the vector
    ///
    /// \return norm of the vector
    ///
    ////////////////////////////////////////////////////////////
    float norm() const noexcept {
        return sqrtf(Xcoord * Xcoord + Ycoord * Ycoord);
    }

    ////////////////////////////////////////////////////////////
    /// \brief Checks does Gvector has a 0 coordinates
    ///
    /// \return if vector is null vector return true, else false
    ///
    ////////////////////////////////////////////////////////////
    bool is_null() const noexcept {
        return AlmostEqual(Xcoord - Ycoord, 0);
    }
    
    ////////////////////////////////////////////////////////////
    /// Member data
    ////////////////////////////////////////////////////////////
    float Xcoord;
    float Ycoord;
}; 

////////////////////////////////////////////////////////////
/// \relates Gvector
/// \brief Overload of unary operator-
///
/// \param Rhs Gvector to negate
///
/// \return Memberwise opposite of the given vector
///
////////////////////////////////////////////////////////////
inline Gvector operator- (const Gvector& Rhs) noexcept {
    return Gvector(-Rhs.Xcoord, -Rhs.Ycoord);
}

////////////////////////////////////////////////////////////
/// \relates Gvector
/// \brief Overload of binary operator+=
///
/// This operator performs a memberwise addition of both vectors,
/// and assigns the result to \a _Lhs.
///
/// \param _Lhs Left operand (a vector)
/// \param _Rhs Rihgt operand (a vector)
///
/// \return Reference to \a _Lhs
///
////////////////////////////////////////////////////////////
inline Gvector& operator+= (Gvector& _Lhs, const Gvector& _Rhs) noexcept {
    _Lhs.Xcoord += _Rhs.Xcoord;
    _Lhs.Ycoord += _Rhs.Ycoord;
    return _Lhs;
}

////////////////////////////////////////////////////////////
/// \relates Gvector
/// \brief Overload of binary operator-=
///
/// This operator performs a memberwise addition of both vectors,
/// and assigns the result to \a _Lhs.
///
/// \param _Lhs Left operand (a vector)
/// \param _Rhs Rihgt operand (a vector)
///
/// \return Reference to \a _Lhs
///
////////////////////////////////////////////////////////////
inline Gvector& operator-= (Gvector& _Lhs, const Gvector& _Rhs) noexcept {
    _Lhs.Xcoord -= _Rhs.Xcoord;
    _Lhs.Ycoord -= _Rhs.Ycoord;
    return _Lhs;
}

////////////////////////////////////////////////////////////
/// \relates Gvector
/// \brief Overload of binary operator*=
///
/// This operator performs a memberwise multiplication of vector,
/// and assigns the result to \a _Lhs.
///
/// \param _Lhs   Left operand (a vector)
/// \param _Scal Rihgt operand (a scalar value)
///
/// \return Reference to \a _Lhs
///
////////////////////////////////////////////////////////////
inline Gvector& operator*= (Gvector& _Lhs, float _Scal) noexcept {
    _Lhs.Xcoord *= _Scal;
    _Lhs.Ycoord *= _Scal;
    return _Lhs;
}

////////////////////////////////////////////////////////////
/// \relates Gvector
/// \brief Overload of binary operator+
///
/// \param _Lhs  Left operand (a vector)
/// \param _Rhs  Right operand (a vector)
///
/// \return Memberwise addition of both vectors
///
////////////////////////////////////////////////////////////
inline Gvector operator+ (const Gvector& _Lhs, const Gvector& _Rhs) noexcept {
    return Gvector(_Lhs.Xcoord + _Rhs.Xcoord, _Lhs.Ycoord + _Rhs.Ycoord);
}

////////////////////////////////////////////////////////////
/// \relates Gvector
/// \brief Overload of binary operator-
///
/// \param _Lhs  Left operand (a vector)
/// \param _Rhs  Right operand (a vector)
///
/// \return Memberwise subtraction of both vectors
///
////////////////////////////////////////////////////////////
inline Gvector operator- (const Gvector& _Lhs, const Gvector& _Rhs) noexcept {
    return Gvector(_Lhs.Xcoord - _Rhs.Xcoord, _Lhs.Ycoord - _Rhs.Ycoord);
}

////////////////////////////////////////////////////////////
/// \relates Gvector
/// \brief Overload of binary operator*
///
/// \param _Lhs   Left operand (a vector)
/// \param _Scal Right operand (a scalar value)
///
/// \return Memberwise multiplication by \a _Scal
///
////////////////////////////////////////////////////////////
inline Gvector operator* (const Gvector& _Lhs, float _Scal) noexcept {
    return Gvector(_Lhs.Xcoord * _Scal, _Lhs.Ycoord * _Scal);
}

////////////////////////////////////////////////////////////
/// \relates Gvector
/// \brief Overload of binary operator*
///
/// \param _Scal Left operand (a scalar value)
/// \param _Rhs   Right operand (a vector)
///
/// \return Memberwise multiplication by \a _Scal
///
////////////////////////////////////////////////////////////
inline Gvector operator* (float _Scal, const Gvector& _Rhs) noexcept {
    return Gvector(_Rhs.Xcoord * _Scal, _Rhs.Ycoord * _Scal);
}

////////////////////////////////////////////////////////////
/// \relates Gvector
/// \brief Overload of binary operator/
///
/// \param _Lhs   Left operand (a vector)
/// \param _Scal Right operand (a scalar value)
///
/// \return Memberwise division by \a _Scal
///
////////////////////////////////////////////////////////////
inline Gvector operator/ (const Gvector& _Lhs, float _Scal) {
    _AXC _VERIFY(AlmostEqual(_Scal, 0), "division by 0!");
    return Gvector(_Lhs.Xcoord / _Scal, _Lhs.Ycoord / _Scal);
}

////////////////////////////////////////////////////////////
/// \relates Gvector
/// \brief Overload of binary operator/=
///
/// This operator performs a memberwise division by \a _Scal,
/// and assigns the result to \a _Lhs.
///
/// \param _Lhs   Left operand (a vector)
/// \param _Scal Right operand (a scalar value)
///
/// \return Reference to \a _Lhs
///
////////////////////////////////////////////////////////////
inline Gvector& operator/= (Gvector& _Lhs, float _Scal) { 
    _AXC _VERIFY(AlmostEqual(_Scal,0), "division by 0!");
    _Lhs.Xcoord /= _Scal;
    _Lhs.Ycoord /= _Scal;
    return _Lhs;
}

////////////////////////////////////////////////////////////
/// \relates Gvector
/// \brief Overload of binary operator==
///
/// This operator compares strict equality between two vectors.
///
/// \param _Lhs Left operand (a vector)
/// \param _Rhs Right operand (a vector)
///
/// \return True if \a _Lhs is equal to \a _Rhs
///
////////////////////////////////////////////////////////////
inline bool operator== (const Gvector& _Lhs, const Gvector& _Rhs) noexcept {
    return AlmostEqual(_Lhs.Xcoord, _Rhs.Xcoord) && AlmostEqual(_Lhs.Ycoord, _Rhs.Ycoord);
}

////////////////////////////////////////////////////////////
/// \relates Gvector
/// \brief Overload of binary operator!=
///
/// This operator compares strict difference between two vectors.
///
/// \param _Lhs Left operand (a vector)
/// \param _Rhs Right operand (a vector)
///
/// \return True if \a _Lhs is not equal to \a _Rhs
///
////////////////////////////////////////////////////////////
inline bool operator!= (const Gvector& _Lhs, const Gvector& _Rhs) noexcept {
    return !(_Lhs == _Rhs);
}

////////////////////////////////////////////////////////////
/// \relates Gvector
/// \brief Dot product of 2 vectors
///
/// \param a first operand (a vector)
/// \param b second operand (a vector)
///
/// \return Dot product of two given vectors
///
////////////////////////////////////////////////////////////
inline float dot (const Gvector& a, const Gvector& b) noexcept {
    return a.Xcoord * b.Xcoord + a.Ycoord * b.Ycoord;
}

////////////////////////////////////////////////////////////
/// \relates Gvector
/// \brief Cross product of 2 vectors
///
/// This function calculates cross product 2D vectors, if
/// their Zcoord = 0. The result equals a det of square matrix
/// based on 2 given vectors.
///
/// \param a first operand (a vector)
/// \param b second operand (a vector)
///
/// \return Cross product of two given vectors
///
////////////////////////////////////////////////////////////
inline float cross (const Gvector& a, const Gvector& b) noexcept {
    return a.Xcoord * b.Ycoord - a.Ycoord * b.Xcoord;
}

////////////////////////////////////////////////////////////
/// \brief Function gives a normal vector to given one
///
/// \param v vector ??
///
/// \return normal vector to \a v
///
////////////////////////////////////////////////////////////
inline Gvector getNormal (const Gvector& v) noexcept {
    return Gvector(v.Ycoord, -v.Xcoord);
}

////////////////////////////////////////////////////////////
/// \brief Calculates directional vector to given
///
/// \param v vector ??
///
/// \return directional vector to \a v
///
////////////////////////////////////////////////////////////
inline Gvector normalize (const Gvector& v) noexcept {
    float length = v.norm();
    return Gvector(v.Xcoord / length, v.Ycoord / length);
}

////////////////////////////////////////////////////////////
/// \relates Gvector
/// \brief Calculates an angle between two vectors
///
/// \param a first operand (a vector)
/// \param b second operand (a vector)
///
/// \return cos of angle between vectors \a a and \a b
///
////////////////////////////////////////////////////////////
inline float getCosAngle (const Gvector& a, const Gvector& b) noexcept {
    return dot(normalize(a), normalize(b));
}

////////////////////////////////////////////////////////////
/// \brief Absolute value of vector
///
/// \param v vector ??
///
/// \return vector with abs(coors) based on \a v
///
////////////////////////////////////////////////////////////
inline Gvector abs (const Gvector& v) noexcept {
    return Gvector(
        _MATH abs(v.Xcoord),
        _MATH abs(v.Ycoord)
    ); 
}

_ST_END // END namespace st

#endif // GVECTOR_H
////////////////////////////////////////////////////////////
/// \relates math Mathematical Library
///
/// Math support structures
///
////////////////////////////////////////////////////////////
