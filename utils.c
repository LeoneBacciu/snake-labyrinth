//
// Created by stark on 27/10/22.
//

#include "utils.h"
int clamp(const int low, const int value, const int high) {
    return value < low ? low : (value > high ? high : value);
}