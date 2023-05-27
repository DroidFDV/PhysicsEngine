// simple class presenting an object


#ifndef VERLET_H
#define VERLET_H 

#ifndef __has_cpp_attribute
#define __has_cpp_attribute(name) 0
#endif

#include <cmath>
#include <SFML/Graphics.hpp>
#include "../Math.hpp"


using namespace _math;

struct Verlet {

    Verlet() = default;
    
    // ??
    Verlet (Gvector _Position, float _Radius) noexcept : 
        posNow(_Position),
        posPrev(_Position),
        radius(_Radius),
        acceleration(0.0f, 0.0f)
    {}

    void updatePosition (float dt) {
        const Gvector shift = posNow - posPrev;
        posPrev = posNow;
        posNow = posNow + shift + acceleration * dt * dt;
        acceleration = {};
    }

    void accelerate (Gvector acc) {
        acceleration += acc;
    }

    // ??
    void setVelocity (Gvector _Velocity, float dt) noexcept {
        posPrev = posNow - (_Velocity * dt);
    }

    // ??
    void addVelocity (Gvector _Velocity, float dt) noexcept {
        posPrev -= _Velocity * dt;
    }

    [[nodiscard]] Gvector getVelocity (float dt) const {
        return Gvector( (posNow - posPrev) * (1 / dt) );

    }

    Point posNow;
    Point posPrev;
    Gvector acceleration;
    float radius = 10.0f;
    sf::Color color = sf::Color::Black; 
};

#endif // VERLET_H
