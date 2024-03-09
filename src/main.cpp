#include <SFML/Graphics.hpp>
#include <chrono>
#include <libs/Engine/include/Engine.h>
#include <Logger/include/logger.h>
#include <config.h>

int main() {
    loggerInit(config::log_file_path);

    Engine engine;
    spdlog::info("Engine start");
    engine.initialization();
    spdlog::info("Engine initialization");
    sf::Clock deltaClock;
    while (engine.window.isOpen()) {
        auto start = std::chrono::system_clock::now();
        sf::Event event;
        sf::Time dt = deltaClock.restart();
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

        engine.frametime = dt.asMilliseconds() / 1000.;
    }

    spdlog::info("Engine stops with code {}", 0);
    return 0;
}