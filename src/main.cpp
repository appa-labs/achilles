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
        }
        engine.PhysicPerFrame();
        engine.RenderFrame();
        auto end = std::chrono::system_clock::now();
        engine.frametime =
            std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.;
    }
    return 0;
}