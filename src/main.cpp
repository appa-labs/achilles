#include <SFML/Graphics.hpp>
#include <libs/Engine/include/Engine.h>

int main() {
    Engine engine;
    engine.Initialization();

    while (engine.window.isOpen()) {
        sf::Event event;
        while (engine.window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                engine.window.close();
            }
        }
        engine.RenderFrame();
    }
    return 0;
}