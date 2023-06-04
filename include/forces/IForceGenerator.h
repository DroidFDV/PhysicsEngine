#ifndef IFORCE_GEN_H
#define IFORCE_GEN_H


struct RigidBody;


class IForceGenerator {
public:

    virtual void updateForce(RigidBody* body, float dt) const = 0;
};


#endif // IFORCE_GEN_H
