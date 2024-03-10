// juez43.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <unordered_map>
#include <fstream>

using namespace std;

/*@ <answer> */


void resuelveCaso() {
    int numCap;
    cin >> numCap;
    int max = 0;
    int actual = 0;
    unordered_map<int,int> map;
    int num;
    for (int i = 1; i < numCap + 1; i++) {
        cin >> num;
        int* dia = &map[num];
        if (*dia != 0) {
            if (max < actual) {
                max = actual;
            }
            actual = min(i - *dia, actual + 1);
        }
        else{    
            actual += 1;
        }
        *dia = i;
    }
    if (actual > max) {
        max = actual;
    }
    std::cout << max << "\n";
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
