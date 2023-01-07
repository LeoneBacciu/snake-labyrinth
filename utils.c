/**
 * @file utils.c
 */

#include "utils.h"

int clamp(const int low, const int value, const int high) {
    return value < low ? low : (value > high ? high : value);
}

void sleep_ms(int milliseconds) {
#ifdef WIN32
    Sleep(milliseconds);
#elif _POSIX_C_SOURCE >= 199309L
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
#else
    if (milliseconds >= 1000)
      sleep(milliseconds / 1000);
    usleep((milliseconds % 1000) * 1000);
#endif
}

char *to_roman(int x) {
    if (x == 0) return "Nihil";
    char *numerus[] = {"M\0", "CM\0", "D\0", "CD\0", "C\0", "XC\0", "L\0", "XL\0", "X\0", "IX\0", "V\0", "IV\0", "I\0"};
    int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    char *out = calloc(50, sizeof(char));
    if (x < 0) {
        x *= -1;
        out[0] = '-';
    }
    while (x > 0) {
        for (int i = 0; i < 13; ++i) {
            if (x >= values[i]) {
                x -= values[i];
                out = strcat(out, numerus[i]);
                break;
            }
        }
    }


    return out;
}
