// juez46.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <fstream>
#include <list>
#include <forward_list>
using namespace std;

/*@ <answer> */

struct tipo {
    int num;
    int pos;
};

class CarnetPuntos {
private:
    unordered_map<string, pair<int,list<string>::iterator>> set;
    vector<int> puntos;
    vector<list<string>> id;

    void nuevo(string dni);
    void quitar(string dni, int puntos);
    void consultar(string dni);
    void cuantos_con_puntos(int puntos) const;
    void recuperar(string dni, int puntos);
    list<string> const& lista_por_puntos(int puntos) const;
public:
    CarnetPuntos() : set(), puntos(16), id(16) {};
    void resolver(string orden);
};

void CarnetPuntos::nuevo(string dni) {
    if (set.count(dni)) {
        throw(domain_error("Conductor duplicado"));
    }
    else {
        id[15].push_front(dni);
        set.insert({ dni, {15, id[15].begin()}});
        puntos[15] += 1;  
    }
}
void CarnetPuntos::quitar(string dni, int puntos) {
    auto it = set.find(dni);
    if (it == set.end()) {
        throw(domain_error("Conductor inexistente"));
    }
    else {
        if (it->second.first > 0 && puntos > 0) {
            this->puntos[it->second.first] -= 1;
            id[it->second.first].erase(it->second.second);
            it->second.first = it->second.first - puntos;
            if (it->second.first < 0) {
                it->second.first = 0;
            }
            id[it->second.first].push_front(dni);
            this->puntos[it->second.first] += 1;
            it->second.second = id[it->second.first].begin();
        }
    }

}
void CarnetPuntos::consultar(string dni) {
    auto it = set.find(dni);
    if (it == set.end()) {
        throw(domain_error("Conductor inexistente"));
    }
    else {
        cout << "Puntos de " << it->first << ": " << it->second.first << "\n";
    }
}
void CarnetPuntos::cuantos_con_puntos(int puntos) const {
    if (puntos > 15 || puntos < 0) {
        throw(domain_error("Puntos no validos"));
    }
    else {
        cout << "Con " << puntos << " puntos hay " << this->puntos[puntos] << "\n";
    }
}

void CarnetPuntos::recuperar(string dni, int puntos) {
    auto it = set.find(dni);
    if (it == set.end()) {
        throw(domain_error("Conductor inexistente"));
    }
    else {
        
        if (it->second.first < 15 && puntos > 0) {
            this->puntos[it->second.first] -= 1;
            id[it->second.first].erase(it->second.second);
            it->second.first = it->second.first + puntos;
            if (it->second.first > 15) {
                it->second.first = 15;
            }

            id[it->second.first].push_front(dni);
            this->puntos[it->second.first] += 1;
            it->second.second = id[it->second.first].begin();
        }
        
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
        else if (orden == "recuperar") {
            int puntos;
            string dni;
            cin >> dni >> puntos; 
            recuperar(dni, puntos);
        }
        else if (orden == "lista_por_puntos") {
            int puntos;
            cin >> puntos;
            auto& lista = lista_por_puntos(puntos);
            cout << "Tienen " << puntos << " puntos: ";
            for (auto& dni : lista) {
                cout << dni << " ";
            }
            cout << endl;
        }
    }
    catch (exception& e) {
        cout << "ERROR: " << e.what() << "\n";
    }


}

list<string> const& CarnetPuntos::lista_por_puntos(int puntos) const{
    if (puntos > 15 || puntos < 0) {
        throw(domain_error("Puntos no validos"));
    }
    else {
        return id[puntos];
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
