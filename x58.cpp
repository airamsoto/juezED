// Eligiendo deporte
// -----------------
// Estructuras de datos


// Utiliza las clases de la STL de C++ para este problema
// Añade los #include que creas necesarios

#include <iostream>
#include <fstream>
#include <cassert>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
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

    unordered_map<string, unordered_set<string>> competiciones;
    unordered_map<string, string> alumnosMAPA;
    unordered_map<string, int> results;
    unordered_set<string> vetados;
    unordered_set<string> eliminados;
    cin >> aux;
    if (!cin) return false;
    while (aux != "_FIN_") {

        string alumnos;
        cin >> alumnos;
        if (!results.count(aux)) results[aux] = 0;
        while (islower(alumnos[0]) || isdigit(alumnos[0])) {
            if (!vetados.count(alumnos)) {
                competiciones[aux].insert(alumnos);
                alumnosMAPA[alumnos] = aux;
                results[aux] += 1;
                vetados.insert(alumnos);
            } else if (alumnosMAPA.count(alumnos) && alumnosMAPA.at(alumnos) != aux && !eliminados.count(alumnos)) {
                results[alumnosMAPA.at(alumnos)] -= 1;
                competiciones[alumnosMAPA.at(alumnos)].erase(alumnos);
                vetados.insert(alumnos);
                eliminados.insert(alumnos);
            }

            cin >> alumnos;
        }
        aux = alumnos;
    }
    vector<pair<string, int >> sorted_r(results.begin(), results.end());

    sort(sorted_r.begin(), sorted_r.end(), [](const pair<string, int> &a, const pair<string, int> &b) {
        if (a.second != b.second)
            return a.second > b.second;
        return a.first < b.first;
    });

    for (const auto &result: sorted_r) {
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
