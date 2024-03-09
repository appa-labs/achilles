#include <Engine/include/tools.h>
#include <cmath>
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
    return line(p1 + vector, p2 + vector);
}

vec line::norm() const {  // единичная нормаль к поверхности
    double a = p1.y - p2.y, b = p2.x - p1.x;
    vec no(a, b);
    return no / no.length();
}

double Distance(const vec& p1, const vec& p2) {
    return sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
}

double Distance(const vec& point, const line& segment) {
    if ((point - segment.p1) * (segment.p2 - segment.p1) < 0) {
        return (point - segment.p1).length();
    }
    if ((point - segment.p2) * (segment.p1 - segment.p2) < 0) {
        return (point - segment.p2).length();
    }

    double a = segment.p1.y - segment.p2.y, b = segment.p2.x - segment.p1.x,
           c = segment.p1.x * segment.p2.y - segment.p2.x * segment.p1.y;
    return abs(a * point.x + b * point.y + c) / sqrt(a * a + b * b);
}

double SignedDistance(const vec& point, const line& segment) {
    double a = segment.p1.y - segment.p2.y, b = segment.p2.x - segment.p1.x,
           c = segment.p1.x * segment.p2.y - segment.p2.x * segment.p1.y;
    return (a * point.x + b * point.y + c) / sqrt(a * a + b * b);
}

double Distance(const line& l1, const line& l2) {
    if (IsIntersect(l1, l2)) {
        return 0;
    }
    return std::min(
        Distance(l1.p1, l2),
        std::min(Distance(l1.p2, l2), std::min(Distance(l2.p1, l1), Distance(l2.p2, l1))));
}

bool IsIntersect(const line& l1, const line& l2) {
    double a1 = SignedDistance(l1.p1, l2);
    double b1 = SignedDistance(l1.p2, l2);

    double a2 = SignedDistance(l2.p1, l1);
    double b2 = SignedDistance(l2.p2, l1);

    return (a1 >= 0 && b1 <= 0 || a1 <= 0 && b1 >= 0) && (a2 >= 0 && b2 <= 0 || a2 <= 0 && b2 >= 0);
}

vec Projection(const vec& v, const line& axis) {
    vec vaxis(axis.p1.x - axis.p2.x, axis.p1.y - axis.p2.y);
    if (vaxis * v <= 0) {
        vaxis = vaxis * (-1);
    }
    return vaxis / vaxis.length() * (vaxis * v) / vaxis.length();
}

vec Projection(const vec& v, vec axis) {
    if (axis * v <= 0) {
        axis = axis * (-1);
    }
    return axis / axis.length() * (axis * v) / axis.length();
}

void MoveableObject::move(const vec& vector) {
    basepoint = basepoint + vector;
}

void MoveableObject::sumNormalForces(Object* obj) {
    if (this == obj) {
        return;
    }
    for (line line1 : polygons) {
        line1 = line1.move(basepoint);
        for (line line2 : obj->polygons) {
            line2 = line2.move(obj->basepoint);
            vec Nadditional;  
            if (Distance(line1, line2) <= PH_CONST_COLLISION_PRES) {
                if (Projection(velocity, line2.norm()) * (basepoint - line2.p1) >= 0) {
                    continue;  // make obj get out of other obj
                }
                vec N = Projection(resultantForce, line2.norm()) * (-1);
                if (Projection(N, line2.norm()) * (basepoint - line2.p1) <= 0) {
                    N = vec(0, 0);
                }
                vec Ffrict = velocity / velocity.length() * N.length() * frictionCoef * (-1);
                resultantForce = resultantForce + N + Ffrict;
                velocity = Projection(velocity, line2);
                Nadditional = N / 2.;
            }
            resultantForce = resultantForce + Nadditional;
        }
    }
}
