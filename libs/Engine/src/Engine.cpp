#include <Engine/include/Engine.h>
#include <Engine/include/tools.h>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

void Engine::Initialization() {
    width = sf::VideoMode::getDesktopMode().width;
    height = sf::VideoMode::getDesktopMode().height;
    aspect = static_cast<double>(width) / height;

    LoadObjTypes("resources/objectTypes.txt");
    LoadObjects("resources/objectMap.txt");
}

void Engine::LoadObjTypes(std::string path) {
    std::ifstream fin;
    fin.open(path);
    if (!(fin.is_open())) {
        std::cerr << "Не удалось открыть файл с паттернами объектов по пути " +
                         path;  // потом прикрутим логгер какой нибудь, мне лень
        Stop();
    }
    line buf({0, 0}, {0, 0});
    std::string inputbuffer;
    std::string strbuf;
    std::vector<line> vectorbuf;
    double x1, y1, x2, y2;
    while (std::getline(fin, inputbuffer)) {
        std::stringstream input(inputbuffer);
        input >> strbuf;
        while (input >> x1 >> y1 >> x2 >> y2) {
            buf = line({x1, y1}, {x2, y2});
            vectorbuf.push_back(buf);
        }
        objtypes_.insert({strbuf, vectorbuf});
        vectorbuf.clear();
    }
}

void Engine::LoadObjects(std::string path) {  // пока что, требование оптимизации: писать в файле
                                              // объекты с одинаковыми названиями подряд
    std::ifstream fin;
    fin.open(path);
    if (!(fin.is_open())) {
        std::cerr << "Не удалось открыть файл с картой объектов по пути " +
                         path;  // потом прикрутим логгер какой нибудь, мне лень
        Stop();
    }
    vec buf(0, 0);
    std::string inputbuffer;
    std::string name;
    std::vector<line> vectorcache;
    std::string cachename;
    double x1, y1;
    while (std::getline(fin, inputbuffer)) {
        std::stringstream input(inputbuffer);
        input >> name >> x1 >> y1;
        buf = vec(x1, y1);
        if (cachename != name) {
            cachename = name;
            vectorcache = objtypes_[name];
        }
        objects_.push_back(std::make_unique<Object>(buf, vectorcache));
    }
}

void Engine::Stop() {
    exit(-1);
}

void Engine::RenderFrame() {
    //win_.clear(sf::Color(0, 0, 0, 0));
    for (const auto& obj : objects_) {
        
    }
}

void Engine::RenderObject(std::unique_ptr<Object> object) {

}