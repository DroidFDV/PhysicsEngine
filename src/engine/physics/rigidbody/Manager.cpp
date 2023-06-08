#include "../../../../include/rigidbody/Manager.h"
#include "../../../../include/rigidbody/RigidBody.h"
#include "../../../../include/render/World.h"


Manager::Manager (IShell* shellA, IShell* shellB) noexcept {
    if (shellA->getMass() > shellB->getMass()) {
        smallShell = shellB;
        bigShell   = shellA;
    } else {
        smallShell = shellA;
        bigShell   = shellB;
    }

    numContacts = Collide(arrContacts, smallShell, bigShell);
    friction = sqrtf(shellA->getFriction() * shellB->getFriction());
}

void Manager::update (Contact* newContacts, int numNewContacts) {
    Contact mergeContacts[2];

    for (int i = 0; i < numNewContacts; i++) {
        Contact* newCont = newContacts + i; // newCont = newContacts[i]
        int k = -1;

        for (int j = 0; j < numContacts; j++) {
            Contact* oldCont = arrContacts + j; // oldCont = arrContacts[j]

            if (newCont->Feature.value == oldCont->Feature.value) {
                k = j;
                break;
            }
        }

        if (k > -1) { 
            Contact* cont = mergeContacts + i;
            Contact* oldCont = arrContacts + k;

            *cont = *newCont;

            if (World::warmStarting) {
                cont->accNormalImpulse = oldCont->accNormalImpulse;
                cont->accTangentImpulse = oldCont->accTangentImpulse;
                cont->accNormalImpulseBias = oldCont->accNormalImpulseBias;
            } else {
                cont->accNormalImpulse = 0.0f;
                cont->accTangentImpulse = 0.0f;
                cont->accNormalImpulseBias = 0.0f;
            }
        } else { // there is a newCont not equal one of oldContacts
            mergeContacts[i] = newContacts[i];
        }
    }

    for (int i = 0; i < numNewContacts; i++) {
        arrContacts[i] = mergeContacts[i];
    }

    numContacts = numNewContacts;
}

void Manager::preStep (float invDt) {
    const float ALLOWED_PENETR = 0.01f;
    float BIAS_FACTOR = World::posCorrection ? 0.2f : 0.0f;

    for (int i = 0; i < numContacts; i++) {
        Contact* cont = arrContacts + i;

        _st::Gvector r1 = cont->ContactPos - smallShell->getPosition();
        _st::Gvector r2 = cont->ContactPos - bigShell->getPosition();

        // Precompute normal mass, tangent mass, bias 
        float rn1 = dot(r1, cont->Normal);
        float rn2 = dot(r2, cont->Normal);
        float kNormal = smallShell->getInvMass() + bigShell->getInvMass();
        kNormal += smallShell->getInvI() * (dot(r1, r1) - rn1 * rn1) +
            bigShell->getInvI() * (dot(r2,r2) - rn2 * rn2);
        cont->MassNormal = 1.0f / kNormal;
        
        _st::Gvector Tangent = cross(cont->Normal, 1.0f);
        float rt1 = dot(r1, Tangent);
        float rt2 = dot(r2, Tangent);
        float kTangent = smallShell->getInvMass() + bigShell->getInvMass();
        kNormal += smallShell->getInvI() * (dot(r1, r1) - rt1 * rt1) +
            bigShell->getInvI() * (dot(r2,r2) - rt2 * rt2);
        cont->MassTangent = 1.0f / kTangent;

        cont->Bias = -BIAS_FACTOR * invDt * _math::min(0.0f, cont->Separation + ALLOWED_PENETR);

        if (World::accImpulses) {
            // Apply normal + friction inmpulse
            _st::Gvector f = cont->accNormalImpulse * cont->Normal + 
                                cont->accTangentImpulse * Tangent;
            
            smallShell->Mybody->Velocity -= smallShell->getInvMass() * f;
            smallShell->Mybody->AngularVelocity -= smallShell->getInvI() * cross(r1, f);

            bigShell->Mybody->Velocity += bigShell->getInvMass() * f;
            bigShell->Mybody->AngularVelocity += bigShell->getInvI() * cross(r2, f);
        }
    }
}

void Manager::applyImpulse() {
    RigidBody* b1 = smallShell->Mybody;
    RigidBody* b2 = bigShell->Mybody;

    for (int i = 0; i < numContacts; i++) {
        Contact* cont = arrContacts + i;
        cont->r1 = cont->ContactPos - b1->Position;
        cont->r2 = cont->ContactPos - b2->Position;

        // Relative velocity at contact 
        _st::Gvector dv = b2->Velocity + cross(b2->AngularVelocity, cont->r2) - 
                            b1->Velocity - cross(b1->AngularVelocity, cont->r1);

        // Compute normal impulse 
        float vn = dot(dv, cont->Normal);

        float dPn = cont->MassNormal * (-vn + cont->Bias);

        if (World::accImpulses) {
            // Clamp the acc implulse
            float Pn0 = cont->accNormalImpulse;
            cont->accNormalImpulse = _math::max(Pn0 + dPn, 0.0f);
            dPn = cont->accNormalImpulse - Pn0;
        } else {
            dPn = _math::max(dPn, 0.0f);
        }

        // Apply contact impulse 
        _st::Gvector Pn = dPn * cont->Normal;

        b1->Velocity -= b1->InvMass * Pn;
        b1->AngularVelocity -= b1->InvI * cross(cont->r1, Pn);

        b2->Velocity -= b2->InvMass * Pn;
        b2->AngularVelocity += b2->InvI * cross(cont->r2, Pn);

        // Relative velocity at contact 
        dv = b2->Velocity + cross(b2->AngularVelocity, cont->r2) -
                b1->Velocity -
                cross(b1->AngularVelocity, cont->r2);

        _st::Gvector tangent = cross(cont->Normal, 1.0f);
        float vt = dot(dv, tangent);
        float dPt = cont->MassTangent * (-vt);

        if (World::accImpulses) { 
            // Compute fricton impulse 
            float maxPt = friction * cont->accNormalImpulse;
            
            // Clamp friction 
            float oldTangentImpulse = cont->accTangentImpulse;
            cont->accTangentImpulse = clamp(oldTangentImpulse + dPt, -maxPt, maxPt);
            dPt = cont->accTangentImpulse = cont->accTangentImpulse - oldTangentImpulse;
        } else {
            float maxPt = friction * dPn;
            dPt = clamp(dPt, -maxPt, maxPt);
        }

        // Aplly contact impulse 
        _st::Gvector Pt = dPt * tangent;

        b1->Velocity -= b1->InvMass * Pt;
        b1->AngularVelocity -= b1->InvI * cross(cont->r1, Pt);

        b2->Velocity += b2->InvMass * Pt;
        b2->AngularVelocity += b2->InvI * cross(cont->r2, Pt);
    }
}

