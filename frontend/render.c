#include "render.h"
#include <menu.h>

#define MCOLOR_DEFAULT 0
#define MCOLOR_ME 1
#define MCOLOR_GOLD 2
#define MCOLOR_DANGER 3
#define MCOLOR_END 4
#define MCOLOR_WALL 5


void render_init() {
    initscr();

    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    if (!has_colors()) {
        endwin();
        printf("Your terminal does not support color\n");
        exit(1);
    }
    curs_set(0);
    start_color();
    init_pair(MCOLOR_DEFAULT, COLOR_WHITE, COLOR_BLACK);
    init_pair(MCOLOR_ME, COLOR_WHITE, COLOR_GREEN);
    init_pair(MCOLOR_GOLD, COLOR_YELLOW, COLOR_BLACK);
    init_pair(MCOLOR_DANGER, COLOR_WHITE, COLOR_RED);
    init_pair(MCOLOR_END, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(MCOLOR_WALL, COLOR_WHITE, COLOR_BLUE);
    clear();
}

void render_destroy() {
    clear();
    curs_set(1);
    endwin();
}

void char_to_move(maze_t *maze, int c) {
    if (c == 'w') maze_move(maze, 0, -1);
    if (c == 'a') maze_move(maze, -1, 0);
    if (c == 's') maze_move(maze, 0, 1);
    if (c == 'd') maze_move(maze, 1, 0);
}

attr_t char_to_color(char ch) {
    switch (ch) {
        case 'o':
            return COLOR_PAIR(MCOLOR_ME);
        case '$':
            return COLOR_PAIR(MCOLOR_GOLD);
        case '!':
            return COLOR_PAIR(MCOLOR_DANGER);
        case '_':
            return COLOR_PAIR(MCOLOR_END);
        case '#':
            return COLOR_PAIR(MCOLOR_WALL);
        default:
            return COLOR_PAIR(MCOLOR_DEFAULT);
    }
}

char char_to_display(char ch) {
    if (ch == '$' || ch == '!') return ch;
    return ' ';
}

void render_loop(int argc, char **argv) {
    maze_t *maze = maze_make();

    maze_load(maze, argv[1]);

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
    clear();
    attr_t last_color = -1;
    for (int r = 0; r < maze->rows; ++r) {
        for (int c = 0; c < maze->cols; ++c) {
            char ch;

            if (maze->pos.x == c && maze->pos.y == r) ch = 'o';
            else ch = mget(maze, c, r);

            attr_t color = char_to_color(ch);

            if (last_color != color) {
                attroff(last_color);
                attron(color);
                last_color = color;
            }
            printw("%c", char_to_display(ch));
        }
        printw("\n");
    }
    refresh();
}