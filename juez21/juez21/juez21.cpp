// juez21.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <list>
#include <fstream>

using namespace std;


/*@ <answer> */
void resolver(string& lista) {
    list<char> resultado;
    auto it = lista.begin();
    auto aux = resultado.begin();
    while (it != lista.end()) {
        if (*it == '-') {
            aux = resultado.begin();
        }
        else if (*it == '+') {
            aux = resultado.end();
        }
        else if (*it == '*') {
            if (aux != resultado.end()) {
                aux++;
            }
        }
        else if (*it == '3') {
            if (aux != resultado.end()) {
                aux = resultado.erase(aux);
            }
        }
        else {
            resultado.insert(aux, *it);
        }
        ++it;
    }
    for (auto it = resultado.begin(); it != resultado.end(); it++) {
        cout << *it;
    }
    cout << endl;
}

bool resuelveCaso() {
    string cadena;
    cin >> cadena;
    if (!cin) {
        return false;
    }
    else {
       resolver(cadena);
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
