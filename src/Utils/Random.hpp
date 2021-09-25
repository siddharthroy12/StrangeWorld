#ifndef UTIL_RANDOM_HPP
#define UTIL_RANDOM_HPP

#include <cstdlib>

// Stolen from Java to get non-biased random number
static int randRange(int min, int max) {
    int n = max - min + 1;
    int remainder = RAND_MAX % n;
    int x;
    do {
        x = rand();
    } while (x >= RAND_MAX - remainder);
    return min + x % n;
}

#endif
