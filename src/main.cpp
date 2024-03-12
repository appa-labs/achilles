#include <SFML/Graphics.hpp>
#include <chrono>
#include <libs/Engine/include/Engine.h>
#include <Logger/include/logger.h>
#include <config.h>

int main() {
    loggerInit(config::log_file_path);

    Engine engine;
    spdlog::info("Engine start");

    //----------------------------------------------- INITIALIZE -----------------------------------------------
    engine.initialization();
    spdlog::info("Engine initialization");
    sf::Text frameRateText;
    sf::Font font;
    sf::Clock Clock;

    //----------------------------------------------- LOAD -----------------------------------------------
    if (font.loadFromFile("resources/fonts/arial.ttf")) {
        frameRateText.setFont(font);
        spdlog::info("Font successfuly loaded");
    }
    else {
        spdlog::info("Font load error", -1);
        engine.stop();
    }

    engine.window.setFramerateLimit(60);
    while (engine.window.isOpen()) {
        sf::Time deltaTimer = Clock.restart();

        engine.frametime = deltaTimer.asSeconds(); //compute the framerate
        
        sf::Event event;
        while (engine.window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                engine.window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Escape:
                        spdlog::info("Engine stops with code {}", -1);
                        engine.stop();
                        break;
                    case sf::Keyboard::Space:
                        spdlog::info("Character jump");
                        engine.characterJump();
                        break;
                    case sf::Keyboard::A:
                        spdlog::info("Character move left");
                        engine.characterLeft();
                        break;
                    case sf::Keyboard::D:
                        spdlog::info("Character move right");
                        engine.characterRight();
                        break;
                    case sf::Keyboard::R:
                        spdlog::info("Engine restart");
                        engine.restart();
                        break;
                }
            }
        }
        engine.physicsPerFrame();
        engine.renderFrame();
        engine.renderFPS(frameRateText);
    }
     
    spdlog::info("Engine stops with code {}", 0);
    return 0;
}