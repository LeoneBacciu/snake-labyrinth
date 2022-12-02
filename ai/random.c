#include "random.h"

void random_init() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    long usec = tv.tv_usec;
#ifdef __WIN32
    srand(usec);
#else
    srand48(usec);
#endif
}

long random_range_int(int min, int max) {
#ifdef __WIN32
    return rand() % (max + 1 - min) + min;
#else
    return lrand48() % (max + 1 - min) + min;
#endif
}

double random_range_double(double min, double max) {
#ifdef __WIN32
    return rand() * (max - min) / RAND_MAX + min;
#else
    return drand48() * (max - min) + min;
#endif
}

void random_shuffle(int *array, size_t n) {
    if (n > 1) {
        for (size_t i = n - 1; i > 0; i--) {
            size_t j = (unsigned int) random_range_double(0, i + 1);
            int t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
}
