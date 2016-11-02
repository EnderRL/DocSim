#include <iostream>
#include "kshingle.h"
using namespace std;


int jaccard(KShingleSet A, KShingleSet B) {

}

void leeString(string& text) {
    cout << "Introduce la string a analizar" << endl;
    getline(cin,text);
    cout << "La string es: " << text << endl;
}


int main() {
    cout << "Empieza el algoritmo de la similitud de Jaccard." << endl;
    cout << "Introduce la k deseada." << endl;
    int k;
    cin >> k;
    cout << "K es " << k << endl;
    string text1,text2;
    getline(cin,text1);
    leeString(text1);
    leeString(text2);
    KShingleSet kshingleset1(k,text1);
    KShingleSet kshingleset2(k,text2);
    cout << "El coeficiente de jaccard es " << kshingleset1.jaccard(kshingleset2) << endl;
}

