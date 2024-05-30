/*
 * ---------------------------------------------------------------
 *                 ESTRUCTURAS DE DATOS - EXAMEN FINAL
 *                   CONVOCATORIA EXTRAORDINARIA
 * ---------------------------------------------------------------
 *                            Ejercicio 3
 * ---------------------------------------------------------------
 */


// Nombre y apellidos: ________________________________________

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <list>
#include <utility>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <algorithm>
// Añade los #include que necesites

using namespace std;

/*
 * Implementación del TAD Restaurante
 */

using plato = string;
class Restaurante {
private:
    // Coloca aquí los atributos y métodos privados de la clase.
    struct tMesa {
        int mesa;
        unordered_map<plato, list<list<plato>::iterator>> listaPlatosIterator;
        unordered_map<plato, list<list<pair<int, plato>>::iterator>> listaPlatosGeneralIterator;
        unordered_set<plato> setPlatos;
    };
    unordered_map<int, tMesa> mapa_mesas;
    unordered_map<int, list<plato>> lista_platos;
    list<pair<int, plato>> lista_general;

public:
    // ¡No olvides el coste de las operaciones!

    void nueva_mesa(int num) {
        if (mapa_mesas.count(num)) throw domain_error("Mesa ocupada");
        mapa_mesas[num].mesa = num;
    }

    void nuevo_pedido(int mesa, string plato) {
        if (!mapa_mesas.count(mesa)) throw domain_error("Mesa vacia");
        auto it = lista_platos[mesa].insert(lista_platos.at(mesa).end(), plato);

        auto& listaPlatosEnMesa = mapa_mesas[mesa].listaPlatosIterator[plato];
        listaPlatosEnMesa.insert(listaPlatosEnMesa.end(), it);

        auto platoGeneralIt = lista_general.insert(lista_general.end(), { mesa ,plato });
        auto& listPlatosGeneral = mapa_mesas.at(mesa).listaPlatosGeneralIterator[plato];
        listPlatosGeneral.insert(listPlatosGeneral.end(), platoGeneralIt);
        mapa_mesas[mesa].setPlatos.insert(plato);
    }

    pair<int, string> servir() {
        auto it = lista_general.begin();
        if (it != lista_general.end()) {
            auto& listaPlatosGeneralEnPlato = mapa_mesas[it->first].listaPlatosGeneralIterator[it->second];
            listaPlatosGeneralEnPlato.erase(listaPlatosGeneralEnPlato.begin());

            auto& listaPlatos = mapa_mesas[it->first].listaPlatosIterator[it->second];
            lista_platos[it->first].erase(*listaPlatos.begin());
            listaPlatos.erase(listaPlatos.begin());

            if (listaPlatos.empty()) {
                mapa_mesas[it->first].setPlatos.erase(it->second);
            }

            pair<int, string> resultado = *it;
            lista_general.erase(it);
            return resultado;
        } else {
            throw domain_error("No hay pedidos pendientes");
        }
    }

    vector<string> que_falta(int mesa) const {
        if (!mapa_mesas.count(mesa)) throw domain_error("Mesa vacia");

        const auto& setPlatos = mapa_mesas.at(mesa).setPlatos;
        vector<string> platos_faltan(setPlatos.begin(), setPlatos.end());
        sort(platos_faltan.begin(), platos_faltan.end());
        return platos_faltan;
    }

    void cancelar_pedido(int mesa, const string& plato) {
        if (!mapa_mesas.count(mesa)) throw domain_error("Mesa vacia");
        auto& listaPlatosEnMesa = mapa_mesas[mesa].listaPlatosIterator[plato];
        if (listaPlatosEnMesa.empty()) throw domain_error("Producto no pedido por la mesa");

        auto itPrimerPlato = --listaPlatosEnMesa.end();
        lista_platos[mesa].erase(*itPrimerPlato);
        listaPlatosEnMesa.erase(itPrimerPlato);

        auto& listaPlatosGeneral = mapa_mesas[mesa].listaPlatosGeneralIterator[plato];
        auto itPrimerPlatoGeneral = --listaPlatosGeneral.end();
        lista_general.erase(*itPrimerPlatoGeneral);
        listaPlatosGeneral.erase(itPrimerPlatoGeneral);

        if (listaPlatosEnMesa.empty()) {
            mapa_mesas[mesa].setPlatos.erase(plato);
        }
    }
};


//---------------------------------------------------------------
// No modificar nada por debajo de esta línea
// -------------------------------------------------------------


// Función que trata un caso de prueba.
bool tratar_caso() {
    Restaurante r;

    string operacion;
    cin >> operacion;

    if (cin.eof()) return false;

    while (operacion != "FIN") {
        try {
            if (operacion == "nueva_mesa") {
                int n; cin >> n;
                r.nueva_mesa(n);
            } else if (operacion == "nuevo_pedido") {
                int n; cin >> n;
                string p; cin >> p;
                r.nuevo_pedido(n, p);
            } else if (operacion == "cancelar_pedido") {
                int n; cin >> n;
                string p; cin >> p;
                r.cancelar_pedido(n, p);
            } else if (operacion == "servir") {
                pair<int, string> par = r.servir();
                cout << par.second << " " << par.first << "\n";
            } else if (operacion == "que_falta") {
                int n; cin >> n;
                vector<string> platos = r.que_falta(n);
                cout << "En la mesa " << n << " falta:\n";
                for (const string& p : platos) {
                    cout << "  " << p << "\n";
                }
            }
        } catch (exception& e) {
            cout << "ERROR: " << e.what() << "\n";
        }

        cin >> operacion;
    }

    cout << "---\n";

    return true;
} // tratar_caso

int main() {
#ifndef DOMJUDGE
    std::ifstream in("sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (tratar_caso()) { }

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif

    return 0;
}
