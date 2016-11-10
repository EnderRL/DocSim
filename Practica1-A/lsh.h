#ifndef LSH_H
#define LSH_H
#include <vector>
using namespace std;

typedef unsigned int uint;
typedef unsigned long long ull;
const ull MAX_SIZE_4B =  4294967296;

class LSH {
private:
    uint b, r, mod;
    vector<vector<uint>> *matrix;
    list<list<uint>> posiblesParejas;
    vector<vector<list<uint>>> tablaHash;
    void insertHash(int j, int k);
    uint hasheaNumero(int i, int j, int k);
public:
    LSH(const vector<vector<uint>>& matrix, uint b, uint r);

};



#endif // LSH_H
