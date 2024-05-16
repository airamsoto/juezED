/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
  * MUY IMPORTANTE: Para realizar este ejercicio solo podéis
  * modificar el código contenido entre las etiquetas <answer>
  * y </answer>. Toda modificación fuera de esas etiquetas está
  * prohibida, pues no se tendrá en cuenta para la corrección.
  *
  * Tampoco esta permitido modificar las líneas que contienen
  * las etiquetas <answer> y </answer>, obviamente :-)
  */


  //@ <answer>
  /*
    Indica el nombre y apellidos de los componentes del grupo
    ---------------------------------------------------------
    Componente 1:
    Componente 2:
  */
  //@ </answer>


  // Añade los #include que necesites
#include <iostream>
#include <fstream>
#include <cassert>
#include <memory>
#include <queue>
#include <stack>
#include <utility>

using namespace std;

/*
  Implementación de conjuntos. Contiene la definición del método `find_le` que
  tendrás que implementar.
*/

template <typename T> class SetTree {
public:
    SetTree() : root_node(nullptr), num_elems(0) {}
    SetTree(const SetTree& other)
        : num_elems(other.num_elems), root_node(copy_nodes(other.root_node)) {}
    ~SetTree() { delete_nodes(root_node); }

    void insert(const T& elem) {
        auto [new_root, inserted] = insert(root_node, elem);
        root_node = new_root;
        if (inserted) {
            num_elems++;
        }
    }

    bool contains(const T& elem) const { return search(root_node, elem); }

    void erase(const T& elem) {
        auto [new_root, removed] = erase(root_node, elem);
        root_node = new_root;
        if (removed) {
            num_elems--;
        }
    }

    int size() const { return num_elems; }
    bool empty() const { return num_elems == 0; }

    SetTree& operator=(const SetTree& other) {
        if (this != &other) {
            num_elems = other.num_elems;
            delete_nodes(root_node);
            root_node = copy_nodes(other.root_node);
        }
        return *this;
    }

    void display(std::ostream& out) const {
        out << "{";
        display(root_node, out);
        out << "}";
    }


    //@ <answer>
      // Implementa aquí la función `find_le` que se pide.
      // Si necesitas métodos privados auxiliares, impleméntalos al final de la clase

      // ¡No olvides el coste! Para ello puedes suponer que el árbol binario de
      //  búsqueda está equilibrado

    // El coste para esta funcion es el mismo que tiene la funcion recurisiva sobrecargada
    // que recibe un nodo y el elemento que ya hemos visto que tiene coste O(log N) siendo N
    // los elementos totales del arbol así que el coste de esta llamada inicial es el mismo

    pair<T, bool> find_le(const T& elem) {
        return find_le(root_node, elem);
        //Solo es hacer la llamada al auxiliar y devolver el pair

    }
    //@ </answer>


private:
    struct Node {
        T elem;
        Node* left, * right;

        Node(Node* left, const T& elem, Node* right)
            : left(left), elem(elem), right(right) {}
    };

    Node* root_node;
    int num_elems;

    static Node* copy_nodes(const Node* node) {
        if (node == nullptr) {
            return nullptr;
        }
        else {
            return new Node(copy_nodes(node->left), node->elem,
                copy_nodes(node->right));
        }
    }

    static void delete_nodes(const Node* node) {
        if (node != nullptr) {
            delete_nodes(node->left);
            delete_nodes(node->right);
            delete node;
        }
    }

    static std::pair<Node*, bool> insert(Node* root, const T& elem) {
        if (root == nullptr) {
            return { new Node(nullptr, elem, nullptr), true };
        }
        else if (elem < root->elem) {
            auto [new_root_left, inserted] = insert(root->left, elem);
            root->left = new_root_left;
            return { root, inserted };
        }
        else if (root->elem < elem) {
            auto [new_root_right, inserted] = insert(root->right, elem);
            root->right = new_root_right;
            return { root, inserted };
        }
        else {
            return { root, false };
        }
    }

    static bool search(const Node* root, const T& elem) {
        if (root == nullptr) {
            return false;
        }
        else if (elem == root->elem) {
            return true;
        }
        else if (elem < root->elem) {
            return search(root->left, elem);
        }
        else {
            return search(root->right, elem);
        }
    }

    static std::pair<Node*, bool> erase(Node* root, const T& elem) {
        if (root == nullptr) {
            return { root, false };
        }
        else if (elem < root->elem) {
            auto [new_root_left, erased] = erase(root->left, elem);
            root->left = new_root_left;
            return { root, erased };
        }
        else if (root->elem < elem) {
            auto [new_root_right, erased] = erase(root->right, elem);
            root->right = new_root_right;
            return { root, erased };
        }
        else {
            return { remove_root(root), true };
        }
    }

    static Node* remove_root(Node* root) {
        Node* left_child = root->left, * right_child = root->right;
        delete root;
        if (left_child == nullptr && right_child == nullptr) {
            return nullptr;
        }
        else if (left_child == nullptr) {
            return right_child;
        }
        else if (right_child == nullptr) {
            return left_child;
        }
        else {
            auto [lowest, new_right_root] = remove_lowest(right_child);
            lowest->left = left_child;
            lowest->right = new_right_root;
            return lowest;
        }
    }

    static std::pair<Node*, Node*> remove_lowest(Node* root) {
        assert(root != nullptr);
        if (root->left == nullptr) {
            return { root, root->right };
        }
        else {
            auto [removed_node, new_root_left] = remove_lowest(root->left);
            root->left = new_root_left;
            return { removed_node, root };
        }
    }

    static void display(Node* root, std::ostream& out) {
        if (root != nullptr) {
            if (root->left != nullptr) {
                display(root->left, out);
                out << ", ";
            }
            out << root->elem;
            if (root->right != nullptr) {
                out << ", ";
                display(root->right, out);
            }
        }
    }


    //@ <answer>

      // Implementa aquí las funciones privadas auxiliares que necesites.

      // ¡No olvides el coste! Para ello puedes suponer que el árbol binario de
      //  búsqueda está equilibrado

    // Como sabemos que es un arbol equilibrado el coste de esta funcion recursiva va a ser
    // O(log N) siendo N el numero de elementos del arbol y esto es porque busca el elemento del
    // arbol menor o igual al elemento pasado por parametro y esto lo hace con una llamada recurisva
    // a esta misma funcion en el caso peor y como ya hemos demostrado estas busquedas son de coste logaritmico
    // en el caso mas malo
   
    pair<T, bool> find_le(Node* root, const T& elem) {
        if (root == nullptr) {
            return { 0, false };
        }

        if (root->elem <= elem) {
            auto derecha = find_le(root->right, elem);
            if (derecha.second) {
                return derecha;
            }
            else {
                return { root->elem, true };
            }
        }
        else {
            return find_le(root->left, elem);
        }
    }

      // USAR CON FIND_LE

    //@ </answer>
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const SetTree<T>& set) {
    set.display(out);
    return out;
}

//@ <answer>
// ----------------------------------------------
// Modificar a partir de aquí
// ----------------------------------------------

// Función para tratar UN caso de prueba. Devuelve true si se ha tratado un
// caso de prueba o false si no lo ha hecho porque se ha encontrado con la
// marca de fin de entrada (0 0)


// El coste de esta funcion de M y N siendo M el numero de elementos que queremos escribir con nuestro teclado
// (la segunda linea de entrada en cada caso) y N son los elementos que tiene el arbol (los elemtos que tiene el teclado)
// primero tenemos una lectura de fichero y una insercion en el arbol t que como es equilibrado cuesta O(log N) por cada uno de los
// N elementos como media. Y el bucle de calcular la secuencia que hay que escribir tiene como coste O(M log N) porque hace M llamadas
// de operaciones constantes mas una llamada a la funcion find_le de coste (log N).
// Asi que el coste total se podria consisderar de orden del max(O(M log N), O(N log N)) que depende de N y M. Esto lo podemos consisderar
// que sigue en el orden de O(n log n) con n como numero entero de elementos

bool tratar_caso() {
    int n, m, elem;
    int cont = 0;
    bool mayores = true;
    SetTree<int> t;
    std::pair<int, bool> A;

    cin >> n >> m;

    if (n == 0 && m == 0) {
        return false;
    }

    for (int i = 0; i < n; i++) {
        cin >> elem;
        t.insert(elem);
    }
    for (int i = 0; i < m; i++) {
        cin >> elem;
        if (mayores) {
            A = t.find_le(elem);
            if (A.second) {
                cont += elem - A.first + 1;
            }
            else {
                cout << "NO SE PUEDE\n";
                mayores = false;
            }
        }
    }
    if (mayores == true) {
        cout << cont << endl;
    }
    return true;
}

// Implementar

    // Indica el coste de tratar un caso de prueba. Para ello puedes suponer que
    // los conjuntos que utilices están representados mediante árboles de
    // búsqueda equilibrados.


// ----------------------------------------------
// No modificar a partir de la línea
// ----------------------------------------------
//@ </answer>



int main() {
    // Si estás ejecutando el programa en tu ordenador, las siguientes líneas
    // redirigiran cualquier lectura de cin al fichero 'sample.in'. Esto es
    // útil para no tener que teclear los casos de prueba por teclado cada vez
    // que ejecutas el programa.
    //
    // Si prefieres teclear los casos de prueba por teclado en tu ordenador,
    // comenta las líneas comprendidas entre los #ifndef y #endif
#ifndef DOMJUDGE
    std::ifstream in("sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    // Llamamos a `tratar_caso` hasta que se agoten los casos de prueba
    while (tratar_caso()) {}

    // Comenta esto también si has comentado lo anterior.
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}

