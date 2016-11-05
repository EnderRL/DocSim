#include <iostream>
#include <fstream>
#include "kshingleset.h"
#include "kshinglehash.h"
#include "minhashsignatures.h"

void leeString(string& text) {
    cout << "Introduce la string a analizar" << endl;
    getline(cin,text);
    cout << "La string es: " << text << endl;
}

void testKShingles() {
    cout << "Empieza el algoritmo de la similitud de Jaccard." << endl;
    cout << "Introduce la k deseada." << endl;
    int k;
    cin >> k;
    cout << "K es " << k << endl;
    string text1,text2;
    getline(cin,text1);
    leeString(text1);
    leeString(text2);
    KShingleSet kshingleset1(k, text1);
    KShingleSet kshingleset2(k, text2);
    kshingleset1.print();
    cout << endl;
    kshingleset2.print();
    cout << "El coeficiente de jaccard es " << kshingleset1.jaccard(kshingleset2) << endl;
}

void testHashKShingles() {
    cout << "Introduce la string a convertir a numero" << endl;
    string text;
    leeString(text);
    cout << "Resultado: " << KShingle::hashKShingle(text) << endl;
}

void testMinHash() {
    ifstream in1("../text1.txt");
    ifstream in2("../text2.txt");

    in1.seekg(0, ios::end);
    in2.seekg(0, ios::end);

    uint size1 = in1.tellg();
    uint size2 = in2.tellg();

    cout << "texto 1 size: " << size1 << " texto 2 size: " << size2 << endl;

    in1.seekg(0, ios::beg);
    in2.seekg(0, ios::beg);

    char* text1 = new char[size1];
    in1.read(text1, size1);

    char* text2 = new char[size2];
    in2.read(text2, size2);

    cout << "Introduce la k deseada." << endl;
    int k;
    cin >> k;
    cout << "K es " << k << endl;
    cout << "Introduce t" << endl;
    uint t;
    cin >> t;
    KShingleSet kshingleset1(k, text1, size1);
    KShingleSet kshingleset2(k, text2, size2);
    cout << "El coeficiente de jaccard es con la manera guay " << kshingleset1.jaccard(kshingleset2) << endl;

    vector<char*> textos = {text1, text2};
    vector<uint> textSize = {size1, size2};
    MinHashSignatures minHashSignatures(t, k, textos, textSize);
    cout << "El coeficiente de jaccard es con la manera NO guay "  <<    minHashSignatures.jaccard(0,1) << endl;

}

int main() {
    testMinHash();
}

