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
#include <vector>
#include <cassert>
#include <iostream>
#include <iterator>
#include <memory>
#include <queue>
#include <stack>

  // Clase para representar árboles binarios.
  // No es posible modificar esta clase para el problema de hoy
using namespace std;
template <class T> class BinTree {

private:
    struct TreeNode;
    using NodePointer = std::shared_ptr<TreeNode>;

public:
    bool sobrecarga(const BinTree<T>& tree1) const;
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

    template <typename U> void preorder(U func) const {
        preorder(root_node, func);
    }

    template <typename U> void inorder(U func) const { inorder(root_node, func); }

    template <typename U> void postorder(U func) const {
        postorder(root_node, func);
    }

    template <typename U> void levelorder(U func) const;

private:
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

    template <typename U> static void preorder(const NodePointer& node, U func);

    template <typename U> static void inorder(const NodePointer& node, U func);

    template <typename U> static void postorder(const NodePointer& node, U func);
};

template <typename T>
template <typename U>
void BinTree<T>::preorder(const NodePointer& node, U func) {
    if (node != nullptr) {
        func(node->elem);
        preorder(node->left, func);
        preorder(node->right, func);
    }
}
template <typename T>
bool  BinTree<T>::sobrecarga(const BinTree<T>& tree1) const {
    return root_node != tree1.root_node;
}

template <typename T>
template <typename U>
void BinTree<T>::inorder(const NodePointer& node, U func) {
    if (node != nullptr) {
        inorder(node->left, func);
        func(node->elem);
        inorder(node->right, func);
    }
}

template <typename T>
template <typename U>
void BinTree<T>::postorder(const NodePointer& node, U func) {
    if (node != nullptr) {
        postorder(node->left, func);
        postorder(node->right, func);
        func(node->elem);
    }
}

template <typename T>
template <typename U>
void BinTree<T>::levelorder(U func) const {
    std::queue<NodePointer> pending;
    if (root_node != nullptr) {
        pending.push(root_node);
    }
    while (!pending.empty()) {
        NodePointer current = pending.front();
        pending.pop();
        cout << current->elem << endl;
        func(current->elem);
        if (current->left != nullptr) {
            pending.push(current->left);
        }
        if (current->right != nullptr) {
            pending.push(current->right);
        }
    }
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const BinTree<T>& tree) {
    tree.display(out);
    return out;
}
template <typename T>
bool operator!=(const BinTree<T>& tree1, const BinTree<T>& tree2) {
    return tree1.sobrecarga(tree2);
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
El coste de la funcion recorrido es lineal, al igual que el recorrido en anchura, puesto que solo le hacemos modificaciones de
coste constante a cada elemento. Hacemos el recorrido en anchura del arbol llevando guardados el ultimo elemento del nivel que 
estamos recorriendo y el ultimo elemento del nivel de debajo(pero este no es definitivo, va variando segun vamos recorriendo la rama de arriba). 
Por tanto para cada elemento, si no es el ultimo elemento del nivel actualizo el ultimo elemnto del nivel de abajo(en caso de que tenga hijos).
Si si que es el ultimo elemento del nivel, introduzco en el vector solucion el front() de la cola, actualizo el ultimo elemento del nivel de abajo(si este ultimo elemento tiene hijos) y 
por ultimo paso ya al nivel de abajo (cambiando la variable ultimo elemento del nivel actual por la de ultimo elemento del nivel de abajo)
*/




vector<int> recorrido(BinTree<int>& arbol) {
std:queue<BinTree<int>> pending;
    vector<int> vector;

    BinTree<int> elem;
    BinTree<int> elem2;
    if (!arbol.empty()) {
        pending.push(arbol);
        elem = pending.front();
        vector.push_back(pending.front().root());
    }

    while (!pending.empty()) {


        BinTree<int> current = pending.front();
        pending.pop();
        if (current != elem) {
            if (!current.left().empty()) {
                pending.push(current.left());
                elem2 = current.left();
            }
            if (!current.right().empty()) {
                pending.push(current.right());
                elem2 = current.right();
            }


        }
        else {
            if (!current.left().empty()) {
                pending.push(current.left());
                elem2 = current.left();
            }
            if (!current.right().empty()) {
                pending.push(current.right());
                elem2 = current.right();
            }
            elem = elem2;
            BinTree<int> tree;
            elem2 = tree;
            if (!pending.empty()) {
                vector.push_back(pending.front().root());
            }

        }

    }
    return vector;
}

vector<int> perfil(BinTree<int> arbol) {
    vector<int> sol = recorrido(arbol);
    return sol;
}
//@ </answer>

// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------



void resuelveCaso() {
    auto arbol = read_tree<int>(cin);

    auto vperfil = perfil(arbol);
    if (!vperfil.empty()) {
        cout << vperfil[0];
        for (int i = 1; i < vperfil.size(); ++i) {
            cout << ' ' << vperfil[i];
        }
    }
    cout << '\n';
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("datos.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int casos;
    cin >> casos;
    // Resolvemos
    while (casos--) {
        resuelveCaso();
    }

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}