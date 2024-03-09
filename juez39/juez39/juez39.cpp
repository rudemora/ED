// juez39.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <map>
#include <string>
#include <fstream>

using namespace std;

/*@ <answer> */

void resuelve(map<string, int> map, int num) {
    string nombre;
    string estado;
    cin.ignore(1);
    for (int i = 0; i < num; i++) {
        getline(cin, nombre);
        getline(cin, estado);
        if (estado == "CORRECTO") {
            map[nombre] += 1;
        }
        else {
            map[nombre] -= 1;
        }
    }
    for (auto it = map.begin(); it != map.end(); it++) {
        if ((*it).second != 0) {
            cout << (*it).first << ", " << (*it).second << "\n";
        }
    }
}

bool resuelveCaso() {
    int num;
    cin >> num;
    if (num == 0) {
        return false;
    }
    else {
        map<string, int> map;
        resuelve(map, num);
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
