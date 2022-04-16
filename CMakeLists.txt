project(gravity_game)
cmake_minimum_required(VERSION 3.3)

set(CMAKE_C_STANDARD 17)

add_executable(gravity_game "${PROJECT_SOURCE_DIR}/src/gravity_game.c")
target_link_libraries(gravity_game PRIVATE allegro allegro_primitives)
