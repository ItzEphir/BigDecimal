//
// Created by ephir on 26.02.2025.
//

#include "../include/Maths.h"
#include <stdexcept>

int64_t ephir::bigdecimal::maths::fast_log2(uint64_t n) {
    if (n <= 0)
        throw std::out_of_range("log expects value grater than zero");

    static const uint64_t lookup[64] = {
        0, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4,
        5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
        6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
        6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6
    };

    if (n == 0) return 0;

    uint64_t log = 0;
    if (n >= static_cast<size_t>(1) << 32) {
        n >>= 32;
        log += 32;
    }
    if (n >= static_cast<size_t>(1) << 16) {
        n >>= 16;
        log += 16;
    }
    if (n >= static_cast<size_t>(1) << 8) {
        n >>= 8;
        log += 8;
    }
    if (n >= static_cast<size_t>(1) << 4) {
        n >>= 4;
        log += 4;
    }
    log += lookup[n - 1];
    return log;
}
