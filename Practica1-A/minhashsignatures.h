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
using namespace std;

enum PermutationMode {
    Hash,
    HashWithPrime,
    Random
};

typedef unsigned int uint;
typedef vector<vector<uint>> matrix;

class MinHashSignatures {
    vector<pair<uint, uint>> hashFunctions;
    matrix signatures;

    void RandomPermutations(const KShingleMap& map);
public:
    MinHashSignatures(uint t, uint k, const vector<string>& texts, PermutationMode mode);
    double jaccard(uint a, uint b);
    matrix getSignatures() const;
};

#endif // MINHASHSIGNATURES_H
