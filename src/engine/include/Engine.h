#pragma once

#define _SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING
#define _SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS

#include <Engine/include/tools.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <map>
#include <memory>
#include <string>
#include <vector>

// ----------------------------------------------------------------------
// Engine
// ----------------------------------------------------------------------
// Класс Engine выступает в роли объекта игры(приложения). Содержит
// методы инициализации: initialization(), loadObjTypes(..), ...; методы
// рендера: renderFrame(), renderObject(..), ...; контроля состояния
// приложения stop(), restart() и движения игрока: characterJump(),
// characterLeft().
class Engine {
   public:
    int height;
    int width;
    float aspect;
    sf::RenderWindow window;
    float frametime = 1.f;

    void initialization();
    void loadObjTypes(const std::string& path);  // TODO: add AssetManager
    void loadObjects(const std::string& path);
    void stop();
    void renderFrame();
    void renderObject(const std::unique_ptr<Object>& object);
    void physicsPerFrame();
    void drawCollider(const std::unique_ptr<Object>& obj);
    void renderFPS(sf::Text& frame_rate_text);

    void characterJump();
    void characterLeft();
    void characterRight();
    void restart();

   private:
    std::vector<std::unique_ptr<Object>> objects_;
    std::vector<std::unique_ptr<Object>> moveableObjects_;
    std::map<std::string, std::vector<line>> objtypes_;
};