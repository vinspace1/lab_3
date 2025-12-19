#include "figure.h"

class FigureArray {
private:
    Figure** figures;
    int capacity;
    int size_;
    
    void resizeIfNeeded();
    
public:
    FigureArray();
    FigureArray(const FigureArray& other);
    ~FigureArray();
    
    FigureArray& operator=(const FigureArray& other);
    
    void addFigure(Figure* figure);
    void removeFigure(int index);
    
    Figure* operator[](int index) const;
    
    int size() const;
    int getCapacity() const;
    bool empty() const;
    
    double totalArea() const;
    
    void printAll() const;
    friend std::ostream& operator<<(std::ostream& os, const FigureArray& arr);
    
    void clear();
};