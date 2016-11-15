#include <iostream>
#include <chrono>
#include <cmath>
#include "kshingleset.h"
#include "lsh.h"
#include "minhashsignatures.h"
#include "reader.h"
#include "kshinglesethashed.h"
using namespace chrono;





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
    double minError = 1;
    for (uint i = 2; i < t; ++i) {
        if (t%i == 0) {
            uint bAux = i;
            uint rAux = t/i;
            double relativeError = (abs(pow(1./bAux,1./rAux) - thershold))/thershold;
            if (minError > relativeError) {
                minError = relativeError;
                b = bAux;
                r = rAux;
            }
        }
     }
    if (minError >= 1) return false;
    return true;

}


void segundoExperimentoLSH() {


   uint k = 9;
   uint b,r;
   double treshold = 0.7;
   uint t = 250;

   escogeParametrosLSH(treshold,t,b,r);

    vector<string> texts(21);
    texts[0] = "../DataSet Experimento 1/juegodetronos.txt";
    for (int i = 1; i < 21; ++i) {
        texts[i] = "../DataSet Experimento 1/juegodetronosRandom" + to_string(i-1) + ".txt";
    }

    set<pair<uint,uint>> correctPairs;

    for (uint i = 0; i < 20; ++i) {
        Reader reader1(texts[i]);
        for (uint j = i + 1; j < 20; ++j) {
            Reader reader2(texts[j]);
            KShingleSetHashed kshingleset1(k, reader1.getText(), reader1.getfileSize());
            KShingleSetHashed kshingleset2(k, reader2.getText(), reader2.getfileSize());
            if (KShingleSetHashed::jaccard(kshingleset1,kshingleset2) >= treshold) correctPairs.insert(pair<uint,uint>(i,j));
        }
    }

    MinHashSignatures minHash(t, k,  texts, Hash32, true,time(NULL));

    ofstream writeFile("../Resultados experimentos/Experimentos LSH/resultadosSegundoExpetimentoLSH.txt");
    writeFile << "MOD\tFALSOS_POSITIVOS\tFALSOS_NEGATVOS\tSIMILITUD_SETS\tTIEMPO\tESPACIO"<<endl;


    uint mod = 13;
    for (uint count = 0; count < 100; ++count) {

       steady_clock::time_point t1 = steady_clock::now();

       LSH lsh(minHash.getSignatures(),b,r,mod,true);

       steady_clock::time_point t2 = steady_clock::now();

       lsh = LSH(minHash.getSignatures(),b,r,mod,false);


       uint unionSize, intersectionSize;

       setSimilarity(unionSize, intersectionSize, correctPairs, *lsh.getSetPairs());

       duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

       writeFile << mod << "\t" << lsh.getSetPairs()->size() - intersectionSize << "\t" <<  correctPairs.size() - intersectionSize << "\t" << (double)intersectionSize / (double)unionSize << "\t" << time_span.count() <<  "\t" << lsh.size() <<   endl;
        mod = nextPrime(mod+1);

   }
}

void primerExperimentoLSH() {

   vector<string> texts(21);
   texts[0] = "../DataSet Experimento 1/textoDummy.txt";
   for (int i = 1; i < 21; ++i) {
       texts[i] = "../DataSet Experimento 1/textoDummyRandom" + to_string(i-1) + ".txt";
   }


   ofstream writeFile("../Resultados experimentos/Experimentos LSH/resultadosPrimerExpetimentoLSH.txt");
   writeFile << "TRESHOLD\tB\tR\tFALSOS_POSITIVOS\tFALSOS_NEGATVOS\tSIMILTUD_SETS\tTIEMPO\tESPACIO"<<endl;

   srand(time(NULL));
   uint mod =nextPrime(rand()%200+100);

   uint k = 9;
   vector<vector<double>> matrix(21,vector<double>(21));
   for (uint i = 0; i < 20; ++i) {
       Reader reader1(texts[i]);
       KShingleSetHashed kshingleset1(k, reader1.getText(), reader1.getfileSize());
       for (uint j = i + 1; j < 20; ++j) {
           Reader reader2(texts[j]);
           KShingleSetHashed kshingleset2(k, reader2.getText(), reader2.getfileSize());
           matrix[i][j] = KShingleSetHashed::jaccard(kshingleset1,kshingleset2);
       }
   }


   for (double treshold = 0.5; treshold <= 1; treshold += 0.01) {

       uint b,r;
       uint t = 250;

      if (escogeParametrosLSH(treshold,t,b,r)) {

           set<pair<uint,uint>> correctPairs;
           for (uint i = 0; i < 20; ++i) {
               for (uint j = i ; j < 20; ++j) {
                   if (matrix[i][j] >= treshold) correctPairs.insert(pair<uint,uint>(i,j));
               }
           }

           MinHashSignatures minHash(t, k,  texts, Hash32, true,time(NULL));


           steady_clock::time_point t1 = steady_clock::now();

           LSH lsh(minHash.getSignatures(),b,r,mod,true);

           steady_clock::time_point t2 = steady_clock::now();


           lsh = LSH(minHash.getSignatures(),b,r,mod,false);


           uint unionSize, intersectionSize;

           setSimilarity(unionSize, intersectionSize, correctPairs, *lsh.getSetPairs());

           duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

           writeFile << treshold << "\t" << b << "\t" << r << "\t" << lsh.getSetPairs()->size() - intersectionSize << "\t" <<  correctPairs.size() - intersectionSize << "\t" << (double)intersectionSize /(double)unionSize << "\t" << time_span.count() << "\t" << lsh.size() << endl;
      }

   }
}

int main() {
    segundoExperimentoLSH();
}
