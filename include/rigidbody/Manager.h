#ifndef ARBITER_H
#define ARBITER_H


#include "../Math.hpp"
#include "../structures/Gvector.hpp"
#include "../structures/Point.hpp"
#include "../primitives/IShell.h"


using namespace _math;
using namespace _st;


// struct RigidBody;


union FeaturePair {
    
    struct Edges {
        char inEdge1;
        char outEdge1;
        char inEdge2;
        char outEdge2;
    } e;

    int value;
};


struct Contact {

    Contact() noexcept :
        accNormalImpulse(0.0f),
        accTangentImpulse(0.0f), 
        accNormalImpulseBias(0.0f)
    {}



    Gvector     ContactPos;
    Gvector     Normal;
    Point       r1, r2;
    float       Separation;
    float       accNormalImpulse;        // Pn
    float       accTangentImpulse;       // Pt
    float       accNormalImpulseBias;    // Pnb
    float       MassNormal, MassTangent;
    float       Bias;
    FeaturePair Feature;
};


struct ManagerKey {
    
    ManagerKey (IShell* shellA, IShell* shellB) {
        shellA->getMass() < shellB->getMass() ? 
            smallShell = shellA, bigShell = shellB :
            smallShell = shellB, bigShell = shellA; 
    }



    IShell* smallShell; // has smaller mass
    IShell* bigShell; // has bigger mass
};


struct Manager {

    enum {MAX_POINTS = 2};

    Manager (IShell* shellA, IShell* shellB) noexcept;

    void update (Contact* contacts, int numContacts);

    void preStep (float invDt);

    void applyImpulse();

    

    // TODO std::vector<Contact> vecContacts;
    Contact arrContacts[MAX_POINTS];
    int     numContacts; 

    IShell* smallShell;
    IShell* bigShell;

    float friction; // combined friction
};


inline bool operator< (const ManagerKey& _Lhs, const ManagerKey& _Rhs) {
    if (_Lhs.smallShell->getMass() < _Rhs.smallShell->getMass()) { return true; }
    if (
        _Lhs.smallShell->getMass() == _Rhs.smallShell->getMass() &&
        _Lhs.bigShell->getMass() < _Rhs.bigShell->getMass()
    ) { return true; }
    
    return false;
}


int Collide (Contact* _contact, IShell* shellA, IShell* shellB);


#endif // ARBITER_H
