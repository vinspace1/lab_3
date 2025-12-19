#include "figure.h"

class Square : public Figure {
private:
    Point vertices[4];
    
public:
    Square();
    Square(const Point points[4]);
    
    Point geometricCenter() const override;
    double getArea() const override;
    
    Square& operator=(const Figure& other) override;
    bool operator==(const Figure& other) const override;
    
    Square(const Square& other);
    Square& operator=(const Square& other);
    
    friend std::ostream& operator<<(std::ostream& os, const Square& sq);
    friend std::istream& operator>>(std::istream& is, Square& sq);
    
    const Point* getVertices() const { return vertices; }
};