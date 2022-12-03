#pragma once

#include <sys/time.h>
#include <stdlib.h>


void random_init();

long random_range_int(int min, int max);

double random_range_double(double min, double max);

void random_shuffle(int *array, size_t n);
