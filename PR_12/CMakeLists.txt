cmake_minimum_required(VERSION 3.20)
project(PR_12 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(Library SHARED
        Library.cpp
        Library.h
)

add_executable(PR_12 main.cpp)

target_link_libraries(PR_12 PRIVATE Library)

if(WIN32)
    add_custom_command(TARGET PR_12 POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:Library>
            $<TARGET_FILE_DIR:PR_12>
            COMMENT "Копируем DLL рядом с исполняемым файлом"
    )
endif()