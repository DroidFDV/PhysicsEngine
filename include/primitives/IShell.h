#ifndef ISHELL_H
#define ISHELL_H


#include "../rigidbody/RigidBody.h"


class IShell {
public:
    
    IShell (RigidBody* body) noexcept : Mybody(body) {}
    
    virtual ~IShell() = 0;
    
public:
    RigidBody* Mybody;
};


#endif // ISHELL_H
