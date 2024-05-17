// Actualización de un diccionario
// -------------------------------
// Estructuras de datos


// Utiliza las clases de la STL de C++ para este problema
// Añade los #include que creas necesarios

#include <iostream>
#include <cassert>
#include <fstream>
#include <sstream>
#include <set>
#include <map>

using namespace std;


//
// Implementa a continuación la función que trata un caso de prueba.
//

void tratar_caso() {
    string c, linea;
    int v;
    map<string, int> jose, jose2;
    getline(cin, linea);
    istringstream stream(linea);

    while (stream >> c >> v) {

        jose.insert({c, v});
    }
    set<string> nuevos, eliminados, modificados;
    getline(cin, linea);
    istringstream stream2(linea);
    while (stream2 >> c >> v) {

        jose2.insert({c, v});

    }
    for (const auto &[clave, valor]: jose2) {
        if (jose.count(clave) == 0) {
            nuevos.insert(clave);
        } else if (jose.at(clave) != valor) {
            {

                modificados.insert(clave);
            }
        }
    }
    for (const auto &[clave, valor]: jose) {
        if (jose2.count(clave) == 0) {
            eliminados.insert(clave);
        }
    }
    if (nuevos.empty() && eliminados.empty() && modificados.empty()) {
        cout << "Sin cambios" << endl;
    } else {
        if (!nuevos.empty()) {
            cout << "+ ";
            for (const auto &clave: nuevos) {
                cout << clave << " ";
            }
            cout << endl;
        }
        if (!eliminados.empty()) {
            cout << "- ";
            for (const auto &clave: eliminados) {
                cout << clave << " ";
            }
            cout << endl;
        }
        if (!modificados.empty()) {
            cout << "* ";
            for (const auto &clave: modificados) {
                cout << clave << " ";
            }
            cout << endl;
        }
    }

    cout << "---" << endl;


}


int main() {
#ifndef DOMJUDGE
    ifstream in("sample.in");
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
    int n;
    cin >> n;
    cin.ignore();
    for (int i = 0; i < n; ++i) {
        tratar_caso();
    }


#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
#endif
    return 0;
}