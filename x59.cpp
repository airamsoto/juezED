#include <iostream>
#include <cassert>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
//TIME LIMIT
using namespace std;

bool tratar_caso() {
    int n, a, p;
    cin >> n >> a >> p;
    if (n == 0 && a == 0 && p == 0) return false;

    unordered_map<string, unordered_map<string, string>> mapa;
    unordered_set<string> activos;
    unordered_set<string> to_remove;

    for (int i = 0; i < n; ++i) {
        string nombre;
        cin >> nombre;
        activos.insert(nombre);
        for (int j = 0; j < a; ++j) {
            string id, sol;
            cin >> id >> sol;
            mapa[nombre][id] = sol;
        }
    }
    for (int i = 0; i < p; ++i) {
        string id, sol;
        cin >> id >> sol;


        for (const auto& estudiante : activos) {
            if (mapa[estudiante].count(id) && mapa[estudiante][id] != sol) {
                to_remove.insert(estudiante);
            }
        }

    }
    for (const auto& estudiante : to_remove) {
        activos.erase(estudiante);
    }

    cout << activos.size() << endl;
    return true;
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
