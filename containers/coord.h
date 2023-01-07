/**
 * @file coord.h
 * @brief Coordinate Wrapper
 */

#pragma once

/**
 * @def c(x, y)
 * @brief Creates a coord_t from x/y pair
 */
#define c(x, y) ((coord_t) {x, y})

/**
 * @def cx(crd)
 * @brief Explodes a coord_t in "x, y"
 * @attention Use carefully, mainly for back-compatibility
 */
#define cx(crd) (crd).x, (crd).y

/**
 * @def c_eq(a, b)
 * @brief Checks if a and b are equal
 */
#define c_eq(a, b) ((a).x == (b).x && (a).y == (b).y)

/**
 * @def c_add(a, b)
 * @brief Creates a coord_t by adding a and b
 */
#define c_add(a, b) c((a).x + (b).x, (a).y + (b).y)

/**
 * @struct coord_t
 * @brief Represents an x/y pair
 *
 * @var coord_t::x
 *  X coordinate
 * @var coord_t::y
 *  Y coordinate
 */
typedef struct {
    int x, y;
} coord_t;

