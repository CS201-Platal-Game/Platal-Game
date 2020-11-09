cmake_minimum_required(VERSION 3.17)
project(map_demo)

# PROJECT DIR SETUP
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR})

# SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
set(SDL2_LIBS SDL2_image SDL2 pthread)

# EXECUTABLE
add_library(map_demo_lib 
            ${CMAKE_CURRENT_SOURCE_DIR}/src/Game.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/map.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/TextureManager.cpp)

add_executable(map_demo src/main.cpp)
target_link_libraries(map_demo map_demo_lib ${SDL2_LIBS})
