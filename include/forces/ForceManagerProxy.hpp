#ifndef FORCEPROXY_H
#define FORCEPROXY_H


class  IForceGenerator;
struct RigidBody;


struct ForceManagerProxy {
    
    ForceManagerProxy (IForceGenerator* fgen, RigidBody* body) noexcept :
        Mygen(fgen),
        Mybody(body)
    {}

    bool operator== (ForceManagerProxy* otherProxy) {
        return this->Mygen == otherProxy->Mygen && this->Mybody == otherProxy->Mybody;
    }



    IForceGenerator* Mygen;
    RigidBody*       Mybody;
};


// inline bool operator== (const ForceManagerProxy& _Lhs, const ForceManagerProxy& _Rhs) {
//         return _Lhs.Mygen == _Rhs.Mygen && _Lhs.Mybody == _Rhs.Mybody;
// }


#endif // FORCEPROXY_H
