#pragma once

#include <limits.h>
#include "maze.h"
#include "containers/path.h"
#include "containers/heap.h"

bool can_outperform(int best_score, int max_bonus, maze_state_t *maze);

path_values_t solve(maze_state_t *maze);
