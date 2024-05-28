// Entramar dos listas doblemente enlazadas
// ----------------------------------------
// Estructuras de datos

#include <iostream>
#include <cassert>
#include <fstream>
using namespace std;

class ListLinkedDouble {
private:

    struct Node {
        int value;
        Node* next;
        Node* prev;
    };
    static void attach(Node *node, Node *before);

    static void detach(Node *node);

public:
    ListLinkedDouble() : num_elems(0) {
        head = new Node;
        head->next = head;
        head->prev = head;
    }

    ListLinkedDouble(const ListLinkedDouble& other) : ListLinkedDouble() {
        copy_nodes_from(other);
        num_elems = other.num_elems;
    }

    ~ListLinkedDouble() { delete_nodes(); }

    void push_front(const int& elem) {
        Node* new_node = new Node{ elem, head->next, head };
        head->next->prev = new_node;
        head->next = new_node;
        num_elems++;
    }

    void push_back(const int& elem) {
        Node* new_node = new Node{ elem, head, head->prev };
        head->prev->next = new_node;
        head->prev = new_node;
        num_elems++;
    }

    void pop_front() {
        assert(num_elems > 0);
        Node* target = head->next;
        head->next = target->next;
        target->next->prev = head;
        delete target;
        num_elems--;
    }

    void pop_back() {
        assert(num_elems > 0);
        Node* target = head->prev;
        target->prev->next = head;
        head->prev = target->prev;
        delete target;
        num_elems--;
    }

    int size() const { return num_elems; }

    bool empty() const { return num_elems == 0; };

    const int& front() const {
        assert(num_elems > 0);
        return head->next->value;
    }

    int& front() {
        assert(num_elems > 0);
        return head->next->value;
    }

    const int& back() const {
        assert(num_elems > 0);
        return head->prev->value;
    }

    int& back() {
        assert(num_elems > 0);
        return head->prev->value;
    }

    const int& operator[](int index) const {
        assert(0 <= index && index < num_elems);
        Node* result_node = nth_node(index);
        return result_node->value;
    }

    int& operator[](int index) {
        assert(0 <= index && index < num_elems);
        Node* result_node = nth_node(index);
        return result_node->value;
    }

    ListLinkedDouble& operator=(const ListLinkedDouble& other) {
        if (this != &other) {
            delete_nodes();
            head = new Node;
            head->next = head->prev = head;
            copy_nodes_from(other);
            num_elems = other.num_elems;
        }
        return *this;
    }

    void display(std::ostream& out) const;

    void display() const { display(std::cout); }

    // El m�todo se implementa m�s abajo, fuera de la definici�n de la clase.
    void desparizar(ListLinkedDouble& other);

private:
    // Declara aqu� los m�todos auxiliares privados que necesites,

    Node* head;
    int num_elems;

    Node* nth_node(int n) const;
    void delete_nodes();
    void copy_nodes_from(const ListLinkedDouble& other);
};

ListLinkedDouble::Node* ListLinkedDouble::nth_node(int n) const {
    int current_index = 0;
    Node* current = head->next;

    while (current_index < n && current != head) {
        current_index++;
        current = current->next;
    }

    return current;
}

void ListLinkedDouble::delete_nodes() {

}

void ListLinkedDouble::copy_nodes_from(const ListLinkedDouble& other) {
    Node* current_other = other.head->next;
    Node* last = head;

    while (current_other != other.head) {
        Node* new_node = new Node{ current_other->value, head, last };
        last->next = new_node;
        last = new_node;
        current_other = current_other->next;
    }
    head->prev = last;
}

void ListLinkedDouble::display(std::ostream& out) const {
    out << "[";
    if (head->next != head) {
        out << head->next->value;
        Node* current = head->next->next;
        while (current != head) {
            out << ", " << current->value;
            current = current->next;
        }
    }
    out << "]" << endl;
}

std::ostream& operator<<(std::ostream& out, const ListLinkedDouble& l) {
    l.display(out);
    return out;
}

// ===========================================================
// Escribe tu soluci�n por debajo de esta l�nea
// ===========================================================
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
// Implementa el m�todo pedido aqu�. No te olvides del coste.
void ListLinkedDouble::desparizar(ListLinkedDouble &other) {
    Node* current = head->next->next;
    Node* prev;

    while (current->prev != head) {
        prev = current->prev;
        if(prev->value % 2 == 0) {
            detach(prev);
            other.attach(prev, other.head->prev);
            num_elems--;
            other.num_elems++;
        }

        current = current->next;

    }
}



void tratar_caso() {
    int n, m, elem;
    cin >> n;
    ListLinkedDouble l1, l2;
    while (n != 0) {
        l1.push_back(n);
        cin >> n;
    }
    cin >> n;
    while (n != 0) {
        l2.push_back(n);
        cin >> n;
    }
    l1.desparizar(l2);

    l1.display(cout);
    l2.display(cout);

    cout << '\n';


    // Escribe aqu� el c�digo para leer de la entrada
    // un caso de prueba y procesarlo.
}


int main() {

#ifndef DOMJUDGE
    std::ifstream in("sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif


    int num_casos;
    std::cin >> num_casos;

    while (num_casos > 0) {
        tratar_caso();
        num_casos--;
    }

    // Comenta esto tambi�n si has comentado lo anterior.
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}