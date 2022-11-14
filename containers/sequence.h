/**
 * @file sequence.h
 * @brief Immutable sequence DS
 */

#pragma once

#include <stdlib.h>
#include <memory.h>

/**
 * @struct sequence_t
 * @brief Immutable sequence of number
 *
 * @var sequence_t::size
 *  Number of elements
 * @var sequence_t::s
 *  Sequence of numbers
 *  @attention Do not use directly
 */
typedef struct {
    size_t size;
    int *s;
} sequence_t;

/**
 * @brief Creates an empty sequence
 * @return empty sequence {}
 */
sequence_t sequence_create();

/**
 * @brief Creates a sequence with the given value
 * @param value number
 * @return {value}
 */
sequence_t sequence_element(int value);

/**
 * @brief Creates a new sequence from the one given and the value
 * @param sequence previous sequence
 * @param value number
 * @return sequence + {value}
 */
sequence_t sequence_add(sequence_t sequence, int value);

/**
 * @brief Gets the element in position i
 * @param sequence
 * @param i index
 * @return ith element
 */
int sequence_get(sequence_t sequence, size_t i);

/**
 * @brief Gets the first element of the sequence
 * @param sequence
 * @return first element
 */
int sequence_first(sequence_t sequence);

/**
 * @brief Gets the last element of the sequence
 * @param sequence
 * @return last element
 */
int sequence_last(sequence_t sequence);

/**
 * @brief Deletes all the data
 * @param sequence
 * @note Does not free the sequence_t pointer
 */
void sequence_destroy(sequence_t *sequence);

/**
 * @brief Frees the memory and deletes all the data
 * @param sequence
 */
void sequence_free(sequence_t *sequence);
