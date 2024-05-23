
Se ha añadido el archivo adjunto x71.cpp.Ninguno seleccionado

Ir al contenido
        Uso de Gmail con lectores de pantalla
Se ha marcado la conversación como spam.
Más información  Deshacer
        Conversaciones
Instagram
2
New login on Instagram from Safari on Mac OS X
- We've noticed a new login, airamsoto_ We've noticed a login from a device that you don't usually use. Mac OS X · Safari · Madrid, Spain April 22 at 1:48 PM (PDT) If this was you, you won

22 abr
        Colegio Mayor Nuest.
SOLICITUD DE REINGRESO COLEGIO MAYOR GUADALUPE 2024-2025
Archivo adjunto:
REGLAMENTO_RÉGIMEN_INTERNO_GUADALUPE_2022-2023.pdf
22 abr
5,93 GB ocupados de 15 GB
        Términos · Privacidad · Política del programa
        Última actividad de la cuenta: hace 54 minutos
        Detalles
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
        if (!personaEmpleos[nombre].count(empleo)) {
            personaEmpleos[nombre].insert(empleo);
            empleosPersona[empleo].push_back(nombre);



            empleoIterators[empleo][nombre] = --empleosPersona[empleo].end(); //todo revisar ejercicio 70 para ver si lo hice iugal




            personaEmpleosOrdenada[nombre].insert(empleo);
        }
    }

    string ofertaEmpleo(const string &empleo) {
        if (!empleosPersona.count(empleo)) {
            throw domain_error("No existen personas apuntadas a este empleo");
        }

        string persona = empleosPersona[empleo].front();
        empleosPersona[empleo].pop_front();


        empleoIterators[empleo].erase(persona);



        if (empleosPersona[empleo].empty()) {
            empleosPersona.erase(empleo);
            empleoIterators.erase(empleo);
        }

        for (const auto &e : personaEmpleos[persona]) {
            auto it = empleoIterators[e].find(persona);
            if (it != empleoIterators[e].end()) {
                empleosPersona[e].erase(it->second);
                empleoIterators[e].erase(it);
                if (empleosPersona[e].empty()) {
                    empleosPersona.erase(e);
                    empleoIterators.erase(e);
                }
            }
        }

        personaEmpleos.erase(persona);
        personaEmpleosOrdenada.erase(persona);

        return persona;
    }

    vector<string> listadoEmpleos(const string &persona) const {
        if (!personaEmpleos.count(persona)) {
            throw domain_error("Persona inexistente");
        }
        return {personaEmpleosOrdenada.at(persona).begin(), personaEmpleosOrdenada.at(persona).end()};
    }

private:
    unordered_map<string, list<string>> empleosPersona;
    unordered_map<string, unordered_map<string, list<string>::iterator>> empleoIterators;
    unordered_map<string, set<string>> personaEmpleosOrdenada;
    unordered_map<string, unordered_set<string>> personaEmpleos;
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

x71.cpp
        Mostrando x71.cpp.