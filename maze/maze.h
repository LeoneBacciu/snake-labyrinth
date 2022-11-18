/**
 * @file maze.h
 * @brief Collection of functions to manage the maze instance
 */

#pragma once

#include <stdlib.h>
#include <ncurses.h>
#include "utils.h"
#include "containers/coord.h"
#include "containers/matrix.h"
#include "containers/path.h"

#define RIGHT 0 ///< RIGHT direction encoding
#define UP 1    ///< UP direction encoding
#define LEFT 2  ///< LEFT direction encoding
#define DOWN 3  ///< DOWN direction encoding

/**
 * @brief List of 4 possible movements RIGHT, UP, LEFT, DOWN
 */
extern const coord_t movements[];

/**
 * @brief List of translations for movements
 * RIGHT -> E
 * UP -> N
 * LEFT -> W
 * DOWN -> S
 */
extern const char movement_to_char[];

/**
 * @struct maze_state_t
 * @brief Represents a maze
 *
 * @var maze_state_t::matrix
 *  Matrix containing maze cells
 * @var maze_state_t::pos
 *  Current position of player
 * @var maze_state_t::end
 *  Position of exit
 * @var maze_state_t::coins
 *  Number of coins reached so far
 * @var maze_state_t::steps
 *  Number of steps done so far
 * @var maze_state_t::path
 *  Path of game
 */
typedef struct {
    matrix_t *matrix;
    matrix_t *initial_matrix;
    coord_t start, pos, end;
    int coins, steps;
    path_t *path;
} maze_state_t;

/**
 * @brief Generates an empty maze
 * @return maze_state_t*
 */
maze_state_t *maze_create(int cols, int rows);

/**
 * @brief Deletes all data
 * @param maze
 */
void maze_destroy(maze_state_t *maze);

/**
 * @brief Frees the memory and deletes all data
 * @param maze
 */
void maze_free(maze_state_t *maze);

/**
 * @brief Creates a copy of the given maze
 * @param maze
 * @return maze_state_t*
 */
maze_state_t *maze_copy(maze_state_t *maze);

/**
 * @brief Creates a copy of the initial state of the given maze
 * @param maze
 * @return maze_state_t*
 */
maze_state_t *maze_copy_initial(maze_state_t *maze);

/**
 * @brief Moves the current position if possible
 * @param maze
 * @param direction one of RIGHT, UP, LEFT, DOWN
 */
void maze_move(maze_state_t *maze, int direction);

/**
 * @brief Creates a copy of the maze and moves the position in the new one
 * @param maze
 * @param direction
 * @return maze_state_t*
 */
maze_state_t *maze_copy_move(maze_state_t *maze, int direction);

/**
 * @brief Gets the value in position coord
 * @param maze
 * @param coord
 * @return the char at that position
 */
char maze_get(maze_state_t *maze, coord_t coord);

/**
 * @brief Sets the value in position coord
 * @param maze
 * @param coord
 * @param v the new value
 */
void maze_set(maze_state_t *maze, coord_t coord, char v);

/**
 * @brief Loads a maze from a file
 * @param path
 * @return maze_state_t*
 */
maze_state_t *maze_load_file(char *path);

/**
 * @brief Loads a maze from stdin
 * @return maze_state_t*
 */
maze_state_t *maze_load_stdin();

/**
 * @brief Checks player reached end
 * @param maze
 * @return false if pos == end, else true
 */
bool maze_is_end(maze_state_t *maze);

/**
 * @brief Checks if coord is valid in this maze
 * @param maze
 * @param coord
 * @return true if coord is possible
 */
bool maze_valid_coord(maze_state_t *maze, coord_t coord);

/**
 * @brief Checks if a cell is free
 * @param maze
 * @param coord
 * @return false if the cell contains # else true
 */
bool maze_can_go(maze_state_t *maze, coord_t coord);

/**
 * @brief Computes the score at the current state
 * @param maze
 * @return score
 */
int maze_score(maze_state_t *maze);

/**
 * @brief Resets the state of the maze to n steps back
 * @param maze
 * @param steps number of steps
 */
void maze_rollback(maze_state_t *maze, int steps);
