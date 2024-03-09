/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */

 /*
  * MUY IMPORTANTE: Solo se corregirán los comentarios y el código
  * contenidos entre las etiquetas <answer> y </answer>.
  * Toda modificación fuera de esas etiquetas no será corregida.
  */

  /*@ <answer>
    Estudiante 1: Rubén de Mora Losada
    Estudiante 2: David Esparza Sainz

    Dad una explicación de la solución y justificad el coste del
    algoritmo.

    Hemos utilizado dos iteradores inicializados al inicio de la lista (it) y eñ siguiente (next)
    a este. Mientras que estemos en la lista, es decir, next sea diferente de l.end(), tendremos 
    que suavizar la lista. Lo primero sea comprobar si debemos introducir elementos entre 
    un elemento y su siguiente, es decir, si su diferencia en valor absoluto es mayor que 1. 
    En este caso, deberemos introducir números comprobando si deben ser en orden creciente o decreciente,
    para aumentar los iteradores una posición cuando introducimos un elemento utilizamos lo que devuelven las funciones insert. 
    En otro caso, si los dos elementos son iguales, debemos eliminar los repetidos, así que hacemos uso de la función erase y, de nuevo,
    volvemos a utilizar el iterador devuelto por la función. Por último, si los dos elementos tienen diferencia de 1, simplemente avanzamos
    los iteradores de forma manual para comprobar con los siguientes 2 elementos.

    El coste de la función es lineal respecto a los números de la lista sumado al valor absoluto de la diferencia de los elementos cogidos dos a dos, orden lineal.

   *@ </answer> */


#include <iostream>
#include <fstream>
#include <list>
using namespace std;

// ----------------------------------------------------------------
//@ <answer>

void suavizar(list<int>& l) {
    // Implementa aquí la función pedida
    auto it = l.begin();
    auto next = ++l.begin();
    while (next != l.end()) {

        if (abs(*it - *next) > 1) {
            if (*it < *next) {
                it = l.insert(next, *it + 1);
            }
            else {
                it = l.insert(next, *it - 1);
            }
        }
        else if (*it - *next == 0) {
            ++next;
            it = l.erase(it);
            
        }
        else {
            ++it;
            ++next;
        }
        

    }
}

bool resuelveCaso() {
    int longitud;
    cin >> longitud;
    if (!cin)
        return false;

    list<int> l;

    for (int i = 0; i < longitud; i++) {
        int x; cin >> x;
        l.push_back(x);
    }

    suavizar(l);

    // imprimir l
    for (auto it = l.begin(); it != l.end(); it++) {
        cout << *it << " ";
    }
    cout << "\n";
    return true;
}
//@ </answer>

// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------

int main() {
#ifndef DOMJUDGE
    std::ifstream in("datos.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
    std::ofstream out("datos.out");
    auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif

    while (resuelveCaso()) {}

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    std::cout.rdbuf(coutbuf);
    system("PAUSE");
#endif
    return 0;
}
