#include "kshingleset.h"


KShingleSet::KShingleSet(int k, const char* source, uint size) : KShingle(k) {
    char subString[k];
    for (uint i = 0; i <= size-k; ++i) {
        for (int j = 0; j < k; ++j) {
            subString[j] =  source[i+j];
        }
        string aux(subString, k);
        kshingles.insert(aux);
    }
}

double KShingleSet::jaccard(const KShingleSet &A, const KShingleSet &B) {
    uint unionSize = 0;
    uint interSize = 0;
    IteratorS i = A.kshingles.cbegin();
    uint ipos = 0;
    IteratorS j = B.kshingles.cbegin();
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



uint KShingleSet::size() {
    return kshingles.size()*(k*sizeof(char));
}

