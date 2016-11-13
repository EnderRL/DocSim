#include "reader.h"

Reader::Reader(const string& fileName) {
    ifstream input(fileName);

    input.seekg(0, ios::end);
    fileSize = input.tellg();

    input.seekg(0, ios::beg);

    fileText = new char[fileSize];

    input.read(fileText, fileSize);
}

char* Reader::getText() {
    return fileText;
}

uint Reader::getfileSize() {
    return fileSize;
}

void Reader::deleteText() {
    delete fileText;
}

Reader::~Reader() {
    delete fileText;
}
