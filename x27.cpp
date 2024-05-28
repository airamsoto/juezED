// El mayor de cada k elementos
// ----------------------------
// Estructuras de datos


/*
  En este ejercicio solamente pueden utilizarse las colecciones vistas durante
  esta semana: pilas, colas, o dobles colas.

  En lugar de utilizar las implementaciones vistas en clase, utilizad las que
  vienen implementadas en la biblioteca estándar de C++, que son las
  siguientes:

  - queue, definida en el fichero de cabecera <queue>
    Documentación: https://en.cppreference.com/w/cpp/container/queue

  - stack, definida en el fichero de cabecera <stack>
    Documentación: https://en.cppreference.com/w/cpp/container/stack

  - deque, definida en el fichero de cabecera <deque>
    Documentación: https://en.cppreference.com/w/cpp/container/deque

  Añade los #include con los ficheros de cabecera del TAD o los TADs que
  vais a utilizar.
*/


#include <iostream>
#include <cassert>
#include <string>
#include <fstream>
#include <stack>
#include <deque>


using namespace std;



// Implementa aquí la función para tratar UN caso de prueba. La función
// devuelve false si, en lugar de encontrarse con un caso de prueba, se ha
// topado con la marca de fin de fichero. Por el contrario, si se ha
// encontrado con un caso de prueba y lo ha procesado, devuelve true.

// No olvides indicar y justificar el coste de la función.


bool tratar_caso() {
    int n, s, aux, k = 1, poslastPila = 0;
    cin >> n >> s;
    stack <int> pila;
    deque<int> dobleCola;
    if (!cin) return false;
    for (int i = 0; i < n; ++i) {
        /*
        cin >> aux;
        if(pila.empty()) {
            poslastPila = 1;
            pila.push(aux);
        } else if(pila.top() < aux) {
            poslastPila = 1;

            pila.pop();
            pila.push(aux);

        }
        if(k == s || s == 1) {
            k--;
            cout << pila.top() << " ";
            if(poslastPila >= s) pila.pop();
        }
        k++;
        poslastPila++;*/
        cin >> aux;
        if(dobleCola.empty()) {
            dobleCola.push_front(aux);

        } else {
            if (aux > dobleCola.front()) {
                dobleCola.push_back(dobleCola.front());
                dobleCola.pop_front();
                dobleCola.push_front(aux);
            }
        }
        if(k == s) {

        }


    }
    cout << '\n';


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
