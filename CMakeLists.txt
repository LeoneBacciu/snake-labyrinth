cmake_minimum_required(VERSION 3.23)
project(snake_labyrinth C)

set(CMAKE_C_STANDARD 99)

include_directories(.)
include_directories(maze)

add_executable(snake_labyrinth
        rogueutil.c rogueutil.h maze/maze.c maze/maze.h main.c frontend/render.c frontend/render.h utils.c utils.h)
