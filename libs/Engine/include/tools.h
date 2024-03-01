#pragma once

#include <cmath>
#include <string>
#include <utility>
#include <vector>

extern inline const double PH_CONST_G = 9.81;
extern inline const double PH_CONST_COLLISION_PRES = 0.3;

/// немного структур с доп. функционалом

class vec {
   public:
    double x = 0, y = 0;

    // это и вектор, и точка, по сути. Просто понаписано всяких прикольных штук для удобства

    vec() : x(0), y(0) {
    }

    vec(double _x, double _y) : x(_x), y(_y) {
    }

    vec operator+(vec vect) {
        return vec(x + vect.x, y + vect.y);
    }

    vec operator-(vec vect) {
        return vec(x - vect.x, y - vect.y);
    }

    double operator*(vec vect) {
        return x * vect.x + y * vect.y;
    }

    vec operator*(double k) {
        return vec(x * k, y * k);
    }

    vec operator/(double k) {
        return vec(x / k, y / k);
    }

    double length() {
        return std::sqrt(x * x + y * y);
    }

    vec cord(int width, int height) const;  // преобразование из моих координат в сфмл

    vec anticord(int width, int height) const;  // обратное
};

class line {
   public:
    vec d1, d2;  // наш отрезочек тире текстура (ну а что, в три д у нас полигоны - часть плоскости,
                 // значит тут будет часть прямой - отрезок.

    line(vec p1, vec p2) : d1(p1), d2(p2){};

    line move(vec vector);
    vec norm();  // единичная нормаль к поверхности
};

// перегружаем одну функцию для всевозможных расстояний

double Distance(vec p1, vec p2);

double Distance(vec dot, line line);  // расстояние от точки до отрезка

double SignedDistance(vec dot, line line);  // знаковое расстояние от точки до отрезка(прямой)

inline double Distance(line line, vec dot) {
    return Distance(dot, line);
}

double Distance(
    line l1, line l2);  // расстояние от отрезка до отрезка (т.е минимальная длина отрезка, начало
                        // которого принадлежит первому отрезку, а конец - второму

bool IsIntersect(line l1, line l2);             // пересекаются ли отрезки

class Object;
bool IsCollide(Object* first, Object* second);  // соударяются ли объекты

/// новая концепция - объект. Самое главное это его основная точка (по ней потом будем сортировать
/// для оптимизирования отрисовки); Содержит в себе набор полигонов (линий), позже добавим текстуру

class Object {
   protected:
    friend bool IsCollide(Object* first, Object* second);
    friend class Engine;
    vec basepoint_;
    std::vector<line> polygons_;

   public:
    explicit Object(std::vector<line> polygons) : polygons_(std::move(polygons)) {
    }

    explicit Object(vec basepoint, std::vector<line> polygons);

    virtual ~Object() = default;
};

// идея: хранить отдельно паттерны, типо название объекта и его полигоны (относительно basepoint). А
// в списке текстур просто указывать название и basepoint. Load Надо будет еще поменять...

class MoveableObject : public Object {
   public:
    vec resultantForce;
    vec velocity;
    double mass = 1;

   public:
    void move(vec vector);

    explicit MoveableObject(vec basepoint, std::vector<line> polygons)
        : Object(basepoint, polygons) {
    }

    explicit MoveableObject(vec basepoint, std::vector<line> polygons, double m)
        : Object(basepoint, polygons), mass(m) {
    }
};