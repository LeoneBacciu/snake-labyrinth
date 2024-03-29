/**
 * @file render.c
 */

#include "render.h"
#include "ai/solver.h"
#include "ai/rl/agent.h"

#define MCOLOR_DEFAULT 0 ///< @brief white - black
#define MCOLOR_ME 1 ///< @brief white - green
#define MCOLOR_GOLD 2 ///< @brief yellow - black
#define MCOLOR_DANGER 3 ///< @brief white - red
#define MCOLOR_END 4 ///< @brief white - magenta
#define MCOLOR_WALL 5 ///< @brief white - blue
#define MCOLOR_WIN 6 ///< @brief yellow - black
#define MCOLOR_NSCORE 7 ///< @brief red - black
#define MCOLOR_PSCORE 8 ///< @brief green - black
#define MCOLOR_LIVES 9 ///< @brief red - black
#define MCOLOR_DRILL 10 ///< @brief white - yellow
#define MCOLOR_NDRILL 11 ///< @brief yellow - black
#define MCOLOR_TAIL 12 ///< @brief white - yellow

#define YOU_WON_LINES 5 ///< @brief Endgame text height
#define YOU_WON_COLS 43 ///< @brief Endgame text width

/// @brief Endgame Text
static char you_won[YOU_WON_LINES][YOU_WON_COLS + 1] = {
        {" \\ \\   / /          \\ \\        / /         \0"},
        {"  \\ \\_/ /__  _   _   \\ \\  /\\  / /__  _ __  \0"},
        {"   \\   / _ \\| | | |   \\ \\/  \\/ / _ \\| '_ \\ \0"},
        {"    | | (_) | |_| |    \\  /\\  / (_) | | | |\0"},
        {"    |_|\\___/ \\__,_|     \\/  \\/ \\___/|_| |_|\0"}
};


/**
 * @internal
 * @brief Moves the player given the key pressed
 * @param maze
 * @param ch id of the key
 */
static void move_player(maze_state_t *maze, int ch) {
    if (ch == 'w' || ch == 'W' || ch == KEY_UP) maze_move(maze, UP);
    if (ch == 'a' || ch == 'A' || ch == KEY_LEFT) maze_move(maze, LEFT);
    if (ch == 's' || ch == 'S' || ch == KEY_DOWN) maze_move(maze, DOWN);
    if (ch == 'd' || ch == 'D' || ch == KEY_RIGHT) maze_move(maze, RIGHT);
}

/**
 * @internal
 * @brief Gets the corresponding color pair for a char
 * @param ch
 * @return the color pair
 */
static attr_t char_to_color(int ch) {
    switch (ch) {
        case 't':
            return COLOR_PAIR(MCOLOR_TAIL);
        case 'o':
        case 'O':
        case 'x':
            return COLOR_PAIR(MCOLOR_ME);
        case '$':
            return COLOR_PAIR(MCOLOR_GOLD);
        case '!':
            return COLOR_PAIR(MCOLOR_DANGER);
        case '_':
            return COLOR_PAIR(MCOLOR_END);
        case '#':
            return COLOR_PAIR(MCOLOR_WALL);
        case 'T':
            return COLOR_PAIR(MCOLOR_DRILL);
        default:
            return COLOR_PAIR(MCOLOR_DEFAULT);
    }
}

/**
 * @internal
 * @brief Gets the corresponding border pattern for a char
 * @param ch
 * @return the borders
 */
static borders_t char_to_border(int ch) {
    if (ch == '$' || ch == '!' || ch == 'T')
        return (borders_t) {true, true, true, true};
    if (IS_SNAKE_TAIL(ch)) {
        borders_t borders = {true, true, true, true};
        if (SNAKE_BITS_B(ch) != -1)
            borders.b[SNAKE_BITS_B(ch)] = false;
        borders.b[SNAKE_BITS_F(ch)] = false;
        return borders;
    }
    return (borders_t) {false, false, false, false};
}

/**
 * @internal
 * @brief Gets the character to display in the terminal from a char
 * @param ch
 * @return the character
 */
static char char_to_display_char(int ch) {
    if (ch == '$' || ch == '!' || ch == 'T') return ch;
    if (ch == 't') return '*';
    return ' ';
}

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
    init_pair(MCOLOR_NSCORE, COLOR_RED, COLOR_BLACK);
    init_pair(MCOLOR_PSCORE, COLOR_GREEN, COLOR_BLACK);
    init_pair(MCOLOR_LIVES, COLOR_RED, COLOR_BLACK);
    init_pair(MCOLOR_DRILL, COLOR_WHITE, COLOR_YELLOW);
    init_pair(MCOLOR_NDRILL, COLOR_YELLOW, COLOR_BLACK);
    init_pair(MCOLOR_TAIL, COLOR_WHITE, COLOR_YELLOW);
    clear();
}

void render_destroy() {
    attroff(-1);
    curs_set(1);
    endwin();
}

void render_loop(maze_state_t *maze, int mode) {
    if (mode == 0) {
        maze_state_t *solution = solve_fast(maze);
        render_replay(solution);
        render_end_game(solution);
    } else if (mode == 1) {
        maze_state_t *solution = solve_strong(maze);
        render_replay(solution);
        render_end_game(solution);
    } else if (mode == 2) {
        maze_state_t *solution = solve_rl(maze);
        render_replay(solution);
        render_end_game(solution);
    } else {
        render_maze(maze);
        int c;
        while (1) {
            c = getch();
            if (c == 'q') break;
            move_player(maze, c);
            if (c == 'u') {
                maze_rollback(maze, 5);
            }
            render_maze(maze);
            if (maze_is_end(maze)) {
                render_end_game(maze);
                break;
            }
        }
    }

    maze_free(maze);
}

void render_maze(maze_state_t *maze) {
    clear();

    attroff(-1);
    attron(COLOR_PAIR(MCOLOR_DEFAULT));

    int ratio_x = COLS / (int) maze->matrix->cols, ratio_y = (LINES - 5) / (int) maze->matrix->rows;
    int ratio = MIN(ratio_x, ratio_y);
    int rows_term = (int) maze->matrix->rows * ratio, cols_term = (int) maze->matrix->cols * ratio;

    if (ratio == 0) {
        attroff(-1);
        attron(COLOR_PAIR(MCOLOR_DANGER));
        printw("Terminal too small for this maze!");
        refresh();
        return;
    }

    if (maze_score(maze) < 1000)
        attron(COLOR_PAIR(MCOLOR_NSCORE));
    else
        attron(COLOR_PAIR(MCOLOR_PSCORE));
#ifdef ROMAN
    mvprintw((LINES - rows_term) / 2 - 2, (COLS - cols_term) / 2, "Score: %s", to_roman(maze_score(maze)));
#else
    mvprintw((LINES - rows_term) / 2 - 2, (COLS - cols_term) / 2, "Score: %d", maze_score(maze));
#endif

    attron(COLOR_PAIR(MCOLOR_NDRILL));
    mvprintw((LINES + rows_term) / 2 + 1, (COLS + cols_term) / 2 - 9, "Drills: %d", maze->drills);
    attron (COLOR_PAIR(MCOLOR_LIVES));
    for (int i = 0; i < maze->lives; ++i) {
#ifdef _WIN32
        cchar_t magic_char = {0, {0x2665, 0}};
        mvadd_wch((LINES - rows_term) / 2 - 2, (COLS + cols_term) / 2 - i * 2 - 1, &magic_char);
#else
        mvprintw((LINES - rows_term) / 2 - 2, (COLS + cols_term) / 2 - i * 2 - 1, "%ls", L" \u2665");
#endif
    }
    if (maze->lives == 0) {
        mvprintw((LINES + rows_term) / 2 + 1, (COLS - cols_term) / 2, "No more lives!");
    }


    attr_t last_color = -1;
    for (int r = 0; r < rows_term; ++r) {
        for (int c = 0; c < cols_term; ++c) {
            int nr = r / ratio, nc = c / ratio;

            int ch = maze_get(maze, c(nc, nr));

            borders_t borders = char_to_border(ch);

            if (ratio > 2 &&
                ((borders.b[0] && c % ratio == ratio - 1 ||
                  borders.b[1] && r % ratio == 0 ||
                  borders.b[2] && c % ratio == 0 ||
                  borders.b[3] && r % ratio == ratio - 1) ||
                 IS_VERTEX(c, r, ratio) && IS_SNAKE_TAIL(ch)))
                ch = ' ';

            if (IS_SNAKE(ch)) {
                if (maze->coins > 4 && maze_distance_from_tail(maze, c(nc, nr)) < 2) ch = 't';
                else ch = IS_SNAKE_HEAD(ch) ? 'O' : 'o';
            }

            attr_t color = char_to_color(ch);
            if (last_color != color) {
                attroff(last_color);
                attron(color);
                last_color = color;
            }

            mvaddch((LINES - rows_term) / 2 + r, (COLS - cols_term) / 2 + c, char_to_display_char(ch));
        }
    }
    refresh();
}

void render_end_game(maze_state_t *maze) {
    __restart_endgame:
    clear();
    attroff(-1);
    attron(COLOR_PAIR(MCOLOR_WIN));
    for (int i = 0; i < 5; i++) {
        mvprintw((LINES / 2) - YOU_WON_LINES + i, (COLS - YOU_WON_COLS) / 2, "%s", you_won[i]);
    }
    mvprintw(LINES / 2 + 2, COLS / 2, "Press Q to exit game\n");
    mvprintw(LINES / 2 + 4, COLS / 2, "Press R to watch replay\n");
    if (maze_score(maze) < 0)
        attron(COLOR_PAIR(MCOLOR_NSCORE));
    else
        attron(COLOR_PAIR(MCOLOR_PSCORE));
#ifdef ROMAN
    mvprintw(LINES / 2 + 6, COLS / 2, "Score: %s", to_roman(maze_score(maze)));
#else
    mvprintw(LINES / 2 + 6, COLS / 2, "Score: %d", maze_score(maze));
#endif
    while (1) {
        char ch = getch();
        if (ch == 'q' || ch == 'Q') break;
        if (ch == 'r' || ch == 'R') {
            render_replay(maze);
            goto __restart_endgame;
        }
    }


}

void render_replay(maze_state_t *maze) {
    maze_state_t *copy = maze_copy_initial(maze);
    path_values_t path = path_values(maze->path);
    for (int i = 0; i < path.size; ++i) {
        maze_move(copy, path.values[i]);
        render_maze(copy);
        sleep_ms(100);
    }
    maze_free(copy);
}
