#ifndef AABB_H
#define AABB_H


#include "../Math.hpp"
#include "IShell.h"


using namespace _math;


// Box vertex and edge numbering:
//
//        ^ y
//        |
//        e1
//   v2 ------ v1
//    |        |
// e2 |        | e4  --> x
//    |        |
//   v3 ------ v4
//        e3
//


class AABB : public IShell {
public:
 
    AABB (RigidBody* body) noexcept :
        IShell(body)
    {}
   
    ~AABB() override = default;
    
    // TODO i'am not shure what i want to get here: do i need
    // to consider Mybody->Position as (0,0) here?
    Point getLocalMaxCorner() const {
        _AXC _VERIFY (Mybody == nullptr, "Mybody is nullptr!");
        return Point(Mybody->Position + Mybody->Size * 0.5f);
    } 
    
    //
    Point getLocalMinCorner() const {
        _AXC _VERIFY (Mybody == nullptr, "Mybody is nullptr!");
        return Point(Mybody->Position - Mybody->Size * 0.5f);
    }

    Point getWorldMaxCorner() const {
        return getLocalMaxCorner();
    }

    Point getWorldMinCorner() const {
        return getLocalMinCorner();
    }

    //
    std::vector<Point> getVertices() const
    {
        _AXC _VERIFY (Mybody == nullptr, "Mybody is nullptr!");
        std::vector<Point> vertices; 

        Point minCorner = Mybody->Position + Mybody->Size * 0.5f;
        Point maxCorner = Mybody->Position - Mybody->Size * 0.5f;
       
        vertices.push_back(maxCorner);
        vertices.push_back(Point(minCorner.Xcoord, maxCorner.Ycoord));
        vertices.push_back(minCorner);
        vertices.push_back(Point(maxCorner.Xcoord, minCorner.Ycoord));

        return vertices;
    }    
};


#endif // AABB_H
