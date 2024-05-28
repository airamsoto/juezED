#include <iostream>
#include <cassert>
#include <memory>
#include <tuple>
#include <fstream>

using namespace std;

template<class T>
class BinTree {
private:
    struct TreeNode;
    using NodePointer = std::shared_ptr<TreeNode>;

public:
    BinTree() : root_node(nullptr) {}

    BinTree(const T &elem) : root_node(std::make_shared<TreeNode>(nullptr, elem, nullptr)) {}

    BinTree(const BinTree &left, const T &elem, const BinTree &right)
            : root_node(std::make_shared<TreeNode>(left.root_node, elem, right.root_node)) {}

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

template<typename T>
BinTree<T> read_tree(std::istream &in) {
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

pair<bool, int> bienCod(const BinTree<int> &arbol) {
    if (arbol.empty()) {
        return {true, 0};
    } else if (arbol.left().empty() && arbol.right().empty())return {true, arbol.root()};
    else {
        auto [diestroIzq, sumasIzq] = bienCod(arbol.left());
        auto [diestroDer, sumasDer] = bienCod(arbol.right());
        bool diestro = sumasDer > sumasIzq;

        return {diestro && diestroIzq && diestroDer, sumasDer + sumasIzq + arbol.root()};
    }
}

bool bien_codificado(const BinTree<int> &arbol) {
    auto [jose, pedro] = bienCod(arbol);
    return jose;
}

// Función que trata un caso de prueba
void tratar_caso() {
    BinTree<int> t = read_tree<int>(cin);
    if (bien_codificado(t)) cout << "SI";
    else cout << "NO";
    cout << '\n';


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
