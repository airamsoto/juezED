//
// Created by airam on 23/05/2024.
//
/*
 * add song cancion artista duracion si existe una cancion con el mismo nombre dara error
 * addToPlaylist añade la cancion al final de la lista de reproduccion si la cancion ya estaba no hace nada y si no esta en el ipud da error
 * current devuelve la primera cancion de la lista de repoduccion, da error si la lista es vacia
 * play la primera cancion de la lista de reproduccion se elimina de la lista y se registra como reproducida, si la lista es vacia NO TIENE EFECTO
 * totalTime devuelve la ssuma de las duraciones de canciones de la lista si es vacia devuelve 0
 * recent devuelve la lista de las ultima reproducidas (n) de mas reciente a antigua, si n > listareproducidas -> envia toda la lista si una cancion se ha reproducido mas de una vez solo figura 1
 * deletesong elimina all the rastro de la cancion en el ipud, si la cancion no existe no hace nada
 */

// iPud
// ----
// Estructuras de datos

// Añade los #include que creas necesarios

#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>

using namespace std;

//TODO FALLA EN EL RECENT QUE CUADNO PONES UNA NO DEVUELVE LA ULTIMA
class iPud {
public:
    iPud() {}

    void addSong(const string &name, const string &artist, int duration) {

        if (cancionesDuracion.count(name)) throw std::domain_error("Error");
        cancionesDuracion[name] = duration;
    }

    void addToPlaylist(const string &name) {
        if (!cancionesDuracion.count(name)) throw std::domain_error("Error");
        if (!playListSet.count(name)) {
            playList.push_back(name);
            playListSet.insert(name);

            duracion += cancionesDuracion[name];
            playlistIterators[name] = --playList.end();

        }
    }

    string current() const {
        if (playListSet.empty()) throw std::domain_error("Error");
        return playList.front();
    }

    void play() {
        if (!playList.empty()) {
            duracion -= cancionesDuracion[playList.front()];
            playListSet.erase(playList.front());
            playlistIterators[playList.front()] = --playList.end();
            if(reproducidasSet.count(playList.front())) {
                auto it = reproducidastIterator[playList.front()];
                reproducidastIterator.erase(playList.front());
                reproducidasSet.erase(playList.front());
                reproducidas.erase(it);

            }
            reproducidas.push_front(playList.front());
            reproducidastIterator[playList.front()] = reproducidas.begin();
            reproducidasSet.insert(playList.front());

            playList.pop_front();
        }
    }

    int totalTime() const {
        return duracion;
    }

    list<string> recent(int n) const {
        if (n > reproducidas.size()) {
            n = reproducidas.size();
        }
        auto it = reproducidas.begin();
        advance(it, n);
        return list<string>(reproducidas.begin(), it);
    }

    void deleteSong(const string &song) {
        if (cancionesDuracion.count(song)) {
            if(reproducidasSet.count(song)) {
                auto it = reproducidastIterator[song];
                reproducidastIterator.erase(song);
                reproducidasSet.erase(song);
                reproducidas.erase(it);
            }
            if (playListSet.count(song)) duracion -= cancionesDuracion[song];
            cancionesDuracion.erase(song);
            playlistIterators.erase(song);
            playListSet.erase(song);



        }

    }


private:
    unordered_map<string, int> cancionesDuracion;
    list<string> playList;
    unordered_set<string> playListSet;
    list<string> reproducidas;
    unordered_set<string> reproducidasSet;
    int duracion = 0;
    unordered_map<string, list<string>::iterator> playlistIterators;
    unordered_map<string, list<string>::iterator>  reproducidastIterator;

};


bool tratar_caso() {
    string comando;
    cin >> comando;
    if (cin.eof()) {
        return false;
    }

    iPud ipud;

    while (comando != "FIN") {
        try {
            if (comando == "addSong") {
                string nombre, artista;
                int duracion;
                cin >> nombre >> artista >> duracion;
                ipud.addSong(nombre, artista, duracion);
            } else if (comando == "addToPlaylist") {
                string nombre;
                cin >> nombre;
                ipud.addToPlaylist(nombre);
            } else if (comando == "current") {
                ipud.current();
            } else if (comando == "play") {
                try {
                    string cancion = ipud.current();
                    ipud.play();
                    cout << "Sonando " << cancion << "\n";
                } catch (exception &e) {
                    cout << "No hay canciones en la lista\n";
                }
            } else if (comando == "totalTime") {
                int tiempo = ipud.totalTime();
                cout << "Tiempo total " << tiempo << "\n";
            } else if (comando == "recent") {
                int n;
                cin >> n;
                list<string> canciones = ipud.recent(n);
                if (!canciones.empty()) {
                    cout << "Las " << canciones.size() << " mas recientes\n";
                    for (const string &s: canciones) {
                        cout << "    " << s << "\n";
                    }
                } else {
                    cout << "No hay canciones recientes\n";
                }
            } else if (comando == "deleteSong") {
                string nombre;
                cin >> nombre;
                ipud.deleteSong(nombre);
            }
        } catch (exception &e) {
            cout << "ERROR " << comando << "\n";
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
