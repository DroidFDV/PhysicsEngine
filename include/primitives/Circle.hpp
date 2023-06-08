#ifndef CIRCLE_H
#define CIRCLE_H


#include "../Math.hpp"
#include "IShell.h"


using namespace _math;


////////////////////////////////////////////////////////////
/// \brief Derived class from IShell to present a circle shape
///
////////////////////////////////////////////////////////////
class Circle : public IShell {
public:
    
    ////////////////////////////////////////////////////////////
    /// \brief Construct circle shape by given body
    ///
    ////////////////////////////////////////////////////////////
    Circle (RigidBody* body) noexcept :
        IShell(body)
    {
        if (body->ShapeTraits.shapeTy != body_shape_type::Circle) {
            body->ShapeTraits.shapeTy = body_shape_type::Circle;
        }
    }

    ////////////////////////////////////////////////////////////
    /// \brief Get radius of inner rigid body
    /// \return Radius of inner body
    /// \warning Not availible for AABB and OBB
    ////////////////////////////////////////////////////////////
    float getRadius() const noexcept {
        return this->getSize().Xcoord;
    }
    
    ////////////////////////////////////////////////////////////
    /// \brief Destructor
    ///
    ////////////////////////////////////////////////////////////
    ~Circle() override = default;
};


#endif // CIRCLE_H
