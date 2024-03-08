#include <SFML/Graphics.hpp>
#include <chrono>
#include <libs/Engine/include/Engine.h>

int main() {
    Engine engine;
    engine.initialization();

    while (engine.window.isOpen()) {
        auto start = std::chrono::system_clock::now();
        sf::Event event;
        while (engine.window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                engine.window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Escape:
                        engine.stop();
                        break;
                    case sf::Keyboard::Space:
                        engine.characterJump();
                        break;
                    case sf::Keyboard::A:
                        engine.characterLeft();
                        break;
                    case sf::Keyboard::D:
                        engine.characterRight();
                        break;
                    case sf::Keyboard::R:
                        engine.restart();
                        break;
                }
            }
        }
        engine.physicsPerFrame();
        engine.renderFrame();
        auto end = std::chrono::system_clock::now();
        engine.frametime =
            std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.;
    }
    return 0;
}