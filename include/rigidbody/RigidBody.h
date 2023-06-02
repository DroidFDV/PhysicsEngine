#ifndef RIGIDBODY_H
#define RIGIDBODY_H 


#include "../Math.hpp"
#include "../structures/Gvector.hpp"
#include "../structures/Point.hpp"


using namespace _math;
using namespace _st;


struct RigidBody {

    RigidBody() noexcept;

    // void set (const Point& position, const Gvector& width, float mass) noexcept;

    void set (const Point& position, const Gvector& size, float mass);

    void applyForce (const Gvector& force) noexcept;
    
   
    
    ////////////////////////////////////////////////////////////
    /// State
        Point   Position;
        float   Rotation;
        Gvector Velocity;
        float   AngularVelocity;
    ////////////////////////////////////////////////////////////
    
    ////////////////////////////////////////////////////////////
    /// Box properties
        Gvector Size;
        float   Mass, InvMass;
        float   InertiaTensor, InvI;
        float   Friction;
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    /// Applied forces
        Gvector Force;
        float   Torque;
    ////////////////////////////////////////////////////////////
};

#endif // RIGIDBODY_H 
