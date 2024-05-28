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
    #include <utility>
    #include <unordered_map>
    #include <unordered_set>

    #include <list>
    #include <algorithm>

    using namespace std;

    class Restaurante {
    private:
        unordered_map<int, list<string>> mesas;
        unordered_map<int, unordered_set<string>> mesasFalta;
        unordered_map<int, unordered_multiset<string>> mesasPlatosSet;
        list<pair<int, string>> ultimosPlatosPorMesa;
        unordered_map<int, list<pair<int, string>>::iterator> ultimosPlatosIndices;

    public:
        void nueva_mesa(int num) {
            if (mesas.count(num)) throw domain_error("Mesa ocupada");
            mesas[num];
            mesasPlatosSet[num];
            mesasFalta[num];
        }

        void nuevo_pedido(int mesa, string plato) {
            if (!mesas.count(mesa)) throw domain_error("Mesa vacia");
            mesas[mesa].push_back(plato);
            mesasPlatosSet[mesa].insert(plato);
            ultimosPlatosPorMesa.push_back({mesa, plato});
            ultimosPlatosIndices[mesa] = --ultimosPlatosPorMesa.end();
            mesasFalta[mesa].insert(plato);
        }

        pair<int, string> servir() {
            if (ultimosPlatosPorMesa.empty()) throw domain_error("No hay pedidos pendientes");
            auto [mesa, plato] = ultimosPlatosPorMesa.front();
            ultimosPlatosPorMesa.pop_front();

            ultimosPlatosIndices.erase(mesa);

            auto& lista = mesas[mesa];
            auto it = find(lista.begin(), lista.end(), plato);
            if (it != lista.end()) lista.erase(it);
            if (mesasPlatosSet[mesa].count(plato)) {
                auto platoIt = mesasPlatosSet[mesa].find(plato);
                mesasPlatosSet[mesa].erase(platoIt);
            }

            if (!mesasPlatosSet[mesa].count(plato)) {
                mesasFalta[mesa].erase(plato);
            }
            return {mesa, plato};
        }

        vector<string> que_falta(int mesa) const {
            if (!mesas.count(mesa)) throw domain_error("Mesa vacia");
            return {mesasFalta.at(mesa).begin(), mesasFalta.at(mesa).end()};
        }

        void cancelar_pedido(int mesa, const string &plato) {
            if (!mesas.count(mesa)) throw domain_error("Mesa vacia");
            if (!mesasPlatosSet[mesa].count(plato)) throw domain_error("Producto no pedido por la mesa");

            if (ultimosPlatosIndices.count(mesa) && ultimosPlatosIndices[mesa]->second == plato) {
                auto it = ultimosPlatosIndices[mesa];
                ultimosPlatosPorMesa.erase(it); //TODO EL PROBLEMA ES QUE NO REGISTRA VARIOS PLATOS IGUALES PARA LA MISMA MESA
                ultimosPlatosIndices.erase(mesa);

            }

            auto platoIt = mesasPlatosSet[mesa].find(plato);
            mesasPlatosSet[mesa].erase(platoIt);
            if (!mesasPlatosSet[mesa].count(plato)) {
                mesasFalta[mesa].erase(plato);
            }

            auto &lista = mesas[mesa];
            auto listIt = find(lista.begin(), lista.end(), plato);
            if (listIt != lista.end()) lista.erase(listIt);
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
                    for (const string &p : platos) {
                        cout << "  " << p << "\n";
                    }
                }
            } catch (exception &e) {
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

        while(tratar_caso()) { }

    #ifndef DOMJUDGE
        std::cin.rdbuf(cinbuf);
    #endif

        return 0;
    }
    /*
     * bravas 1
    gazpacho 7
    En la mesa 7 falta:
    croquetas
    En la mesa 1 falta:
    En la mesa 7 falta:
    croquetas
    ensalada
    En la mesa 7 falta:
    croquetas
    ensalada
    En la mesa 7 falta:
    ensalada
    ensalada 7
    ERROR: No hay pedidos pendientes
    ---
    ERROR: Mesa ocupada
    ERROR: Mesa vacia
    ERROR: Producto no pedido por la mesa
    croquetas 1
    ERROR: No hay pedidos pendientes
    ERROR: Producto no pedido por la mesa
    ---

     */