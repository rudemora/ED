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
    Estudiante 1: David Esparza Sainz
    Estudiante 2: Rubén De Mora Losada

    Dad una explicación de la solución y justificad el coste del
    algoritmo.

    En la solucion hemos empleado una pila. La idea general es, solo me interesan aquellos elementos para los que no he encontrado un elemento mayor
    despues puesto que la lista esta ordenada por fechar crecientes. Para ello uso una pila y en cada iteracion vamos eliminando todos los elementos
    con que son menores que el elemnto i-esimo del vector y en caso de que no quede vacia imprimimos por pantalla el top (si no "NO HAY").

   *@ </answer> */


#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
using namespace std;

// ----------------------------------------------------------------
//@ <answer>
struct tSol {
    int valor;
    string fecha;
};
void resolver(vector <tSol> const& v) {//Coste lineal respecto al numero de elementos de v puesto que el numero de elementos de la pila que tengo que eliminar en cada iteracion tiene coste constante( ya que de media tengo que eliminar a lo maximo 1 por cada itereacion lo cual tiene coste constante (en caso de que la pila acabe vacia si el maximo es el ultimo elemento, si la pila no acaba vacia la media es aun menor). 
    stack<tSol> s;
    for (tSol sol : v) {
        while (!s.empty() && s.top().valor <= sol.valor) {
            s.pop();
        }
        if (!s.empty()) {
            cout << s.top().fecha << endl;
        }
        else {
            cout << "NO HAY" << endl;
        }
        s.push(sol);
    }
}
bool resuelveCaso() {
    int N;
    cin >> N;
    if (!cin)
        return false;
    vector<tSol> v(N);
    string aux;
    int valor;
    tSol s;
    for (int i = 0; i < N; i++) {
        cin >> aux >> valor;
        s = { valor,aux };
        v[i] = s;

    }
    resolver(v);
    cout << "---" << endl;
    // completar...


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
