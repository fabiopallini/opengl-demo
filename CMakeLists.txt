cmake_minimum_required(VERSION 3.10.2)
project (game)

#include_directories(include)

file(GLOB SOURCES "src/*.cpp")

#link_directories(lib)

find_library(SDL2_LIBRARY SDL2)
find_library(SDL2_image_LIBRARY SDL2_image)

if(NOT SDL2_LIBRARY OR NOT SDL2_image_LIBRARY)
    message(FATAL_ERROR "SDL2 or SDL2_image not found")
endif()

add_executable(game ${SOURCES})
target_link_libraries(game ${SDL2_LIBRARY} ${SDL2_image_LIBRARY} GL GLU)
