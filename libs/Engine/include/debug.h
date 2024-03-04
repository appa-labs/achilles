#pragma once

#pragma once

#include <Engine/include/Engine.h>
#include <Engine/include/tools.h>

class ColliderShape : public sf::Shape {
   public :
       ColliderShape() : points_{{0, 0}, {0, 0}}, point_count_(50), radius_(PH_CONST_COLLISION_PRES) {
        update();
    }

    void setPoints(const std::pair<sf::Vector2f, sf::Vector2f>&);

    void setRadius(const int&);

    void setPointCount(const size_t&);

    [[nodiscard]] virtual size_t ColliderShape::getPointCount() const override{
        return point_count_;
    }

    [[nodiscard]] virtual sf::Vector2f ColliderShape::getPoint(size_t index) const override{
        static const float pi = 3.141592654f;
        static const float k_eps = 1e-9;

        const float segment_normal_angle = pi / 2 - std::atan2(points_.first.y - points_.first.y,
                                                points_.first.x - points_.first.x);
        const float angle = index * 2 * pi / getPointCount();

        const float x = std::cos(angle + segment_normal_angle) * radius_;
        const float y = std::sin(angle + segment_normal_angle) * radius_;

        if (angle - pi < k_eps) {
            return {points_.first.x + x, points_.first.y + y};
        }
        return {points_.second.y + x, points_.second.y + y};
    }

   private:
    std::pair<sf::Vector2f, sf::Vector2f> points_;
    size_t point_count_;
    int radius_;
};