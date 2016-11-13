#ifndef READER_H
#define READER_H
#include <fstream>
#include <iostream>
using namespace std;

typedef unsigned int uint;

class Reader {
    uint fileSize;
    char* fileText;

public:
    Reader(const string& fileName);
    ~Reader();

    char* getText();
    uint getfileSize();
};

#endif // READER_H
