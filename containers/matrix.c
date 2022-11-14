#include "matrix.h"

matrix_t *matrix_create(size_t cols, size_t rows, int val) {
    matrix_t *matrix = malloc(sizeof(matrix_t));
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->m = calloc(rows * cols, sizeof(int));
    for (int i = 0; i < cols * rows; ++i) matrix->m[i] = val;
    return matrix;
}

int matrix_get(matrix_t *matrix, size_t x, size_t y) {
    return matrix->m[y * matrix->cols + x];
}

void matrix_set(matrix_t *matrix, size_t x, size_t y, int v) {
    matrix->m[y * matrix->cols + x] = v;
}

bool matrix_set_min(matrix_t *matrix, size_t x, size_t y, int v) {
    int o = matrix_get(matrix, x, y);
    if (v < o) {
        matrix_set(matrix, x, y, v);
        return true;
    }
    return false;
}

bool matrix_set_max(matrix_t *matrix, size_t x, size_t y, int v) {
    int o = matrix_get(matrix, x, y);
    if (v > o) {
        matrix_set(matrix, x, y, v);
        return true;
    }
    return false;
}

matrix_t *matrix_copy(matrix_t *matrix) {
    size_t size = matrix->cols * matrix->rows * sizeof(int);
    matrix_t *new_matrix = malloc(sizeof(matrix_t));
    memcpy(new_matrix, matrix, sizeof(matrix_t));
    new_matrix->m = malloc(size);
    memcpy(new_matrix->m, matrix->m, size);
    return new_matrix;
}

void matrix_destroy(matrix_t *matrix) {
    free(matrix->m);
}

void matrix_free(matrix_t *matrix) {
    matrix_destroy(matrix);
    free(matrix);
}
