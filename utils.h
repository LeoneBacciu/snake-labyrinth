//
// Created by stark on 27/10/22.
//

#ifndef SNAKE_LABYRINTH_UTILS_H
#define SNAKE_LABYRINTH_UTILS_H

#include <malloc.h>
#include <stdio.h>

int clamp(int low, int value, int high);


#ifdef _WIN32
__size_t getline(char **lineptr, size_t *n, FILE *stream);
#endif

#endif //SNAKE_LABYRINTH_UTILS_H
