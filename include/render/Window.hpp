#ifndef WINDOW_H
#define WINDOW_H


#include <SFML/Graphics.hpp>
#include <SFML/Window/WindowStyle.hpp>


////////////////////////////////////////////////////////////
/// \brief Struct to present trais of window
////////////////////////////////////////////////////////////
struct window_traits {
    
    ////////////////////////////////////////////////////////////
    /// \brief Construct window_traits and setting, install level
    ///        of anti analiasing is 1
    ////////////////////////////////////////////////////////////
    window_traits() noexcept : settings() {
        settings.antialiasingLevel = 1;
    }


    ////////////////////////////////////////////////////////////
    /// Member data
    ////////////////////////////////////////////////////////////
    static const int32_t width           = 1280;
    static const int32_t height          = 720;
    static const int32_t frameRateLimit  = 60;
    inline static const std::string name = "beta version";

    sf::Uint32          style = sf::Style::None; 
    sf::ContextSettings settings;
    sf::Color backgroundColor = sf::Color::White;
};

#endif // WINDOW_H
