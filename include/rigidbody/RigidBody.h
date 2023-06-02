#ifndef RIGIDBODY_H
#define RIGIDBODY_H 


#include "../Math.hpp"
#include "../structures/Gvector.hpp"
#include "../structures/Point.hpp"


using namespace _math;
using namespace _st;


struct RigidBody {

    RigidBody();

    void set (const Gvector& width, float mass) noexcept;

    void applyForce (const Gvector& force) noexcept;
    
   

    // Gvector Width;
    Point Position;
    float Rotation;

    Gvector Velocity;
    float   AngularVelocity;

    Gvector Force;
    float   Torque;

    // float Friction;
    float Mass, InvMass;
    float I, InvI;
};

#endif // RIGIDBODY_H 
