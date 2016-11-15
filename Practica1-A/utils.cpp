#include "utils.h"

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

uint nextPrime(uint a) {
    while (!isPrime(a)) ++a;
    return a;
}


ull holdrand = 1;

void userSrand(uint seed) {
    holdrand = (uint)seed;
}

uint userRand() {
    const uint m = 67108864;
    const uint a = 26353589;
    const uint c = 14181771;
    holdrand = (a*holdrand + c) % m;
    return holdrand;
}


void textGenerator(const string& path, const string &nombre, uint numTexts, uint increment) {
    srand(time(NULL));
    userSrand(time(NULL));
    Reader input(path + nombre + ".txt");

    char* text = input.getText();
    uint size = input.getfileSize();
    char* copy = new char[size];
    uint numIterations;

    for (uint j = 0; j < numTexts; ++j) {
        numIterations = increment*j + 10;
        memcpy(copy, text, size);
        ofstream output(path + nombre + "Random" + to_string(j) + ".txt");

        for (uint i = 0; i < numIterations; ++i) {
            uint randomSize = rand()%6 + 1;

            if (rand()%10 <= 8) {
                uint indexRandom1 = userRand()%size;
                uint indexRandom2 = userRand()%size;
                if (indexRandom1 > size-randomSize) indexRandom1 = size-randomSize;
                if (indexRandom2 > size-randomSize) indexRandom2 = size-randomSize;

                for (uint k = 0; k < randomSize; ++k) {
                    char aux = copy[indexRandom1+k];
                    copy[indexRandom1+k] = copy[indexRandom2+k];
                    copy[indexRandom2+k] = aux;
                }
            }
            else {
                uint indexRandom = userRand()%size;
                if (indexRandom > size-randomSize) indexRandom = size-randomSize;

                for (uint k = indexRandom; k < indexRandom+randomSize; ++k) {
                    copy[k] = rand()%128;
                }
            }
        }
        output.write(copy, size);
        output.close();
    }
}

void textGenerator(const string& nombre) {
    srand(time(NULL));
    ifstream input("../" + nombre + ".txt");

    string word;
    vector<string> words;

    while (input >> word) {
        words.push_back(word);
    }

    vector<string> copy(words.size());

    for(uint i = 0; i < 20 ;++i) {
        list<uint> indices;
        for(uint j = 0; j < words.size(); ++j) indices.push_back(j);
        for(uint j = 0; j < words.size(); ++j) {
            uint indiceRandom = rand()%indices.size();
            list<uint>::iterator iterador = indices.begin();
            for(uint k = 0; k <indiceRandom; ++k) {
                ++iterador;
            }
            copy[*iterador] = words[j];
            indices.erase(iterador);
        }

        ofstream output("../" + nombre + "Random" + to_string(i) + ".txt");
        for (string wordInText : copy) {
            output << wordInText << " ";
        }
        output.close();
    }
}
