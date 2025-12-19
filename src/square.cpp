#include "square.h"
#include <iostream>
#include <cmath>

Square::Square() {
    for (int i = 0; i < 4; i++) {
        vertices[i] = Point(0, 0);
    }
}

Square::Square(const Point points[4]) {
    for (int i = 0; i < 4; i++) {
        vertices[i] = points[i];
    }
}

Point Square::geometricCenter() const {
    double sumX = 0, sumY = 0;
    for (int i = 0; i < 4; i++) {
        sumX += vertices[i].x;
        sumY += vertices[i].y;
    }
    return Point(sumX / 4, sumY / 4);
}

double Square::getArea() const {
    double area = 0;
    
    for (int i = 0; i < 4; i++) {
        int j = (i + 1) % 4;
        area += vertices[i].x * vertices[j].y;
        area -= vertices[j].x * vertices[i].y;
    }
    
    return std::abs(area) / 2.0;
}

Square& Square::operator=(const Figure& other) {
    if (this == &other) return *this;
    
    const Square* otherSq = dynamic_cast<const Square*>(&other);
    if (otherSq) {
        for (int i = 0; i < 4; i++) {
            vertices[i] = otherSq->vertices[i];
        }
    }
    return *this;
}

bool Square::operator==(const Figure& other) const {
    const Square* otherSq = dynamic_cast<const Square*>(&other);
    if (!otherSq) return false;
    
    for (int i = 0; i < 4; i++) {
        if (!(vertices[i] == otherSq->vertices[i])) {
            return false;
        }
    }
    return true;
}

Square::Square(const Square& other) {
    for (int i = 0; i < 4; i++) {
        vertices[i] = other.vertices[i];
    }
}

Square& Square::operator=(const Square& other) {
    if (this != &other) {
        for (int i = 0; i < 4; i++) {
            vertices[i] = other.vertices[i];
        }
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Square& sq) {
    os << "Square vertices: ";
    for (int i = 0; i < 4; i++) {
        os << sq.vertices[i];
        if (i < 3) os << " ";
    }
    return os;
}

std::istream& operator>>(std::istream& is, Square& sq) {
    for (int i = 0; i < 4; i++) {
        is >> sq.vertices[i];
    }
    return is;
}