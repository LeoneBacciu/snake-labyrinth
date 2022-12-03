#pragma once

#include <limits.h>
#include "maze.h"
#include "containers/path.h"
#include "containers/heap.h"

#define SOLVER_RUNS 100

bool can_outperform(int best_score, int max_bonus, maze_state_t *maze);

maze_state_t *solve(maze_state_t *maze);

maze_state_t *solve_rec(maze_state_t *maze);
