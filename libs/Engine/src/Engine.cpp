#include <Engine/include/Engine.h>
#include <Engine/include/tools.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
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

    sf::ContextSettings settings(0, 0, 8, 1, 1, 0, false);
    window.create(sf::VideoMode(width, height), "Achilles", sf::Style::Fullscreen, settings);

    LoadObjTypes("resources/objectTypes.txt");
    LoadObjects("resources/objectMap.txt");
}

void Engine::LoadObjTypes(const std::string& path) {
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

void Engine::LoadObjects(
    const std::string& path) {  // пока что, требование оптимизации: писать в файле
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
        input >> inputbuffer;
        if (inputbuffer == "m") {
            double mass;
            input >> mass;
            moveableObjects_.push_back(std::make_unique<MoveableObject>(buf, vectorcache, mass));
        }
        if (inputbuffer == "s") {
            objects_.push_back(std::make_unique<Object>(buf, vectorcache));
        }
    }
    objtypes_.clear();  // оптимизация памяти, хоть какая то
}

void Engine::Stop() {
    exit(-1);
}

void Engine::RenderFrame() {
    window.clear(sf::Color(0, 0, 0, 0));
    for (const auto& obj : objects_) {
        RenderObject(obj);
    }
    for (const auto& obj : moveableObjects_) {
        RenderObject(obj);
    }
    window.display();
}

void Engine::RenderObject(const std::unique_ptr<Object>& object) {
    for (const auto& line : object->polygons_) {
        sf::Vertex vline[] = {
          sf::Vertex(sf::Vector2f(
              (object->basepoint_ + line.d1).cord(width, height).x,
              (object->basepoint_ + line.d1).cord(width, height).y)),
          sf::Vertex(sf::Vector2f(
              (object->basepoint_ + line.d2).cord(width, height).x,
              (object->basepoint_ + line.d2).cord(width, height).y))};
        window.draw(vline, 2, sf::Lines);
    }
}

void Engine::PhysicsPerFrame() {
    for (auto& _obj : moveableObjects_) {
        auto obj = static_cast<MoveableObject*>(_obj.get());
        vec& F = obj->resultantForce;
        double m = obj->mass;
        vec& vel = obj->velocity;

        F = vec(0, -1 * m * PH_CONST_G) + obj->magicForces;
        for (const auto& coln : objects_) {
            obj->SumNormalForces(coln.get()->basepoint_, coln.get()->polygons_);
        }
        for (const auto& coln : moveableObjects_) {
            obj->SumNormalForces(coln.get()->basepoint_, coln.get()->polygons_);
        }

        obj->magicForces = vec(0, 0);

        vec a = F / m;
        vel = vel + a * frametime;
        obj->move(vel * frametime);
    }
}