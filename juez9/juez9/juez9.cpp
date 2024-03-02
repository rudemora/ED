/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */

 /*
  * MUY IMPORTANTE: Solo se corregirán los comentarios y el código
  * contenidos entre las etiquetas <answer> y </answer>.
  * Toda modificación fuera de esas etiquetas no será corregida.
  */

  /*@ <answer>
   *  Estudiante 1: David Esparza Sainz
   *  Estudiante 2: Rubén de Mora Losada
   *@ </answer> */

   /*
    * Implementa las operaciones pedidas en el ejercicio al final de
    * este fichero, entre las etiquetas.
    */

#include <iostream>
#include <cassert>
#include <fstream>


class ListLinkedSingle {
private:
    struct Node {
        int value;
        Node* next;
    };

public:
    ListLinkedSingle() : head(nullptr) { }
    ~ListLinkedSingle() {
        delete_list(head);
    }

    ListLinkedSingle(const ListLinkedSingle& other)
        : head(copy_nodes(other.head)) { }

    void push_front(const int& elem) {
        Node* new_node = new Node{ elem, head };
        head = new_node;
    }

    void push_back(const int& elem);

    void pop_front() {
        assert(head != nullptr);
        Node* old_head = head;
        head = head->next;
        delete old_head;
    }

    void pop_back();

    int size() const;

    bool empty() const {
        return head == nullptr;
    };

    const int& front() const {
        assert(head != nullptr);
        return head->value;
    }

    int& front() {
        assert(head != nullptr);
        return head->value;
    }

    const int& back() const {
        return last_node()->value;
    }

    int& back() {
        return last_node()->value;
    }

    const int& at(int index) const {
        Node* result_node = nth_node(index);
        assert(result_node != nullptr);
        return result_node->value;
    }

    int& at(int index) {
        Node* result_node = nth_node(index);
        assert(result_node != nullptr);
        return result_node->value;
    }

    void display(std::ostream& out) const;
    void display() const {
        display(std::cout);
    }

    // Nuevo método. Debe implementarse abajo
    void merge(ListLinkedSingle& l2);

private:
    Node* head;

    void delete_list(Node* start_node);
    Node* last_node() const;
    Node* nth_node(int n) const;
    Node* copy_nodes(Node* start_node) const;

};

ListLinkedSingle::Node* ListLinkedSingle::copy_nodes(Node* start_node) const {
    if (start_node != nullptr) {
        Node* result = new Node{ start_node->value, copy_nodes(start_node->next) };
        return result;
    }
    else {
        return nullptr;
    }
}

void ListLinkedSingle::delete_list(Node* start_node) {
    if (start_node != nullptr) {
        delete_list(start_node->next);
        delete start_node;
    }
}

void ListLinkedSingle::push_back(const int& elem) {
    Node* new_node = new Node{ elem, nullptr };
    if (head == nullptr) {
        head = new_node;
    }
    else {
        last_node()->next = new_node;
    }
}

void ListLinkedSingle::pop_back() {
    assert(head != nullptr);
    if (head->next == nullptr) {
        delete head;
        head = nullptr;
    }
    else {
        Node* previous = head;
        Node* current = head->next;

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

    Node* current = head;
    while (current != nullptr) {
        num_nodes++;
        current = current->next;
    }

    return num_nodes;
}


ListLinkedSingle::Node* ListLinkedSingle::last_node() const {
    assert(head != nullptr);
    Node* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    return current;
}

ListLinkedSingle::Node* ListLinkedSingle::nth_node(int n) const {
    assert(0 <= n);
    int current_index = 0;
    Node* current = head;

    while (current_index < n && current != nullptr) {
        current_index++;
        current = current->next;
    }

    return current;
}

void ListLinkedSingle::display(std::ostream& out) const {
    out << "[";
    if (head != nullptr) {
        out << head->value;
        Node* current = head->next;
        while (current != nullptr) {
            out << ", " << current->value;
            current = current->next;
        }
    }
    out << "]";
}

// ----------------------------------------------------------------
// ¡No modificar nada por encima de esta línea!

// Implementa a continuación el método pedido.
//@ <answer>

void ListLinkedSingle::merge(ListLinkedSingle& l2) {
    Node* c1 = head;
    Node* c2 = l2.head;
    Node* pos = c1;
    if (c1 == nullptr) {//ESTOS CASOS BASES SOBRAN LA MAYORIA MIRAR LOS DE ENTRAMAR DOS LISTAS DOBLEMENTE ENLAZADAS
        if (c2 != nullptr) {
            head = c2;
            pos = c2;
            c2 = c2->next;
            while (c2 != nullptr) {

                pos->next = c2;
                pos = c2;
                c2 = c2->next;
            }
        }

    }
    if (c2 == nullptr) {
        if (c1 != nullptr) {
            c1 = c1->next;
            while (c1 != nullptr) {
                pos->next = c1;
                pos = c1;
                c1 = c1->next;
            }
        }

    }
    if (c1 != nullptr && c2 != nullptr) {
        if (c1->value < c2->value) {
            this->head = c1;

            pos = c1;
            c1 = c1->next;
        }
        else {
            this->head = c2;
            pos = c2;
            c2 = c2->next;
        }
        while (c1 != nullptr && c2 != nullptr) {
            if (c1->value <= c2->value) {
                pos->next = c1;
                pos = c1;
                c1 = c1->next;
            }
            else {
                pos->next = c2;
                pos = c2;
                c2 = c2->next;
            }
        }
        if (c1 != nullptr) {
            while (c1 != nullptr) {
                pos->next = c1;
                pos = c1;
                c1 = c1->next;
            }
        }

        else if (c2 != nullptr) {
            while (c2 != nullptr) {
                pos->next = c2;
                pos = c2;
                c2 = c2->next;
            }
        }
    }


    l2.head = nullptr;
}

// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------

using namespace std;

ListLinkedSingle leerLista() {
    ListLinkedSingle lista;
    int n;
    std::cin >> n;
    while (n != 0) {
        lista.push_back(n);
        std::cin >> n;
    }
    return lista;
}

void resuelveCaso() {
    auto lista1 = leerLista();
    auto lista2 = leerLista();

    lista1.merge(lista2);
    lista1.display(); cout << '\n';
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("datos.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
    std::ofstream out("datos.out");
    auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif

    // Leemos el número de casos de prueba que vendrán a continuación
    int num_casos;
    cin >> num_casos;

    for (int i = 0; i < num_casos; i++) {
        resuelveCaso();
    }

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    std::cout.rdbuf(coutbuf);
    system("PAUSE");
#endif
    return 0;
    return 0;
}
