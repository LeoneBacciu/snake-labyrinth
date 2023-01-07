/**
 * @file agent.h
 * @brief AI Q-Learning solver
 */

#pragma once

#include "maze.h"
#include "q_table.h"
#include "ai/random.h"

/**
 * @brief Solves the maze (AI EXPERIMENTAL)
 * @param maze
 * @return the solved maze
 */
maze_state_t *solve_rl(maze_state_t *maze);