#include <iostream>
#include <fstream>
#include <list>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <stdexcept>

using namespace std;

class Supermercado {
public:
    Supermercado(int num_cajas) {
        this->num_cajas = num_cajas;
    }

    void nuevo_cliente(const string &dni, int num_cola) {
        if (num_cola >= num_cajas) throw domain_error("Cola inexistente");
        if (clientesSistema.count(dni)) throw domain_error("Cliente duplicado");
        cajasCola[num_cola].push_front(dni);
        auto it = cajasCola[num_cola].begin();
        clientesSistema[dni] = it;
        clientesCola[dni] = num_cola;
    }

    void cambiar_cola(const string &dni, int num_cola) {
        if (num_cola >= num_cajas) throw domain_error("Cola inexistente");
        if (!clientesSistema.count(dni)) throw domain_error("Cliente inexistente");
        if(clientesCola.at(dni) == num_cola) return;
        int cola_actual = clientesCola[dni];
        auto it = clientesSistema[dni];
        cajasCola[cola_actual].erase(it);
        cajasCola[num_cola].push_front(dni);
        clientesSistema[dni] =  cajasCola[num_cola].begin();
        clientesCola[dni] = num_cola;
    }

    int consultar_cliente(const string &dni) const {
        if (!clientesSistema.count(dni)) throw domain_error("Cliente inexistente");
        return clientesCola.at(dni);
    }

    int cuantos_en_cola(int num_cola) const {
        if (num_cola >= num_cajas) throw domain_error("Cola inexistente");
        if(!cajasCola.count(num_cola)) return 0;
        return cajasCola.at(num_cola).size();
    }

    vector<string> clientes_en_cola(int num_cola) const {
        vector<string> vacio;
        if (num_cola >= num_cajas) throw domain_error("Cola inexistente");
        if (cajasCola.count(num_cola) == 0) return vacio;
        return {cajasCola.at(num_cola).begin(), cajasCola.at(num_cola).end()};
    }

private:
    int num_cajas;
    unordered_map<string, list<string>::iterator> clientesSistema;
    unordered_map<int, list<string>> cajasCola;
    unordered_map<string, int> clientesCola;

};

bool tratar_caso() {
    int num_colas;
    cin >> num_colas;

    if (cin.eof()) return false;

    Supermercado sup(num_colas);

    string comando;
    cin >> comando;
    while (comando != "FIN") {
        try {
            if (comando == "nuevo_cliente") {
                string dni; cin >> dni;
                int num_cola; cin >> num_cola;
                sup.nuevo_cliente(dni, num_cola);
            } else if (comando == "cambiar_cola") {
                string dni; cin >> dni;
                int num_cola; cin >> num_cola;
                sup.cambiar_cola(dni, num_cola);
            } else if (comando == "consultar_cliente") {
                string dni; cin >> dni;
                int p = sup.consultar_cliente(dni);
                cout << "El cliente " << dni << " esta en la cola " << p << "\n";
            } else if (comando == "cuantos_en_cola") {
                int num_cola; cin >> num_cola;
                int result = sup.cuantos_en_cola(num_cola);
                cout << "En la cola " << num_cola << " hay " << result << " clientes\n";
            } else if (comando == "clientes_en_cola") {
                int num_cola; cin >> num_cola;
                vector<string> lista = sup.clientes_en_cola(num_cola);
                cout << "En la cola " << num_cola << " estan:";
                for (const string &s: lista) {
                    cout << " " << s;
                }
                cout << "\n";
            }
        } catch (exception &e) {
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
