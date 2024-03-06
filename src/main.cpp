#include <SFML/Graphics.hpp>
#include <chrono>
#include <libs/Engine/include/Engine.h>

int main() {
    Engine engine;
    engine.Initialization();

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
                        engine.Stop();
                        break;
                    case sf::Keyboard::Space:
                        engine.CharacterJump();
                        break;
                    case sf::Keyboard::A:
                        engine.CharacterLeft();
                        break;
                    case sf::Keyboard::D:
                        engine.CharacterRight();
                        break;
                    case sf::Keyboard::R:
                        engine.Restart();
                        break;
                }
            }
        }
        engine.PhysicsPerFrame();
        engine.RenderFrame();
        auto end = std::chrono::system_clock::now();
        engine.frametime =
            std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.;
    }
    return 0;
}