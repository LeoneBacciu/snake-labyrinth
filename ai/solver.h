/**
 * @file solver.h
 * @brief AI solver functions
 */

#pragma once

#include <limits.h>
#include "maze.h"
#include "containers/path.h"
#include "containers/heap.h"

#define SOLVER_FAST_RUNS 500 ///< @brief Default number of random fast solver runs
#define SOLVER_STRONG_DEPTH 20 ///< @brief Max depth for strong solver

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
