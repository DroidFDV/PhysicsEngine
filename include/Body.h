// simple class presenting an object

#ifndef BODY_H
#define BODY_H 

#include "FlatMathUtils.hpp"


struct Body {

    Body() = default;

// 
    void set (const _math::gvector& w, float M);

    void addForce (const _math::gvector& _Force) { force += _Force; }
    
    
    _math::gvector width;
    _math::gvector position;
    float          rotation;

    _math::gvector velocity;
    float          angularVelocity;

    _math::gvector force;
    float          torque;

    float friction;
    float mass, invMass;
    float I, invI;
};

#endif //  
