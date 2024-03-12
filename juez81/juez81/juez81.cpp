// juez81.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <queue>
#include <fstream>

/*@ <answer> */

using namespace std;

void resolver(int& N, int& M, int& T) {
	int numHongos = 0;
	queue<pair<int,int>> hongos; //primero las horas
	queue<pair<int,int>> yemas; //segundos el numero con esas horas
	int tiempo = N;
	hongos.push({ N, 1 });
	int n1, n2;
	while (tiempo <= T) {
		n1 = 0;
		n2 = 0;
		if (hongos.front().first == tiempo) {
			n1 = hongos.front().second;
			hongos.pop();
			
		}
		if ( !yemas.empty() && yemas.front().first == tiempo) {
			n2 = yemas.front().second;
			yemas.pop();
		}
		yemas.push({M + tiempo, n1 + n2 });
		hongos.push({ N + tiempo, n1 + n2 });	
		tiempo += 1;
	}
	while (!hongos.empty()) {
		numHongos += hongos.front().second;
		
		hongos.pop();
		
	}
	while (!yemas.empty()) {
		numHongos += yemas.front().second;
		yemas.pop();
	}
	cout << numHongos << "\n";
}

bool resuelveCaso() {
	int N, M, T;
	cin >> N >> M >> T;
	if (!cin) {
		return false;
	}
	else {
		resolver(N, M, T);
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
