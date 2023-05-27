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
    Verlet (sf::Vector2f _Position, float _Radius) noexcept : 
        posNow(_Position),
        posPrev(_Position),
        radius(_Radius),
        acceleration(0.0f, 0.0f)
    {}

    void updatePosition (float dt) {
        const sf::Vector2f shift = posNow - posPrev;
        posPrev = posNow;
        posNow = posNow + shift + acceleration * dt * dt;
        acceleration = {};
    }

    void accelerate (sf::Vector2f acc) {
        acceleration += acc;
    }

    // ??
    void setVelocity (sf::Vector2f _Velocity, float dt) noexcept {
        posPrev = posNow - (_Velocity * dt);
    }

    // ??
    void addVelocity (sf::Vector2f _Velocity, float dt) noexcept {
        posPrev -= _Velocity * dt;
    }

    [[nodiscard]] sf::Vector2f getVelocity (float dt) const {
        return sf::Vector2f( (posNow - posPrev) * (1 / dt) );

    }

    sf::Vector2f posNow;
    sf::Vector2f posPrev;
    sf::Vector2f acceleration;
    float radius = 10.0f;
    sf::Color color = sf::Color::Black; 
};

#endif // VERLET_H
