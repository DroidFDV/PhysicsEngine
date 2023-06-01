// simple class presenting an object


#ifndef VERLET_H
#define VERLET_H 

#ifndef __has_cpp_attribute
#define __has_cpp_attribute(name) 0
#endif

#include <cmath>
#include <SFML/Graphics.hpp>
#include "../Math.hpp"
#include "../structures/Gvector.hpp"
#include "../structures/Point.hpp"

using namespace _math;
using namespace st;
struct Verlet {

    Verlet() = default;
    
    Verlet (const Gvector& _position, float _radius) noexcept : 
        posNow(_position),
        posPrev(_position),
        radius(_radius),
        acceleration(0.0f, 0.0f)
    {}

    void updatePosition (float dt) {
        const Gvector shift = posNow - posPrev;
        posPrev = posNow;
        posNow = posNow + shift + acceleration * dt * dt;
        acceleration = {};
    }

    void accelerate (const Gvector& acc) {
        acceleration += acc;
    }

    // ??
    void setVelocity (const Gvector& velocity, float dt) noexcept {
        posPrev = posNow - (velocity * dt);
    }

    // ??
    void addVelocity (const Gvector& velocity, float dt) noexcept {
        posPrev -= velocity * dt;
    }

    [[nodiscard]] Gvector getVelocity (float dt) const {
        return Gvector( (posNow - posPrev) * (1 / dt) );

    }

    Point   posNow;
    Point   posPrev;
    Gvector acceleration;
    float   radius = 10.0f;
    sf::Color color = sf::Color::Black; 
};

#endif // VERLET_H
