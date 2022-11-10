/**
 * @file h.h
 * @brief An implementation of a Min Heap DS
 */

#pragma once

#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>

/**
 * @struct heap_node_t
 * @brief A node of a Min Heap
 *
 * @var heap_node_t::key
 *  The sorting key
 * @var heap_node_t::value
 *  A pointer to the corresponding object
 */
typedef struct {
    int key;
    void *value;
} heap_node_t;

/**
 * @struct heap_t
 * @brief Min Heap DS
 *
 * @var heap_t::cap
 *  Capacity of the Heap
 * @var heap_t::size
 *  Current size of the Heap
 * @var heap_t::h
 *  Tree of nodes, stored as an array
 *  @attention Do not use directly
 *  @see heap_node_t
 */
typedef struct {
    size_t cap;
    size_t size;
    heap_node_t *h;
} heap_t;

/**
 * @brief Creates a Min Heap
 * @param cap initial capacity of the h
 * @return pointer to a new Min Heap
 */
heap_t *heap_create(size_t cap);

/**
 * @brief Inserts a new element in the Heap
 * @param heap
 * @param key the smaller the key, the higher the priority
 * @param value pointer to any object in memory
 */
void heap_insert(heap_t *heap, int key, void *value);

/**
 * @brief Inserts a Node directly
 * @note Not suggested
 * @param heap
 * @param node instance of a heap_node_t
 * @see heap_insert
 */
void heap_insert_node(heap_t *heap, heap_node_t node);

/**
 * @brief Extracts the element with the lowest key
 * @param heap
 * @return pointer to the value of the element
 */
void *heap_extract(heap_t *heap);

/**
 * @brief Changes the capacity of the Min Heap (only if bigger)
 * @param heap
 * @param cap new capacity
 */
void heap_resize(heap_t *heap, size_t cap);

/**
 * @brief Checks if the Min Heap is empty
 * @param heap
 * @return true if the Heap is empty, else false
 */
bool heap_empty(heap_t *heap);

/**
 * Frees the memory deleting all the data
 * @param heap
 */
void heap_destroy(heap_t *heap);

/**
 * @brief Gets the ith node
 * @attention For internal use only
 * @param heap
 * @param i index in the internal array
 * @return pointer to ith node
 */
heap_node_t *heap_get(heap_t *heap, size_t i);

/**
 * @brief Calculates the index of the parent
 * @attention For internal use only
 * @param i child
 * @return parent
 */
size_t heap_parent_index(size_t i);

/**
 * @brief Calculates the index of the left child
 * @attention For internal use only
 * @param i parent
 * @return child
 */
size_t heap_lchild_index(size_t i);

/**
 * @brief Calculates the index of the right child
 * @attention For internal use only
 * @param i parent
 * @return child
 */
size_t heap_rchild_index(size_t i);

/**
 * @brief Swaps two nodes
 * @attention For internal use only
 * @param a pointer to first node
 * @param b pointer to second node
 */
void heap_swap_nodes(heap_node_t *a, heap_node_t *b);
