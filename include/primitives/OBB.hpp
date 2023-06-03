#ifndef OBB_H
#define OBB_H


#include "../Math.hpp"
#include "IShell.h"


using namespace _math;


class OBB : public IShell {
    
    // TODO i should calculate Size other way
    OBB (const Point& maxCorner, const Point& minCorner) noexcept :
        IShell(nullptr),
        Size(maxCorner - minCorner)
    {}
    
    // TODO Size there incorrect
    Point getMaxCorner() const {
        _AXC _VERIFY (Mybody == nullptr, "Mybody is nullptr!");
        return Point(Mybody->Position + Size * 0.5f);
    } 
    
    // TODO Size there incorrect
    Point getMinCorner() const {
        _AXC _VERIFY (Mybody == nullptr, "Mybody is nullptr!");
        return Point(Mybody->Position - Size * 0.5f);
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

        if ( !AlmostEqual(Rotation, 0.0f) )
        {
            SQmatrix RotMatrix(Rotation);
            for (Point& vertice : vertices) {
                vertice = vertice.rotate(Mybody->Position, RotMatrix);
            }
        }
        return vertices;
    }
    
    
    
    RigidBody* Mybody;
    Gvector    Size;     // [width, height]
    float      Rotation;
};


#endif // OBB_H
