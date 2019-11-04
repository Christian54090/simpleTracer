cmake_minimum_required(VERSION 3.15)
project(simpleTracer)

set(CMAKE_CXX_STANDARD 14)

add_executable(simpleTracer src/main.cpp src/Vec.h src/Shapes.cpp src/Shapes.h src/Texture.cpp src/Texture.h src/Light.cpp src/Light.h)