

#include <iostream>
#include <iomanip>
#include <fstream>
#include<unordered_map>
#include <list>
#include <exception>
#include <unordered_set>
#include <vector>
#include <stdexcept>

class TAD {
public:

    TAD(): duracion_total(0){}

    void addSong(std::string S, std::string A, int D) {
        if (mapa_canciones.count(S) == 0) {
            InfoCancion ic = { S,A,D,{},{},false,false};
            mapa_canciones.insert({S,ic});
        }
        else {
            throw std::runtime_error("addSong");
        }
    }

    void addToPlaylist(std::string S) {
        if (mapa_canciones.count(S)>0 ) {
            if(cjto_lr.count(S) == 0)
            {
                cjto_lr.insert(S);
                auto it = lr.insert(lr.end(), S);
                mapa_canciones.at(S).it_lr = it;
                mapa_canciones.at(S).en_lr = true;
                duracion_total += mapa_canciones.at(S).duracion;
            }
        }
        else {
            throw std::runtime_error("addToPlaylist");
        }
    }

    std::string current() {
        if (!lr.empty()) {
            return lr.front();
        }
        else {
            throw std::runtime_error("current");
        }
    }

    std::string play() {
        std::string actu = "";
        if (!lr.empty()) {
            actu = lr.front();
            if (cjto_reproducidas.count(actu) == 0) {
                auto it_rep = reproducidas.insert(reproducidas.begin(), actu);
                mapa_canciones.at(actu).it_reproducidas = it_rep;
                mapa_canciones.at(actu).en_reproducidas = true;
                cjto_reproducidas.insert(actu);
            }
            else {
                auto it_eliminar = mapa_canciones.at(actu).it_reproducidas;
                reproducidas.erase(it_eliminar);
                auto it_insertar = reproducidas.insert(reproducidas.begin(), actu);
                mapa_canciones.at(actu).it_reproducidas = it_insertar;
            }
            duracion_total -= mapa_canciones.at(actu).duracion;
            mapa_canciones.at(actu).en_lr = false;
            lr.erase(lr.begin());
            cjto_lr.erase(actu);
        }
        return actu;
    }

    int totalTime() {
        return duracion_total;
    }

    std::vector<std::string> recent(int N) {
        std::vector<std::string> dev;

        auto iterar = reproducidas.begin();

        while (iterar!=reproducidas.end() && (int)dev.size() < N) {
            std::string aux = *iterar;
            dev.push_back(aux);
            iterar++;
        }

        return dev;
    }

    void deleteSong(std::string S) {
        if (mapa_canciones.count(S) > 0) {
            if (mapa_canciones.at(S).en_lr) {
                auto it_lr_ = mapa_canciones.at(S).it_lr;
                lr.erase(it_lr_);
                cjto_lr.erase(S);
                duracion_total -= mapa_canciones.at(S).duracion;
            }

            if (mapa_canciones.at(S).en_reproducidas) {
                auto it_repr= mapa_canciones.at(S).it_reproducidas;
                reproducidas.erase(it_repr);
                cjto_reproducidas.erase(S);
            }
            mapa_canciones.erase(S);
        }

    }


private:

    struct InfoCancion {
        std::string titulo;
        std::string artista;
        int duracion;
        std::list<std::string>::iterator it_lr;
        std::list<std::string>::iterator it_reproducidas;
        bool en_lr;
        bool en_reproducidas;
    };

    std::unordered_map<std::string, InfoCancion> mapa_canciones;
    std::list<std::string> lr;
    std::unordered_set<std::string> cjto_lr;
    std::list<std::string> reproducidas;
    std::unordered_set<std::string> cjto_reproducidas;
    int duracion_total;

};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    std::string opp;
    std::cin >> opp;
    if (!std::cin)
        return false;

    TAD tad;

    while (opp != "FIN") {
        try {
            if (opp == "addSong") {
                std::string nombre, autor;
                int duracion;
                std::cin >> nombre >> autor >> duracion;
                tad.addSong(nombre, autor, duracion);
            }
            else if (opp == "addToPlaylist") {
                std::string cancion;
                std::cin >> cancion;
                tad.addToPlaylist(cancion);
            }
            else if (opp == "current") {
                tad.current();
            }
            else if (opp == "play") {
                std::string reproducida = tad.play();
                if (reproducida != "") {
                    std::cout << "Sonando " << reproducida;
                }
                else {
                    std::cout << "No hay canciones en la lista";
                }
                std::cout << '\n';
            }
            else if (opp == "totalTime") {
                int duracion_total = tad.totalTime();
                std::cout << "Tiempo total " << duracion_total << '\n';
            }
            else if (opp == "recent") {
                int N;
                std::cin >> N;
                std::vector<std::string>res = tad.recent(N);
                if (res.size() > 0) {
                    std::cout << "Las " << res.size() << " mas recientes\n";
                    for (int i = 0; i < (int)res.size(); i++) {
                        std::cout <<"    "<< res[i] << '\n';
                    }
                }
                else {
                    std::cout << "No hay canciones recientes\n";
                }

            }
            else if (opp == "deleteSong") {
                std::string cancion;
                std::cin >> cancion;
                tad.deleteSong(cancion);
            }


        }
        catch (std::exception& e) {
            std::cout << "ERROR " << e.what()<<'\n';
        }

        std::cin >> opp;
    }

    std::cout << "---\n";

    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif


    while (resuelveCaso());


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}