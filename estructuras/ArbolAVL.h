/*
Archivo: ArbolAVL.h
Autores: 
Juan Felipe Guevara Olaya jfguevarao@udistrital.edu.co
Jean Pierre
Melissa
*/
#ifndef ARBOLAVL_H
#define ARBOLAVL_H

#include <iostream>

template <typename T>
class NodoAVL {
    /*
    Clase que representa un nodo en el árbol AVL.

    Atributos:
    - dato: Valor almacenado en el nodo.
    - izquierdo: Puntero al subárbol izquierdo.
    - derecho: Puntero al subárbol derecho.
    - altura: Altura del nodo en el árbol.

    Metodos:
    - Constructor: Inicializa el nodo con un valor y establece los punteros izquierdo y derecho en nullptr.
    - Destructor: Libera la memoria del nodo y sus hijos.
    */

public:
    T dato;
    NodoAVL* izquierdo;
    NodoAVL* derecho;
    int altura;

    // Constructor
    NodoAVL(const T& dato) {
        this->dato = dato;
        izquierdo = derecho = nullptr;
        altura = 1;
    }
};

template <typename T>
class ArbolAVL {
    /*
    Clase que representa un árbol AVL.
    Atributos:
    - raiz: Puntero al nodo raíz del árbol.
    Metodos:
    - Constructor: Inicializa el árbol con la raíz en nullptr.
    - Destructor: Libera la memoria del árbol.
    - insertar: Inserta un nuevo dato en el árbol, manteniendo las propiedades AVL.
    - eliminar: Elimina un dato del árbol, manteniendo las propiedades AVL.
    - buscar: Busca un dato en el árbol y devuelve true si se encuentra, false en caso contrario.
    - mostrarInOrden: Muestra los datos del árbol en orden ascendente.
    */
   
private:
    NodoAVL<T>* raiz;

    int altura(NodoAVL<T>* nodo) {
        return nodo ? nodo->altura : 0;
    }

    int balance(NodoAVL<T>* nodo) {
        return nodo ? altura(nodo->izquierdo) - altura(nodo->derecho) : 0;
    }

    NodoAVL<T>* rotacionDerecha(NodoAVL<T>* y) {
        NodoAVL<T>* x = y->izquierdo;
        NodoAVL<T>* T2 = x->derecho;

        x->derecho = y;
        y->izquierdo = T2;

        y->altura = 1 + std::max(altura(y->izquierdo), altura(y->derecho));
        x->altura = 1 + std::max(altura(x->izquierdo), altura(x->derecho));

        return x;
    }

    NodoAVL<T>* rotacionIzquierda(NodoAVL<T>* x) {
        NodoAVL<T>* y = x->derecho;
        NodoAVL<T>* T2 = y->izquierdo;

        y->izquierdo = x;
        x->derecho = T2;

        x->altura = 1 + std::max(altura(x->izquierdo), altura(x->derecho));
        y->altura = 1 + std::max(altura(y->izquierdo), altura(y->derecho));

        return y;
    }

    NodoAVL<T>* insertar(NodoAVL<T>* nodo, const T& dato) {
        if (!nodo) return new NodoAVL<T>(dato);

        if (dato < nodo->dato)
            nodo->izquierdo = insertar(nodo->izquierdo, dato);
        else if (dato > nodo->dato)
            nodo->derecho = insertar(nodo->derecho, dato);
        else
            return nodo; // Dato duplicado, no se inserta

        nodo->altura = 1 + std::max(altura(nodo->izquierdo), altura(nodo->derecho));

        int balanceo = balance(nodo);

        // Casos de desbalance
        if (balanceo > 1 && dato < nodo->izquierdo->dato)
            return rotacionDerecha(nodo);

        if (balanceo < -1 && dato > nodo->derecho->dato)
            return rotacionIzquierda(nodo);

        if (balanceo > 1 && dato > nodo->izquierdo->dato) {
            nodo->izquierdo = rotacionIzquierda(nodo->izquierdo);
            return rotacionDerecha(nodo);
        }

        if (balanceo < -1 && dato < nodo->derecho->dato) {
            nodo->derecho = rotacionDerecha(nodo->derecho);
            return rotacionIzquierda(nodo);
        }

        return nodo;
    }

    NodoAVL<T>* encontrarMinimo(NodoAVL<T>* nodo) {
        while (nodo->izquierdo != nullptr)
            nodo = nodo->izquierdo;
        return nodo;
    }

    NodoAVL<T>* eliminar(NodoAVL<T>* nodo, const T& dato) {
        // Paso 1: Realizar eliminación estándar de BST
        if (!nodo) return nodo;

        if (dato < nodo->dato)
            nodo->izquierdo = eliminar(nodo->izquierdo, dato);
        else if (dato > nodo->dato)
            nodo->derecho = eliminar(nodo->derecho, dato);
        else {
            // Nodo a eliminar encontrado
            if (!nodo->izquierdo || !nodo->derecho) {
                // Caso 1: Nodo con 0 o 1 hijo
                NodoAVL<T>* temp = nodo->izquierdo ? nodo->izquierdo : nodo->derecho;
                
                if (!temp) {
                    // Caso sin hijos
                    temp = nodo;
                    nodo = nullptr;
                } else {
                    // Caso con un hijo
                    *nodo = *temp; // Copiar el contenido del hijo no vacío
                }
                delete temp;
            } else {
                // Caso 2: Nodo con dos hijos
                // Obtener el sucesor inorden (el menor en el subárbol derecho)
                NodoAVL<T>* temp = encontrarMinimo(nodo->derecho);
                
                // Copiar el dato del sucesor inorden a este nodo
                nodo->dato = temp->dato;
                
                // Eliminar el sucesor inorden
                nodo->derecho = eliminar(nodo->derecho, temp->dato);
            }
        }

        // Si el árbol tenía solo un nodo, retornar
        if (!nodo) return nodo;

        // Paso 2: Actualizar altura del nodo actual
        nodo->altura = 1 + std::max(altura(nodo->izquierdo), altura(nodo->derecho));

        // Paso 3: Obtener el factor de balance
        int balanceo = balance(nodo);

        // Paso 4: Si el nodo está desbalanceado, entonces hay 4 casos

        // Caso Izquierda Izquierda
        if (balanceo > 1 && balance(nodo->izquierdo) >= 0)
            return rotacionDerecha(nodo);

        // Caso Izquierda Derecha
        if (balanceo > 1 && balance(nodo->izquierdo) < 0) {
            nodo->izquierdo = rotacionIzquierda(nodo->izquierdo);
            return rotacionDerecha(nodo);
        }

        // Caso Derecha Derecha
        if (balanceo < -1 && balance(nodo->derecho) <= 0)
            return rotacionIzquierda(nodo);

        // Caso Derecha Izquierda
        if (balanceo < -1 && balance(nodo->derecho) > 0) {
            nodo->derecho = rotacionDerecha(nodo->derecho);
            return rotacionIzquierda(nodo);
        }

        // Retornar el nodo (sin cambios)
        return nodo;
    }

    void inOrden(NodoAVL<T>* nodo) const {
        if (nodo) {
            inOrden(nodo->izquierdo);
            std::cout << nodo->dato << " ";
            inOrden(nodo->derecho);
        }
    }

    NodoAVL<T>* buscar(NodoAVL<T>* nodo, const T& clave) const {
        if (!nodo || nodo->dato == clave) return nodo;

        if (clave < nodo->dato)
            return buscar(nodo->izquierdo, clave);
        else
            return buscar(nodo->derecho, clave);
    }

    void liberar(NodoAVL<T>* nodo) {
        if (!nodo) return;
        liberar(nodo->izquierdo);
        liberar(nodo->derecho);
        delete nodo;
    }

public:
    ArbolAVL() : raiz(nullptr) {}

    ~ArbolAVL() {
        liberar(raiz);
    }

    void insertar(const T& dato) {
        raiz = insertar(raiz, dato);
    }

    void eliminar(const T& dato) {
        raiz = eliminar(raiz, dato);
    }

    bool buscar(const T& clave) const {
        return buscar(raiz, clave) != nullptr;
    }

    void mostrarInOrden() const {
        inOrden(raiz);
    }

    bool estaVacio() const {
        return raiz == nullptr;
    }
};

#endif // ARBOLAVL_H