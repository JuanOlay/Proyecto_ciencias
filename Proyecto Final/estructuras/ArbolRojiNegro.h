#ifndef ARBOLROJINEGRO_H
#define ARBOLROJINEGRO_H

#include <iostream>
#include <string>
#include <queue>
#include <stack>

template <class T>
struct nodo {
    T info;
    int clave;
    bool color = 1; // Rojo = 1, Negro = 0
    nodo* padre = nullptr;
    nodo* hijoDer = nullptr;
    nodo* hijoIzq = nullptr;
};

template <class T>
class ArbolRojiNegro {
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
    std::queue<T> recorridoInOrden();
    std::queue<T> recorridoPosOrden();
    std::queue<T> recorridoPreOrden();
    std::queue<T> recorridoPorNiveles();
};

template <class T>
ArbolRojiNegro<T>::ArbolRojiNegro(){
    cab = new nodo<T>;
    cab -> hijoDer = nullptr;
    numElem = 0;
}

template <class T>
ArbolRojiNegro<T>::~ArbolRojiNegro() {
}

template <class T>
bool ArbolRojiNegro<T>::arbolVacio() {
    return cab -> hijoDer == nullptr;
}

template <class T>
void ArbolRojiNegro<T>::rotarIzquierda(nodo<T>* nodoDescendente) {
    nodo<T>* nodoAscendente = nodoDescendente->hijoDer;
    nodoDescendente->hijoDer = nodoAscendente->hijoIzq;

    if (nodoAscendente->hijoIzq != nullptr) {
        nodoAscendente->hijoIzq->padre = nodoDescendente;
    }

    nodoAscendente->padre = nodoDescendente->padre;

    if (nodoDescendente->padre == nullptr) {
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
    nodo<T>* nodoAscendente = nodoDescendente->hijoIzq;
    nodoDescendente->hijoIzq = nodoAscendente->hijoDer;

    if (nodoAscendente->hijoDer != nullptr) {
        nodoAscendente->hijoDer->padre = nodoDescendente;
    }

    nodoAscendente->padre = nodoDescendente->padre;

    if (nodoDescendente->padre == nullptr) {
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
    nodo<T>* nodoNuevo = new nodo<T>;
    nodoNuevo->clave = clave;
    nodoNuevo->info = info;
    nodo<T>* temp = cab->hijoDer;
    nodo<T>* padreTemp = cab;

    if (temp == nullptr) {
        cab->hijoDer = nodoNuevo;
        nodoNuevo->padre = cab;
        nodoNuevo->color = 0; 
        return "Hecho";
    }

    while (temp != nullptr) {
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

            if (tio != nullptr && tio->color == 1) {
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

            if (tio != nullptr && tio->color == 1) {
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
    while (actual != nullptr && actual->clave != clave) {
        if (clave < actual->clave)
            actual = actual->hijoIzq;
        else
            actual = actual->hijoDer;
    }
    return actual;
} 

template <class T>
std::string ArbolRojiNegro<T>::eliminar(int clave) {
    nodo<T>* nodoABorrar = buscar(clave);
    if (nodoABorrar == nullptr) return "No se puede hacer la eliminacion dado que este nodo no se encuentra en el arbol";

    nodo<T>* y = nodoABorrar;
    nodo<T>* x = nullptr;
    int yColorOriginal = y->color;


    if (nodoABorrar->hijoIzq != nullptr && nodoABorrar->hijoDer != nullptr) {
        y = nodoABorrar->hijoDer;
        while (y->hijoIzq != nullptr)
            y = y->hijoIzq;

        yColorOriginal = y->color;

        x = (y->hijoDer != nullptr) ? y->hijoDer : y->hijoIzq;

        if (y->padre == nodoABorrar) {
            if (x != nullptr)
                x->padre = y;
        } else {
            if (x != nullptr)
                x->padre = y->padre;
            if (y->padre->hijoIzq == y)
                y->padre->hijoIzq = x;
            else
                y->padre->hijoDer = x;

            y->hijoDer = nodoABorrar->hijoDer;
            if (y->hijoDer != nullptr)
                y->hijoDer->padre = y;
        }

        if (nodoABorrar->padre == nullptr)
            cab->hijoDer = y;
        else if (nodoABorrar->padre->hijoIzq == nodoABorrar)
            nodoABorrar->padre->hijoIzq = y;
        else
            nodoABorrar->padre->hijoDer = y;

        y->padre = nodoABorrar->padre;
        y->hijoIzq = nodoABorrar->hijoIzq;
        if (y->hijoIzq != nullptr)
            y->hijoIzq->padre = y;
        y->color = nodoABorrar->color;
    } else {
        x = (nodoABorrar->hijoIzq != nullptr) ? nodoABorrar->hijoIzq : nodoABorrar->hijoDer;

        if (x != nullptr)
            x->padre = nodoABorrar->padre;

        if (nodoABorrar->padre == nullptr)
            cab->hijoDer = x;
        else if (nodoABorrar->padre->hijoIzq == nodoABorrar)
            nodoABorrar->padre->hijoIzq = x;
        else
            nodoABorrar->padre->hijoDer = x;
    }

    delete nodoABorrar;

    if (yColorOriginal == 0 && x != nullptr) {
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

                if ((hermano->hijoIzq == nullptr || hermano->hijoIzq->color == 0) &&
                    (hermano->hijoDer == nullptr || hermano->hijoDer->color == 0)) {
                    hermano->color = 1;
                    x = x->padre;
                } else {
                    if (hermano->hijoDer == nullptr || hermano->hijoDer->color == 0) {
                        if (hermano->hijoIzq != nullptr)
                            hermano->hijoIzq->color = 0;
                        hermano->color = 1;
                        rotarDerecha(hermano);
                        hermano = x->padre->hijoDer;
                    }

                    hermano->color = x->padre->color;
                    x->padre->color = 0;
                    if (hermano->hijoDer != nullptr)
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

                if ((hermano->hijoDer == nullptr || hermano->hijoDer->color == 0) &&
                    (hermano->hijoIzq == nullptr || hermano->hijoIzq->color == 0)) {
                    hermano->color = 1;
                    x = x->padre;
                } else {
                    if (hermano->hijoIzq == nullptr || hermano->hijoIzq->color == 0) {
                        if (hermano->hijoDer != nullptr)
                            hermano->hijoDer->color = 0;
                        hermano->color = 1;
                        rotarIzquierda(hermano);
                        hermano = x->padre->hijoIzq;
                    }

                    hermano->color = x->padre->color;
                    x->padre->color = 0;
                    if (hermano->hijoIzq != nullptr)
                        hermano->hijoIzq->color = 0;
                    rotarDerecha(x->padre);
                    x = cab->hijoDer;
                }
            }
        }

        if (x != nullptr)
            x->color = 0;
    }

    return "Hecho";
}

template <class T>
void ArbolRojiNegro<T>::modificar(int clave, const T& nuevaInfo) {
    nodo<T>* n = buscar(clave);
    if (n != nullptr)
        n->info = nuevaInfo;
}

template <class T>
void destruir(nodo<T>* r) {
    if (r == nullptr) return;
    destruir(r->hijoIzq);
    destruir(r->hijoDer);
    delete r;
}

template <class T>
std::queue<T> ArbolRojiNegro<T>::recorridoInOrden() {
    std::queue<T> resultado;
    std::stack<nodo<T>*> pila;
    nodo<T>* actual = cab->hijoDer;

    while (actual != nullptr || !pila.empty()) {
        while (actual != nullptr) {
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
    std::queue<T> resultado;
    if (cab->hijoDer == nullptr) return resultado;

    std::stack<nodo<T>*> pila;
    pila.push(cab->hijoDer);

    while (!pila.empty()) {
        nodo<T>* actual = pila.top();
        pila.pop();
        resultado.push(actual->info);

        if (actual->hijoDer != nullptr) pila.push(actual->hijoDer);
        if (actual->hijoIzq != nullptr) pila.push(actual->hijoIzq);
    }

    return resultado;
}

template <class T>
std::queue<T> ArbolRojiNegro<T>::recorridoPosOrden() {
    std::queue<T> resultado;
    if (cab->hijoDer == nullptr) return resultado;

    std::stack<nodo<T>*> s1, s2;
    s1.push(cab->hijoDer);

    while (!s1.empty()) {
        nodo<T>* actual = s1.top();
        s1.pop();
        s2.push(actual);

        if (actual->hijoIzq != nullptr) s1.push(actual->hijoIzq);
        if (actual->hijoDer != nullptr) s1.push(actual->hijoDer);
    }

    while (!s2.empty()) {
        resultado.push(s2.top()->info);
        s2.pop();
    }

    return resultado;
}

template <class T>
std::queue<T> ArbolRojiNegro<T>::recorridoPorNiveles() {
    std::queue<T> resultado;
    if (cab->hijoDer == nullptr) return resultado;

    std::queue<nodo<T>*> q;
    q.push(cab->hijoDer);

    while (!q.empty()) {
        nodo<T>* actual = q.front();
        q.pop();
        resultado.push(actual->info);

        if (actual->hijoIzq != nullptr) q.push(actual->hijoIzq);
        if (actual->hijoDer != nullptr) q.push(actual->hijoDer);
    }

    return resultado;
}


#endif