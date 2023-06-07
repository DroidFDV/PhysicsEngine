#include <iostream>
#include "../include/render/Window.hpp"
// #include "../include/rigidbody/RigidBody.h"
// #include "../include/primitives/IShell.h"


int main()
{
    // Create window
    window_traits wTraits;
    
    sf::RenderWindow Window (
        sf::VideoMode(wTraits.width, wTraits.height), 
        wTraits.name,
        wTraits.style
    );

    Window.setFramerateLimit(wTraits.frameRateLimit);
  


    // Set simulation attributes
    // static const float object_spawn_delay = 0.025f;
    // static const float object_spawn_speed = 100.0f;
    // static const _st::Gvector object_spawn_position = { 0.0f, 0.0f };
   


    // Main loop
    sf::Clock Clock;
    
    while (Window.isOpen()) 
    {
        sf::Event event{};
        while (Window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) 
            {
                Window.close();
            }
        }



        // future main code
        // ...
        // ...
        // update all positions



        Window.clear(wTraits.backgroundColor);

        // Render all objects 
        
        Window.display();
    }

    return 0;
}
