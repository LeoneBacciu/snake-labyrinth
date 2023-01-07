/**
 * @file utils.h
 * @brief Collection of generic utility functions
 */

#pragma once

#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <stdlib.h>

#ifdef WIN32

#include <winbase.h>

#elif _POSIX_C_SOURCE >= 199309L

#include <time.h>

#else

#include <unistd.h>

#endif

#define MIN(a, b) (a<b? a : b) ///< @brief Generic min function
#define MAX(a, b) (a>b? a : b) ///< @brief Generic max function

/**
 * @brief Clamps a number between low and high
 * @param low
 * @param value
 * @param high
 * @return the clamped number
 */
int clamp(int low, int value, int high);

/**
 * @brief Sleeps for a certain time in milliseconds
 * @param milliseconds the sleep time
 */
void sleep_ms(int milliseconds);

/**
 * @brief Converts the score from arabic to latin numbers
 * @param x the score in arabic numbers
 * @return the score in latin numbers
 */
char *to_roman(int x);
