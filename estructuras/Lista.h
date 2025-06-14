/*
Archivo: Lista.h
Autores: 
Juan Felipe Guevara Olaya jfguevarao@udistrital.edu.co
Jean Pierre
Melissa
*/

#ifndef LISTA_H
#define LISTA_H

#include "Nodo.h"
#include <iostream>

template <class T>
class Lista {
    /*
    Clase Lista: Representa una lista enlazada simple con dos punteros.
    Atributos:
    - cabeza: Puntero al primer nodo de la lista.
    - cola: Puntero al último nodo de la lista.
    - tamano: Tamaño actual de la lista.
    Métodos:
    - Constructor: Inicializa la lista vacía.
    - Destructor: Libera la memoria de los nodos.
    - getTamano: Retorna el tamaño actual de la lista.
    - estaVacia: Verifica si la lista está vacía.
    - insertarInicio: Inserta un nuevo nodo al inicio de la lista.
    - insertarFinal: Inserta un nuevo nodo al final de la lista.
    - eliminar: Elimina un nodo con un valor específico de la lista.
    - buscar: Busca un nodo con un valor específico y retorna un puntero a su dato.
    - mostrar: Muestra los elementos de la lista en orden.
    */
private:
    Nodo<T>* cabeza;
    Nodo<T>* cola;
    int tamano;

public:
    // Constructor
    Lista() : cabeza(nullptr), cola(nullptr), tamano(0) {}

    // Destructor
    ~Lista() {
        while (cabeza != nullptr) {
            Nodo<T>* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }
        cola = nullptr;
        tamano = 0;
    }

    // Métodos básicos
    int getTamano() const { return tamano; }
    bool estaVacia() const { return cabeza == nullptr; }

    void insertarInicio(T info) {
        Nodo<T>* nuevoNodo = new Nodo<T>(info);
        if (estaVacia()) {
            cabeza = cola = nuevoNodo;
        } else {
            nuevoNodo->siguiente = cabeza;
            cabeza = nuevoNodo;
        }
        tamano++;
    }

    void insertarFinal(T info) {
        Nodo<T>* nuevoNodo = new Nodo<T>(info);
        if (estaVacia()) {
            cabeza = cola = nuevoNodo;
        } else {
            cola->siguiente = nuevoNodo;
            cola = nuevoNodo;
        }
        tamano++;
    }

    void eliminar(T info) {
        if (estaVacia()) return;

        if (cabeza->dato == info) {
            Nodo<T>* temp = cabeza;
            cabeza = cabeza->siguiente;
            if (cabeza == nullptr) cola = nullptr;
            delete temp;
            tamano--;
            return;
        }

        Nodo<T>* actual = cabeza;
        while (actual->siguiente != nullptr && actual->siguiente->dato != info) {
            actual = actual->siguiente;
        }

        if (actual->siguiente != nullptr) {
            Nodo<T>* nodoEliminar = actual->siguiente;
            actual->siguiente = nodoEliminar->siguiente;
            if (nodoEliminar == cola) cola = actual;
            delete nodoEliminar;
            tamano--;
        }
    }

    T* buscar(T info) const {
        Nodo<T>* actual = cabeza;
        while (actual != nullptr) {
            if (actual->dato == info) return &actual->dato;
            actual = actual->siguiente;
        }
        return nullptr;
    }

    void mostrar() const {
        if (estaVacia()) {
            std::cout << "Lista vacía" << std::endl;
            return;
        }

        Nodo<T>* actual = cabeza;
        std::cout << "Lista: ";
        while (actual != nullptr) {
            std::cout << actual->dato;
            if (actual->siguiente != nullptr) std::cout << " -> ";
            actual = actual->siguiente;
        }
        std::cout << std::endl;
    }
};

#endif // LISTA_H
