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
    bool estaOrdenada;      // Nuevo atributo
    int tipoOrdenamiento;   // Nuevo atributo: 0=ninguno, 1=burbuja, 2=shell, 3=merge

    // Métodos auxiliares privados para ordenamiento
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
                    // Intercambiar datos
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
        
        // Convertir lista a array temporal para Shell Sort
        T* arr = new T[tamano];
        Nodo<T>* actual = cabeza;
        for (int i = 0; i < tamano; i++) {
            arr[i] = actual->dato;
            actual = actual->siguiente;
        }
        
        // Shell Sort
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
        
        // Copiar array ordenado de vuelta a la lista
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
        
        // Convertir lista a array temporal para Merge Sort
        T* arr = new T[tamano];
        Nodo<T>* actual = cabeza;
        for (int i = 0; i < tamano; i++) {
            arr[i] = actual->dato;
            actual = actual->siguiente;
        }
        
        // Merge Sort
        _mergeSort(arr, 0, tamano - 1);
        
        // Copiar array ordenado de vuelta a la lista
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

    // Búsqueda binaria (solo si está ordenada)
    T* _busquedaBinaria(T info) const {
        if (!estaOrdenada) return NULL;
        
        // Convertir a array temporal para búsqueda binaria
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

    // Búsqueda lineal tradicional
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
    // Constructor
    Lista() : cabeza(NULL), cola(NULL), tamano(0), estaOrdenada(false), tipoOrdenamiento(0) {}

    // Destructor
    ~Lista() {
        while (cabeza != NULL) {
            Nodo<T>* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }
        cola = NULL;
        tamano = 0;
    }

    // Métodos básicos (SIN CAMBIOS)
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
        /*
        Método para buscar un elemento en una posición específica.
        Parámetros:
        - pos: La posición del elemento a buscar.
        Retorno:
        - Un puntero al dato si se encuentra, o NULL si la posición es inválida.
        */
        if (pos < 0 || pos >= tamano) return NULL;
        Nodo<T>* actual = cabeza;
        int i = 0;
        while (actual != NULL && i < pos) {
            actual = actual->siguiente;
            i++;
        }
        return (actual != NULL) ? &actual->dato : NULL;
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
        /*
        Operador de acceso por índice.
        Parámetros:
        - indice: El índice del elemento a acceder.
        Retorno:
        - Referencia al dato en la posición especificada.
        */
        Nodo<T>* actual = cabeza;
        int i = 0;
        while (actual && i < indice) {
            actual = actual->siguiente;
            i++;
        }
        if (!actual) throw std::out_of_range("Índice fuera de rango");
        return actual->dato;
    }
};

#endif // LISTA_H