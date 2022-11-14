#include "path.h"

path_t *path_create() {
    return NULL;
}

path_t *path_element(int value) {
    path_t *path = malloc(sizeof(path_t));
    path->size = 1;
    path->ref_count = 0;
    path->value = value;
    path->prev = NULL;
    return path;
}

path_t *path_add(path_t *path, int value) {
    path_t *node = path_element(value);
    node->prev = path;
    node->ref_count = 0;
    if (path == NULL) {
        node->size = 1;
    } else {
        node->size = path->size + 1;
        path->ref_count += 1;
    }
    return node;
}

path_values_t path_values(path_t *path) {
    int *arr = calloc(path->size, sizeof(int));
    path_t *node = path;
    for (size_t i = path->size; i > 0; --i) {
        arr[i - 1] = node->value;
        node = node->prev;
    }
    return (path_values_t) {path->size, arr};
}

void path_free(path_t *path) {
    path_t *prev, *node = path;
    while (node != NULL && node->ref_count == 0) {
        prev = node;
        node = node->prev;
        if (node != NULL) node->ref_count -= 1;
        free(prev);
    }
}
