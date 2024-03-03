// juez18.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <stack>
#include <fstream>

/*@ <answer> */

bool resuelveCaso() {

    int n;
    std::cin >> n;
    if (!std::cin)  // fin de la entrada
        return false;
    std::stack<int> entrada;
    int x;
    for (int i = 0; i < n; i++) {
        std::cin >> x;
        entrada.push(x);
    }
    bool premio = true;
    int mediano = -1;
    std::stack<int> pila;
    while (premio && !entrada.empty()) {
        if (pila.empty()) pila.push(entrada.top());
        else if (!pila.empty() && mediano < entrada.top()) {
            while (!pila.empty() && pila.top() < entrada.top()) {
                mediano = pila.top();
                pila.pop();
            }
            pila.push(entrada.top());
        }
        else {
            premio = false;
        }
        entrada.pop();
    }

    if (premio) std::cout << "SIEMPRE PREMIO\n";
    else std::cout << "ELEGIR OTRA\n";
    return true;
}
/*@ </answer> */

int main() {
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
