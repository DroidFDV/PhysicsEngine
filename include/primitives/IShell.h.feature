#ifndef ISHELL_H
#define ISHELL_H


#include "../rigidbody/RigidBody.h"


class IShell;
class RigidBody;


struct IShellProxy {

    IShellProxy() noexcept = default;

    IShellProxy (IShell* shell, RigidBody* body) noexcept :
        Myshell(shell),
        Mybody(body)
    {}



    const IShell*    Myshell;
    const RigidBody* Mybody;
};


struct IShell {
public:
    
    IShell (RigidBody* body) noexcept :
        Myproxy(this, body)
    {}
    
    virtual ~IShell() = 0;
    
public:
    const IShellProxy* Myproxy;   
    // RigidBody* Mybody;
};


#endif // ISHELL_H
