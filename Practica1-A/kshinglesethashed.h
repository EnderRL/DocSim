#ifndef KSHINGLESETHASHED_H
#define KSHINGLESETHASHED_H
#include "kshingle.h"
#include <set>
using namespace std;

typedef set<uint>::iterator IteratorU;

class KShingleSetHashed : public KShingle {
    set<uint> kshingles;

public:
    KShingleSetHashed(int k, const char* source, uint size);
    uint size();
    double jaccard(const KShingle& Bs);
    void print();
};

#endif // KSHINGLESETHASHED_H
