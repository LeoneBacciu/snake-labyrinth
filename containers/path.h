/**
 * @file path.h
 * @brief Special Linked List DS to represent a Path
 */

#pragma once

#include <stdlib.h>
#include <memory.h>

/**
 * @struct path_t
 * @brief Last node of the Path
 *
 * @var path_t::size
 *  Length of the Path
 * @var path_t::ref_count
 *  Reference count used to free the memory
 *  @attention Do not use directly
 * @var path_t::value
 *  Value of the node (last value)
 * @var path_t::prev
 *  Previous node of the Path
 *  @attention Do not use directly
 */
struct path_t {
    size_t size, ref_count;
    int value;
    struct path_t *prev;
};

struct path_t;
typedef struct path_t path_t; ///< @private

/**
 * @struct path_values_t
 * @brief Ordered representation of a Path, for efficient access
 *
 * @var path_values_t::size
 *  Length of the Path
 * @var path_values_t::values
 *  Path as an array of length size
 */
typedef struct {
    size_t size;
    int *values;
} path_values_t;

/**
 * @brief Creates an empty Path
 * @return empty Path {}
 */
path_t *path_create();

/**
 * @brief Creates a path of one node
 * @param value number
 * @return {value}
 */
path_t *path_element(int value);

/**
 * @brief Creates a copy of the path
 * @param path
 * @return path_t*
 */
path_t *path_copy(path_t *path);

/**
 * @brief Increments the ref counter, use this instead of direct assignment
 * @param path
 * @return path_t*, the same as path
 */
path_t *path_assign(path_t *path);

/**
 * @brief Creates a new Path from the one given and the value
 * @param path base Path
 * @param value number to append
 * @return path + {value}
 */
path_t *path_add(path_t *path, int value);

/**
 * @brief Transforms a path_t in the corresponding path_values_t
 * @param path
 * @return Array of the values of the path_t in order of insertion
 */
path_values_t path_values(path_t *path);

/**
 * @brief Frees the current node and all previous if possible
 * @param path
 */
void path_free(path_t *path);
