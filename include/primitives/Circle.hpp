// primitive form to shell the rigid body


#ifndef CIRCLE_H
#define CIRCLE_H


#include "../Math.hpp"
#include "IShell.h"


using namespace _math;


class Circle : public IShell {
public:
    
    using body_shape_type = RigidBody::shape_traits::type;


    Circle (RigidBody* body) noexcept :
        IShell(body)
    {
        if (body->ShapeTraits.shapeTy != body_shape_type::Circle) {
            body->ShapeTraits.shapeTy = body_shape_type::Circle;
        }
    }

    float getRadius() noexcept {
        return this->getSize().Xcoord;
    }

    ~Circle() override = default;
};



#endif // CIRCLE_H
