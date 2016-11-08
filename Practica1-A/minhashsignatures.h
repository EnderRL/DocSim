#ifndef MINHASHSIGNATURES_H
#define MINHASHSIGNATURES_H

#include <vector>
#include <string>
#include <iostream>
#include <ctime>
#include <unordered_set>
#include "kshingle.h"
using namespace std;

typedef unsigned int uint;
typedef vector<vector<uint>> matrix;

class MinHashSignatures {
    vector<pair<uint, uint>> hashFunctions;
    matrix signatures;
public:
    MinHashSignatures(uint t, uint k, vector<string> texts);
    MinHashSignatures(uint t, uint k, vector<char*> texts, vector<uint> textSize);
    double jaccard(uint a, uint b);
};

#endif // MINHASHSIGNATURES_H
