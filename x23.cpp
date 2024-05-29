// Facundo y el undo
// -----------------
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
#include <sstream>


using namespace std;



// Implementa aquí la función para tratar UN caso de prueba.

// No olvides indicar y justificar el coste de la función.

void tratar_caso() {
    string aux;
    deque <string> frase;
    stack <string> borradas;

    getline(cin, aux);
    bool z = false;
    stringstream ss(aux);
    string palabra;
    while (ss >> palabra) {
        if (palabra == "*" && !frase.empty()) {
            borradas.push(frase.front());
            frase.pop_front();
            z = false;
        } else if (palabra == "+" ) {

            if(borradas.empty() && !frase.empty() && !z) {
                frase.pop_front();
            } else if(!borradas.empty()) {
                frase.push_front(borradas.top());
                borradas.pop();
            } z = true;
        } else if (palabra != "*" && palabra != "+") {
            frase.push_front(palabra);
            if(!borradas.empty())
            borradas.pop();
            z = false;
        }
    }
    while (!frase.empty()) {
        cout << frase.back() << " ";
        frase.pop_back();
    }
    cout << '\n';
    /*
     * 4
Hola me llaom * llamo javier * Javier y boy a Guadalajara * Toledo * * * voy a Toledo
Cuatro * * Cinco lobitos tiene * + la lova * * * + + loba
Y + + Pero la lova no * * * + loba no esta para + pa tipos como Platero y + * tu
hola * hello * + + * + +
     */

}


int main() {
    // Leemos el número de casos de prueba
#ifndef DOMJUDGE
    std::ifstream in("sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int num_casos;
    cin >> num_casos;
    cin.ignore(10, '\n');

    // Ejecutamos tratar_caso() tantas veces como diga el número leído
    for (int i = 0; i < num_casos; i++) {
        tratar_caso();
    }
    // Comenta esto tambi�n si has comentado lo anterior.
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif

    return 0;
}
