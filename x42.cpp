// Árboles densos
// --------------
// Estructuras de datos


#include <iostream>
#include <cassert>
#include <memory>
#include <utility>
#include <vector>
#include <queue>
#include <stack>
#include <fstream>
#include <climits>

// TAD de árboles binarios de búsqueda
template<class T>
class BinTree {

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

    template<typename U>
    void preorder(U func) const {
        preorder(root_node, func);
    }

    template<typename U>
    void inorder(U func) const { inorder(root_node, func); }

    template<typename U>
    void postorder(U func) const {
        postorder(root_node, func);
    }

    template<typename U>
    void levelorder(U func) const;

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

    template<typename U>
    static void preorder(const NodePointer &node, U func);

    template<typename U>
    static void inorder(const NodePointer &node, U func);

    template<typename U>
    static void postorder(const NodePointer &node, U func);
};

template<typename T>
template<typename U>
void BinTree<T>::preorder(const NodePointer &node, U func) {
    if (node != nullptr) {
        func(node->elem);
        preorder(node->left, func);
        preorder(node->right, func);
    }
}

template<typename T>
template<typename U>
void BinTree<T>::inorder(const NodePointer &node, U func) {
    if (node != nullptr) {
        inorder(node->left, func);
        func(node->elem);
        inorder(node->right, func);
    }
}

template<typename T>
template<typename U>
void BinTree<T>::postorder(const NodePointer &node, U func) {
    if (node != nullptr) {
        postorder(node->left, func);
        postorder(node->right, func);
        func(node->elem);
    }
}

template<typename T>
template<typename U>
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

template<typename T>
std::ostream &operator<<(std::ostream &out, const BinTree<T> &tree) {
    tree.display(out);
    return out;
}

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

using namespace std;



bool ascendente_denso2(const BinTree<int> &tree, int &minimo) {
    bool denso = true;
    if (!tree.empty()) {

        if(tree.left().empty() && tree.right().empty() || (tree.left().empty() && !tree.right().empty())) {
            if(minimo == INT_MIN) minimo  = tree.root();
            denso = true;
        }
        if (!ascendente_denso2(tree.left(), minimo)){
            denso = false;
        }
        if (tree.root() != minimo){
            denso = false;
        } else {
            minimo++;
        }
        if (!ascendente_denso2(tree.right(), minimo)){
            denso = false;
        }
    }
    return denso;
}

bool ascendente_denso(const BinTree<int> &tree) {
    int i = INT_MIN;
    return ascendente_denso2(tree, i);

}



// Función que trata un caso de prueba
void tratar_caso() {
    BinTree<int> tree = read_tree<int>(std::cin);

    std::cout << (ascendente_denso(tree) ? "SI" : "NO") << std::endl;
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


