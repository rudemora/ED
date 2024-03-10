/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */

 /*
  * MUY IMPORTANTE: Para realizar este ejercicio solo podéis
  * modificar el código contenido entre las etiquetas <answer>
  * y </answer>. Toda modificación fuera de esas etiquetas no
  * será corregida.
  *
  * Tampoco esta permitido modificar las líneas que contienen
  * las etiquetas <answer> y </answer>, obviamente :-)
  */

  //@ <answer>
  // Nombre y Apellidos:
  //@ </answer>

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
    using namespace std;




 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

void resuelveCaso() {

    // leer los datos de la entrada
    map<string, int> diccionario;
    string linea, clave;
    getline(cin, linea);
    stringstream ss1(linea);
    while (ss1 >> clave) {  
        int aux;
        ss1 >> aux;
        diccionario[clave] = aux;
    }
    getline(cin, linea);
    stringstream ss2(linea);
    vector<string> nuevos;
    vector<string> cambios;
    while (ss2 >> clave) {  
        int aux;
        ss2 >> aux;
        if (diccionario.count(clave)) {  
            if (diccionario[clave] != aux) {  
                cambios.push_back(clave);
            }
            diccionario.erase(clave);  
        }
        else {  
            nuevos.push_back(clave);
        }
    }
    bool cambio = false;
    if (nuevos.size()) {
        sort(nuevos.begin(), nuevos.end());  
        cambio = true;
        cout << "+ ";
        for (string clave : nuevos) {
            cout << clave << ' ';
        }
        cout << '\n';
    }
    if (diccionario.size()) {
        cambio = true;
        cout << "- ";
        for (auto [clave, valor] : diccionario) {
            cout << clave << ' ';
        }
        cout << '\n';
    }
    if (cambios.size()) {
        sort(cambios.begin(), cambios.end());  
        cambio = true;
        cout << "* ";
        for (string clave : cambios) {
            cout << clave << ' ';
        }
        cout << '\n';
    }
    if (!cambio) cout << "Sin cambios\n";
    cout << "---\n";
    
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
#ifndef DOMJUDGE
    std::ifstream in("datos.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
    std::ofstream out("datos.out");
    auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif


    int casos;
    cin >> casos;
    cin.ignore(1);
    while (casos--) {
        resuelveCaso();
    }

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    std::cout.rdbuf(coutbuf);
    system("PAUSE");
#endif
    return 0;
}