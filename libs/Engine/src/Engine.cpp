#include <Engine/include/Engine.h>
#include <SFML/Graphics.hpp>

void Engine::Initialization() {
    width = sf::VideoMode::getDesktopMode().width;
    height = sf::VideoMode::getDesktopMode().height;
    aspect = static_cast<double>(width) / height;
}