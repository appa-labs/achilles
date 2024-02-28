#include <Engine/include/Engine.h>
#include <Engine/include/tools.h>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

void Engine::Initialization() {
    width = sf::VideoMode::getDesktopMode().width;
    height = sf::VideoMode::getDesktopMode().height;
    aspect = static_cast<double>(width) / height;

    LoadObjects("resources/objects.txt");
}

void Engine::LoadObjects(std::string path) {
    // пока что формат: две координату первой точки, после две координаты второй
    std::ifstream fin;
    fin.open(path);
    if (!(fin.is_open())) {
        std::cerr << "Ќе удалось открыть файл с объектами по пути " +
                         path;  // потом прикрутим логгер какой нибудь, мне лень
        Stop();
    }
    line buf({0, 0}, {0, 0});
    std::string inputbuffer;
    while (std::getline(fin, inputbuffer)) {
        std::stringstream input(inputbuffer);
        double x1, y1, x2, y2;
        input >> x1 >> y1 >> x2 >> y2;
        buf = line(
            {x1, y1}, {x2, y2});  // если кажетс€, что это сделано топорно, то это только кажетс€.
        objects_.push_back(buf);
    }
}

void Engine::Stop() {
    exit(-1);
}