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
    for (auto& _obj : moveable_objects_) {  // NOLINT
        auto* obj = dynamic_cast<MoveableObject*>(_obj.get());
        Vector2f& force = obj->resultant_force;
        float mass = obj->mass;
        Vector2f& vel = obj->velocity;

        force = Vector2f(0, -1 * mass * kPhysConstG) + obj->magic_force;

        Vector2f general_normal = computeCollideNormalWithStatic(obj) + computeCollideNormalWithMoveable(obj);

        if(obj->in_touch) {
            force -= Projection(force, general_normal);
            vel -= Projection(vel, general_normal);
        }

        obj->magic_force = nullvector;

        Vector2f acceleration = force / mass;
        vel = vel + acceleration * frametime / 1000.f;
        obj->move(vel * frametime / 1000.f);
    }
}

// This functions computes general normal like in case of colliding with 1 LineSegment
// NEED OPTIMIZATION IN THE FUTURE
Vector2f Engine::computeCollideNormalWithStatic(MoveableObject* self) {
    player_color = sf::Color::White; // DEBUG
    
    Vector2f generalNormal = nullvector;
    self->in_touch = false;
    for (const auto& obj : objects_) {
        for (LineSegment justline : obj->polygons) {
            justline = justline.move(obj->basepoint);
            for (const auto& line : self->polygons) {
                Vector2f path = self->velocity * frametime / 1000.f;
                Vector2f cur_p1 = line.p1 + self->basepoint;
                Vector2f cur_p2 = line.p2 + self->basepoint;

                auto path_area = Parallelogram(cur_p1, cur_p2, cur_p2 + path, cur_p1 + path);
                if (path_area.cover(justline)) {
                    generalNormal += justline.getNormal();
                    self->in_touch = true;
                    player_color = sf::Color::Red;  // DEBUG
                }
            }
        }
    }
    return generalNormal;
}

// same as higher func but with (possible) movement and forces of other object(s)
Vector2f Engine::computeCollideNormalWithMoveable(MoveableObject* self) {
    return {0, 0};
}