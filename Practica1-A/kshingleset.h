#ifndef KSHINGLESET_H
#define KSHINGLESET_H

#include "kshingle.h"
#include <set>
#include <iostream>
using namespace std;

typedef set<string>::iterator Iterator;

class KShingleSet : public KShingle {

    set<string> kshingles;

public:
    KShingleSet(int k, const string& source);
    KShingleSet(int k, const char* source, uint size);
    int size();
    double jaccard(const KShingle& Bs);
    void print();
};

#endif // KSHINGLESET_H
