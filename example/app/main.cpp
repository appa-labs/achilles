#include <memory>

#include "example/core/my_engine.h"
#include "example/logger/logger_init.h"

int main() {

    // TODO(fndk): Add config file, maybe json or protobuf
    loggerInit("logs/game-log.txt");

    
    std::unique_ptr<MyEngine> engine(new MyEngine());
    spdlog::info("Engine created");

    // ------------------------------------------------------------
    // Engine initialization
    // ------------------------------------------------------------
    engine->initialization();
    spdlog::info("Engine initialization");
    sf::Text frame_rate_text;
    sf::Font font;
    sf::Clock clock;

    // ------------------------------------------------------------
    // Font loading
    // ------------------------------------------------------------
    if (font.loadFromFile("example/resources/fonts/arial.ttf")) {
        frame_rate_text.setFont(font);
        spdlog::info("Font successfuly loaded");
    } else {
        spdlog::error("Font load error", -1);
        engine->stop();
    }


    // ------------------------------------------------------------
    // Main loop
    // ------------------------------------------------------------
    engine->window.setFramerateLimit(60);
    while (engine->window.isOpen()) {
        const sf::Time delta_timer = clock.restart();

        engine->frametime = delta_timer.asSeconds() * 1000.f;  // compute the framerate

        sf::Event event;
        while (engine->window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                engine->stop();
            }
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Escape:
                        engine->stop();
                        break;
                    case sf::Keyboard::Space:
                        engine->characterJump();
                        break;
                    case sf::Keyboard::R:
                        spdlog::info("Engine restart");
                        engine->restart();
                        break;
                    default:
                        break;
                }
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            engine->characterLeft();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            engine->characterRight();
        }
        engine->renderPhysics();
        engine->renderFrame();
        engine->renderFPS(frame_rate_text);
    }

    spdlog::info("Engine stops with code {}", 0);
    return 0;
}