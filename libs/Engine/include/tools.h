#pragma once

#include <cmath>
#include <string>
#include <utility>
#include <vector>

/// немного структур с доп. функционалом

class vec {
   public:
    double x = 0, y = 0;
    // это и вектор, и точка, по сути. ѕросто понаписано вс€ких прикольных штук дл€ удобства

    vec(double _x, double _y) : x(_x), y(_y){};

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
                 // значит тут будет часть пр€мой - отрезок.

    line(vec p1, vec p2) : d1(p1), d2(p2){};

    line move(vec vector);
    vec norm();  // единична€ нормаль к поверхности
};

// перегружаем одну функцию дл€ всевозможных рассто€ний

double Distance(vec p1, vec p2);

double Distance(vec dot, line line);  // рассто€ние от точки до отрезка

double SignedDistance(vec dot, line line);  // знаковое рассто€ние от точки до отрезка(пр€мой)

inline double Distance(line line, vec dot) {
    return Distance(dot, line);
}

double Distance(
    line l1, line l2);  // рассто€ние от отрезка до отрезка (т.е минимальна€ длина отрезка, начало
                        // которого принадлежит первому отрезку, а конец - второму

bool IsIntersect(line l1, line l2);  // пересекаютс€ ли отрезки

/// нова€ концепци€ - объект. —амое главное это его основна€ точка (по ней потом будем сортировать
/// дл€ оптимизировани€ отрисовки); —одержит в себе набор полигонов (линий), позже добавим текстуру

class Object {
   private:
    friend class Engine;
    vec basepoint_;
    std::vector<line> polygons_;

   public:
    void move(vec vector);

    explicit Object(std::vector<line> polygons) : basepoint_(0, 0), polygons_(std::move(polygons)) {
    }

    explicit Object(vec basepoint, std::vector<line> polygons);
};

// иде€: хранить отдельно паттерны, типо название объекта и его полигоны (относительно basepoint). ј
// в списке текстур просто указывать название и basepoint. Load Ќадо будет еще помен€ть...