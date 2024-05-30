
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
        if (!personaEmpleo[nombre].count(empleo)) {
            auto it = empleosPersona[empleo].insert(empleosPersona[empleo].end(), nombre);
            empleoIterators[empleo][nombre] = it;
            personaEmpleo[nombre].insert(empleo);
            personaEmpleoOrdenada[nombre].insert(empleo);

        }
    }
    string ofertaEmpleo(const string &empleo) {
        if(!empleosPersona.count(empleo)) throw domain_error ("No existen personas apuntadas a este empleo");
        auto persona = empleosPersona[empleo].front();


        for (const auto &empleosDePersona : personaEmpleo[persona]) {
            auto it = empleoIterators[empleosDePersona].at(persona);
            empleosPersona[empleosDePersona].erase(it);
            empleoIterators[empleosDePersona].erase(persona);
            if(empleosPersona[empleosDePersona].empty()) {
                empleoIterators.erase(empleosDePersona);
                empleosPersona.erase(empleosDePersona);
            }
        }
        personaEmpleo.erase(persona);
        personaEmpleoOrdenada.erase(persona);
        return persona;
    }

    vector<string> listadoEmpleos(const string &persona) const {
        if(personaEmpleo.count(persona)) {
            return {personaEmpleoOrdenada.at(persona).begin(), personaEmpleoOrdenada.at(persona).end()};
        } else throw domain_error ("Persona inexistente");

    }

private:
    using persona = string;
    using empleo = string;

    unordered_map<empleo, list<persona>> empleosPersona;
    unordered_map<empleo, unordered_map<persona, list<persona>::iterator>> empleoIterators;
    unordered_map<persona, unordered_set<empleo>> personaEmpleo;
    unordered_map<persona, set<empleo>> personaEmpleoOrdenada;



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
