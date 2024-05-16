// Paréntesis equilibrados
// -----------------------
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
using namespace std;

template<
	class T,
	class Container = std::deque<T>
> class stack;


// Implementa aquí la función para tratar UN caso de prueba. La función
// devuelve false si, en lugar de encontrarse con un caso de prueba, se ha
// topado con la marca de fin de fichero. Por el contrario, si se ha
// encontrado con un caso de prueba y lo ha procesado, devuelve true.

// No olvides indicar y justificar el coste de la función.

bool tratar_caso() {
	std::stack<char> pila;
	string frase;
	bool vabien = true;
	getline(cin, frase);
	if (!cin)return false;
	for (char letra : frase) {
		if (letra == '[' || letra == '{' || letra == '(') {
			pila.push(letra);

		}
		else if (letra == ']' || letra == '}' || letra == ')') {
			if (pila.empty()) {
				cout << "NO" << endl;
				return true;
			}
			char top = pila.top();
			pila.pop();
			switch (letra) {
			case ']':if (top != '[') {
				cout << "NO\n";
				return true;
			}break;
					

			case ')':if (top != '(') {
				cout << "NO\n";
				return true;
			}break;
					
			case '}':if (top != '{') {
				cout << "NO\n";
				return true;
			}break;
					
			}

		}
	}
	if (pila.empty()) cout << "SI\n";
	else cout << "NO\n";
	return true;


}

int main() {

#ifndef DOMJUDGE
	std::ifstream in("sample.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (tratar_caso()) {

	}

	// Comenta esto también si has comentado lo anterior.
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
#endif
	return 0;
}