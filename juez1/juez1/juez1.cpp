// juez1.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>

//@ <answer>
using namespace std;

class Hora {
	int horas;
	int minutos;
	int segundos;
	public:
		Hora() {
			this->horas = 0;
			this->minutos = 0;
			this->segundos = 0;
		}
		Hora(int hora, int minuto, int segundo) {
			this->horas = hora;
			this->minutos = minuto;
			this->segundos = segundo;
		}
		friend istream& operator >> (istream& is, Hora& hora);
		friend ostream& operator << (ostream& os, Hora& hora);
		bool operator < (Hora& hora) {
			if (this->horas < hora.horas) {
				return true;
			}
			else if (this->horas == hora.horas && this->minutos < hora.minutos) {
				return true;
			}
			else if (this->horas == hora.horas && this->minutos == hora.minutos && this->segundos < hora.segundos) {
				return true;
			}
			else if (this->horas == hora.horas && this->minutos == hora.minutos && this->segundos == hora.segundos) {
				return true;
			}
			else {
				return false;
			}
		}
};

istream& operator >> (istream& is, Hora& hora) {
	string input;
	cin >> input;
	int h = stoi(input.substr(0, 2));
	int min = stoi(input.substr(3, 5));
	int seg = stoi(input.substr(6, 8));
	hora = Hora(h, min, seg);
	return is;
}

ostream& operator << (ostream& os, Hora& hora) {
	std::cout << setfill('0') << setw(2) << hora.horas << ":" << setw(2) << hora.minutos << ":" << setw(2) << hora.segundos << "\n";
	return os;
}

int resolver(vector<Hora>& v, Hora& hora, int ini, int fin) {
	if (ini + 1 > fin) {
		if (hora < v[fin]) {
			return fin;
		}
		else {
			return -1;
		}
	}
	else {
		int medio = (ini + fin - 1) / 2;
		if (hora < v[medio]) {
			return resolver(v, hora, ini, medio);
		}
		else {
			return resolver(v, hora, medio + 1, fin);
		}
	}
}

bool resuelveCaso() {
	int trenes;
	int horas;
	cin >> trenes >> horas;
	if (trenes == 0 && horas == 0) {
		return false;
	}
	else {
		vector<Hora> v(trenes);
		for (int i = 0; i < trenes; i++) {
			cin >> v[i];
		}
		string horaIn;
		for (int i = 0; i < horas; i++) {
			cin >> horaIn;
			int h = stoi(horaIn.substr(0, 2));
			int min = stoi(horaIn.substr(3, 5));
			int seg = stoi(horaIn.substr(6, 8));
			Hora hora(h, min, seg);
			int sol = resolver(v, hora, 0, trenes - 1);
			if (sol == -1) {
				cout << "NO\n";
			}
			else {
				cout << v[sol];
			}
		}
		cout << "---\n";
		return true;
	}
}
//@ <answer>

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
