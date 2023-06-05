#ifndef POINT_H
#define POINT_H

#include "SQmatrix.hpp"

_ST_BEGIN
using namespace _math;

////////////////////////////////////////////////////////////
/// \brief Utility struct for manipulating
///        2-dimensional vectors. Type of values is float.
///
////////////////////////////////////////////////////////////
struct Point : Gvector {

    Point (float x = 0.0f, float y = 0.0f) noexcept : Gvector(x,y) {}

    Point (const Gvector& gvector) noexcept : Gvector(gvector) {}

    Point& set (float x, float y) noexcept {
        Xcoord = x;
        Ycoord = y;
        return *this;
    }

    //
    Point rotate (const Point& Origin, float AngleDegrees) const noexcept {
        SQmatrix RotMatrix(AngleDegrees);
        return Point( (RotMatrix * (*this - Origin)) + Origin );
    }

    //
    Point rotate (const Point& Origin, const SQmatrix& RotMatrix) const noexcept {
        return Point( (RotMatrix * (*this - Origin)) + Origin );
    }
};

_ST_END // END namespace st

#endif // POINT_H
