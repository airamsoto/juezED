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


 // Añade los #include que necesites
#include <iostream>
#include <fstream>
#include <cassert>
#include <map>

//usamos string para el stoi
#include <string>

using namespace std;

// En este ejercicio utilizamos la clase `map` de la librería estándar de C++,
// en lugar de la clase MapTree vista en clase. La interfaz de `map` es casi
// la misma que la de `MapTree`. Consulta el FAQ de la práctica para ver las
// diferencias principales.

// También puedes ver la documentación de la clase `map` en:
// https://en.cppreference.com/w/cpp/container/map



// Define un tipo para representar los programas

using programa = map<int, pair<string, string>>;

// Define un tipo para almacenar el valor de cada variable del programa

using memoria = map<string, int>;


// Función para ejecutar un programa.
//
// Recibe:
//    - El programa `p` a ejecutar
//    - Máximo número de instrucciones a ejecutar. Si se intenta ejecutar un número mayor
//      de instrucciones, se detiene la ejecución y se devuelve la memoria correspondiente
//      al estado del programa en el momento de detenerse.
//
// Devuelve un par con dos componentes:
//    - El estado de la memoria tras la ejecución del programa, bien sea porque se haya
//      ejecutado la última instrucción, o bien porque se haya alcanzado el límite de
//      instrucciones ejecutadas indicado por el parámetro `max_pasos`.  
//    - Un booleano que indique si se ha producido un error en la ejecución del programa
//      Devuelve `true` si se ha encontrado ejecutar una instrucción "GOTO n", donde n
//      es un número de instrucción que no se encuentra en el programa. Devuelve `false`
//      en caso contrario. Si el valor de esta componente es `true`, la primera componente
//      del par es irrelevante.

// Indica el coste, en el caso peor, de la función `ejecutar`, en función del tamaño
// del programa `p` y de `num_pasos`
pair<memoria, bool> ejecutar(const programa& p, int max_pasos) {
    memoria mem;

    auto it = p.begin();
    while (max_pasos > 0 && it != p.end()) {
        auto [ins, value] = it->second;

        if (it == p.end()) {
            return { mem, true };
        }

        if (ins == "INCR") {
            auto it2 = mem.find(value);
            if (it2 != mem.end()) {
                mem.insert_or_assign(value, ++it2->second);

            }
            else {
                mem.insert_or_assign(it->second.second, 1);
            }
            ++it;
        }
        else if (it->second.first == "GOTO") {
            int num = stoi(it->second.second);
            auto goto_it = p.find(num);
            if (goto_it == p.end()) {
                return { mem, false };
            }
            it = goto_it;
        }
        max_pasos--;
    }

    return { mem, true };
}



// Introduce el código para tratar un caso de prueba. Devuelve true
// si se ha encontrado un caso de prueba en la entrada, o false si,
// en su lugar, se ha encontrado la marca de fin de fichero (EOF).
bool tratar_caso() {
    int pos;
    string orden;
    string ins;
    int dir;
    string var;
    int pasos;

    programa p;
    cin >> orden;
    if (!cin) {
        return false;
    }
    while (cin && orden != "BYE") {
        while (orden != "RUN") {
            pos = stoi(orden);
            cin >> ins;
            cin >> var;
            pair<string, string> pair = { ins, var };
            p.insert_or_assign(pos, pair);
            cin >> orden;
        }
        cin >> pasos;
        auto sol = ejecutar(p, pasos);
        // ejecutar instrucciones del mapa
        if (!sol.second) {
            std::cout << "ERROR\n";
        }
        else {
            for (auto [k, val] : sol.first) {
                cout << k << " = " << val << endl;
            }
            // recorrer todas la variables de memoria y escribir por pantalla
            cout << "OK\n";
        }
        cin >> orden;
    }
    std::cout << "---\n";
    return true;
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

// Llamamos a `tratar_caso` hasta que se agoten los casos de prueba
while (tratar_caso()) {}

// Comenta esto también si has comentado lo anterior.
#ifndef DOMJUDGE
std::cin.rdbuf(cinbuf);
#endif
return 0;
}