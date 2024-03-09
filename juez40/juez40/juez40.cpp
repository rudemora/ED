// juez40.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>


/*@ <answer> */


using namespace std;

ostream& operator<<(ostream& os, vector<int>& v) {
    for (auto it = v.begin(); it != v.end(); it++) {
        cout << (*it) << " ";
    }
    cout << "\n";
    return os;
}

string minuscula(string word) {
    for (int i = 0; i < word.length(); i++) {
        word[i] = tolower(word[i]);
    }
    return word;
}

void resolver(int N) {
    map<string, vector<int>> map;
    string cadena;
    string word;
    cin.ignore(1);
    for (int i = 0; i < N; i++) {
        getline(cin, cadena);
        stringstream ss(cadena);
        while (ss >> word) {
            word = minuscula(word);
            if (word.length() > 2) {
                if (map[word].empty()) {
                    map[word].push_back(i + 1);
                }
                else if (map[word][map[word].size() - 1] != i + 1) {
                    map[word].push_back(i + 1);
                }
            }
        }
    }
    for (auto it = map.begin(); it != map.end(); it++) {
        cout << (*it).first << " " << (*it).second;
    }
}

/*@ </answer> */

bool resuelveCaso() {
    int N;
    cin >> N;
    if (N == 0) {
        return false;
    }
    else {
        resolver(N);
        cout << "---\n";
        return true;
    }
}

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
