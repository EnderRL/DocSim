#ifndef KSHINGLESPARSEMATRIX_H
#define KSHINGLESPARSEMATRIX_H
#include <unordered_map>
#include <unordered_set>
#include "utils.h"


class KShingleSparseMatrix {
    int k;
public:
    unordered_map<uint,unordered_set<uint>> mapa;

    KShingleSparseMatrix(int k);
    void add(uint document, const char* source, uint size);
};

#endif // KSHINGLEMAP_H
