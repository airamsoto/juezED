#include <iostream>
#include <cassert>
#include <fstream>
#include <list>
#include <cmath>

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
    auto inicio = joses.begin();
    auto next = ++joses.begin();
    while ( inicio != --joses.end() && next != joses.begin()) {
        if(*inicio - *next < -1) {
            inicio = joses.insert(next, *inicio +1);

        } else if(*inicio - * next > 1) {
            inicio = joses.insert(next , *inicio -1);

        } else if( *inicio - * next  ==0 ) {
            next = joses.erase(next);

        } else {
            inicio++;
            next++;
        }
    }
   auto it = joses.begin();
    while (it != joses.end()) {
        cout << *it << " ";
        it++;
    }
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
