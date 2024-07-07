#include <chrono>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "src/app/config.h"
#include "src/logger/logger_init.h"
#include "src/core/engine/engine.h"

int main() {
    loggerInit(config::log_file_path);

    Engine engine;
    spdlog::info("Engine start");

    //----------------------------------------------- INITIALIZE
    //-----------------------------------------------
    engine.initialization();
    spdlog::info("Engine initialization");
    sf::Text frame_rate_text;
    sf::Font font;
    sf::Clock clock;

    //----------------------------------------------- LOAD
    //-----------------------------------------------
    if (font.loadFromFile("resources/fonts/arial.ttf")) {
        frame_rate_text.setFont(font);
        spdlog::info("Font successfuly loaded");
    } else {
        spdlog::info("Font load error", -1);
        engine.stop();
    }

    engine.window.setFramerateLimit(60);
    while (engine.window.isOpen()) {
        sf::Time delta_timer = clock.restart();

        engine.frametime = delta_timer.asSeconds() * 1000.f;  // compute the framerate

        sf::Event event;
        while (engine.window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                engine.stop();
            }
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Escape:
                        engine.stop();
                        break;
                    case sf::Keyboard::Space:
                        engine.characterJump();
                        break;
                    case sf::Keyboard::R:
                        spdlog::info("Engine restart");
                        engine.restart();
                        break;
                    default:
                        break;
                }
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            engine.characterLeft();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            engine.characterRight();
        }
        engine.physicsPerFrame();
        engine.renderFrame();
        engine.renderFPS(frame_rate_text);
    }

    spdlog::info("Engine stops with code {}", 0);
    return 0;
}