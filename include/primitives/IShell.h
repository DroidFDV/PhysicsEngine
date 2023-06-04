#ifndef ISHELL_H
#define ISHELL_H


#include "../rigidbody/RigidBody.h"


class IShell {
public:
    
    IShell (RigidBody* body) noexcept : Mybody(body) {}
    
    virtual ~IShell() = 0;
    
    // TODO _AXC _VERIFY(Mybody == nullprt, "Mybody is nullprt!!!")
    const _st::Point& getPosition() const noexcept {
        return Mybody->Position;
    }

    float getRotation() const noexcept {
        return Mybody->Rotation;
    }

    const _st::Gvector& getVelocity() const noexcept {
        return Mybody->Velocity;
    } 

    float getAngularVelocity() const noexcept {
        return Mybody->AngularVelocity;
    }

    const _st::Gvector& getSize() const noexcept {
        return Mybody->Size;
    }  
    
    float getMass() const noexcept {
        return Mybody->Mass;
    }
    
    float getInvMass() const noexcept {
        return Mybody->InvMass;
    }

    float getInertiaTensor() const noexcept {
        return Mybody->InertiaTensor;
    }

    float getInvI() const noexcept {
        return Mybody->InvI;
    }
    
    float getFriction() const noexcept {
        return Mybody->Friction;
    }

    const _st::Gvector& getForce() const noexcept {
        return Mybody->Force;
    }

    float getTorque() const noexcept {
        return Mybody->Torque;
    }



public:
    RigidBody* Mybody;
};


#endif // ISHELL_H
