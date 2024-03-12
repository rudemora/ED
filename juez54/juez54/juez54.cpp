// juez54.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <unordered_map>
#include <set>
#include <vector>
#include <list>
#include <algorithm>
#include <fstream>

using namespace std;

/*@ <answer> */

struct info {
    int gravedad;
    list<string>::iterator pos;
};

class Urgencias {
private:
    unordered_map<string, info> unmap;
    list<string> gravedad1;
    list<string> gravedad2;
    list<string> gravedad3;
    vector<string> recuper;
public:

    Urgencias() : unmap(), gravedad1(), gravedad2(), gravedad3(), recuper() {};

    void nuevo_paciente(string paciente, int gravedad) {
        auto it = unmap.find(paciente);
        if (it != unmap.end()) {
            throw(domain_error("Paciente repetido"));
        }
        else {
            if (gravedad < 1 || gravedad > 3) {
                throw(domain_error("Gravedad incorrecta"));
            }
            else {
                if (gravedad == 1) {
                    gravedad1.push_front(paciente);
                    unmap.insert({ paciente, {gravedad, gravedad1.begin()} });
                }
                else if (gravedad == 2) {
                    gravedad2.push_front(paciente);
                    unmap.insert({ paciente, {gravedad, gravedad2.begin()} });
                }
                else {
                    gravedad3.push_front(paciente);
                    unmap.insert({ paciente, {gravedad, gravedad3.begin()} });
                }

            }
        }
        
    }
    int gravedad_actual(string paciente) {
        auto it = unmap.find(paciente);
        if (it == unmap.end()) {
            throw(domain_error("Paciente inexistente"));
        }
        else {
            return it->second.gravedad;
        }
    }
    string siguiente() {
        if (gravedad3.empty()) {
            if (gravedad2.empty()) {
                if (gravedad1.empty()) {
                    throw(domain_error("No hay pacientes"));
                }
                else {
                    string sol = gravedad1.back(); 
                    gravedad1.pop_back();
                    unmap.erase(sol);
                    return sol;
                }

            }
            else {
                string sol = gravedad2.back();
                gravedad2.pop_back();
                unmap.erase(sol);
                return sol;
            }

        }
        else {
            string sol = gravedad3.back();
            gravedad3.pop_back();
            unmap.erase(sol);
            return sol;
        }

    }
    void mejora(string paciente) {
        auto it = unmap.find(paciente);
        if (it == unmap.end()) {
            throw(domain_error("Paciente inexistente"));
        }
        else {
            int gravedad = it->second.gravedad;
            if (gravedad == 1) {
                gravedad1.erase(it->second.pos);
                unmap.erase(paciente);
                recuper.push_back(paciente);
            }
            else if (gravedad == 2) {
                gravedad2.erase(it->second.pos);
                gravedad1.push_back(paciente);
                it->second.pos = gravedad1.begin();
                it->second.gravedad -= 1;
            }
            else {
                gravedad3.erase(it->second.pos);
                gravedad2.push_back(paciente);
                it->second.pos = gravedad2.begin();
                it->second.gravedad -= 1;
            }
        }
    }
    vector<string> recuperados() {
         sort(this->recuper.begin(), this->recuper.end());
         return this->recuper;
    }
};

bool resuelveCaso() {
    string orden;
    cin >> orden;
    if (!cin) {
        return false;
    }
    else {
        Urgencias urgencias;
        while (orden != "FIN") {
            string paciente;
            int gravedad;
            try {
                if (orden == "nuevo_paciente") {
                    cin >> paciente >> gravedad;
                    urgencias.nuevo_paciente(paciente, gravedad);
                }
                else if (orden == "gravedad_actual") {
                    cin >> paciente;
                    int sol = urgencias.gravedad_actual(paciente);
                    cout << "La gravedad de " << paciente << " es " << sol << "\n";
                }
                else if (orden == "siguiente") {
                    string sol = urgencias.siguiente();
                    cout << "Siguiente paciente: " << sol << "\n";
                }
                else if (orden == "mejora") {
                    cin >> paciente;
                    urgencias.mejora(paciente);
                }
                else if (orden == "recuperados") {
                    vector<string> sol = urgencias.recuperados();
                    cout << "Lista de recuperados: ";
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
