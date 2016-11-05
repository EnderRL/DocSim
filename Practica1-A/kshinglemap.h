#ifndef KSHINGLEMAP_H
#define KSHINGLEMAP_H
#include <unordered_map>
#include <list>
using namespace std;

typedef unsigned int uint;

class kshinglemap
{
private:

    int k;
public:
    unordered_map<uint,list<uint>> mapa;
    kshinglemap(int k);
    void add(uint document, const char* source, uint size);
    int size();

    void print();
};

#endif // KSHINGLEMAP_H
