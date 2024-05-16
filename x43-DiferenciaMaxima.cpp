// Diferencia máxima en un árbol binario
// -------------------------------------
// Estructuras de datos


#include <iostream>
#include <cassert>
#include <memory>
#include <utility>
#include <vector>
#include <queue>
#include <stack>
#include <fstream>

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
pair<int, int> maximaDifAux (const BinTree<int> & t) {
    if(t.empty()) return {-1, -1};
    else {

        int mejorResultado = 0;

        if(!t.left().empty()) mejorResultado = max (abs (t.root()-t.left().root()), mejorResultado);

        auto[hojaIzquierda, maximaIzq] = maximaDifAux(t.left());
        if(!t.right().empty() && t.left().empty()) mejorResultado = max (abs (t.root()-t.right().root()), mejorResultado);
        else if(!t.right().empty()) mejorResultado = max (abs (hojaIzquierda-t.right().root()), mejorResultado);
        auto [hojaDerecha, maximaDer] = maximaDifAux(t.right());

        int dev = t.root();
        if (hojaDerecha != -1) dev  = hojaDerecha;
        else if (hojaIzquierda != -1) dev = hojaIzquierda;


        return {dev, max (mejorResultado, max (maximaDer, maximaIzq)) };
    }
}



int maxima_diferencia(const BinTree<int> &tree) {

    return maximaDifAux(tree).second;

}

// Función para tratar un caso de prueba
void tratar_caso() {
    BinTree<int> t = read_tree<int>(cin);
    cout << maxima_diferencia(t) << "\n";
}


int main() {
#ifndef DOMJUDGE
    ifstream in("sample.in");
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        tratar_caso();
    }


#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
#endif
    return 0;
}
