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
#include "Entidades.h"
#include <iostream>
#include <stdexcept>

template <class T>
class Lista {
    /*
    Clase Lista: Representa una lista enlazada simple con dos punteros.
    Atributos:
    - cabeza: Puntero al primer nodo de la lista.
    - cola: Puntero al último nodo de la lista.
    - tamano: Tamaño actual de la lista.
    - estaOrdenada: Indica si la lista está ordenada (nuevo atributo).
    - tipoOrdenamiento: Tipo de algoritmo usado para ordenar (nuevo atributo).
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
    bool estaOrdenada;
    int tipoOrdenamiento;   // 0=ninguno, 1=burbuja, 2=shell, 3=merge

    void _ordenarSegunTamano() {
        if (tamano <= 1 || estaOrdenada) return;

        if (tamano < 1000) {
            _ordenamientoBurbuja();
        } else if (tamano < 3000) {
            _ordenamientoShell();
        } else {
            _ordenamientoMerge();
        }
    }

    void _ordenamientoBurbuja() {
        if (tamano <= 1) return;
        
        bool intercambio;
        do {
            intercambio = false;
            Nodo<T>* actual = cabeza;
            while (actual != NULL && actual->siguiente != NULL) {
                if (actual->dato > actual->siguiente->dato) {
                    T temp = actual->dato;
                    actual->dato = actual->siguiente->dato;
                    actual->siguiente->dato = temp;
                    intercambio = true;
                }
                actual = actual->siguiente;
            }
        } while (intercambio);
        
        estaOrdenada = true;
        tipoOrdenamiento = 1;
    }

    void _ordenamientoShell() {
        if (tamano <= 1) return;
        
        T* arr = new T[tamano];
        Nodo<T>* actual = cabeza;
        for (int i = 0; i < tamano; i++) {
            arr[i] = actual->dato;
            actual = actual->siguiente;
        }
        
        for (int gap = tamano / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < tamano; i++) {
                T temp = arr[i];
                int j;
                for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                    arr[j] = arr[j - gap];
                }
                arr[j] = temp;
            }
        }
        
        actual = cabeza;
        for (int i = 0; i < tamano; i++) {
            actual->dato = arr[i];
            actual = actual->siguiente;
        }
        
        delete[] arr;
        estaOrdenada = true;
        tipoOrdenamiento = 2;
    }

    void _ordenamientoMerge() {
        if (tamano <= 1) return;
        
        T* arr = new T[tamano];
        Nodo<T>* actual = cabeza;
        for (int i = 0; i < tamano; i++) {
            arr[i] = actual->dato;
            actual = actual->siguiente;
        }
        
        _mergeSort(arr, 0, tamano - 1);
        
        actual = cabeza;
        for (int i = 0; i < tamano; i++) {
            actual->dato = arr[i];
            actual = actual->siguiente;
        }
        
        delete[] arr;
        estaOrdenada = true;
        tipoOrdenamiento = 3;
    }

    void _mergeSort(T* arr, int izq, int der) {
        if (izq < der) {
            int medio = izq + (der - izq) / 2;
            _mergeSort(arr, izq, medio);
            _mergeSort(arr, medio + 1, der);
            _merge(arr, izq, medio, der);
        }
    }

    void _merge(T* arr, int izq, int medio, int der) {
        int n1 = medio - izq + 1;
        int n2 = der - medio;
        
        T* L = new T[n1];
        T* R = new T[n2];
        
        for (int i = 0; i < n1; i++)
            L[i] = arr[izq + i];
        for (int j = 0; j < n2; j++)
            R[j] = arr[medio + 1 + j];
        
        int i = 0, j = 0, k = izq;
        
        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                arr[k] = L[i];
                i++;
            } else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }
        
        while (i < n1) {
            arr[k] = L[i];
            i++;
            k++;
        }
        
        while (j < n2) {
            arr[k] = R[j];
            j++;
            k++;
        }
        
        delete[] L;
        delete[] R;
    }

    T* _busquedaBinaria(T info) const {
        if (!estaOrdenada) return NULL;
        
        T* arr = new T[tamano];
        Nodo<T>** nodos = new Nodo<T>*[tamano];
        Nodo<T>* actual = cabeza;
        
        for (int i = 0; i < tamano; i++) {
            arr[i] = actual->dato;
            nodos[i] = actual;
            actual = actual->siguiente;
        }
        
        int izq = 0, der = tamano - 1;
        T* resultado = NULL;
        
        while (izq <= der) {
            int medio = izq + (der - izq) / 2;
            if (arr[medio] == info) {
                resultado = &(nodos[medio]->dato);
                break;
            }
            if (arr[medio] < info) {
                izq = medio + 1;
            } else {
                der = medio - 1;
            }
        }
        
        delete[] arr;
        delete[] nodos;
        return resultado;
    }

    T* _busquedaLineal(T info) const {
        Nodo<T>* actual = cabeza;
        while (actual != NULL) {
            if (actual->dato == info) return &actual->dato;
            actual = actual->siguiente;
        }
        return NULL;
    }

    void _marcarComoDesordenada() {
        estaOrdenada = false;
        tipoOrdenamiento = 0;
    }

public:
    Lista() : cabeza(NULL), cola(NULL), tamano(0), estaOrdenada(false), tipoOrdenamiento(0) {}

    ~Lista() {
        while (cabeza != NULL) {
            Nodo<T>* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }
        cola = NULL;
        tamano = 0;
    }

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
        return cabeza == NULL;
    }

    void insertarInicio(T info) {
        /*
        Método para insertar un nuevo nodo al inicio de la lista.
        Ahora marca la lista como desordenada después de insertar.
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
        _marcarComoDesordenada(); // Nueva funcionalidad
    }

    void insertarFinal(T info) {
        /*
        Método para insertar un nuevo nodo al final de la lista.
        Ahora marca la lista como desordenada después de insertar.
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
        _marcarComoDesordenada(); // Nueva funcionalidad
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
            if (cabeza == NULL) cola = NULL;
            delete temp;
            tamano--;
            return;
        }

        Nodo<T>* actual = cabeza;
        while (actual->siguiente != NULL && !(actual->siguiente->dato == info)) {
            actual = actual->siguiente;
        }

        if (actual->siguiente != NULL) {
            Nodo<T>* nodoEliminar = actual->siguiente;
            actual->siguiente = nodoEliminar->siguiente;
            if (nodoEliminar == cola) cola = actual;
            delete nodoEliminar;
            tamano--;
        }
    }

    T* buscar(T info) {
        /*
        Método que busca un nodo en la lista por su dato.
        Ahora usa búsqueda optimizada: ordena la lista si no está ordenada
        y luego usa búsqueda binaria para máxima eficiencia.
        Retorna un puntero al dato si se encuentra, o NULL si no se encuentra.
        Parámetros:
        - info: El valor a buscar en la lista.
        Retorno:
        - Un puntero al dato si se encuentra, o NULL si no se encuentra.
        Si la lista está vacía, retorna NULL.
        */
        if (estaVacia()) return NULL;

        // Ordenar la lista si no está ordenada para búsqueda óptima
        if (!estaOrdenada) {
            _ordenarSegunTamano();
        }

        // Usar búsqueda binaria si está ordenada, lineal si no
        if (estaOrdenada) {
            return _busquedaBinaria(info);
        } else {
            return _busquedaLineal(info);
        }
    }
    
    T* buscarEnPos(int pos) const {
	    if (pos < 0 || pos >= tamano) return nullptr;
	    Nodo<T>* actual = cabeza;
	    for (int i = 0; i < pos; ++i) {
	        if (actual == nullptr) return nullptr; // Protecci�n extra
	        actual = actual->siguiente;
	    }
	    return (actual != nullptr) ? &actual->dato : nullptr;
	}

    void mostrar() const {
        /*
        Método para mostrar toda la lista.
        Recorre todos los nodos y muestra sus datos.
        Ahora también muestra información sobre el estado de ordenamiento.
        Parámetros: Ninguno
        Retorno: Ninguno
        */
        if (estaVacia()) {
            std::cout << "Lista vacía" << std::endl;
            return;
        }

        Nodo<T>* actual = cabeza;
        std::cout << "Lista: ";
        while (actual != NULL) {
            std::cout << actual->dato;
            if (actual->siguiente != NULL) std::cout << " -> ";
            actual = actual->siguiente;
        }
        std::cout << std::endl;
        
        // Información adicional sobre el estado de ordenamiento
        std::cout << "Tamaño: " << tamano;
        if (estaOrdenada) {
            std::cout << " | Ordenada con: ";
            switch (tipoOrdenamiento) {
                case 1: std::cout << "Burbuja"; break;
                case 2: std::cout << "Shell Sort"; break;
                case 3: std::cout << "Merge Sort"; break;
                default: std::cout << "Desconocido"; break;
            }
        } else {
            std::cout << " | No ordenada";
        }
        std::cout << std::endl;
    }

   T& operator[](int indice) {
	    if (indice < 0 || indice >= tamano)
	        throw std::out_of_range("�ndice fuera de rango");
	
	    Nodo<T>* actual = cabeza;
	    int i = 0;
	    while (actual && i < indice) {
	        actual = actual->siguiente;
	        i++;
	    }
	
	    if (!actual)
	        throw std::runtime_error("Error interno: nodo nulo en posici�n v�lida");
	
	    return actual->dato;
	}
	
	// Dentro de la clase Lista<T>
	Lista<T>& operator=(const Lista<T>& otra) {
	    if (this == &otra) return *this;
	
	    // Liberar lista actual
	    while (cabeza != nullptr) {
	        Nodo<T>* temp = cabeza;
	        cabeza = cabeza->siguiente;
	        delete temp;
	    }
	
	    cola = nullptr;
	    tamano = 0;
	
	    // Copiar elementos de la otra lista
	    Nodo<T>* actual = otra.cabeza;
	    while (actual != nullptr) {
	        insertarFinal(actual->dato);
	        actual = actual->siguiente;
	    }
	
	    estaOrdenada = otra.estaOrdenada;
	    tipoOrdenamiento = otra.tipoOrdenamiento;
	
	    return *this;
	}

};

#endif // LISTA_H