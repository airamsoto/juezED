// Reordenando la cola
// -------------------
// Estructuras de datos


/*
  En este ejercicio solamente pueden utilizarse las colecciones vistas durante
  esta semana: pilas, colas, o dobles colas.

  En lugar de utilizar las implementaciones vistas en clase, utilizad las que
  vienen implementadas en la biblioteca est‡ndar de C++, que son las
  siguientes:

  - queue, definida en el fichero de cabecera <queue>
    Documentaci—n: https://en.cppreference.com/w/cpp/container/queue

  - stack, definida en el fichero de cabecera <stack>
    Documentaci—n: https://en.cppreference.com/w/cpp/container/stack

  - deque, definida en el fichero de cabecera <deque>
    Documentaci—n: https://en.cppreference.com/w/cpp/container/deque

  A–ade los #include con los ficheros de cabecera del TAD o los TADs que
  vais a utilizar.
*/


#include <iostream>
#include <cassert>
#include <string>
#include <fstream>
#include <queue>
#include <stack>


using namespace std;

template<
        class T,
        class Container = std::deque<T>
>
class queue;

template<
        class T,
        class Container = std::stack<T>
>
class stack;


// Implementa aqu’ la funci—n para tratar UN caso de prueba. La funci—n
// devuelve false si, en lugar de encontrarse con un caso de prueba, se ha
// topado con la marca de fin de entrada (0). Por el contrario, si se ha
// encontrado con un caso de prueba y lo ha procesado, devuelve true.

// No olvides indicar y justificar el coste de la funci—n.

bool tratar_caso() {
    std::deque<int> dobleCola;
    int n, num;
    cin >> n;
    if (n == 0) return false;
    for (int i = 0; i < n; i++) {
        cin >> num;
        if (num < 0) dobleCola.push_back(num);
        else dobleCola.push_front(num);
    }
    while (!dobleCola.empty()) {
        cout << dobleCola.back() << " ";
        dobleCola.pop_back();
    }
    cout << endl;
    return true;

}


int main() {

#ifndef DOMJUDGE
    std::ifstream in("sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif


    while (tratar_caso()) {}

    // Comenta esto tambiŽn si has comentado lo anterior.
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}