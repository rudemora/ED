// juez82.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <list>
#include <string>
#include <fstream>

/*@ <answer> */
using namespace std;

enum class Categoria { Primero, Segundo, Postre };
struct Plato {
    Categoria categoria;
    string nombre;
};

void ordenar_menu(list<Plato>& platos) {//coste lineal tamaño lista enlazada platos
    auto it = platos.begin();
    auto segundos = platos.begin();
    auto postres = platos.begin();
    while (it != platos.end()) {
        if ((*it).categoria == Categoria::Primero) {
            if ((*segundos).categoria == Categoria::Primero) {
                ++it;
                ++segundos;
                ++postres;
            }
            else {
                if ((*postres).categoria == Categoria::Primero) {
                    ++postres;
                }
                platos.insert(segundos, *it);
                it = platos.erase(it);
            }
            
        }
        else if ((*it).categoria == Categoria::Segundo) {
            if (((*segundos).categoria != Categoria::Segundo)) {
                segundos = platos.insert(postres, *it);
                it = platos.erase(it);
                
            }
            else if ((*postres).categoria == Categoria::Segundo){
                
                ++it;
                ++postres;
            }
            else {
                platos.insert(postres, *it);
                it = platos.erase(it);
            }
        }
        else {
            if (((*postres).categoria != Categoria::Postre)) {
                postres = it;
            }
            ++it;
        }
    }
    for (auto it = platos.begin(); it != platos.end(); it++) {
        if ((*it).categoria == Categoria::Primero) {
            cout << "1";
        }
        else if ((*it).categoria == Categoria::Segundo) {
            cout << "2";
        }
        else {
            cout << "P";
        }
        cout << (*it).nombre << endl;
    }
}

bool resuelveCaso() {
    int N;
    cin >> N;
    if (N == 0) {
        return false;
    }
    else {
        list<Plato> lista;
        string entrada;
        Plato plato;
        for (int i = 0; i < N; i++) {
            cin >> entrada;
            if (entrada == "1") {
                plato.categoria = Categoria::Primero;
            }
            else if (entrada == "2") {
                plato.categoria = Categoria::Segundo;
            }
            else {
                plato.categoria = Categoria::Postre;
            }
            getline(cin, entrada);
            plato.nombre = entrada;
            lista.push_back(plato);
        }
        ordenar_menu(lista);
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
