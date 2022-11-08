#pragma once

#include <malloc.h>
#include <stdio.h>

#define MIN(a, b) (a<b? a : b)
#define MAX(a, b) (a>b? a : b)

int clamp(int low, int value, int high);
