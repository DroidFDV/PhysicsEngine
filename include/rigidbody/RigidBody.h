#ifndef RIGIDBODY_H
#define RIGIDBODY_H 


#include "../Math.hpp"
#include "../structures/Gvector.hpp"
#include "../structures/Point.hpp"
#include <type_traits>


using namespace _math;
using namespace _st;


union body_traits {
   
    enum class type {
        Circle,
        // Triangle,
        Box
    } bTy;

};


struct RigidBody {

    using traits = std::underlying_type<body_traits>;
    
    // TODO do i need constexpr here?
    RigidBody(body_traits::type bodyType) noexcept;

    // void set (const Point& position, const Gvector& width, float mass) noexcept;

    void set (const Point& position, const Gvector& size, float mass);

    void applyForce (const Gvector& force) noexcept;
    
    void updatePosition (float dt); 

    void updateVelocity (const Gvector& velocity, float dt);

    void addVelocity (const Gvector& velocity, float dt);
    
    
    
    //////////////////////////////////////////////////////////// 
    /// Rigid body properties
        static body_traits BodyTraits;

    /// State
        Point   Position;
        float   Rotation;
        Gvector Velocity;
        float   AngularVelocity;
    
    /// Box properties
        Gvector Size;
        float   Mass, InvMass;
        float   InertiaTensor, InvI;
        // float   Friction;

    /// Applied forces
        Gvector Force;
        float   Torque;
    ////////////////////////////////////////////////////////////
};

#endif // RIGIDBODY_H 
