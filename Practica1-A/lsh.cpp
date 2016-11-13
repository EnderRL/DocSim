#include "lsh.h"

LSH::LSH(const vector<vector<uint>>& matrix, uint b, uint r, uint mod) {
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

    /*for (uint i = 0; i < b; ++i) {
        cout << "Banda " << i << endl;
        for (uint j = 0; j < mod; ++j) {
            for (uint value : tablaHash[i][j]) {
                cout << value << " ";
            }
            cout << endl;
        }
    }*/
    tablaHash.clear();

    /*
    for (pair<uint, uint> p : setPairs)  {
        cout << p.first << " " << p.second << endl;
    }*/
}

set<pair<uint, uint> > LSH::getSetPairs() const
{
    return setPairs;
}

void LSH::insertHashTable(int j, int k) {
    vector<list<uint>>& hashTable = tablaHash[j/r];
    uint numeroHashed = hasheaNumero(j,k);
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


uint LSH::hasheaNumero(int j, int k) {
    const ull base = MAX_SIZE_4B;
    ull sum = 0;
    for (uint i = j; i < j+r-1; ++i) {
        sum = (((sum +  (*matrix)[i][k])%mod)*base)%mod;
    }
    sum += (*matrix)[j+r-1][k];
    return sum%mod;
}
