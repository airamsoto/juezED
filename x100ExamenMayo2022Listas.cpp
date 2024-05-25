#include <iostream>
#include <list>
#include <stack>
#include <fstream>

using namespace std;

void reconstruir(list<int> &lista) {
    auto it = lista.begin();
    stack<int> pila;

    while (it != lista.end()) {
        if (*it > 0) {
            pila.push(*it);
            it++;

        } else {
            if (!pila.empty()) {
             *it = -1*pila.top();
              pila.pop();
              it++;
            } else {
                it = lista.erase(it);
            }

        }

    }
    while (!pila.empty()) lista.push_back(-pila.top()), pila.pop();
}

bool tratar_caso() {
    int n, aux;
    list<int> l1;

    cin >> n;
    if (!cin) return false;

    for (int i = 0; i < n; ++i) {
        cin >> aux;
        l1.push_back(aux);
    }

    reconstruir(l1);

    for (const auto &elem : l1) {
        cout << elem << " ";
    }
    cout << '\n';

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
