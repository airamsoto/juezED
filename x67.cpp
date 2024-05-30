#include <iostream>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <algorithm>

using namespace std;

class Ferrovistan {
public:

    void nueva_linea(const string &nombre) {
        if (lineas.count(nombre)) {
            throw domain_error("Linea existente");
        }
        lineas.insert({nombre, {}});
    }
    void nueva_estacion(const string &linea, const string &nombre, int posicion) {
        if (!lineas.count(linea)) {
            throw domain_error("Linea no existente");
        }
        auto& estaciones = lineas[linea].estaciones;
        if (estaciones.count(posicion)) {
            throw domain_error("Posicion ocupada");
        }
        estaciones[posicion] = nombre;
        estacion_lineas[nombre].insert(linea);
    }

    void eliminar_estacion(const string &estacion) {
        if (!estacion_lineas.count(estacion)) {
            throw domain_error("Estacion no existente");
        }
        for (const auto& linea : estacion_lineas[estacion]) {
            lineas[linea].estaciones.erase(estacion_posicion(estacion, linea));
        }
        estacion_lineas.erase(estacion);
    }

    vector<string> lineas_de(const string &estacion) const {
        if (!estacion_lineas.count(estacion)) {
            throw domain_error("Estacion no existente");
        }
        vector<string> lineas(estacion_lineas.at(estacion).begin(), estacion_lineas.at(estacion).end());
        sort(lineas.begin(), lineas.end());
        return lineas;
    }

    string proxima_estacion(const string &linea, const string &estacion) const {
        if (!lineas.count(linea)) {
            throw domain_error("Linea no existente");
        }
        const auto& estaciones = lineas.at(linea).estaciones;
        auto it = estaciones.upper_bound(estacion_posicion(estacion, linea));
        auto last = --estaciones.end();
        if (it->second == last->second) {
            throw domain_error("Fin de trayecto");
        }
        return it->second;
    }

private:
    struct InfoLinea {
        map<int, string> estaciones;
    };

    unordered_map<string, InfoLinea> lineas;
    unordered_map<string, unordered_set<string>> estacion_lineas;

    int estacion_posicion(const string& estacion, const string& linea) const {
        for (const auto& p : lineas.at(linea).estaciones) {
            if (p.second == estacion) {
                return p.first;
            }
        }
        throw domain_error("Estacion no existente");
    }
};

bool tratar_caso() {
    Ferrovistan f;
    string operacion;

    while (cin >> operacion) {
        if (operacion == "nueva_linea") {
            string nombre;
            cin >> nombre;
            try {
                f.nueva_linea(nombre);
            } catch (const domain_error &e) {
                cout << "ERROR: " << e.what() << "\n";
            }
        } else if (operacion == "nueva_estacion") {
            string linea, nombre;
            int posicion;
            cin >> linea >> nombre >> posicion;
            try {
                f.nueva_estacion(linea, nombre, posicion);
            } catch (const domain_error &e) {
                cout << "ERROR: " << e.what() << "\n";
            }
        } else if (operacion == "eliminar_estacion") {
            string estacion;
            cin >> estacion;
            try {
                f.eliminar_estacion(estacion);
            } catch (const domain_error &e) {
                cout << "ERROR: " << e.what() << "\n";
            }
        } else if (operacion == "lineas_de") {
            string estacion;
            cin >> estacion;
            try {
                auto lineas = f.lineas_de(estacion);
                cout << "Lineas de " << estacion << ":";
                for (const auto& linea : lineas) {
                    cout << " " << linea;
                }
                cout << "\n";
            } catch (const domain_error &e) {
                cout << "ERROR: " << e.what() << "\n";
            }
        } else if (operacion == "proxima_estacion") {
            string linea, estacion;
            cin >> linea >> estacion;
            try {
                cout << f.proxima_estacion(linea, estacion) << "\n";
            } catch (const domain_error &e) {
                cout << "ERROR: " << e.what() << "\n";
            }
        } else if (operacion == "FIN") {
            cout << "---\n";
            return true;
        }
    }
    return false;
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