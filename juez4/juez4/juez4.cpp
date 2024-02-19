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
   *  Estudiante 1: Nombre y Apellidos
   *  Estudiante 2: Nombre y Apellidos
   *@ </answer> */

#include <iostream>
#include <cassert>
#include <fstream>
#include <vector>

using namespace std;

const int MAX_ELEMS = 2000;

/*@ <answer> */


void mostrar(vector<char>& sol) {
    for (int i = 0; i < sol.size(); i++) {
        cout << sol[i] << "";
    }
    cout << endl;
}

class Multiconjunto {
public:

    // Implementa las operaciones necesarias.
    // No olvides el coste!
    Multiconjunto()  {
        this->num_elems = 0;
    }

    void anyadir(int elem) {
        if (num_elems == 0) {
            this->elems[0].valor = elem;
            this->elems[0].multiplicidad = 1;
            num_elems += 1;
        }
        else {
            int pos = belongs(elem, 0, num_elems);
            if (pos != -1) {
                this->elems[pos].multiplicidad += 1;
            }
            else{
                int pos = exists(elem, 0, num_elems);
                for (int i = num_elems; i > pos; i--) {
                    elems[i] = elems[i - 1];
                }
                this->elems[pos].valor = elem;
                this->elems[pos].multiplicidad = 1;
                num_elems += 1;
            }
       
        }
        
    }

    void eliminar(int elem) {
            int pos = belongs(elem, 0, num_elems);
            if (pos != -1) {
                //cout << this->elems[pos].multiplicidad;
                if (this->elems[pos].multiplicidad > 1) {
                    this->elems[pos].multiplicidad -= 1;
                }
                else {
                    //cout << num_elems;
                    for (int j = pos; j < num_elems; j++) {
                        this->elems[j].multiplicidad = elems[j + 1].multiplicidad;
                        this->elems[j].valor = elems[j + 1].valor;
                    }
                    num_elems--;
                }
            }
        
    }

    bool pertenece(int elem) {
        return (belongs(elem, 0, num_elems)) != -1;
    }
    
    void resolverVerdes(vector<int>& secuencia, vector<int>& intento, vector<char>& sol) {
        //mostrar();
        for (int i = 0; i < secuencia.size(); i++) {
            if (pertenece(intento[i])) {
               // cout << secuencia[i] << " " << intento[i] << endl;
                if (secuencia[i] == intento[i] && secuencia[i] != -1) {
                    sol[i] = '#';
                    eliminar(intento[i]);
                    
                    intento[i] = -1;
                    secuencia[i] = -1;
                }
            }
            
        }             
    }

    void resolver(vector<int> & secuencia, vector<int> & intento, vector<char>& sol) {
        for (int i = 0; i < secuencia.size(); i++) {
            if (intento[i] != -1 && secuencia[i] != -1 && pertenece(intento[i])) {
                if (sol[i] != '#') {
                    sol[i] = 'O';
                    eliminar(intento[i]);
                }
            }
            else if (intento[i] != -1 && secuencia[i] != -1 && !pertenece(intento[i])) {
                sol[i] = '.';
            }
        }
    }

    void mostrar() {
        for (int i = 0; i < num_elems; i++) {
            cout << this->elems[i].valor << " " << this->elems[i].multiplicidad << "\n";
        }
        cout << "\n";
    }
private:
    struct Elem {
        int valor;
        int multiplicidad;
    };
    Elem elems[MAX_ELEMS];
    int num_elems;
    int exists(int elemento, int ini, int fin) {
        //cout << "   " << ini << " " << fin << endl;
        if (ini + 1 == fin) {
            if (elems[ini].valor < elemento){ //&& elemento < elems[fin].valor) {
                return ini + 1;
            }
            else if (elems[ini].valor == elemento) {
                return ini;
            }
        }
        else {
            int medio = (ini + fin) / 2;
            if (elems[medio].valor == elemento) {
                return medio;
            }
            else if (elemento < elems[medio].valor) {
                return exists(elemento, ini, medio);
            }
            else {
                return exists(elemento, medio, fin);
            }
        }
    }
    int belongs(int elemento, int ini, int fin) {
        //cout << "   " << ini << " " << fin << endl;
        if (ini + 1 == fin) {
            if (elems[ini].valor == elemento) {
                return ini;
            }
            else {
                return -1;
            }
        }
        else {
            int medio = (ini + fin) / 2;
            if (elems[medio].valor == elemento) {
                return medio;
            }
            else if (elemento < elems[medio].valor) {
                return belongs(elemento, ini, medio);
            }
            else {
                return belongs(elemento, medio, fin);
            }
        }
    }
};


// Función que trata un caso de prueba.
// Devuelve false si se ha leído el 0 que marca el fin de la entrada,
// o true en caso contrario.
bool tratar_caso() {
    // Implementar
    int numCasos;
    cin >> numCasos;
    if (numCasos == 0) {
        return false;
    }
    Multiconjunto multiconjunto;
    vector<int> secuencia(numCasos);
    vector<int> intento(numCasos);
    vector<char> sol(numCasos);
    int elemento;
    for (int i = 0; i < numCasos; i++) {
        cin >> elemento;
        secuencia[i] = elemento;
        multiconjunto.anyadir(elemento);
    }
    //multiconjunto.mostrar();
    //Multiconjunto sol = Multiconjunto();
    for (int i = 0; i < numCasos; i++) {
        cin >> elemento;
        intento[i] = elemento;
        //sol.anyadir(elemento);
    }
    multiconjunto.resolverVerdes(secuencia, intento, sol);
    multiconjunto.resolver(secuencia, intento, sol);  
    mostrar(sol);
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

    while (tratar_caso()) {}

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // Descomentar en Windows si la consola se cierra inmediatamente
    std::cout.rdbuf(coutbuf);
    system("PAUSE");
#endif
    return 0;
}
