#include "kshinglemap.h"
#include "kshingle.h"
#include <list>
#include <iostream>

kshinglemap::kshinglemap(int k) {
    this->k = k;
}

void kshinglemap::add(uint document, const char* source, uint size) {
    char subString[k];
    for (uint i = 0; i <= size-k; ++i) {
        for (int j = 0; j < k; ++j) {
            subString[j] =  source[i+j];
        }
        string aux(subString, k);
        uint hashed = KShingle::hashKShingle(aux);
        mapa[hashed].push_back(document);
    }
}

void kshinglemap::print() {
    unordered_map<uint,list<uint>>::iterator it = mapa.begin();
    while (it != mapa.end()) {
        cout << "El kshingle " << it->first << " esta en los documentos";
        for (uint x : it->second) cout << " " << x << endl;
    }
}
