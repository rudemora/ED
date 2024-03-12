// juez53.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <algorithm>
#include <fstream>
#include <list>
using namespace std;


/*@ <answer> */

class Oficina {
private:
	unordered_map<string, unordered_map<string, list<string>::iterator>> unmap;
	unordered_map<string, list<string>> empleos;
public:

	Oficina() : unmap(), empleos() {};

	void altaOficina(string nombre, string puesto) {
		auto it = unmap.find(nombre);
		if (it == unmap.end()) {
			empleos[puesto].push_front(nombre);
			unmap[nombre].insert({ puesto, empleos[puesto].begin() });
		}
		else {
			auto aux = it->second.find(puesto);
			if (aux == it->second.end()) {
				empleos[puesto].push_front(nombre);																																						
				unmap[nombre].insert({ puesto, empleos[puesto].begin() });
			}
		}

	}
	vector<string> listadoEmpleos(string nombre) {
		vector<string> sol;
		auto it = unmap.find(nombre);
		if (it == unmap.end()) {
			throw(domain_error("Persona inexistente"));
		}
		else {
			for (auto it1 = it->second.begin(); it1 != it->second.end(); it1++) {
				sol.push_back((*it1).first);
			}
			return sol;
		}
	}
	string ofertaEmpleo(string empleo) {
		auto it = empleos.find(empleo);
		if (it == empleos.end()) {
			throw(domain_error("No existen personas apuntadas a este empleo")); 
		}
		else {
			string sol = it->second.back();
			for (auto it1 = unmap[sol].begin(); it1 != unmap[sol].end(); it1++) {
				empleos[it1->first].erase(it1->second);
				if (empleos[it1->first].empty()) {
					empleos.erase(it1->first);
				}
			}
			unmap.erase(sol);
			return sol;
		}
	}
};

bool resuelveCaso() {
	string orden;
	cin >> orden;
	if (!cin) {
		return false;
	}
	else {
		Oficina oficina;
		while (orden != "FIN") {
			string nombre;
			string puesto;
			try {
				if (orden == "altaOficina") {
					cin >> nombre;
					cin >> puesto;
					oficina.altaOficina(nombre, puesto);
				}
				else if (orden == "listadoEmpleos") {
					cin >> nombre;
					vector<string> sol = oficina.listadoEmpleos(nombre);
					sort(sol.begin(), sol.end());
					cout << nombre << ": ";
					for (int i = 0; i < sol.size(); i++){
						cout << sol[i] << " ";
					}
					cout << "\n";

				}
				else if (orden == "ofertaEmpleo") {
					cin >> puesto;
					string sol = oficina.ofertaEmpleo(puesto);
					cout << puesto << ": " << sol << "\n";

				}
			}
			catch (exception& e) {
				cout << "ERROR: " << e.what() << "\n";
			}
			
			cin >> orden;
		}
		cout << "---\n";
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
