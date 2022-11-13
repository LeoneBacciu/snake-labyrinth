cmake_minimum_required(VERSION 3.23)
project(snake_labyrinth C)

set(CMAKE_C_STANDARD 99)

if (WIN32)
    set(CURSES_INCLUDE_PATH "C:/MinGW/include/ncursesw")
endif ()

find_package(Curses REQUIRED)
if (WIN32)
    find_library(MENU_LIBRARY libmenuw)
else ()
    find_library(MENU_LIBRARY menu)
endif ()
include_directories(${CURSES_INCLUDE_DIR})

include_directories(.)
include_directories(maze)

add_executable(snake_labyrinth
        containers/heap.c containers/heap.h
        containers/matrix.c containers/matrix.h
        containers/sequence.c containers/sequence.h
        frontend/render.c frontend/render.h
        maze/maze.c maze/maze.h
        utils.c utils.h
        main.c)
target_link_libraries(snake_labyrinth ${MENU_LIBRARY} ${CURSES_LIBRARIES})
