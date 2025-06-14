/*
Autores:
Juan Felipe Guevara Olaya - jfguevarao@udistrital.edu.co
Jean Pierre
Melissa
*/
#ifndef NODOMULTILISTA_H
#define NODOMULTILISTA_H

#include "Lista.h"

template <class T>
struct NodoMultilista {
    /*
    Clase NodoMultilista: Representa un nodo en una estructura de datos de multilista.
    Atributos:
    - dato: Almacena el valor del nodo de tipo T.
    - siguiente: Puntero al siguiente nodo en la misma dimensión.
    - anterior: Puntero al nodo anterior en la misma dimensión.
    - sublista: Puntero a una sublista asociada al nodo.
    Métodos:
    - Constructor: Inicializa el nodo con un valor y establece los punteros a nullptr.
    - Destructor: Limpia los punteros al destruir el nodo.
    */
    T dato;
    NodoMultilista* siguiente;
    NodoMultilista* anterior;
    Lista<T>* sublista;

    NodoMultilista(T valor) {
        /*
        Constructor: Inicializa el nodo con un valor y establece los punteros a nullptr.
        */
        dato = valor;
        siguiente = nullptr;
        anterior = nullptr;
        sublista = new Lista<T>();
    }

    ~NodoMultilista() {
        /*
        Destructor: Limpia los punteros al destruir el nodo.
        */
        delete sublista;
        siguiente = nullptr;
        anterior = nullptr;
    }
};

#endif // NODOMULTILISTA_H
