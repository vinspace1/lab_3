cmake_minimum_required(VERSION 3.14)
project(GeometryFigures)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Основное приложение
add_executable(geometry_app
    src/main.cpp
    src/octagon.cpp
    src/triangle.cpp
    src/square.cpp
    src/array.cpp
)

target_include_directories(geometry_app PRIVATE include)

# Юнит-тесты
enable_testing()

# Загружаем GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

# Тесты для фигур
add_executable(figure_tests
    tests/test_figures.cpp
    src/octagon.cpp
    src/triangle.cpp
    src/square.cpp
    src/array.cpp
)

target_include_directories(figure_tests PRIVATE include)
target_link_libraries(figure_tests GTest::gtest GTest::gtest_main)

# Тесты для массива
add_executable(array_tests
    tests/test_array.cpp
    src/octagon.cpp
    src/triangle.cpp
    src/square.cpp
    src/array.cpp
)

target_include_directories(array_tests PRIVATE include)
target_link_libraries(array_tests GTest::gtest GTest::gtest_main)

# Регистрируем тесты
add_test(NAME FigureTests COMMAND figure_tests)
add_test(NAME ArrayTests COMMAND array_tests)