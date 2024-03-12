// juez80.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <deque>
#include <stack>
#include <sstream>
#include <fstream>

using namespace std;

/*@ <answer> */
void resolver(stringstream& cadena) {

	deque<string> cola;
	stack<bool> pila;
	stack<string> eliminadas;
	string palabra;

	while (cadena >> palabra) {
		if (palabra == "*") {
			if (!cola.empty()) {
				eliminadas.push(cola.back());
				cola.pop_back();
				pila.push(false); //true cuando hacemos delete
			}
		}
		else if (palabra == "+") {
			if (!pila.empty()) {
				if (pila.top()) {//hacer un delete
					cola.pop_back();				
				}
				else {
					if (!eliminadas.empty()) {// escribir lo deshecho
						cola.push_back(eliminadas.top());
						eliminadas.pop();
					}
				}
				pila.pop();
			}
			
		}		
		else {
			pila.push(true); // true cuando escribimos
			cola.push_back(palabra);
		}
	}
	while (!cola.empty()) {
		cout << cola.front() << " ";
		cola.pop_front();
	}
	cout << "\n";
}


void resuelveCaso() {
	string cadena;
	getline(cin, cadena);
	stringstream entrada(cadena);
	resolver(entrada);
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
	char aux;
	cin.get(aux);
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
