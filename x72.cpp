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


using namespace std;


class iPud {
public:
    iPud() { }

    void addSong(const string &name, const string &artist, int duration) {

    }

    void addToPlaylist(const string &name) {

    }

    string current() const {
        return "";
    }

    void play() {

    }

    int totalTime() const {
        return -1;
    }

    list<string> recent(int n) const {
        return {};
    }

    void deleteSong(const string &song) {

    }


private:
 /*
  * reproducidas ordenadas y  no ordenadas para busquedas por ejemplo para ver si ya se ha añadido las no ordenadas puede
  *  unorder set de canciones generales para el ipud
  *  uroder map de canciion mas int de la duracion de la cancion
  *
  *
  */
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
            if (comando == "addSong")  {
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
