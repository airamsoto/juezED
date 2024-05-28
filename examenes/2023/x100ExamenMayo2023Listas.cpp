// Sumar a un elemento de una lista ordenada
// -----------------------------------------
// Estructuras de datos

#include <iostream>
#include <cassert>
#include <fstream>

using namespace std;

class ListLinkedDouble {
private:
    struct Node {
        string value;
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

    void push_front(const string &elem) {
        Node *new_node = new Node{elem, head->next, head};
        head->next->prev = new_node;
        head->next = new_node;
        num_elems++;
    }

    void push_back(const string &elem) {
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

    const string &front() const {
        assert(num_elems > 0);
        return head->next->value;
    }

    string &front() {
        assert(num_elems > 0);
        return head->next->value;
    }

    const string &back() const {
        assert(num_elems > 0);
        return head->prev->value;
    }

    string &back() {
        assert(num_elems > 0);
        return head->prev->value;
    }

    const string &operator[](int index) const {
        assert(0 <= index && index < num_elems);
        Node *result_node = nth_node(index);
        return result_node->value;
    }

    string &operator[](int index) {
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
    void rotar_derecha();


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

    // Implementar
}

// No olvides el coste!
void ListLinkedDouble::detach(Node *current) {
    current->prev->next = current->next;
    current->next->prev = current->prev;

}


void ListLinkedDouble::rotar_derecha() {

    Node *current = head->next->next->next;
    Node* ultimo_impar;

    while (current != head && current->next != head) {
        ultimo_impar = current->prev->prev;
        detach(ultimo_impar);
        attach(ultimo_impar, current->prev);
        current = current->next->next;
    }

    if (current->next == head) { //impar
        ultimo_impar = current->prev->prev;
        detach(ultimo_impar); //utimo caso
        attach(ultimo_impar, current->prev);


        detach(current);
        attach(current, head);

    } else { //par
        ultimo_impar = current->prev->prev;
        detach(ultimo_impar);
        attach(ultimo_impar, head);
    }

}


bool tratar_caso() {
    int n;
    string aux;
    cin >> n;
    if(!cin) return false;
    ListLinkedDouble l1;
    for (int i = 0; i < n; ++i) {
        cin >> aux;
        l1.push_back(aux);
    }
    l1.rotar_derecha();
    l1.display();
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
