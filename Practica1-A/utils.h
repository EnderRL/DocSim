#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <time.h>
#include <vector>
#include <list>
#include "reader.h"

typedef unsigned int uint;
typedef unsigned long long ull;
using namespace std;

static const ull MAX_SIZE_4B = 4294967296;

uint nextPrime(uint number);
void userSrand(uint seed);
uint userRand();
void textGenerator(const string& nombre);
void textGenerator(const string& path, const string &nombre, uint numTexts, uint increment);

#endif // UTILS_H

