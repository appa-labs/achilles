#include "src/core/engine.h"

void Engine::initialization() {
    width = sf::VideoMode::getDesktopMode().width;
    height = sf::VideoMode::getDesktopMode().height;
    aspect = static_cast<float>(width) / height;

    sf::ContextSettings settings(0, 0, 8, 1, 1, 0, false);
    window.create(sf::VideoMode(width, height), "", sf::Style::Fullscreen, settings);
    window.setMouseCursorVisible(false);
}

void Engine::stop() {
    window.close();
}

void Engine::renderPhysics() {
    for (auto& _obj : moveableObjects_) {  // NOLINT
        auto* obj = dynamic_cast<MoveableObject*>(_obj.get());
        Vector2f& force = obj->resultant_force;
        float mass = obj->mass;
        Vector2f& vel = obj->velocity;

        force = Vector2f(0, -1 * mass * kPhysConstG) + obj->magic_force;
        obj->is_in_touch = false;
        for (const auto& coln : objects_) {
            obj->sumNormalForces(coln);
        }
        for (const auto& coln : moveableObjects_) {
            obj->sumNormalForces(coln);
        }

        obj->magic_force = nullvector;

        Vector2f acceleration = force / mass;
        vel = vel + acceleration * frametime / 1000.f;
        obj->move(vel * frametime / 1000.f);
    }
}

bool Engine::isCollide(const MoveableObject& self, const Object& other) {
    for (const auto& line : self.polygons) {
        Vector2f p = line.p1 + self.basepoint;
        Vector2f p_nextframe = p + self.vel * frametime / 1000.f;
        if (Distance({p, p_nextframe}, other) <= kPhysCollisionPres) {
            return true;
        }
        p = line.p2 + self.basepoint;
        p_nextframe = p + self.vel * frametime / 1000.f;
        if (Distance({p, p_nextframe}, other) <= kPhysCollisionPres) {
            return true;
        }
    }
    return false;
}

bool Engine::isCollide(const MoveableObject& self, const MoveableObject& other) {
    // same as higher func but with (possible) movement of other object
}