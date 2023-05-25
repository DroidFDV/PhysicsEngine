// 

#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <map>
#include "FlatMathUtils.hpp"
#include "Arbiter.h"


struct Body;
struct Joint;

struct World {

    World (_math::gvector _Gravity, int _Iterations) :
        gravity(_Gravity),
        iterations(_Iterations)
    {}

    void add (Body* _Body);
    void add (Joint* _Joint);
    void _CLEAR();

    void step (float _Distance);

    void broadPhase();

    std::vector<Body*>  bodies;
    std::vector<Joint*> joints;
    std::map<ArbiterKey, Arbiter> arbiters;
    
    _math::gvector gravity;
    int iterations;

    static bool accumulateImpulses;
    static bool warmStarting;
    static bool positionCorrection;

};

#endif
