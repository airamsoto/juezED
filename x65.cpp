// Elecciones Presidenciales
// -------------------------
// Estructuras de datos

// Añade los #include que creas necesarios

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <set>
#include <map>

using namespace std;


class ConteoVotos {
public:
    void nuevo_estado(const string &nombre, int num_compromisarios) {
        if (estados.count(nombre)) throw std::domain_error("Estado ya existente");
        estados.insert({nombre, {num_compromisarios}});


    }

    void sumar_votos(const string &estado, const string &partido, int num_votos) {
        tEstado &estadoBuscado = buscar_estado(estado);
        estadoBuscado.votosPartido[partido] += num_votos;
        if (estadoBuscado.votosPartido[partido] > estadoBuscado.votosPartido[estadoBuscado.ganador]) {
            string antiguo_ganador = estadoBuscado.ganador;
            estadoBuscado.ganador = partido;
            partidos[partido] += estadoBuscado.comisarios;
            if (antiguo_ganador != "") {
                partidos[antiguo_ganador] -= estadoBuscado.comisarios;
                if (partidos[antiguo_ganador] == 0) partidos.erase(antiguo_ganador);
            }
        }
    }


    string ganador_en(const string &estado) const {
        return buscar_estado(estado).ganador;
    }


    vector<pair<string, int>> resultados() const {
        vector<pair<string, int>> result(partidos.size());
        copy(partidos.begin(), partidos.end(), result.begin());
        return result;
    }

private:
    typedef struct tEstado {
        string ganador;
        int comisarios;
        unordered_map<string, int> votosPartido;
        tEstado(int nc): comisarios(nc), votosPartido(), ganador("") { }
    };
    unordered_map<string, tEstado> estados;
    map<string, int> partidos;


    tEstado &buscar_estado(const string &nombre) {
        auto it = estados.find(nombre);
        if (it == estados.end()) {
            throw domain_error("Estado no encontrado");
        }
        return it->second;
    }


    const tEstado &buscar_estado(const string &nombre) const {
        auto it = estados.find(nombre);
        if (it == estados.end()) {
            throw domain_error("Estado no encontrado");
        }
        return it->second;
    }


};


bool tratar_caso() {
    string comando;
    cin >> comando;
    if (cin.eof()) return false;

    ConteoVotos cv;

    while (comando != "FIN") {
        try {
            if (comando == "nuevo_estado") {
                string estado;
                int num_compromisarios;
                cin >> estado >> num_compromisarios;
                cv.nuevo_estado(estado, num_compromisarios);
            } else if (comando == "sumar_votos") {
                string estado;
                string partido;
                int num_votos;
                cin >> estado >> partido >> num_votos;
                cv.sumar_votos(estado, partido, num_votos);
            } else if (comando == "ganador_en") {
                string estado;
                cin >> estado;
                string ganador = cv.ganador_en(estado);
                cout << "Ganador en " << estado << ": " << ganador << "\n";
            } else if (comando == "resultados") {
                for (const auto &[partido, num_comp]: cv.resultados()) {
                    cout << partido << " " << num_comp << "\n";
                }
            }
        } catch (std::exception &e) {
            cout << e.what() << "\n";
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
