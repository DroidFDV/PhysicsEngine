#ifndef COLLISIONDET_H
#define COLLISIONDET_H


#include "../Math.hpp"
#include "../structures/Point.hpp"
#include "../structures/Line.hpp"
#include "../primitives/Circle.hpp"
#include "../primitives/AABB.hpp"
#include "../primitives/OBB.hpp"


struct IsCollision {
   
    // ===========================================
    // Point vs. Primitives
    // ===========================================
 
    bool pointLine (const Point& point, const Line& line) const noexcept {
        float dx = line.end.Xcoord - line.begin.Xcoord; 
        float dy = line.end.Ycoord - line.begin.Ycoord;

        float k = dy / dx;
        float b = line.end.Ycoord - k * line.end.Xcoord;

        // now we have an equation of line: y = kx + b
        return AlmostEqual(point.Ycoord, k * point.Xcoord + b);
    } 


    bool pointCircle (const Point& point, const Circle& circle) const noexcept {
        Gvector circleCenter = circle.Mybody->Position;
        Gvector dirVec = point - circleCenter;
        float distance2 = dot(dirVec, dirVec);
        return (circle.Radius * circle.Radius  >= distance2);
    }


    // bool pointAABB (const Point& point, const AABB& box) const noexcept {}
    //
    // bool pointOBB (const Point& point, const OBB& box) const noexcept {}
   

    // ===========================================
    // Line vs. Primitives
    // ===========================================
 
    // bool lineCircle (const Line& line, const Circle& circle) const noexcept {}
    // 
    // bool lineAABB (const Line& line, const AABB& box) const noexcept {}
    //
    // bool lineOBB (const Line& line, const OBB& box) const noexcept {}

    bool CircleCircle (const Circle& circleA, const Circle& circleB) const noexcept {
        Point CircleACenter = circleA.Mybody->Position;
        Point CircleBCenter = circleB.Mybody->Position;
        float distance2 = dot(CircleBCenter - CircleACenter, CircleBCenter - CircleACenter); 
        return (
        ( (circleA.Radius + circleB.Radius) * (circleA.Radius + circleB.Radius) ) >= distance2
        );
    }


    // ===========================================
    // Point vs. Primitives
    // ===========================================
 
    // bool CircleAABB (const Circle& circle, const AABB& box) const noexcept {}
    //
    // bool CircleOBB (const Circle& circle, const OBB& box) const noexcept {}
    //
    // bool AABBAABB (const AABB& boxA, const AABB& boxB) const noexcept {}
    //
    // bool AABBOBB (const AABB& rgBox, const OBB& rotBox) const noexcept {}
    //
    // bool OBBOBB (const OBB& boxA, const OBB& boxB) const noexcept {}
};


#endif // COLLISIONDET_H
