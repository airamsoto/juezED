// Misterios de Pekín
// ------------------
// Estructuras de datos

// Añade los #include que creas necesarios

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <fstream>


using namespace std;


class MisteriosDePekin {

public:
    MisteriosDePekin(const string &culpable) {
        this->culpable = culpable;
        culpables[culpable] = unordered_set<string>();
    }

    void anyadir_rasgo(const string &sospechoso, const string &rasgo) {
        if(jugadores.empty()) {
            culpables[sospechoso].insert(rasgo);

        } else throw std::domain_error ("Juego ya empezado");


    }

    vector<string> sospechosos() const {
        vector <string> sos;
        for (const auto &pair : culpables) {
            sos.push_back(pair.first);
        }

        return {sos};
    }

    void nuevo_jugador(const string &nombre) {
        if(jugadores.count(nombre)) throw std::domain_error("Jugador existente");
        for (const auto &pair : culpables) jugadores[nombre].insert(pair.first);

    }

    void jugador_descarta(const string &jugador, const string &rasgo) {
        if(!jugadores.count(jugador)) throw std::domain_error("Jugador no existente");
        for (const auto &pair : culpables) {
            if(pair.second.count(rasgo)) {
                if (jugadores[jugador].count(pair.first)) {
                    jugadores[jugador].erase(pair.first);
                }
            }

        }


    }

    bool jugador_enganyado(const string &jugador) const {
        if(jugadores.count(jugador)){
            if(jugadores.at(jugador).count(culpable) == 0) return true;
            return false;
        } throw std::domain_error("Jugador no existente");


    }

    bool puede_detener_culpable(const string &jugador) const {
        if(jugadores.count(jugador)) {
               if (jugadores.at(jugador).size() == 1) {
                   if(jugadores.at(jugador).count(culpable)) return true;

               } else return false;
        } else throw std::domain_error ("Jugador no existente");

    }


private:
    string culpable;
    //nombre sospechoso y rasgos
    map<string, unordered_set<string>> culpables;
    //nombre jugador y lista sospechosos

    unordered_map<string, unordered_set<string>> jugadores;


    vector<pair<string, bool>> pistas;
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
                for (const string &s : mp.sospechosos()) {
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
                string nombre; string rasgo;
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
            }
        } catch (exception &e) {
            cout << "ERROR: " << e.what() << endl;
        }

        cin >> comando;
    }

    cout << "---" << endl;

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

