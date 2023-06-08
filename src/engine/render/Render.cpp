#include "../../../include/render/Render.h"


void Render::render (const World& world) const {
    renderShells(world.vecObjects);
}


// TODO this should be optimize, i shoudn't create a ...Shape every time
//      in function, instead i need to pass this ...Shape as a parametr
//      in function, in function i need change it's size, color, radius.
//      So, use just 1 ...Shape for every type of shells;
void Render::renderShells (const std::vector<IShell*> vecShells) const {
    for (auto* shell : vecShells) {
        return renderObject(shell, sf::Color::Blue);
    }
}


void Render::renderObject (IShell* shell, sf::Color color) const {}


void Render::renderObject (const Circle& circle, sf::Color color) const {
    sf::CircleShape CircleS(circle.getRadius());
    CircleS.setOrigin(circle.getRadius(), circle.getRadius());
    CircleS.setFillColor(color);
    CircleS.setPosition(circle.getPosition());
    CircleS.setPointCount(128);

    _Target.draw(CircleS);
}


void Render::renderObject (const AABB& box, sf::Color color) const {
    sf::RectangleShape BoxS(box.getSize());
    BoxS.setFillColor(color);
    BoxS.setPosition(box.getPosition());
    
    _Target.draw(BoxS);
}


void Render::renderObject (const OBB& box, sf::Color color) const {
    sf::RectangleShape BoxS(box.getSize());
    BoxS.setFillColor(color);
    BoxS.setPosition(box.getPosition());
    BoxS.setRotation(box.getRotation());

    _Target.draw(BoxS);
}

