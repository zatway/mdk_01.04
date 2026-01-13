cmake_minimum_required(VERSION 4.0)
project(PR_11)

set(CMAKE_CXX_STANDARD 20)

add_executable(PR_11 main.cpp
        MathLib.cpp
        MathLib.h)

cmake_minimum_required(VERSION 4.0)
project(PR_11)

set(CMAKE_CXX_STANDARD 20)

add_library(MathLib STATIC MathLib.cpp MathLib.h)

add_executable(MathClient main.cpp)

target_link_libraries(MathClient MathLib)