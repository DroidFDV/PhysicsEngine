#ifndef POINT_H
#define POINT_H

#include "SQmatrix.hpp"

_ST_BEGIN
using namespace _math;

////////////////////////////////////////////////////////////
/// Utility struct to present a point in R^2 
///
////////////////////////////////////////////////////////////
struct Point : Gvector {
    
    ////////////////////////////////////////////////////////////
    /// Construct a point through two given coords
    /// 
    /// \param x first coord
    /// \param y second coord
    ////////////////////////////////////////////////////////////
    Point (float x = 0.0f, float y = 0.0f) noexcept : Gvector(x,y) {}

    ////////////////////////////////////////////////////////////
    /// Construct a point through given vector
    /// 
    /// \param gvector vector to construct (a vector)
    ////////////////////////////////////////////////////////////
    Point (const Gvector& gvector) noexcept : Gvector(gvector) {}

    ////////////////////////////////////////////////////////////
    /// Set point's coords
    /// 
    /// \param x first new coord
    /// \param y second new coord
    /// \return New point with (x,y) coords
    ////////////////////////////////////////////////////////////
    Point& set (float x, float y) noexcept {
        Xcoord = x;
        Ycoord = y;
        return *this;
    }

    ////////////////////////////////////////////////////////////
    /// Rotate point with respect other point
    /// 
    /// \param Origin point to be rotated around it
    /// \param AngleDegrees rotation angle in degrees
    /// \return New rotated point
    ////////////////////////////////////////////////////////////
    Point rotate (const Point& Origin, float AngleDegrees) const noexcept {
        SQmatrix RotMatrix(AngleDegrees);
        return Point( (RotMatrix * (*this - Origin)) + Origin );
    }

    ////////////////////////////////////////////////////////////
    /// Rotate point with respect other point
    /// 
    /// \param Origin point to be rotated around it
    /// \param RotMatrix rotation matrix
    /// \return New rotated point
    ////////////////////////////////////////////////////////////
    Point rotate (const Point& Origin, const SQmatrix& RotMatrix) const noexcept {
        return Point( (RotMatrix * (*this - Origin)) + Origin );
    }
};


_ST_END // END namespace st

#endif // POINT_H
