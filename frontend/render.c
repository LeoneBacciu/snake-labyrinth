#include "render.h"

void render_init() {
    hidecursor();
    saveDefaultColor();
    cls();
}

void render_destroy() {
    cls();
    resetColor();
    showcursor();
}

void char_to_move(maze_t *maze, int c) {
    if (c == 'w') maze_move(maze, 0, -1);
    if (c == 'a') maze_move(maze, -1, 0);
    if (c == 's') maze_move(maze, 0, 1);
    if (c == 'd') maze_move(maze, 1, 0);
}

void render_loop(int argc, char **argv) {
    maze_t *maze = maze_make();
#ifdef _WIN32
    load("..\\maze1.txt", maze);
#else
    load("/home/stark/CLionProjects/uni/snake-labyrinth/maze1.txt", maze);
#endif

    render_maze(maze);
    int c;
    while (1) {
        c = getch();
        if (c == 'q') break;
        char_to_move(maze, c);
        render_maze(maze);
    }
    maze_destroy(maze);
}

void render_maze(maze_t *maze) {
    cls();
    for (int r = 0; r < maze->rows; ++r) {
        for (int c = 0; c < maze->cols; ++c) {
            if (maze->pos.x == c && maze->pos.y == r)
                colorPrint(GREEN, NOCOLOR, "o");
            else
                colorPrint(RED, NOCOLOR, "%c", mget(maze, c, r));
        }
        colorPrint(RED, NOCOLOR, "\n");
    }
}