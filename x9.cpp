#include <iostream>
#include <fstream>
#include <cassert>
#include <map>
//TODO NO CONSIGO HACERLO
using namespace std;

class ListLinkedSingle {
public:
    ListLinkedSingle() : head(nullptr) {}
    bool tratar_caso();
    void  display();
    void push_front(const int &elem) {
        Node *new_node = new Node { elem, head };
        head = new_node;
    }
    void reverse_segment(int index, int length);
    void push_back(const int &elem);
    void pop_back();
    void pop_front();
// ...
private:
    struct Node {
        int value;
        Node *next;
    };
    Node *head;






};
void ListLinkedSingle::reverse_segment(int index, int length) {
    Node* current = head;
    Node* prev;
    int i = 0;
    while (current != nullptr && i < index){
        prev = current;
        current = current->next;
        i++;
    }
    Node *start = current;
    Node *next = nullptr;
    Node *prevSegmentEnd = prev; // Mantén un puntero al final del segmento anterior

    // Invierte el segmento
    while (current != nullptr && i < index + length) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
        i++;
    }

    // Conecta el segmento invertido con el segmento anterior (si lo hay)
    if (prevSegmentEnd != nullptr) {
        prevSegmentEnd->next = prev;
    } else {
        head = prev; // Si no hay segmento anterior, el segmento invertido comienza desde el principio de la lista
    }

    // Conecta el segmento invertido con el resto de la lista
    start->next = current;

}
void ListLinkedSingle::push_back(const int &elem) {
    Node *new_node = new Node { elem, nullptr };
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
bool ListLinkedSingle::tratar_caso() {
    ListLinkedSingle l1;
    int numElems, value, x1, x2;
    cin >> numElems;
    if(!cin) return false;
    cin >> x1 >> x2;

    for (int i = 0; i < numElems; ++i) {
        cin >> value;
        l1.push_back(value);
    }
    l1.reverse_segment(x1,x2);
    l1.display();

return true;
}
void ListLinkedSingle::display() {

    cout << "[";
    if (head != nullptr) {
        cout <<head->value;
        Node *current = head->next;
        while (current != nullptr) {
            cout << ", "  << current->value;
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








int main() {

#ifndef DOMJUDGE
    std::ifstream in("sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    int numero_casos;
    cin >> numero_casos;
    ListLinkedSingle l1;
// Llamamos a `tratar_caso` hasta que se agoten los casos de prueba
    while (l1.tratar_caso())

// Comenta esto también si has comentado lo anterior.
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}
/*
8 2 4
1 2 3 4 5 6 7 8
8 0 8
1 2 3 4 5 6 7 8
8 3 1
1 2 3 4 5 6 7 8

 */
