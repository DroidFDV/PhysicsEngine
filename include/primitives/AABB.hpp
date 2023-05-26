//

#ifndef AABB_H
#define AABB_H


#include "../Math.hpp"
#include "../bodies/RigidBody.h"



using namespace _math;

struct AABB {
    
    // using position = _Mybody->position;
    
    AABB (const Point& maxCorner, const Point& minCorner) noexcept :
        size(maxCorner - minCorner),
        _Mybody(nullptr)
    {}
    
    //
    Point getMaxCorner() const {
        _AXC _VERIFY (_Mybody == nullptr, "_Mybody is nullptr!");
        return Point(_Mybody->position + size * 0.5f);
    } 
    
    //
    Point getMinCorner() const {
        _AXC _VERIFY (_Mybody == nullptr, "_Mybody is nullptr!");
        return Point(_Mybody->position - size * 0.5f);
    }

    //
    std::vector<Point> getVertices() const {
        _AXC _VERIFY (_Mybody == nullptr, "_Mybody is nullptr!");
        std::vector<Point> vertices; 

        Point minCorner = _Mybody->position + size * 0.5f;
        Point maxCorner = _Mybody->position - size * 0.5f;
       
        vertices.push_back(minCorner);
        vertices.push_back(Point(minCorner.Xcoord, maxCorner.Ycoord));
        vertices.push_back(maxCorner);
        vertices.push_back(Point(maxCorner.Xcoord, minCorner.Ycoord));

        return vertices;
    }
    

    
    RigidBody* _Mybody;
    Gvector    size;   // [width, height]
};


#endif // AABB_H
