
/*@ <answer>
 *
 * Nombre y Apellidos: Rubén de Mora Losada
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <map>
#include <vector>
    using namespace std;

struct InfoPartido {
    int votos;
};

struct InfoEstado {
    unordered_map<string, InfoPartido> partidos;
    string ganador = " ";  //Guardamos el ganador actual
    int maxVotos;  //Con el maximo de votos
    int numCompromisarios;  //El numero de compromisarios del estado
};

class Elecciones {

public:

    void nuevo_estado(const string& nombre, int num_compromisarios) {
        if (estados.count(nombre)) throw std::domain_error("Estado ya existente");
        estados[nombre].numCompromisarios = num_compromisarios;
    }

    void sumar_votos(const string& estado, const string& partido, int num_votos) {
        if (!estados.count(estado)) throw std::domain_error("Estado no encontrado");
        auto& e = estados[estado];
        auto& p = e.partidos[partido];
        p.votos += num_votos;
        if (e.maxVotos < p.votos) {  //Si el partido se convierte en la mayoria
            if (e.ganador != " ") {
                auto& ganadorAnterior = ganadores[e.ganador];
                ganadorAnterior -= e.numCompromisarios;
                if (ganadorAnterior < 1) ganadores.erase(e.ganador);  //Si el partido que ganaba anteriormente se queda sin votos se borra del mapa
            }
            ganadores[partido] += e.numCompromisarios;
            e.ganador = partido;
            e.maxVotos = p.votos;
        }
    }

    string ganador_en(const string& estado) const {
        if (!estados.count(estado)) throw std::domain_error("Estado no encontrado");
        return estados.at(estado).ganador;
    }

    vector<pair<string, int>> resultados() const {
        vector<pair<string, int>> resultado;
        for (auto& g : ganadores) {
            resultado.push_back({ g.first, g.second });
        }
        return resultado;
    }

private:
    unordered_map<string, InfoEstado> estados;
    map<string, int> ganadores;
};

bool resuelveCaso() {
    Elecciones elecciones;
    string op;
    string estado;
    string partido;
    int votos;
    int compromisarios;
    cin >> op;
    if (!std::cin) return false;
    while (op != "FIN") {
        if (op == "nuevo_estado") {
            cin >> estado >> compromisarios;
            try {
                elecciones.nuevo_estado(estado, compromisarios);
            }
            catch (std::domain_error& e) {
                cout << e.what() << '\n';
            }
        }
        else if (op == "sumar_votos") {
            cin >> estado >> partido >> votos;
            try {
                elecciones.sumar_votos(estado, partido, votos);
            }
            catch (std::domain_error& e) {
                cout << e.what() << '\n';
            }
        }
        else if (op == "ganador_en") {
            cin >> estado;
            try {
                string ganador = elecciones.ganador_en(estado);
                cout << "Ganador en " << estado << ": " << ganador << '\n';
            }
            catch (std::domain_error& e) {
                cout << e.what() << '\n';
            }
        }
        else {
            for (auto& ganador : elecciones.resultados()) {
                cout << ganador.first << ' ' << ganador.second << '\n';
            }
        }
        cin >> op;
    }
    cout << "---\n";
    return true;
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
