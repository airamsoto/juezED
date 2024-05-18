// Eligiendo deporte
// -----------------
// Estructuras de datos


// Utiliza las clases de la STL de C++ para este problema
// Añade los #include que creas necesarios

#include <iostream>
#include <fstream>
#include <cassert>
#include <unordered_map>
#include <set>
#include <vector>
#include <algorithm>


using namespace std;


//
// Implementa a continuación la función que trata un caso de prueba.
// Devuelve false si, en lugar de un caso de prueba, se encuentra la marca
// de fin de la entrada (EOF), o true en caso contrario.
//

bool tratar_caso() {
    string aux;
    
    unordered_map<string, set<string>> competiciones;
    set<string> vetados;
    cin >> aux;
    while (aux != "_FIN_") {

        competiciones.emplace(aux, set<string>());
        string alumnos;
        cin >> alumnos;
        while (islower(alumnos[0]) || isdigit(alumnos[0])) {

            if( !vetados.count(alumnos)) {

                competiciones[aux].insert( alumnos);
                vetados.insert(alumnos);
            } else if (competiciones[aux].count(alumnos)) {

            } else {
                for (auto& par : competiciones) {
                    par.second.erase(alumnos);
                }
                vetados.insert(alumnos);

            }

            cin >> alumnos;
        }
        aux = alumnos;
    }
    vector<pair<string, int>> resultados;
    for (const auto& pair : competiciones) {
        resultados.emplace_back(pair.first, pair.second.size());
    }
    sort(resultados.begin(), resultados.end(), [](const auto& a, const auto& b) {
        return (a.second > b.second || (a.second == b.second && a.first[0] < b.first[0]));
    });
    for (const auto& result : resultados) {
        cout << result.first << " " << result.second << endl;
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
