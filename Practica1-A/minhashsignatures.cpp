#include "minhashsignatures.h"

MinHashSignatures::MinHashSignatures(uint t, uint k, vector<string> texts) {
    hashFunctions = vector<pair<uint, uint>>(t);
    signatures = matrix(t, vector<uint>(texts.size(), 0xFFFFFFFF));
    srand(time());
    for (uint i = 0; i < t; ++i) {
        hashFunctions[i] = pair<uint, uint>(rand(), rand());
    }
    const ull mod = 4294967296;
    uint j = 0;
    for (string text : texts) {
        for (uint i = 0; i <= text.size()-k; ++i) {
            ull hashed = KShingle::hashKShingle(text.substr(i, k));
            for (uint row = 0; row < t; ++row) {
                pair<uint, uint> p = hashFunctions[row];
                uint permutedRow = (p.first*hashed + p.second)%mod;
                signatures[row][j] = min(permutedRow, signatures[row][j]);
            }
        }
        ++j;
    }

    for (uint i = 0; i < t; ++i) {
        for (uint j = 0; j < texts.size(); ++j) {
            cout << signatures[i][j] << " ";
        }
        cout << endl;
    }
}

double MinHashSignatures::jaccard(uint a, uint b) {
    uint sum = 0;
    for (uint i = 0; i < t; ++i) {
        if (signatures[i][a] == signatures[i][b]) ++sum;
    }
    return double(sum)/t;
}
