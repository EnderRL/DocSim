#ifndef MINHASHSIGNATURES_H
#define MINHASHSIGNATURES_H

#include <unordered_set>
#include "kshingle.h"
#include "kshinglesparsematrix.h"
#include "reader.h"
#include "utils.h"

enum PermutationMode {
    Hash,
    Hash32,
    HashWithPrime,
    Random
};

typedef vector<vector<uint>> matrix;

class MinHashSignatures {

    matrix signatures;
    uint medida;
    uint medidaFinal;
    void randomPermutations(const KShingleSparseMatrix& map, bool tiempo);
    void permutations32(const vector<string>& texts, uint t, uint k, bool tiempo);

public:
    MinHashSignatures(uint t, uint k, const vector<string>& texts, PermutationMode mode, bool tiempo,uint seed);
    double jaccard(uint a, uint b);
    uint size();
    uint finalSize();
    matrix getSignatures() const;

};

#endif // MINHASHSIGNATURES_H
