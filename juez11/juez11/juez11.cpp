// juez11.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <fstream>
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
    void zip(ListLinkedDouble list2);
    void display();
};

/*@ <answer> */

void ListLinkedDouble::zip(ListLinkedDouble list2) { // lineal respecto a la longitud de la mínima longitud de la lista
    if (num_elems > 0 && list2.num_elems > 0) {
        Node* current1 = head->next;
        Node* current2 = list2.head->next;
        while (current1 != head && current2 != list2.head) {
            Node* aux1 = current1;
            Node* aux2 = current2;
            current1 = current1->next;
            current2 = current2->next;
            aux2->next->prev = aux2->prev;
            aux2->prev->next = aux2->next;
            aux2->next = aux1->next;
            aux1->next->prev = aux2;
            aux2->prev = aux1;
            aux1->next = aux2;
        }
        if (current2 != list2.head) {
            head->prev->next = list2.head->next;
            list2.head->next->prev = head->next;
            list2.head->prev->next = head;
            head->prev = list2.head->prev;
        }

        
    }
    else if (list2.num_elems > 0) {
        head = list2.head;
        head->prev = list2.head->prev;
        head->next = list2.head->next;
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
    ListLinkedDouble list1;
    ListLinkedDouble list2;
    int elemento;
    for (int i = 0; i < longitud; i++) {
        cin >> elemento;
        list1.push_back(elemento);
    }
    cin >> longitud;
    for (int i = 0; i < longitud; i++) {
        cin >> elemento;
        list2.push_back(elemento);
    }
    list1.zip(list2);
    list1.display();
    return true;
    
}

int main()
{
#ifndef DOMJUDGE
    std::ifstream in("datos.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
    std::ofstream out("datos.out");
    auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif
    int numCasos;
    cin >> numCasos;
    for (int i = 0; i < numCasos; i++) {
        resuelveCaso();
    }
    
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
