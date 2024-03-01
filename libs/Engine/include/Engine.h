#pragma once
#include <Engine/include/tools.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <map>
#include <memory>
#include <string>
#include <vector>

static inline const double PH_CONST_G = 9.81;

class Engine {
   public:
    int height;
    int width;
    double aspect;
    sf::RenderWindow window;

    void Initialization();
    void LoadObjTypes(const std::string& path);
    void LoadObjects(const std::string& path);
    void Stop();
    void RenderFrame();
    void RenderObject(const std::unique_ptr<Object>& object);
    void PhysicPerFrame();

   private:
    std::vector<std::unique_ptr<Object>> objects_;
    std::vector<std::unique_ptr<Object>> moveableObjects_;
    std::map<std::string, std::vector<line>> objtypes_;
};