/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */

 /*
  * MUY IMPORTANTE: Para realizar este ejercicio solo podéis
  * modificar el código contenido entre las etiquetas <answer>
  * y </answer>. Toda modificación fuera de esas etiquetas está
  * prohibida, pues no será corregida.
  *
  * Tampoco esta permitido modificar las líneas que contienen
  * las etiquetas <answer> y </answer>, obviamente :-)
  */

  //@ <answer>
  // Nombre y Apellidos:
  //@ </answer>

#include <iostream>
#include <fstream>
#include <memory>
#include <cassert>
#include <vector>

/*
  Implementación de la clase BinTree para representar árboles binarios.

  Para realizar este ejercicio no es necesario modificar la clase.
 */

template <class T> class BinTree {
public:
    BinTree() : root_node(nullptr) {}

    BinTree(const T& elem)
        : root_node(std::make_shared<TreeNode>(nullptr, elem, nullptr)) {}

    BinTree(const BinTree& left, const T& elem, const BinTree& right)
        : root_node(std::make_shared<TreeNode>(left.root_node, elem,
            right.root_node)) {}

    bool empty() const { return root_node == nullptr; }

    const T& root() const {
        assert(root_node != nullptr);
        return root_node->elem;
    }

    BinTree left() const {
        assert(root_node != nullptr);
        BinTree result;
        result.root_node = root_node->left;
        return result;
    }

    BinTree right() const {
        assert(root_node != nullptr);
        BinTree result;
        result.root_node = root_node->right;
        return result;
    }

    void display(std::ostream& out) const { display_node(root_node, out); }

private:
    struct TreeNode;
    using NodePointer = std::shared_ptr<TreeNode>;

    struct TreeNode {
        TreeNode(const NodePointer& left, const T& elem, const NodePointer& right)
            : elem(elem), left(left), right(right) {}

        T elem;
        NodePointer left, right;
    };

    NodePointer root_node;

    static void display_node(const NodePointer& root, std::ostream& out) {
        if (root == nullptr) {
            out << ".";
        }
        else {
            out << "(";
            display_node(root->left, out);
            out << " " << root->elem << " ";
            display_node(root->right, out);
            out << ")";
        }
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const BinTree<T>& tree) {
    tree.display(out);
    return out;
}


using namespace std;
// ----------------------------------------------------------------
// ¡No modificar nada importante por encima de esta línea!

// Implementa a continuación la función pedida. Puedes definir las funciones
// auxiliares que necesites.
//@ <answer>

BinTree<int> reconstruir(vector<int> const& preorden,
    vector<int> const& inorden) {
    
    if (preorden.size() == 0) { //|| inorden.size() == 0) { BinTree<int> arbol;
        BinTree<int> arbol;
        return arbol;
    }
    else {
        int sep = preorden[0];
        int i = 0;
        vector<int> aux1; //primer trozo del inorden
        vector<int> aux2; //segundo trozo del inorden
        vector<int> aux3; //primer trozo del preorden
        vector<int> aux4; //segundo trozo del preorden
        while (i < inorden.size() && inorden[i] != sep) {
            aux1.push_back(inorden[i]);
            i = i + 1;
        }
        i = i + 1;
        while (i < inorden.size()) {
            aux2.push_back(inorden[i]);
            i = i + 1;
        }
        i = 1;
        while (i < aux1.size() + 1) {
            aux3.push_back(preorden[i]);
            i = i + 1;
        }
        while (i < preorden.size()) {
            aux4.push_back(preorden[i]);
            i = i + 1;
        }
        BinTree<int> left  = reconstruir(aux3, aux1);
        BinTree<int> right = reconstruir(aux4, aux2);
        BinTree<int> arbol2(left, sep, right);
        return arbol2;
    }
    
}



bool resuelveCaso() {

    // leemos la entrada
    int N;
    cin >> N;
    if (!cin)
        return false;

    vector<int> preorden(N);
    for (int& c : preorden) {
        cin >> c;
    }

    vector<int> inorden(N);
    for (int& c : inorden) {
        cin >> c;
    }

    auto arbol = reconstruir(preorden, inorden);
    cout << arbol << '\n';
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
}
