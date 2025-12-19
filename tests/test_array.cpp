#include <gtest/gtest.h>
#include "array.h"
#include "octagon.h"
#include "triangle.h"
#include "square.h"
#include <stdexcept>

class FigureArrayTest : public ::testing::Test {
protected:
    FigureArray* array;
    
    void SetUp() override {
        array = new FigureArray();
        
        // Добавляем тестовые фигуры
        Point triPoints[3] = {Point(0, 0), Point(3, 0), Point(0, 4)};
        Point sqPoints[4] = {Point(0, 0), Point(2, 0), Point(2, 2), Point(0, 2)};
        Point octPoints[8];
        for (int i = 0; i < 8; i++) {
            octPoints[i] = Point(i, i);
        }
        
        array->addFigure(new Triangle(triPoints));
        array->addFigure(new Square(sqPoints));
        array->addFigure(new Octagon(octPoints));
    }
    
    void TearDown() override {
        delete array;
    }
};

TEST_F(FigureArrayTest, ConstructorAndSize) {
    EXPECT_EQ(array->size(), 3);
    EXPECT_FALSE(array->empty());
}

TEST_F(FigureArrayTest, AddFigure) {
    Point points[3] = {Point(1, 1), Point(4, 1), Point(1, 5)};
    array->addFigure(new Triangle(points));
    
    EXPECT_EQ(array->size(), 4);
}

TEST_F(FigureArrayTest, RemoveFigure) {
    array->removeFigure(0);
    EXPECT_EQ(array->size(), 2);
    array->removeFigure(1);
    EXPECT_EQ(array->size(), 1);
    
    EXPECT_NO_THROW(array->removeFigure(10));
    EXPECT_EQ(array->size(), 1);
    
    EXPECT_NO_THROW(array->removeFigure(-1));
    EXPECT_EQ(array->size(), 1);
}

TEST_F(FigureArrayTest, TotalArea) {
    double triangleArea = 6.0;
    double squareArea = 4.0;
    Point octPoints[8];
    for (int i = 0; i < 8; i++) {
        octPoints[i] = Point(i, i);
    }
    Octagon octagon(octPoints);
    double octagonArea = octagon.getArea();
    
    double expectedTotal = triangleArea + squareArea + octagonArea;
    EXPECT_DOUBLE_EQ(array->totalArea(), expectedTotal);
}

TEST_F(FigureArrayTest, AccessOperator) {
    EXPECT_NE((*array)[0], nullptr);
    EXPECT_NE((*array)[1], nullptr);
    EXPECT_NE((*array)[2], nullptr);
    
    EXPECT_EQ((*array)[10], nullptr);
    EXPECT_EQ((*array)[-1], nullptr);
    
    Figure* fig1 = (*array)[0];
    Figure* fig2 = (*array)[1];
    Figure* fig3 = (*array)[2];
    
    EXPECT_NE(dynamic_cast<Triangle*>(fig1), nullptr);
    EXPECT_NE(dynamic_cast<Square*>(fig2), nullptr);
    EXPECT_NE(dynamic_cast<Octagon*>(fig3), nullptr);
}

TEST_F(FigureArrayTest, Clear) {
    EXPECT_EQ(array->size(), 3);
    
    array->clear();
    EXPECT_EQ(array->size(), 0);
    EXPECT_TRUE(array->empty());
    EXPECT_DOUBLE_EQ(array->totalArea(), 0.0);
}

TEST_F(FigureArrayTest, OutputOperator) {
    std::stringstream ss;
    ss << *array;
    
    std::string result = ss.str();
    
    EXPECT_NE(result.find("Array of 3 figures"), std::string::npos);
    EXPECT_NE(result.find("Triangle"), std::string::npos);
    EXPECT_NE(result.find("Square"), std::string::npos);
    EXPECT_NE(result.find("Octagon"), std::string::npos);
    EXPECT_NE(result.find("Total area"), std::string::npos);
}

TEST_F(FigureArrayTest, CopyConstructor) {
    FigureArray array2(*array);
    
    EXPECT_EQ(array2.size(), 3);
    EXPECT_DOUBLE_EQ(array2.totalArea(), array->totalArea());
    
    array->removeFigure(0);
    EXPECT_EQ(array->size(), 2);
    EXPECT_EQ(array2.size(), 3);
}

TEST_F(FigureArrayTest, AssignmentOperator) {
    FigureArray array2;
    
    EXPECT_EQ(array2.size(), 0);
    array2 = *array;
    
    EXPECT_EQ(array2.size(), 3);
    EXPECT_DOUBLE_EQ(array2.totalArea(), array->totalArea());
    array->removeFigure(0);
    EXPECT_EQ(array->size(), 2);
    EXPECT_EQ(array2.size(), 3);
}

TEST_F(FigureArrayTest, EmptyArray) {
    FigureArray emptyArray;
    
    EXPECT_EQ(emptyArray.size(), 0);
    EXPECT_TRUE(emptyArray.empty());
    EXPECT_DOUBLE_EQ(emptyArray.totalArea(), 0.0);
    EXPECT_NO_THROW(emptyArray.removeFigure(0));
    EXPECT_NO_THROW(emptyArray.removeFigure(10));
    EXPECT_EQ(emptyArray[0], nullptr);
}

TEST_F(FigureArrayTest, AddNullptr) {
    int initialSize = array->size();
    array->addFigure(nullptr);

    EXPECT_EQ(array->size(), initialSize);
}

TEST(FigureArrayAdvancedTest, MixedOperations) {
    FigureArray arr;
    Point triPoints[3] = {Point(0, 0), Point(5, 0), Point(0, 5)};
    arr.addFigure(new Triangle(triPoints));

    EXPECT_EQ(arr.size(), 1);
    EXPECT_DOUBLE_EQ(arr.totalArea(), 12.5); 

    Point sqPoints[4] = {Point(0, 0), Point(3, 0), Point(3, 3), Point(0, 3)};
    arr.addFigure(new Square(sqPoints));

    EXPECT_EQ(arr.size(), 2);
    EXPECT_DOUBLE_EQ(arr.totalArea(), 12.5 + 9.0);

    arr.removeFigure(0);

    EXPECT_EQ(arr.size(), 1);
    EXPECT_DOUBLE_EQ(arr.totalArea(), 9.0);

    arr.clear();

    EXPECT_EQ(arr.size(), 0);
    EXPECT_DOUBLE_EQ(arr.totalArea(), 0.0);
}

TEST(FigureArrayAdvancedTest, CapacityManagement) {
    FigureArray arr;
    for (int i = 0; i < 20; i++) {
        Point triPoints[3] = {Point(0, 0), Point(1, 0), Point(0, 1)};
        arr.addFigure(new Triangle(triPoints));
    }

    EXPECT_EQ(arr.size(), 20);
    EXPECT_GE(arr.getCapacity(), 20);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}