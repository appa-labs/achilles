#pragma once
#include <Engine/include/tools.h>
#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <string>
#include <vector>

class Engine {
   public:
    static inline int height;
    static inline int width;
    static inline double aspect;

    Engine() = delete;

    static inline void Initialization();
    static inline void LoadObjTypes(std::string path);
    static inline void LoadObjects(std::string path);
    static inline void Stop();
    static inline void RenderFrame();
    static inline void RenderObject(std::unique_ptr<Object> object);

   private:
    static std::vector<std::unique_ptr<Object>> objects_;
    static std::map<std::string, std::vector<line>> objtypes_;
    // static sf::ContextSettings settings_(0, 0, 8, 1, 1, 0, false);
    // static sf::RenderWindow win_(sf::VideoMode(width, height), "game", sf::Style::Fullscreen,
    // settings);
};