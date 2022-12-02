#pragma once

#ifdef __WIN32
#else

#include <stdlib.h>
#include <sys/time.h>

#endif

void random_init();

long random_range_int(int min, int max);

double random_range_double(double min, double max);

void random_shuffle(int *array, size_t n);
