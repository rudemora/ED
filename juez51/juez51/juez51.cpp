// juez51.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <list>
#include <vector>
using namespace std;

/*@ <answer> */

struct info {
    string artist;
    int duration = 0;
    list<string>::iterator posR;
    list<string>::iterator posL;
};

class iPud {
private:
    int total;
    unordered_map<string, info> unmap;
    unordered_set<string> lista;
    unordered_set<string> repr;
    list<string> reproducidas;
    list<string> enLista;
    
public:

    iPud() : total(0), unmap(), lista(), reproducidas(), enLista(), repr() {};

    void deleteSong(string song) {
        auto it = unmap.find(song);
        if (it != unmap.end()) {
            if (it->second.posL != enLista.end()) {
                total -= it->second.duration;
                enLista.erase(it->second.posL);
                lista.erase(song);
            }
            if (it->second.posR != reproducidas.end()) {
                reproducidas.erase(it->second.posR);
                repr.erase(song);
            }
            unmap.erase(song);
        }
    }

    void addSong(string song, string artist, int tiempo) {
        auto it = unmap.find(song);
        if (it != unmap.end()) {
            throw(domain_error("addSong"));
        }
        else {
            unmap.insert({ song, {artist, tiempo, reproducidas.end(), enLista.end()} });
        }
    }
    void addToPlaylist(string song) {
        auto it = unmap.find(song);
        if (it == unmap.end()) {
            throw(domain_error("addToPlaylist"));
        }
        else if (!lista.count(song)) {   
            lista.insert(song);
            enLista.push_front(song);
            it->second.posL = enLista.begin();
            total += (*it).second.duration;
        }
    }

    string current() {
        if (lista.empty()) {
            throw(domain_error("current"));
        }
        else {
            return enLista.back();
        }
    }

    string play() {
        if (!enLista.empty()) {
            string song = enLista.back();
            auto& aux = unmap[song];
            if (!repr.count(song)) {
                total -= aux.duration;
                reproducidas.push_front(song);
                aux.posR = reproducidas.begin();
                enLista.erase(aux.posL);
                aux.posL = enLista.end();
                lista.erase(song);
                repr.insert(song);
            }
            else {
                total -= aux.duration;
                reproducidas.push_front(song);
                reproducidas.erase(aux.posR);
                aux.posR = reproducidas.begin();
                enLista.erase(aux.posL);
                aux.posL = enLista.end();
                lista.erase(song);
            }
            return song;
        }
        return "";
    }

    int totalTime() {
        return total;
    }

    vector<string> recent(int N) {
        vector<string> sol;
        int contador = 0;
        for (auto it = reproducidas.begin(); it != reproducidas.end(); it++) {
            sol.push_back(*it);
            contador += 1;
            if (contador == N) {
                break;
            }
        }
        return sol;
    }

    
};

bool resuelveCaso() {
    string orden;
    cin >> orden;
    if (!cin) {
        return false;
    }
    else {
        iPud ipud;
        while (orden != "FIN") {
            string song;
            string artist;
            int duracion;
            int N;
            try {
                if (orden == "addSong") {
                    cin >> song >> artist >> duracion;
                    ipud.addSong(song, artist, duracion);
                }
                else if (orden == "addToPlaylist") {
                    cin >> song;
                    ipud.addToPlaylist(song);
                }
                else if (orden == "current") {
                    string sol = ipud.current();
                }
                else if (orden == "play") {
                    string sol = ipud.play();
                    if (sol != "") {
                        cout << "Sonando " << sol << "\n";
                    }
                    else {
                        cout << "No hay canciones en la lista\n";
                    }
                }
                else if (orden == "totalTime") {
                    int sol = ipud.totalTime();
                    cout << "Tiempo total " << sol << "\n";
                }
                else if (orden == "recent") {
                    cin >> N;
                    vector<string> sol = ipud.recent(N);
                    if (sol.size() == 0) {
                        cout << "No hay canciones recientes\n";
                    }
                    else {
                        cout << "Las " << sol.size() << " mas recientes\n";
                        for (auto it = sol.begin(); it != sol.end(); it++) {
                            cout << "    " << (*it) << "\n";
                        }
                    }
                }
                else if (orden == "deleteSong") {
                    cin >> song;
                    ipud.deleteSong(song);
                }
            }
            catch (exception& e) {
                cout << "ERROR " << e.what() << "\n";
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
