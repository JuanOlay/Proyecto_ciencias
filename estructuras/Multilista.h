/*
Archivo: multilista.h
Autores:
Juan Felipe Guevara Olaya - jfguevarao@udistrital.edu.co
Jean Pierre
Melissa
*/

#ifndef MULTILISTA_H
#define MULTILISTA_H

#include "NodoMultilista.h"
#include "Lista.h"
#include <iostream>

template <class T>
class Multilista {
    /*
    Clase Multilista: Representa una estructura de datos de multilista bidireccional.
    Cada nodo contiene un dato y una sublista asociada.
    
    Atributos:
    - cabeza: Puntero al primer nodo de la multilista principal.
    - cola: Puntero al último nodo de la multilista principal.
    - tamano: Número de nodos en la multilista principal.
    
    Métodos:
    - Constructor: Inicializa la multilista vacía.
    - Destructor: Libera la memoria de todos los nodos y sublistas.
    - getTamano: Retorna el tamaño de la multilista principal.
    - estaVacia: Verifica si la multilista está vacía.
    - insertarInicio: Inserta un nuevo nodo al inicio de la multilista.
    - insertarFinal: Inserta un nuevo nodo al final de la multilista.
    - insertarEnSublista: Inserta un elemento en la sublista de un nodo específico.
    - eliminar: Elimina un nodo de la multilista principal.
    - eliminarDeSublista: Elimina un elemento de una sublista específica.
    - buscar: Busca un nodo en la multilista principal.
    - buscarEnSublista: Busca un elemento en la sublista de un nodo específico.
    - mostrar: Muestra toda la multilista con sus sublistas.
    - mostrarSublista: Muestra la sublista de un nodo específico.
    */

private:
    NodoMultilista<T>* cabeza;
    NodoMultilista<T>* cola;
    int tamano;

public:
    // Constructor
    Multilista() : cabeza(nullptr), cola(nullptr), tamano(0) {}

    // Destructor
    ~Multilista() {
        while (cabeza != nullptr) {
            NodoMultilista<T>* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }
        cola = nullptr;
        tamano = 0;
    }

    // Métodos básicos de información
    int getTamano() const { 
        return tamano; 
    }

    bool estaVacia() const { 
        return cabeza == nullptr; 
    }

    // Inserción en la multilista principal
    void insertarInicio(T dato) {
        NodoMultilista<T>* nuevoNodo = new NodoMultilista<T>(dato);
        
        if (estaVacia()) {
            cabeza = cola = nuevoNodo;
        } else {
            nuevoNodo->siguiente = cabeza;
            cabeza->anterior = nuevoNodo;
            cabeza = nuevoNodo;
        }
        tamano++;
    }

    void insertarFinal(T dato) {
        NodoMultilista<T>* nuevoNodo = new NodoMultilista<T>(dato);
        
        if (estaVacia()) {
            cabeza = cola = nuevoNodo;
        } else {
            cola->siguiente = nuevoNodo;
            nuevoNodo->anterior = cola;
            cola = nuevoNodo;
        }
        tamano++;
    }

    // Inserción en sublistas
    bool insertarEnSublista(T datoNodo, T datoSublista) {
        NodoMultilista<T>* nodo = buscarNodo(datoNodo);
        if (nodo != nullptr) {
            nodo->sublista->insertarFinal(datoSublista);
            return true;
        }
        return false;
    }

    bool insertarEnSublistaInicio(T datoNodo, T datoSublista) {
        NodoMultilista<T>* nodo = buscarNodo(datoNodo);
        if (nodo != nullptr) {
            nodo->sublista->insertarInicio(datoSublista);
            return true;
        }
        return false;
    }

    // Eliminación de la multilista principal
    bool eliminar(T dato) {
        if (estaVacia()) return false;

        NodoMultilista<T>* actual = cabeza;
        
        while (actual != nullptr) {
            if (actual->dato == dato) {
                // Actualizar enlaces
                if (actual->anterior != nullptr) {
                    actual->anterior->siguiente = actual->siguiente;
                } else {
                    cabeza = actual->siguiente;
                }
                
                if (actual->siguiente != nullptr) {
                    actual->siguiente->anterior = actual->anterior;
                } else {
                    cola = actual->anterior;
                }
                
                delete actual;
                tamano--;
                return true;
            }
            actual = actual->siguiente;
        }
        return false;
    }

    // Eliminación de sublistas
    bool eliminarDeSublista(T datoNodo, T datoSublista) {
        NodoMultilista<T>* nodo = buscarNodo(datoNodo);
        if (nodo != nullptr) {
            nodo->sublista->eliminar(datoSublista);
            return true;
        }
        return false;
    }

    // Búsqueda en la multilista principal
    NodoMultilista<T>* buscarNodo(T dato) const {
        NodoMultilista<T>* actual = cabeza;
        while (actual != nullptr) {
            if (actual->dato == dato) {
                return actual;
            }
            actual = actual->siguiente;
        }
        return nullptr;
    }

    T* buscar(T dato) const {
        NodoMultilista<T>* nodo = buscarNodo(dato);
        return (nodo != nullptr) ? &nodo->dato : nullptr;
    }

    // Búsqueda en sublistas
    bool buscarEnSublista(T datoNodo, T datoSublista) const {
        NodoMultilista<T>* nodo = buscarNodo(datoNodo);
        if (nodo != nullptr) {
            return nodo->sublista->buscar(datoSublista) != nullptr;
        }
        return false;
    }

    // Mostrar la multilista completa
    void mostrar() const {
        if (estaVacia()) {
            std::cout << "Multilista vacía" << std::endl;
            return;
        }

        NodoMultilista<T>* actual = cabeza;
        std::cout << "=== MULTILISTA ===" << std::endl;
        
        while (actual != nullptr) {
            std::cout << "Nodo principal: " << actual->dato << std::endl;
            std::cout << "  Sublista -> ";
            
            if (actual->sublista->estaVacia()) {
                std::cout << "vacía" << std::endl;
            } else {
                actual->sublista->mostrar();
            }
            
            std::cout << std::endl;
            actual = actual->siguiente;
        }
        std::cout << "=================" << std::endl;
    }

    // Mostrar solo una sublista específica
    void mostrarSublista(T datoNodo) const {
        NodoMultilista<T>* nodo = buscarNodo(datoNodo);
        if (nodo != nullptr) {
            std::cout << "Sublista del nodo " << datoNodo << ": ";
            nodo->sublista->mostrar();
        } else {
            std::cout << "Nodo " << datoNodo << " no encontrado" << std::endl;
        }
    }

    // Mostrar solo la multilista principal (sin sublistas)
    void mostrarPrincipal() const {
        if (estaVacia()) {
            std::cout << "Multilista vacía" << std::endl;
            return;
        }

        NodoMultilista<T>* actual = cabeza;
        std::cout << "Multilista principal: ";
        
        while (actual != nullptr) {
            std::cout << actual->dato;
            if (actual->siguiente != nullptr) {
                std::cout << " <-> ";
            }
            actual = actual->siguiente;
        }
        std::cout << std::endl;
    }

    // Obtener el tamaño de una sublista específica
    int getTamanoSublista(T datoNodo) const {
        NodoMultilista<T>* nodo = buscarNodo(datoNodo);
        return (nodo != nullptr) ? nodo->sublista->getTamano() : -1;
    }

    // Verificar si una sublista está vacía
    bool sublistaEstaVacia(T datoNodo) const {
        NodoMultilista<T>* nodo = buscarNodo(datoNodo);
        return (nodo != nullptr) ? nodo->sublista->estaVacia() : true;
    }
};

#endif // MULTILISTA_H