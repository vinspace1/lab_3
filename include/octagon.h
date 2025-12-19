#include "figure.h"

class Octagon : public Figure {
private:
    Point vertices[8];
    
public:
    Octagon();
    Octagon(const Point points[8]);
    
    Point geometricCenter() const override;
    double getArea() const override;
    
    Octagon& operator=(const Figure& other) override;
    bool operator==(const Figure& other) const override;
    
    Octagon(const Octagon& other);
    Octagon& operator=(const Octagon& other);
    
    friend std::ostream& operator<<(std::ostream& os, const Octagon& oct);
    friend std::istream& operator>>(std::istream& is, Octagon& oct);
    
    const Point* getVertices() const { return vertices; }
};