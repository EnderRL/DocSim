#include "minhashsignatures.h"

MinHashSignatures::MinHashSignatures(uint t, uint k, vector<string> texts) {
    hashFunctions = vector<pair<uint, uint>>(t);
    signatures = matrix(t, vector<uint>(texts.size(), 0xFFFFFFFF));
    srand(time(NULL));
    for (uint i = 0; i < t; ++i) {
        hashFunctions[i] = pair<uint, uint>(rand(), rand());
        cout << "H" << i << " es " << hashFunctions[i].first << "x + " << hashFunctions[i].second << " mod 2^32" << endl;
    }
    const ull mod = 4294967296;
    uint j = 0;
    for (string text : texts) {
        for (uint i = 0; i <= text.size()-k; ++i) {
            ull hashed = KShingle::hashKShingle(text.substr(i, k));
            cout << "He sacado el kshingle " << text.substr(i,k) << " del texto " << j << " y su hasheado me ha dao " << hashed << endl;
            for (uint row = 0; row < t; ++row) {
                pair<uint, uint> p = hashFunctions[row];
                uint permutedRow = ((p.first*hashed)%mod + p.second)%mod;
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

MinHashSignatures::MinHashSignatures(uint t, uint k, vector<char *> texts, vector<uint> textSize) {
    hashFunctions = vector<pair<uint, uint>>(t);
    signatures = matrix(t, vector<uint>(texts.size(), 0xFFFFFFFF));
    srand(time(NULL));
    for (uint i = 0; i < t; ++i) {
        hashFunctions[i] = pair<uint, uint>(rand(), rand());
        cout << "H" << i << " es " << hashFunctions[i].first << "x + " << hashFunctions[i].second << " mod 2^32" << endl;
    }
    const ull mod = 4294967296;
    uint j = 0;
    char subString[k+1];
    subString[k] = 0;
    for (char* text : texts) {
        for (uint i = 0; i <= textSize[j]-k; ++i) {
            for (uint l = 0; l < k; ++l) {
                subString[l] = text[i+l];
            }
            ull hashed = KShingle::hashKShingle(subString);
            cout << "He sacado el kshingle " << subString << " del texto " << j << " y su hasheado me ha dao " << hashed << endl;
            for (uint row = 0; row < t; ++row) {
                pair<uint, uint> p = hashFunctions[row];
                uint permutedRow = ((p.first*hashed)%mod + p.second)%mod;
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
    for (uint i = 0; i < signatures.size(); ++i) {
        if (signatures[i][a] == signatures[i][b]) ++sum;
    }
    cout << "Hay " << sum << " filas iguales y " << signatures.size() << " filas en total." << endl;
    return double(sum)/signatures.size();
}
