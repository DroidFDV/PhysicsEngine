// 

#ifndef ARBITER_H
#define ARBITER_H

#include "FlatMathUtils.hpp"


struct Body;

union FeaturePair
{
    struct Edges {
        
        char inEdge1;
        char inEdge2;
        char outEdge1;
        char outEdge2;
    } e;
    
    int value;
};

struct Contact {

    Contact() : Pn(0.0f), Pt(0.0f), Pnb(0.0f) {}


    _math::gvector position;
    _math::gvector vecNormal;
    _math::gvector r1, r2;

    float separation;
    float Pn;  // accumulated normal impulse
    float Pt;  // accumulated tanget impulse
    float Pnb; // accumulated normal impulse for position bias

    float massNormal, massTangent;
    float bias;
    FeaturePair feature;
};

struct ArbiterKey {

    ArbiterKey (Body* B1, Body* B2) {
        // if (B1 < B2) {
        //
        // }
        B1 < B2 ? body1 = B1, body2 = B2 : body1 = B2, body2 = B1;
    }

    Body* body1;
    Body* body2;
};

struct Arbiter {
    // TODO: does I really need this?
    enum { MAX_POINTS = 2 };

    Arbiter  (Body* B1, Body* B2);

    void update (Contact* contacts, int numContacts);

    void preStep (float _intDist);

    void applyImpulse();


    Contact contacts[MAX_POINTS];
    int numContacts;
    
    Body* body1;
    Body* body2;

    float friction; // combined friction
};

// for std::set
inline bool operator< (const ArbiterKey& Ak1, const ArbiterKey& Ak2) {
    if (Ak1.body1 < Ak2.body1) { return true; }
    if ( Ak1.body1 == Ak2.body1 && Ak1.body2 < Ak2.body2 ) { return true; }

    return false;
}

int Collide (Contact* contacts, Body* body1, Body* body2);

#endif
