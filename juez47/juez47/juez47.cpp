// juez47.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

/*@ <answer> */

struct info {
    string profesor;
    int puntuacion;
};

class autoescuela {
private:
    unordered_map<string, info> alumnos;
    unordered_map<string, unordered_map<string, int>> profesores;
    void alta(string A, string P);
    bool es_alumno(string A, string P);
    int puntuacion(string A);
    void actualizar(string A, int N);
    void examen(string P, int N);
    void aprobar(string A);

public:
    void resolver(string orden);
};

void autoescuela::alta(string A, string P) { //coste constante por ser unordered
    auto it = alumnos.find(A);
    if (it == alumnos.end()) {
        alumnos.insert({ A, { P , 0 } });
        profesores[P].insert({ A, 0 });
    }
    else {
        if (it->second.profesor != P) { //si ya está con ese profesor no hace falta cambiar nada
            profesores[it->second.profesor].erase(A);
            it->second.profesor = P;
            profesores[P].insert({ A, it->second.puntuacion });
            
        }
    }
}

bool autoescuela::es_alumno(string A, string P) {//coste constante por ser unordered
    return profesores[P].count(A);
}

int autoescuela::puntuacion(string A) {//coste constante por ser unordered
    auto it = alumnos.find(A);
    if (it == alumnos.end()) {
        throw(domain_error(""));
    }
    else {
        return it->second.puntuacion;
    }
}

void autoescuela::actualizar(string A, int N) {//coste constante por ser unordered
    auto it = alumnos.find(A);
    if (it == alumnos.end()) {
        throw(domain_error(""));
    }
    else {
        it->second.puntuacion += N;
        profesores[it->second.profesor][A] += N;
    }
}
void autoescuela::examen(string P, int N) {//coste logaritmico por el sort, lo demas es constante, creo que no se puede mejorar el tiempo
    vector<string> alumnos;
    cout << "Alumnos de " << P << " a examen:\n";
    auto& aux = profesores[P];
    for (auto it = aux.begin(); it != aux.end(); it++) {
        if ((*it).second >= N) {
            alumnos.push_back((*it).first);
        }
    }
    sort(alumnos.begin(), alumnos.end());
    for (auto it = alumnos.begin(); it != alumnos.end(); it++) {
        cout << *it << "\n";
    }
}
void autoescuela::aprobar(string A) { //coste constante
    auto it = alumnos.find(A);
    if (it == alumnos.end()) {
        throw(domain_error(""));
    }
    else {
        profesores[it->second.profesor].erase(A);
        alumnos.erase(it);
    }
}

void autoescuela::resolver(string orden) {
    try {
        if (orden == "alta") {
            string A, P;
            cin >> A >> P;
            alta(A, P);
        }
        else if (orden == "es_alumno") {
            string A, P;
            cin >> A >> P;
            bool sol = es_alumno(A, P);
            cout << A;
            if (!sol) {
                cout << " no";
            }
            cout << " es alumno de " << P << "\n";
        }
        else if (orden == "puntuacion") {
            string A;
            cin >> A;
            int sol = puntuacion(A);
            cout << "Puntuacion de " << A << ": " << sol << "\n";
        }
        else if (orden == "actualizar") {
            string A;
            int N;
            cin >> A >> N;
            actualizar(A, N);
        }
        else if (orden == "examen") {
            string P;
            int N;
            cin >> P >> N;
            examen(P, N);
        }
        else if (orden == "aprobar") {
            string A;
            cin >> A;
            aprobar(A);
        }
    }
    catch (exception& e) {
        cout << "ERROR\n";
    }
}

bool resuelveCaso() {
    string orden;
    cin >> orden;
    if (!cin) {
        return false;
    }
    else {
        autoescuela autoes;
        while (orden != "FIN") {
            autoes.resolver(orden);
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
