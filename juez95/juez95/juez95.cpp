// juez95.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <unordered_map>
#include <algorithm>
using namespace std;

struct info {
    string region;
    int puntos;
    int caballeros;
    list<string>::iterator pos;
};

class ElGrande {
private:
    unordered_map<string, info> jugadores;
    unordered_map<string, list<string>> regiones;
public:
    void anyadir_jugador(string jug) {
        auto it = jugadores.find(jug);
        if (it != jugadores.end()) {
            throw(domain_error("Jugador existente"));
        }
        else {
            jugadores.insert({ jug, {}});
        }
    }
    void colocar_caballero(string jug, string reg) {
        auto it = jugadores.find(jug);
        if (it == jugadores.end()) {
            throw(domain_error("Jugador no existente"));
        }
        it->second.region = reg;
        auto& aux = regiones[reg];
        aux.push_front(jug);
        it->second.pos = aux.begin();
        it->second.caballeros += 1;
        if (aux.size() == 1) {
            it->second.puntos += 1;
        }
    }
    int puntuacion(string jug) {
        auto it = jugadores.find(jug);
        if (it == jugadores.end()) {
            throw(domain_error("Jugador no existente"));
        }
        else {
            return it->second.puntos;
        }
    }
    vector<string> regiones_en_disputa() {
        vector<string> sol;
        for (auto it = regiones.begin(); it != regiones.end(); it++) {
            if (it->second.size() > 1) {
                sol.push_back(it->first);
            }
        }
        return sol;
    }

    void expulsar_caballeros(string region) {

    }
};

bool resuelveCaso() {
    string orden; 
    cin >> orden; 
    if (!cin) {
        return false;
    }
    else {
        string jug;
        string reg;
        ElGrande grande;
        while (orden != "FIN") {
            try {
                if (orden == "anyadir_jugador") {
                    cin >> jug;
                    grande.anyadir_jugador(jug);
                }
                else if (orden == "colocar_caballero") {
                    cin >> jug >> reg;
                    grande.colocar_caballero(jug, reg);
                }
                else if (orden == "puntuacion") {
                    cin >> jug;
                    int sol = grande.puntuacion(jug);
                    cout << "Puntuacion de " << jug << ": " << sol << "\n";
                }
                else if (orden == "regiones_en_disputa") {
                    vector<string> sol = grande.regiones_en_disputa();
                    cout << "Regiones en disputa:\n";
                    sort(sol.begin(), sol.end());
                    for (auto it = sol.begin(); it != sol.end(); it++) {
                        cout << (*it) << "\n";
                    }
                }
                else if (orden == "expulsar_caballeros") {
                    cin >> reg;
                    grande.expulsar_caballeros(reg);
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

int main()
{
    while (resuelveCaso());
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
