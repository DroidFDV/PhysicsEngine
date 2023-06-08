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

////////////////////////////////////////////////////////////
/// \brief Derived class from IShell to present right box
///
////////////////////////////////////////////////////////////
class AABB : public IShell {
public:
 
    ////////////////////////////////////////////////////////////
    /// \brief Construct AABB by given rigid body
    ///
    ////////////////////////////////////////////////////////////
    AABB (RigidBody* body) noexcept :
        IShell(body)
    {}
   
    ////////////////////////////////////////////////////////////
    /// \brief Destructor
    ///
    ////////////////////////////////////////////////////////////
    ~AABB() override = default;
    
    ////////////////////////////////////////////////////////////
    /// \brief Function to compute local max corner of body with
    ///        respect of the center of inner body 
    ///
    /// \return v1 in local space of innner body
    ////////////////////////////////////////////////////////////
    Point getLocalMaxCorner() const {
        _AXC _VERIFY (Mybody == nullptr, "Mybody is nullptr!");
        return Point(Mybody->Size * 0.5f);
    } 
    
    ////////////////////////////////////////////////////////////
    /// \brief Function to compute local min corner of body with
    ///        respect of the center of inner body 
    ///
    /// \return v3 in local space of innner body
    ////////////////////////////////////////////////////////////
    Point getLocalMinCorner() const {
        _AXC _VERIFY (Mybody == nullptr, "Mybody is nullptr!");
        return Point(-Mybody->Size * 0.5f);
    }

   ////////////////////////////////////////////////////////////
    /// \brief Function to compute world max corner of body with
    ///        respect of the center of world 
    ///
    /// \return v1 in world space
    ////////////////////////////////////////////////////////////
    Point getWorldMaxCorner() const {
        _AXC _VERIFY (Mybody == nullptr, "Mybody is nullptr!");
        return Point(Mybody->Position + Mybody->Size * 0.5f);
    }

    ////////////////////////////////////////////////////////////
    /// \brief Function to compute world min corner of body with
    ///        respect of the center of world 
    ///
    /// \return v3 in world space
    ////////////////////////////////////////////////////////////
    Point getWorldMinCorner() const {
        _AXC _VERIFY (Mybody == nullptr, "Mybody is nullptr!");
        return Point(Mybody->Position - Mybody->Size * 0.5f);
    }

    ////////////////////////////////////////////////////////////
    /// \brief Function to get vertices of rigid body
    ///
    /// \return std::vector<Point> std::vector of vertices 
    ///         { v1, v2, v3, v4 }
    ////////////////////////////////////////////////////////////
    std::vector<Point> getVertices() const {
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
