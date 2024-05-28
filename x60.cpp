// Hundido y vencido
// -----------------
// Estructuras de datos


// Utiliza las clases de la STL de C++ para este problema
// Añade los #include que creas necesarios

#include <iostream>
#include <cassert>
#include <fstream>
#include <unordered_set>
#include <string>
#include <unordered_map>


using namespace std;


//
// Implementa a continuación la función que trata un caso de prueba.
// Devuelve false si, en lugar de un caso de prueba, se encuentra la marca
// de fin de la entrada (0 0), o true en caso contrario.
//

bool tratar_caso() {
    int alumnos, flotas;
    string nombre, flota;
    cin >> alumnos >> flotas;
    if (alumnos == 0 && flotas == 0) return false;
    unordered_map<string, unordered_set<string>> alumnosFlotas;
    unordered_map<string, unordered_set<string>> flotasAlumnos;
    for (int i = 0; i < alumnos; ++i) {
        cin >> nombre;
        alumnosFlotas[nombre];
        for (int j = 0; j < flotas; ++j) {
            cin >> flota;
            alumnosFlotas.at(nombre).insert(flota);
            flotasAlumnos[flota].insert(nombre);
        }
    }
    int numeroPasos;
    cin >> numeroPasos;
    for (int i = 0; i < numeroPasos; ++i) {
        cin >> nombre;
        cin >> flota;
        if (flotasAlumnos.count(flota)) {

            bool vencido = false;
            auto it = flotasAlumnos[flota].begin();
            while (it != flotasAlumnos[flota].end()) {
                const string &al = *it;
                if(al != nombre) alumnosFlotas[al].erase(flota);
                if (!vencido && alumnosFlotas[al].empty()) {
                    vencido = true;
                }
                ++it;
            }


            if (flotasAlumnos[flota].size() == 1 && flotasAlumnos.at(flota).count(nombre)) cout << "AGUA" << '\n';
            else {

                auto it = flotasAlumnos[flota].begin();
                while (it != flotasAlumnos[flota].end()) {
                    if (*it != nombre) {
                        it = flotasAlumnos[flota].erase(it);
                    } else {
                        ++it;
                    }
                }
                if(flotasAlumnos[flota].empty()) flotasAlumnos.erase(flota);
                if (vencido) cout << "VENCIDO\n";
                else cout << "HUNDIDO" << '\n';
            }


        } else {
            cout << "AGUA" << '\n';
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
#endif

    return 0;
}
