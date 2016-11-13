#ifndef KSHINGLESET_H
#define KSHINGLESET_H

#include "kshingle.h"
#include <set>
using namespace std;

typedef set<string>::iterator IteratorS;

class KShingleSet : public KShingle {

    set<string> kshingles;

public:
    KShingleSet(int k, const string& source);
    KShingleSet(int k, const char* source, uint size);
    uint size();
    static double jaccard(const KShingleSet& A, const KShingleSet& B);
    double jaccard(const KShingle& Bs);
    void print();
};

#endif // KSHINGLESET_H
