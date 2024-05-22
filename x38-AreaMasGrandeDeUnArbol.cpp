// Área más grande en un árbol binario
// -----------------------------------
// Estructuras de datos


#include <iostream>
#include <cassert>
#include <memory>
#include <utility>
#include <fstream>

// TAD de árboles binarios de búsqueda
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
    // Las definiciones de TreeNode y NodePointer dependen recursivamente
    // la una de la otra. Por eso declaro 'struct TreeNode;' antes de NodePointer
    // para que el compilador sepa, cuando analice la definición de NodePointer,
    // que TreeNode va a ser definida más adelante.

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


int area_mayor_sin_barreras(const BinTree<bool> &tree) {

    if (tree.empty()) return 0;
    else {

        int nodosIzquierda = area_mayor_sin_barreras(tree.left());
        int nodosDerecha = area_mayor_sin_barreras(tree.right());
        int actual = nodosDerecha + nodosIzquierda;
        q
        if(!tree.left().empty()  && tree.left().root() == 1) {
            actual-=nodosIzquierda;
        }
        if(!tree.right().empty() && tree.right().root() == 1) {
            actual-=nodosDerecha;
        }
        if(tree.root() == 0) actual++;
        else actual = 0;

        return max (actual, max (nodosDerecha, nodosIzquierda));

    }
}


// Función que trata un caso de prueba
void tratar_caso() {
    BinTree<bool> t = read_tree<bool>(cin);

    cout << area_mayor_sin_barreras(t) << "\n";
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

