#include <iostream>
#include "engine/Renderer.hpp"



int main()
{
    // Create window 
    constexpr int32_t Window_Width  = 1000;
    constexpr int32_t Window_Height = 1000;

    sf::ContextSettings Settings;
    Settings.antialiasingLevel = 1;
    sf::RenderWindow Window(sf::VideoMode(Window_Width, Window_Height), "alpha version", sf::Style::Default, Settings);
    const uint32_t FrameRate = 60;
    Window.setFramerateLimit(FrameRate);

    Arbiter Arbiter;
    Renderer Renderer {Window};

    // Arbiter configuration
    Arbiter.setConstraint( {static_cast<float>(Window_Width) * 0.6f, static_cast<float>(Window_Height) * 0.6f}, 450.0f);
    Arbiter.setSubStepsCount(8);
    Arbiter.setSimulationUpdateRate(FrameRate);

    // Set simulation attributes
    const float          object_spawn_delay    = 0.025f;
    const float          object_spawn_speed    = 1200.0f;
    const _math::Gvector object_spawn_position = {500.0f, 200.0f};
    const float          object_min_radius     = 1.0f;
    const float          object_max_radius     = 20.0f;
    const uint32_t       max_objects_count     = 1000;
    const float          max_angle             = 1.0f;

    sf::Clock clock;

    // Main loop
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

        if (Arbiter.getObjectsCount() < max_objects_count && clock.getElapsedTime().asSeconds() >= object_spawn_delay)
        {
            clock.restart();
            auto& object      = Arbiter.addObject(object_spawn_position, _math::random(object_min_radius, object_max_radius));
            const float t     = Arbiter.getTime();
            const float angle = max_angle * sinf(t) + _math::PI * 0.5f;
            Arbiter.setObjectVelecity( object, object_spawn_speed * _math::Gvector{cosf(angle), sinf(angle)} );
            object.color = sf::Color::Green;
        }

        Arbiter.update();
        Window.clear(sf::Color::White);
        Renderer.render(Arbiter);

        Window.display();
    }


    return 0;
}
