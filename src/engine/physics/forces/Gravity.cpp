#include "../../../../include/forces/Gravity.h"


Gravity::Gravity (_st::Gvector worldGravity) noexcept :
    LocalGravity(worldGravity)
{}

void Gravity::updateForce (RigidBody* body, float dt) const {
    body->addForce(LocalGravity);
}
