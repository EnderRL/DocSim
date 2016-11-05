#include "kshingle.h"

KShingle::KShingle(int k) {
    this->k = k;
}

uint KShingle::hashKShingle(const string& kshingle) {
    const uint base = 256;
    const ull mod = 4294967296;
    ull sum = 0;
    for (uint i = 0; i < kshingle.size()-1; ++i) {
        sum = (((sum +  kshingle[i])%mod)*base)%mod;
    }
    sum += kshingle[kshingle.size()-1];
    return sum%mod;
}

uint KShingle::hashKShingle(const char* kshingle, uint size) {
    const uint base = 256;
    const ull mod = 4294967296;
    ull sum = 0;
    for (uint i = 0; i < size-1; ++i) {
        sum = (((sum +  kshingle[i])%mod)*base)%mod;
    }
    sum += kshingle[size-1];
    return sum%mod;
}
