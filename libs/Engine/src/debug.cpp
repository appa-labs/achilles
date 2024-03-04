#include <Engine/include/debug.h>

void ColliderShape::setPoints(const std::pair<sf::Vector2f, sf::Vector2f>& points) {
    points_ = points;
    update();
}

void ColliderShape::setRadius(const int& radius) {
    radius_ = radius;
    update();
}

void ColliderShape::setPointCount(const size_t& point_count) {
    point_count_ = point_count;
    update();
}