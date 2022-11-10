#include "matrix.h"

matrix_t *matrix_create(size_t cols, size_t rows, ll val) {
    matrix_t *matrix = malloc(sizeof(matrix_t));
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->m = calloc(rows * cols, sizeof(ll));
    for (int i = 0; i < cols * rows; ++i) matrix->m[i] = val;
    return matrix;
}

ll matrix_get(matrix_t *matrix, size_t x, size_t y) {
    return matrix->m[y * matrix->cols + x];
}

void matrix_set(matrix_t *matrix, size_t x, size_t y, ll v) {
    matrix->m[y * matrix->cols + x] = v;
}

ll matrix_set_min(matrix_t *matrix, size_t x, size_t y, ll v) {
    ll o = matrix_get(matrix, x, y);
    if (v < o) {
        matrix_set(matrix, x, y, v);
        return v;
    }
    return o;
}

ll matrix_set_max(matrix_t *matrix, size_t x, size_t y, ll v) {
    ll o = matrix_get(matrix, x, y);
    if (v > o) {
        matrix_set(matrix, x, y, v);
        return v;
    }
    return o;
}

void matrix_destroy(matrix_t *matrix) {
    free(matrix->m);
    free(matrix);
}
