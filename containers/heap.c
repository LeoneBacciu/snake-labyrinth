#include "heap.h"

heap_t *heap_create(size_t cap) {
    heap_t *heap = malloc(sizeof(heap_t));
    heap->cap = cap;
    heap->size = 0;
    heap->h = calloc(cap, sizeof(heap_node_t));
    return heap;
}

void heap_insert(heap_t *heap, int key, void *value) {
    heap_node_t node = (heap_node_t) {key, value};
    heap_insert_node(heap, node);
}

void heap_insert_node(heap_t *heap, heap_node_t node) {
    if (heap->size == heap->cap) heap_resize(heap, heap->cap * 2);

    size_t i = heap->size++;
    heap->h[i] = node;

    size_t pi = heap_parent_index(i);
    heap_node_t *parent, *current;
    while (i > 0 && (parent = heap_get(heap, pi))->key < (current = heap_get(heap, i))->key) {
        heap_swap_nodes(parent, current);
        i = pi;
        pi = heap_parent_index(pi);
    }
}

void *heap_extract(heap_t *heap) {
    if (heap->size == 0) return NULL;
    heap_node_t *root = heap_get(heap, 0);
    void *value = root->value;
    heap_swap_nodes(root, heap_get(heap, --heap->size));

    size_t i = 0, max_i = 0;
    heap_node_t *last = heap_get(heap, 0), *max = heap_get(heap, 0);
    while (1) {
        size_t l = heap_lchild_index(i), r = heap_rchild_index(i);
        heap_node_t *lnode = heap_get(heap, l), *rnode = heap_get(heap, r);
        if (r < heap->size && rnode->key >= max->key) {
            max_i = r;
            max = rnode;
        }
        if (l < heap->size && lnode->key >= max->key) {
            max_i = l;
            max = lnode;
        }

        if (max == last) break;

        heap_swap_nodes(max, last);
        last = max;
        i = max_i;
    }

    return value;
}

void heap_resize(heap_t *heap, size_t cap) {
    if (cap <= heap->cap) return;
    heap->cap = cap;
    heap->h = realloc(heap->h, cap * sizeof(heap_node_t));
}

bool heap_empty(heap_t *heap) {
    return heap->size == 0;
}

void heap_destroy(heap_t *heap) {
    free(heap->h);
}

void heap_free(heap_t *heap) {
    heap_destroy(heap);
    free(heap);
}

heap_node_t *heap_get(heap_t *heap, size_t i) {
    return &heap->h[i];
}

size_t heap_parent_index(size_t i) {
    if (i < 1) return 0;
    return (i - 1) / 2;
}

void heap_swap_nodes(heap_node_t *a, heap_node_t *b) {
    heap_node_t tmp = *a;
    *a = *b;
    *b = tmp;
}

size_t heap_lchild_index(size_t i) {
    return (2 * i + 1);
}

size_t heap_rchild_index(size_t i) {
    return (2 * i + 2);
}
