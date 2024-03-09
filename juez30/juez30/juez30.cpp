/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */


 /*@ <answer>

  Introduce el nombre y apellidos de los/as componentes del grupo:

  Estudiante 1: David Esparza Sainz
  Estudiante 2: Rubén de Mora Losada


  Dad una explicación de la solución y justificad su coste.

  @ </answer> */

#include <iostream>
#include <fstream>
#include <cassert>
#include <memory>
#include <utility>


  // Clase para representar árboles binarios.
  // No es posible modificar esta clase para el problema de hoy

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

template <typename T> BinTree<T> read_tree(std::istream& in) {
    char c;
    in >> c;
    if (c == '.') {
        return BinTree<T>();
    }
    else {
        assert(c == '(');
        BinTree<T> left = read_tree<T>(in);
        T elem;
        in >> elem;
        BinTree<T> right = read_tree<T>(in);
        in >> c;
        assert(c == ')');
        BinTree<T> result(left, elem, right);
        return result;
    }
}


using namespace std;


// ----------------------------------------------------------------
// Define aquí la función pedida en el enunciado.
// Puedes definir las funciones auxiliares que necesites, pero siempre
// entre las marcas <answer> y </answer>

//@ <answer>
/*
EXPLICACION DEL ALGORITMO: la idea consiste en cortar por el árbol que deje de ser completo cuanto antes( en cuanto a niveles se refiere) (Si los 2 dejan de serlo a la vez pero uno pasa a ser vacio y otro no, corto por este ultimo)
Si son simetricos me da igual por cual cortar */
tuple<int, int, int> resolver(BinTree<char> const& arbol) {
    if (arbol.empty()) {
        return{ 0,0,0 };
    }
    else {
        int acumulado;
        auto [nivel1, n1, acumulado1] = resolver(arbol.left());
        auto [nivel2, n2, acumulado2] = resolver(arbol.right());

        if (nivel1 <= nivel2) {
            acumulado = n2 + acumulado1;
        }
        else if (nivel2 < nivel1) {
            acumulado = n1 + acumulado2;
        }
        return{ min(nivel1,nivel2) + 1,n1 + n2 + 1,acumulado };

    }

}

int salvar_arbol(BinTree<char> const& arbol) {
    auto [n, m, b] = resolver(arbol);
    return b;
}

// Indica aquí el coste del algoritmo y las recurrencias planteadas en
// el caso del árbol equilibrado, y en el caso del árbol degenerado.

/*
*           { c,  n = 0
* T(n)=     { T(ni) + T(nd) + k,  n>0
* Sea n el número de nodos, ni el número de nodos de la rama izquierda y nd el número de nodos de la rama derecha (ni + nd = n)
* Como la recurrencia es igual  que la de la funcion que calcula la altura, tal y como explicaba el video, el coste es lineal independientemente de ni y nd.
*/

//@ </answer>

// ¡No modificar nada debajo de esta línea!
//
void resuelveCaso() {
    BinTree<char> arbol = read_tree<char>(cin);
    assert(!arbol.empty());
    cout << salvar_arbol(arbol) << "\n";
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("datos.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
    std::ofstream out("datos.out");
    auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif
    int num_casos;
    cin >> num_casos;
    while (num_casos--) {
        resuelveCaso();
    }
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    std::cout.rdbuf(coutbuf);
    system("PAUSE");
#endif
    return 0;
}
