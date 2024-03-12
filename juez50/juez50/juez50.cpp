

/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*@ <answer>

  Introduce el nombre y apellidos de los/as componentes del grupo:

  Estudiante 1: David Esparza Sainz
  Estudiante 2: Rubén de Mora Losada

  Utilzamos un unordered_map con clave string (nombre de torre) y valor la posición de cada torre (componenteX, componenteY). Además, utilizamos
  otros 2 unordered_map, uno con clave las componente X y valores mapas ordenados con las componentes Y con esa misma X; y otro análogo para las 
  componentes Y (valor las componentes X ordenadas). La idea es utilizar mapas ordenados para todas las torres que compartan componentes X y tienen
  diferente Y y otro para todas las X que comparten componente Y ordenado con el fin de poder avanzar en coste constante en la dirección adecuada. 
  El avanzar tiene coste constante porque utilizamos iteradores para avanzar en el mapa (como mucho una posición). Sin embargo, para llegar a ese 
  iterador el coste es logaritmico porque tenemos que buscar en un mapa ordenado. Todas las demás operaciones tienen coste constante por el mismo
  motivo, excepto la funcion posicion

  @ </answer> */


  // Añade los include que necesites
#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
#include <stdexcept>
#include <map>
#include <unordered_map>
#include <vector>

    using namespace std;

// Tipo de datos para representar direcciones
// Para hacer referencia a los elementos de este tipo enumerado se utiliza:
//   Direccion::Norte, Direccion::Sur, etc.
enum class Direccion { Norte, Sur, Este, Oeste };

struct tCoor {
    int x;
    int y;
};

// Operador para leer una dirección desde un flujo de entrada.
// Ejemplo de uso:
//
// Direccion dir;
// cin >> dir;
//
istream& operator>>(istream& is, Direccion& dir) {
    string palabra; is >> palabra;
    if (palabra == "Norte") dir = Direccion::Norte;
    else if (palabra == "Sur") dir = Direccion::Sur;
    else if (palabra == "Este") dir = Direccion::Este;
    else if (palabra == "Oeste") dir = Direccion::Oeste;
    else throw std::domain_error("Lectura de direccion incorrecta");
    return is;
}

// Implementa a continuación la clase Desierto.
//@ <answer>
 //Sea k el número de torres
class Desierto {
public:

    Desierto() : torres(), torresX(), torresY() { }

    void anyadir_torre(const string& nombre, int x, int y) {  //O(logk)
        if (torres.count(nombre)) throw std::domain_error("Torre ya existente");
        if (torre_en_posicion(x, y).first) throw std::domain_error("Posicion ocupada");
        torres[nombre] = { x, y };
        torresX[x][y] = nombre;  
        torresY[y][x] = nombre;
    }

    void eliminar_torre(const string& nombre) {  //O(logk)
        if (!torres.count(nombre)) throw std::domain_error("Torre no existente");
        torresX[torres[nombre].first].erase(torres[nombre].second);
        torresY[torres[nombre].second].erase(torres[nombre].first);
        torres.erase(nombre);
    }

    pair<bool, string> torre_en_posicion(int x, int y) const {  //O(logk)
        if (torresX.count(x) && torresX.at(x).count(y)) return { true, torresX.at(x).at(y) };
        else return { false, " " };
    }

    pair<int, int> posicion(const string& nombre) const {  //O(1)
        if (!torres.count(nombre)) throw std::domain_error("Torre no existente");
        return torres.at(nombre);
    }
     
    string torre_mas_cercana(const string& nombre, const Direccion& dir) const { //O(logk)
        if (!torres.count(nombre)) throw std::domain_error("Torre no existente");
        pair<bool, string> sol = buscarTorre({ torres.at(nombre).first, torres.at(nombre).second }, dir);
        if (sol.first) return sol.second;
        else throw std::domain_error("No hay torres en esa direccion");
    }

private:

    unordered_map<string, pair<int, int>> torres;
    unordered_map<int, map<int, string>> torresY, torresX;
    pair<bool, string> buscarTorre(const tCoor& coor, const Direccion& dir) const {   
        switch (dir) {
        case Direccion::Norte: {
            auto it = torresX.at(coor.x).find(coor.y);
            it++;
            if (it == torresX.at(coor.x).end()) return { false, " " };
            else return { true, it->second };
            break;
        }
        case Direccion::Este: {
            auto it = torresY.at(coor.y).find(coor.x);
            it++;
            if (it == torresY.at(coor.y).end()) return { false, " " };
            else return { true, it->second };
            break;
        }
        case Direccion::Sur: {
            auto it = torresX.at(coor.x).find(coor.y);
            if (it == torresX.at(coor.x).begin()) return { false, " " };
            it--;
            return { true, it->second };
            break;
        }
        case Direccion::Oeste: {
            auto it = torresY.at(coor.y).find(coor.x);
            if (it == torresY.at(coor.y).begin()) return { false, " " };
            it--;
            return { true, it->second };
            break;
        }
        }
    }
};

//@ </answer>
// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------

bool resuelveCaso() {
    string inst, nombre; int x, y; Direccion dir;
    cin >> inst;
    if (!cin) return false;
    Desierto desierto;
    while (inst != "FIN") {
        try {
            if (inst == "anyadir_torre") {
                cin >> nombre >> x >> y;
                desierto.anyadir_torre(nombre, x, y);
            }
            else if (inst == "eliminar_torre") {
                cin >> nombre;
                desierto.eliminar_torre(nombre);
            }
            else if (inst == "posicion") {
                cin >> nombre;
                auto [x, y] = desierto.posicion(nombre);
                cout << x << ' ' << y << '\n';
            }
            else if (inst == "torre_en_posicion") {
                cin >> x >> y;
                auto [hay, nombre] = desierto.torre_en_posicion(x, y);
                if (hay) cout << "SI " << nombre << '\n';
                else cout << "NO\n";
            }
            else {
                cin >> nombre >> dir;
                nombre = desierto.torre_mas_cercana(nombre, dir);
                cout << nombre << '\n';
            }
        }
        catch (domain_error& e) {
            cout << e.what() << '\n';
        }
        cin >> inst;
    }
    cout << "---\n";
    return true;
}


int main() {
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso()) {}

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}

