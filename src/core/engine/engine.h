#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <spdlog/spdlog.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "src/core/tools/tools.h"

// ----------------------------------------------------------------------
// Engine
// ----------------------------------------------------------------------
// ����� Engine ��������� � ���� ������� ����(����������). ��������
// ������ �������������: initialization(), loadObjTypes(..), ...; ������
// �������: renderFrame(), renderObject(..), ...; �������� ���������
// ���������� stop(), restart() � �������� ������: characterJump(),
// characterLeft().
class Engine {
   public:
    int height;
    int width;
    float aspect;
    sf::RenderWindow window;
    float frametime = 1.f;
    vec camera{};

    void initialization();
    void loadObjTypes(const std::string& path);  // TODO: add AssetManager
    void loadObjects(const std::string& path);
    void stop();
    void renderFrame();
    void renderObject(const std::unique_ptr<Object>& object);
    void physicsPerFrame();
    void drawBaton(const std::unique_ptr<Object>& obj);
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