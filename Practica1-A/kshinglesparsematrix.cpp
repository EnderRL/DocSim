#include "kshinglesparsematrix.h"
#include "kshingle.h"
#include <list>
#include <iostream>

KShingleSparseMatrix::KShingleSparseMatrix(int k) {
    this->k = k;
}

void KShingleSparseMatrix::add(uint document, const char* source, uint size) {

    for (uint i = 0; i <= size-k; ++i) {
        uint hashed = KShingle::hashKShingle(source, i, i+k-1);
        mapa[hashed].insert(document);
    }
}


