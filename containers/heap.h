/**
 * @file heap.h
 * @brief Max Heap DS
 */

#pragma once

#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>

/**
 * @struct heap_node_t
 * @brief A node of a Max Heap
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
 * @brief Max Heap DS
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
 * @brief Creates a Max Heap
 * @param cap initial capacity of the h
 * @return pointer to a new Max Heap
 */
heap_t *heap_create(size_t cap);

/**
 * @brief Inserts a new element in the Heap
 * @param heap
 * @param key the higher the key, the higher the priority
 * @param value pointer to any object in memory
 */
void heap_insert(heap_t *heap, int key, void *value);

/**
 * @brief Extracts the element with the highest key
 * @param heap
 * @return pointer to the value of the element
 */
void *heap_extract(heap_t *heap);

/**
 * @brief Changes the capacity of the Max Heap (only if bigger)
 * @param heap
 * @param cap new capacity
 */
void heap_resize(heap_t *heap, size_t cap);

/**
 * @brief Checks if the Max Heap is empty
 * @param heap
 * @return true if the Heap is empty, else false
 */
bool heap_empty(heap_t *heap);

/**
 * @brief Deletes all the data
 * @param heap
 * @note Does not free the heap_t pointer
 */
void heap_destroy(heap_t *heap);

/**
 * @brief Frees the memory and deletes all the data
 * @param heap
 */
void heap_free(heap_t *heap);
