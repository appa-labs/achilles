#include "src/tools/tools.h"

[[nodiscard]] Vector2f Vector2f::getSfmlCords(int width, int height) const {
    float aspect = static_cast<float>(width) / height;
    return {(x + 1.f * aspect) / aspect / 2.f * width, (-1.f * y + 1.f) / 2.f * height};
}

[[nodiscard]] Vector2f Vector2f::getLocalCords(int width, int height) const {
    float aspect = static_cast<float>(width) / height;
    return {x * aspect * 2.f / width - 1.f * aspect, (-1.f * y) * 2.f / height + 1.f};
}

[[nodiscard]] float Vector2f::length() const {
    return math_sqrt(squaredLength());
}

[[nodiscard]] float Vector2f::squaredLength() const {
    return x * x + y * y;
}

Vector2f& Vector2f::normilize() {
    float vec_length = math_sqrt(squaredLength());
    x /= vec_length;
    y /= vec_length;
    return *this;
}

Vector2f Vector2f::operator+(const Vector2f& other) const {
    return {x + other.x, y + other.y};
}

Vector2f& Vector2f::operator+=(const Vector2f& other) {
    *this = *this + other;
    return *this;
}

Vector2f Vector2f::operator-(const Vector2f& other) const {
    return {x - other.x, y - other.y};
}

Vector2f& Vector2f::operator-=(const Vector2f& other) {
    *this = *this - other;
    return *this;
}

Vector2f Vector2f::operator*(float scalar) const {
    return {x * scalar, y * scalar};
}

Vector2f& Vector2f::operator*=(float scalar) {
    *this = *this * scalar;
    return *this;
}

float Vector2f::operator*(const Vector2f& other) const {
    return x * other.x + y * other.y;
}

Vector2f Vector2f::operator/(float scalar) const {
    return {x / scalar, y / scalar};
}

Vector2f& Vector2f::operator/=(float scalar) {
    *this = *this / scalar;
    return *this;
}

Vector2f Vector2f::operator/(const Vector2f& other) const {
    return {x / other.x, y / other.y};
}

Vector2f& Vector2f::operator/=(const Vector2f& other) {
    *this = *this / other;
    return *this;
}

Vector2f Vector2f::operator-() const {
    return {-x, -y};
}

Vector2f operator*(float scalar, const Vector2f& vector) {
    return vector * scalar;
}

bool Vector2f::operator==(const Vector2f& other) const {
    return math_abs(x - other.x) <= kEps && math_abs(y - other.y) <= kEps;
}

bool Vector2f::operator!=(const Vector2f& other) const {
    return !(*this == other);
}

[[nodiscard]] float LineSegment::squaredLength() const {
    return (p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y);
}

[[nodiscard]] LineSegment LineSegment::move(const Vector2f& vector) const {
    return {p1 + vector, p2 + vector};
}

[[nodiscard]] Vector2f LineSegment::getNormal() const {
    float a = p1.y - p2.y;
    float b = p2.x - p1.x;
    Vector2f normal(a, b);
    normal.normilize();
    return normal;
}

[[nodiscard]] double Triangle::doubleSquare() {
    double double_square = static_cast<double>(p2.x - p1.x) * (p3.y - p1.y);
    double_square -= static_cast<double>(p3.x - p1.x) * (p2.y - p1.y);
    return math_abs(double_square);
}

[[nodiscard]] double Quadrangle::doubleSquare() const {
    double squre = Triangle(p1, p2, p3).doubleSquare();
    squre += Triangle(p1, p3, p4).doubleSquare();
    return squre;
}

[[nodiscard]] bool Quadrangle::cover(const Vector2f& point) const{
    double from_point_double_square = Triangle(p1, p2, point).doubleSquare();
    from_point_double_square += Triangle(p2, p3, point).doubleSquare();
    from_point_double_square += Triangle(p3, p4, point).doubleSquare();

    return math_abs(from_point_double_square - doubleSquare()) <= kEps;
}

[[nodiscard]] bool Quadrangle::cover(const LineSegment& segment) const {
    return cover(segment.p1) || cover(segment.p2) || 
            IsIntersect(segment, LineSegment(p1, p2)) ||
            IsIntersect(segment, LineSegment(p2, p3)) || 
            IsIntersect(segment, LineSegment(p3, p4)) ||
            IsIntersect(segment, LineSegment(p4, p1));
}

[[nodiscard]] double Parallelogram::doubleSquare() const {
    return Triangle(p1, p2, p3).doubleSquare() * 2;
}

[[nodiscard]] bool PathCollisionArea::collision(const LineSegment& segment) const {
    return cover(segment) || 
        math_abs(Distance(LineSegment(p1, p2), segment) - kPhysCollisionPres) < kEps ||
        math_abs(Distance(LineSegment(p2, p3), segment) - kPhysCollisionPres) < kEps ||
        math_abs(Distance(LineSegment(p3, p4), segment) - kPhysCollisionPres) < kEps ||
        math_abs(Distance(LineSegment(p4, p1), segment) - kPhysCollisionPres) < kEps;
}

float Distance(const Vector2f& p1, const Vector2f& p2) {
    return math_sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
}

float Distance(const Vector2f& point, const LineSegment& segment) {
    float l2 = segment.squaredLength();  // avoid sqrt
    if (l2 == 0) {                       // length == 0
        return Distance(point, segment.p1);
    }
    // Consider the line extending the segment, parameterized as p1 + t(p2 - p1).
    // We find projection of point p onto the line.
    // It falls where t = [(p-p1) . (p2-p1)] / |p2-p1|^2
    // We clamp t from [0,1] to handle points outside the segment.
    const float t =
        std::max(0.0f, std::min(1.0f, (point - segment.p1) * (segment.p2 - segment.p1) / l2));
    const Vector2f projection = segment.p1 + t * (-segment.p1);  // Projection falls on the segment
    return Distance(point, projection);
}

float Distance(const LineSegment& s1, const LineSegment& s2) {
    if (IsIntersect(s1, s2)) {
        return 0;
    }
    return std::min(
        Distance(s1.p1, s2),
        std::min(Distance(s1.p2, s2), std::min(Distance(s2.p1, s1), Distance(s2.p2, s1))));
}

float SignedDistance(const Vector2f& point, const LineSegment& segment) {
    float a = segment.p1.y - segment.p2.y;
    float b = segment.p2.x - segment.p1.x;
    float c = segment.p1.x * segment.p2.y - segment.p2.x * segment.p1.y;
    return (a * point.x + b * point.y + c) / math_sqrt(a * a + b * b);
}

bool IsIntersect(const LineSegment& s1, const LineSegment& s2) {
    float a1 = SignedDistance(s1.p1, s2);
    float b1 = SignedDistance(s1.p2, s2);

    float a2 = SignedDistance(s2.p1, s1);
    float b2 = SignedDistance(s2.p2, s1);

    return ((a1 >= 0 && b1 <= 0) || (a1 <= 0 && b1 >= 0)) &&
           ((a2 >= 0 && b2 <= 0) || (a2 <= 0 && b2 >= 0));
}

Vector2f Projection(const Vector2f& v, const LineSegment& axis_line) {
    Vector2f axis_vec = axis_line.p2 - axis_line.p1;
    return Projection(v, axis_vec);
}

Vector2f Projection(const Vector2f& v, Vector2f axis_vec) {
    float axis_vec_ls = axis_vec.squaredLength();
    return axis_vec * ((axis_vec * v) / axis_vec_ls);
}

void MoveableObject::move(const Vector2f& vector) {
    basepoint = basepoint + vector;
}