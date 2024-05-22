// Ferrovistán
// -----------
// Estructuras de datos

// Añade los #include que creas necesarios

#include <iostream>
#include <fstream>
#include <vector>


using namespace std;


class Ferrovistan {
public:

    void nueva_linea(const string &nombre) {

    }


    void nueva_estacion(const string &linea, const string &nombre, int posicion) {

    }

    void eliminar_estacion(const string &estacion) {

    }

    vector<string> lineas_de(const string &estacion) const {
        return {};
    }

    string proxima_estacion(const string &linea, const string &estacion) const {
        return "";
    }

private:

};



bool tratar_caso() {
    Ferrovistan f;
    string operacion;
    cin >> operacion;

    if (cin.eof()) return false;

    while (operacion != "FIN") {
        try {
            if (operacion == "nueva_linea") {
                string nombre; cin >> nombre;
                f.nueva_linea(nombre);
            } else if (operacion == "nueva_estacion") {
                string linea; cin >> linea;
                string nombre; cin >> nombre;
                int posicion; cin >> posicion;
                f.nueva_estacion(linea, nombre, posicion);
            } else if (operacion == "eliminar_estacion") {
                string estacion; cin >> estacion;
                f.eliminar_estacion(estacion);
            } else if (operacion == "lineas_de") {
                string estacion; cin >> estacion;
                vector<string> lineas = f.lineas_de(estacion);
                cout << "Lineas de " << estacion << ":";
                for (const string &linea: lineas) {
                    cout << " " << linea;
                }
                cout << "\n";
            } else if (operacion == "proxima_estacion") {
                string linea; cin >> linea;
                string estacion; cin >> estacion;
                string proxima = f.proxima_estacion(linea, estacion);
                cout << proxima << "\n";
            }
        } catch (exception &e) {
            cout << "ERROR: " << e.what() << "\n";
        }
        cin >> operacion;
    }
    cout << "---\n";
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

