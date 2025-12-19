#include "triangle.h"
#include <iostream>
#include <cmath>

Triangle::Triangle() {
    for (int i = 0; i < 3; i++) {
        vertices[i] = Point(0, 0);
    }
}

Triangle::Triangle(const Point points[3]) {
    for (int i = 0; i < 3; i++) {
        vertices[i] = points[i];
    }
}

Point Triangle::geometricCenter() const {
    double sumX = vertices[0].x + vertices[1].x + vertices[2].x;
    double sumY = vertices[0].y + vertices[1].y + vertices[2].y;
    return Point(sumX / 3, sumY / 3);
}

double Triangle::getArea() const {
    double area = vertices[0].x * (vertices[1].y - vertices[2].y) +
                  vertices[1].x * (vertices[2].y - vertices[0].y) +
                  vertices[2].x * (vertices[0].y - vertices[1].y);
    
    return std::abs(area) / 2.0;
}

Triangle& Triangle::operator=(const Figure& other) {
    if (this == &other) return *this;
    
    const Triangle* otherTri = dynamic_cast<const Triangle*>(&other);
    if (otherTri) {
        for (int i = 0; i < 3; i++) {
            vertices[i] = otherTri->vertices[i];
        }
    }
    return *this;
}

bool Triangle::operator==(const Figure& other) const {
    const Triangle* otherTri = dynamic_cast<const Triangle*>(&other);
    if (!otherTri) return false;
    
    for (int i = 0; i < 3; i++) {
        if (!(vertices[i] == otherTri->vertices[i])) {
            return false;
        }
    }
    return true;
}

Triangle::Triangle(const Triangle& other) {
    for (int i = 0; i < 3; i++) {
        vertices[i] = other.vertices[i];
    }
}

Triangle& Triangle::operator=(const Triangle& other) {
    if (this != &other) {
        for (int i = 0; i < 3; i++) {
            vertices[i] = other.vertices[i];
        }
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Triangle& tri) {
    os << "Triangle vertices: ";
    for (int i = 0; i < 3; i++) {
        os << tri.vertices[i];
        if (i < 2) os << " ";
    }
    return os;
}

std::istream& operator>>(std::istream& is, Triangle& tri) {
    for (int i = 0; i < 3; i++) {
        is >> tri.vertices[i];
    }
    return is;
}