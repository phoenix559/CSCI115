cmake_minimum_required(VERSION 4.3)
project(Lab_2)

set(CMAKE_CXX_STANDARD 20)

add_executable(Lab_2 main.cpp
        ThreeDArray.h
        ThreeDArray.cpp
        "../Lab 1/MyArray.cpp"
        "../Lab 1/MyArray.h"
)
