#ifndef KSHINGLE_H
#define KSHINGLE_H

#include <string>
using namespace std;

typedef unsigned int uint;
typedef unsigned long long ull;

class KShingle {
protected:
    int k;
public:
    KShingle(int k);
    static uint hashKShingle(const string& kshingle);
    virtual double jaccard(const KShingle& B) = 0;
    virtual int size() = 0;
    virtual void print() = 0;
};

#endif // KSHINGLE_H
