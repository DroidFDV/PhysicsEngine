// primitive form to shell the rigid body


#ifndef CIRCLE_H
#define CIRCLE_H


#include "../Math.hpp"
#include "../bodies/RigidBody.h"



struct Circle {
    
    Circle (float _Radius = 1.0f) noexcept : radius(_Radius) {}

    float radius;
};



#endif // CIRCLE_H
