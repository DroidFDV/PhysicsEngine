//

#include "../Math.hpp"
#include "../bodies/RigidBody.h"

#ifndef OBB_H
#define OBB_H



using namespace _math;

struct OBB {
    
    // using position = _Mybody->position;
    
    OBB (const Point& maxCorner, const Point& minCorner) noexcept :
        size(maxCorner.Coords - minCorner.Coords),
        _Mybody(nullptr)
    {}
    
    // TODO its incorrect
    Point getMaxCorner() const {
        _AXC _VERIFY (_Mybody == nullptr, "_Mybody is nullptr!");
        return Point(_Mybody->position.Coords + size * 0.5f);
    } 
    
    // TODO int incorrect
    Point getMinCorner() const {
        _AXC _VERIFY (_Mybody == nullptr, "_Mybody is nullptr!");
        return Point(_Mybody->position.Coords - size * 0.5f);
    }

    //
    std::vector<Point> getVertices() const {
        _AXC _VERIFY (_Mybody == nullptr, "_Mybody is nullptr!");
        std::vector<Point> vertices; 

        Point minCorner = _Mybody->position.Coords + size * 0.5f;
        Point maxCorner = _Mybody->position.Coords - size * 0.5f;
       
        vertices.push_back(minCorner);
        vertices.push_back(Point(minCorner.Coords.Xcoord, maxCorner.Coords.Ycoord));
        vertices.push_back(maxCorner);
        vertices.push_back(Point(maxCorner.Coords.Xcoord, minCorner.Coords.Ycoord));

        if ( !AlmostEqual(rotation, 0.0f) ) {
            SQmatrix RotMatrix(rotation);

            for (Point& vertice : vertices) {
                vertice = vertice.rotate(_Mybody->position, RotMatrix);
            }
        }

        return vertices;
    }
    

    
    RigidBody* _Mybody;
    Gvector    size;   // [width, height]
    float      rotation;
};


#endif // OBB_H
