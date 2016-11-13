#include "minhashsignatures.h"

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
    //vector<bool> v (a+a, true);
    //garbell(v);
    while (!isPrime(a)) ++a;
    //while(!v[a]) ++a;
    return a;
}

matrix MinHashSignatures::getSignatures() const
{
    return signatures;
}

void MinHashSignatures::randomPermutations(const KShingleMap &map,bool tiempo) {

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

        for (uint row = 0; row < t; ++row) {
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
    srand(time(NULL));
    for (uint i = 0; i < t; ++i) {
        hashFunctions[i] = pair<uint, uint>(rand(), rand());
        //cout << "H" << i << " es " << hashFunctions[i].first << "x + " << hashFunctions[i].second << " mod 2^32" << endl;
    }
    const ull mod = 4294967296;
    uint j = 0;
    for (string nombreArchivo : texts) {
        Reader reader(nombreArchivo);

        for (uint i = 0; i <= reader.getfileSize()-k; ++i) {
            ull hashed = KShingle::hashKShingle(reader.getText(),i,i+k-1);
            //cout << "He sacado el kshingle " << text.substr(i,k) << " del texto " << j << " y su hasheado me ha dao " << hashed << endl;
            for (uint row = 0; row < t; ++row) {
                pair<uint, uint> p = hashFunctions[row];
                uint permutedRow = ((p.first*hashed)%mod + p.second)%mod;
                signatures[row][j] = min(permutedRow, signatures[row][j]);
            }
        }
        ++j;
    }

    /*
    for (uint i = 0; i < t; ++i) {
        for (uint j = 0; j < texts.size(); ++j) {
            cout << signatures[i][j] << " ";
        }
        cout << endl;
    }*/
}

MinHashSignatures::MinHashSignatures(uint t, uint k, const vector<string>& texts, PermutationMode mode,bool tiempo) {

    this->tiempo = tiempo;
    medida = 0;
    medidaFinal = 0;
    KShingleMap mapa(k);
    signatures = matrix(t, vector<uint>(texts.size(), 0xFFFFFFFF));

    if (mode == Hash32) {
        permutations32(texts, t, k, tiempo);
        return;
    }

    //LEE TEXTOS Y LOS KSHINGLEA
    for (uint i = 0; i < texts.size(); ++i) {

        ifstream input(texts[i]);

        input.seekg(0, ios::end);
        uint size = input.tellg();
        input.seekg(0, ios::beg);

        char* text = new char[size];

        input.read(text, size);
        mapa.add(i, text, size);

        delete text;
        input.close();
    }

    if(not tiempo) {
        for (pair<uint,unordered_set<uint>> it : mapa.mapa) {
            medida += it.second.size()*sizeof(uint);
        }
    }

    srand(time(NULL));

    if (mode == Random) {
        randomPermutations(mapa,tiempo);
        return;
    }

    uint numRepetidos = 0;
    unordered_set<uint> repeated;
    vector<pair<uint, uint>> hashFunctions(t);
    if(not tiempo) medida += t*2*sizeof(uint);
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

            if (row == 0) {
                unordered_set<uint>::iterator it = repeated.find(permutedRow);

                if (it != repeated.end()) ++numRepetidos;
                else repeated.insert(permutedRow);
            }

            for (uint documento :  kShingleActual.second) {
                signatures[row][documento] = min(permutedRow, signatures[row][documento]);
            }
        }
        ++indice;
    }


    //cout << "Repetidos funcion hash 1: " << numRepetidos << endl;
    /*for (uint i = 0; i < t; ++i) {
        for (uint j = 0; j < texts.size(); ++j) {
            cout << signatures[i][j] << " ";
        }
        cout << endl;
    }*/
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
