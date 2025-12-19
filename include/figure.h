#pragma once

#include <iostream>
#include <cmath>

struct Point {
    double x, y;
    
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    
    bool operator==(const Point& other) const {
        return std::abs(x - other.x) < 1e-9 && std::abs(y - other.y) < 1e-9;
    }
    
    // Вывод точки
    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        os << p.x << " " << p.y;
        return os;
    }
    
    // Ввод точки
    friend std::istream& operator>>(std::istream& is, Point& p) {
        is >> p.x >> p.y;
        return is;
    }
};

class Figure {
public:
    virtual ~Figure() = default;
    
    virtual Point geometricCenter() const = 0;
    
    virtual double getArea() const = 0;

    virtual Figure& operator=(const Figure& other) = 0;
    virtual bool operator==(const Figure& other) const = 0;
    
    operator double() const {
        return getArea();
    }
};