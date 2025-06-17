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
    struct NodoAVL {
    /*
    Estructura que representa un nodo en el árbol AVL.
    Atributos:
    - dato: El valor almacenado en el nodo.
    - izquierdo: Puntero al subárbol izquierdo.
    - derecho: Puntero al subárbol derecho.
    - altura: La altura del nodo, utilizada para mantener el balance del árbol.
    */
    T dato;
    NodoAVL* izquierdo;
    NodoAVL* derecho;
    int altura;
    NodoAVL(const T valor) : dato(valor), izquierdo(nullptr), derecho(nullptr), altura(1) {}
    };

    NodoAVL* raiz;

    int altura(NodoAVL* nodo) {
        /*
        Función que devuelve la altura de un nodo.
        Si el nodo es nullptr, devuelve 0. De lo contrario, devuelve la altura del nodo.
        */
        return nodo ? nodo->altura : 0;
    }

    int balance(NodoAVL* nodo) {
        /*
        Función que devuelve el factor de balance de un nodo.
        El factor de balance se calcula como la altura del subárbol izquierdo menos la altura del subárbol derecho.
        */
        return nodo ? altura(nodo->izquierdo) - altura(nodo->derecho) : 0;
    }

    NodoAVL* rotacionDerecha(NodoAVL* y) {
        /*
        Realiza una rotación a la derecha en el subárbol con raíz en y.
        Este caso ocurre cuando el subárbol izquierdo es más alto que el derecho.
        Se ajustan los punteros y se recalculan las alturas de los nodos.
        Devuelve el nuevo nodo raíz del subárbol.
        1. y se convierte en el nuevo nodo raíz.
        2. El hijo izquierdo de y (x) se convierte en el nuevo nodo raíz.
        3. El hijo derecho de x (T2) se convierte en el hijo izquierdo de y.
        4. Se actualizan las alturas de y y x.
        5. Devuelve x como el nuevo nodo raíz del subárbol.
        */
        NodoAVL* x = y->izquierdo;
        NodoAVL* T2 = x->derecho;

        x->derecho = y;
        y->izquierdo = T2;

        y->altura = 1 + std::max(altura(y->izquierdo), altura(y->derecho));
        x->altura = 1 + std::max(altura(x->izquierdo), altura(x->derecho));

        return x;
    }

    NodoAVL* rotacionIzquierda(NodoAVL* x) {
        /*
        Realiza una rotación a la izquierda en el subárbol con raíz en x.
        Este caso ocurre cuando el subárbol derecho es más alto que el izquierdo.
        Se ajustan los punteros y se recalculan las alturas de los nodos.
        Devuelve el nuevo nodo raíz del subárbol.
        1. x se convierte en el nuevo nodo raíz.
        2. El hijo derecho de x (y) se convierte en el nuevo nodo raíz.
        3. El hijo izquierdo de y (T2) se convierte en el hijo derecho de x.
        4. Se actualizan las alturas de x y y.
        5. Devuelve y como el nuevo nodo raíz del subárbol.
        */
        NodoAVL* y = x->derecho;
        NodoAVL* T2 = y->izquierdo;

        y->izquierdo = x;
        x->derecho = T2;

        x->altura = 1 + std::max(altura(x->izquierdo), altura(x->derecho));
        y->altura = 1 + std::max(altura(y->izquierdo), altura(y->derecho));

        return y;
    }

    NodoAVL* insertar(NodoAVL* nodo, const T dato) {
        /*
        Función que inserta un nuevo dato en el árbol AVL.
        Si el nodo es nullptr, crea un nuevo nodo con el dato.
        Si el dato es menor que el dato del nodo actual, se inserta en el subárbol izquierdo.
        Si el dato es mayor, se inserta en el subárbol derecho.
        Si el dato ya existe, no se inserta (no se permiten duplicados).
        Después de insertar, se actualiza la altura del nodo y se verifica el balanceo.
        Si el árbol está desbalanceado, se realizan las rotaciones necesarias para restaurar el balance.
        Devuelve el nuevo nodo raíz del subárbol.
        */
        if (!nodo) return new NodoAVL(dato);

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

    NodoAVL* encontrarMinimo(NodoAVL* nodo) {
        /*
        Función que encuentra el nodo con el valor mínimo en un árbol AVL.
        Se recorre el subárbol izquierdo hasta encontrar el nodo más a la izquierda.
        */
        while (nodo->izquierdo != nullptr)
            nodo = nodo->izquierdo;
        return nodo;
    }

    NodoAVL* eliminar(NodoAVL* nodo, const T dato) {
        /*
        Función que elimina un nodo con un valor específico de un árbol AVL.
        Si el nodo es nullptr, retorna nullptr.
        Si el dato es menor que el dato del nodo actual, se elimina en el subárbol izquierdo.
        Si el dato es mayor, se elimina en el subárbol derecho.
        Después de eliminar, se actualiza la altura del nodo y se verifica el balanceo.
        Si el árbol está desbalanceado, se realizan las rotaciones necesarias para restaurar el balance.
        Devuelve el nuevo nodo raíz del subárbol.
        Parametros:
        - nodo: Puntero al nodo actual del árbol.
        - dato: El valor del nodo a eliminar.
        Retorno:
        - Puntero al nuevo nodo raíz del subárbol después de la eliminación.
        */
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
                NodoAVL* temp = nodo->izquierdo ? nodo->izquierdo : nodo->derecho;
                
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
                NodoAVL* temp = encontrarMinimo(nodo->derecho);
                
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

    void inOrden(NodoAVL* nodo) const {
        /*
        Método para realizar un recorrido en orden del árbol AVL.
        Muestra los nodos en orden ascendente.
        Parámetros:
        - nodo: Puntero al nodo actual del árbol.
        Retorno: Ninguno
        */
        if (nodo) {
            inOrden(nodo->izquierdo);
            std::cout << nodo->dato << " ";
            inOrden(nodo->derecho);
        }
    }

    NodoAVL* buscar(NodoAVL* nodo, const T clave) const {
        /*
        Método que busca un nodo en el árbol AVL por su clave.
        Retorna un puntero al nodo si se encuentra, o nullptr si no se encuentra.
        Parámetros:
        - nodo: Puntero al nodo actual del árbol.
        - clave: La clave a buscar en el árbol.
        Retorno:
        - Un puntero al nodo si se encuentra, o nullptr si no se encuentra.
        */
        if (!nodo || nodo->dato == clave) return nodo;

        if (clave < nodo->dato)
            return buscar(nodo->izquierdo, clave);
        else
            return buscar(nodo->derecho, clave);
    }

    void liberar(NodoAVL* nodo) {
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

    void insertar(const T dato) {
        raiz = insertar(raiz, dato);
    }

    void eliminar(const T dato) {
        raiz = eliminar(raiz, dato);
    }

    bool buscar(const T clave) const {
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