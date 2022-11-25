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

#define MIN(a, b) (a<b? a : b)
#define MAX(a, b) (a>b? a : b)

int clamp(int low, int value, int high);


void sleep_ms(int milliseconds);

char *to_roman(int x);

void shuffle(int *array, size_t n);