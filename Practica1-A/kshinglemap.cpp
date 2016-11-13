#include "kshinglemap.h"
#include "kshingle.h"
#include <list>
#include <iostream>

KShingleMap::KShingleMap(int k) {
    this->k = k;
}

void KShingleMap::add(uint document, const char* source, uint size) {
    char subString[k];
    for (uint i = 0; i <= size-k; ++i) {
        uint hashed = KShingle::hashKShingle(source, i, i+k-1);
        mapa[hashed].push_back(document);
    }
}

void KShingleMap::print() {
    unordered_map<uint,list<uint>>::iterator it = mapa.begin();
    while (it != mapa.end()) {
        cout << "El kshingle " << it->first << " esta en los documentos";
        for (uint x : it->second) cout << " " << x << endl;
    }
}
