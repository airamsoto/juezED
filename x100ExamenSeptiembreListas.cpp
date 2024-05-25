// Sumar a un elemento de una lista ordenada
// -----------------------------------------
// Estructuras de datos
//TODO USAR LIST LINKED SINGLE Y NO DOUBLE

#include <iostream>
#include <cassert>
#include <fstream>

using namespace std;

class ListLinkedDouble {
private:
    struct Node {
        int value;
        Node *next;
        Node *prev;
    };

public:
    ListLinkedDouble() : num_elems(0) {
        head = new Node;
        head->next = head;
        head->prev = head;
    }

    ListLinkedDouble(const ListLinkedDouble &other) : ListLinkedDouble() {
        copy_nodes_from(other);
        num_elems = other.num_elems;
    }

    ~ListLinkedDouble() { delete_nodes(); }

    void push_front(const int &elem) {
        Node *new_node = new Node{elem, head->next, head};
        head->next->prev = new_node;
        head->next = new_node;
        num_elems++;
    }

    void push_back(const int &elem) {
        Node *new_node = new Node{elem, head, head->prev};
        head->prev->next = new_node;
        head->prev = new_node;
        num_elems++;
    }

    void pop_front() {
        assert(num_elems > 0);
        Node *target = head->next;
        head->next = target->next;
        target->next->prev = head;
        delete target;
        num_elems--;
    }

    void pop_back() {
        assert(num_elems > 0);
        Node *target = head->prev;
        target->prev->next = head;
        head->prev = target->prev;
        delete target;
        num_elems--;
    }

    int size() const { return num_elems; }

    bool empty() const { return num_elems == 0; };

    const int &front() const {
        assert(num_elems > 0);
        return head->next->value;
    }

    int &front() {
        assert(num_elems > 0);
        return head->next->value;
    }

    const int &back() const {
        assert(num_elems > 0);
        return head->prev->value;
    }

    int &back() {
        assert(num_elems > 0);
        return head->prev->value;
    }

    const int &operator[](int index) const {
        assert(0 <= index && index < num_elems);
        Node *result_node = nth_node(index);
        return result_node->value;
    }

    int &operator[](int index) {
        assert(0 <= index && index < num_elems);
        Node *result_node = nth_node(index);
        return result_node->value;
    }

    ListLinkedDouble &operator=(const ListLinkedDouble &other) {
        if (this != &other) {
            delete_nodes();
            head = new Node;
            head->next = head->prev = head;
            copy_nodes_from(other);
            num_elems = other.num_elems;
        }
        return *this;
    }

    void display(std::ostream &out) const;

    void display() const { display(std::cout); }


    // Nuevo método
    // Se implementa más abajo
    void partition(int pivot);


private:
    Node *head;
    int num_elems;

    Node *nth_node(int n) const;

    void delete_nodes();

    void copy_nodes_from(const ListLinkedDouble &other);

    static void attach(Node *node, Node *before);

    static void detach(Node *node);
};

ListLinkedDouble::Node *ListLinkedDouble::nth_node(int n) const {
    int current_index = 0;
    Node *current = head->next;

    while (current_index < n && current != head) {
        current_index++;
        current = current->next;
    }

    return current;
}

void ListLinkedDouble::delete_nodes() {
    Node *current = head->next;
    while (current != head) {
        Node *target = current;
        current = current->next;
        delete target;
    }

    delete head;
}

void ListLinkedDouble::copy_nodes_from(const ListLinkedDouble &other) {
    Node *current_other = other.head->next;
    Node *last = head;

    while (current_other != other.head) {
        Node *new_node = new Node{current_other->value, head, last};
        last->next = new_node;
        last = new_node;
        current_other = current_other->next;
    }
    head->prev = last;
}

void ListLinkedDouble::display(std::ostream &out) const {
    out << "[";
    if (head->next != head) {
        out << head->next->value;
        Node *current = head->next->next;
        while (current != head) {
            out << ", " << current->value;
            current = current->next;
        }
    }
    out << "]";
}

std::ostream &operator<<(std::ostream &out, const ListLinkedDouble &l) {
    l.display(out);
    return out;
}


// No olvides el coste!
void ListLinkedDouble::attach(Node *node, Node *before) {
    node->next = before->next;
    node->prev = before;
    before->next->prev = node;
    before->next = node;
}

// No olvides el coste!
void ListLinkedDouble::detach(Node *current) {
    current->prev->next = current->next;
    current->next->prev = current->prev;

}


void ListLinkedDouble::partition(int pivot) {
    Node *current = head->next;
    Node *aux = nullptr;
    Node *prev;
    Node* meter = head->prev;
    Node * perica = head->prev;
    while (current != head) {
        prev = current->prev;
        if (prev->value > pivot) {

            detach(prev);
            attach(prev, head->prev);


        }
        current = current->next;
    }

}


bool tratar_caso() {
    int n, pivot;
    cin >> n >> pivot;
    if (!cin) return false;
    ListLinkedDouble lista;
    int aux;
    for (int i = 0; i < n; ++i) {
        cin >> aux;
        lista.push_back(aux);
    }
    lista.partition(pivot);
    lista.display(cout);
    cout << endl;
    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif


    while (tratar_caso()) {}

// Comenta esto tambi�n si has comentado lo anterior.
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
    return 0;

}