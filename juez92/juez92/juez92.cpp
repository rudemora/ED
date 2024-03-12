// juez92.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <map>
#include <set>
#include <fstream>
using namespace std;

/*@ <answer> */

struct tipo {
    set<int,less<int>> personas;
    string contiene = "";
    int num = 0;
};

void insertarE(map<int,tipo>& mapa, int desp, int i, int& cap) {
    auto it = mapa.find(desp);
    if (it == mapa.end()) {
        auto& aux = mapa[desp];
        aux.contiene = "E";
        aux.num += 1;
        aux.personas.insert(i);
    }
    else {
        if (it->second.personas.size() == cap) {
            auto& aux = mapa[desp];
            if (aux.contiene == "E") {
                auto it = aux.personas.begin();
                if (*it < i) {
                    aux.personas.insert(i);
                    insertarE(mapa, desp + 1, *it, cap);
                    aux.personas.erase(it);
                }
                else {
                    insertarE(mapa, desp + 1, i, cap);
                }
            }
            else {
                insertarE(mapa, desp + 1, i, cap);
            }
        }
        else {
            auto& aux = mapa[desp];
            if (aux.contiene == "E") {
                aux.num += 1;
                aux.personas.insert(i);
                aux.contiene = "E";
            }
            else {
                insertarE(mapa, desp + 1, i, cap);
            }
            
        }
    }
}

void insertarJ(map<int, tipo>& mapa, int desp, int i, int& cap) {
    auto it = mapa.find(desp);
    if (it == mapa.end()) {
        auto& aux = mapa[desp];
        aux.contiene = "J";
        aux.num = 0;
        aux.personas.insert(i);
    }
    else {
        auto& aux = mapa[desp];
        auto it = aux.personas.begin();
        if (aux.contiene == "E") {
            aux.contiene = "J";
            while (!aux.personas.empty()) {
                auto it = aux.personas.begin();
                insertarE(mapa, desp + 1, *it, cap);
                aux.personas.erase(it);
            }
            aux.personas.insert(i);
            aux.num = 0;
        }
        else if (aux.contiene == "J") {
            if (*it < i) {
                aux.contiene = "J";
                insertarJ(mapa, desp + 1, *it, cap);
                aux.personas.erase(it);
                aux.personas.insert(i);
                
                aux.num = 0;
            }
            else {
                insertarJ(mapa, desp + 1, i, cap);
            }
        }
    }

}

bool resuelveCaso()  {
    int C, N, M;
    cin >> C >> N >> M;
    if (C == 0 && N == 0 && M == 0) {
        return false;
    }
    else {
        map<int, tipo> mapa;
        int despacho;
        for (int i = 0; i < N; i++) {
            cin >> despacho;
            insertarE(mapa, despacho, i, C);
        }
        for (int i = 0; i < M; i++) {
            cin >> despacho;
            insertarJ(mapa, despacho, i, C);
        }
        for (auto it = mapa.begin(); it != mapa.end(); it++) {
            if ((*it).second.contiene == "J") {
                cout << (*it).first << " " << "JEFE\n";
            }
            else {
                cout << (*it).first << " " << (*it).second.num << "\n"; //<< *((*it).second.personas.begin()) << "\n";
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
