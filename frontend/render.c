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

void _char_to_move(maze_t *maze, int c) {
    if (c == 'w') maze_move(maze, 0, -1);
    if (c == 'a') maze_move(maze, -1, 0);
    if (c == 's') maze_move(maze, 0, 1);
    if (c == 'd') maze_move(maze, 1, 0);
}

void render_loop(int argc, char **argv) {
    char a[] = {};
    maze_t maze = {a, 0, 0};
    load("/home/stark/CLionProjects/uni/snake-labyrinth/maze1.txt", &maze);

    render_maze(&maze, false);
    int c;
    while (1) {
        c = getch();
        _char_to_move(&maze, c);
        render_maze(&maze, false);
    }
}

void render_maze(maze_t *maze, bool with_input) {
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