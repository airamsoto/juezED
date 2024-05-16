// De postre, un chuletón
// ----------------------
// Estructuras de datos


#include <iostream>
#include <cassert>
#include <fstream>
#include <cassert>
#include <list>

using namespace std;


enum class Categoria { Primero, Segundo, Postre };

struct Plato {
    Categoria categoria;
    string nombre;
};

// Sobrecarga del operador << para imprimir platos
ostream &operator<<(ostream &out, const Plato &plato) {
    switch (plato.categoria) {
        case Categoria::Primero:
            out << "1";
            break;
        case Categoria::Segundo:
            out << "2";
            break;
        case Categoria::Postre:
            out << "P";
            break;
    }
    out << " " << plato.nombre;
    return out;
}


// Indica el coste en función del tamaño del parámetro de entrada
void ordenar_menu(list<Plato> &platos) {
    if (!platos.empty()) {
        auto it = platos.begin();
        for (int i = 0; i < platos.size(); i++) {
            if (it->categoria == Categoria::Primero) {
                platos.insert(platos.end(), *it);
                it = platos.erase(it);
            }
            else it++;
        }
        it = platos.begin();
        for (int i = 0; i < platos.size(); i++) {
            if (it->categoria == Categoria::Segundo) {
                platos.insert(platos.end(), *it);
                it = platos.erase(it);
            }
            else it++;
        }
        it = platos.begin();
        for (int i = 0; i < platos.size(); i++) {
            if (it->categoria == Categoria::Postre) {
                platos.insert(platos.end(), *it);
                it = platos.erase(it);
            }
            else it++;
        }
    }
}


bool tratar_caso() {
    Plato plato;

    list<Plato> lista;

    int n;
    string cat;
    cin >> n;
    if (n == 0) return false;
    int primeros = 0, segundos = 0, postres = 0;
    for (int i = 0; i < n; ++i) {
        cin >> cat;
        if (cat == "P") {
            plato.categoria = Categoria::Postre;

        }
        else if (cat == "1") {
            plato.categoria = Categoria::Primero;

        }
        else if (cat == "2"){
            plato.categoria = Categoria::Segundo;

        }
        getline(cin, plato.nombre);
        lista.push_back(plato);
    }

    ordenar_menu(lista);
    for (Plato p : lista) {
        cout << p;
        cout << endl;
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

    // Comenta esto también si has comentado lo anterior.
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}

