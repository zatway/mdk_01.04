cmake_minimum_required(VERSION 3.20)
project(PZ_13)

set(CMAKE_CXX_STANDARD 17)

add_executable(PZ_13 WIN32 main.cpp)

target_link_libraries(PZ_13 user32 gdi32)