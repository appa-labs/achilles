#pragma once

#include <fstream>
#include <iostream>
#include <spdlog/spdlog.h>

#include "src/core/engine.h"
#include "src/tools/tools.h"

class MyEngine : public Engine {
   public:
    void initialization() override;
    void renderFrame() override;
    void renderObject(const std::unique_ptr<Object>& object) override;
    void stop() override;
    void restart() override;

    void loadObjTypes(const std::string& path);
    void loadObjects(const std::string& path);

    void drawBaton(const std::unique_ptr<Object>& obj);
    void renderFPS(sf::Text& frame_rate_text);

    void characterJump();
    void characterLeft();
    void characterRight();
};