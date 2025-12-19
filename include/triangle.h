#include "figure.h"

class Triangle : public Figure {
private:
    Point vertices[3];
    
public:
    Triangle();
    Triangle(const Point points[3]);
    
    Point geometricCenter() const override;
    double getArea() const override;
    
    Triangle& operator=(const Figure& other) override;
    bool operator==(const Figure& other) const override;
    
    Triangle(const Triangle& other);
    Triangle& operator=(const Triangle& other);
    
    friend std::ostream& operator<<(std::ostream& os, const Triangle& tri);
    friend std::istream& operator>>(std::istream& is, Triangle& tri);
    
    const Point* getVertices() const { return vertices; }
};