#include "kshingle.h"

KShingle::KShingle(int k) {
    this->k = k;
}

uint KShingle::hashKShingle(const char *kshingle, uint firstIndex, uint lastIndex) {
    const uint base = 128;
    const ull mod = MAX_SIZE_4B;

    ull sum = 0;
    uint i;
    for (i = firstIndex; i+3 <= lastIndex; i += 4) {
        uint hashed = 0;
        for (uint  j = i; j < i+3; ++j) {
            hashed = (hashed + kshingle[j])*base;
        }
        hashed += kshingle[i+3];
        sum = (sum + hashed)%mod;
    }
    if (i <= lastIndex) {
        uint hashed = 0;
        while (i < lastIndex) {
            hashed = (hashed + kshingle[i])*base;
            ++i;
        }
        hashed += kshingle[lastIndex];
        sum = (sum+hashed)%mod;
    }
    return sum;
}
