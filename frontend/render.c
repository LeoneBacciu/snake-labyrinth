#include "render.h"

void render_init() {
    initscr();
}

void render_destroy() {
    endwin();
}

void render_loop(int argc, char **argv) {
    char a[] = {};
    maze_t maze = {a, 0, 0};
    load("/home/stark/CLionProjects/uni/snake-labyrinth/maze1.txt", &maze);

    render_maze(&maze, false);
    char c;
    while ((c = getch())) {
        mset(&maze, 0, 1, c);
        render_maze(&maze, false);
    }
}

void render_maze(maze_t *maze, bool with_input) {
    clear();
    for (int r = 0; r < maze->rows; ++r) {
        for (int c = 0; c < maze->cols; ++c) {
            printw("%c", mget(maze, c, r));
        }
        printw("\n");
    }
    refresh();
}