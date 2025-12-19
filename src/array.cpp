#include "array.h"
#include "octagon.h"
#include "triangle.h"
#include "square.h"
#include <iostream>

const int INITIAL_CAPACITY = 10;

// Приватные методы
void FigureArray::resizeIfNeeded() {
    if (size_ >= capacity) {
        int newCapacity = capacity * 2;
        if (newCapacity <= capacity) newCapacity = capacity + 1;
        
        Figure** newFigures = new Figure*[newCapacity];
        
        // Копируем существующие указатели
        for (int i = 0; i < size_; i++) {
            newFigures[i] = figures[i];
        }
        
        // Инициализируем остальные nullptr
        for (int i = size_; i < newCapacity; i++) {
            newFigures[i] = nullptr;
        }
        
        // Освобождаем старый массив
        delete[] figures;
        
        // Обновляем указатель и вместимость
        figures = newFigures;
        capacity = newCapacity;
    }
}

// Публичные методы

// Конструктор по умолчанию
FigureArray::FigureArray() 
    : figures(new Figure*[INITIAL_CAPACITY])
    , capacity(INITIAL_CAPACITY)
    , size_(0) 
{
    for (int i = 0; i < capacity; i++) {
        figures[i] = nullptr;
    }
}

// Конструктор копирования (глубокое копирование)
FigureArray::FigureArray(const FigureArray& other) 
    : figures(new Figure*[other.capacity])
    , capacity(other.capacity)
    , size_(other.size_) 
{
    // Создаем глубокие копии всех фигур
    for (int i = 0; i < size_; i++) {
        if (other.figures[i]) {
            // Определяем тип фигуры и создаем копию
            if (auto oct = dynamic_cast<Octagon*>(other.figures[i])) {
                figures[i] = new Octagon(*oct);
            } else if (auto tri = dynamic_cast<Triangle*>(other.figures[i])) {
                figures[i] = new Triangle(*tri);
            } else if (auto sq = dynamic_cast<Square*>(other.figures[i])) {
                figures[i] = new Square(*sq);
            } else {
                figures[i] = nullptr;
            }
        } else {
            figures[i] = nullptr;
        }
    }
    
    // Инициализируем остальные ячейки nullptr
    for (int i = size_; i < capacity; i++) {
        figures[i] = nullptr;
    }
}

// Деструктор
FigureArray::~FigureArray() {
    clear();
    delete[] figures;
}

// Оператор присваивания (глубокое копирование)
FigureArray& FigureArray::operator=(const FigureArray& other) {
    if (this != &other) {
        // Создаем временную копию
        FigureArray temp(other);
        
        // Обмениваем ресурсы
        Figure** tempFigures = figures;
        int tempCapacity = capacity;
        int tempSize = size_;
        
        figures = temp.figures;
        capacity = temp.capacity;
        size_ = temp.size_;
        
        temp.figures = tempFigures;
        temp.capacity = tempCapacity;
        temp.size_ = tempSize;
        
        // Временный объект уничтожится с нашими старыми ресурсами
    }
    return *this;
}

// Добавление фигуры
void FigureArray::addFigure(Figure* figure) {
    if (!figure) return; // Не добавляем nullptr
    
    resizeIfNeeded();
    figures[size_] = figure;
    size_++;
}

// Удаление фигуры по индексу
void FigureArray::removeFigure(int index) {
    if (index < 0 || index >= size_) return;
    
    // Удаляем фигуру
    delete figures[index];
    
    // Сдвигаем остальные элементы
    for (int i = index; i < size_ - 1; i++) {
        figures[i] = figures[i + 1];
    }
    
    // Обнуляем последний элемент и уменьшаем размер
    figures[size_ - 1] = nullptr;
    size_--;
}

// Доступ к элементам
Figure* FigureArray::operator[](int index) const {
    if (index < 0 || index >= size_) return nullptr;
    return figures[index];
}

// Размер массива
int FigureArray::size() const {
    return size_;
}

// Вместимость массива
int FigureArray::getCapacity() const {
    return capacity;
}

// Проверка на пустоту
bool FigureArray::empty() const {
    return size_ == 0;
}

// Вычисление общей площади
double FigureArray::totalArea() const {
    double total = 0.0;
    for (int i = 0; i < size_; i++) {
        if (figures[i]) {
            total += static_cast<double>(*figures[i]);
        }
    }
    return total;
}

// Вывод информации о всех фигурах (старый метод)
void FigureArray::printAll() const {
    std::cout << "=== Figures in array (" << size_ << " items) ===\n";
    
    if (empty()) {
        std::cout << "Array is empty.\n";
        return;
    }
    
    for (int i = 0; i < size_; i++) {
        std::cout << "[" << (i + 1) << "] ";
        if (figures[i]) {
            // Определяем тип фигуры
            if (dynamic_cast<Octagon*>(figures[i])) {
                std::cout << "Octagon: ";
            } else if (dynamic_cast<Triangle*>(figures[i])) {
                std::cout << "Triangle: ";
            } else if (dynamic_cast<Square*>(figures[i])) {
                std::cout << "Square: ";
            }
            
            // Выводим фигуру через оператор <<
            std::cout << *figures[i] << "\n";
            
            // Выводим геометрический центр
            std::cout << "   Center: " << figures[i]->geometricCenter() << "\n";
            
            // Выводим площадь
            std::cout << "   Area: " << static_cast<double>(*figures[i]) << "\n\n";
        } else {
            std::cout << "[nullptr]\n";
        }
    }
    
    std::cout << "Total area: " << totalArea() << "\n";
    std::cout << "================================\n";
}

// Очистка массива
void FigureArray::clear() {
    for (int i = 0; i < size_; i++) {
        delete figures[i];
        figures[i] = nullptr;
    }
    size_ = 0;
}

// Оператор вывода для массива
std::ostream& operator<<(std::ostream& os, const FigureArray& arr) {
    os << "=== Array of " << arr.size_ << " figures ===\n";
    
    if (arr.empty()) {
        os << "Array is empty.\n";
        os << "================================\n";
        return os;
    }
    
    for (int i = 0; i < arr.size_; i++) {
        if (arr.figures[i]) {
            os << "[" << (i + 1) << "] ";
            
            // Определяем тип фигуры
            if (dynamic_cast<Octagon*>(arr.figures[i])) {
                os << "Octagon: ";
            } else if (dynamic_cast<Triangle*>(arr.figures[i])) {
                os << "Triangle: ";
            } else if (dynamic_cast<Square*>(arr.figures[i])) {
                os << "Square: ";
            }
            
            // Выводим фигуру
            os << *arr.figures[i] << "\n";
            
            // Выводим геометрический центр
            os << "   Center: " << arr.figures[i]->geometricCenter() << "\n";
            
            // Выводим площадь
            os << "   Area: " << static_cast<double>(*arr.figures[i]) << "\n\n";
        }
    }
    
    os << "Total area: " << arr.totalArea() << "\n";
    os << "Capacity: " << arr.capacity << "\n";
    os << "================================\n";
    
    return os;
}