// juez88.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <map>
#include <vector>
#include <fstream>

using namespace std;

/*@ <answer> */

void resolver( map<string, vector<int>> map, int num) {
	int dia;
	string juego;
	for (int i = 0; i < num; i++) {
		cin >> dia;
		cin >> juego;
		if (map.count(juego) && map[juego].size() > dia - 1) {
			cout << map[juego][dia - 1] << "\n";
		}
		else {
			cout << "NO JUEGA\n";
		}
		
	}
	cout << "---\n";
}

bool resuelveCaso() {
	int num;
	cin >> num;
	if (!cin) {
		return false;
	}
	else {
		map<string, vector<int>> map;
		string juego;
		for (int i = 0; i < num; i++) {
			cin >> juego;
			map[juego].push_back(i + 1);
		}
		int preguntas;
		cin >> preguntas;
		resolver(map, preguntas);
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
