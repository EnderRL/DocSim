#ifndef LSH_H
#define LSH_H
#include <iostream>
#include <set>
#include "utils.h"


class LSH {
    uint b, r, mod,  executionSize;
    const vector<vector<uint>>* matrix;
    vector<vector<list<uint>>> tablaHash;
    set<pair<uint,uint>> setPairs;

    void insertHashTable(int j, int k);
    uint numberHash(int i, int j);

public:
    LSH(const vector<vector<uint>>& matrix, uint b, uint r, uint mod, bool tiempo);
    set<pair<uint, uint> >* getSetPairs();
    uint size();
};

#endif // LSH_H
