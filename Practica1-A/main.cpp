#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <cmath>
#include "kshingleset.h"
#include "lsh.h"
#include "minhashsignatures.h"
#include "reader.h"
#include "kshinglesethashed.h"
#include <ctime>
#include <ratio>
#include <chrono>
#include <cstring>
using namespace std::chrono;

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


void generadorTextos(const string& path, const string &nombre, uint numTexts, uint increment) {
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

void generadorTextos(const string& nombre) {
    srand(time(NULL));
    ifstream input("../" + nombre + ".txt");

    input.seekg(0, ios::end);
    uint size = input.tellg();

    input.seekg(0, ios::beg);

    char* text = new char[size];
    input.read(text, size);

    char* permutacion = new char[size];

    for(uint i = 0; i < 20 ;++i) {
        list<uint> indices;
        for(uint j = 0; j < size; ++j) indices.push_back(j);
        for(uint j = 0; j < size; ++j) {
            uint indiceRandom = rand()%indices.size();
            list<uint>::iterator iterador = indices.begin();
            for(uint k = 0; k <indiceRandom; ++k) {
                ++iterador;
            }
            permutacion[*iterador] = text[j];
            indices.erase(iterador);
        }

        ofstream output("../" + nombre + "Random" + to_string(i) + ".txt");
        output.write(permutacion, size);
        output.close();
    }


}

void leeString(string& text) {
    cout << "Introduce la string a analizar" << endl;
    getline(cin,text);
    cout << "La string es: " << text << endl;
}

void testKShingles() {
    cout << "Empieza el algoritmo de la similitud de Jaccard." << endl;
    cout << "Introduce la k deseada." << endl;
    int k;
    cin >> k;
    cout << "K es " << k << endl;
    string text1,text2;
    getline(cin,text1);
    leeString(text1);
    leeString(text2);
    KShingleSet kshingleset1(k, text1);
    KShingleSet kshingleset2(k, text2);
    kshingleset1.print();
    cout << endl;
    kshingleset2.print();
    cout << "El coeficiente de jaccard es " << kshingleset1.jaccard(kshingleset2) << endl;
}

void testMinHash(const vector<string>& names, PermutationMode permutationMode,bool tiempo,ofstream& writer) {


    steady_clock::time_point t1;
    steady_clock::time_point t2;
    duration<double> time_span;

    t1 = steady_clock::now();
    MinHashSignatures minHashSignatures(250, 9, names, permutationMode,tiempo);
    t2 = steady_clock::now();
    time_span = duration_cast<duration<double>>(t2 - t1);
    if(tiempo) writer << time_span.count() << " ";
    else {
        writer << minHashSignatures.size() << " " << minHashSignatures.finalSize() << " ";
        for(int i = 1;i<20;++i){
            writer << minHashSignatures.jaccard(0,i);
            if(i < 19) writer << " ";
            else writer << endl;
        }
    }
   // cout << "El coeficiente de jaccard es con la manera NO guay "  <<    minHashSignatures.jaccard(0, 1) << endl;
}

void primerExperimento(const vector<string>& name1, const vector<string>& name2) {
    ofstream output("../Resultados experimentos/Experimentos Jaccard Similarity/jaccardsimilarity.txt");

    output << "Hashed time\tHashed space\tHashed res\tNo Hashed time\tNo Hashed space\tNo Hasehd res" << endl;
    for (uint i = 0; i < name1.size(); ++i) {
        Reader file1(name1[i]);
        Reader file2(name2[i]);

        cout << "comparando " << name1[i] << " " << name2[i] << endl;

        output << name1[i] << "\t" << name2[i] << endl;

        for (uint k = 4; k <= 10; ++k) {

            steady_clock::time_point t1 = steady_clock::now();

            KShingleSetHashed kshingles1(k, file1.getText(), file1.getfileSize());
            KShingleSetHashed kshingles2(k, file2.getText(), file2.getfileSize());

            double jaccardHashed = KShingleSetHashed::jaccard(kshingles1, kshingles2);

            steady_clock::time_point t2 = steady_clock::now();

            duration<double> timeSpan = duration_cast<duration<double>>(t2 - t1);

            output << timeSpan.count() << "\t" << kshingles1.size()+kshingles2.size() << "\t" << jaccardHashed << "\t";

            t1 = steady_clock::now();

            KShingleSet kshinglesSet1(k, file1.getText(), file1.getfileSize());
            KShingleSet kshinglesSet2(k, file2.getText(), file2.getfileSize());

            double jaccardNoHashed = KShingleSet::jaccard(kshinglesSet1, kshinglesSet2);

            t2 = steady_clock::now();

            timeSpan = duration_cast<duration<double>>(t2 - t1);

            output << timeSpan.count() << "\t" << kshinglesSet1.size()+kshinglesSet2.size() << "\t" << jaccardNoHashed << endl;
        }
        output << endl;
    }
}

void primerExperimento(const vector<string>& names) {
    ofstream output("../Resultados experimentos/Experimentos Jaccard Similarity/jaccardsimilarity.txt");

    output << "Hashed time\tHashed space\tHashed res\tNo Hashed time\tNo Hashed space\tNo Hasehd res" << endl;
    Reader file1(names[0]);
    for (uint i = 1; i < names.size(); ++i) {
        Reader file2(names[i]);

        cout << "comparando " << names[0] << " " << names[i] << endl;

        output << names[i] << "\t" << names[i] << endl;

        for (uint k = 4; k <= 10; ++k) {

            steady_clock::time_point t1 = steady_clock::now();

            KShingleSetHashed kshingles1(k, file1.getText(), file1.getfileSize());
            KShingleSetHashed kshingles2(k, file2.getText(), file2.getfileSize());

            double jaccardHashed = KShingleSetHashed::jaccard(kshingles1, kshingles2);

            steady_clock::time_point t2 = steady_clock::now();

            duration<double> timeSpan = duration_cast<duration<double>>(t2 - t1);

            output << timeSpan.count() << "\t" << kshingles1.size()+kshingles2.size() << "\t" << jaccardHashed << "\t";

            t1 = steady_clock::now();

            KShingleSet kshinglesSet1(k, file1.getText(), file1.getfileSize());
            KShingleSet kshinglesSet2(k, file2.getText(), file2.getfileSize());

            double jaccardNoHashed = KShingleSet::jaccard(kshinglesSet1, kshinglesSet2);

            t2 = steady_clock::now();

            timeSpan = duration_cast<duration<double>>(t2 - t1);

            output << timeSpan.count() << "\t" << kshinglesSet1.size()+kshinglesSet2.size() << "\t" << jaccardNoHashed << endl;
        }
        output << endl;
    }
}

void testLSH() {

    const vector<vector<uint>> matrix = { {0,1,2},
                                    {1,1,1},
                                    {2,2,2},

                                    {0,0,2},
                                    {1,1,2},
                                    {2,2,2},

                                    {3,3,3},
                                    {4,4,4},
                                    {5,5,5}};

    LSH lsh(matrix, 3, 3, 10);
}
void experimentoMinHash(const vector<string>& names,string outputFile) {

    ofstream writer(outputFile);
    writer << "TiempoMHHash EEMHHash EFMHHash JaccardMHHash TiempoMHPrimos EEMHPrimos EFMHPrimos Jaccard MHPrimos TiempoMH32 EEMH32 EFMH32 JaccardMH32 TiempoGuay EFGuay JaccardGuay" << endl;

        cout << "Tiempo Hash" << endl;
        testMinHash(names,Hash,true,writer);
        cout << "Espacio Hash" << endl;
        testMinHash(names, Hash, false, writer);
        cout << "Tiempo Primos" << endl;
        testMinHash(names,HashWithPrime,true, writer);
        cout << "Espacio Primos" << endl;
        testMinHash(names,HashWithPrime,false, writer);
        cout << "Tiempo 32" << endl;
        testMinHash(names,Hash32,true, writer);
        cout << "Espacio 32" << endl;
        testMinHash(names,Hash32,false, writer);

        Reader file1(names[0]);
        for(uint i = 1; i < names.size(); ++i) {
            Reader file2 (names[i]);
            KShingleSetHashed kShingleSet1(9,file1.getText(),file1.getfileSize());
            KShingleSetHashed kShingleSet2(9,file2.getText(),file2.getfileSize());
            writer << KShingleSetHashed::jaccard(kShingleSet1,kShingleSet2) << endl;
        }
}

void setSimilarity (uint& unionSize, uint& interSize, const set<pair<uint,uint>>& correctPairs, const set<pair<uint,uint>>& lshPairs) {
    unionSize = 0;
    interSize = 0;
    set<pair<uint,uint>>::iterator i = correctPairs.cbegin();
    uint ipos = 0;
    set<pair<uint,uint>>::iterator j = lshPairs.cbegin();
    uint jpos = 0;
    while (i != correctPairs.cend() and j != lshPairs.cend()) {
        if (*i == *j) {
            ++interSize;
            ++i;
            ++ipos;
            ++j;
            ++jpos;
        }
        else if (*i < *j) {
            ++i;
            ++ipos;
        }
        else {
            ++j;
            ++jpos;
        }
        ++unionSize;
    }
    if (i == correctPairs.cend()) unionSize += lshPairs.size() - jpos;
    else unionSize += correctPairs.size() - ipos;
}

bool escogeParametrosLSH(const double thershold, const uint t, uint& b, uint& r) {
    for (double error = 0.01; error <= 1; error += 0.01) {
         srand(time(NULL));
         list<uint> possibleBValues;
         for (uint i = 2; i <= t; ++i) possibleBValues.push_back(i);

         while (possibleBValues.size() != 0) {
             list<uint>::iterator it;
             uint indiceRandom = rand()%possibleBValues.size();
             it = possibleBValues.begin();
             for (uint i = 0; i < indiceRandom; ++i) ++it;
             b = *it;
             if (t%b == 0) {
                 r = t/b;
                 double relativeError = (abs(pow(1./b,1./r) - thershold))/thershold;
                 cout << "Relative error: " << relativeError << " cota error: " << error << " b: " << b << " r: " << r << endl;
                 if ((abs(pow(1./b,1./r) - thershold))/thershold <= error) {
                    cout << "Lo he conseguido con error relativo de " << error << endl;
                     return true;
                 }
             }
             possibleBValues.erase(it);
         }

    }
    return false;
}

void primerExperimentoLSH() {
   for (uint mod = 5; mod < 500; mod +=5) {

       vector<string> texts(21);
       texts[0] = "../DataSet Experimento 1/juegodetronos.txt";
       for (int i = 1; i < 21; ++i) {
           texts[i] = "../DataSet Experimento 1/juegodetronosRandom" + to_string(i-1) + ".txt";
       }

       uint b,r;
       double thershold;
       uint t = 10;

       if (!escogeParametrosLSH(thershold,t,b,r)) cout << "No existe b y r con threshold " << thershold << endl;


       uint k = 5;


       set<pair<uint,uint>> correctPairs;

       for (uint i = 0; i < 20; ++i) {
           for (uint j = i + 1; j < 20; ++j) {
               KShingleSet kshingleset1(k, texts[i]);
               KShingleSet kshingleset2(k, texts[j]);
               if (kshingleset1.jaccard(kshingleset2) >= thershold) correctPairs.insert(pair<uint,uint>(i,j));
           }
       }

       MinHashSignatures minHash(t, k,  texts, HashWithPrime, true);

       steady_clock::time_point t1 = steady_clock::now();

       LSH lsh(minHash.getSignatures(),b,r,mod);

       steady_clock::time_point t2 = steady_clock::now();

       ofstream writeFile("./Resultados experimentos/resultadosPrimerExpetimentoLSH.txt");

       uint unionSize, intersectionSize;

       setSimilarity(unionSize, intersectionSize, correctPairs, lsh.getSetPairs());

       cout << "En total hay " << correctPairs.size() << " parejas de textos similares " <<
               lsh.getSetPairs().size() << " parejas de LSH similares." << endl;
       cout << "Coinciden " << intersectionSize << " parejas que son el " << (double)intersectionSize/(double)unionSize << "%" << endl;

       duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
   }
}

int main() {
    uint t;
    double treshold;
    cout << "Introduce t y treshold" << endl;
    cin >> t >> treshold;
    uint b, r;
    if (!escogeParametrosLSH(treshold,t,b,r)) cout << "No existe b y r con threshold " << treshold << endl;
    cout << "La b es " << b << " y la r es " << r << endl;

}



