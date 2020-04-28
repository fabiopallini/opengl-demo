cmake_minimum_required(VERSION 3.10.2)
project (demo)

#include_directories(include)

file(GLOB SOURCES "src/*.c")

#link_directories(lib)

find_library(sdl2 SDL2)
find_library(sdl2_image SDL2_image)

if(APPLE)
    find_library(opengGL OpenGL)
endif()

if(NOT sdl2 OR NOT sdl2_image)
    message(FATAL_ERROR "SDL2 or SDL2_image not found")
endif()

if(APPLE)
    if(NOT opengGL)
        message(FATAL_ERROR "OpengGL not found")
    endif()
endif()

add_executable(demo ${SOURCES})
target_compile_options(demo PRIVATE "-Wno-deprecated")

if(APPLE)
    target_link_libraries(demo ${sdl2} ${sdl2_image} ${opengGL})
else()
    target_link_libraries(demo ${sdl2} ${sdl2_image} GL GLU)
endif()