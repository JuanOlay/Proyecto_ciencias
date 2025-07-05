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
        /*
        Nodo de la multilista que contiene un dato, punteros al siguiente y anterior, y una sublista.
        Atributos:
        - dato: Almacena el valor del nodo de tipo T.
        - siguiente: Puntero al siguiente nodo en la multilista.
        - anterior: Puntero al nodo anterior en la multilista.
        - sublista: Puntero a una instancia de Lista<T> que representa la sub
        lista asociada a este nodo.
        Métodos:
        - Constructor: Inicializa el nodo con un valor y crea una nueva sublista.
        - Destructor: Limpia la memoria de la sublista.
        */
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
/*
MUY IMPORTANTE CAMBIAR ESTE METODO POR UNA BUSQUEDA CON MENOR COMPLEJIDAD ALGORITMICA
*/
    // Método auxiliar para buscar nodo
    NodoMultilista* buscarNodo(T dato) const {
        /*
        Método que busca un nodo en la multilista por su dato.
        Retorna un puntero al nodo si se encuentra, o nullptr si no se encuentra.

        Parámetros:
        - dato: El valor a buscar en la multilista.

        Retorno:
        - Un puntero al nodo si se encuentra, o nullptr si no se encuentra.
        */
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

    void insertar(T dato, bool alInicio = false) {
        /*
        Método para insertar un nuevo nodo en la multilista.
        Si alInicio es verdadero, se inserta al principio; de lo contrario, al final.
        Parámetros:
        - dato: El valor a insertar en la multilista.
        - alInicio: Indica si la inserción es al principio (true) o al final (false).
        Se hace una sobrecarga del método para permitir la inserción en ambas posiciones.
        Retorno: No retorna nada, pero modifica la estructura de la multilista.
        */
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
        /*
        Método para eliminar un nodo de la multilista.
        Retorna true si se elimina con éxito, o false si no se encuentra el nodo.
        Parámetros:
        - dato: El valor del nodo a eliminar de la multilista.
        Retorno: true si se elimina, false si no se encuentra.
        Si la multilista está vacía, retorna false.
        */
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
/*
IMPORTANTE CAMBIAR ESTE METODO NO MENTIRAS No es necesario xd */
    // Búsqueda en la multilista principal
    T* buscar(T dato) const {
        /*
        Método que busca un nodo en la multilista por su dato.
        Retorna un puntero al dato si se encuentra, o nullptr si no se encuentra.
        Parámetros:
        - dato: El valor a buscar en la multilista.
        Retorno:
        - Un puntero al dato si se encuentra, o nullptr si no se encuentra.
        Si la multilista está vacía, retorna nullptr.
        */
        NodoMultilista* nodo = buscarNodo(dato);
        return (nodo != nullptr) ? &nodo->dato : nullptr;
    }

    // OPERACIONES EN SUBLISTAS (USANDO MÉTODOS DE LISTA PARA QUE SEA MAS EFICAZ) ===

    /* NOTA : nose si se podra hacer de una forma con menos modifciaciones al metodo original xd osea solo llamando al metodo 
    tambien en mi opinion asi es mejor para solo definir el la gestion multilista siempre que se pueda y no tener que 
    definir como lista y multilista al tener la opcion de llamar los metodos de lista desde multilista nose cual opcion 
    consume menos memoria*/
    
    // Inserción en sublista 
    bool insertarEnSublista(T datoNodo, T datoSublista, bool alInicio = false) {
        /*
        Método para insertar un nuevo nodo en una sublista.
        Si alInicio es verdadero, se inserta al principio; de lo contrario, al final.
        Se hace una sobrecarga gracias al parametro alInicio si no se especifica se inserta al final.
        Parámetros:
        - datoNodo: El valor del nodo principal que contiene la sublista.
        - datoSublista: El valor a insertar en la sublista.
        - alInicio: Indica si la inserción es al principio (true) o al final (false).
        Retorno: true si se inserta con éxito, false si no se encuentra el nodo principal.
        */
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
        /*
        Método para eliminar un nodo de una sublista.
        Retorna true si se elimina con éxito, o false si no se encuentra el nodo.
        Parámetros:
        - datoNodo: El valor del nodo principal que contiene la sublista.
        - datoSublista: El valor del nodo a eliminar de la sublista.
        Retorno: true si se elimina, false si no se encuentra.
        */
        NodoMultilista* nodo = buscarNodo(datoNodo);
        if (nodo != nullptr) {
            nodo->sublista->eliminar(datoSublista);
            return true;
        }
        return false;
    }

    // Búsqueda en sublista 
    bool buscarEnSublista(T datoNodo, T datoSublista) const {
        /*
        Método que busca un nodo en una sublista por su dato.
        Retorna true si se encuentra, o false si no se encuentra.
        Parámetros:
        - datoNodo: El valor del nodo principal que contiene la sublista.
        - datoSublista: El valor a buscar en la sublista.
        Retorno:
        - true si se encuentra, o false si no se encuentra.
        */
        NodoMultilista* nodo = buscarNodo(datoNodo);
        if (nodo != nullptr) {
            return nodo->sublista->buscar(datoSublista) != nullptr;
        }
        return false;
    }

    // MÉTODOS DE INFORMACIÓN DE SUBLISTAS ===
    
    // Obtener tamaño de sublista 
    int getTamanoSublista(T datoNodo) const {
        /*
        Método para obtener el tamaño de una sublista.
        Retorna el tamaño de la sublista si se encuentra el nodo, o -1 si no se encuentra.
        Parámetros:
        - datoNodo: El valor del nodo principal que contiene la sublista.
        Retorno:
        - El tamaño de la sublista si se encuentra, o -1 si no se encuentra.
        */
        NodoMultilista* nodo = buscarNodo(datoNodo);
        return (nodo != nullptr) ? nodo->sublista->getTamano() : -1;
    }

    // Verificar si sublista está vacía 
    bool sublistaEstaVacia(T datoNodo) const {
        /*
        Método para verificar si una sublista está vacía.
        Retorna true si la sublista está vacía, o false si no lo está.
        Parámetros:
        - datoNodo: El valor del nodo principal que contiene la sublista.
        Retorno:
        - true si la sublista está vacía, o false si no lo está.
        */
        NodoMultilista* nodo = buscarNodo(datoNodo);
        return (nodo != nullptr) ? nodo->sublista->estaVacia() : true;
    }

    // MÉTODOS DE VISUALIZACIÓN ===
    
    // Mostrar toda la multilista
    void mostrar() const {
        /*
        Método para mostrar toda la multilista.
        Recorre todos los nodos principales y sus sublistas, mostrando sus datos.
        Parámetros: Ninguno
        Retorno: Ninguno
        */
        if (estaVacia()) {
            cout << "Multilista vacía" << endl;
            return;
        }

        NodoMultilista* actual = cabeza;
        cout << "------------MULTILISTA-------------" << endl;
        
        while (actual != nullptr) {
            cout << "Nodo principal: " << actual->dato << endl;
            cout << "  ";
            
            // Delegar la visualización a la Lista para evitar duplicación de código
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

    /*IMPORTANTE ESTO DEBERIA SER UNA FUNCION EN LA CLASE LISTA Y AQUI SOLO SER LLAMADA NO CONSTRUIRLA DE 0*/
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
        /*
        Método para mostrar la lista principal.
        Recorre todos los nodos principales y muestra sus datos.
        Parámetros: Ninguno
        Retorno: Ninguno
        Este método es útil para visualizar la estructura principal de la multilista sin las sublistas.
        */
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
talvez necesario en el futuro pero por ahora no se usa xd
    // MÉTODO DE ACCESO DIRECTO A SUBLISTAS 
    
    // Obtener acceso directo a una sublista para operaciones más complejas
    Lista<T>* obtenerSublista(T datoNodo) const {
        NodoMultilista* nodo = buscarNodo(datoNodo);
        return (nodo != nullptr) ? nodo->sublista : nullptr;
    }
*/

};

#endif // MULTILISTA_H