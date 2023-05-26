//

#include "../../../../include/bodies/Joint.h"

//
bool CollisionDetector::PointLine (const Point& point, const Line& line) const {
    float dy = line.end.Ycoord - line.begin.Ycoord;
    float dx = line.end.Xcoord - line.begin.Xcoord;  

    float k = dy / dx;
    float b = line.begin.Ycoord - k * line.begin.Xcoord;

    // now we have an equation of line: y = kx + b;

    return ( AlmostEqual(point.Ycoord, k * point.Xcoord + b) );
}

//
bool CollisionDetector::PointCircle (const Point& point, const Circle& circle) const {
    Gvector pointTOcenter(circle._Mybody->position - point);
    return ( AlmostEqual(dot(pointTOcenter, pointTOcenter), circle.radius * circle.radius) );
}
