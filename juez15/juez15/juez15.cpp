// juez15.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <queue>
#include <fstream>

using namespace std;


/*@ <answer> */
void resolver(queue<int>& v, int& k) {
	int ultimo = 0;
	int contador = 0;
	while (!v.empty()) {
		if (contador < k) {
			v.push(v.front());
			ultimo = v.front();
			v.pop();
			contador += 1;
		}
		else {
			contador = 0;
			ultimo = v.front();
			v.pop();
		}
	}
	cout << ultimo << "\n";
}

bool resuelveCaso() {
	int N;
	int k;
	cin >> N >> k;
	if (N == 0 && k == 0) {
		return false;
	}
	else {
		queue<int> v;
		for (int i = 1; i < N + 1; i++) {
			v.push(i);
		}
		resolver(v, k);
		return true;
	}
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
