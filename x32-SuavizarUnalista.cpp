#include <iostream>
#include <cassert>
#include <fstream>
#include <list>
#include <cmath> // Necesario para abs()

using namespace std;

bool tratar_caso() {
    int n;
    if (!(cin >> n))
        return false;

    list<int> joses;
    int aux;
    for (int i = 0; i < n; i++) {
        cin >> aux;
        joses.push_back(aux);
    }

    auto it = joses.begin();

    while ((it) != (joses.end())) {
        auto nextit = next(it);

        int diferencia = (*nextit - *it);

        if (diferencia > 1) {
            if (*nextit < *it) {
                for (int i = 0; i < diferencia; i++) {
                    it = joses.insert(nextit, *it - 1);
                }
            } else {
                for (int i = 1; i < diferencia; ++i) {
                    it = joses.insert(nextit, *it + 1);
                }
            }
        } else if (diferencia == 0) {
                joses.erase(nextit);
        }

        it++;
    }

    for (int i : joses)
        cout << i << " ";
    cout << endl;

    return true;
}

int main() {
#ifndef DOMJUDGE
    ifstream in("sample.in");
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif

    while (tratar_caso()) {}

#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
#endif
    return 0;
}
