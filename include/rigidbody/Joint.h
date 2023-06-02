//

#ifndef JOINT_H
#define JOINT_H


#include "../Math.hpp"
#include "../primitives/AABB.hpp"
#include "../primitives/Circle.hpp"
#include "../primitives/OBB.hpp"


using namespace _math;

struct RigidBody;

struct Joint;

struct CollisionDetector {
    
    // ===========================================
    // Point vs. Primitives
    // ===========================================
    
    bool PointLine (const Point& point, const Line& line) const;

    bool PointCircle (const Point& point, const Circle& circle) const;

    bool PointAABB (const Point& point, const AABB& Box) const;

    bool PointOOB (const Point& point, const OBB& Box) const;
    
    // ===========================================
    // Line vs. Primitives
    // ===========================================



    // ===========================================
    // Primitives vs. Primitives
    // ===========================================

};


#endif 
