#include "path.h"

path_t *path_create() {
    return NULL;
}

path_t *path_element(int value) {
    path_t *path = malloc(sizeof(path_t));
    path->size = 1;
    path->ref_count = 1;
    path->value = value;
    path->prev = NULL;
    return path;
}

path_t *path_add(path_t *path, int value) {
    path_t *node = path_element(value);
    node->prev = path;
    if (path == NULL) {
        node->size = 1;
    } else {
        node->size = path->size + 1;
        path->ref_count += 1;
    }
    return node;
}

path_values_t path_values(path_t *path) {
    if (path == NULL) return (path_values_t) {0, NULL};

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
    while (node != NULL && --(node->ref_count) == 0) {
        prev = node;
        node = node->prev;
        free(prev);
    }
}

path_t *path_copy(path_t *path) {
    if (path == NULL) return NULL;

    path_t *node = malloc(sizeof(path_t)), *next, *initial;
    memcpy(node, path, sizeof(path_t));
    initial = node;
    while (node->prev != NULL) {
        next = malloc(sizeof(path_t));
        memcpy(next, node->prev, sizeof(path_t));
        node->prev = next;
        node = next;
    }
    return initial;
}

path_t *path_assign(path_t *path) {
    if (path != NULL) path->ref_count += 1;
    return path;
}
