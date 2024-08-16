#pragma once

#include "src/tools/tools.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <map>
#include <memory>
#include <vector>

// ----------------------------------------------------------------------
// Engine
// ----------------------------------------------------------------------
// Class Engine is a base class for all engines. It has fields for window
// width, height, aspect ratio, camera position, frame time, window object,
// vector of objects, vector of moveable objects, map of object types.
// It has methods for initialization, stop, restart, render frame, render
// object, render physics.
class Engine {
   public:
    int height{0};
    int width{0};
    float aspect{0};
    float frametime = 1.f;
    sf::RenderWindow window;
    Vector2f camera;

    sf::Color player_color = sf::Color::White;  // DEBUG

    Engine() = default;

    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;
    Engine(Engine&&) noexcept = delete;
    Engine& operator=(Engine&&) noexcept = delete;

    virtual void initialization();
    virtual void stop();

    virtual void restart() = 0;
    virtual void renderFrame() = 0;
    virtual void renderObject(const std::unique_ptr<Object>& object) = 0;

    void renderPhysics();

    virtual ~Engine() = default;

    // DEBUG
    void renderPath(const std::unique_ptr<Object>& obj);

   protected:
    std::vector<std::unique_ptr<Object>> objects_;
    std::vector<std::unique_ptr<Object>> moveable_objects_;
    std::map<std::string, std::vector<LineSegment>> objtypes_;

   private:
    Vector2f computeCollideNormalWithStatic(MoveableObject* self);
    Vector2f computeCollideNormalWithMoveable(MoveableObject* self);
};