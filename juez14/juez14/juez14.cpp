// juez14.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <string>
#include <stack>
#include <fstream>

using namespace std;

/*@ <answer> */

void resolver(string cadena) {
    stack<char> pila;
    int i = 0;
    bool valid = true;
    while (i < cadena.length() && valid) {
        if (cadena[i] == '[' || cadena[i] == '{' || cadena[i] == '(') {
            pila.push(cadena[i]);
        }
        else if (cadena[i] == ']') {
            if (pila.empty() || pila.top() != '[') {
                valid = false;
            }
            else {
                pila.pop();
            }
        }
        else if (cadena[i] == '}') {
            if (pila.empty() || pila.top() != '{') {
                valid = false;
            }
            else {
                pila.pop();
            }
        }
        else if (cadena[i] == ')') {
            if (pila.empty() || pila.top() != '(') {
                valid = false;
            }
            else {
                pila.pop();
            }
        }
        i++;
    }
    if (valid && pila.empty()) {
        cout << "SI\n";
    }
    else {
        cout << "NO\n";
    }
}

bool resuelveCaso() {
    string cadena;
    getline(cin, cadena);
    if (!cin) {
        return false;
    }
    resolver(cadena);
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
