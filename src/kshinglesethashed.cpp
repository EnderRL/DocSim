#include "kshinglesethashed.h"

KShingleSetHashed::KShingleSetHashed(int k, const char* source, uint size) : KShingle(k) {
    for (uint i = 0; i <= size-k; ++i) {
        uint result = hashKShingle(source, i, i+k-1);
        kshingles.insert(result);
    }
}

double KShingleSetHashed::jaccard(const KShingleSetHashed &A, const KShingleSetHashed &B) {
    uint unionSize = 0;
    uint interSize = 0;
    IteratorU i = A.kshingles.cbegin();
    uint ipos = 0;
    IteratorU j = B.kshingles.cbegin();
    uint jpos = 0;
    while (i != A.kshingles.cend() and j != B.kshingles.cend()) {
        if (*i == *j) {
            ++interSize;
            ++i;
            ++ipos;
            ++j;
            ++jpos;
        }
        else if (*i < *j) {
            ++i;
            ++ipos;
        }
        else {
            ++j;
            ++jpos;
        }
        ++unionSize;
    }
    if (i == A.kshingles.cend()) unionSize += B.kshingles.size() - jpos;
    else unionSize += A.kshingles.size() - ipos;
    return (double)interSize/unionSize;
}


uint KShingleSetHashed::size() {
    return kshingles.size()*sizeof(uint);
}
