cmake_minimum_required(VERSION 3.23)
project(snake_labyrinth C)

set(CMAKE_C_STANDARD 99)

find_package(Curses REQUIRED)
find_library(MENU_LIBRARY menu)
include_directories(${CURSES_INCLUDE_DIR})

include_directories(.)
include_directories(maze)

add_executable(snake_labyrinth
        maze/maze.c maze/maze.h main.c frontend/render.c frontend/render.h utils.c utils.h)
target_link_libraries(snake_labyrinth ${MENU_LIBRARY} ${CURSES_LIBRARIES})
