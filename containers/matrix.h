/**
 * @file matrix.h
 * @brief Matrix DS
 */

#pragma once

#include <stdlib.h>
#include <stdbool.h>

typedef long long ll;

/**
 * @struct matrix_t
 * @brief Matrix DS
 *
 * @var matrix_t::rows
 *  Number of rows
 * @var matrix_t::cols
 *  Number of cols
 * @var matrix_t::m
 *  Matrix stored as an array
 *  @attention Do not use directly
 *  @see matrix_get
 *  @see matrix_set
 */
typedef struct {
    size_t rows, cols;
    ll *m;
} matrix_t;

/**
 * @brief Creates a Matrix
 * @param cols number of columns
 * @param rows number of rows
 * @param val default value of cells
 * @return pointer to the Matrix
 */
matrix_t *matrix_create(size_t cols, size_t rows, ll val);

/**
 * @brief Gets a value from the Matrix
 * @param matrix
 * @param x coordinate
 * @param y coordinate
 * @return value in x:y coordinate
 */
ll matrix_get(matrix_t *matrix, size_t x, size_t y);

/**
 * @brief Sets a value in the Matrix
 * @param matrix
 * @param x coordinate
 * @param y coordinate
 * @param v value to set
 */
void matrix_set(matrix_t *matrix, size_t x, size_t y, ll v);

/**
 * @brief Sets a value in the Matrix if it is smaller than the current
 * @param matrix
 * @param x coordinate
 * @param y coordinate
 * @param v value to test and set
 * @return the smallest value between v and the current
 */
ll matrix_set_min(matrix_t *matrix, size_t x, size_t y, ll v);

/**
 * @brief Sets a value in the Matrix if it is bigger than the current
 * @param matrix
 * @param x coordinate
 * @param y coordinate
 * @param v value to test and set
 * @return the biggest value between v and the current
 */
ll matrix_set_max(matrix_t *matrix, size_t x, size_t y, ll v);

/**
 * @brief Frees the memory deleting all the data
 * @param matrix
 */
void matrix_destroy(matrix_t *matrix);
