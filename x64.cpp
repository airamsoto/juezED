// Misterios de Pekín
// ------------------
// Estructuras de datos

// Añade los #include que creas necesarios

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <list>


using namespace std;


class MisteriosDePekin {
public:
    MisteriosDePekin(const string &culpable) {
        this->culpable = culpable;
        cjt_sospechososOrdenados.insert(culpable);


    }

    void anyadir_rasgo(const string &sospechoso, const string &rasgo) {
       if(!mapa_jugadores.empty()) throw domain_error ("Juego ya empezado");
       rasgosSospechosos[rasgo].insert(sospechoso);
       cjt_sospechososOrdenados.insert(sospechoso);

    }

    vector<string> sospechosos() const {

        return vector<string>{cjt_sospechososOrdenados.begin(), cjt_sospechososOrdenados.end()};
    }

    void nuevo_jugador(const string &nombre) {
        if(mapa_jugadores.count(nombre)) throw domain_error ("Jugador existente");
        mapa_jugadores[nombre];
        if(puede_detener_culpable(nombre)) {
            auto it = lista_jugadores_potenciales.insert(lista_jugadores_potenciales.end(), nombre);
            mapa_potenciales[nombre] = it;
        }

    }

    void jugador_descarta(const string &jugador, const string &rasgo) {
        if(!mapa_jugadores.count(jugador)) throw domain_error ("Jugador no existente");
        if(rasgosSospechosos.count(rasgo)) {
            for (const auto& sospech :rasgosSospechosos[rasgo]) {
                mapa_jugadores[jugador].insert(sospech);

            }
        }
        if(mapa_potenciales.count(jugador) && !puede_detener_culpable(jugador)) {
            lista_jugadores_potenciales.erase(mapa_potenciales.at(jugador));
            mapa_potenciales.erase(jugador);

        }
        if(!mapa_potenciales.count(jugador) && puede_detener_culpable(jugador)) {
            auto it = lista_jugadores_potenciales.insert(lista_jugadores_potenciales.end(), jugador);
            mapa_potenciales[jugador] = it;
        }

    }

    bool jugador_enganyado(const string &jugador) const {
        if(!mapa_jugadores.count(jugador)) throw domain_error ("Jugador no existente");
        return (mapa_jugadores.at(jugador).count(culpable));
    }

    bool puede_detener_culpable(const string &jugador) const {
        if(!mapa_jugadores.count(jugador)) throw domain_error ("Jugador no existente");
        const auto &infoJugador = mapa_jugadores.at(jugador);
        return infoJugador.size() - cjt_sospechososOrdenados.size() == -1 && !infoJugador.count(culpable);
    }
    vector<string> ganadores_potenciales() const {

        return {lista_jugadores_potenciales.begin(), lista_jugadores_potenciales.end()};

    }


private:
    using jugador = string;
    using sospechoso = string;
    using rasgos = string;
    string culpable;
    unordered_map<jugador, unordered_set<sospechoso>> mapa_jugadores;
    unordered_map<rasgos, unordered_set<sospechoso>> rasgosSospechosos;
    set<sospechoso> cjt_sospechososOrdenados;


    unordered_map<jugador, list<jugador>::iterator> mapa_potenciales;
    list<jugador> lista_jugadores_potenciales;

};
void imprime_lista(const vector<string> &lista) {
    bool primero = true;
    for (const auto &s : lista) {
        cout << (primero ? "" : " ") << s;
        primero = false;
    }
}
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
                imprime_lista(mp.ganadores_potenciales());
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