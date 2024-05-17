// Me pilló el toro
// ----------------
// Estructuras de datos


// Utiliza las clases de la STL de C++ para este problema
// Añade los #include que creas necesarios

#include <iostream>
#include <cassert>
#include <fstream>
#include <map>

using namespace std;


//
// Implementa a continuación la función que trata un caso de prueba.
// Devuelve false si, en lugar de un caso de prueba, se encuentra la marca
// de fin de la entrada (0), o true en caso contrario.
//

bool tratar_caso() {
    int numero;
    string nombre, nota;
    map <string, int> alumnos;
    cin >> numero;
    if (numero == 0) return false;
    for (int i = 0; i < numero; ++i) {
        cin.ignore();
        getline(cin, nombre);

        cin >> nota;
        if(alumnos.count(nombre) != 0) { //aqui si esta
            if (nota == "INCORRECTO")
            alumnos.at(nombre)--;
            else alumnos.at(nombre)++;

        } else { //no esta
            if(nota == "INCORRECTO")
            alumnos.insert({nombre, -1});
            else alumnos.insert({nombre,1});
        }
    }
    for (const auto& pair : alumnos) {
        if(pair.second != 0) {
            cout << pair.first << ", " << pair.second << '\n';

        }

    }
    cout << "---\n";
    return true;
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