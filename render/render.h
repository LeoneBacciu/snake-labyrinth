/**
 * @file render.h
 * @brief Rendering functions
 */

#pragma once

/// @cond DO_NOT_DOCUMENT
#define _XOPEN_SOURCE_EXTENDED
/// @endcond

#include <stdlib.h>
#include <ncurses.h>

#include "maze/maze.h"

/// @brief Checks if coordinate is a cell vertex
#define IS_VERTEX(c, r, ratio) ((((r) % (ratio) == 0) + ((c) % (ratio) == 0) + ((r) % (ratio) == (ratio) - 1) + ((c) % (ratio) == (ratio) - 1)) == 2)

/**
 * @struct borders_t
 * @brief Describes borders of a cell
 *
 * @var borders_t::b
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
 * @param maze
 * @param mode (0 = fast, 1 = strong, 2 = experimental, 3 = interactive)
 */

void render_loop(maze_state_t *maze, int mode);

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

/**
 * @brief Renders the replay of the game
 * @param maze
 */
void render_replay(maze_state_t *maze);
