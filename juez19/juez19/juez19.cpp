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
    Estudiante 1: Nombre y Apellidos
    Estudiante 2: Nombre y Apellidos

    Dad una explicación de la solución y justificad el coste del
    algoritmo.

   *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
using namespace std;

/* ===================================================
 * Izmplementad aquí debajo vuestro algoritmo
 * ===================================================
 *@ <answer> */
struct tElementos {
    int valor;
    int pos;
};
void resolver(vector<int> const& v, int k) {
    deque<tElementos> aux;
    tElementos e;
    e = { v[0],0 };
    aux.push_front(e);
    for (int i = 1; i < k; i++) {
        while (!aux.empty() && aux.back().valor < v[i]) {
            aux.pop_back();
        }
        while (!aux.empty() && !(aux.front().pos >= (i - k + 1))) {
            aux.pop_front();
        }
        e = { v[i],i };
        aux.push_back(e);
    }
    cout << aux.front().valor << " ";

    for (int i = k; i < v.size(); i++) {
        while (!aux.empty() && aux.back().valor < v[i]) {
            aux.pop_back();
        }
        while (!aux.empty() && !(aux.front().pos >= (i - k + 1))) {
            aux.pop_front();
        }
        e = { v[i],i };
        aux.push_back(e);
        cout << aux.front().valor << " ";
    }

}
bool resuelveCaso() {
    int N, k;
    cin >> N >> k;

    if (!cin)
        return false;

    vector<int> v(N);
    for (int i = 0; i < N; i++) {
        cin >> v[i];
    }
    resolver(v, k);
    cout << endl;
    return true;
}

/*@ </answer> */

int main() {
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
    return 0;
}
