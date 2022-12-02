#include "render.h"
#include "ai/solver.h"
#include "ai/rl/agent.h"

#define is_challenge(s) (!strcmp(s, "--challenge"))

#define MCOLOR_DEFAULT 0
#define MCOLOR_ME 1
#define MCOLOR_GOLD 2
#define MCOLOR_DANGER 3
#define MCOLOR_END 4
#define MCOLOR_WALL 5
#define MCOLOR_WIN 6
#define MCOLOR_NSCORE 7
#define MCOLOR_PSCORE 8
#define MCOLOR_LIVES 9
#define MCOLOR_DRILL 10
#define MCOLOR_NDRILL 11

#define YOU_WON_LINES 5
#define YOU_WON_COLS 43

char you_won[YOU_WON_LINES][YOU_WON_COLS + 1] = {
        {" \\ \\   / /          \\ \\        / /         \0"},
        {"  \\ \\_/ /__  _   _   \\ \\  /\\  / /__  _ __  \0"},
        {"   \\   / _ \\| | | |   \\ \\/  \\/ / _ \\| '_ \\ \0"},
        {"    | | (_) | |_| |    \\  /\\  / (_) | | | |\0"},
        {"    |_|\\___/ \\__,_|     \\/  \\/ \\___/|_| |_|\0"}
};

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
    clear();
}

void render_destroy() {
    attroff(-1);
    curs_set(1);
    endwin();
}

void char_to_move(maze_state_t *maze, int c) {
    if (c == 'w' || c == 'W' || c == KEY_UP) maze_move(maze, UP);
    if (c == 'a' || c == 'A' || c == KEY_LEFT) maze_move(maze, LEFT);
    if (c == 's' || c == 'S' || c == KEY_DOWN) maze_move(maze, DOWN);
    if (c == 'd' || c == 'D' || c == KEY_RIGHT) maze_move(maze, RIGHT);
}

attr_t char_to_color(char ch) {
    switch (ch) {
        case 'o':
            return COLOR_PAIR(MCOLOR_ME);
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

char char_to_display(char ch) {
    if (ch == '$' || ch == '!' || ch == 'T') return ch;
    return ' ';
}

void render_loop(int argc, char **argv) {
    maze_state_t *maze;

    if (argc > 1) maze = maze_load_file(argv[1]);
    else exit(EXIT_FAILURE);

    if (argc > 2 && is_challenge(argv[2])) {
//        solve_rl(maze);
//        exit(0);

        // TODO: rewrite better
        maze_state_t *initial_solution = solve(maze);
        maze_state_t *sim = maze_simulate(maze, path_values(initial_solution->path));
        for (int i = 0; i < SOLVER_RUNS; ++i) {
            maze_state_t *tmp = solve(maze);
            maze_state_t *tmp_sim = maze_simulate(maze, path_values(tmp->path));
            if (maze_score(sim) < maze_score(tmp_sim)) {
                maze_free(sim);
                sim = tmp_sim;
            } else {
                maze_free(tmp_sim);
            }
            maze_free(tmp);
        }

        render_replay(sim);
        while (getch() != 'q');
    } else {
        render_maze(maze);
        int c;
        while (1) {
            c = getch();
            if (c == 'q') break;
            char_to_move(maze, c);
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
    if (maze_score(maze) < 0)
        attron(COLOR_PAIR(MCOLOR_NSCORE));
    else
        attron(COLOR_PAIR(MCOLOR_PSCORE));
//    mvprintw((LINES - rows_term) / 2 - 2, (COLS - cols_term) / 2, "Score: %s", to_roman(maze_score(maze)));
    mvprintw((LINES - rows_term) / 2 - 2, (COLS - cols_term) / 2, "Score: %d", maze_score(maze));

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

    if (ratio == 0) {
        attroff(-1);
        attron(COLOR_PAIR(MCOLOR_DANGER));
        printw("Terminal too small for this maze!");
        refresh();
        return;
    }

    attr_t last_color = -1;
    for (int r = 0; r < rows_term; ++r) {
        for (int c = 0; c < cols_term; ++c) {
            int nr = r / ratio, nc = c / ratio;

            char ch;
            if (maze->pos.x == nc && maze->pos.y == nr) ch = 'o';
            else ch = maze_get(maze, c(nc, nr));

            attr_t color = char_to_color(ch);
            if (last_color != color) {
                attroff(last_color);
                attron(color);
                last_color = color;
            }
            mvaddch((LINES - rows_term) / 2 + r, (COLS - cols_term) / 2 + c, char_to_display(ch));
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
    mvprintw(LINES / 2 + 6, COLS / 2, "Score: %s", to_roman(maze_score(maze)));
    while (1) {
        char ch = getch();
        if (ch == 'q' || ch == 'Q') break;
        if (ch == 'r' || ch == 'R') {
            render_replay(maze);
            goto __restart_endgame;
        }
    }


}

int render_menu(char *title, int choices_count, char **choices) {
    ITEM **items;
    int c;
    MENU *menu;
    WINDOW *window;
    int width = 0, height = choices_count, current = 0, out_width, out_height, delta_height = 3, delta_width = 1;

    choices_count = choices_count;
    items = (ITEM **) calloc(choices_count, sizeof(ITEM *));
    for (int i = 0; i < choices_count; ++i) {
        items[i] = new_item(choices[i], choices[i]);
        width = MAX(width, strlen(choices[i]));
    }
    items[choices_count] = (ITEM *) NULL;
    width += 3;

    out_height = height + 4;
    out_width = width + 4;

    menu = new_menu((ITEM **) items);

    window = newwin(out_height, out_width, (LINES - out_height) / 2, (COLS - out_width) / 2);
    keypad(window, TRUE);

    set_menu_win(menu, window);
    set_menu_sub(menu, derwin(window, height, width, delta_height, delta_width));

    set_menu_mark(menu, " * ");

    box(window, 0, 0);

    mvwprintw(window, 1, (int) (out_width - strlen(title)) / 2, "%s", title);
    refresh();

    mvwaddch(window, 2, 0, ACS_LTEE);
    mvwhline(window, 2, 1, ACS_HLINE, out_width - 2);
    mvwaddch(window, 2, out_width - 1, ACS_RTEE);
    refresh();

    post_menu(menu);
    wrefresh(window);

    while ((c = wgetch(window)) != '\n') {
        mvwin(window, (LINES - out_height) / 2, (COLS - out_width) / 2);
        refresh();
        post_menu(menu);
        if (c == 's' || c == 'S' || c == KEY_DOWN)
            menu_driver(menu, REQ_DOWN_ITEM);
        if (c == 'w' || c == 'W' || c == KEY_UP)
            menu_driver(menu, REQ_UP_ITEM);
        current = item_index(current_item(menu));
        wrefresh(window);
    }

    unpost_menu(menu);
    free_menu(menu);
    for (int i = 0; i < choices_count; ++i) free_item(items[i]);

    return current;
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
