#pragma once
#include <Engine/include/tools.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <map>
#include <memory>
#include <string>
#include <vector>

class Engine {
   public:
    int height;
    int width;
    double aspect;
    sf::RenderWindow window;
    double frametime = 0;

    void Initialization();
    void LoadObjTypes(const std::string& path);
    void LoadObjects(const std::string& path);
    void Stop();
    void RenderFrame();
    void RenderObject(const std::unique_ptr<Object>& object);
    void PhysicsPerFrame();
    void RenderCollider(const std::unique_ptr<Object>& object);
    void PrintCollider(const line& l);

    void CharacterJump();
    void CharacterLeft();
    void CharacterRight();
    void Restart();

   private:
    std::vector<std::unique_ptr<Object>> objects_;
    std::vector<std::unique_ptr<Object>> moveableObjects_;
    std::map<std::string, std::vector<line>> objtypes_;
};