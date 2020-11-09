cmake_minimum_required(VERSION 3.17)
project(map_demo)

# PROJECT DIR SETUP
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR})

# LIBS
find_package(SDL2 REQUIRED)
include_directories(${PROJECT_NAME} ${SDL2_INCLUDE_DIRS})

add_executable(map_demo main.cpp src/Game.cpp src/map.cpp
        src/TextureManager.cpp)

set(LIBS SDL2_image SDL2 pthread)

include_directories(
        ${PROJECT_NAME}
        ${CMAKE_SOURCE_DIR}/src
        ${OPENGL_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/include
        ${HEADER_FILES}
)
target_link_libraries(${PROJECT_NAME} ${LIBS})

link_directories(${CMAKE_SOURCE_DIR}/lib)