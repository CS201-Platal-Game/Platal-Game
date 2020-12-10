cmake_minimum_required(VERSION 3.10)

project(platal_game)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -pedantic)

# Directories setup.
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR})

# Options.
option(PLATAL_BUILD_DEMO "Build map_demo." ON)

# SDL2.
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
set(SDL2_LIBS SDL2_image SDL2_ttf SDL2 pthread)

# Executables.
if(PLATAL_BUILD_DEMO)
    add_subdirectory(demo)
endif()

add_library(platal_lib 
            src/character.cpp
            src/dialogue.cpp
            src/game.cpp
            src/platal_map.cpp
            src/object.cpp
            src/clock.cpp
            src/stats.cpp
            src/utils/texture_manager.cpp 
            src/utils/Animation.h
            src/utils/font_manager.cpp
            src/utils/texture_manager.cpp)
add_executable(platal src/main.cpp)
target_link_libraries(platal platal_lib ${SDL2_LIBS})
