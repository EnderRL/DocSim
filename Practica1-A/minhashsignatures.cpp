#include "minhashsignatures.h"
#include "kshinglemap.h"

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



/*MinHashSignatures::MinHashSignatures(uint t, uint k, vector<char *> texts, vector<uint> textSize) {
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
}*/

bool isPrime(uint number) {

    if (number == 2 || number == 3)
        return true;

    if (number % 2 == 0 || number % 3 == 0)
        return false;

    uint divisor = 6;
    while (divisor * divisor - 2 * divisor + 1 <= number) {

        if (number % (divisor - 1) == 0)
            return false;

        if (number % (divisor + 1) == 0)
            return false;

        divisor += 6;

    }

    return true;

}

void garbell(vector<bool>& v){
    v[0] = false;
    v[1] = false;
    for(uint i = 2; i*i <= v.size(); ++i){
        if(v[i]){
            for(uint j = 2*i;j < v.size(); j = j+i){
                v[j] = false;
            }
        }
    }
}


int nextPrime(uint a) {
    vector<bool> v (a+a, true);
    garbell(v);
    //while (!isPrime(++a));
    while(!v[a]) ++a;
    return a;
}

MinHashSignatures::MinHashSignatures(uint t, uint k, vector<char *> texts, vector<uint> textSize) {
    hashFunctions = vector<pair<uint, uint>>(t);
    signatures = matrix(t, vector<uint>(texts.size(), 0xFFFFFFFF));

    srand(time(NULL));

    for (uint i = 0; i < t; ++i) {
        hashFunctions[i] = pair<uint, uint>(rand(), rand());
    }

    kshinglemap mapa(k);
    unordered_set<uint> repetidos;
    uint numRepetidos = 0;

    for (uint j = 0; j < texts.size(); ++j) mapa.add(j, texts[j], textSize[j]);
    cout << "kshingles total " << mapa.mapa.size() << endl;

    //uint modPrime = mapa.mapa.size();
    uint modPrime = nextPrime(mapa.mapa.size());
    int indice = 0;

    for (pair<uint,list<uint>> kShingleActual : mapa.mapa) {
        for (uint row = 0; row < t; ++row) {
            pair<uint, uint> p = hashFunctions[row];

            uint permutedRow = ((p.first*indice)%modPrime + p.second)%modPrime;

            if (row == 0) {
                unordered_set<uint>::iterator it = repetidos.find(permutedRow);

                if (it != repetidos.end()) ++numRepetidos;
                else repetidos.insert(permutedRow);
            }

            for (uint documento :  kShingleActual.second) {
                signatures[row][documento] = min(permutedRow, signatures[row][documento]);
            }
        }
        ++indice;
    }

    cout << "Repetidos funcion hash 1: " << numRepetidos << endl;

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
