#include "octagon.h"
#include <iostream>
#include <cmath>

Octagon::Octagon() {
    for (int i = 0; i < 8; i++) {
        vertices[i] = Point(0, 0);
    }
}

Octagon::Octagon(const Point points[8]) {
    for (int i = 0; i < 8; i++) {
        vertices[i] = points[i];
    }
}

Point Octagon::geometricCenter() const {
    double sumX = 0, sumY = 0;
    for (int i = 0; i < 8; i++) {
        sumX += vertices[i].x;
        sumY += vertices[i].y;
    }
    return Point(sumX / 8, sumY / 8);
}

double Octagon::getArea() const {
    double area = 0;
    
    for (int i = 0; i < 8; i++) {
        int j = (i + 1) % 8;
        area += vertices[i].x * vertices[j].y;
        area -= vertices[j].x * vertices[i].y;
    }
    
    return std::abs(area) / 2.0;
}

Octagon& Octagon::operator=(const Figure& other) {
    if (this == &other) return *this;
    
    const Octagon* otherOct = dynamic_cast<const Octagon*>(&other);
    if (otherOct) {
        for (int i = 0; i < 8; i++) {
            vertices[i] = otherOct->vertices[i];
        }
    }
    return *this;
}

bool Octagon::operator==(const Figure& other) const {
    const Octagon* otherOct = dynamic_cast<const Octagon*>(&other);
    if (!otherOct) return false;
    
    for (int i = 0; i < 8; i++) {
        if (!(vertices[i] == otherOct->vertices[i])) {
            return false;
        }
    }
    return true;
}

Octagon::Octagon(const Octagon& other) {
    for (int i = 0; i < 8; i++) {
        vertices[i] = other.vertices[i];
    }
}

Octagon& Octagon::operator=(const Octagon& other) {
    if (this != &other) {
        for (int i = 0; i < 8; i++) {
            vertices[i] = other.vertices[i];
        }
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Octagon& oct) {
    os << "Octagon vertices: ";
    for (int i = 0; i < 8; i++) {
        os << oct.vertices[i];
        if (i < 7) os << " ";
    }
    return os;
}

std::istream& operator>>(std::istream& is, Octagon& oct) {
    for (int i = 0; i < 8; i++) {
        is >> oct.vertices[i];
    }
    return is;
}