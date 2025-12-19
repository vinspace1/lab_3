#include "figure.h"

class FigureArray {
private:
    Figure** figures;
    int capacity;
    int size_;
    
    void resizeIfNeeded();
    
public:
    // Конструкторы и деструктор
    FigureArray();
    FigureArray(const FigureArray& other);
    ~FigureArray();
    
    // Оператор присваивания
    FigureArray& operator=(const FigureArray& other);
    
    // Добавление и удаление
    void addFigure(Figure* figure);
    void removeFigure(int index);
    
    // Доступ к элементам
    Figure* operator[](int index) const;
    
    // Информация о массиве
    int size() const;
    int getCapacity() const;
    bool empty() const;
    
    // Вычисления
    double totalArea() const;
    
    // Вывод
    void printAll() const;
    friend std::ostream& operator<<(std::ostream& os, const FigureArray& arr);
    
    // Управление памятью
    void clear();
};