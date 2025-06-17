/*
Archivo: multilista.h
Autores:
Juan Felipe Guevara Olaya - jfguevarao@udistrital.edu.co
Jean Pierre
Melissa
*/

#ifndef MULTILISTA_H
#define MULTILISTA_H

#include "Lista.h"
#include <iostream>

using namespace std;

template <class T>
class Multilista {
    /*
    Clase Multilista: Representa una estructura de datos de multilista bidireccional.
    Cada nodo contiene un dato y una sublista asociada.
    
    Atributos:
    - listaBase: Lista que maneja los nodos principales de la multilista.
    - sublistas: Mapa de sublistas asociadas a cada nodo principal.
    
    Métodos principales:
    - Constructor/Destructor: Manejo de memoria
    - getTamano/estaVacia: Información básica
    - insertar: Inserta en la lista principal (delegado a Lista)
    - insertarEnSublista: Inserta en una sublista específica
    - eliminar: Elimina de la lista principal
    - eliminarDeSublista: Elimina de una sublista específica
    - buscar: Busca en la lista principal
    - buscarEnSublista: Busca en una sublista específica
    - mostrar: Muestra toda la estructura
    - mostrarSublista: Muestra una sublista específica
    */

private:
    struct NodoMultilista {
        T dato;
        NodoMultilista* siguiente;
        NodoMultilista* anterior;
        Lista<T>* sublista;

        NodoMultilista(T valor) : dato(valor), siguiente(nullptr), anterior(nullptr), sublista(new Lista<T>()) {}
        
        ~NodoMultilista() {
            delete sublista;
        }
    };

    NodoMultilista* cabeza;
    NodoMultilista* cola;
    int tamano;

    // Método auxiliar para buscar nodo
    NodoMultilista* buscarNodo(T dato) const {
        NodoMultilista* actual = cabeza;
        while (actual != nullptr) {
            if (actual->dato == dato) {
                return actual;
            }
            actual = actual->siguiente;
        }
        return nullptr;
    }

public:
    // Constructor
    Multilista() : cabeza(nullptr), cola(nullptr), tamano(0) {}

    // Destructor
    ~Multilista() {
        while (cabeza != nullptr) {
            NodoMultilista* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }
        cola = nullptr;
        tamano = 0;
    }

    // Información básica
    int getTamano() const { 
        return tamano; 
    }

    bool estaVacia() const { 
        return cabeza == nullptr; 
    }

    // OPERACIONES EN LA LISTA PRINCIPAL ===
    
    // Inserción en la multilista principal
    void insertar(T dato, bool alInicio = false) {
        NodoMultilista* nuevoNodo = new NodoMultilista(dato);
        
        if (estaVacia()) {
            cabeza = cola = nuevoNodo;
        } else if (alInicio) {
            nuevoNodo->siguiente = cabeza;
            cabeza->anterior = nuevoNodo;
            cabeza = nuevoNodo;
        } else {
            cola->siguiente = nuevoNodo;
            nuevoNodo->anterior = cola;
            cola = nuevoNodo;
        }
        tamano++;
    }

    // Eliminación de la multilista principal
    bool eliminar(T dato) {
        if (estaVacia()) return false;

        NodoMultilista* actual = cabeza;
        
        while (actual != nullptr) {
            if (actual->dato == dato) {
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

    // Búsqueda en la multilista principal
    T* buscar(T dato) const {
        NodoMultilista* nodo = buscarNodo(dato);
        return (nodo != nullptr) ? &nodo->dato : nullptr;
    }

    // OPERACIONES EN SUBLISTAS (USANDO MÉTODOS DE LISTA) ===
    
    // Inserción en sublista 
    bool insertarEnSublista(T datoNodo, T datoSublista, bool alInicio = false) {
        NodoMultilista* nodo = buscarNodo(datoNodo);
        if (nodo != nullptr) {
            if (alInicio) {
                nodo->sublista->insertarInicio(datoSublista);
            } else {
                nodo->sublista->insertarFinal(datoSublista);
            }
            return true;
        }
        return false;
    }

    // Eliminación de sublista 
    bool eliminarDeSublista(T datoNodo, T datoSublista) {
        NodoMultilista* nodo = buscarNodo(datoNodo);
        if (nodo != nullptr) {
            nodo->sublista->eliminar(datoSublista);
            return true;
        }
        return false;
    }

    // Búsqueda en sublista 
    bool buscarEnSublista(T datoNodo, T datoSublista) const {
        NodoMultilista* nodo = buscarNodo(datoNodo);
        if (nodo != nullptr) {
            return nodo->sublista->buscar(datoSublista) != nullptr;
        }
        return false;
    }

    // MÉTODOS DE INFORMACIÓN DE SUBLISTAS ===
    
    // Obtener tamaño de sublista 
    int getTamanoSublista(T datoNodo) const {
        NodoMultilista* nodo = buscarNodo(datoNodo);
        return (nodo != nullptr) ? nodo->sublista->getTamano() : -1;
    }

    // Verificar si sublista está vacía 
    bool sublistaEstaVacia(T datoNodo) const {
        NodoMultilista* nodo = buscarNodo(datoNodo);
        return (nodo != nullptr) ? nodo->sublista->estaVacia() : true;
    }

    // MÉTODOS DE VISUALIZACIÓN ===
    
    // Mostrar toda la multilista
    void mostrar() const {
        if (estaVacia()) {
            cout << "Multilista vacía" << endl;
            return;
        }

        NodoMultilista* actual = cabeza;
        cout << "------------MULTILISTA-------------" << endl;
        
        while (actual != nullptr) {
            cout << "Nodo principal: " << actual->dato << endl;
            cout << "  ";
            
            // Delegar la visualización a la Lista
            if (actual->sublista->estaVacia()) {
                cout << "Sublista vacía" << endl;
            } else {
                actual->sublista->mostrar();
            }
            
            cout << endl;
            actual = actual->siguiente;
        }
        cout << "-------------------" << endl;
    }

    // Mostrar solo una sublista específica
    void mostrarSublista(T datoNodo) const {
        NodoMultilista* nodo = buscarNodo(datoNodo);
        if (nodo != nullptr) {
            cout << "Sublista del nodo " << datoNodo << ": ";
            nodo->sublista->mostrar();
        } else {
            cout << "Nodo " << datoNodo << " no encontrado" << endl;
        }
    }

    // Mostrar solo la multilista principal
    void mostrarPrincipal() const {
        if (estaVacia()) {
            cout << "Multilista vacía" << endl;
            return;
        }

        NodoMultilista* actual = cabeza;
        cout << "Multilista principal: ";
        
        while (actual != nullptr) {
            cout << actual->dato;
            if (actual->siguiente != nullptr) {
                cout << " <-> ";
            }
            actual = actual->siguiente;
        }
        cout << endl;
    }
/*
    // MÉTODO DE ACCESO DIRECTO A SUBLISTAS 
    
    // Obtener acceso directo a una sublista para operaciones más complejas
    Lista<T>* obtenerSublista(T datoNodo) const {
        NodoMultilista* nodo = buscarNodo(datoNodo);
        return (nodo != nullptr) ? nodo->sublista : nullptr;
    }
*/

};

#endif // MULTILISTA_H