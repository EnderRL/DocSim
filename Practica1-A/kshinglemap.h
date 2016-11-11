#ifndef KSHINGLEMAP_H
#define KSHINGLEMAP_H
#include <unordered_map>
#include <list>
using namespace std;

typedef unsigned int uint;

class KShingleMap {
    int k;
public:
    unordered_map<uint,list<uint>> mapa;

    KShingleMap(int k);
    void add(uint document, const char* source, uint size);
    void print();
};

#endif // KSHINGLEMAP_H
