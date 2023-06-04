#ifndef WORLD_H
#define WORLD_H


#include <vector>
#include <map>
#include "../Math.hpp"
#include "../rigidbody/Manager.h"


struct RigidBody;


struct World {

    World (_st::Gvector gravity, int iterations) noexcept :
        WorldGravity(gravity),
        Iterations(iterations)
    {}
   
    void addObject (IShell* object);

    void clear();

    void step (float dt);

    void broadPhase();
    
    std::vector<IShell*> vecObjects;
    std::map<ManagerKey, Manager> mapManagers;
    _st::Gvector WorldGravity; 
    int          Iterations;
    static bool  accImpulses;
    static bool  warmStarting;
    static bool  posCorrection;
};


#endif // WORLD_H
