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

    // это и вектор, и точка, по сути. ѕросто понаписано вс€ких прикольных штук дл€ удобства

    vec() : x(0), y(0) {
    }

    vec(double _x, double _y) : x(_x), y(_y) {
    }

    vec operator+(const vec& vect) const {
        return vec(x + vect.x, y + vect.y);
    }

    vec operator-(const vec& vect) const {
        return vec(x - vect.x, y - vect.y);
    }

    double operator*(const vec& vect) const {
        return x * vect.x + y * vect.y;
    }

    vec operator*(double k) const {
        return vec(x * k, y * k);
    }

    vec operator/(double k) const {
        return vec(x / k, y / k);
    }

    bool operator==(const vec& other) const {
        return abs(x - other.x) <= 0.0001 && abs(y - other.y) <= 0.0001;
    }

    double length() const {
        return std::sqrt(x * x + y * y);
    }

    vec cord(int width, int height) const;  // преобразование из моих координат в сфмл

    vec anticord(int width, int height) const;  // обратное
};

class line {
   public:
    vec d1, d2;  // наш отрезочек тире текстура (ну а что, в три д у нас полигоны - часть плоскости,
                 // значит тут будет часть пр€мой - отрезок.

    line(const vec& p1, const vec& p2) : d1(p1), d2(p2){};

    line move(const vec& vector) const;
    vec norm() const;  // единична€ нормаль к поверхности

    bool operator==(const line& other) const {
        return d1 == other.d1 && d2 == other.d2;
    }
};

// перегружаем одну функцию дл€ всевозможных рассто€ний

double Distance(const vec& p1, const vec& p2);

double Distance(const vec& dot, const line& line);  // рассто€ние от точки до отрезка

double SignedDistance(
    const vec& dot, const line& line);  // знаковое рассто€ние от точки до отрезка(пр€мой)

inline double Distance(const line& line, const vec& dot) {
    return Distance(dot, line);
}

double Distance(const line& l1, const line& l2);  // рассто€ние от отрезка до отрезка (т.е
                                                  // минимальна€ длина отрезка,
// начало
// которого принадлежит первому отрезку, а конец - второму

bool IsIntersect(const line& l1, const line& l2);  // пересекаютс€ ли отрезки

vec Proection(const vec& what, const line& axis);

vec Proection(const vec& what, vec vaxis);

/// нова€ концепци€ - объект. —амое главное это его основна€ точка (по ней потом будем сортировать
/// дл€ оптимизировани€ отрисовки); —одержит в себе набор полигонов (линий), позже добавим текстуру

class Object {
   protected:
    friend class Engine;
    vec basepoint_;
    std::vector<line> polygons_;

   public:
    explicit Object(const vec& basepoint, const std::vector<line>& polygons)
        : basepoint_(basepoint), polygons_(polygons) {
    }

    virtual ~Object() = default;
};

// иде€: хранить отдельно паттерны, типо название объекта и его полигоны (относительно basepoint). ј
// в списке текстур просто указывать название и basepoint. Load Ќадо будет еще помен€ть...

class MoveableObject : public Object {
   public:
    vec resultantForce;
    vec velocity;
    double mass = 0;
    vec magicForces;
    double frictionCoef = 0;

   public:
    void move(const vec& vector);

    void SumNormalForces(const vec& basepoint, const std::vector<line>& polygons);

    explicit MoveableObject(const vec& basepoint, const std::vector<line>& polygons)
        : Object(basepoint, polygons) {
    }

    explicit MoveableObject(const vec& basepoint, const std::vector<line>& polygons, double m)
        : Object(basepoint, polygons), mass(m) {
    }
};