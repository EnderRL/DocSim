#include "kshinglemap.h"
#include "kshingle.h"
#include <list>
#include <iostream>

KShingleMap::KShingleMap(int k) {
    this->k = k;
}

void KShingleMap::add(uint document, const char* source, uint size) {

    for (uint i = 0; i <= size-k; ++i) {
        //cout << "size: " << size << endl;
        //cout << i << endl;
        uint hashed = KShingle::hashKShingle(source, i, i+k-1);
        mapa[hashed].insert(document);
    }
}

void KShingleMap::print() {

    for (pair<uint,unordered_set<uint>> it : mapa) {
        cout << "El kshingle " << it.first << " esta en los documentos ";
        for (uint x : it.second) cout << x << " ";
        cout << endl;
    }
}
