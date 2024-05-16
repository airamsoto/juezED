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
#include <vector>
#include <cassert>


using namespace std;





class ToeplitzMatrix {
private:
    vector<int> matriz;
    int n, m;

public:
    ToeplitzMatrix(int filas, int columnas, int valor) : n(filas), m(columnas) {
        matriz.resize(n + m - 1, valor);
    }
    assert(i >= 0 && i < n && j >= 0 && j < m);

    int get(int i, int j) {
        int pos = n-i+j;
        return matriz[pos];
    }

    void set(int i, int j, int valor) {
        //assert(i >= 0 && i < n && j >= 0 && j < m);
        //matriz[j - i + n - 1].push_back(valor);
        matriz[n-i+j] = valor;
    }
};


// Define aquí la clase ToeplitzMatrix e implementa sus métodos.
//
// No te olvides de indicar y justificar el coste del constructor y el coste de cada método.

void ejecuta(int filas, int columnas, int valor) {
    string op;
    int i, j, a;
    ToeplitzMatrix matrix =  ToeplitzMatrix(filas,columnas,valor);
//llamada al constructor

    cin >> op;
    while (op != "FIN") {
        if (op == "set") {
            cin >> i >> j >> a;

            matrix.set(i,j,a);
//llama a funcion de clase
        }
        else if (op == "get") {
            cin >> i >> j;
            cout << matrix.get(i,j) <<endl;
//llama a funcion de clase constante
        }
        cin >> op;
    }
    cout << "---\n";
}

bool tratar_caso() {
    int filas, columnas, valor;
    cin >> filas >> columnas >> valor;
    if (filas == 0 && columnas == 0 && valor == 0) return false;
// Implementa el código para tratar un caso de prueba.
    ejecuta(filas, columnas, valor);
// Esta función debe devolver `false` si, en lugar de un caso de prueba,
// se ha encontrado con la marca de fin de entrada (0 0 0).
    return true;
// En caso contrario, debe procesar el caso de prueba y devolver `true`.
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (tratar_caso()) {}

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}