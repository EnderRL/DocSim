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

void testMinHash(const vector<string>& names, PermutationMode permutationMode,bool tiempo) {

    /*cout << "Introduce la k deseada." << endl;
    uint k;
    cin >> k;
    cout << "Introduce t" << endl;
    uint t;
    cin >> t;
    */

    MinHashSignatures minHashSignatures(9, 250, names, permutationMode,tiempo);
    if(not tiempo) cout << minHashSignatures.size() << " " << minHashSignatures.finalSize() << " ";
   // cout << "El coeficiente de jaccard es con la manera NO guay "  <<    minHashSignatures.jaccard(0, 1) << endl;
    minHashSignatures.jaccard(0, 1);
}

void testKShingleHashed(const string& name1, const string& name2) {
    ofstream output("../Resultados experimentos/Experimentos Jaccard Similarity/jaccardsimilarity.txt");

    output << "Hashed time\tHashed space\tHashed res\tNo Hashed time\tNo Hashed space\tNo Hasehd res" << endl;

    Reader file1(name1);
    Reader file2(name2);

    steady_clock::time_point t1 = steady_clock::now();

    KShingleSetHashed kshingles1(9, file1.getText(), file1.getfileSize());
    KShingleSetHashed kshingles2(9, file2.getText(), file2.getfileSize());

    double jaccardHashed = KShingleSetHashed::jaccard(kshingles1, kshingles2);

    steady_clock::time_point t2 = steady_clock::now();

    duration<double> timeSpan = duration_cast<duration<double>>(t2 - t1);

    output << timeSpan.count() << "\t" << kshingles1.size()+kshingles2.size() << "\t" << jaccardHashed << endl;

    t1 = steady_clock::now();

    KShingleSet kshinglesSet1(9, file1.getText(), file1.getfileSize());
    KShingleSet kshinglesSet2(9, file2.getText(), file2.getfileSize());

    double jaccardNoHashed = KShingleSet::jaccard(kshinglesSet1, kshinglesSet2);

    t2 = steady_clock::now();

    timeSpan = duration_cast<duration<double>>(t2 - t1);

    output << timeSpan.count() << "\t" << kshinglesSet1.size()+kshinglesSet2.size() << "\t" << jaccardNoHashed << endl;
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

    vector<string> names = {"../textoPrueba1.txt", "../textoPrueba2.txt" };
    steady_clock::time_point t1;
    steady_clock::time_point t2;
    duration<double> time_span;
    for(int i = 0; i < 1; ++i) {
        //Medir tiempo exacto
        t1 = steady_clock::now();
        testMinHash(names,Random,true);
        t2 = steady_clock::now();
        time_span = duration_cast<duration<double>>(t2 - t1);
        cout << time_span.count() << " ";

        //Medir espacio exacto
        testMinHash(names,Random,false);

        //Medir tiempo Hash
        t1 = steady_clock::now();
        testMinHash(names,Hash,true);
        t2 = steady_clock::now();
        time_span = duration_cast<duration<double>>(t2 - t1);
        cout << time_span.count() << " ";

        //Medir espacio Hash
        testMinHash(names, Hash, false);

        //Medir tiempo Hash Primos
        t1 = steady_clock::now();
        testMinHash(names,HashWithPrime,true);
        t2 = steady_clock::now();
        time_span = duration_cast<duration<double>>(t2 - t1);
        cout << time_span.count() << " ";

        //Medir espacio Hash Primos
        testMinHash(names,HashWithPrime,false);



        Reader file1(names[0]);
        Reader file2 (names[1]);


        t1 = steady_clock::now();
        KShingleSetHashed kShingleSet1(9,file1.getText(),file1.getfileSize());
        KShingleSetHashed kShingleSet2(9,file2.getText(),file2.getfileSize());
        KShingleSetHashed::jaccard(kShingleSet1,kShingleSet2);
        t2 = steady_clock::now();
        time_span = duration_cast<duration<double>>(t2 - t1);
        cout << time_span.count() << " ";
        cout << kShingleSet1.size()+kShingleSet2.size() << endl;

        //Cambiar par de textos
        names[0] =  "";
        names[1] =  "";
    }


}
int main() {
    //vector<string> names = {"../textoPrueba1.txt", "../textoPrueba2.txt" };
    //testKShingleHashed(names[0], names[1]);
    experimentoMinHash();
}

/*int main() {
    vector<string> names = {"../lorem0.txt", "../lorem2.txt" };
    testKShingleHashed(names[0], names[1]);
}*/

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

/*int main() {
    primerExperimentoLSH();
}*/


