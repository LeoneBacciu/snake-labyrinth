/**
 * @file sequence.h
 * @brief Immutable sequence DS
 */

#pragma once

#include <stdlib.h>
#include <memory.h>

typedef long long ll;

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
    ll *s;
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
sequence_t sequence_element(ll value);

/**
 * Creates a new sequence from the one given and the value
 * @param sequence previous sequence
 * @param value number
 * @return sequence + {value}
 */
sequence_t sequence_add(sequence_t sequence, ll value);

/**
 * Gets the element in position i
 * @param sequence
 * @param i index
 * @return ith element
 */
ll sequence_get(sequence_t sequence, size_t i);

/**
 * Gets the first element of the sequence
 * @param sequence
 * @return first element
 */
ll sequence_first(sequence_t sequence);

/**
 * Gets the last element of the sequence
 * @param sequence
 * @return last element
 */
ll sequence_last(sequence_t sequence);

/**
 * Frees the memory and deletes all the data
 * @param sequence
 */
void sequence_destroy(sequence_t *sequence);
