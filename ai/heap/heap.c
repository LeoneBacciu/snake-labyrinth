#include "heap.h"

heap_t *heap_create(size_t cap) {
    heap_t *heap = malloc(sizeof(heap_t));
    heap->cap = cap;
    heap->size = 0;
    heap->heap = malloc(cap * sizeof(heap_node_t));
    return heap;
}

void heap_insert(heap_t *heap, int key, void *value) {
    heap_node_t *node = malloc(sizeof(heap_node_t));
    node->key = key;
    node->value = value;
    heap_insert_node(heap, node);
}


void heap_insert_node(heap_t *heap, heap_node_t *node) {
    if (heap->size == heap->cap) heap_resize(heap, heap->cap * 2);

    size_t i = heap->size++;
    heap->heap[i] = node;

    size_t pi = heap_parent_index(i);
    heap_node_t *parent, *current;
    while (i > 0 && (parent = heap_get(heap, pi))->key > (current = heap_get(heap, i))->key) {
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

    size_t i = 0;
    heap_node_t *last = heap_get(heap, 0), *min = heap_get(heap, 0), *tmp;
    do {
        size_t l = heap_lchild_index(i), r = heap_rchild_index(i);
        if (l < heap->size && (tmp = heap_get(heap, l))->key < min->key) min = tmp;
        if (r < heap->size && (tmp = heap_get(heap, r))->key < min->key) min = tmp;
        if (min != last) {
            heap_swap_nodes(min, last);
            last = min;
        }
    } while (min != last);

    return value;
}

void heap_resize(heap_t *heap, size_t cap) {
    if (cap <= heap->cap) return;
    heap_node_t **new = malloc(cap * sizeof(heap_node_t *));
    memcpy(new, heap->heap, heap->cap * sizeof(heap_node_t *));
    heap->cap = cap;
    heap->heap = new;
}

bool heap_empty(heap_t *heap) {
    return heap->size == 0;
}

heap_node_t *heap_get(heap_t *heap, size_t i) {
    return heap->heap[i];
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

size_t heap_lchild_index(size_t i) { return (2 * i + 1); }

size_t heap_rchild_index(size_t i) { return (2 * i + 2); }


