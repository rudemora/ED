// juez94.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <fstream>
#include <unordered_set>
#include <list>
using namespace std;

/*@ <answer> */

struct tipo {
    int cant = 0;
    map<string, int, less<string>> fecha;
    list<string> clientes;
};

class Tienda {
private:
    unordered_map<string, tipo> unmap; //cada producto
    unordered_map<string, pair<list<list<string>::iterator>, int>> clientes; //cada cliente

public:
    Tienda() : unmap() {};
    vector<string> adquirir(string cod, string f, int cant) {
        auto& aux = unmap[cod];
        vector<string> sol;
        unordered_set<string> adquiridos;
        aux.cant += cant;
        aux.fecha.insert({ f,cant });
        string cliente;
        while (aux.cant > 0 && !aux.clientes.empty()) {
            cliente = aux.clientes.back();
            auto& aux2 = clientes[cliente];
            aux2.second -= 1;
            aux.cant -= 1;
            aux.clientes.erase(*(aux2.first.begin()));
            aux2.first.pop_front();
            if (!adquiridos.count(cliente)) {
                sol.push_back(cliente);
                adquiridos.insert(cliente);
            }
        }
        if (aux.cant == 0) {
            aux.fecha.clear();
        }
        return sol;
    }

    pair<bool,string> vender(string cod, string cli) {
        auto it = unmap.find(cod);
        if (it == unmap.end()) {
            auto& aux = unmap[cod];
            aux.clientes.push_front(cli);
            clientes[cli].first.push_back(aux.clientes.begin());
            clientes[cli].second += 1;
            return { false, "" };
        }
        else if (it->second.cant == 0) {
            it->second.clientes.push_front(cli);
            clientes[cli].first.push_back(it->second.clientes.begin());
            clientes[cli].second += 1;
            return { false, "" };
        }
        else {
            it->second.cant -= 1;
            auto fecha = it->second.fecha.begin();
            
            string sol = "";
            if ((*fecha).second > 1) {
                (*fecha).second -= 1;
                sol = (*fecha).first;
            }
            else {
                sol = (*fecha).first;
                
                it->second.fecha.erase(fecha);
            }
            return { true, sol};
        }

    }

    int cuantos(string cod) {
        return unmap[cod].cant;
    }

    bool hay_esperando(string cod) {
        return unmap[cod].clientes.empty();
    }
};

bool resuelveCaso() {
    string orden;
    cin >> orden;
    if (!cin) {
        return false;
    }
    else {
        string cod, f, cli;
        int cant;
        Tienda tienda;
        while (orden != "FIN") {
            if (orden == "adquirir") {
                cin >> cod >> f >> cant;
                vector<string> sol = tienda.adquirir(cod, f, cant);
                cout << "PRODUCTO ADQUIRIDO ";
                for (auto it = sol.begin(); it != sol.end(); it++) {
                    cout << (*it) << " ";
                }
                cout << "\n";
            }
            else if (orden == "vender") {
                cin >> cod >> cli;
                pair<bool, string> sol = tienda.vender(cod, cli);
                if (sol.first == false) {
                    cout << "EN ESPERA";
                }
                else {
                    cout << "VENDIDO " + sol.second;
                }
                cout << "\n";
            }
            else if (orden == "cuantos") {
                cin >> cod;
                int sol = tienda.cuantos(cod);
                cout << sol << "\n";
            }
            else if (orden == "hay_esperando") {
                cin >> cod;
                bool sol = tienda.hay_esperando(cod);
                if (sol) {
                    cout << "NO";
                }
                else {
                    cout << "SI";
                }
                cout << "\n";
            }
            cin >> orden;
        }
        cout << "---\n";
        return true;
    }
}

/*@ </answer> */

int main()
{/*
#ifndef DOMJUDGE
    std::ifstream in("datos.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
    std::ofstream out("datos.out");
    auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif*/
    while (resuelveCaso());/*
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    std::cout.rdbuf(coutbuf);
    system("PAUSE");
#endif*/
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
