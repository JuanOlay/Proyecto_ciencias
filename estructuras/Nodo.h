/* 
Archivo "Nodo.h"
Autores: 
Juan Felipe Guevara Olaya jfguevarao@udistrital.edu.co
Jean Pierre
Melissa
*/
#ifndef NODO_H
#define NODO_H

template <class T>
struct Nodo {
    /*
    Clase Nodo: Representa un nodo genérico para una estructura de datos doblemente enlazada.

    Atributos:
    - dato: Almacena el valor del nodo de tipo T.
    - siguiente: Puntero al siguiente nodo en la estructura enlazada.
    - anterior: Puntero al nodo anterior en la estructura enlazada.

    Métodos:
    - Constructor: Inicializa el nodo con un valor y establece los punteros a nullptr.
    - Destructor: Limpia los punteros al destruir el nodo.
    */

    T dato;
    Nodo* siguiente;
    Nodo* anterior;

    // Constructor
    Nodo(T valor) {
        dato = valor;
        siguiente = nullptr;
        anterior = nullptr;
    }

    // Destructor
    ~Nodo() {
        siguiente = nullptr;
        anterior = nullptr;
    }
};

#endif // NODO_H