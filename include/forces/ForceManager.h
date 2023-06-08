#ifndef FMANAGER_H
#define FMANAGER_H


#include "IForceGenerator.h"
#include "ForceManagerProxy.hpp"
#include <vector>
#include <algorithm>
// #include <map>


class ForceManager {
public:
   
    using fmp = ForceManagerProxy;


    ForceManager() = default;
    
    ~ForceManager() {
        this->clean();    
    }

    void add (IForceGenerator* fgen, RigidBody* body) {
        fmp* proxy = new fmp(fgen, body);
        Registry.push_back(proxy);
    }

    // TODO create way to use std::map 
    // TODO OPTIMIZE!!
    void remove (IForceGenerator* fgen, RigidBody* body) {
        for (int i = 0; i < Registry.size(); i++) {
            if (Registry[i]->Mygen == fgen && Registry[i]->Mybody == body) {
                fmp* _proxy = Registry[i];
                Registry.erase(std::next(Registry.begin(),i));
                delete _proxy;
                break;
            }
        }
    }

    void clean() {
        while (Registry.size() > 0) {
            fmp* _proxy = Registry[0];
            Registry.erase(Registry.begin());
            delete _proxy;
        }
    }

    void updateAllForces (float dt) {
        for (fmp* proxy : Registry) {
            proxy->Mygen->updateForce(proxy->Mybody, dt);
        }
    }

  

    std::vector<fmp*> Registry;
    // std::map<RigidBody*, std::vector<IForceGenerator*>> Registry;
};


#endif // FMANAGER_H
