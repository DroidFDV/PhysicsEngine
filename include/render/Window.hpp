#ifndef WINDOW_H
#define WINDOW_H


#include <SFML/Graphics.hpp>
#include <SFML/Window/WindowStyle.hpp>


struct window_traits {

    window_traits() noexcept : settings() {
        settings.antialiasingLevel = 1;
    }



    static const int32_t width           = 1280;
    static const int32_t height          = 720;
    static const int32_t frameRateLimit  = 60;
    inline static const std::string name = "beta version";

    sf::Uint32          style = sf::Style::None; 
    sf::ContextSettings settings;
    sf::Color backgroundColor = sf::Color::White;
};

#endif // WINDOW_H
