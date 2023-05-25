// simple class presenting an object

#ifndef BODY_H
#define BODY_H 

#include "FlatMathUtils.hpp"


struct Body {

    Body();

// 
    void set (const _math::gvector& _Width, float _Mass) noexcept;

    void addForce (const _math::gvector& _Force) noexcept;
    
    
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
