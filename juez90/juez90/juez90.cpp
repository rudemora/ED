// juez90.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <cassert>
#include <iostream>
#include <iterator>
#include <memory>
#include <queue>
#include <stack>
#include <fstream>

using namespace std;

template <class T> class BinTree {

private:
    struct TreeNode;
    using NodePointer = std::shared_ptr<TreeNode>;

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

    template <typename U> void preorder(U func) const {
        preorder(root_node, func);
    }

    template <typename U> void inorder(U func) const {
        std::stack<NodePointer> st;

        descend_and_push(root_node, st);

        while (!st.empty()) {
            NodePointer current = st.top();
            st.pop();

            func(current->elem);

            descend_and_push(current->right, st);
        }
    }

    template <typename U> void postorder(U func) const {
        postorder(root_node, func);
    }

    void levelorder() const;

    class iterator {
    public:
        const T& operator*() const {
            assert(!st.empty());
            return st.top()->elem;
        }

        const T* operator->() const { return &operator*(); }

        iterator& operator++() {
            assert(!st.empty());
            NodePointer top = st.top();
            st.pop();
            BinTree::descend_and_push(top->right, st);
            return *this;
        }

        iterator operator++(int) {
            iterator previous = *this;
            ++(*this);
            return previous;
        }

        bool operator==(const iterator& other) const { return st == other.st; }

        bool operator!=(const iterator& other) const {
            return !this->operator==(other);
        }

    private:
        friend class BinTree;

        iterator() {}

        iterator(const NodePointer& root) { BinTree::descend_and_push(root, st); }

        std::stack<NodePointer> st;
    };

    iterator begin() const { return iterator(root_node); }

    iterator end() const { return iterator(); }

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

    static void descend_and_push(const NodePointer& node,
        std::stack<NodePointer>& st);

    template <typename U> static void preorder(const NodePointer& node, U func);

    template <typename U> static void postorder(const NodePointer& node, U func);
};

template <typename T>
void BinTree<T>::descend_and_push(const NodePointer& node,
    stack<NodePointer>& st) {
    NodePointer current = node;
    while (current != nullptr) {
        st.push(current);
        current = current->left;
    }
}

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
template <typename U>
void BinTree<T>::postorder(const NodePointer& node, U func) {
    if (node != nullptr) {
        postorder(node->left, func);
        postorder(node->right, func);
        func(node->elem);
    }
}

template <typename T>
void BinTree<T>::levelorder() const {
    std::queue<NodePointer> pending;
    if (root_node != nullptr) {
        pending.push(root_node);
    }
    while (!pending.empty()) {
        NodePointer current = pending.front();
        pending.pop();
        cout << current->elem;
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

/*@ <answer> */

template <typename T>
int resolver(BinTree<T>& arbol) {
    std::queue<BinTree<T>> pending;
    if (arbol.empty()) {
        return 0;
    }
    else if (!arbol.empty()) {
        pending.push(arbol);
    }
    int contador = 0;
    int maximoI = pending.front().root();
    int maximoI1 = 0;
    while (!pending.empty()) {
        int tam = pending.size();
        for (int i = 0; i < tam; i++) {
            auto a = pending.front();
            pending.pop();
            if (!a.left().empty() && !a.right().empty()) {
                pending.push(a.left());
                pending.push(a.right());
                maximoI1 = max(a.left().root(), max(a.right().root(), maximoI1));
            }
            else if (!a.right().empty()) {
                pending.push(a.right());
                maximoI1 = max(maximoI1, a.right().root());
            }
            else if (!a.left().empty()) {
                pending.push(a.left());
                maximoI1 = max(maximoI1, a.left().root());
            }


        }
        if (maximoI1 > maximoI) {
            contador += 1;
        }
        maximoI = maximoI1;
        maximoI1 = 0;
    }    
    return contador;
}

int num_aventajados(BinTree<int> &tree) {
    int sol = resolver(tree);
    return sol;
}

void resuelveCaso() {
    BinTree<int> tree = read_tree<int>(cin);
    cout << num_aventajados(tree) << "\n";
}


/*@ </answer> */

int main()
{
#ifndef DOMJUDGE
    std::ifstream in("datos.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
    std::ofstream out("datos.out");
    auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif
    int numCasos; 
    cin >> numCasos;
    for (int i = 0; i < numCasos; i++) {
        resuelveCaso();
    }
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
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
