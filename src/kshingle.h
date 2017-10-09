#ifndef KSHINGLE_H
#define KSHINGLE_H

#include <iostream>
#include <fstream>
#include "utils.h"

class KShingle {
protected:
    int k;
public:
    KShingle(int k);
    static uint hashKShingle(const char* kshingle, uint firstIndex, uint lastIndex);
    virtual uint size() = 0;
};

#endif // KSHINGLE_H
