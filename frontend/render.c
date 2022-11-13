#include "render.h"

#define MCOLOR_DEFAULT 0
#define MCOLOR_ME 1
#define MCOLOR_GOLD 2
#define MCOLOR_DANGER 3
#define MCOLOR_END 4
#define MCOLOR_WALL 5
#define MCOLOR_WIN 6


void render_init() {
    initscr();

    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    if (!has_colors()) {
        endwin();
        printf("Your terminal does not support color\n");
        exit(EXIT_FAILURE);
    }
    curs_set(0);
    start_color();
    init_pair(MCOLOR_DEFAULT, COLOR_WHITE, COLOR_BLACK);
    init_pair(MCOLOR_ME, COLOR_WHITE, COLOR_GREEN);
    init_pair(MCOLOR_GOLD, COLOR_YELLOW, COLOR_BLACK);
    init_pair(MCOLOR_DANGER, COLOR_WHITE, COLOR_RED);
    init_pair(MCOLOR_END, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(MCOLOR_WALL, COLOR_WHITE, COLOR_BLUE);
    init_pair(MCOLOR_WIN, COLOR_YELLOW, COLOR_BLACK);
    clear();
}

void render_destroy() {
    //clear();
    curs_set(1);
    endwin();
}

void char_to_move(maze_t *maze, int c) {
    if (c == 'w' || c == 'W' || c == KEY_UP) maze_move(maze, 0, -1);
    if (c == 'a' || c == 'A' || c == KEY_LEFT) maze_move(maze, -1, 0);
    if (c == 's' || c == 'S' || c == KEY_DOWN) maze_move(maze, 0, 1);
    if (c == 'd' || c == 'D' || c == KEY_RIGHT) maze_move(maze, 1, 0);
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
        if (maze->pos.x == maze->end.x) {
            clear();
            attroff(-1);
            attron(COLOR_PAIR(MCOLOR_WIN));
            for(int i=0; i<=4; i++){
                mvprintw((LINES/2)-5+i, (COLS-43)/2, you_won[i]);
                printw("\n");
            }
            mvprintw(LINES / 2 + 2, COLS / 2, "Press Q to exit game\n");
        }
    }
    maze_destroy(maze);
}

void render_maze(maze_t *maze) {
    clear();
    int ratio_x = COLS / maze->cols;
    int ratio_y = LINES / maze->rows;
    int ratio = MIN(ratio_x, ratio_y);
    attr_t last_color = -1;
    for (int r = 0; r < (maze->rows) * ratio; ++r) {
        for (int c = 0; c < (maze->cols) * ratio; ++c) {
            char ch;
            int nr = r / ratio, nc = c / ratio;

            if (maze->pos.x == nc && maze->pos.y == nr) ch = 'o';
            else ch = mget(maze, nc, nr);
            attr_t color = char_to_color(ch);
            if (last_color != color) {
                attroff(last_color);
                attron(color);
                last_color = color;
            }
            mvaddch(r, (COLS - maze->cols * ratio) / 2 + c, char_to_display(ch));
        }
        addch('\n');
    }
    refresh();
}
char you_won [5][44]={  {" \\ \\   / /          \\ \\        / /         \0"},
                        {"  \\ \\_/ /__  _   _   \\ \\  /\\  / /__  _ __  \0"},
                        {"   \\   / _ \\| | | |   \\ \\/  \\/ / _ \\| '_ \\ \0"},
                        {"    | | (_) | |_| |    \\  /\\  / (_) | | | |\0"},
                        {"    |_|\\___/ \\__,_|     \\/  \\/ \\___/|_| |_|\0"}};