//

#include "Body.h"

Body::Body() { 
    width.set(1.0f, 1.0f);

    position.set(0.0f, 0.0f);
    rotation = 0.0f;

    velocity.set(0.0f, 0.0f);
    angularVelocity = 0.0f;

    force.set(0.0f, 0.0f);
    torque = 0.0f;

    friction = 0.2f; // WHY 0.2f?
    mass     = FLT_MAX;
    invMass  = 0.0f;
    I        = FLT_MAX;
    invI     = 0.0f;
}

void Body::set (const _math::gvector& _Width, float _Mass) noexcept {
    width = _Width;

    position.set(0.0f, 0.0f);
    rotation = 0.0f;

    velocity.set(0.0f, 0.0f);
    angularVelocity = 0.0f;

    force.set(0.0f, 0.0f);
    torque = 0.0f;

    friction = 0.2f; // WHY 0.2f?
    mass = _Mass;

    if (mass < FLT_MAX) {
        invMass = 1.0f / mass;
        I       = mass * (
                    width.Xcoord * width.Xcoord +
                    width.Ycoord * width.Ycoord
                    ) / 12.0f;
        invI    = 1.0f / I;
    }
    else {
        invMass = 0.0f;
        I       = FLT_MAX;
        invI    = 0.0f;
    }
}

void Body::addForce (const _math::gvector& _Force) noexcept {
    force += _Force;
}
