#include <gtest/gtest.h>
#include "octagon.h"
#include "triangle.h"
#include "square.h"
#include <sstream>
#include <cmath>

TEST(PointTest, ConstructorAndEquality) {
    Point p1(1.0, 2.0);
    EXPECT_DOUBLE_EQ(p1.x, 1.0);
    EXPECT_DOUBLE_EQ(p1.y, 2.0);
    
    Point p2(1.0, 2.0);
    Point p3(1.1, 2.0);
    
    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
}

TEST(PointTest, StreamOperators) {
    Point p(3.5, 4.2);
    
    std::stringstream ss;
    ss << p;
    EXPECT_EQ(ss.str(), "3.5 4.2");
    
    Point p2;
    std::stringstream input("5.5 6.6");
    input >> p2;
    EXPECT_DOUBLE_EQ(p2.x, 5.5);
    EXPECT_DOUBLE_EQ(p2.y, 6.6);
}

TEST(TriangleTest, Constructor) {
    Point points[3] = {Point(0, 0), Point(4, 0), Point(0, 3)};
    Triangle triangle(points);
    
    const Point* vertices = triangle.getVertices();
    EXPECT_DOUBLE_EQ(vertices[0].x, 0);
    EXPECT_DOUBLE_EQ(vertices[0].y, 0);
    EXPECT_DOUBLE_EQ(vertices[1].x, 4);
    EXPECT_DOUBLE_EQ(vertices[1].y, 0);
    EXPECT_DOUBLE_EQ(vertices[2].x, 0);
    EXPECT_DOUBLE_EQ(vertices[2].y, 3);
}

TEST(TriangleTest, GeometricCenter) {
    Point points[3] = {Point(0, 0), Point(6, 0), Point(0, 8)};
    Triangle triangle(points);
    
    Point center = triangle.geometricCenter();
    EXPECT_DOUBLE_EQ(center.x, 2.0);
    EXPECT_DOUBLE_EQ(center.y, 8.0/3.0); 
}

TEST(TriangleTest, Area) {
    Point points[3] = {Point(0, 0), Point(5, 0), Point(0, 4)};
    Triangle triangle(points);
    
    EXPECT_DOUBLE_EQ(triangle.getArea(), 10.0);
}

TEST(TriangleTest, DoubleCastOperator) {
    Point points[3] = {Point(0, 0), Point(3, 0), Point(0, 4)};
    Triangle triangle(points);
    
    double area = static_cast<double>(triangle);
    EXPECT_DOUBLE_EQ(area, 6.0); 
}

TEST(TriangleTest, OutputOperator) {
    Point points[3] = {Point(1, 2), Point(3, 4), Point(5, 6)};
    Triangle triangle(points);
    std::stringstream ss;
    ss << triangle; 
    std::string result = ss.str();

    EXPECT_NE(result.find("Triangle vertices:"), std::string::npos);
    EXPECT_NE(result.find("1 2"), std::string::npos);
    EXPECT_NE(result.find("3 4"), std::string::npos);
    EXPECT_NE(result.find("5 6"), std::string::npos);
}

TEST(TriangleTest, InputOperator) {
    Triangle triangle;
    std::stringstream input("1 2 3 4 5 6");
    input >> triangle;
    
    const Point* vertices = triangle.getVertices();
    EXPECT_DOUBLE_EQ(vertices[0].x, 1);
    EXPECT_DOUBLE_EQ(vertices[0].y, 2);
    EXPECT_DOUBLE_EQ(vertices[1].x, 3);
    EXPECT_DOUBLE_EQ(vertices[1].y, 4);
    EXPECT_DOUBLE_EQ(vertices[2].x, 5);
    EXPECT_DOUBLE_EQ(vertices[2].y, 6);
}

TEST(TriangleTest, CopyConstructor) {
    Point points[3] = {Point(0, 0), Point(4, 0), Point(0, 3)};
    Triangle triangle1(points);
    
    Triangle triangle2 = triangle1;
    
    EXPECT_TRUE(triangle1 == triangle2);
    EXPECT_DOUBLE_EQ(triangle2.getArea(), 6.0);
}

TEST(TriangleTest, AssignmentOperator) {
    Point points1[3] = {Point(0, 0), Point(4, 0), Point(0, 3)};
    Point points2[3] = {Point(1, 1), Point(5, 1), Point(1, 4)};
    
    Triangle triangle1(points1);
    Triangle triangle2(points2);
    
    triangle2 = triangle1;
    EXPECT_TRUE(triangle1 == triangle2);
}

TEST(SquareTest, ConstructorAndArea) {
    Point points[4] = {Point(0, 0), Point(4, 0), Point(4, 4), Point(0, 4)};
    Square square(points);
    
    EXPECT_DOUBLE_EQ(square.getArea(), 16.0); 
}

TEST(SquareTest, GeometricCenter) {
    Point points[4] = {Point(0, 0), Point(6, 0), Point(6, 6), Point(0, 6)};
    Square square(points);
    
    Point center = square.geometricCenter();
    EXPECT_DOUBLE_EQ(center.x, 3.0);
    EXPECT_DOUBLE_EQ(center.y, 3.0);
}

TEST(SquareTest, DoubleCast) {
    Point points[4] = {Point(0, 0), Point(3, 0), Point(3, 3), Point(0, 3)};
    Square square(points);
    
    double area = static_cast<double>(square);
    EXPECT_DOUBLE_EQ(area, 9.0);
}

TEST(SquareTest, StreamOperators) {
    Square square;
    std::stringstream input("0 0 2 0 2 2 0 2");
    input >> square;
    
    std::stringstream output;
    output << square;
    
    std::string result = output.str();
    EXPECT_NE(result.find("Square vertices:"), std::string::npos);
    EXPECT_NE(result.find("0 0"), std::string::npos);
    EXPECT_NE(result.find("2 2"), std::string::npos);
}

TEST(OctagonTest, ConstructorAndArea) {
    Point points[8];
    for (int i = 0; i < 8; i++) {
        double angle = 2 * M_PI * i / 8;
        points[i] = Point(cos(angle), sin(angle));
    }
    
    Octagon octagon(points);
    
    double expectedArea = 2 * sqrt(2); 
    EXPECT_NEAR(octagon.getArea(), expectedArea, 1e-9);
}

TEST(OctagonTest, GeometricCenter) {
    Point points[8];
    for (int i = 0; i < 8; i++) {
        points[i] = Point(i, i*2);
    }
    
    Octagon octagon(points);
    Point center = octagon.geometricCenter();
    
    double expectedX = (0+1+2+3+4+5+6+7) / 8.0;
    double expectedY = (0+2+4+6+8+10+12+14) / 8.0;
    
    EXPECT_DOUBLE_EQ(center.x, expectedX);
    EXPECT_DOUBLE_EQ(center.y, expectedY);
}

TEST(OctagonTest, StreamOperators) {
    Octagon octagon;
    std::stringstream input("0 0 1 0 2 1 2 2 1 3 0 3 -1 2 -1 1");
    input >> octagon;
    
    std::stringstream output;
    output << octagon;
    
    std::string result = output.str();
    EXPECT_NE(result.find("Octagon vertices:"), std::string::npos);
}

// Тесты полиморфизма
TEST(PolymorphismTest, FigurePointers) {
    Point triPoints[3] = {Point(0, 0), Point(3, 0), Point(0, 4)};
    Point sqPoints[4] = {Point(0, 0), Point(2, 0), Point(2, 2), Point(0, 2)};
    
    Triangle triangle(triPoints);
    Square square(sqPoints);
    
    Figure* fig1 = &triangle;
    Figure* fig2 = &square;
    
    EXPECT_DOUBLE_EQ(fig1->getArea(), 6.0);
    EXPECT_DOUBLE_EQ(fig2->getArea(), 4.0); 
    
    double area1 = static_cast<double>(*fig1);
    double area2 = static_cast<double>(*fig2);
    EXPECT_DOUBLE_EQ(area1, 6.0);
    EXPECT_DOUBLE_EQ(area2, 4.0);

    Point center1 = fig1->geometricCenter();
    EXPECT_DOUBLE_EQ(center1.x, 1.0); 
    EXPECT_DOUBLE_EQ(center1.y, 4.0/3.0); 
}

TEST(PolymorphismTest, OutputThroughBasePointer) {
    Point triPoints[3] = {Point(0, 0), Point(3, 0), Point(0, 4)};
    Triangle triangle(triPoints);
    
    Figure* fig = &triangle;
    
    std::stringstream ss;
    ss << *fig;
    
    std::string result = ss.str();
    
    double expectedArea = 6.0;
    std::stringstream expected;
    expected << expectedArea;
    
    EXPECT_EQ(result, expected.str());
    EXPECT_NE(result.find("6"), std::string::npos);
}

TEST(PolymorphismTest, DifferentTypesNotEqual) {
    Point triPoints[3] = {Point(0, 0), Point(3, 0), Point(0, 4)};
    Point sqPoints[4] = {Point(0, 0), Point(2, 0), Point(2, 2), Point(0, 2)};
    
    Triangle triangle(triPoints);
    Square square(sqPoints);
    
    EXPECT_FALSE(triangle == square);
    
    Figure* fig1 = &triangle;
    Figure* fig2 = &square;
    EXPECT_FALSE(*fig1 == *fig2);
}

TEST(EdgeCasesTest, DegenerateTriangle) {
    Point points[3] = {Point(0, 0), Point(2, 2), Point(4, 4)}; 
    Triangle triangle(points);

    EXPECT_DOUBLE_EQ(triangle.getArea(), 0.0);
}

TEST(EdgeCasesTest, LargeCoordinates) {
    Point points[3] = {Point(1e6, 1e6), Point(1e6 + 1000, 1e6), Point(1e6, 1e6 + 1000)};
    Triangle triangle(points);
    
    EXPECT_DOUBLE_EQ(triangle.getArea(), 500000.0);
}

TEST(EdgeCasesTest, SelfAssignment) {
    Point points[3] = {Point(0, 0), Point(3, 0), Point(0, 4)};
    Triangle triangle(points);
    
    Figure& fig = triangle;
    fig = fig;
    
    EXPECT_DOUBLE_EQ(triangle.getArea(), 6.0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}