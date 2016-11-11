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
    static const ull MAX_SIZE_4B = 4294967296;

    KShingle(int k);
    static uint hashKShingle(const string& kshingle);
    static uint hashKShingle(const char* kshingle, uint size);
    virtual double jaccard(const KShingle& B) = 0;
    virtual int size() = 0;
    virtual void print() = 0;
};

#endif // KSHINGLE_H
