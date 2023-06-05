#ifndef LINE_H
#define LINE_H


#include "Point.hpp"


_ST_BEGIN
using namespace _math;


////////////////////////////////////////////////////////////
/// \brief Utility struct to present a line 
///
////////////////////////////////////////////////////////////
struct Line {

    
    ////////////////////////////////////////////////////////////
    /// \brief Construct a line through two given points
    /// 
    /// \param a first point
    /// \param b second point
    ///
    ////////////////////////////////////////////////////////////
    Line (const Point& a, Point& b) noexcept : 
        begin(a),
        end(b),
        direction(end.Xcoord - begin.Xcoord, end.Ycoord - end.Ycoord)
    {}

    ////////////////////////////////////////////////////////////
    /// \brief Construct a line through point and direction
    ///        vector
    ///
    /// \param a         point
    /// \param dirVector direction vector
    ///
    /// TODO: check correctness of the dirVector (!= 0) within 
    ///       template, mb create a struct null_vector??
    ////////////////////////////////////////////////////////////
    // Line (const Point& a, const Gvector& dirVector) :
    //     begin(a),
    // {}

    
    ////////////////////////////////////////////////////////////
    /// \brief Construct a line through point and direction
    ///        vector
    /// 
    /// \param dirVector direction vector
    ///
    /// TODO: TODO check dirVector != 0
    ////////////////////////////////////////////////////////////
    Line (const Gvector& dirVector) : 
        begin(0,0),
        end(dirVector.Xcoord, dirVector.Xcoord),
        direction(dirVector) 
    {}
    
    ////////////////////////////////////////////////////////////
    /// \brief rotate line by given angle with respect of origin
    ///        point
    /// 
    /// \param Origin point to rotate with respect of it
    /// \param angle  angle to rotate in degrees
    ///
    /// \return rotated line
    ////////////////////////////////////////////////////////////
    Line rotate (const Point& Origin, float angleDegrees) noexcept {
        SQmatrix RotMatrix(angleDegrees);
        Point _Begin ( begin.rotate(Origin, RotMatrix) );
        Point _End ( end.rotate(Origin, RotMatrix) );

        return Line (_Begin, _End);
    }
    
    
    
    ////////////////////////////////////////////////////////////
    /// Member data
    ////////////////////////////////////////////////////////////
    Point   begin;
    Point   end;
    Gvector direction; 
};


_ST_END // END namespace _math

    
#endif // POINT_H
