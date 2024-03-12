// juez52.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <unordered_map>
#include <list>
#include <string>
#include <map>
#include <fstream>

using namespace std;


/*@ <answer> */

struct info {
    int ejemplares;
    int numVentas;
    list<string>::iterator orden;
    
};

class Libro {
public:
    Libro() : mapa(), orden() {};
    void nuevoLibro(int numero, string nombre) { //O(1)
        auto it = mapa.find(nombre);
        if (it == mapa.end()) {
            mapa.insert({ nombre, {numero, 0, }});
        }
        else {
            it->second.ejemplares += numero;
        }
    }
    void comprar(string nombre) {//O(logl)
        auto it = mapa.find(nombre);
        if (it == mapa.end()) {
            throw(invalid_argument("Libro no existente"));
        }
        else if (it->second.ejemplares == 0) {
            throw(out_of_range("No hay ejemplares"));
        }
        else {
            it->second.ejemplares -= 1;
            it->second.numVentas += 1;
            if (it->second.numVentas > 1) {//ya se habían comprado libros antes
                orden[it->second.numVentas - 1].erase(it->second.orden);
            }
            orden[it->second.numVentas].push_front(nombre); //no se simplificar esto en una instruccion que evite hacer dos accesos a orden
            it->second.orden = orden[it->second.numVentas].begin();
         }
    }
    void numEjemplares(string nombre) { //O(1)
        auto it = mapa.find(nombre);
        if (it == mapa.end()) {
            throw(invalid_argument("No existe el libro " + nombre + " en el sistema"));
        }
        else {
            cout << "Existen " << it->second.ejemplares << " ejemplares del libro " << nombre;
        }
    }
    
    void top10() {//O(1)
        int contador = 0;
        cout << "TOP10\n";
        auto it = orden.begin();
        while (contador < 10 && it != orden.end()) {
            auto aux = it->second.begin();
            while (contador < 10 && aux != it->second.end()) {
                cout << "    " << (*aux) << "\n";
                contador += 1;
                ++aux;
            }
            ++it;
        }
    }

    void estaLibro(string libro) {//O(1)
        auto it = mapa.find(libro);
        if (it == mapa.end()) {
            cout << "No existe el libro " << libro << " en el sistema";
        }
        else {
            cout << "El libro " << libro << " esta en el sistema";
        }
    }

    void elimLibro(string libro) { //O(logl)
        auto it = mapa.find(libro);
        if (it != mapa.end()) {
            if (it->second.numVentas > 0) {
                orden[it->second.numVentas].erase(it->second.orden);
            }
            mapa.erase(libro);
        }
    }

private:
    unordered_map <string, info> mapa;
    map < int, list<string>, greater<int>> orden;
};

bool resuelveCaso() {
    int num; 
    cin >> num;
    if (!cin) {
        return false;
    }
    else {
        string orden;
        Libro libro;
        for (int i = 0; i < num; i++) {
            cin >> orden;
            string nombre;
            int numero;
            try {
                if (orden == "nuevoLibro") {
                    cin >> numero;
                    cin.ignore(1);
                    getline(cin, nombre);
                    libro.nuevoLibro(numero, nombre);
                }
                else if (orden == "comprar") {
                    cin.ignore(1);
                    getline(cin, nombre);
                    libro.comprar(nombre);
                }
                else if (orden == "numEjemplares") {
                    cin.ignore(1);
                    getline(cin, nombre);
                    libro.numEjemplares(nombre);
                    cout << "\n";
                }
                else if (orden == "top10") {
                    libro.top10();
                }
                else if (orden == "estaLibro") {
                    cin.ignore(1);
                    getline(cin, nombre);
                    libro.estaLibro(nombre);
                    cout << "\n";
                }
                else if (orden == "elimLibro") {
                    cin.ignore(1);
                    getline(cin, nombre);
                    libro.elimLibro(nombre);
                }
            }
            catch (exception& e) {
                cout << e.what();
                cout << "\n";
            }
        }
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
