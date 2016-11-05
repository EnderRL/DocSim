#include <iostream>
#include "kshingleset.h"
#include "kshinglehash.h"
#include "minhashsignatures.h"
using namespace std;

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
    string s1, s2;
    leeString(s1);
    leeString(s2);
    cout << "Introduce la k deseada." << endl;
    int k;
    cin >> k;
    cout << "K es " << k << endl;
    cout << "Introduce t" << endl;
    uint t;
    cin >> t;
    KShingleSet kshingleset1(k, s1);
    KShingleSet kshingleset2(k, s2);
    cout << "El coeficiente de jaccard es con la manera guay " << kshingleset1.jaccard(kshingleset2) << endl;

    vector<string> textos = {s1,s2};
    MinHashSignatures minHashSignatures(t,k,textos);
    cout << "El coeficiente de jaccard es con la manera NO guay "  <<    minHashSignatures.jaccard(0,1) << endl;

}

int main() {
    testMinHash();
}

