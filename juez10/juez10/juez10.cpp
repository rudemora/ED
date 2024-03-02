// juez10.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <fstream>

using namespace std;

class ListLinkedDouble {
private:
    struct Node {
        int value;
        Node* next;
        Node* prev;
    };
    Node* head;
    int num_elems;
public:


    ListLinkedDouble() : num_elems(0) {
        head = new Node;
        head->next = head;
        head->prev = head;
    }

    void push_back(int elemento);
    void swap2by2();
    void display();
};

/*@ <answer> */

void ListLinkedDouble::swap2by2() { // lineal respecto a la longitud de la lista
    Node* current = head->next;
    Node* next = nullptr;
    Node* aux = nullptr;
    while (current->next != head && current != head) {
        aux = current;
        next = current->next;
        current = next->next;
        if (aux == head->next) {
            aux->prev = next;
            aux->next = next->next;
            next->next->prev = aux;
            next->next = aux;
            head->next = next;
            next->prev = head;
        }
        else {
            aux->prev->next = next;
            next->prev = aux->prev;
            aux->prev = next;
            aux->next = next->next;
            next->next->prev = aux;
            next->next = aux;

        }
    }
}

/*@ </answer> */

void ListLinkedDouble::push_back(int elemento) {
    Node* newNode = new Node{ elemento, head, head->prev };
    head->prev->next = newNode;
    head->prev = newNode;
    num_elems++;
}

void ListLinkedDouble::display() {
    Node* current = head->next;
    cout << "[";
    if (current != head) {
        cout << current->value;
        current = current->next;
    }
    while (current != head) {
        cout << ", " << current->value;
        current = current->next;
    }
    cout << "]\n";
}

bool resuelveCaso() {
    int longitud;
    cin >> longitud;
    if (longitud == 0) {
        return false;
    }
    else {
        ListLinkedDouble list;
        int elemento;
        for (int i = 0; i < longitud; i++) {
            cin >> elemento;
            list.push_back(elemento);
        }
        list.swap2by2();
        list.display();
        return true;
    }
}

int main()
{
#ifndef DOMJUDGE
    std::ifstream in("datos.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
    std::ofstream out("datos.out");
    auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif
    while (resuelveCaso());

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    std::cout.rdbuf(coutbuf);
    system("PAUSE");
#endif
    return 0;
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
