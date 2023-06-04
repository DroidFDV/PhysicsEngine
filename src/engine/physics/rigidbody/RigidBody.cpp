#include "../../../../include/rigidbody/RigidBody.h"
#include "../../../../include/Utils.hpp"


RigidBody::RigidBody(body_traits::type bodyType) noexcept :
    Position(0.0f, 0.0f),
    Rotation(0.0f),
    Velocity(0.0f, 0.0f),
    AngularVelocity(0.0f),
    Size(1.0f, 1.0f),
    Mass(FLT_MAX),
    InvMass(0.0f),
    InertiaTensor(FLT_MAX),
    InvI(0.0f),
    // Friction(0.2f),
    Force(0.0f, 0.0f),
    Torque(0.0f)
{ 
    BodyTraits.bTy = bodyType;
    // BodyTraits.bTy(bodyType)
}
    

void RigidBody::set (const Point& position, const Gvector& size, float mass) {
    _AXC _VERIFY(mass < 0, "Mass of the object should be positive");
   
    Position = position;
    Rotation = 0.0f;
    Velocity = Gvector(0.0f, 0.0f);
    AngularVelocity = 0.0f;
    
    Size     = size; 
    Mass     = mass; 
    // Friction = 0.2f;
    
    Force    = Gvector(0.0f, 0.f);
    Torque   = 0.0f;

    if (mass < FLT_MAX) { // super massive rigid body
        InvMass = 1.0f / mass;
        InertiaTensor = mass * dot(Size, Size) / 12.0f; // TODO Why 12.0f?
        InvI = 1.0f / InertiaTensor;
    } else {
        InvMass = 0.0f;
        InertiaTensor = FLT_MAX;
        InvI = 0.0f;
    }
}


void RigidBody::updateForce (const Gvector& force) noexcept {
    Force += force;
}
