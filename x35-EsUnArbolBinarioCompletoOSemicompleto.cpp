// ¿Es un árbol binario completo o semicompleto?
// ---------------------------------------------
// Estructuras de datos


#include <iostream>
#include <cassert>
#include <memory>
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




    tuple<bool, bool, int> esCompleto(const BinTree<char> &arbol) {
        if (arbol.empty()) {
            return {true, true, 0};
        }
else {
            auto [completoIzq, semicompletoIzq, nivelIzq] = esCompleto(arbol.left());
            auto [completoDer, semicompletoDer, nivelDer] = esCompleto(arbol.right());

            int nivel = max(nivelIzq, nivelDer) + 1;
            bool completo = completoIzq && completoDer && (nivelIzq == nivelDer);
/*
- Si el izquierdo tiene una altura más que el derecho y ambos son completos, entonces el árbol es semicompleto.
- Si el izquierdo es semicompleto y el derecho es completo, entonces el árbol también puede ser semicompleto (depende de las alturas).
- Si el izquierdo es completo y el derecho es semicompleto, entonces el árbol también puede ser semicompleto (depende de las alturas).
 */
            bool semicompleto = (nivelIzq-nivelDer == 1 && completoDer && completoIzq) || (semicompletoIzq && completoDer && nivelIzq-nivelDer == 1) || (completoIzq && semicompletoDer && nivelIzq == nivelDer);

            return {completo, semicompleto, nivel};
        }

}



// Implementa las funciones recursivas que sean necesarias


void tratar_caso() {
    // Introduce aquí el código para tratar un caso de prueba.

    BinTree<char> t = read_tree<char>(cin);
    auto [completo, semicompleto, nivel] = esCompleto(t);
    if(completo ) cout << "COMPLETO";
    else if (semicompleto) cout << "SEMICOMPLETO";
    else cout << "NADA";
    cout << endl;


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

