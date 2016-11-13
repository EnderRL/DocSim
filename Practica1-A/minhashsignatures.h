#ifndef MINHASHSIGNATURES_H
#define MINHASHSIGNATURES_H

#include <vector>
#include <string>
#include <iostream>
#include <ctime>
#include "kshingle.h"
#include "kshinglemap.h"
#include <unordered_set>
#include <fstream>
#include <list>
using namespace std;

enum PermutationMode {
    Hash,
    HashWithPrime,
    Random
};

typedef unsigned int uint;
typedef vector<vector<uint>> matrix;

class MinHashSignatures {

    matrix signatures;
    uint medida;
    uint medidaFinal;
    bool tiempo;


    void RandomPermutations(const KShingleMap& map, bool tiempo);
public:
    MinHashSignatures(uint t, uint k, const vector<string>& texts, PermutationMode mode, bool tiempo);
    double jaccard(uint a, uint b);
    uint size();
    uint finalSize();
};

#endif // MINHASHSIGNATURES_H
