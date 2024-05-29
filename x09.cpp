// Invertir un segmento de una lista enlazada simple
// -------------------------------------------------
// Estructuras de datos

#include <iostream>
#include <cassert>
#include <fstream>

/*
 * Implementación del TAD Lista mediante listas enlazadas simples.
 */

class ListLinkedSingle {
private:
    struct Node {
        int value;
        Node *next;
    };

public:
    ListLinkedSingle() {
        head = new Node;
        head->next = nullptr;
    }

    ~ListLinkedSingle() { delete_list(head); }

    ListLinkedSingle(const ListLinkedSingle &other)
            : head(copy_nodes(other.head)) {}

    void push_front(const int &elem) {
        Node *new_node = new Node{elem, head->next};
        head->next = new_node;
    }

    void push_back(const int &elem);

    void pop_front() {
        assert(head->next != nullptr);
        Node *old_head = head->next;
        head->next = head->next->next;
        delete old_head;
    }

    void pop_back();

    int size() const;

    bool empty() const { return head->next == nullptr; };

    const int &front() const {
        assert(head->next != nullptr);
        return head->next->value;
    }

    int &front() {
        assert(head->next != nullptr);
        return head->next->value;
    }

    const int &back() const { return last_node()->value; }

    int &back() { return last_node()->value; }

    const int &at(int index) const {
        Node *result_node = nth_node(index);
        assert(result_node != nullptr);
        return result_node->value;
    }

    int &at(int index) {
        Node *result_node = nth_node(index);
        assert(result_node != nullptr);
        return result_node->value;
    }

    void display(std::ostream &out) const;

    void display() const { display(std::cout); }

    void reverse_segment(int index, int length);

private:
    Node *head;

    void delete_list(Node *start_node);
    Node *last_node() const;
    Node *nth_node(int n) const;
    Node *copy_nodes(Node *start_node) const;
};

ListLinkedSingle::Node *ListLinkedSingle::copy_nodes(Node *start_node) const {
    if (start_node != nullptr) {
        Node *result = new Node{start_node->value, copy_nodes(start_node->next)};
        return result;
    } else {
        return nullptr;
    }
}

void ListLinkedSingle::delete_list(Node *start_node) {
    if (start_node != nullptr) {
        delete_list(start_node->next);
        delete start_node;
    }
}

void ListLinkedSingle::push_back(const int &elem) {
    Node *new_node = new Node{elem, nullptr};
    last_node()->next = new_node;
}

void ListLinkedSingle::pop_back() {
    assert(head->next != nullptr);
    Node *previous = head;
    Node *current = head->next;

    while (current->next != nullptr) {
        previous = current;
        current = current->next;
    }

    delete current;
    previous->next = nullptr;
}

int ListLinkedSingle::size() const {
    int num_nodes = 0;

    Node *current = head->next;
    while (current != nullptr) {
        num_nodes++;
        current = current->next;
    }

    return num_nodes;
}

ListLinkedSingle::Node *ListLinkedSingle::last_node() const {
    Node *current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    return current;
}

ListLinkedSingle::Node *ListLinkedSingle::nth_node(int n) const {
    assert(0 <= n);
    int current_index = 0;
    Node *current = head->next;

    while (current_index < n && current != nullptr) {
        current_index++;
        current = current->next;
    }

    return current;
}

void ListLinkedSingle::display(std::ostream &out) const {
    out << "[";
    if (head->next != nullptr) {
        out << head->next->value;
        Node *current = head->next->next;
        while (current != nullptr) {
            out << ", " << current->value;
            current = current->next;
        }
    }
    out << "]";
}


void ListLinkedSingle::reverse_segment(int index, int length) {
    if (index < 0 || length <= 0) return;
    Node* prev = nullptr;
    Node* current = head->next;
    Node* next = nullptr;
    Node* inicio = head;
    Node* end;
    for (int i = 0; i < index; ++i) {
        inicio = current;
        current = current->next;
    }
    end = current;
    for (int j = 0; current != nullptr && j < length; ++j) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

   inicio->next = prev;
    end->next = current;

}





using namespace std;


// Función para tratar un caso de prueba
// Devuelve `false` si no ha podido leer la entrada porque se
// ha encontrado con fin de fichero. Devuelve `true` en caso
// contrario
bool tratar_caso() {
    int N, P, L, aux;
    cin >> N >> P >> L;
    if (cin.eof()) return false;
    ListLinkedSingle l1;
    for (int i = 0; i < N; ++i) {
        cin >> aux;
        l1.push_back(aux);
    }
    l1.reverse_segment(P, L);
    l1.display(std::cout);
    cout << '\n';

    // ...

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
