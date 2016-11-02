#ifndef KSHINGLE_H
#define KSHINGLE_H

#include <set>
#include <string>
#include <iostream>
using namespace std;


typedef set<string>::iterator Iterator;


class KShingleSet {

private:
    int k;
    set<string> kshingles;

public:
    KShingleSet(int k, string source);
    bool addKShingle(string shingle);
    bool removeKShingle(string shingle);
    int size();
    double jaccard(const KShingleSet& B);
    void toString();
};

#endif // KSHINGLE_H
