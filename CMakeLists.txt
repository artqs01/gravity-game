project(gravity_game)
cmake_minimum_required(VERSION 3.3)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DDEBUG -g -fsanitize=address -fsanitize=undefined -fno-builtin -fno-omit-frame-pointer")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -march=native -O3 -ffast-math -ftree-vectorize")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}-Wall -Wextra")
add_executable(gravity_game
    "${PROJECT_SOURCE_DIR}/src/gravity_game.c"
    "${PROJECT_SOURCE_DIR}/src/vect2.c"
    "${PROJECT_SOURCE_DIR}/src/obj.c"
    "${PROJECT_SOURCE_DIR}/src/draw.c"
)
target_link_libraries(gravity_game PRIVATE allegro allegro_primitives m)
target_include_directories(gravity_game PRIVATE "${PROJECT_SOURCE_DIR}/src")
