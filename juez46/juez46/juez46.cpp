// juez46.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

/*@ <answer> */

class CarnetPuntos {
private:
    unordered_map<string, int> set;
    vector<int> puntos;
    void nuevo(string dni);
    void quitar(string dni, int puntos);
    void consultar(string dni);
    void cuantos_con_puntos(int puntos);

public: 
    CarnetPuntos() : set(), puntos(16) {};
    void resolver(string orden);
};

void CarnetPuntos::nuevo(string dni) {
    if (set.count(dni)) {
        throw(domain_error("Conductor duplicado"));
    }
    else {
        set.insert({ dni, 15 });
        puntos[15] += 1;
    }
}
void CarnetPuntos::quitar(string dni, int puntos) {
    auto it = set.find(dni);
    if (it == set.end()) {
        throw(domain_error("Conductor inexistente"));
    }
    else {
        this->puntos[it->second] -= 1;
        it->second = it->second - puntos;
        if (it->second < 0) {
            it->second = 0;
        }
        this->puntos[it->second] += 1;
    }
}
void CarnetPuntos::consultar(string dni) {
    auto it = set.find(dni);
    if (it == set.end()) {
        throw(domain_error("Conductor inexistente"));
    }
    else {
        cout << "Puntos de " << it->first << ": " << it->second << "\n";
    }
}
void CarnetPuntos::cuantos_con_puntos(int puntos) {
    if (puntos > 15 || puntos < 0) {
        throw(domain_error("Puntos no validos"));
    }
    else {
        cout << "Con " << puntos << " puntos hay " << this->puntos[puntos] << "\n";
    }
}

void CarnetPuntos::resolver(string orden) {
    try {
        if (orden == "nuevo") {
            string dni;
            cin >> dni;
            nuevo(dni);
        }
        else if (orden == "quitar") {
            string dni;
            int puntos;
            cin >> dni >> puntos;
            quitar(dni, puntos);
        }
        else if (orden == "consultar") {
            string dni;
            cin >> dni;
            consultar(dni);
        }
        else if (orden == "cuantos_con_puntos") {
            int puntos;
            cin >> puntos;
            cuantos_con_puntos(puntos);
        }
    }
    catch (exception& e) {
        cout << "ERROR: " << e.what() << "\n";
    }
    
    
}

bool resuelveCaso() {
    string orden;
    cin >> orden;
    if (!cin) {
        return false;
    }
    else {
        CarnetPuntos carnet;
        while (orden != "FIN") {
            carnet.resolver(orden);
            cin >> orden;
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
