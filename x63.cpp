#include <iostream>
#include <unordered_map>
#include <map>
#include <vector>
#include <string>
#include <stdexcept>
#include <fstream>

using namespace std;

class Autoescuela {
public:
    Autoescuela() {}

    void alta(const string &alumno, const string &profesor) {
        int puntuacion = 0;
        auto it = alumno_a_profesor.find(alumno);
        if (it != alumno_a_profesor.end()) {
            puntuacion = autoescuela[it->second].at(alumno);
            autoescuela[it->second].erase(alumno);
        }

        autoescuela[profesor][alumno] = puntuacion;
        alumno_a_profesor[alumno] = profesor;
    }

    bool es_alumno(const string &alumno, const string &profesor) const {
        auto it = autoescuela.find(profesor);
        if (it != autoescuela.end()) {
            return it->second.count(alumno) > 0;
        }
        return false;
    }

    int puntuacion(const string &alumno) const {
        auto it = alumno_a_profesor.find(alumno);
        if (it != alumno_a_profesor.end()) {
            return autoescuela.at(it->second).at(alumno);
        }
        throw std::domain_error("El alumno A no esta matriculado");
    }

    void actualizar(const string &alumno, int puntos) {
        auto it = alumno_a_profesor.find(alumno);
        if (it != alumno_a_profesor.end()) {
            autoescuela[it->second].at(alumno) += puntos;
        } else {
            throw std::domain_error("El alumno A no esta matriculado");
        }
    }

    vector<string> examen(const string &profesor, int minimo_puntos) const {
        vector<string> alumnos;
        auto it = autoescuela.find(profesor);
        if (it != autoescuela.end()) {
            for (const auto &pair : it->second) {
                if (pair.second >= minimo_puntos) {
                    alumnos.push_back(pair.first);
                }
            }
        }
        return alumnos;
    }

    void aprobar(const string &alumno) {
        auto it = alumno_a_profesor.find(alumno);
        if (it != alumno_a_profesor.end()) {
            autoescuela[it->second].erase(alumno);
            alumno_a_profesor.erase(alumno);
        } else {
            throw std::domain_error("El alumno A no esta matriculado");
        }
    }

private:
    unordered_map<string, map<string, int>> autoescuela;
    unordered_map<string, string> alumno_a_profesor;
};

bool tratar_caso() {
    Autoescuela ae;
    string operacion;
    cin >> operacion;
    if (cin.eof()) return false;

    while (operacion != "FIN") {
        try {
            if (operacion == "alta") {
                string alumno, profesor;
                cin >> alumno >> profesor;
                ae.alta(alumno, profesor);
            } else if (operacion == "es_alumno") {
                string alumno, profesor;
                cin >> alumno >> profesor;
                if (ae.es_alumno(alumno, profesor)) {
                    cout << alumno << " es alumno de " << profesor << endl;
                } else {
                    cout << alumno << " no es alumno de " << profesor << endl;
                }
            } else if (operacion == "puntuacion") {
                string alumno;
                cin >> alumno;
                int puntuacion = ae.puntuacion(alumno);
                cout << "Puntuacion de " << alumno << ": " << puntuacion << endl;
            } else if (operacion == "actualizar") {
                string alumno;
                int puntuacion;
                cin >> alumno >> puntuacion;
                ae.actualizar(alumno, puntuacion);
            } else if (operacion == "examen") {
                string profesor;
                int minimo_puntos;
                cin >> profesor >> minimo_puntos;
                cout << "Alumnos de " << profesor << " a examen:" << endl;
                for (const string &nombre : ae.examen(profesor, minimo_puntos)) {
                    cout << nombre << endl;
                }
            } else if (operacion == "aprobar") {
                string alumno;
                cin >> alumno;
                ae.aprobar(alumno);
            }
        } catch (std::exception &e) {
            cout << "ERROR" << endl;
        }

        cin >> operacion;
    }

    cout << "---\n";
    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif


    while (tratar_caso()) {}

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif

    return 0;
}
