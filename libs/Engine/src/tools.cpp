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

double Distance(line l1, line l2) {

}