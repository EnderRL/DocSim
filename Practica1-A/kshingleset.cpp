#include "kshingleset.h"

KShingleSet::KShingleSet(int k, const string &source) : KShingle(k) {
    //TODO: TRATAR ESPACIOS EN BLANCO PARA LA GENTE QUE ESCRIBE MAL
    for (unsigned int i = 0; i <= source.size()-k ; ++i) {
        kshingles.insert(source.substr(i, k));
    }
}

KShingleSet::KShingleSet(int k, const char* source, uint size) : KShingle(k) {
    char subString[k];
    for (uint i = 0; i <= size-k; ++i) {
        for (int j = 0; j < k; ++j) {
            subString[j] =  source[i+j];
        }
        string aux(subString, k);
        kshingles.insert(aux);
    }
}

double KShingleSet::jaccard(const KShingleSet &A, const KShingleSet &B) {
    uint unionSize = 0;
    uint interSize = 0;
    IteratorS i = A.kshingles.cbegin();
    uint ipos = 0;
    IteratorS j = B.kshingles.cbegin();
    uint jpos = 0;
    while (i != A.kshingles.cend() and j != B.kshingles.cend()) {
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
    if (i == A.kshingles.cend()) unionSize += B.kshingles.size() - jpos;
    else unionSize += A.kshingles.size() - ipos;
    return (double)interSize/unionSize;
}

double KShingleSet::jaccard(const KShingle &Bs) {
    const KShingleSet& B = (KShingleSet&)Bs;
    int unionSize = 0;
    int interSize = 0;
    IteratorS i = kshingles.begin();
    int ipos = 0;
    IteratorS j = B.kshingles.cbegin();
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

void KShingleSet::print() {
    for (string s : kshingles) {
        cout << s << endl;
    }
}

uint KShingleSet::size() {
    return kshingles.size();
}

