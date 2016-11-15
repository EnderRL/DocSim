#include <iostream>
#include <chrono>
#include <cmath>
#include "kshingleset.h"
#include "lsh.h"
#include "minhashsignatures.h"
#include "reader.h"
#include "kshinglesethashed.h"
using namespace chrono;


void primerExperimentoJaccard(const vector<string>& names, const string& testName) {
    ofstream output("../Resultados experimentos/Experimentos Jaccard Similarity/" + testName + ".txt");

    output << "Hashed time\tHashed space\tHashed res\tNo Hashed time\tNo Hashed space\tNo Hasehd res" << endl;
    Reader file1(names[0]);
    for (uint i = 1; i < names.size(); ++i) {
        Reader file2(names[i]);

        cout << "comparando " << names[0] << " " << names[i] << endl;

        output << names[0] << "\t" << names[i] << endl;

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

int main() {
    vector<string> texts(21);
    texts[0] = "../DataSet Experimento 1/texto50palabras.txt";
    for (int i = 1; i < 21; ++i) {
        texts[i] = "../DataSet Experimento 1/texto50palabrasRandom" + to_string(i-1) + ".txt";
    }
    primerExperimentoJaccard(texts, "texto50palabras");
    texts[0] = "../DataSet Experimento 1/juegodetronos.txt";
    for (int i = 1; i < 21; ++i) {
        texts[i] = "../DataSet Experimento 1/juegodetronosRandom" + to_string(i-1) + ".txt";
    }
    primerExperimentoJaccard(texts, "juegodetronos");
    texts[0] = "../DataSet Experimento 1/textoDummy.txt";
    for (int i = 1; i < 21; ++i) {
        texts[i] = "../DataSet Experimento 1/textoDummyRandom" + to_string(i-1) + ".txt";
    }
    primerExperimentoJaccard(texts, "textoDummy");
}
