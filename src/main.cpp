#include "octagon.h"
#include "triangle.h"
#include "square.h"
#include "array.h"
#include <iostream>
#include <string>

void demonstrateAllRequirements() {
    std::cout << "=== DEMONSTRATION OF ALL REQUIREMENTS ===\n\n";
    
    // 1. Создание фигур
    std::cout << "1. CREATING FIGURES:\n";
    
    Point trianglePoints[3] = {Point(0,0), Point(4,0), Point(0,3)};
    Triangle tri(trianglePoints);
    
    Point squarePoints[4] = {Point(0,0), Point(3,0), Point(3,3), Point(0,3)};
    Square sq(squarePoints);
    
    Point octagonPoints[8] = {
        Point(0,0), Point(2,0), Point(3,1), Point(3,3),
        Point(2,4), Point(0,4), Point(-1,3), Point(-1,1)
    };
    Octagon oct(octagonPoints);
    
    // 2. Демонстрация оператора << (вывод вершин)
    std::cout << "2. OPERATOR << (OUTPUT VERTICES):\n";
    std::cout << "Triangle: " << tri << "\n";
    std::cout << "Square: " << sq << "\n";
    std::cout << "Octagon: " << oct << "\n\n";
    
    // 3. Демонстрация геометрического центра
    std::cout << "3. GEOMETRIC CENTER:\n";
    std::cout << "Triangle center: " << tri.geometricCenter() << "\n";
    std::cout << "Square center: " << sq.geometricCenter() << "\n";
    std::cout << "Octagon center: " << oct.geometricCenter() << "\n\n";
    
    // 4. Демонстрация оператора приведения к double (площадь)
    std::cout << "4. OPERATOR double() (AREA):\n";
    std::cout << "Triangle area: " << static_cast<double>(tri) << "\n";
    std::cout << "Square area: " << static_cast<double>(sq) << "\n";
    std::cout << "Octagon area: " << static_cast<double>(oct) << "\n\n";
    
    // 5. Демонстрация оператора >> (чтение)
    std::cout << "5. OPERATOR >> (READING):\n";
    
    Triangle newTri;
    std::cout << "Enter 3 points for triangle (x1 y1 x2 y2 x3 y3): ";
    std::cin >> newTri;
    
    std::cout << "You entered: " << newTri << "\n";
    std::cout << "Its area: " << static_cast<double>(newTri) << "\n\n";
    
    // 6. Работа с массивом
    std::cout << "6. WORKING WITH ARRAY:\n";
    FigureArray array;
    array.addFigure(new Triangle(tri));
    array.addFigure(new Square(sq));
    array.addFigure(new Octagon(oct));
    array.addFigure(new Triangle(newTri));
    
    std::cout << array;
    
    // 7. Удаление из массива
    std::cout << "7. REMOVING FIGURE FROM ARRAY:\n";
    array.removeFigure(1);
    std::cout << "After removing index 1:\n";
    std::cout << array;
}

int main() {
    demonstrateAllRequirements();
    return 0;
}