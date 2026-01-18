cmake_minimum_required(VERSION 3.20)
project(PZ_15 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(Library STATIC
        ../PR_12/Library.cpp
        ../PR_12/Library.h
)

target_include_directories(Library PUBLIC ../PR_12)

add_executable(PZ_15 WIN32
        main.cpp
)

target_link_libraries(PZ_15 PRIVATE Library)
