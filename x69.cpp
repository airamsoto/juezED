// Academia de Chino
// -----------------
// Estructuras de datos

// Añade los #include que creas necesarios

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <stdexcept>
#include <stack>
#include <deque>


using namespace std;


class AcademiaChino {
public:

    AcademiaChino() {}

    void nuevo_estudiante(const std::string &dni, int grupo) {
        if (alumnos.count(dni) || alumnos_graduados.count(dni)) {
            throw std::domain_error("Estudiante existente");
        }
        if (grupo <= 0 || grupo > 6) {
            throw std::domain_error("Grupo Incorrecto");
        }
        alumnos.insert(dni);
        alumnos_busquedas[grupo].insert(dni);
        auto it = academia[grupo].insert(academia[grupo].end(), dni);
        alumno_pos[dni] = it;
        alumno_grupo[dni] = grupo;


    }

    int grupo_estudiante(const std::string &dni) const {
        if (alumnos_graduados.count(dni))throw std::domain_error("Estudiante ya graduado");
        if (alumno_grupo.count(dni)) return alumno_grupo.at(dni);
        throw std::domain_error("Estudiante no existente");
    }
    void promocionar(const std::string &dni) {
        if (alumnos_graduados.count(dni)) {
            throw std::domain_error("Estudiante ya graduado");
        }
        if (!alumnos.count(dni)) {
            throw std::domain_error("Estudiante no existente");
        }
        int grupo_actual = alumno_grupo[dni];
        alumnos_busquedas[grupo_actual].erase(dni);
        academia[grupo_actual].erase(alumno_pos[dni]);
        alumno_grupo[dni] += 1;

        if (alumno_grupo[dni] > 6) {
            alumnos_graduados.insert(dni);
            alumnos_graduados_ordenados.insert(dni);
            alumnos.erase(dni);
            alumno_grupo.erase(dni);
            alumno_pos.erase(dni);
        } else {
            int nuevo_grupo = alumno_grupo[dni];
            alumnos_busquedas[nuevo_grupo].insert(dni);
            auto it = academia[nuevo_grupo].insert(academia[nuevo_grupo].end(), dni);
            alumno_pos[dni] = it;
        }
    }

    list<std::string> graduados() const {
        return {alumnos_graduados_ordenados.begin(), alumnos_graduados_ordenados.end()};
    }

    std::string novato(int grupo) const {
        if (grupo > 0 && grupo <= 6) {
            if (academia.count(grupo) && !academia.at(grupo).empty()) {
                return academia.at(grupo).back();
            } else throw std::domain_error("Grupo vacio");
        } else  throw std::domain_error("Grupo incorrecto");


    }


private:
    unordered_map<int, list<string>> academia;
    unordered_set<string> alumnos;
    unordered_map<int, unordered_set<string>> alumnos_busquedas;
    unordered_set<string> alumnos_graduados;
    set<string> alumnos_graduados_ordenados;
    unordered_map<string, int> alumno_grupo;
    unordered_map<string, list<string>::iterator> alumno_pos;

};


bool tratar_caso() {
    AcademiaChino ac;
    string comando;
    cin >> comando;
    if (cin.eof()) return false;

    while (comando != "FIN") {
        try {
            if (comando == "nuevo_estudiante") {
                string dni;
                int grupo;
                cin >> dni >> grupo;
                ac.nuevo_estudiante(dni, grupo);
            } else if (comando == "grupo_estudiante") {
                string dni;
                cin >> dni;
                int grupo = ac.grupo_estudiante(dni);
                cout << dni << " esta en el grupo " << grupo << "\n";
            } else if (comando == "promocionar") {
                string dni;
                cin >> dni;
                ac.promocionar(dni);
            } else if (comando == "graduados") {
                list<string> graduados = ac.graduados();
                cout << "Lista de graduados:";
                for (const string &s: graduados) {
                    cout << " " << s;
                }
                cout << "\n";
            } else if (comando == "novato") {
                int grupo;
                cin >> grupo;
                string novato = ac.novato(grupo);
                cout << "Novato de " << grupo << ": " << novato << "\n";
            }
        } catch (std::domain_error &e) {
            cout << "ERROR: " << e.what() << "\n";
        }

        cin >> comando;
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