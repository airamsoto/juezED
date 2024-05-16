/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */


 /*
   Indica el nombre y apellidos de los componentes del grupo
   ---------------------------------------------------------
   Componente 1: Alberto Zurita Aguado
   Componente 2: Airam Martin Soto

 */

#include <iostream>
#include <fstream>
#include <cassert>
#include <unordered_set>
#include <map>;
#include <unordered_map>;
#include <set>

 // Añade los include que necesites

using namespace std;

bool tratar_caso() {
int num, aux, bombo;
string nombre;
std::map<string, std::unordered_set<int>> jugadores;
bool ganador = false;
std::set<int> numeros;

cin >> num;

if (num == 0) {
return false;
}

for (int i = 0; i < num; i++) {
cin >> nombre;

cin >> aux;
while (aux != 0) {
jugadores[nombre].insert(aux);
numeros.insert(aux);
cin >> aux;
}

}

while (!ganador) {
cin >> bombo;
if (numeros.count(bombo) > 0) {
for (auto& j : jugadores) {
auto& carton = j.second;
if (carton.count(bombo) > 0) {
carton.erase(bombo);
}
if (j.second.empty()) {
ganador = true;
cout << j.first << " ";
}
}
}

}
cout << endl;

return true;
// Escribe aquí el código para tratar un caso de prueba
}

int main() {
// Si estás ejecutando el programa en tu ordenador, las siguientes líneas
// redirigiran cualquier lectura de cin al fichero 'sample.in'. Esto es
// útil para no tener que teclear los casos de prueba por teclado cada vez
// que ejecutas el programa.
//
// Si prefieres teclear los casos de prueba por teclado en tu ordenador,
// comenta las líneas comprendidas entre los #ifndef y #endif
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