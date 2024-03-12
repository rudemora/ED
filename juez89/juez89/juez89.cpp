// juez89.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <list>
#include <fstream>

using namespace std;

/*@ <answer> */

bool es_toeplitz(const list<list<int>>& matriz) {//se recorre dos veces cada fila - 1 (menos la primera y la ultima) 
    auto it = matriz.begin();
    int tamano = (*it).size();
    auto it1 = (*it).begin();
    while (++it != matriz.end()) {
        auto it2 = ++(*it).begin();
        for (int i = 0; i < tamano - 1; i++) {
            if ((*it1) != (*it2)) {
                return false;
            }
            else {
                it1++;
                it2++;
            }
        }
        it1 = (*it).begin();
        
    }
    return true;
}

bool resuelveCaso() {
    int fila;
    cin >> fila;
    if (fila == 0) {
        return false;
    }
    else {
        list<list<int>> lista;
        int col;
        while (fila != 0) {
            cin >> col;
            list<int> aux;
            aux.push_back(fila);
            while (col != 0) {
                aux.push_back(col);
                cin >> col;
            }
            lista.push_back(aux);
            cin >> fila;
        }
        bool sol = es_toeplitz(lista);
        if (sol) {
            cout << "SI";
        }
        else {
            cout << "NO";
        }
        cout << "\n";
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
