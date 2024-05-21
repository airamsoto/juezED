#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <stdexcept>
#include <algorithm>

using namespace std;

class MisteriosDePekin {
public:
    MisteriosDePekin(const string &culpable) {
        this->culpable = culpable;
        sospechosos_ordenados.insert(culpable);
    }

    void anyadir_rasgo(const string &sospechoso, const string &rasgo) {
        if (jugadores.empty()) {
            culpables[sospechoso] = {rasgo};
            rasgos_sospechosos[rasgo].insert(sospechoso);
            sospechosos_ordenados.insert(sospechoso);
        } else {
            throw domain_error("Juego ya empezado");
        }
    }

    vector<string> sospechosos() const {

        return vector<string>(sospechosos_ordenados.begin(), sospechosos_ordenados.end());
    }

    void nuevo_jugador(const string &nombre) {
        if (jugadores.count(nombre)) {
            throw domain_error("Jugador existente");
        }
        jugadores[nombre];
        if (sospechosos_ordenados.size() < 2) {
            ganadoresPotenciales.push_back(nombre);
            mapa_potenciales[nombre] = --ganadoresPotenciales.end();
        }

    }

    void jugador_descarta(const string &jugador, const string &rasgo) {
        if (!jugadores.count(jugador)) {
            throw domain_error("Jugador no existente");
        }

        if (rasgos_sospechosos.count(rasgo)) {
            for (const auto &sospechoso: rasgos_sospechosos[rasgo]) {
                jugadores[jugador].insert(sospechoso);
            }
            bool puede = (sospechosos_ordenados.size()  == jugadores[jugador].size() + 1) &&
                         jugadores[jugador].count(culpable) == 0;
            bool noPuede = (sospechosos_ordenados.size() != jugadores[jugador].size() + 1) &&
                           jugadores[jugador].count(culpable) == 1;;

            if (puede && mapa_potenciales.find(jugador) == mapa_potenciales.end()) {
                ganadoresPotenciales.push_back(jugador);
                mapa_potenciales[jugador] = --ganadoresPotenciales.end();
            } else if (noPuede && mapa_potenciales.find(jugador) != mapa_potenciales.end()) {
                ganadoresPotenciales.erase(mapa_potenciales[jugador]);
                mapa_potenciales.erase(jugador);
            }
        }
    }

    bool jugador_enganyado(const string &jugador) const {
        if (jugadores.count(jugador)) {
            return jugadores.at(jugador).count(culpable) == 1;
        }
        throw domain_error("Jugador no existente");
    }

    bool puede_detener_culpable(const string &jugador) const {
        if (jugadores.count(jugador)) {
            return jugadores.at(jugador).size() == sospechosos_ordenados.size() - 1 &&
                   !jugadores.at(jugador).count(culpable);
        }
        throw domain_error("Jugador no existente");
    }

    vector<string> ganadores_potenciales() const {
        return vector<string>(ganadoresPotenciales.begin(), ganadoresPotenciales.end());

    }

    void imprime_lista(const vector<string> &lista) {
        bool primero = true;
        for (const auto &s: lista) {
            cout << (primero ? "" : " ") << s;
            primero = false;
        }
    }

private:
    string culpable;
    unordered_map<string, unordered_set<string>> culpables;
    unordered_map<string, unordered_set<string>> jugadores;
    unordered_map<string, unordered_set<string>> rasgos_sospechosos;
    set<string> sospechosos_ordenados;
    list<string> ganadoresPotenciales;
    unordered_map<string, list<string>::iterator> mapa_potenciales;
};

bool tratar_caso() {
    string culpable;
    cin >> culpable;

    if (cin.eof()) return false;

    MisteriosDePekin mp(culpable);
    cout << "OK" << endl;

    string comando;
    cin >> comando;

    while (comando != "FIN") {
        try {
            if (comando == "anyadir_rasgo") {
                string sospechoso, rasgo;
                cin >> sospechoso >> rasgo;
                mp.anyadir_rasgo(sospechoso, rasgo);
                cout << "OK" << endl;
            } else if (comando == "sospechosos") {
                bool primero = true;
                for (const string &s: mp.sospechosos()) {
                    cout << (primero ? "" : " ") << s;
                    primero = false;
                }
                cout << endl;
            } else if (comando == "nuevo_jugador") {
                string nombre;
                cin >> nombre;
                mp.nuevo_jugador(nombre);
                cout << "OK" << endl;
            } else if (comando == "jugador_descarta") {
                string nombre, rasgo;
                cin >> nombre >> rasgo;
                mp.jugador_descarta(nombre, rasgo);
                cout << "OK" << endl;
            } else if (comando == "jugador_enganyado") {
                string nombre;
                cin >> nombre;
                bool enganyado = mp.jugador_enganyado(nombre);
                cout << nombre << (enganyado ? "" : " no") << " ha sido enganyado" << endl;
            } else if (comando == "puede_detener_culpable") {
                string nombre;
                cin >> nombre;
                bool puede = mp.puede_detener_culpable(nombre);
                cout << nombre << (puede ? "" : " no") << " puede detener al culpable" << endl;
            } else if (comando == "ganadores_potenciales") {
                mp.imprime_lista(mp.ganadores_potenciales());
                cout << endl;
            }
        } catch (const exception &e) {
            cout << "ERROR: " << e.what() << endl;
        }

        cin >> comando;
    }

    cout << "---" << endl;

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
