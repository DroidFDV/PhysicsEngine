#ifndef RENDER_H
#define RENDER_H


#include <SFML/Graphics.hpp>
#include "World.h"
#include "../structures/Gvector.hpp"
#include "../primitives/Circle.hpp"
#include "../primitives/AABB.hpp"
#include "../primitives/OBB.hpp"

class Render {
public:
    
    explicit Render (sf::RenderTarget& target) : _Target(target) {}

    void render (const World& world) const;



private:
 
    void renderShells (const std::vector<IShell*> vecShells) const;
   
    void renderObject (IShell*, sf::Color color) const;

    void renderObject (const Circle& circle, sf::Color color) const;

    void renderObject (const AABB& box, sf::Color color) const;

    void renderObject (const OBB& box, sf::Color color) const;



    sf::RenderTarget& _Target;
};


#endif // RENDER_H
