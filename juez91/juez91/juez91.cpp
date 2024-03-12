// juez91.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

/*@ <answer> */

struct estado {
    int tiempo = 0; 
    int intentos = 0;
    string solucion = " ";
};

struct sol {
    string nombre = "";
    int resueltos = 0;
    int tiempo = 0;
    bool operator < (sol& s) {
        if (resueltos > s.resueltos || (resueltos == s.resueltos && tiempo < s.tiempo) || (resueltos == s.resueltos && tiempo == s.tiempo && nombre < s.nombre)) {
            return true;
        }
        else {
            return false;
        }
    }
};

void resuelveCaso() {
    string cadena;
    cin >> cadena;
    string nombre;
    int tiempo; 
    string state;
    unordered_map<string, map<string, estado>> map;
    while (cadena != "FIN") {
        cin >> nombre;
        cin >> tiempo;
        cin >> state;
        if (map[cadena][nombre].solucion != "AC") {
            if (state != "AC") {
                map[cadena][nombre].intentos += 1;
            }
            map[cadena][nombre].solucion = state;
            map[cadena][nombre].tiempo = tiempo;
        }
        cin >> cadena;
    }
    vector<sol> final;
    for (auto it = map.begin(); it != map.end(); ++it) {
        int resueltos = 0;
        int tiempo = 0; 
        for (auto it1 = (*it).second.begin(); it1 != (*it).second.end(); ++it1) {
            if ((*it1).second.solucion == "AC") {
                resueltos += 1;
                tiempo += (*it1).second.tiempo + (*it1).second.intentos * 20;
            }
        }
        final.push_back({ (*it).first, resueltos, tiempo });
    }
    sort(final.begin(), final.end());
    for (auto it = final.begin(); it != final.end(); it++) {
        cout << (*it).nombre << " " << (*it).resueltos << " " << (*it).tiempo << "\n";
    }
    cout << "---\n";
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
