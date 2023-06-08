#ifndef RENDER_H
#define RENDER_H


#include <SFML/Graphics.hpp>
#include "World.h"
#include "../structures/Gvector.hpp"
#include "../primitives/Circle.hpp"
#include "../primitives/AABB.hpp"
#include "../primitives/OBB.hpp"

////////////////////////////////////////////////////////////
/// \brief Class to draw objects in window
////////////////////////////////////////////////////////////
class Render {
public:
    
    ////////////////////////////////////////////////////////////
    /// \brief Construct Render to draw a target
    ///
    /// \param Target to draw
    ///
    ////////////////////////////////////////////////////////////
    explicit Render (sf::RenderTarget& target) : _Target(target) {}

    ////////////////////////////////////////////////////////////
    /// \brief Main function of Render - draw a worlds in window
    ///
    /// \param world A world that should be drown
    ////////////////////////////////////////////////////////////
    void render (const World& world) const;



private:
 
    ////////////////////////////////////////////////////////////
    /// \brief Function to draw shells
    ///
    /// \param vecShells Vector of all shells in the world
    ////////////////////////////////////////////////////////////
    void renderShells (const std::vector<IShell*> vecShells) const;
   
    ////////////////////////////////////////////////////////////
    /// \brief Function to draw just one shell from the world
    ///
    /// \param shell Shell to draw
    /// \param color Color of sheel
    ////////////////////////////////////////////////////////////
    void renderObject (IShell* shell, sf::Color color) const;

    ////////////////////////////////////////////////////////////
    /// \brief Specialization where shell is Circle
    ///
    /// \param circle Circle to draw
    /// \param color Color of circle
    ////////////////////////////////////////////////////////////
    void renderObject (const Circle& circle, sf::Color color) const;

    ////////////////////////////////////////////////////////////
    /// \brief Specialization where shell is AABB
    ///
    /// \param box AABB to draw
    /// \param color Color of circle
    ////////////////////////////////////////////////////////////
    void renderObject (const AABB& box, sf::Color color) const;

    ////////////////////////////////////////////////////////////
    /// \brief Specialization where shell is OBB
    ///
    /// \param box OBB to draw
    /// \param color Color of circle
    ////////////////////////////////////////////////////////////
    void renderObject (const OBB& box, sf::Color color) const;


    
    ////////////////////////////////////////////////////////////
    /// Member data
    ////////////////////////////////////////////////////////////
    sf::RenderTarget& _Target;
};


#endif // RENDER_H
