// 

#ifndef JOINT_H
#define JOINT_H

#include "FlatMathUtils.hpp"


struct Body;

struct Joint {

    Joint() : 
        body1(0),
        body2(0),
        P(0.0f, 0.0f),
        biasFactor(0.2f),
        softness(0.0f)
    {}

    void set (Body* _Body1, Body* _Body2, const _math::gvector _Anchor);

    void preStep (float _invDist);

    void applyImpulse();


        
    _math::sq_matrix M;
   
    _math::gvector localAnchor1, localAnchor2;
   
    _math::gvector r1, r2;
   
    _math::gvector bias;
    float          biasFactor;
    float          softness;
   
    _math::gvector P; // accumulated impulse 
    
    Body* body1;
    Body* body2;
};

#endif // 
