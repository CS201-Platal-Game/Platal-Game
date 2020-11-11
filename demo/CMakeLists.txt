add_library(map_demo_lib game.cpp map.cpp texture_manager.cpp)
add_executable(map_demo main.cpp)
target_link_libraries(map_demo map_demo_lib ${SDL2_LIBS})
