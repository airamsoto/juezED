// Teclado estropeado
// ------------------
// Estructuras de datos


#include <iostream>
#include <cassert>
#include <list>
#include <fstream>

using namespace std;


void teclado (list<char> &lista, string frase) {
    auto it = lista.begin();
    for (char c: frase) {

        if (c == '-') {
            it = lista.begin();
        } else if (c == '+') {
            it = lista.end();
        } else if (c == '*') {
            if (it != lista.end())
                it++;
        } else if (c == '3') {
            if (it != lista.end())
                it = lista.erase(it);
        } else {
            lista.insert(it, c);
        }

    }

    for (char c: lista) cout << c;

}

bool tratar_caso() {
    list<char> lista;
    string frase;
    getline(cin, frase);
    if(!cin) return false;
    teclado(lista, frase);
    cout <<endl;
    return true;
}

int main() {

#ifndef DOMJUDGE
    std::ifstream in("sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif


    while (tratar_caso()) {}

    // Comenta esto tambi�n si has comentado lo anterior.
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}
