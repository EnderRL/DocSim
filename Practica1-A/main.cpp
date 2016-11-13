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
    char* copy = new char[input.getfileSize()];
    uint numIterations;

    for (uint j = 0; j < numTexts; ++j) {
        numIterations = increment*j + 10;
        memcpy(copy, text, input.getfileSize());
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
        output.write(copy, input.getfileSize());
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

void testHashKShingles() {
    cout << "Introduce la string a convertir a numero" << endl;
    string text;
    leeString(text);
    cout << "Resultado: " << KShingle::hashKShingle(text) << endl;
}

void testMinHash(const vector<string>& names, PermutationMode permutationMode,bool tiempo,ofstream& writer) {

    /*cout << "Introduce la k deseada." << endl;
    uint k;
    cin >> k;
    cout << "Introduce t" << endl;
    uint t;
    cin >> t;
    */

    MinHashSignatures minHashSignatures(9, 250, names, permutationMode,tiempo);
    if(not tiempo) writer << minHashSignatures.size() << " " << minHashSignatures.finalSize() << " " << minHashSignatures.jaccard(0,1) << " ";
   // cout << "El coeficiente de jaccard es con la manera NO guay "  <<    minHashSignatures.jaccard(0, 1) << endl;
}

void testKShingleHashed(const vector<string>& name1, const vector<string>& name2) {
    ofstream output("../Resultados experimentos/Experimentos Jaccard Similarity/jaccardsimilarity.txt");

    output << "Hashed time\tHashed space\tHashed res\tNo Hashed time\tNo Hashed space\tNo Hasehd res" << endl;
    for (uint i = 0; i < name1.size(); ++i) {
        Reader file1(name1[i]);
        Reader file2(name2[i]);

        cout << "comparando " << name1[i] << " " << name2[i] << endl;

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
void experimentoMinHash() {

    ofstream writer("../Experimento.txt");
    writer << "TiempoMHExacto EEMHExacto EFMHExacto Jaccard MHExacto TiempoMHHash EEMHHash EFMHHash JaccardMHHash TiempoMHPrimos EEMHPrimos EFMHPrimos Jaccard MHPrimos TiempoMH32 EEMH32 EFMH32 JaccardMH32 TiempoGuay EFGuay JaccardGuay" << endl;
    vector<string> names = {"../textoPrueba1.txt", "../textoPrueba2.txt" };
    steady_clock::time_point t1;
    steady_clock::time_point t2;
    duration<double> time_span;
    for(int i = 0; i < 1; ++i) {
        //Medir tiempo exacto
        t1 = steady_clock::now();
        testMinHash(names,Random,true,writer);
        t2 = steady_clock::now();
        time_span = duration_cast<duration<double>>(t2 - t1);
        writer << time_span.count() << " ";

        //Medir espacio exacto
        testMinHash(names,Random,false,writer);

        //Medir tiempo Hash
        t1 = steady_clock::now();
        testMinHash(names,Hash,true,writer);
        t2 = steady_clock::now();
        time_span = duration_cast<duration<double>>(t2 - t1);
        writer << time_span.count() << " ";

        //Medir espacio Hash
        testMinHash(names, Hash, false, writer);

        //Medir tiempo Hash Primos
        t1 = steady_clock::now();
        testMinHash(names,HashWithPrime,true, writer);
        t2 = steady_clock::now();
        time_span = duration_cast<duration<double>>(t2 - t1);
        writer << time_span.count() << " ";

        //Medir espacio Hash Primos
        testMinHash(names,HashWithPrime,false, writer);

        //Medir tiempo Hash 2^32
        t1 = steady_clock::now();
        testMinHash(names,Hash32,true, writer);
        t2 = steady_clock::now();
        time_span = duration_cast<duration<double>>(t2 - t1);
        writer << time_span.count() << " ";

        //Medir espacio Hash 2^32
        testMinHash(names,Hash32,false, writer);

        Reader file1(names[0]);
        Reader file2 (names[1]);

        t1 = steady_clock::now();
        KShingleSetHashed kShingleSet1(9,file1.getText(),file1.getfileSize());
        KShingleSetHashed kShingleSet2(9,file2.getText(),file2.getfileSize());

        t2 = steady_clock::now();
        time_span = duration_cast<duration<double>>(t2 - t1);
        writer << time_span.count() << " ";
        writer << kShingleSet1.size()+kShingleSet2.size() << " ";
        writer << KShingleSetHashed::jaccard(kShingleSet1,kShingleSet2) << endl;

        //Cambiar par de textos
        names[0] =  "";
        names[1] =  "";
    }
}
int main() {
    vector<string> names1 = {
        "../DataSet Experimento 1/textoDummy.txt",
        "../DataSet Experimento 1/textoDummy.txt",
        "../DataSet Experimento 1/textoDummy.txt",
        "../DataSet Experimento 1/textoDummy.txt",
        "../DataSet Experimento 1/textoDummy.txt",
        "../DataSet Experimento 1/textoPrueba1.txt"};
    vector<string> names2 = {
        "../DataSet Experimento 1/textoDummyRandom0.txt",
        "../DataSet Experimento 1/textoDummyRandom5.txt",
        "../DataSet Experimento 1/textoDummyRandom10.txt",
        "../DataSet Experimento 1/textoDummyRandom15.txt",
        "../DataSet Experimento 1/textoDummyRandom19.txt",
        "../DataSet Experimento 1/textoPrueba2.txt"};
    testKShingleHashed(names1, names2);
    //generadorTextos("../DataSet Experimento 1/", "textoDummy", 20, 100);
}

void primerExperimentoLSH() {
   for (uint mod = 5; mod < 500; mod +=5) {
       steady_clock::time_point t1 = steady_clock::now();

       vector<string> texts(20);
       for (int i = 0; i < 20; ++i) {
           texts[i]=("../textoRandom" + to_string(i) + ".txt");

       }

       uint t = 10;
       uint k = 5;
       uint b = 5, r = 2;
       double thershold = pow((double)1/b,(double)1/r);

       vector<vector<double>> matrix(20,vector<double>(20));

       set<pair<int,int>> correctPairs;

       for (int i = 0; i < 20; ++i) {
           for (int j = i + 1; j < 20; ++j) {
               if (i == j) matrix[i][j] = 1;
               else {
                   KShingleSet kshingleset1(k, texts[i]);
                   KShingleSet kshingleset2(k, texts[j]);
                   if (kshingleset1.jaccard(kshingleset2) >= thershold) correctPairs.insert(pair<int,int>(i,j));
               }

           }
       }




       MinHashSignatures minHash(t, k,  texts, HashWithPrime, true);


       LSH lsh(minHash.getSignatures(),b,r,mod);

       ofstream writeFile("./Resultados experimentos/resultadosPrimerExpetimentoLSH.txt");

       cout << "ESTE SET ES EL DE PAREJAS REALES CON SIMILITUD >= " << thershold << endl;
       for (pair<int,int> p : correctPairs) {
            cout << p.first << ' ' << p.second << endl;
       }

       cout << "ESTE SET ES EL DE PAREJAS DE LSH" <<  endl;
       for (pair<int,int> p : lsh.getSetPairs()) {
            cout << p.first << ' ' << p.second << endl;
       }



       steady_clock::time_point t2 = steady_clock::now();
       duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
   }
}


