#ifndef KSHINGLEMAP_H
#define KSHINGLEMAP_H
#include <unordered_map>
#include <unordered_set>
using namespace std;

typedef unsigned int uint;

class KShingleMap {
    int k;
public:
    unordered_map<uint,unordered_set<uint>> mapa;

    KShingleMap(int k);
    void add(uint document, const char* source, uint size);
    void print();
};

#endif // KSHINGLEMAP_H
