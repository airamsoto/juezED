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
    void add_to(int index, int val);


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

std::ostream &operator<<(std::ostream &out, const ListLinkedDouble &l) {
    l.display(out);
    return out;
}


// No olvides el coste!
void ListLinkedDouble::attach(Node *node, Node *before) {
    // Implementar
}

// No olvides el coste!
void ListLinkedDouble::detach(Node *current) {
    current->prev->next = current->next;
    current->next->prev = current->prev;

}


void ListLinkedDouble::add_to(int index, int val) {
    assert(index >= 0 && index < num_elems);

    Node* current = head->next;
    for (int i = 0; i < index; ++i) {
        current = current->next;
    }
    current->value += val;
    Node* temp = current;
    int updated_value = current->value;
    current->prev->next = current->next;
    current->next->prev = current->prev;
    Node* aux = head->next;



    while (aux != head && aux->value < updated_value) {
        aux = aux->next;
    }
    temp->next = aux;
    temp->prev = aux->prev;
    aux->prev->next = temp;
    aux->prev = temp;
}




bool tratar_caso() {
    // Introduce aquí el código para tratar un caso de prueba.
    // Devuelve false si se ha leído la marca de fin de entrada;
    // true en caso contrario.
    int tamanio, indice, suma;
    cin >> tamanio >> indice >> suma;
    if (tamanio == 0 && indice == 0 && suma == 0) return false;
    ListLinkedDouble l1;
    int aux;
    for (int i = 0; i < tamanio; ++i) {
        cin >> aux;
        l1.push_back(aux);
    }
    if(suma != 0)
    l1.add_to(indice, suma);
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