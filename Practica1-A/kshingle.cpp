#include "kshingle.h"


KShingleSet::KShingleSet(int k, string source) {
    this->k = k;
    //TODO: TRATAR ESPACIOS EN BLANCO PARA LA GENTE QUE ESCRIBE MAL
    for (unsigned int i = 0; i <= source.size()-k ; ++i) {
        kshingles.insert(source.substr(i, k));

    }
}

double KShingleSet::jaccard(const KShingleSet &B) {
    int unionSize = 0;
    int interSize = 0;
    Iterator i = kshingles.begin();
    int ipos = 0;
    Iterator j = B.kshingles.cbegin();
    int jpos = 0;
    while (i != kshingles.end() and j != B.kshingles.cend()) {
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
    if (i == kshingles.end()) {
        unionSize += B.kshingles.size() - jpos;
    }
    else if (j == B.kshingles.end()) {
        unionSize += kshingles.size() - ipos;
    }
    return (double)interSize/unionSize;
}


void KShingleSet::toString() {
    cout << "k = " << k << endl;
    for (string s : kshingles) {
        cout << s << endl;
    }
}

bool KShingleSet::addKShingle(string shingle) {
    return true;
}

bool KShingleSet::removeKShingle(string shingle) {
    return false;
}

int KShingleSet::size() {
    return kshingles.size();
}

