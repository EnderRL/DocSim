#ifndef KSHINGLEHASH_H
#define KSHINGLEHASH_H

#include "kshingle.h"
#include <set>
#include <iostream>
using namespace std;

class KShingleHash : public KShingle {
    set<uint> kshingles;
public:
    KShingleHash(int k, const string& source);
};

#endif // KSHINGLEHASH_H
