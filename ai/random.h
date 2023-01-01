/**
 * @file random.h
 * @brief Collection of utility functions for random numbers
 */
#pragma once

#include <sys/time.h>
#include <stdlib.h>

/**
 * @brief Initializes the random seed using the current time
 */
void random_init();

/**
 * @brief Random integer in range
 * @param min
 * @param max
 * @return a random integer in the range [min, max]
 */
long random_range_int(int min, int max);

/**
 * @brief Random double in range
 * @param min
 * @param max
 * @return a random double in range [min, max)
 */
double random_range_double(double min, double max);

/**
 * @brief Shuffles an array using Fisher–Yates
 * @param array
 * @param n
 */
void random_shuffle(int *array, size_t n);
