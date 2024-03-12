// juez93.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <unordered_map>
#include <list>
#include <fstream>
#include <vector>
using namespace std;

/*@ <answer> */

struct tipo {
    int num_cola;
    list<string>::iterator posCola;
};

class Supermercado {
private:
    unordered_map<string, tipo> clientes;
    vector<list<string>> colas;


public:
    Supermercado(int num_cajas) : clientes(), colas(num_cajas) {};

    void nuevo_cliente(string cod, int num) {
        if (num > colas.size() - 1 || num < 0) {
            throw(domain_error("Cola inexistente"));
        }
        else {
            auto it = clientes.find(cod);
            if (it != clientes.end()) {
                throw(domain_error("Cliente duplicado"));
            }
            else {
                auto& aux = colas[num];
                aux.push_front(cod);
                clientes.insert({ cod, {num, aux.begin() } });
            }
        }

    }

    void cambiar_cola(string cod, int num) {
        if (num > colas.size() - 1 || num < 0) {
            throw(domain_error("Cola inexistente"));
        }
        else {
            auto it = clientes.find(cod);
            if (it == clientes.end()) {
                throw(domain_error("Cliente inexistente"));
            }
            else if (it->second.num_cola != num) {
                colas[it->second.num_cola].erase(it->second.posCola);
                auto& aux = colas[num];
                aux.push_front(cod);
                it->second.num_cola = num;
                it->second.posCola = aux.begin();
            }
        }
    }

    int consultar_cliente(string cod) {
        auto aux = clientes.find(cod);
        if (aux == clientes.end()){
            throw(domain_error("Cliente inexistente"));

        }
        else{
            return aux->second.num_cola;
        }
    }


    int cuantos_en_cola(int num) {
        if (num > colas.size() - 1 || num < 0) {
            throw(domain_error("Cola inexistente"));
        }
        else {
            return colas[num].size();
        }
    }

    list<string> clientes_cola(int num) {
        if (num > colas.size() - 1 || num < 0) {
            throw(domain_error("Cola inexistente"));
        }
        else {
            return colas[num];
        }
    }
};

bool resuelveCaso() {
    int cajas;
    cin >> cajas;
    if (!cin) {
        return false;
    }
    else {
        string orden;
        string cod_cliente;
        int num_cola;
        cin >> orden;
        Supermercado super(cajas);
        while (orden != "FIN") {
            try {
                if (orden == "nuevo_cliente") {
                    cin >> cod_cliente >> num_cola;
                    super.nuevo_cliente(cod_cliente, num_cola);
                }
                else if (orden == "cambiar_cola") {
                    cin >> cod_cliente >> num_cola;
                    super.cambiar_cola(cod_cliente, num_cola);
                }
                else if (orden == "consultar_cliente") {
                    cin >> cod_cliente;
                    int sol = super.consultar_cliente(cod_cliente);
                    cout << "El cliente " << cod_cliente << " esta en la cola " << sol << "\n";
                }
                else if (orden == "cuantos_en_cola") {
                    cin >> num_cola;
                    int sol = super.cuantos_en_cola(num_cola);
                    cout << "En la cola " << num_cola << " hay " << sol << " clientes\n";
                }
                else if (orden == "clientes_en_cola") {
                    cin >> num_cola;
                    list<string> sol = super.clientes_cola(num_cola);
                    cout << "En la cola " << num_cola << " estan: ";
                    for (auto it = sol.begin(); it != sol.end(); it++) {
                        cout << (*it) << " ";
                    }
                    cout << "\n";
                }
            }
            catch (exception& e) {
                cout << "ERROR: " << e.what() << "\n";
            }
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
