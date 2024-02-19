// juez2.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <fstream>
#include <cmath>

//@ <answer>
using namespace std;

class Complejo {
    double a;
    double b;
    public:
        Complejo(double real, double imaginario) {
            this->a = real;
            this->b = imaginario;
        }
        Complejo operator + (Complejo& complejo) {
            Complejo sol = Complejo(this->a + complejo.a, this->b + complejo.b);
            return sol;
        }
        Complejo operator * (Complejo& complejo) {
            Complejo sol = Complejo((this->a * complejo.a) - (this->b * complejo.b), (this->a * complejo.b) + (this->b * complejo.a));
            return sol;
        }
        double modulo() {
            return sqrt(((this->a) * (this->a)) + ((this->b) * (this->b)));
        }
};

bool resolver(Complejo& complejo, int& num, Complejo z, int iteracion) {
    if (z.modulo() > 2) {
        return false;
    }
    else {
        if (iteracion < num) {
            return resolver(complejo, num, z * z + complejo, iteracion + 1);
        }
        return true;
    }
}

void resuelveCaso() {
    double a;
    double b;
    int num;
    cin >> a >> b >> num;
    Complejo complejo(a, b);
    Complejo z(0, 0);
    bool sol = resolver(complejo, num, z, 0);
    if (!sol) {
        cout << "NO\n";
    }
    else {
        cout << "SI\n";
    }
}


//@ <answer>

int main()
{
#ifndef DOMJUDGE
    
    std::ofstream out("datos.out");
    auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif
    int numCasos;
    cin >> numCasos;
    for (int i = 0; i < numCasos; i++) {
        resuelveCaso();
    }
#ifndef DOMJUDGE
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
