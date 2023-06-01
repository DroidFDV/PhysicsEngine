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
    
    Verlet (const sf::Vector2f& _position, float _radius) noexcept : 
        posNow(_position),
        posPrev(_position),
        radius(_radius),
        acceleration(0.0f, 0.0f)
    {}

    void updatePosition (float dt) {
        const sf::Vector2f shift = posNow - posPrev;
        posPrev = posNow;
        posNow = posNow + shift + acceleration * dt * dt;
        acceleration = {};
    }

    void accelerate (const sf::Vector2f& acc) {
        acceleration += acc;
    }

    // ??
    void setVelocity (const sf::Vector2f& velocity, float dt) noexcept {
        posPrev = posNow - (velocity * dt);
    }

    // ??
    void addVelocity (const sf::Vector2f& velocity, float dt) noexcept {
        posPrev -= velocity * dt;
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
