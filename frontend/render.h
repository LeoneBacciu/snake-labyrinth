#pragma once

#define _XOPEN_SOURCE_EXTENDED

#include <stdlib.h>
#include "maze/maze.h"
#include <ncurses.h>

#ifdef USE_MENU
#include <menu.h>
#endif

#define IS_VERTEX(c, r, ratio) (((r % ratio == 0) + (c % ratio == 0) + (r % ratio == ratio - 1) + (c % ratio == ratio - 1)) == 2)

/**
 * @struct borders_t
 * @brief Describes borders of a cell
 *
 * @var bool::b
 *  States if the four borders of a char are occupied
 */
typedef struct {
    bool b[4];
} borders_t;

/**
 * @brief Initializes NCurses and colors
 */
void render_init();

/**
 * @brief Stops NCurses and frees the cursor
 */
void render_destroy();

/**
 * @brief Renders the main game loop
 * @param argc
 * @param argv
 */

void render_loop(int argc, char **argv);

/**
 * @brief Renders the current maze
 * @param maze
 */
void render_maze(maze_state_t *maze);

/**
 * @brief Renders the final screen
 * @param maze
 */

void render_end_game(maze_state_t *maze);

#ifdef USE_MENU
/**
 * @brief Renders the menu
 * @param title the title of the game
 * @param choices_count number of possible choices
 * @param choices pointer to different choices
 * @return the value corresponding to the selected choice
 */

int render_menu(char *title, int choices_count, char **choices);
#endif

/**
 * @brief Renders the replay of the game
 * @param maze
 */
void render_replay(maze_state_t *maze);
