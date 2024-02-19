// juez3.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>

/*@ <answer> */
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
			return false;
		}
		else {
			return false;
		}
	}

	bool operator == (Hora& hora) {
		if (horas == hora.horas && minutos == hora.minutos && segundos == hora.segundos) {
			return true;
		}
		else {
			return false;
		}
	}

	void operator + (Hora& hora) {
		int segundos = this->segundos + hora.segundos;
		this->segundos = (segundos)%60;
		int minutos = this->minutos + hora.minutos + (segundos / 60);
		this->minutos = (minutos)%60;
		int horas = this->horas + hora.horas + (minutos / 60);
		this->horas = (horas)%24;
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
	std::cout << setfill('0') << setw(2) << hora.horas << ":" << setw(2) << hora.minutos << ":" << setw(2) << hora.segundos;
	return os;
}


class Pelicula {

	Hora inicio;
	Hora fin;
	string nombre;
	
    public:
		Pelicula() {

		}

		Pelicula(Hora inicio, Hora fin, string nombre) {
			this->inicio = inicio;
			this->fin = fin;
			this->nombre = nombre;
		}
		void sumar() {
			inicio + fin;
		}

		friend istream& operator >> (istream& is, Pelicula& pelicula);
		friend ostream& operator << (ostream& os, Pelicula& pelicula);

		bool operator < (Pelicula& peli) {
			if (inicio < peli.inicio) {
				return true;
			}
			else if (inicio == peli.inicio) {
				if (nombre < peli.nombre) {
					return true;
				}
			}
			return false;
			
		}
};

istream& operator >> (istream& is, Pelicula& pelicula) {
	string input;
	cin >> input;
	int h = stoi(input.substr(0, 2));
	int min = stoi(input.substr(3, 5));
	int seg = stoi(input.substr(6, 8));
	pelicula.inicio = Hora(h, min, seg);
	cin >> input;
	h = stoi(input.substr(0, 2));
	min = stoi(input.substr(3, 5));
	seg = stoi(input.substr(6, 8));
	pelicula.fin = Hora(h, min, seg);
	cin.ignore();
	getline(cin, input);
	pelicula.nombre = input;
	return is;
}

ostream& operator << (ostream& os, Pelicula& pelicula) {
	cout << pelicula.inicio << " " << pelicula.nombre << "\n";
	return os;
}


bool resuelveCaso() {
	int pelis;
	cin >> pelis;
	if (pelis == 0) {
		return false;
	}
	vector <Pelicula> v(pelis);
	for (int i = 0; i < pelis; i++) {
		cin >> v[i];
	}		

	for (int i = 0; i < v.size(); i++) {
		v[i].sumar();
	}
	sort(v.begin(), v.end());
	for (int i = 0; i < v.size(); i++) {
		cout << v[i];
	}
	cout << "---\n";
	return true;
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
