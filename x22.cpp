// Decodificación de mensajes
// --------------------------
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
#include <deque>
#include <stack>
#include <queue>



using namespace std;



// Implementa aquí la función para tratar UN caso de prueba. La función
// devuelve false si, en lugar de encontrarse con un caso de prueba, se ha
// topado con la marca de fin de fichero. Por el contrario, si se ha
// encontrado con un caso de prueba y lo ha procesado, devuelve true.

// No olvides indicar y justificar el coste de la función.
bool esVocal(char c) {
    c = std::tolower(c);
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}
bool tratar_caso() {
    string actual = "";
    char c;
    cin >> c;
    if (!cin) return false;
    deque<char> cola;
    stack<char> pila;
    cola.push_back(c);
    while (std::cin.get(c)) {
        if(c == '\n') break;
        pila.push(c);
        cin >> c;
        if(c == '\n') break;
        cola.push_back(c);

    }
    while (!cola.empty()) {
            if (esVocal(cola.front())) {
                cout << cola.front();
                cola.pop_front();
            } else {
                char aux = cola.front();
                cola.pop_front();
                if(esVocal(aux)) {
                    cout << aux;
                } else {
                    if(!esVocal(cola.front())) {
                        cout << cola.front() << aux;
                        cola.pop_front();

                    } else {
                        cout << aux << cola.front();
                    }
                }

            }

    }

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
