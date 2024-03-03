// juez16.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <queue>
#include <stack>
#include <fstream>

using namespace std;
/*@ <answer> */

void resolver(queue<int>& v) {// Debido a la ordenación por valor absoluto, los números negativos van a estar ordenados al reves, por ello los meto en una pila, para que los mas negativos
                              // se queden en la parte superior y segun baje vayan siendo negativos menores. Los números positivos están ordenados correctamente, basta tomar una pila para
                              // tenerlos guardados y diferenciarlos de los negativos
    stack<int> negativos;
    queue<int> positivos;
    while (!v.empty()) {
        if (v.front() < 0) {
            negativos.push(v.front());
            v.pop();
        }
        else {
            positivos.push(v.front());
            v.pop();
        }
    }
    while (!negativos.empty()) {
        v.push(negativos.top());
        negativos.pop();
    }
    while (!positivos.empty()) {
        v.push(positivos.front());
        positivos.pop();
    }
}

bool resuelveCaso() {
    int longitud;
    cin >> longitud;
    if (longitud == 0) {
        return false;
    }
    else {
        queue<int> v;
        int elemento;
        for (int i = 0; i < longitud; i = i + 1) {
            cin >> elemento;
            v.push(elemento);
        }
        resolver(v);
        while (!v.empty()) {
            cout << v.front() << " ";
            v.pop();
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
