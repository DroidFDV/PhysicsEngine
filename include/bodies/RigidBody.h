// simple class presenting an object


#ifndef RIGIDBODY_H
#define RIGIDBODY_H 


#include "../Math.hpp"



using namespace _math;

struct RigidBody {

    RigidBody();

// 
    void set (const Gvector& _Width, float _Mass) noexcept;

    void addForce (const Gvector& _Force) noexcept;
    
    
    Gvector width;
    Point position;
    float rotation;

    Gvector velocity;
    float   angularVelocity;

    Gvector force;
    float   torque;

    float friction;
    float mass, invMass;
    float I, invI;
};

#endif // RIGIDBODY_H 
