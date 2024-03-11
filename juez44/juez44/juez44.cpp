// juez44.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <map>
#include <set>
#include <fstream>
using namespace std;

bool resuelveCaso() {
    int numJug;
    cin >> numJug;
    if (numJug == 0) {
        return false;
    }
    else {
        map<string, set<int>> nom;
        map<int, set<string>> num;
        string nombre;
        int numero;
        for (int i = 0; i < numJug; i++) {
            cin >> nombre;
            cin >> numero;
            set<int>* aux = &nom[nombre];
            while (numero != 0) {
                (*aux).insert(numero);
                num[numero].insert(nombre);
                cin >> numero;
            }
        }
        bool fin = false;
        while (!fin) {
            cin >> numero;
            for (string jug : num[numero]) {
                set<int>* aux = &nom[jug];
                (*aux).erase(numero);
                if ((*aux).empty()) {
                    fin = true;
                    cout << jug << " ";
                }
            }
        }
        cout << "\n";
        return true;
    }
    
    
}

int main()
{
#ifndef DOMJUDGE
    std::ifstream in("datos.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
    std::ofstream out("datos.out");
    auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif
    while(resuelveCaso());
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
