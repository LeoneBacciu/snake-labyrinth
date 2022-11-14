/**
 * @file maze.h
 * @brief Collection of functions to manage the maze instance
 */

#pragma once

#include <stdlib.h>
#include <ncurses.h>
#include "utils.h"
#include "containers/coord.h"

#define RIGHT 0 ///< RIGHT direction encoding
#define UP 1    ///< UP direction encoding
#define LEFT 2  ///< LEFT direction encoding
#define DOWN 3  ///< DOWN direction encoding

/**
 * @brief List of 4 possible movements RIGHT, UP, LEFT, DOWN
 */
extern const coord_t movements[];

/**
 * @struct maze_t
 * @brief Represents a maze
 *
 * @var maze_t::_m
 *  The internal representation of the maze
 *  @attention Do not use directly
 *  @see mget
 *  @see mset
 * @var maze_t::rows
 *  Number of rows
 * @var maze_t::cols
 *  Number of columns
 * @var maze_t::pos
 *  Current position of player
 * @var maze_t::end
 *  Position of exit
 */
typedef struct {
    char *_m;
    int rows, cols;
    coord_t pos, end;
} maze_t;

/**
 * @brief Generates an empty maze
 * @return maze_t*
 */
maze_t *maze_create();

/**
 * @brief Frees the memory of a maze
 * @param maze
 */
void maze_destroy(maze_t *maze);

/**
 * @brief Moves the current position if possible
 * @param maze
 * @param coord
 */
void maze_move(maze_t *maze, coord_t coord);

/**
 * @brief Resizes the maze by allocating the necessary memory
 * @attention This erases the previous maze
 * @param maze
 * @param cols number of rows
 * @param rows number of columns
 */
void maze_resize(maze_t *maze, int cols, int rows);

/**
 * @brief Gets the value in position coord
 * @param maze
 * @param coord
 * @return the char at that position
 */
char mget(maze_t *maze, coord_t coord);

/**
 * @brief Sets the value in position coord
 * @param maze
 * @param coord
 * @param v the new value
 */
void mset(maze_t *maze, coord_t coord, char v);

/**
 * @brief Loads a maze from a file
 * @param maze
 * @param path the path of the file
 */
void maze_load(maze_t *maze, char *path);

/**
 * @brief Checks player reached end
 * @param maze
 * @return false if pos == end, else true
 */
bool maze_is_end(maze_t *maze);

/**
 * @brief Checks if coord is valid in this maze
 * @param maze
 * @param coord
 * @return true if coord is possible
 */
bool maze_valid_coord(maze_t *maze, coord_t coord);

/**
 * @brief Checks if a cell is free
 * @param maze
 * @param coord
 * @return false if the cell contains # else true
 */
bool maze_can_go(maze_t *maze, coord_t coord);
