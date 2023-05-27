#ifndef LINE_H
#define LINE_H

#include "Point.hpp"

_ST_BEGIN
using namespace _math;

////////////////////////////////////////////////////////////
/// \brief Utility struct for manipulating
///        2-dimensional vectors. Type of values is float.
///
////////////////////////////////////////////////////////////
struct Line {

    Line (const Point& a, Point& b) noexcept : 
        begin(a),
        end(b),
        direction(end.Xcoord - begin.Xcoord, end.Ycoord - end.Ycoord)
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

_ST_END // END namespace st

#endif // POINT_H
