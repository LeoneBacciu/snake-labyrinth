/**
 * @file matrix.h
 * @brief Matrix DS
 */

#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>

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
    int *m;
} matrix_t;

/**
 * @brief Creates a Matrix
 * @param cols number of columns
 * @param rows number of rows
 * @param val default value of cells
 * @return pointer to the Matrix
 */
matrix_t *matrix_create(size_t cols, size_t rows, int val);

/**
 * @brief Gets a value from the Matrix
 * @param matrix
 * @param x coordinate
 * @param y coordinate
 * @return value in x:y coordinate
 */
int matrix_get(matrix_t *matrix, size_t x, size_t y);

/**
 * @brief Sets a value in the Matrix
 * @param matrix
 * @param x coordinate
 * @param y coordinate
 * @param v value to set
 */
void matrix_set(matrix_t *matrix, size_t x, size_t y, int v);

/**
 * @brief Sets a value in the Matrix if it is smaller than the current
 * @param matrix
 * @param x coordinate
 * @param y coordinate
 * @param v value to test and set
 * @return true if the value was updated, else false
 */
bool matrix_set_min(matrix_t *matrix, size_t x, size_t y, int v);

/**
 * @brief Sets a value in the Matrix if it is bigger than the current
 * @param matrix
 * @param x coordinate
 * @param y coordinate
 * @param v value to test and set
 * @return true if the value was updated, else false
 */
bool matrix_set_max(matrix_t *matrix, size_t x, size_t y, int v);

/**
 * @brief Copies the matrix
 * @param matrix
 * @return a copy of the matrix
 */
matrix_t *matrix_copy(matrix_t *matrix);

/**
 * @brief Deletes all the data
 * @param matrix
 * @note Does not free the matrix_t pointer
 */
void matrix_destroy(matrix_t *matrix);

/**
 * @brief Frees the memory and deletes all the data
 * @param matrix
 */
void matrix_free(matrix_t *matrix);
