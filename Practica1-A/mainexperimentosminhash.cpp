#include <iostream>
#include <chrono>
#include <cmath>
#include "kshingleset.h"
#include "lsh.h"
#include "minhashsignatures.h"
#include "reader.h"
#include "kshinglesethashed.h"
using namespace chrono;

void testMinHash(const vector<string>& names, PermutationMode permutationMode, bool tiempo, ofstream& writer,uint seed) {


    steady_clock::time_point t1;
    steady_clock::time_point t2;
    duration<double> time_span;

    t1 = steady_clock::now();
    MinHashSignatures minHashSignatures(250, 9, names, permutationMode,tiempo,seed);
    t2 = steady_clock::now();
    time_span = duration_cast<duration<double>>(t2 - t1);
    if(tiempo) writer << time_span.count() << " ";
    else {
        writer << minHashSignatures.size() << " " << minHashSignatures.finalSize() << " ";
        for(uint i = 1;i<names.size();++i){
            writer << minHashSignatures.jaccard(0,i);
            if(i < names.size()-1) writer << " ";
            else writer << endl;
        }
    }
   // cout << "El coeficiente de jaccard es con la manera NO guay "  <<    minHashSignatures.jaccard(0, 1) << endl;
}

void testMinHashVariableT(const vector<string>& names, PermutationMode permutationMode,bool tiempo,ofstream& writer,uint t,uint seed) {


    steady_clock::time_point t1;
    steady_clock::time_point t2;
    duration<double> time_span;

    t1 = steady_clock::now();
    MinHashSignatures minHashSignatures(t, 9, names, permutationMode,tiempo,seed);
    t2 = steady_clock::now();
    time_span = duration_cast<duration<double>>(t2 - t1);
    if(tiempo) writer << t << " " << time_span.count() << " ";
    else {
        writer << minHashSignatures.size() << " " << minHashSignatures.finalSize() << " ";
        for(uint i = 1;i<names.size();++i){
            writer << minHashSignatures.jaccard(0,i);
            if(i < names.size()-1) writer << " ";
            else writer << endl;
        }
    }
   // cout << "El coeficiente de jaccard es con la manera NO guay "  <<    minHashSignatures.jaccard(0, 1) << endl;
}

void experimentoMinHash(const vector<string>& names,string outputFile) {

    ofstream writer(outputFile);
    writer << "TiempoMHHash EEMHHash EFMHHash JaccardMHHash TiempoMHPrimos EEMHPrimos EFMHPrimos Jaccard MHPrimos TiempoMH32 EEMH32 EFMH32 JaccardMH32 TiempoGuay EFGuay JaccardGuay" << endl;

    uint seed = time(NULL);
    cout << "Tiempo Hash" << endl;
    testMinHash(names,Hash,true,writer,seed);
    cout << "Espacio Hash" << endl;
    testMinHash(names, Hash, false, writer,seed);
    cout << "Tiempo Primos" << endl;
    testMinHash(names,HashWithPrime,true, writer,seed);
    cout << "Espacio Primos" << endl;
    testMinHash(names,HashWithPrime,false, writer,seed);
    cout << "Tiempo 32" << endl;
    testMinHash(names,Hash32,true, writer,seed);
    cout << "Espacio 32" << endl;
    testMinHash(names,Hash32,false, writer,seed);

    Reader file1(names[0]);
    for(uint i = 1; i < names.size(); ++i) {
        Reader file2 (names[i]);
        KShingleSetHashed kShingleSet1(9,file1.getText(),file1.getfileSize());
        KShingleSetHashed kShingleSet2(9,file2.getText(),file2.getfileSize());
        writer << KShingleSetHashed::jaccard(kShingleSet1,kShingleSet2) << endl;
    }
}


void experimentoMinHash32(const vector<string>& names, string outputFile){

    ofstream writer(outputFile);
    uint seed = time(NULL);
    for(uint t = 100; t < 900; t += 50) {
        cout << "Tiempo Hash32" << endl;
        testMinHashVariableT(names,Hash32,true,writer,t,seed);
        cout << "Espacio Hash32" << endl;
        testMinHashVariableT(names,Hash32,false,writer,t,seed);
    }
}

int main() {
    vector<string> texts(21);
    texts[0] = "../DataSet Experimento 1/textoDummy.txt";
    for (int i = 1; i < 21; ++i) {
        texts[i] = "../DataSet Experimento 1/textoDummyRandom" + to_string(i-1) + ".txt";
    }
    experimentoMinHash(texts,"../Resultados experimentos/Experimentos MinHash/resultadosExperimentoDummy.txt");

    texts[0] = "../DataSet Experimento 1/texto50palabras.txt";
    for (int i = 1; i < 21; ++i) {
        texts[i] = "../DataSet Experimento 1/texto50palabrasRandom" + to_string(i-1) + ".txt";
    }
    experimentoMinHash(texts,"../Resultados experimentos/Experimentos MinHash/resultadosExperimento50palabras.txt");

    texts[0] = "../DataSet Experimento 1/juegodetronos.txt";
    for (int i = 1; i < 21; ++i) {
        texts[i] = "../DataSet Experimento 1/juegodetronosRandom" + to_string(i-1) + ".txt";
    }
    experimentoMinHash(texts,"../Resultados experimentos/Experimentos MinHash/resultadosJuegoDeTronos.txt");

    texts[0] = "../DataSet Experimento 1/textoDummy.txt";
    for (int i = 1; i < 21; ++i) {
        texts[i] = "../DataSet Experimento 1/textoDummyRandom" + to_string(i-1) + ".txt";
    }
    experimentoMinHash32(texts,"../Resultados experimentos/Experimentos MinHash/resultadosExperimentoDummyVariable.txt");

    texts[0] = "../DataSet Experimento 1/texto50palabras.txt";
    for (int i = 1; i < 21; ++i) {
        texts[i] = "../DataSet Experimento 1/texto50palabrasRandom" + to_string(i-1) + ".txt";
    }
    experimentoMinHash32(texts,"../Resultados experimentos/Experimentos MinHash/resultadosExperimento50palabrasVariable.txt");

    texts[0] = "../DataSet Experimento 1/juegodetronos.txt";
    for (int i = 1; i < 21; ++i) {
        texts[i] = "../DataSet Experimento 1/juegodetronosRandom" + to_string(i-1) + ".txt";
    }
    experimentoMinHash32(texts,"../Resultados experimentos/Experimentos MinHash/resultadosJuegoDeTronosVariable.txt");
}
