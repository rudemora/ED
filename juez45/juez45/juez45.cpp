/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */

 /*@ <answer>

  Introduce el nombre y apellidos de los/as componentes del grupo:

  Estudiante 1: David Esparza Sainz
  Estudiante 2: Rubén de Mora Losada


  Dad una explicación de la solución y justificad su coste.

  Utilizamos un diccionario para guardar los deportes con el número de 
  jugadores de cada deporte. También utilizamos otro diccionario con clave
  el nombre de cada jugador y valor el deporte al que está jugando. Como necesitamos
  devolver una lista de deportes con el numero de jugadores de cada uno de mayor a menor
  hemos sobrecargado el operador menor que utiliza la función sort para poder ordenarlo
  de la manera adecuada. Si el deporte es jugado por un jugador que ya juega a ese deporte, 
  entonces no lo contamos. Si queremos que un jugador juegue a un deporte distinto al que ya juega
  utilizamos la palabra "centinela"  para recordar que ese jugador ha estado en varios deportes y nunca deberemos
  volver a contarlo.

  Por utilizar unordered_map, el coste amoritazado de acceso a cada elemento es constante
  al igual que la inserción. Por tanto, el coste de la función es mlogm siendo n
  el numero de deportes jugados y m el numero de jugadores por utilizar el sort de algorithm, asumiendo que el número de participantes por cada 
  depores es relativamente pequeño.

  @ </answer> */

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <algorithm>
#include <vector>
using namespace std;

struct tipo {
	string deporte;
	int numero;
};

// Implementa a continuación la función que resuelve un caso de
// prueba. Puedes utilizar otras funciones auxiliares, pon su
// implementación debajo de la etiqueta <answer>.
//@ <answer>

bool operator< (tipo& t1, tipo& t2) {
	if (t1.numero > t2.numero) {
		return true;
	}
	else if (t1.numero == t2.numero && t1.deporte <= t2.deporte) {
		return true;
	}
	else {
		return false;
	}
}

bool resuelveCaso() {
	string cadena; 
	cin >> cadena;
	if (!cin) {
		return false;
	}
	else {
		unordered_map<string, int> unmap;
		unordered_map<string, string> unmap1;
		string deporte;
		while (cadena != "_FIN_") {
			if (cadena[0] <= 'Z' && cadena[0] >= 'A') {
				deporte = cadena;
				unmap[deporte] = 0;
			}
			else {
				if (unmap1.count(cadena)) {
					string aux = unmap1[cadena];
					if (aux == "centinela") {

					}
					else {
						if (unmap1[cadena] == deporte) {

						}
						else {
							unmap[aux] -= 1;
							unmap1[cadena] = "centinela";
						}
						
					}
				}
				else {
					unmap1[cadena] = deporte;
					unmap[deporte] += 1;
				}
			}
			cin >> cadena;
		}

		vector<tipo> vect;
		for (auto it = unmap.begin(); it != unmap.end(); it++) {
			vect.push_back({ (*it).first, (*it).second } );
		}
		sort(vect.begin(), vect.end());
		for (auto i = vect.begin(); i < vect.end(); i++) {
			cout << (*i).deporte << " " <<  (*i).numero << "\n";
		}
		cout << "---\n";
	}

	return true;
}




//@ </answer>
// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------

int main() {
	
#ifndef DOMJUDGE
	std::ifstream in("datos.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());
	
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	// Descomentar si se trabaja en Visual Studio
	// system("PAUSE");
#endif
	return 0;
}
