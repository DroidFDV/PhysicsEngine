#ifndef RIGIDBODY_H
#define RIGIDBODY_H 


#include "../Math.hpp"
#include "../structures/Gvector.hpp"
#include "../structures/Point.hpp"


using namespace _math;
using namespace _st;


struct RigidBody {
   
    struct shape_traits {
       
        enum class type {
            Circle,
            Triangle,
            Box,
        } shapeTy;
    };
   
    // using traits = std::underlying_type<body_traits>;
    
    // TODO do i need constexpr here?
    RigidBody(shape_traits::type bodyType) noexcept;

    // void set (const Point& position, const Gvector& width, float mass) noexcept;

    void set (const Point& position, const Gvector& size, float mass);

    void addForce (const Gvector& force) noexcept;
    
    void updatePosition (float dt); 

    void updateVelocity (const Gvector& velocity, float dt);

    void addVelocity (const Gvector& velocity, float dt);
    
    

    //////////////////////////////////////////////////////////// 
    /// Rigid body properties
        static shape_traits ShapeTraits;

    /// State
        Point   Position;
        float   Rotation;
        Gvector Velocity; // linear velocity
        float   AngularVelocity;
    
    /// Box properties
        Gvector Size; // if ShapeTraits.shapeTy == shape_traits::type::Circle
    //                   => Size = (Radius, Radius), else [width, height]
        float   Mass, InvMass;
        float   InertiaTensor, InvI;
        float   Friction;

    /// Applied forces
        Gvector Force; // accumulated force
        float   Torque;
    ////////////////////////////////////////////////////////////
};

#endif // RIGIDBODY_H 
