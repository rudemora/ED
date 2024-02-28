// juez6.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <cassert>
#include <fstream>

/*@ <answer> */
using namespace std;

class ListLinkedSingle {
private:
	struct Node {
		int value;
		Node* next;
	};
	Node* head;

public:
	ListLinkedSingle() : head(nullptr) {}
	void duplicate();
	void push_back(int num);
	void display();

};

void ListLinkedSingle::duplicate() { // coste lineal respecto a la longitud de la lista
	if (head != nullptr) {
		Node* current = head;
		while (current->next != nullptr) {
			current->next = new Node{ current->value, current->next };
			current = current->next->next;
		}
		current->next = new Node{ current->value, nullptr };
	}
}

void ListLinkedSingle::push_back(int num) {
	Node* newNode = new Node{ num, nullptr };
	if (head == nullptr) {
		head = newNode;
	}
	else {
		Node* current = head;
		while (current->next != nullptr) {
			current = current->next;
		}
		current->next = newNode;
	}
}

void ListLinkedSingle::display() {
	cout << "[";
	if (head != nullptr) {
		cout << head->value;
		Node* current = head->next;
		while (current != nullptr) {
			cout << ", " << current->value;
			current = current->next;
		}
	}
	cout << "]\n";
}

void resuelveCaso() {
	int num;
	cin >> num;
	ListLinkedSingle listLinked;
	while (num != 0) {
		listLinked.push_back(num);
		cin >> num;
	}
	listLinked.duplicate();
	listLinked.display();
}

/*@ </answer> */

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
