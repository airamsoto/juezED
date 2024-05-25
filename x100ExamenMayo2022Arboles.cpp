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

tuple<int, int> auxIntermedios(const BinTree<int> tree, int padre) {
    if (tree.empty()) {
        return {0,0};
    } else if (tree.left().empty() && tree.right().empty()) {
        if(tree.root()==0&&padre!=-1){
            return {tree.root(), 1};
        }
        return {tree.root(), 0};
    }
    else {
        auto[sumaIzq, nodosIntIzq] = auxIntermedios(tree.left(),  tree.root());
        auto [ sumaDer, nodosIntDer] = auxIntermedios(tree.right(), tree.root());
        int total = sumaIzq + sumaDer + tree.root();
        int numIntermedios = nodosIntDer + nodosIntIzq;
      if(padre!=-1&&abs(sumaIzq-sumaDer)%padre==tree.root()){
          numIntermedios++;
      }

        return {total, numIntermedios} ;

    }
}


int num_nodos_intermedios(const BinTree<int> &tree) {
    return 0;
}

// Función que trata un caso de prueba
void tratar_caso() {
    BinTree<int> t = read_tree<int>(cin);
    int n = 0, padre;
    auto [jose , pedro ] = auxIntermedios(t, -1);
    cout << pedro << '\n';


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
