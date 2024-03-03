// juez17.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <fstream>

using namespace std;

/*@ <answer> */

bool isVowel(char vowel) {
    return tolower(vowel) == 'a' || tolower(vowel) == 'e' || tolower(vowel) == 'i' || tolower(vowel) == 'o' || tolower(vowel) == 'u';
}

void resolverConsonantes(queue<char>& cola, stack<char> pila) {
    stack<char> aux;
    string sol;
    while (!cola.empty()) {
        if (isVowel(cola.front())) {
            while (!aux.empty()) {
                sol.push_back(aux.top());
                aux.pop();
            }
            sol.push_back(cola.front());
            cola.pop();
        }
        else {
            aux.push(cola.front());
            cola.pop();
        }
    }
    while (!pila.empty()) {
        if (isVowel(pila.top())) {
            while (!aux.empty()) {
                sol.push_back(aux.top());
                aux.pop();
            }
            sol.push_back(pila.top());
            pila.pop();
        }
        else {
            aux.push(pila.top());
            pila.pop();
        }
    }
    while (!aux.empty()) {
        sol.push_back(aux.top());
        aux.pop();
    }
    cout << sol << "\n";
}


void resolver(string& cadena) {
    stack<char> pila;
    queue<char> cola;
    for (int i = 0; i < cadena.length() ; i++) {
        if (i % 2 == 0) {
            cola.push(cadena[i]);
        }
        else {
            pila.push(cadena[i]);
        }
    }
    resolverConsonantes(cola, pila);  
}

bool resuelveCaso() {
    string cadena;
    if (!getline(cin, cadena)) {
        return false;
    }
    resolver(cadena);
    return true;
}

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
