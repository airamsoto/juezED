// Partición de una lista enlazada ordenada
// ----------------------------------------
// Estructuras de datos
#include <fstream>
#include <iostream>
#include <cassert>

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

    void display_reverse(std::ostream &out) const;

    void display_reverse() const {
        display_reverse(std::cout);
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

    // Nuevos métodos
    // Se implementan más abajo
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

void ListLinkedDouble::display_reverse(std::ostream &out) const {
    out << "[";
    if (head->prev != head) {
        out << head->prev->value;
        Node *current = head->prev->prev;
        while (current != head) {
            out << ", " << current->value;
            current = current->prev;
        }
    }
    out << "]";
}

std::ostream &operator<<(std::ostream &out, const ListLinkedDouble &l) {
    l.display(out);
    return out;
}


// 0(1)
void ListLinkedDouble::attach(Node *node, Node *before) {
    node->next = before->next;
    node->prev = before;
    before->next->prev = node;
    before->next = node;
}

// 0(1)
void ListLinkedDouble::detach(Node *node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
}


// 0(n) siendo n el numero de nodos de la lista ya que los recorre todos para compararlos con el pivot y hace operaciones constantes
void ListLinkedDouble::partition(int pivot) {
    Node *current = head->next;
    Node *aux = head;
    Node *jose;
    while (current != head) {
        jose = current->next;
        if (current->value <= pivot) {
            detach(current);
            attach(current, aux);


            aux = current;
        }
        current = jose;
    }
}


void tratar_caso() {
    int aux;
    cin >> aux;
    ListLinkedDouble lista;
    while (aux != 0) {
        lista.push_back(aux);
        cin >> aux;
    }
    cin >> aux;
    lista.partition(aux);
    lista.display(cout);
    cout << endl;
    lista.display_reverse(cout);
    cout << endl;
}


int main() {
    // Leemos el número de casos de prueba
#ifndef DOMJUDGE
    std::ifstream in("sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int num_casos;
    cin >> num_casos;


    // Ejecutamos tratar_caso() tantas veces como diga el número leído
    for (int i = 0; i < num_casos; i++) {
        tratar_caso();
    }
    // Comenta esto tambi�n si has comentado lo anterior.
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif

    return 0;
}
/*
 * [5, 7, 4, 6, 10, 9]
[9, 10, 6, 4, 7, 5]
[5, 4, 6, 10, 9, 7]
[7, 9, 10, 6, 4, 5]
[5, 10, 9, 7, 4, 6]
[6, 4, 7, 9, 10, 5]
[5, 10, 9, 7, 4, 6]
[6, 4, 7, 9, 10, 5]
[4]
[4]
[4]
[4]
[]
[]
 */
