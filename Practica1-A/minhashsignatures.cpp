#include "minhashsignatures.h"


matrix MinHashSignatures::getSignatures() const
{
    return signatures;
}

void MinHashSignatures::randomPermutations(const KShingleSparseMatrix &map,bool tiempo) {

    uint t = signatures.size();
    vector<list<uint>> permutationLists(t);

    for (uint i = 0; i < t; ++i) {
        list<uint>& permutationList = permutationLists[i];
        for (uint j = 0; j < map.mapa.size(); ++j) permutationList.push_back(j);
    }

    if(not tiempo) {
        for(uint i = 0; i < t; ++i) {
            medida += permutationLists[i].size()*sizeof(uint);
        }
    }

    uint indice = 0;

    for (pair<uint,unordered_set<uint>> kShingleActual : map.mapa) {
        cout << (double) indice/map.mapa.size() << endl;
        for (uint row = 0; row < t; ++row) {
            //cout << t << endl;
            //cout << "dentro segundo for en la row: " << row << endl;
            list<uint>& permutationList = permutationLists[row];

            uint randomIndex = rand()%permutationList.size();
            list<uint>::iterator it = permutationList.begin();

            for (uint i = 0; i < randomIndex; ++i) ++it;

            uint permutedRow = *it;
            permutationList.erase(it);

            for (uint documento :  kShingleActual.second) {
                signatures[row][documento] = min(permutedRow, signatures[row][documento]);
            }
        }
        ++indice;
    }

}

void MinHashSignatures::permutations32(const vector<string>& texts, uint t, uint k, bool tiempo) {

    vector<pair<uint, uint>> hashFunctions(t);
    if(not tiempo) medida += t*2*sizeof(uint);
    signatures = matrix(t, vector<uint>(texts.size(), 0xFFFFFFFF));
    for (uint i = 0; i < t; ++i) {
        hashFunctions[i] = pair<uint, uint>(rand(), rand());
    }
    const ull mod = 4294967296;
    uint j = 0;
    for (string nombreArchivo : texts) {
        Reader reader(nombreArchivo);

        for (uint i = 0; i <= reader.getfileSize()-k; ++i) {
            ull hashed = KShingle::hashKShingle(reader.getText(),i,i+k-1);
            for (uint row = 0; row < t; ++row) {
                pair<uint, uint> p = hashFunctions[row];
                uint permutedRow = ((p.first*hashed)%mod + p.second)%mod;
                signatures[row][j] = min(permutedRow, signatures[row][j]);
            }
        }
        ++j;
    }
}

MinHashSignatures::MinHashSignatures(uint t, uint k, const vector<string>& texts, PermutationMode mode,bool tiempo, uint seed) {
    srand(seed);
    medida = 0;
    medidaFinal = 0;
    KShingleSparseMatrix mapa(k);
    signatures = matrix(t, vector<uint>(texts.size(), 0xFFFFFFFF));

    if (mode == Hash32) {
        permutations32(texts, t, k, tiempo);
        return;
    }

    //LEE TEXTOS Y LOS KSHINGLEA

    for (uint i = 0; i < texts.size(); ++i) {
        Reader reader(texts[i]);
        mapa.add(i,reader.getText(),reader.getfileSize());
    }

    if(not tiempo) {
        for (pair<uint,unordered_set<uint>> it : mapa.mapa) {
            medida += it.second.size()*sizeof(uint);
        }
        medida += t*2*sizeof(uint);
    }



    if (mode == Random) {
        randomPermutations(mapa,tiempo);
        return;
    }
    vector<pair<uint, uint>> hashFunctions(t);
    for (uint i = 0; i < t; ++i) {
        hashFunctions[i] = pair<uint, uint>(rand(), rand());
    }

    uint mod;
    if (mode == HashWithPrime) mod = nextPrime(mapa.mapa.size());
    else mod = mapa.mapa.size();

    uint indice = 0;

    for (pair<uint,unordered_set<uint>> kShingleActual : mapa.mapa) {
        for (uint row = 0; row < t; ++row) {
            pair<uint, uint> p = hashFunctions[row];

            uint permutedRow = ((p.first*indice)%mod + p.second)%mod;

            for (uint documento :  kShingleActual.second) {
                signatures[row][documento] = min(permutedRow, signatures[row][documento]);
            }
        }
        ++indice;
    }

}

double MinHashSignatures::jaccard(uint a, uint b) {
    uint sum = 0;
    for (uint i = 0; i < signatures.size(); ++i) {
        if (signatures[i][a] == signatures[i][b]) ++sum;
    }
   // cout << "Hay " << sum << " filas iguales y " << signatures.size() << " filas en total." << endl;
    return double(sum)/signatures.size();
}

uint MinHashSignatures::size(){
    return medida + finalSize();
}

uint MinHashSignatures::finalSize() {
    return signatures.size()*signatures[0].size()*sizeof(uint);
}
