#include <iostream>
#include <chrono>
#include <cmath>
#include "kshingleset.h"
#include "lsh.h"
#include "minhashsignatures.h"
#include "reader.h"
#include "kshinglesethashed.h"
using namespace chrono;

void primerExperimentoJaccard(const vector<string>& name1, const vector<string>& name2) {
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

