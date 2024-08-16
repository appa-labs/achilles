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

void Engine::renderPath(const std::unique_ptr<Object>& obj) {
    for (const auto& area : dynamic_cast<MoveableObject*>(obj.get())->areas) {
        {
            sf::Vertex vline[] = {
                sf::Vertex(sf::Vector2f(
                    (area.p1 - camera).getSfmlCords(width, height).x,
                    (area.p1 - camera).getSfmlCords(width, height).y)),
                sf::Vertex(sf::Vector2f(
                    (area.p2 - camera).getSfmlCords(width, height).x,
                    (area.p2 - camera).getSfmlCords(width, height).y))};
            window.draw(static_cast<sf::Vertex*>(vline), 2, sf::Lines);
        }
        {
            sf::Vertex vline[] = {
                sf::Vertex(sf::Vector2f(
                    (area.p2 - camera).getSfmlCords(width, height).x,
                    (area.p2 - camera).getSfmlCords(width, height).y)),
                sf::Vertex(sf::Vector2f(
                    (area.p3 - camera).getSfmlCords(width, height).x,
                    (area.p3 - camera).getSfmlCords(width, height).y))};
            window.draw(static_cast<sf::Vertex*>(vline), 2, sf::Lines);
        }
        {
            sf::Vertex vline[] = {
                sf::Vertex(sf::Vector2f(
                    (area.p3 - camera).getSfmlCords(width, height).x,
                    (area.p3 - camera).getSfmlCords(width, height).y)),
                sf::Vertex(sf::Vector2f(
                    (area.p4 - camera).getSfmlCords(width, height).x,
                    (area.p4 - camera).getSfmlCords(width, height).y))};
            window.draw(static_cast<sf::Vertex*>(vline), 2, sf::Lines);
        }
        {
            sf::Vertex vline[] = {
                sf::Vertex(sf::Vector2f(
                    (area.p1 - camera).getSfmlCords(width, height).x,
                    (area.p1 - camera).getSfmlCords(width, height).y)),
                sf::Vertex(sf::Vector2f(
                    (area.p4 - camera).getSfmlCords(width, height).x,
                    (area.p4 - camera).getSfmlCords(width, height).y))};
            window.draw(static_cast<sf::Vertex*>(vline), 2, sf::Lines);
        }
    }
    window.display();
}


void Engine::renderPhysics() {
    for (auto& _obj : moveable_objects_) {  // NOLINT
        auto* obj = dynamic_cast<MoveableObject*>(_obj.get());
        Vector2f& force = obj->resultant_force;
        float mass = obj->mass;
        Vector2f& vel = obj->velocity;

        force = Vector2f(0, -1 * mass * kPhysConstG) + obj->magic_force;

        Vector2f general_normal = computeCollideNormalWithStatic(obj) + computeCollideNormalWithMoveable(obj);
        renderPath(_obj);  // DEBUG

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
    self->areas.clear();  // DEBUG
    
    Vector2f general_normal = nullvector;
    self->in_touch = false;
    Vector2f path = self->velocity * frametime / 1000.f;
    for (const auto& obj : objects_) {
        for (LineSegment justline : obj->polygons) {
            justline = justline.move(obj->basepoint);
            for (auto line : self->polygons) {
                line = line.move(self->basepoint);

                auto path_area = PathCollisionArea(line, path);

                self->areas.push_back(path_area);  // DEBUG

                if (path_area.collision(justline)) {
                    general_normal += justline.getNormal();
                    self->in_touch = true;
                    player_color = sf::Color::Red;  // DEBUG
                }
            }
        }
    }
    return general_normal;
}

// same as higher func but with (possible) movement and forces of other object(s)
Vector2f Engine::computeCollideNormalWithMoveable(MoveableObject* self) {
    return {0, 0};
}