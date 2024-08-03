#pragma once

#include <cmath>
#include <vector>

#define math_sqrt(x) std::sqrt(x)
#define math_abs(x) std::abs(x)

#define nullvector Vector2f(0, 0)

extern inline const float kPhysConstG = 9.81f;
extern inline const float kPhysCollisionPres = 0.05f;
extern inline const float kEps = 1e-6;

// ----------------------------------------------------------------------
// Vector2f
// ----------------------------------------------------------------------
// Class Vector2f represents a vector or point in 2D space, depends on context.
// It has two float fields: x and y. It has methods for vector normalization,
// getting SFML coordinates, getting local coordinates, vector addition,
// subtraction, multiplication by scalar, division by scalar, comparison.
class Vector2f {
   public:
    float x{0};
    float y{0};

    Vector2f() = default;

    Vector2f(float _x, float _y) : x(_x), y(_y){};  // NOLINT

    [[nodiscard]] float length() const;

    [[nodiscard]] float squaredLength() const;  // avoid a sqrt

    Vector2f& normilize();

    // Arithmetic
    Vector2f& operator+=(const Vector2f& other);

    Vector2f& operator-=(const Vector2f& other);

    Vector2f& operator*=(float scalar);

    Vector2f& operator/=(float scalar);

    Vector2f& operator/=(const Vector2f& other);

    Vector2f operator+(const Vector2f& other) const;

    Vector2f operator-(const Vector2f& other) const;

    Vector2f operator*(float scalar) const;

    // dot product
    float operator*(const Vector2f& other) const;

    Vector2f operator/(float scalar) const;

    Vector2f operator/(const Vector2f& other) const;

    Vector2f operator-() const;

    friend Vector2f operator*(float scalar, const Vector2f& vector);

    // Comparison
    bool operator==(const Vector2f& other) const;

    bool operator!=(const Vector2f& other) const;

    [[nodiscard]] Vector2f getSfmlCords(int width, int height) const;

    [[nodiscard]] Vector2f getLocalCords(int width, int height) const;
};

// ----------------------------------------------------------------------
// LineSegment
// ----------------------------------------------------------------------
// Class Line represents a line segment. It has two fields: p1 and p2
// of type Point2f. It has methods for moving the line segment by a vector,
// getting the normal to the line segment, comparison.
class LineSegment {
   public:
    Vector2f p1;
    Vector2f p2;

    LineSegment(const Vector2f& _p1, const Vector2f& _p2) : p1(_p1), p2(_p2){};  // NOLINT

    [[nodiscard]] float squaredLength() const;

    // Get new segment moved by vector
    [[nodiscard]] LineSegment move(const Vector2f& vector) const;

    // Get normal to the line segment
    [[nodiscard]] Vector2f getNormal() const;

    // Comparison
    bool operator==(const LineSegment& other) const {
        return p1 == other.p1 && p2 == other.p2;
    }
};


// ----------------------------------------------------------------------
// Triangle
// ----------------------------------------------------------------------
// Class Triangle represents a triangle in 2D space. It has three fields:
// p1, p2, p3 of type Vector2f. It has a method for getting the double
// square of the triangle.
class Triangle {
   public:
    Vector2f p1, p2, p3;

    explicit Triangle(const Vector2f& _p1, const Vector2f& _p2, const Vector2f& _p3) // NOLINT
        : p1(_p1), p2(_p2), p3(_p3) {
    }

    [[nodiscard]] double doubleSquare(); // avoid division by 2
};

// ----------------------------------------------------------------------
// Quadrangle
// ----------------------------------------------------------------------
// Class Quadrangle represents a quadrangle in 2D space. It has four fields:
// p1, p2, p3, p4 of type Vector2f. It has a method for getting the double
// square of the quadrangle and a method for checking if a point is inside
// the quadrangle.
class Quadrangle {
   public:
    Vector2f p1, p2, p3, p4;

    explicit Quadrangle(const Vector2f& _p1, const Vector2f& _p2,  // NOLINT
                        const Vector2f& _p3, const Vector2f& _p4)  // NOLINT
        : p1(_p1), p2(_p2), p3(_p3), p4(_p4) {
    }

    virtual ~Quadrangle() = default;

    [[nodiscard]] virtual double doubleSquare(); // avoid division by 2

    [[nodiscard]] bool cover(const Vector2f& point);

    // Check if segment is inside quadrangle or half inside
    [[nodiscard]] bool cover(const LineSegment& segment);
};

// ----------------------------------------------------------------------
// Parallelogram
// ----------------------------------------------------------------------
// Class Parallelogram represents a parallelogram in 2D space. It has four fields:
// p1, p2, p3, p4 of type Vector2f. It inherits from class Quadrangle.
// It has a method for checking if a point is inside the parallelogram.
class Parallelogram : public Quadrangle {
   public:
    explicit Parallelogram(const Vector2f& _p1, const Vector2f& _p2,  // NOLINT
                           const Vector2f& _p3, const Vector2f& _p4)  // NOLINT
        : Quadrangle(_p1, _p2, _p3, _p4) {
    }

    [[nodiscard]] double doubleSquare() override;
};

// ----------------------------------------------------------------------
// Math functions
// ----------------------------------------------------------------------
float Distance(const Vector2f& p1, const Vector2f& p2);

float Distance(const Vector2f& point, const LineSegment& segment);

inline float Distance(const LineSegment& segment, const Vector2f& point) {
    return Distance(point, segment);
}

float SignedDistance(const Vector2f& point, const LineSegment& segment);

float Distance(const LineSegment& s1, const LineSegment& s2);

bool IsIntersect(const LineSegment& l1, const LineSegment& l2);

Vector2f Projection(const Vector2f& v, const LineSegment& axis);

Vector2f Projection(const Vector2f& v, Vector2f axis_vec);

// ----------------------------------------------------------------------
// Object
// ----------------------------------------------------------------------
// Class Object represents a static object in 2D space. It has two fields:
// basepoint of type Point2f and polygons of type std::vector<LineSegment>.
// It has a constructor that initializes the fields. It has a friend class
// Engine.
class Object {
   public:
    explicit Object(
        const Vector2f& _basepoint, const std::vector<LineSegment>& _polygons)  // NOLINT
        : basepoint(_basepoint), polygons(_polygons) {
    }

    virtual ~Object() = default;

    Vector2f basepoint;
    std::vector<LineSegment> polygons;
};

// ----------------------------------------------------------------------
// MoveableObject
// ----------------------------------------------------------------------
// Class MoveableObject represents a moveable object in 2D space. It has
// fields: resultantForce, velocity, magicForces, mass, frictionCoef,
// isInTouch. It has methods: move, sumNormalForces. It has a constructor
// that initializes the fields. It inherits from class Object.
class MoveableObject : public Object {
   public:
    Vector2f resultant_force;
    Vector2f velocity;
    Vector2f magic_force;
    float mass{0.f};
    float friction_coef{1.f};
    bool is_in_touch{false};

    void move(const Vector2f& vector);

    explicit MoveableObject(const Vector2f& basepoint, const std::vector<LineSegment>& polygons)
        : Object(basepoint, polygons) {
    }

    explicit MoveableObject(
        const Vector2f& basepoint, const std::vector<LineSegment>& polygons, float m)
        : Object(basepoint, polygons), mass(m) {
    }
};