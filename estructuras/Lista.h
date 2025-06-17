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
    int getTamano() const { 
        /*
        Método para obtener el tamaño de la lista.
        Retorna el tamaño actual de la lista.
        Parámetros: Ninguno
        Retorno: El tamaño de la lista.
        */
        return tamano; 
    }
    bool estaVacia() const {
        /*
        Método para verificar si la lista está vacía.
        Retorna true si la lista está vacía, o false si no lo está.
        Parámetros: Ninguno
        Retorno: true si la lista está vacía, o false si no lo está.
        */
        return cabeza == nullptr;
    }

    void insertarInicio(T info) {
        /*
        Método para insertar un nuevo nodo al inicio de la lista.
        Parámetros:
        - info: El valor a insertar en la lista.
        Retorno: Ninguno
        */
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
        /*
        Método para insertar un nuevo nodo al final de la lista.
        Parámetros:
        - info: El valor a insertar en la lista.
        Retorno: Ninguno
        */
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
        /*
        Método para eliminar un nodo con un valor específico de la lista.
        Parámetros:
        - info: El valor del nodo a eliminar de la lista.
        Retorno: Ninguno
        */
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
        /*
        Método que busca un nodo en la lista por su dato.
        Retorna un puntero al dato si se encuentra, o nullptr si no se encuentra.
        Parámetros:
        - info: El valor a buscar en la lista.
        Retorno:
        - Un puntero al dato si se encuentra, o nullptr si no se encuentra.
        Si la lista está vacía, retorna nullptr.
        */
        Nodo<T>* actual = cabeza;
        while (actual != nullptr) {
            if (actual->dato == info) return &actual->dato;
            actual = actual->siguiente;
        }
        return nullptr;
    }

    void mostrar() const {
        /*
        Método para mostrar toda la lista.
        Recorre todos los nodos y muestra sus datos.
        Parámetros: Ninguno
        Retorno: Ninguno
        */
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
