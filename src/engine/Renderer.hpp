#ifndef RENDERER_H
#define RENDERER_H


#include "Arbiter.hpp"


class Renderer {
public:

    explicit Renderer(sf::RenderTarget& target) : _Target(target) {}

    void render(const Arbiter& Arbiter) const {
        const std::vector<float> Constraint = Arbiter.getConstraint();
        sf::CircleShape ConstraintBackground { Constraint[2] };

        ConstraintBackground.setOrigin(Constraint[2], Constraint[2]);
        ConstraintBackground.setFillColor(sf::Color::Black);
        ConstraintBackground.setPosition(Constraint[0], Constraint[1]);
        ConstraintBackground.setPointCount(128);
        _Target.draw(ConstraintBackground);

        sf::CircleShape ObjectCircle {1.0f};
        ObjectCircle.setPointCount(32);
        ObjectCircle.setOrigin(1.0f, 1.0f);
        const auto& ObjectsVector = Arbiter.getObjects();

        for (const Verlet& object : ObjectsVector) {
            ObjectCircle.setPosition(object.posNow.Xcoord, object.posNow.Ycoord);
            ObjectCircle.setScale(object.radius, object.radius);
            ObjectCircle.setFillColor(object.color);
            _Target.draw(ObjectCircle);
        }
    }


private:
    sf::RenderTarget& _Target;
};

#endif // RENDERER_H
