/**
 * @file solver.h
 * @brief AI solver functions
 */

#pragma once

#include <limits.h>
#include "maze.h"
#include "containers/path.h"
#include "containers/heap.h"

#define SOLVER_RUNS 500 ///< @brief Default number of random fast solver runs

/**
 * @brief states if the maze can be completed with a better score
 * @param best_score the best score obtained previously
 * @param max_bonus total coins of the maze
 * @param maze
 * @return true if it can outperform, else false
 */
bool can_outperform(int best_score, int max_bonus, maze_state_t *maze);

/**
 * @brief solves the maze (AI FAST)
 * @param maze
 * @return the solved maze
 */
maze_state_t *solve_fast(maze_state_t *maze);

/**
 * @brief solves the maze (AI STRONG)
 * @param maze
 * @return the solved maze
 */
maze_state_t *solve_strong(maze_state_t *maze);
