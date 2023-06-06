#include "../../../include/render/World.h"
#include "../../../include/rigidbody/RigidBody.h"


// using std::vector;
// using std::map;
// using std::pair;


using mgIter = std::map<ManagerKey, Manager>::iterator;
using mgPair = std::pair<ManagerKey, Manager>;


bool World::accImpulses   = true;
bool World::warmStarting  = true;
bool World::posCorrection = true;


IShell* World::addObject (IShell* object) {
    vecObjects.push_back(object);
    return vecObjects.back();
}

void World::clear() {
    mapManagers.clear();
    vecObjects.clear();
}

// TODO OPTIMIZE!!!
void World::broadPhase() {
    for (size_t i = 0; i < vecObjects.size(); i++) {
        IShell* oi = vecObjects[i];

        for (size_t j = i + 1; j < vecObjects.size(); j++) {
            IShell* oj = vecObjects[j];

            if (oi->getInvI() == 0.0f && oj->getInvI() == 0.0f) {
                continue; // oi & oj are both constraints
            }
    
            Manager mg(oi, oj);
            ManagerKey key(oi, oj);

            if (mg.numContacts > 0) {
                mgIter itt = mapManagers.find(key);
                
                if (itt == mapManagers.end()) {
                    mapManagers.insert(mgPair(key, mg));
                } else {
                    itt->second.update(mg.arrContacts, mg.numContacts); 
                }
            } else {
                mapManagers.erase(key); // TODO mb erase(key) for all cases?
            }
        }
    }
}

void World::step (float dt) {
    float invDt = dt > 0 ? 1.0f / dt : 0.0f;

    // Determine overlapping primitives and update contact points
    this->broadPhase();
    
    // Integrate forces
    for (size_t i = 0; i < vecObjects.size(); i++) {
        IShell* shell = vecObjects[i];

        if (shell->getInvMass() == 0.0f) { continue; }

        shell->Mybody->Velocity += dt * (WorldGravity + shell->getInvI() * shell->getForce());
        shell->Mybody->AngularVelocity += dt * shell->getInvI() * shell->getTorque();
    }

    // Perform pre-steps
    for (mgIter itt = mapManagers.begin(); itt != mapManagers.end(); itt++) {
        itt->second.preStep(invDt);
    }

    // Perform iterations
    for (int i = 0; i < Iterations; i++) {
        for (mgIter itt = mapManagers.begin(); itt != mapManagers.end(); itt++) {
            itt->second.applyImpulse();
        }
    }

    // Integrate velocities
    for (size_t i = 0; i < vecObjects.size(); i++) {
        IShell* shell = vecObjects[i];

        shell->Mybody->Position += dt * shell->getVelocity();
        shell->Mybody->Rotation += dt * shell->getAngularVelocity();
        
        shell->Mybody->Force.set(0.0f, 0.0f);
        shell->Mybody->Torque = 0.0f; // TODO why i zero torque?
    }
}





