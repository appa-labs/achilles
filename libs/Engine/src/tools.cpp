#include <Engine/include/tools.h>
#include <cmath>

double Distance(vec p1, vec p2) {
    return std::sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
}

double Distance(vec dot, line line) {  // расстояние от точки до отрезка
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

double SignedDistance(vec dot, line line) {  // знаковое расстояние от точки до отрезка (прямой)
    if ((dot - line.d1) * (line.d2 - line.d1) < 0) {
        return (dot - line.d1).length();
    }
    if ((dot - line.d2) * (line.d1 - line.d2) < 0) {
        return (dot - line.d2).length();
    }

    double a = line.d1.y - line.d2.y, b = line.d2.x - line.d1.x,
           c = line.d1.x * line.d2.y - line.d2.x * line.d1.y;
    return (a * dot.x + b * dot.y + c) / sqrt(a * a + b * b);
}

double Distance(line l1, line l2) {
    if (IsIntersect(l1, l2)) {
        return 0;
    }
    return std::max(
        Distance(l1.d1, l2),
        std::max(Distance(l1.d2, l2), std::max(Distance(l2.d1, l1), Distance(l2.d2, l1))));
}

bool IsIntersect(line l1, line l2) {
    double a1 = SignedDistance(l1.d1, l2);
    double b1 = SignedDistance(l1.d2, l2);

    double a2 = SignedDistance(l2.d1, l1);
    double b2 = SignedDistance(l2.d2, l1);

    return (a1 >= 0 && b1 <= 0 || a1 <= 0 && b1 >= 0) && (a2 >= 0 && b2 <= 0 || a2 <= 0 && b2 >= 0);
}