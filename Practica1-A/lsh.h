#ifndef LSH_H
#define LSH_H
#include <vector>
#include <list>
#include <iostream>
#include <set>
using namespace std;

typedef unsigned int uint;
typedef unsigned long long ull;

class LSH {
    uint b, r, mod;
    const vector<vector<uint>>* matrix;
    list<list<uint>> posiblesParejas;
    vector<vector<list<uint>>> tablaHash;
    set<pair<uint,uint>> setPairs;

    void insertHashTable(int j, int k);
    uint hasheaNumero(int i, int j);

public:
    static const ull MAX_SIZE_4B = 4294967296;
    LSH(const vector<vector<uint>>& matrix, uint b, uint r, uint mod);
};

#endif // LSH_H
