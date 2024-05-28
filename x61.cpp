// Capítulos repetidos
// -------------------
// Estructuras de datos


// Utiliza las clases de la STL de C++ para este problema
// Añade los #include que creas necesarios

#include <iostream>
#include <cassert>
#include <fstream>
#include <unordered_set>
#include <unordered_map>

using namespace std;


//
// Implementa a continuación la función que trata un caso de prueba.
// Devuelve false si, en lugar de un caso de prueba, se encuentra la marca
// de fin de la entrada (EOF), o true en caso contrario.
//

void tratar_caso() {
    int numero_capitulos, capitulo, ultimoCapitulo;
    unordered_set<int> capitulos;
    unordered_map <int, int> capituloDia;
    int contadorActual = 0, contadorMejor = 0;
    cin >> numero_capitulos;
    for (int j = 0; j < numero_capitulos; ++j) {
        cin >> capitulo;
        if (!capitulos.count(capitulo)) {
            capituloDia.insert({capitulo, j});
            capitulos.insert(capitulo);
            contadorActual++;
            contadorMejor = max(contadorActual, contadorMejor);

        } else {
            int posCapitulo = capituloDia.at(capitulo);
            capituloDia[capitulo] = j;
            int intervalo = j - posCapitulo;
            if(contadorActual < intervalo) contadorActual++;
            else contadorActual = j - posCapitulo;

            contadorMejor = max(contadorActual, contadorMejor);
        }

    }
    cout << contadorMejor << '\n';
}


int main() {
#ifndef DOMJUDGE
    std::ifstream in("sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        tratar_caso();
    }


#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif

    return 0;
}

