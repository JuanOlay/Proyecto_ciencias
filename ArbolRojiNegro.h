/*
ArbolRojiNegro.h
Autores:
Juan Felipe Guevara Olaya jfguevarao1211@udistrital.edu.co
Jean pierre
Melissa*/

#ifndef ARBOLROJINEGRO_H
#define ARBOLROJINEGRO_H

#include <iostream>
#include <string>
#include <queue>
#include <stack>

template <class T>
struct nodo {
    /*
    Estructura de un nodo
    Atributos:
    - info: Información del nodo
    - clave: Clave del nodo
    - color: Color del nodo (Rojo = 1, Negro = 0)
    */
    T info;
    int clave;
    bool color = 1; // Rojo = 1, Negro = 0
    nodo* padre = NULL;
    nodo* hijoDer = NULL;
    nodo* hijoIzq = NULL;
};

template <class T>
class ArbolRojiNegro {
    /*
    Clase que representa un árbol rojo-negro
    Atributos:
    - numElem: Número de elementos en el árbol
    - cab: Puntero a la raíz del árbol
   Métodos:
    - rotarIzquierda: Rota un nodo hacia la izquierda
    - rotarDerecha: Rota un nodo hacia la derecha
    */
private:
    int numElem;
    nodo<T>* cab;
    void rotarIzquierda(nodo<T>* nodoDescendente);
    void rotarDerecha(nodo<T>* nodoDescendente);
public:
    ArbolRojiNegro();
    void destruir(nodo<T>* r);
    ~ArbolRojiNegro();
    bool arbolVacio();
    std::string insertar (int clave, T info);
    std::string eliminar(int clave);
    nodo<T>* buscar(int clave);
    void modificar(int clave, const T& nuevaInfo);
    std::queue<T> recorridoInOrden() const;
    std::queue<T> recorridoPosOrden();
    std::queue<T> recorridoPreOrden();
    std::queue<T> recorridoPorNiveles();
};

template <class T>
ArbolRojiNegro<T>::ArbolRojiNegro(){
    /*
    Constructor de la clase ArbolRojiNegro
    Inicializa la raíz del árbol y el contador de elementos.
    Atributos:
    - cab: Puntero a la raíz del árbol, inicializado como un nodo vacío
    - numElem: Contador de elementos, inicializado a 0
    Descripción:
    Este constructor crea un árbol rojo-negro vacío. La raíz del árbol es un nodo que no contiene información y sus hijos son nulos.
    El contador de elementos se inicializa a 0.
    */
    cab = new nodo<T>;
    cab -> hijoDer = NULL;
    numElem = 0;
}

template <class T>
ArbolRojiNegro<T>::~ArbolRojiNegro() {
    /*
    Destructor de la clase ArbolRojiNegro
    Descripción:
    Este destructor se encarga de liberar la memoria ocupada por el árbol.
    */
}

template <class T>
bool ArbolRojiNegro<T>::arbolVacio() {
    /*
    Método que verifica si el árbol está vacío.
    Descripción:
    Este método comprueba si la raíz del árbol es nula, lo que indica que el árbol no contiene elementos.
    Parametros:
    Sin parametros
    Retorno:
    - true si el árbol está vacío, false en caso contrario
    */
    return cab -> hijoDer == NULL;
}

template <class T>
void ArbolRojiNegro<T>::rotarIzquierda(nodo<T>* nodoDescendente) {
    /*
    Método que rota un nodo hacia la izquierda.
    Descripción:
    Este método realiza una rotación a la izquierda en el árbol rojo-negro.
    Parametros:
    - nodoDescendente: Puntero al nodo que se va a rotar hacia la izquierda.
    Retorno:
    Sin retorno
    */
    nodo<T>* nodoAscendente = nodoDescendente->hijoDer;
    nodoDescendente->hijoDer = nodoAscendente->hijoIzq;

    if (nodoAscendente->hijoIzq != NULL) {
        nodoAscendente->hijoIzq->padre = nodoDescendente;
    }

    nodoAscendente->padre = nodoDescendente->padre;

    if (nodoDescendente->padre == NULL) {
        cab = nodoAscendente;
    } else if (nodoDescendente == nodoDescendente->padre->hijoIzq) {
        nodoDescendente->padre->hijoIzq = nodoAscendente;
    } else {
        nodoDescendente->padre->hijoDer = nodoAscendente;
    }

    nodoAscendente->hijoIzq = nodoDescendente;
    nodoDescendente->padre = nodoAscendente;
}

template <class T>
void ArbolRojiNegro<T>::rotarDerecha(nodo<T>* nodoDescendente) {
    /*
    Método que rota un nodo hacia la derecha.
    Descripción:
    Este método realiza una rotación a la derecha en el árbol rojo-negro.
    Parametros:
    - nodoDescendente: Puntero al nodo que se va a rotar hacia la derecha.
    Retorno:
    Sin retorno
    */
    nodo<T>* nodoAscendente = nodoDescendente->hijoIzq;
    nodoDescendente->hijoIzq = nodoAscendente->hijoDer;

    if (nodoAscendente->hijoDer != NULL) {
        nodoAscendente->hijoDer->padre = nodoDescendente;
    }
    nodoAscendente->padre = nodoDescendente->padre;
    if (nodoDescendente->padre == NULL) {
        cab = nodoAscendente;
    } else if (nodoDescendente == nodoDescendente->padre->hijoDer) {
        nodoDescendente->padre->hijoDer = nodoAscendente;
    } else {
        nodoDescendente->padre->hijoIzq = nodoAscendente;
    }
    nodoAscendente->hijoDer = nodoDescendente;
    nodoDescendente->padre = nodoAscendente;
}

template <class T>
std::string ArbolRojiNegro<T>::insertar(int clave, T info) {
    /*
    Método que inserta un nuevo nodo en el árbol rojo-negro.
    Descripción:
    Este método se encarga de insertar un nuevo nodo en el árbol manteniendo las propiedades del árbol rojo-negro.
    Parametros:
    - clave: La clave del nuevo nodo.
    - info: La información del nuevo nodo.
    Retorno:
    - "Hecho" si la inserción fue exitosa.
    - "Clave duplicada" si la clave ya existe en el árbol.
    */
    nodo<T>* nodoNuevo = new nodo<T>;
    nodoNuevo->clave = clave;
    nodoNuevo->info = info;
    nodo<T>* temp = cab->hijoDer;
    nodo<T>* padreTemp = cab;

    if (temp == NULL) {
        cab->hijoDer = nodoNuevo;
        nodoNuevo->padre = cab;
        nodoNuevo->color = 0; 
        return "Hecho";
    }

    while (temp != NULL) {
        padreTemp = temp;
        if (clave < temp->clave) {
            temp = temp->hijoIzq;
        } else if (clave > temp->clave) {
            temp = temp->hijoDer;
        } else {
            delete nodoNuevo;
            return "Clave duplicada";
        }
    }
    nodoNuevo->padre = padreTemp;
    if (clave < padreTemp->clave)
        padreTemp->hijoIzq = nodoNuevo;
    else
        padreTemp->hijoDer = nodoNuevo;

    while (nodoNuevo != cab->hijoDer && nodoNuevo->padre->color == 1) {
        nodo<T>* padre = nodoNuevo->padre;
        nodo<T>* abuelo = padre->padre;

        if (padre == abuelo->hijoIzq) {
            nodo<T>* tio = abuelo->hijoDer;

            if (tio != NULL && tio->color == 1) {
                padre->color = 0;
                tio->color = 0;
                abuelo->color = 1;
                nodoNuevo = abuelo;
            } else {
                if (nodoNuevo == padre->hijoDer) {
                    rotarIzquierda(padre);
                    nodoNuevo = padre;
                    padre = nodoNuevo->padre;
                    abuelo = padre->padre;
                }
                padre->color = 0;
                abuelo->color = 1;
                rotarDerecha(abuelo); 
            }

        } else {
            nodo<T>* tio = abuelo->hijoIzq;

            if (tio != NULL && tio->color == 1) {
                padre->color = 0;
                tio->color = 0;
                abuelo->color = 1;
                nodoNuevo = abuelo;
            } else {
                if (nodoNuevo == padre->hijoIzq) {
                    rotarDerecha(padre);
                    nodoNuevo = padre;
                    padre = nodoNuevo->padre;
                    abuelo = padre->padre;
                }
                padre->color = 0;
                abuelo->color = 1;
                rotarIzquierda(abuelo);
            }
        }
    }
    cab->hijoDer->color = 0;
    return "Hecho";
}

template <class T>
nodo<T>* ArbolRojiNegro<T>::buscar(int clave) {
    nodo<T>* actual = cab -> hijoDer;
    while (actual != NULL && actual->clave != clave) {
        if (clave < actual->clave)
            actual = actual->hijoIzq;
        else
            actual = actual->hijoDer;
    }
    return actual;
} 

template <class T>
std::string ArbolRojiNegro<T>::eliminar(int clave) {
    /*
    Método que elimina un nodo del árbol rojo-negro.
    Descripción:
    Este método se encarga de eliminar un nodo del árbol manteniendo las propiedades del árbol rojo-negro.
    Parametros:
    - clave: La clave del nodo a eliminar.
    Retorno:
    - "Hecho" si la eliminación fue exitosa.
    - "No se puede hacer la eliminación" si el nodo no se encuentra en el árbol.
    */
    nodo<T>* nodoABorrar = buscar(clave);
    if (nodoABorrar == NULL) return "No se puede hacer la eliminacion dado que este nodo no se encuentra en el arbol";

    nodo<T>* y = nodoABorrar;
    nodo<T>* x = NULL;
    int yColorOriginal = y->color;

    if (nodoABorrar->hijoIzq != NULL && nodoABorrar->hijoDer != NULL) {
        y = nodoABorrar->hijoDer;
        while (y->hijoIzq != NULL)
            y = y->hijoIzq;

        yColorOriginal = y->color;

        x = (y->hijoDer != NULL) ? y->hijoDer : y->hijoIzq;

        if (y->padre == nodoABorrar) {
            if (x != NULL)
                x->padre = y;
        } else {
            if (x != NULL)
                x->padre = y->padre;
            if (y->padre->hijoIzq == y)
                y->padre->hijoIzq = x;
            else
                y->padre->hijoDer = x;

            y->hijoDer = nodoABorrar->hijoDer;
            if (y->hijoDer != NULL)
                y->hijoDer->padre = y;
        }

        if (nodoABorrar->padre == NULL)
            cab->hijoDer = y;
        else if (nodoABorrar->padre->hijoIzq == nodoABorrar)
            nodoABorrar->padre->hijoIzq = y;
        else
            nodoABorrar->padre->hijoDer = y;

        y->padre = nodoABorrar->padre;
        y->hijoIzq = nodoABorrar->hijoIzq;
        if (y->hijoIzq != NULL)
            y->hijoIzq->padre = y;
        y->color = nodoABorrar->color;
    } else {
        x = (nodoABorrar->hijoIzq != NULL) ? nodoABorrar->hijoIzq : nodoABorrar->hijoDer;

        if (x != NULL)
            x->padre = nodoABorrar->padre;

        if (nodoABorrar->padre == NULL)
            cab->hijoDer = x;
        else if (nodoABorrar->padre->hijoIzq == nodoABorrar)
            nodoABorrar->padre->hijoIzq = x;
        else
            nodoABorrar->padre->hijoDer = x;
    }

    delete nodoABorrar;

    if (yColorOriginal == 0 && x != NULL) {
        nodo<T>* hermano;

        while (x != cab->hijoDer && x->color == 0) {
            if (x->padre->hijoIzq == x) {
                hermano = x->padre->hijoDer;
                if (hermano->color == 1) {
                    hermano->color = 0;
                    x->padre->color = 1;
                    rotarIzquierda(x->padre);
                    hermano = x->padre->hijoDer;
                }

                if ((hermano->hijoIzq == NULL || hermano->hijoIzq->color == 0) &&
                    (hermano->hijoDer == NULL || hermano->hijoDer->color == 0)) {
                    hermano->color = 1;
                    x = x->padre;
                } else {
                    if (hermano->hijoDer == NULL || hermano->hijoDer->color == 0) {
                        if (hermano->hijoIzq != NULL)
                            hermano->hijoIzq->color = 0;
                        hermano->color = 1;
                        rotarDerecha(hermano);
                        hermano = x->padre->hijoDer;
                    }

                    hermano->color = x->padre->color;
                    x->padre->color = 0;
                    if (hermano->hijoDer != NULL)
                        hermano->hijoDer->color = 0;
                    rotarIzquierda(x->padre);
                    x = cab->hijoDer;
                }
            } else {
                hermano = x->padre->hijoIzq;
                if (hermano->color == 1) {
                    hermano->color = 0;
                    x->padre->color = 1;
                    rotarDerecha(x->padre);
                    hermano = x->padre->hijoIzq;
                }

                if ((hermano->hijoDer == NULL || hermano->hijoDer->color == 0) &&
                    (hermano->hijoIzq == NULL || hermano->hijoIzq->color == 0)) {
                    hermano->color = 1;
                    x = x->padre;
                } else {
                    if (hermano->hijoIzq == NULL || hermano->hijoIzq->color == 0) {
                        if (hermano->hijoDer != NULL)
                            hermano->hijoDer->color = 0;
                        hermano->color = 1;
                        rotarIzquierda(hermano);
                        hermano = x->padre->hijoIzq;
                    }

                    hermano->color = x->padre->color;
                    x->padre->color = 0;
                    if (hermano->hijoIzq != NULL)
                        hermano->hijoIzq->color = 0;
                    rotarDerecha(x->padre);
                    x = cab->hijoDer;
                }
            }
        }

        if (x != NULL)
            x->color = 0;
    }

    return "Hecho";
}

template <class T>
void ArbolRojiNegro<T>::modificar(int clave, const T& nuevaInfo) {
    /*
    Método que modifica la información de un nodo en el árbol rojo-negro.
    Descripción:
    Este método se encarga de modificar la información de un nodo existente en el árbol.
    Parametros:
    - clave: La clave del nodo a modificar.
    - nuevaInfo: La nueva información que se asignará al nodo.
    Retorno:
    - "Hecho" si la modificación fue exitosa.
    - "No se encontró el nodo" si el nodo no existe en el árbol.
    */
    nodo<T>* n = buscar(clave);
    if (n != NULL)
        n->info = nuevaInfo;
}

template <class T>
void destruir(nodo<T>* r) {
    /*
    Método que destruye un nodo del árbol rojo-negro.
    Descripción:
    Este método se encarga de liberar la memoria ocupada por un nodo y sus hijos.
    Parametros:
    - r: Puntero al nodo que se va a destruir.
    Retorno:
    Sin retorno
    */
    if (r == NULL) return;
    destruir(r->hijoIzq);
    destruir(r->hijoDer);
    delete r;
}

template <class T>
std::queue<T> ArbolRojiNegro<T>::recorridoInOrden() const{
    /*
    Método que realiza un recorrido en orden del árbol rojo-negro.
    Descripción:
    Este método se encarga de recorrer el árbol en orden (izquierda, raíz, derecha) y almacenar los valores en una cola.
    Retorno:
    - Una cola con los valores del árbol en orden.
    */
    std::queue<T> resultado;
    std::stack<nodo<T>*> pila;
    nodo<T>* actual = cab->hijoDer;

    while (actual != NULL || !pila.empty()) {
        while (actual != NULL) {
            pila.push(actual);
            actual = actual->hijoIzq;
        }
        actual = pila.top();
        pila.pop();
        resultado.push(actual->info);
        actual = actual->hijoDer;
    }

    return resultado;
}

template <class T>
std::queue<T> ArbolRojiNegro<T>::recorridoPreOrden() {
    /*
    Método que realiza un recorrido en preorden del árbol rojo-negro.
    Descripción:
    Este método se encarga de recorrer el árbol en preorden (raíz, izquierda, derecha) y almacenar los valores en una cola.
    Retorno:
    - Una cola con los valores del árbol en preorden.
    */
    std::queue<T> resultado;
    if (cab->hijoDer == NULL) return resultado;

    std::stack<nodo<T>*> pila;
    pila.push(cab->hijoDer);

    while (!pila.empty()) {
        nodo<T>* actual = pila.top();
        pila.pop();
        resultado.push(actual->info);

        if (actual->hijoDer != NULL) pila.push(actual->hijoDer);
        if (actual->hijoIzq != NULL) pila.push(actual->hijoIzq);
    }

    return resultado;
}

template <class T>
std::queue<T> ArbolRojiNegro<T>::recorridoPosOrden() {
    /*
    Método que realiza un recorrido en postorden del árbol rojo-negro.
    Descripción:
    Este método se encarga de recorrer el árbol en postorden (izquierda, derecha, raíz) y almacenar los valores en una cola.
    Retorno:
    - Una cola con los valores del árbol en postorden.
    */
    std::queue<T> resultado;
    if (cab->hijoDer == NULL) return resultado;

    std::stack<nodo<T>*> s1, s2;
    s1.push(cab->hijoDer);

    while (!s1.empty()) {
        nodo<T>* actual = s1.top();
        s1.pop();
        s2.push(actual);

        if (actual->hijoIzq != NULL) s1.push(actual->hijoIzq);
        if (actual->hijoDer != NULL) s1.push(actual->hijoDer);
    }

    while (!s2.empty()) {
        resultado.push(s2.top()->info);
        s2.pop();
    }

    return resultado;
}

template <class T>
std::queue<T> ArbolRojiNegro<T>::recorridoPorNiveles() {
    /*
    Método que realiza un recorrido por niveles del árbol rojo-negro.
    Descripción:
    Este método se encarga de recorrer el árbol por niveles (de arriba hacia abajo y de izquierda a derecha) y almacenar los valores en una cola.
    Retorno:
    - Una cola con los valores del árbol por niveles.
    */
    std::queue<T> resultado;
    if (cab->hijoDer == NULL) return resultado;

    std::queue<nodo<T>*> q;
    q.push(cab->hijoDer);

    while (!q.empty()) {
        nodo<T>* actual = q.front();
        q.pop();
        resultado.push(actual->info);

        if (actual->hijoIzq != NULL) q.push(actual->hijoIzq);
        if (actual->hijoDer != NULL) q.push(actual->hijoDer);
    }

    return resultado;
}

#endif // ARBOLROJINEGRO_H