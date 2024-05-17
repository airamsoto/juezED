// Referencias cruzadas
// --------------------
// Estructuras de datos


// Utiliza las clases de la STL de C++ para este problema
// Añade los #include que creas necesarios

#include <iostream>
#include <cassert>
#include <fstream>
#include <map>
#include <sstream>
#include <set>

using namespace std;


//
// Implementa a continuación la función que trata un caso de prueba.
// Devuelve false si, en lugar de un caso de prueba, se encuentra la marca
// de fin de la entrada (0), o true en caso contrario.
//


bool tratar_caso() {
    int lineas;
    cin >> lineas;
    if (lineas == 0) return false;

    map<string, set<int>> palabras;
    string aux, linea;
    cin.ignore();

    for (int i = 1; i <= lineas; i++) {
        getline(cin, linea);
        istringstream stream(linea);

        while (stream >> aux) {
            for (char &c: aux) {
                c = tolower(c);

            }
            if (aux.length() > 2) {
                if (palabras.count(aux) == 0) {
                    set<int> lineasset = {i};
                    palabras.insert({aux, lineasset});
                } else { ;
                    palabras.at(aux).insert(i);
                }

            }


        }
    }

    for (const auto &pair: palabras) {

        cout << pair.first << " ";
        for (const auto &linea: pair.second) {
            cout << linea << " ";
        }
        cout << '\n';

    }


    cout << "---\n";

    return true;

    // ...
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif


    while (tratar_caso()) {}


#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // Comentar si no se trabaja en Visual Studio
    //  system("PAUSE");
#endif

    return 0;
}
