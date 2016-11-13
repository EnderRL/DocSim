#include "kshinglesethashed.h"

KShingleSetHashed::KShingleSetHashed(int k, const char* source, uint size) : KShingle(k) {

    for (uint i = 0; i < size; ++i) cout << source[i];

    cout << endl;

    for (uint i = 0; i <= size-k; ++i) {
        uint result = hashKShingle(source, i, i+k-1);
        kshingles.insert(result);
    }
}

double KShingleSetHashed::jaccard(const KShingle &Bs) {
    const KShingleSetHashed& B = (KShingleSetHashed&)Bs;
    int unionSize = 0;
    int interSize = 0;
    IteratorU i = kshingles.begin();
    int ipos = 0;
    IteratorU j = B.kshingles.cbegin();
    int jpos = 0;
    while (i != kshingles.end() and j != B.kshingles.cend()) {
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
    if (i == kshingles.end()) {
        unionSize += B.kshingles.size() - jpos;
    }
    else if (j == B.kshingles.end()) {
        unionSize += kshingles.size() - ipos;
    }
    return (double)interSize/unionSize;
}

void KShingleSetHashed::print() {
    for (uint s : kshingles) {
        cout << s << endl;
    }
}

uint KShingleSetHashed::size() {
    return kshingles.size();
}
