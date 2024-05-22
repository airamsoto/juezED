// Repetir elementos de una lista
// ------------------------------
// Estructuras de datos

#include <iostream>
#include <string>
#include <fstream>
#include <cassert>

using namespace std;

// Implementación del TAD lista utilizando listas enlazadas simples.

class ListLinkedSingle {
private:
    struct Node {
        int value;
        Node *next;
    };

public:
    ListLinkedSingle(): head(nullptr) { }
    ~ListLinkedSingle() {
        delete_list(head);
    }

    ListLinkedSingle(const ListLinkedSingle &other)
            : head(copy_nodes(other.head)) { }

    void push_front(const int &elem) {
        Node *new_node = new Node { elem, head };
        head = new_node;
    }

    void push_back(const int &elem);

    void pop_front() {
        assert (head != nullptr);
        Node *old_head = head;
        head = head->next;
        delete old_head;
    }

    void pop_back();

    int size() const;

    bool empty() const {
        return head == nullptr;
    };

    const int & front() const {
        assert (head != nullptr);
        return head->value;
    }

    int & front() {
        assert (head != nullptr);
        return head->value;
    }

    const int & back() const {
        return last_node()->value;
    }

    int & back() {
        return last_node()->value;
    }

    const int & at(int index) const {
        Node *result_node = nth_node(index);
        assert (result_node != nullptr);
        return result_node->value;
    }

    int & at(int index) {
        Node *result_node = nth_node(index);
        assert (result_node != nullptr);
        return result_node->value;
    }

    // La función está declarada aquí, pero se implementa
    // más abajo
    void replicate(const ListLinkedSingle &ys);

    void display(std::ostream &out) const;
    void display() const {
        display(std::cout);
    }

private:
    Node *head;

    void delete_list(Node *start_node);
    Node *last_node() const;
    Node *nth_node(int n) const;
    Node *copy_nodes(Node *start_node) const;

};

ListLinkedSingle::Node * ListLinkedSingle::copy_nodes(Node *start_node) const {
    if (start_node != nullptr) {
        Node *result = new Node { start_node->value, copy_nodes(start_node->next) };
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
    Node *new_node = new Node { elem, nullptr };
    if (head == nullptr) {
        head = new_node;
    } else {
        last_node()->next = new_node;
    }
}

void ListLinkedSingle::pop_back() {
    assert (head != nullptr);
    if (head->next == nullptr) {
        delete head;
        head = nullptr;
    } else {
        Node *previous = head;
        Node *current = head->next;

        while (current->next != nullptr) {
            previous = current;
            current = current->next;
        }

        delete current;
        previous->next = nullptr;
    }
}

int ListLinkedSingle::size() const {
    int num_nodes = 0;

    Node *current = head;
    while (current != nullptr) {
        num_nodes++;
        current = current->next;
    }

    return num_nodes;
}


ListLinkedSingle::Node * ListLinkedSingle::last_node() const {
    assert (head != nullptr);
    Node *current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    return current;
}

ListLinkedSingle::Node * ListLinkedSingle::nth_node(int n) const {
    assert (0 <= n);
    int current_index = 0;
    Node *current = head;

    while (current_index < n && current != nullptr) {
        current_index++;
        current = current->next;
    }

    return current;
}

void ListLinkedSingle::display(std::ostream &out) const {
    out << "[";
    if (head != nullptr) {
        out << head->value;
        Node *current = head->next;
        while (current != nullptr) {
            out << ", " << current->value;
            current = current->next;
        }
    }
    out << "]";
}


void ListLinkedSingle::replicate(const ListLinkedSingle &ys) {
    Node *current_xs = this->head;
    Node *current_ys = ys.head;
    Node *prev = nullptr;

    while (current_xs != nullptr && current_ys != nullptr) {
        int multiplicador = current_ys->value;

        if (multiplicador == 0) {
            if (prev == nullptr) {
                Node *temp = current_xs;
                head = current_xs->next;
                current_xs = current_xs->next;;
                delete temp;
            } else {
                Node *temp = current_xs;
                prev->next = current_xs->next;
                current_xs = current_xs->next;
                delete temp;
            }
        } else {
            prev = current_xs;
            Node *next = current_xs->next;
            for (int i = 1; i < multiplicador; ++i) {
                Node *new_node = new Node{current_xs->value, next};
                prev->next = new_node;
                prev = new_node;
            }
            current_xs = next;
        }

        current_ys = current_ys->next;
    }


}

void tratar_caso() {
    ListLinkedSingle xs, ys;
    int numElems, value;
    cin >> numElems;
    for (int i = 0; i < numElems; ++i) {
        cin >> value;
        xs.push_front(value);
    }
    for (int i = 0; i < numElems; ++i) {
        cin >> value;
        ys.push_front(value);
    }
    xs.replicate(ys);
    xs.display();
    cout << endl;
}



int main() {
#ifndef DOMJUDGE
std::ifstream in("sample.in");
auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif


int num_casos;
cin >> num_casos;

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

