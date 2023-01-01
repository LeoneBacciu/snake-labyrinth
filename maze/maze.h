/**
 * @file maze.h
 * @brief Collection of functions to manage the maze instance
 */

#pragma once

#include <stdlib.h>
#include "utils.h"
#include "containers/coord.h"
#include "containers/matrix.h"
#include "containers/path.h"

#define TAIL_BASE (1 << 9) ///< @brief Low bound for int representing a tail node
#define TAIL_BASE_MAX (1 << 10) ///< @brief High bound for int representing a tail node

/**
 * @enum direction_t
 * @brief Enum representing one of four directions
 */
typedef enum {
    RIGHT = 0, UP = 1, LEFT = 2, DOWN = 3
} direction_t;

/// @brief Gives the opposite direction N <-> S, E <-> W
#define OPP(d) ((d + 2) % 4)

/// @brief Encodes front and back direction of a tail node
#define SNAKE_TO_BITS(f, b) (TAIL_BASE + ((f + 1) << 4) + (b + 1))
/// @brief Decodes the front direction of a tail node
#define SNAKE_BITS_F(b) (((b % TAIL_BASE) >> 4) - 1)
/// @brief Decodes the back direction of a tail node
#define SNAKE_BITS_B(b) ((b % (1 << 4)) - 1)

/// @brief Encodes and sets front and back direction of a tail node
#define MAZE_SNAKE_SET_BITS(m, c, f, b) maze_set(m, c, SNAKE_TO_BITS(f, b))
/// @brief Encodes and sets the front direction of a tail node
#define MAZE_SNAKE_SET_F(m, c, f) maze_set(m, c, SNAKE_TO_BITS(f, SNAKE_BITS_B(maze_get(m, c))))
/// @brief Encodes and sets the back direction of a tail node
#define MAZE_SNAKE_SET_B(m, c, b) maze_set(m, c, SNAKE_TO_BITS(SNAKE_BITS_F(maze_get(m, c)), b))

/// @brief Checks if cell is tail node
#define IS_SNAKE(a) (a >= TAIL_BASE && a < TAIL_BASE_MAX)
/// @brief Checks if cell is tail head
#define IS_SNAKE_HEAD(a) (IS_SNAKE(a) && SNAKE_BITS_F(a) == -1)
/// @brief Checks if cell is tail end
#define IS_SNAKE_TAIL(a) (IS_SNAKE(a) && SNAKE_BITS_F(a) != -1)

#define MAX_LIVES 5 ///< @brief Initial lives

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
 * @var maze_state_t::initial_matrix
 *  Initial state of matrix containing maze cells
 *  @attention Don't modify
 * @var maze_state_t::head
 *  Current position of the head
 * @var maze_state_t::tail
 *  Current position of the tail end
 * @var maze_state_t::start
 *  Starting position
 * @var maze_state_t::end
 *  Exit position
 * @var maze_state_t::coins
 *  Number of coins reached so far
 * @var maze_state_t::steps
 *  Number of steps done so far
 * @var maze_state_t::lives
 *  Number of lives remaining
 * @var maze_state_t::drills
 *  Number of drills remaining
 * @var maze_state_t::path
 *  Path of game
 */
typedef struct {
    matrix_t *matrix;
    matrix_t *initial_matrix;
    coord_t start, head, tail, end;
    int coins, steps, lives, drills;
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
bool maze_move(maze_state_t *maze, direction_t direction);

/**
 * @brief Creates a copy of the maze and moves the position in the new one
 * @param maze
 * @param direction
 * @return maze_state_t*
 * @return true if can_go else false
 */
maze_state_t *maze_copy_move(maze_state_t *maze, direction_t direction);

/**
 * @brief Gets the value in position coord
 * @param maze
 * @param coord
 * @return the char at that position
 */
int maze_get(maze_state_t *maze, coord_t coord);

/**
 * @brief Sets the value in position coord
 * @param maze
 * @param coord
 * @param v the new value
 */
void maze_set(maze_state_t *maze, coord_t coord, int v);

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
 * @return false if head == end, else true
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

/**
 * @brief Executes the path on a copy of the maze
 * @param maze
 * @param path
 * @return the copy of the maze
 */
maze_state_t *maze_simulate(maze_state_t *maze, path_values_t path);