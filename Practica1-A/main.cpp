#include <iostream>
#include <fstream>
#include "kshingleset.h"
#include "minhashsignatures.h"
#include <list>

void generadorTextos(const string& nombre) {
    srand(time(NULL));
    ifstream input("../" + nombre + ".txt");

    input.seekg(0, ios::end);
    uint size = input.tellg();

    input.seekg(0, ios::beg);

    char* text = new char[size];
    input.read(text, size);

    char* permutacion = new char[size];

    for(uint i = 0; i < 20 ;++i) {
        list<uint> indices;
        for(uint j = 0; j < size; ++j) indices.push_back(j);
        for(uint j = 0; j < size; ++j) {
            uint indiceRandom = rand()%indices.size();
            list<uint>::iterator iterador = indices.begin();
            for(uint k = 0; k <indiceRandom; ++k) {
                ++iterador;
            }
            permutacion[*iterador] = text[j];
            indices.erase(iterador);
        }

        ofstream output("../" + nombre + "Random" + to_string(i) + ".txt");
        output.write(permutacion, size);
        output.close();
    }


}

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

void testMinHash(uint numText, const string& name) {
    vector<char*> texts(numText);
    vector<uint> textSize(numText);

    for (uint i = 0; i < numText; ++i) {
        ifstream input("../" + name + to_string(i) + ".txt");

        input.seekg(0, ios::end);
        uint size = input.tellg();
        input.seekg(ios::beg);

        char* text = new char[size];
        input.read(text, size);

        texts[i] = text;
        textSize[i] = size;

        input.close();
    }

    cout << "Introduce la k deseada." << endl;
    int k;
    cin >> k;
    cout << "Introduce t" << endl;
    uint t;
    cin >> t;
    KShingleSet kshingleset1(k, texts[0], textSize[0]);
    KShingleSet kshingleset2(k, texts[1], textSize[1]);
    cout << "El coeficiente de jaccard es con la manera guay " << kshingleset1.jaccard(kshingleset2) << endl;

    MinHashSignatures minHashSignatures(t, k, texts, textSize);
    cout << "El coeficiente de jaccard es con la manera NO guay "  <<    minHashSignatures.jaccard(0, 1) << endl;

}

void teslLSH() {

    cout << "Introduce la k deseada." << endl;
    int k;
    cin >> k;
    cout << "Introduce la b deseada." << endl;
    int b;
    cin >> b;

}

int main() {
    testMinHash(2, "lorem");
}

