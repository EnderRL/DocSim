#ifndef KSHINGLESETHASHED_H
#define KSHINGLESETHASHED_H
#include "kshingle.h"
#include <set>

typedef set<uint>::iterator IteratorU;

class KShingleSetHashed : public KShingle {
    set<uint> kshingles;

public:
    KShingleSetHashed(int k, const char* source, uint size);
    uint size();
    static double jaccard(const KShingleSetHashed& A, const KShingleSetHashed& B);
};

#endif // KSHINGLESETHASHED_H
