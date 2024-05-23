// Oficinas de empleo
// ------------------
// Estructuras de datos

// Añade los #include que creas necesarios

#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <set>


using namespace std;


class OficinaEmpleo {
public:

    void altaOficina(const string &nombre, const string &empleo) {
        if(!personaEmpleos[nombre].count(empleo)) {
            personaEmpleos[nombre].insert(empleo);
            empleosPersona[empleo].push_back(nombre);
            personaEmpleosOrdenada[nombre].insert(empleo);
        }

    }

    string ofertaEmpleo(string empleo) {
        //TODO FALLA CASO altaOficina Ivan informatica
        //altaOficina Jose informatica
        //altaOficina Ivan administracion
        //ofertaEmpleo administracion
        //ofertaEmpleo informatica
        //listadoEmpleos Ivan
        //FIN
        //TODO ahora fallan casos de prueba

        if (!empleosPersona.count(empleo)) {
            throw std::domain_error("No existen personas apuntadas a este empleo");
        }

        string devuelve = empleosPersona[empleo].back();
        if(personaEmpleos.count(devuelve)) {
            empleosPersona[empleo].pop_back();
            if (empleosPersona[empleo].empty()) empleosPersona.erase(empleo);
            personaEmpleos.erase(devuelve);
            personaEmpleosOrdenada.erase(devuelve);

            return devuelve;
        } else   throw std::domain_error("No existen personas apuntadas a este empleo");

    }

    vector<string> listadoEmpleos(string persona) {
        if(!personaEmpleos.count(persona)) throw std::domain_error ("Persona inexistente");
        return {personaEmpleosOrdenada[persona].begin(), personaEmpleosOrdenada[persona].end()};
    }

private:
    unordered_map<string, deque<string>> empleosPersona;
    unordered_map<string, set<string>> personaEmpleosOrdenada;
    unordered_map<string, set<string>> personaEmpleos;
};



bool tratar_caso() {
    OficinaEmpleo oe;
    string comando;
    cin >> comando;

    if (cin.eof()) return false;

    while (comando != "FIN") {
        try {
            if (comando == "altaOficina") {
                string nombre, empleo;
                cin >> nombre >> empleo;
                oe.altaOficina(nombre, empleo);
            } else if (comando == "ofertaEmpleo") {
                string empleo;
                cin >> empleo;
                string persona = oe.ofertaEmpleo(empleo);
                cout << empleo << ": " << persona << "\n";
            } else if (comando == "listadoEmpleos") {
                string persona;
                cin >> persona;
                vector<string> empleos = oe.listadoEmpleos(persona);
                cout << persona << ":";
                for (const string &e : empleos) {
                    cout << " " << e;
                }
                cout << "\n";
            }
        } catch (std::exception &e) {
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

