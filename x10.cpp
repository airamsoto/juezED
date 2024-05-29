#include <iostream>
#include <fstream>
#include <cassert>
#include <map>
//TODO NO CONSIGO HACERLO
using namespace std;

class ListLinkedSingle {
public:
    ListLinkedSingle() : head(nullptr) {}

    void tratar_caso();

    void display();

    void push_front(const int &elem) {
        Node *new_node = new Node{elem, head};
        head = new_node;
    }
// ...
private:
    struct Node {
        int value;
        Node *next;
    };
    Node *head;

    void escamochar(ListLinkedSingle &dest);

    void push_back(const int &elem);

    void pop_back();

    void pop_front();


};

void ListLinkedSingle::push_back(const int &elem) {
    Node *new_node = new Node{elem, nullptr};
    if (head == nullptr) {
        head = new_node;
    } else {
        Node *current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = new_node;
    }
}

void ListLinkedSingle::tratar_caso() {
    ListLinkedSingle l1, l2;
    int numElems, value;
    cin >> numElems;
    for (int i = 0; i < numElems; ++i) {
        cin >> value;
        l1.push_front(value);
    }
    l1.escamochar(l2);
    l1.display();
    l2.display();


}

void ListLinkedSingle::display() {

    cout << "[";
    if (head != nullptr) {
        cout << head->value;
        Node *current = head->next;
        while (current != nullptr) {
            cout << ", " << current->value;
            current = current->next;
        }
    }
    cout << "]" << endl;
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


void ListLinkedSingle::pop_front() {
    assert (head != nullptr);
    Node *old_head = head;
    head = head->next;
    delete old_head;
}
//TODO METER EN DEST SIN PUSH Y ELIMINAR DE THIS SIN POP

void ListLinkedSingle::escamochar(ListLinkedSingle &dest) {
    if (head == nullptr) {
        return;
    }

    Node* current = head;
    Node* prev = nullptr;

    while (current != nullptr && current->value < 0) {
        if (prev != nullptr) {
            prev->next = current->next;
        } else {
            head = current->next;
        }
        current->next = nullptr;
        if (dest.head == nullptr) {
            dest.head = current;
        } else {
            Node* temp = dest.head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = current;
        }
        current = (prev != nullptr) ? prev->next : head;
    }
    if (current == nullptr) {
        return;
    }
    Node* first_non_negative = current;
    Node* last_non_negative = nullptr;
    while (current != nullptr) {
        if (current->value >= 0) {
            last_non_negative = current;
        }
        current = current->next;
    }

    if (last_non_negative != nullptr) {
        current = last_non_negative->next;
        last_non_negative->next = nullptr;
        while (current != nullptr) {
            Node* next = current->next;
            current->next = nullptr;
            if (dest.head == nullptr) {
                dest.head = current;
            } else {
                Node* temp = dest.head;
                while (temp->next != nullptr) {
                    temp = temp->next;
                }
                temp->next = current;
            }
            current = next;
        }
    }
    head = first_non_negative;
}



int main() {

#ifndef DOMJUDGE
    std::ifstream in("sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    int numero_casos;
    cin >> numero_casos;
    ListLinkedSingle l1;
// Llamamos a `tratar_caso` hasta que se agoten los casos de prueba
    for (int i = 0; i < numero_casos; i++) {
        l1.tratar_caso();

    }

// Comenta esto también si has comentado lo anterior.
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}
/*
4
7
-1 2 -2 -2 -3 -3 4
4
-1 2 -5 3
5
1 -21 -5 -13 2
2
-10 -4

 */
/*
 * 4
7
-1 7 -2 4 1 -5 -3
4
-1 2 -5 3
5
1 -21 -5 -13 2
2
-10 -4
 */
