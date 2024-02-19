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
   *  Estudiante 1: David Esparza Sainz
   *  Estudiante 2: Ruben de Mora Losada
   *@ </answer> */


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>

using namespace std;

const int MAX_RESERVAS = 50000;

/*@ <answer> */

class Teatro {
public:

    // Constructor de la clase
    // Inicializamos el vector de reservas para que tenga longitud MAX_RESERVAS
    // También inicializamos el atributo num_reservas a 0.
    Teatro() : reservas(MAX_RESERVAS), num_reservas(0) { }

    // realizar una nueva reserva, si es posible
    bool nueva_reserva(int inicio, int fin, string nombre) {//orden lineal respecto al numero de reservas en el caso peor
        if (num_reservas == 0) {
            reservas[0].nombre = nombre;
            reservas[0].fin = fin;
            reservas[0].inicio = inicio;
            num_reservas++;
            return true;
        }
        else {


            int pos = busquedaSegmento(0, num_reservas, inicio, fin);
            if (pos == -1) {
                return false;
            }
            else {

                for (int i = num_reservas; i > pos; i--) {
                    reservas[i] = reservas[i - 1];
                }
                reservas[pos] = { inicio,fin,nombre };
                num_reservas++;

            }
            return true;

        }
    }

    // consultar quién tiene reservada una butaca
    string nombre_reserva(int num_butaca) const {//orden logaritmico respecto al numero de reservas
        return busquedaButaca(0, num_reservas, num_butaca);

    }

public:
    struct Reserva {
        int inicio;
        int fin;
        string nombre;
    };

    string busquedaButaca(int ini, int fin, int inicioButaca) const { //orden logaritmico respecto a (fin-ini) (que sera como mucho el numero de reservas en la primera llamada)
        if (ini + 1 == fin) {
            if ((reservas[ini].inicio <= inicioButaca && reservas[ini].fin >= inicioButaca)) {

                return reservas[ini].nombre;
            }
            else {
                return "";
            }
        }
        int m = (ini + fin) / 2;
        if ((reservas[m].inicio <= inicioButaca && reservas[m].fin >= inicioButaca)) {
            return reservas[m].nombre;
        }
        if (reservas[m].fin < inicioButaca) {
            return busquedaButaca(m, fin, inicioButaca);
        }
        else {
            return busquedaButaca(ini, m, inicioButaca);
        }
    }

    int busquedaSegmento(int ini, int fin, int inicioButaca, int finButaca) const { //orden logaritmico respecto a (fin-ini) (que sera como mucho el numero de reservas en la primera llamada)
        if (ini + 1 == fin) {
            if ((reservas[ini].inicio <= inicioButaca && reservas[ini].fin >= inicioButaca) || (reservas[ini].inicio <= finButaca && reservas[ini].fin >= finButaca) || (reservas[ini].inicio > inicioButaca && reservas[ini].fin < finButaca)) {
                return -1;
            }
            else if (reservas[ini].inicio > inicioButaca) {
                return ini;
            }
            else {
                return ini + 1;
            }
        }
        int m = (ini + fin) / 2;
        if ((reservas[m].inicio <= inicioButaca && reservas[m].fin >= inicioButaca) || (reservas[m].inicio <= finButaca && reservas[m].fin >= finButaca) || (reservas[m].inicio > inicioButaca && reservas[m].fin < finButaca)) {
            return -1;
        }
        if (reservas[m].fin < inicioButaca) {
            return busquedaSegmento(m, fin, inicioButaca, finButaca);
        }
        else {
            return busquedaSegmento(ini, m, inicioButaca, finButaca);
        }
    }
    vector<Reserva> reservas;
    int num_reservas;

};

bool tratar_caso() {
    int N, Q;
    cin >> N >> Q;

    if (N == 0 && Q == 0)
        return false;

    Teatro t;

    for (int i = 0; i < N; ++i) {
        int inicio, fin;
        string nombre;
        cin >> inicio >> fin >> nombre;
        if (t.nueva_reserva(inicio, fin, nombre))
            cout << '.';
        else
            cout << 'X';
    }
    cout << '\n';

    for (int i = 0; i < Q; ++i) {
        int num_butaca;
        cin >> num_butaca;
        auto nombre = t.nombre_reserva(num_butaca);
        if (nombre == "")
            cout << "LIBRE\n";
        else
            cout << nombre << "\n";
    }
    cout << "---\n";
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
    std::cout.rdbuf(coutbuf);
    system("PAUSE");
#endif
    return 0;
}
