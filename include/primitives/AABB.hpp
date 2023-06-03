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
 
    AABB (const Point& maxCorner, const Point& minCorner) noexcept :
        IShell(nullptr),
        Size(maxCorner - minCorner)
    {}
   
    ~AABB() override = default;
    
    //
    Point getLocalMaxCorner() const {
        _AXC _VERIFY (Mybody == nullptr, "Mybody is nullptr!");
        return Point(Mybody->Position + Size * 0.5f);
    } 
    
    //
    Point getLocalMinCorner() const {
        _AXC _VERIFY (Mybody == nullptr, "Mybody is nullptr!");
        return Point(Mybody->Position - Size * 0.5f);
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

        Point minCorner = Mybody->Position + Size * 0.5f;
        Point maxCorner = Mybody->Position - Size * 0.5f;
       
        vertices.push_back(maxCorner);
        vertices.push_back(Point(minCorner.Xcoord, maxCorner.Ycoord));
        vertices.push_back(minCorner);
        vertices.push_back(Point(maxCorner.Xcoord, minCorner.Ycoord));

        return vertices;
    }
    
    
    
    Gvector Size;   // [width, height]
};


#endif // AABB_H
