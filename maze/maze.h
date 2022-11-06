/**
 * @file maze.h
 * @brief Collection of functions to manage the maze instance
 */

#pragma once

#include <ncurses.h>
#include "utils.h"

/**
 * @struct coord_t
 * @brief Represents an x/y pair
 *
 * @var coord_t::x
 *  X coordinate
 * @var coord_t::y
 *  Y coordinate
 */
typedef struct {
    int x, y;
} coord_t;

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
maze_t *maze_make();

/**
 * @brief Frees the memory of a maze
 * @param maze
 */
void maze_destroy(maze_t *maze);

/**
 * @brief Moves the current position if possible
 * @param maze
 * @param dx delta x movement
 * @param dy delta y movement
 */
void maze_move(maze_t *maze, int dx, int dy);

/**
 * @brief Resizes the maze by allocating the necessary memory
 * @attention This erases the previous maze
 * @param maze
 * @param x number of rows
 * @param y number of columns
 */
void maze_resize(maze_t *maze, int x, int y);

/**
 * @brief Gets the value in position x/y
 * @param maze
 * @param x
 * @param y
 * @return the char at that position
 */
char mget(maze_t *maze, int x, int y);

/**
 * @brief Sets the value in position x/y
 * @param maze
 * @param x
 * @param y
 * @param v the new value
 */
void mset(maze_t *maze, int x, int y, char v);

/**
 * @brief Loads a maze from a file
 * @param maze
 * @param path the path of the file
 */
void maze_load(maze_t *maze, char *path);

/**
 * @brief Checks if a cell is free
 * @param maze
 * @param x
 * @param y
 * @return \a false if the cell contains # else true
 */
bool can_go(maze_t *maze, int x, int y);