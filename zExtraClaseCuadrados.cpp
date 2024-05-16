/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */

/*
 * MUY IMPORTANTE: Para realizar este ejercicio solo podéis
 * modificar el código contenido entre las etiquetas <answer>
 * y </answer>.
 *
 * Tampoco está permitido modificar las líneas que contienen
 * las etiquetas <answer> y </answer>, obviamente :-)
 */

//@ <answer>
// Nombre y Apellidos: ___________________________________
//@ </answer>

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <cassert>
#include <memory>
#include <tuple>

/*
  Implementación de la clase BinTree para representar árboles binarios.

  Para realizar este ejercicio no es necesario modificar la clase.
 */

template <class T> class BinTree {
public:
  BinTree() : root_node(nullptr) {}

  BinTree(const T &elem)
      : root_node(std::make_shared<TreeNode>(nullptr, elem, nullptr)) {}

  BinTree(const BinTree &left, const T &elem, const BinTree &right)
      : root_node(std::make_shared<TreeNode>(left.root_node, elem,
                                             right.root_node)) {}

  bool empty() const { return root_node == nullptr; }

  const T &root() const {
    assert(root_node != nullptr);
    return root_node->elem;
  }

  BinTree left() const {
    assert(root_node != nullptr);
    BinTree result;
    result.root_node = root_node->left;
    return result;
  }

  BinTree right() const {
    assert(root_node != nullptr);
    BinTree result;
    result.root_node = root_node->right;
    return result;
  }

  void display(std::ostream &out) const { display_node(root_node, out); }

private:

  struct TreeNode;
  using NodePointer = std::shared_ptr<TreeNode>;

  struct TreeNode {
    TreeNode(const NodePointer &left, const T &elem, const NodePointer &right)
        : elem(elem), left(left), right(right) {}

    T elem;
    NodePointer left, right;
  };

  NodePointer root_node;

  static void display_node(const NodePointer &root, std::ostream &out) {
    if (root == nullptr) {
      out << ".";
    } else {
      out << "(";
      display_node(root->left, out);
      out << " " << root->elem << " ";
      display_node(root->right, out);
      out << ")";
    }
  }
};

template <typename T>
std::ostream &operator<<(std::ostream &out, const BinTree<T> &tree) {
  tree.display(out);
  return out;
}

template <typename T> BinTree<T> read_tree(std::istream &in) {
  char c;
  in >> c;
  if (c == '.') {
    return BinTree<T>();
  } else {
    assert(c == '(');
    BinTree<T> left = read_tree<T>(in);
    T elem;
    in >> elem;
    BinTree<T> right = read_tree<T>(in);
    in >> c;
    assert(c == ')');
    BinTree<T> result(left, elem, right);
    return result;
  }
}

using namespace std;

// ----------------------------------------------------------------
// ¡No modificar nada importante por encima de esta línea!

// Implementa a continuación la función pedida. Puedes definir las funciones
// auxiliares que necesites.
//@ <answer> 

//COSTE: n
//Primera componente valor del nodo cuadrado a mayor profundidad, la segunda la profundidad del nodo y la tercera suma de todos los nodos
tuple <int, int, int> nodo_cuadrado_mayor_profT(const BinTree<int> &t){
    
  if(t.empty()) return {-1, -1, 0};
  else {
    auto [nodoI, profI, sumaI] = nodo_cuadrado_mayor_profT(t.left());
    auto [nodoD, profD, sumaD] = nodo_cuadrado_mayor_profT(t.right());
    int suma = sumaI+ sumaD + t.root();
    if(nodoI == -1 && nodoD == -1) {
      if (t.root() == sumaD + sumaI) {
        return {t.root(), 1, suma};
      } return {-1,-1,suma};

    } else {
      if(profI >= profD) {
        return {nodoI, profI+1, suma};
      } else return {nodoD, profD+1, suma};
    }
  }

}


int nodo_cuadrado_mayor_prof(const BinTree<int> &t) {
  auto[nodo, prof, suma] = nodo_cuadrado_mayor_profT(t);
  return nodo;

}

/*@ </answer> */

void resuelveCaso() {
  auto t = read_tree<int>(cin);
  cout << nodo_cuadrado_mayor_prof(t) << '\n';
}

int main() {
#ifndef DOMJUDGE
   std::ifstream in("sample.in");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

   int numCasos;
   cin >> numCasos;

   for (int i = 0; i < numCasos; ++i) {
      resuelveCaso();
   }

#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   // Descomentar si se trabaja en Visual Studio
   // system("PAUSE");
#endif
   return 0;
}
