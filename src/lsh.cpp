#include "lsh.h"

LSH::LSH(const vector<vector<uint>>& matrix, uint b, uint r, uint mod, bool tiempo) {
    this->b = b;
    this->r = r;
    this ->mod = mod;
    this->matrix = &matrix;
    int n = matrix.size();
    int m = matrix[0].size();
    tablaHash = vector<vector<list<uint>>>(b,vector<list<uint>>(mod));
    //PRIMERO RECORREMOS POR BUCKETS
    for (int j = 0; j < n; j+= r){
        for (int k = 0 ; k < m; ++k) {
        //LUEGO VAMOS MIRANDO LOS DIGITOS DE CADA COLUMNA K
            insertHashTable(j, k);

        }
    }
    if (!tiempo) {
        executionSize = 0;
        for (int i = 0; i < tablaHash.size(); ++i) {
            for (int j = 0; j < tablaHash[i].size(); ++j) {
                executionSize += sizeof(uint)*tablaHash[i][j].size();
            }
        }
    }
    tablaHash.clear();

}

void LSH::insertHashTable(int j, int k) {
    vector<list<uint>>& hashTable = tablaHash[j/r];
    uint numeroHashed = numberHash(j,k);
    for (uint x : hashTable[numeroHashed]) {
        uint a, b;
        if (x < k) {
            a = x;
            b = k;
        }
        else {
            a = k;
            b = x;
        }
        pair<uint,uint> auxPair = pair<uint,uint>(a,b);
        setPairs.insert(auxPair);
    }
    hashTable[numeroHashed].push_back(k);
}


uint LSH::numberHash(int j, int k) {
    const ull base = MAX_SIZE_4B;
    ull sum = 0;
    for (uint i = j; i < j+r-1; ++i) {
        sum = (((sum +  (*matrix)[i][k])%mod)*base)%mod;
    }
    sum += (*matrix)[j+r-1][k];
    return sum%mod;
}

set<pair<uint, uint> >* LSH::getSetPairs() {
    return &setPairs;
}

uint LSH::size() {
   return sizeof(pair<uint,uint>)*setPairs.size() + executionSize;
}
