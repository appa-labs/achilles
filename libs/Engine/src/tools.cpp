#include <Engine/include/tools.h>
#include <cmath>
#include <string>
#include <utility>
#include <vector>

vec vec::cord(int width, int height) const {  // преобразование из моих координат в сфмл
    double aspect = static_cast<double>(width) / height;
    return {(x + 1. * aspect) / aspect / 2. * width, (-1 * y + 1.) / 2. * height};
}

vec vec::anticord(int width, int height) const {  // обратное
    double aspect = static_cast<double>(width) / height;
    return {x * aspect * 2. / width - 1. * aspect, (-1 * y) * 2. / height + 1.};
}

line line::move(const vec& vector) const {
    return line(d1 + vector, d2 + vector);
}

vec line::norm() const {  // единичная нормаль к поверхности
    double a = d1.y - d2.y, b = d2.x - d1.x;
    vec no(a, b);
    return no / no.length();
}

double Distance(const vec& p1, const vec& p2) {
    return sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
}

double Distance(const vec& dot, const line& line) {
    if ((dot - line.d1) * (line.d2 - line.d1) < 0) {
        return (dot - line.d1).length();
    }
    if ((dot - line.d2) * (line.d1 - line.d2) < 0) {
        return (dot - line.d2).length();
    }

    double a = line.d1.y - line.d2.y, b = line.d2.x - line.d1.x,
           c = line.d1.x * line.d2.y - line.d2.x * line.d1.y;
    return abs(a * dot.x + b * dot.y + c) / sqrt(a * a + b * b);
}

double SignedDistance(const vec& dot, const line& line) {
    double a = line.d1.y - line.d2.y, b = line.d2.x - line.d1.x,
           c = line.d1.x * line.d2.y - line.d2.x * line.d1.y;
    return (a * dot.x + b * dot.y + c) / sqrt(a * a + b * b);
}

double Distance(const line& l1, const line& l2) {
    if (IsIntersect(l1, l2)) {
        return 0;
    }
    return std::min(
        Distance(l1.d1, l2),
        std::min(Distance(l1.d2, l2), std::min(Distance(l2.d1, l1), Distance(l2.d2, l1))));
}

bool IsIntersect(const line& l1, const line& l2) {
    double a1 = SignedDistance(l1.d1, l2);
    double b1 = SignedDistance(l1.d2, l2);

    double a2 = SignedDistance(l2.d1, l1);
    double b2 = SignedDistance(l2.d2, l1);

    return (a1 >= 0 && b1 <= 0 || a1 <= 0 && b1 >= 0) && (a2 >= 0 && b2 <= 0 || a2 <= 0 && b2 >= 0);
}

vec Proection(const vec& what, const line& axis) {
    vec vaxis(axis.d1.x - axis.d2.x, axis.d1.y - axis.d2.y);
    if (vaxis * what <= 0) {
        vaxis = vaxis * (-1);
    }
    return vaxis / vaxis.length() * (vaxis * what) / vaxis.length();
}

vec Proection(const vec& what, vec vaxis) {
    if (vaxis * what <= 0) {
        vaxis = vaxis * (-1);
    }
    return vaxis / vaxis.length() * (vaxis * what) / vaxis.length();
}

void MoveableObject::move(const vec& vector) {
    basepoint_ = basepoint_ + vector;
}

void MoveableObject::SumNormalForces(Object* obj) {
    if (this == obj) {
        return;
    }
    for (line line1 : polygons_) {
        line1 = line1.move(basepoint_);
        for (line line2 : obj->polygons_) {
            line2 = line2.move(obj->basepoint_);
            if (Distance(line1, line2) <= PH_CONST_COLLISION_PRES) {
                if (Proection(velocity, line2.norm()) * (basepoint_ - line2.d1) >= 0) {
                    continue;
                }
                vec N = Proection(resultantForce, line2.norm()) * (-1);
                vec Ffrict = velocity * N.length() * frictionCoef * (-1);
                resultantForce = resultantForce + N + Ffrict;
                velocity = Proection(velocity, line2);
            }
        }
    }
}

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
