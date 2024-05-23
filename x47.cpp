// Reconstruir un árbol binario
// ----------------------------
// Estructuras de datos


#include <iostream>
#include <cassert>
#include <memory>
#include <utility>
#include <vector>
#include <queue>
#include <fstream>
#include <stack>
#include <unordered_map>

// TAD de árboles binarios de búsqueda
template <class T> class BinTree {

private:
    struct TreeNode;
    using NodePointer = std::shared_ptr<TreeNode>;

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

    template <typename U> void preorder(U func) const {
        preorder(root_node, func);
    }

    template <typename U> void inorder(U func) const { inorder(root_node, func); }

    template <typename U> void postorder(U func) const {
        postorder(root_node, func);
    }

    template <typename U> void levelorder(U func) const;

private:
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

    template <typename U> static void preorder(const NodePointer &node, U func);

    template <typename U> static void inorder(const NodePointer &node, U func);

    template <typename U> static void postorder(const NodePointer &node, U func);
};

template <typename T>
template <typename U>
void BinTree<T>::preorder(const NodePointer &node, U func) {
    if (node != nullptr) {
        func(node->elem);
        preorder(node->left, func);
        preorder(node->right, func);
    }
}

template <typename T>
template <typename U>
void BinTree<T>::inorder(const NodePointer &node, U func) {
    if (node != nullptr) {
        inorder(node->left, func);
        func(node->elem);
        inorder(node->right, func);
    }
}

template <typename T>
template <typename U>
void BinTree<T>::postorder(const NodePointer &node, U func) {
    if (node != nullptr) {
        postorder(node->left, func);
        postorder(node->right, func);
        func(node->elem);
    }
}

template <typename T>
template <typename U>
void BinTree<T>::levelorder(U func) const {
    std::queue<NodePointer> pending;
    if (root_node != nullptr) {
        pending.push(root_node);
    }
    while (!pending.empty()) {
        NodePointer current = pending.front();
        pending.pop();
        func(current->elem);
        if (current->left != nullptr) {
            pending.push(current->left);
        }
        if (current->right != nullptr) {
            pending.push(current->right);
        }
    }
}

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


// Define las funciones auxiliares que creas necesarias


BinTree<int> creaArbolNuevo(vector<int> const& preorder, int inicioPreorden, int finalPreorden, vector<int> const& inorder, int inicioInorden, int finalInorden, unordered_map<int, int>& inMap) {
    if (inicioPreorden > finalPreorden || inicioInorden > finalInorden) return BinTree<int>();

    int rootVal = preorder[inicioPreorden]; //saco la raiz que es el primer valor del preorder
    BinTree<int> leftTree, rightTree; //creo subizq y subder
    int inRoot = inMap[rootVal]; //como en los mapas tengo alamcenado el valor del nodo junto a su posicion en iorden, tengo la posicion de la raiz en el vector inorden
    int numsLeft = inRoot - inicioInorden; //numero de elementos que hay desde en el subarbol izquierdo

    if (inicioInorden <= inRoot - 1) { //si hay mas de dos elemetos, es la comparacion entre donde empieza el inorden y donde se encunetra l araiz en el mismo vecotr
        leftTree = creaArbolNuevo(preorder, inicioPreorden + 1, inicioPreorden + numsLeft, inorder, inicioInorden, inRoot - 1, inMap);
        /* preorder: se le pasa la lista preornde
         * inicioPreorden + 1 avanzo una en el inicio de preorden para pasar a la primera pos siguiente de la raiz
         * inicioPreorden + numsLeft el final del subarbol izquierdo sera en la lista de preorden el inicio + el numero de elementos sacado de la lista de inorden
         * inorder lista inorden
         * inicioInorden el inicio en inorden sigue sienod el mismo ya que el primer elemento aun no lo hemos tocaod y pertenece al subarbol izquierdo
         * inRoot - 1, podemos restarle uno ya que in root es la posicion de la raiz que ya la hemos miraod y ajustamos mas el intervalo
         * inMap)
         */
    }

    if (inRoot + 1 <= finalInorden) {
        rightTree = creaArbolNuevo(preorder, inicioPreorden + numsLeft + 1, finalPreorden, inorder, inRoot + 1, finalInorden, inMap);
        /*
         *preorder
         * inicioPreorden + numsLeft + 1 el inicio del preorden ahora sera el inicio del deel izquierdo + el numero de elemnto de la izquieda + la raiz
         * finalPreorden sigue siendo el mismo
         * inorder lista ocompelta
         * inRoot + 1,  el inicio del inorden es una posicion a la derecha de la raiz ya que eso es el comienzo del arbol derecho
         * finalInorden el final del arbol derecho se corresponde con el final de la lista inorden
         * inMap)
         */
    }

    return BinTree<int>(leftTree, rootVal, rightTree);
}

BinTree<int> reconstruir(vector<int> const& preorden, vector<int> const& inorden) {
    unordered_map<int, int> mapa;
    for (int i = 0; i < inorden.size(); i++) {
        mapa[inorden[i]] = i;
    }
    return creaArbolNuevo(preorden, 0, preorden.size() - 1, inorden, 0, inorden.size() - 1, mapa);
}

// Función que trata un caso de prueba
bool tratar_caso() {
    int num_elems;
    cin >> num_elems;

    if (cin.eof()) return false;

    vector<int> preorden, inorden;

    for (int i = 0; i < num_elems; i++) {
        int x; cin >> x;
        preorden.push_back(x);
    }

    for (int i = 0; i < num_elems; i++) {
        int x; cin >> x;
        inorden.push_back(x);
    }

    cout << reconstruir(preorden, inorden) << "\n";

    return true;
}



int main() {
#ifndef DOMJUDGE
    std::ifstream in("sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (tratar_caso()) {}

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif

    return 0;
}

