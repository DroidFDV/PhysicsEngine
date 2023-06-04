#ifndef GRAVITY_H
#define GRAVITY_H


#include "IForceGenerator.h"
#include "../structures/Gvector.hpp"


class Gravity : public IForceGenerator {
    
    Gravity (_st::Gvector worldGravity) noexcept;
   
    virtual void updateForce (RigidBody* body, float dt) const override;



    _st::Gvector LocalGravity;
};

#endif // GRAVITY_H
