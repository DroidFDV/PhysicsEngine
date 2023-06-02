// primitive form to shell the rigid body


#ifndef CIRCLE_H
#define CIRCLE_H


#include "../Math.hpp"
#include "IShell.h"


using namespace _math;


class Circle : public IShell {
    
    Circle (RigidBody* body, float radius = 1.0f) noexcept :
        IShell(body),
        Radius(radius)
    {}

    ~Circle() override = default;

    float Radius;
};



#endif // CIRCLE_H
