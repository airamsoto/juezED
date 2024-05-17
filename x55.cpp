// Todos al jardín
// ---------------
// Estructuras de datos


// Utiliza las clases de la STL de C++ para este problema
// Añade los #include que creas necesarios

#include <iostream>
#include <cassert>
#include <map>
#include <fstream>
#include <queue>
using namespace std;


//
// Implementa a continuación la función que trata un caso de prueba.
// Devuelve false si, en lugar de un caso de prueba, se encuentra la marca
// de fin de la entrada (0 0 0), o true en caso contrario.
//REPRESENTO EL 5 COMO JEFE



#include <iostream>
#include <map>
#include <fstream>
#include <set>
#include <vector>
using namespace std;

bool tratar_caso() {
    int c, n, m;
    cin >> c >> n >> m;
    if (c == 0 && n == 0 && m == 0) return false;

    map<int, int> despachos;
    set<int> despachos_ocupados;
    vector<int> empleados(n), directivos(m);

    for (int i = n - 1; i >= 0; --i) {
        cin >> empleados[i];
    }

    for (int i = m - 1; i >= 0; --i) {
        cin >> directivos[i];
    }

    for (int i = 0; i < m; ++i) {
        int despacho = directivos[i];
        while (despachos_ocupados.count(despacho)) {
            despacho++;
        }
        despachos[despacho] = 5;
        despachos_ocupados.insert(despacho);
    }
    for (int i = 0; i < n; ++i) {
        int despacho = empleados[i];
        while (despachos_ocupados.count(despacho) || (despachos[despacho] >= c && despachos[despacho] != 5)) {
            despacho++;
        }
        despachos[despacho]++;
        if (despachos[despacho] == c) {
            despachos_ocupados.insert(despacho);
        }
    }

    for (const auto &pair : despachos) {
        cout << pair.first << " ";
        if (pair.second == 5) {
            cout << "JEFE\n";
        } else {
            cout << pair.second << '\n';
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




