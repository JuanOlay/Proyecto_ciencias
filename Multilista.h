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
#include <unordered_map>

using namespace std;

template <class TPrincipal, class TSublista>
class Multilista {
    /*
    Clase Multilista: Representa una estructura de datos de multilista bidireccional.
    Cada nodo contiene un dato y una sublista asociada.
    
    Atributos:
    - cabeza/cola: Punteros al primer y último nodo de la lista principal
    - tamano: Número de nodos en la lista principal
    - indiceNodos: Mapa hash para búsqueda O(1) (opcional)
    - estaOrdenada: Indica si la lista principal está ordenada
    - tipoOrdenamiento: Tipo de algoritmo usado para ordenar (0=ninguno, 1=burbuja, 2=shell, 3=merge, 4=quick)
    */

private:
    struct NodoMultilista {
        TPrincipal dato;
        NodoMultilista* siguiente;
        NodoMultilista* anterior;
        Lista<TSublista>* sublista;

        NodoMultilista(TPrincipal valor) : dato(valor), siguiente(nullptr), anterior(nullptr), sublista(new Lista<TSublista>()) {}
        
        ~NodoMultilista() {
            delete sublista;
        }
    };

    NodoMultilista* cabeza;
    NodoMultilista* cola;
    int tamano;
    
    // Nuevos atributos para ordenamiento optimizado
    bool estaOrdenada;
    int tipoOrdenamiento; // 0=ninguno, 1=burbuja, 2=shell, 3=merge, 4=quick
    
    // Opcional: Índice hash para búsqueda O(1)
    // mutable unordered_map<TPrincipal, NodoMultilista*> indiceNodos;

    // Métodos privados para ordenamiento automático
    void _ordenarSegunTamano() {
        if (tamano <= 1 || estaOrdenada) return;

        if (tamano < 1000) {
            _ordenamientoBurbuja();
        } else if (tamano < 3000) {
            _ordenamientoShell();
        } else {
            _ordenamientoQuick();
        }
    }

    void _ordenamientoBurbuja() {
        if (tamano <= 1) return;
        
        bool intercambio;
        do {
            intercambio = false;
            NodoMultilista* actual = cabeza;
            while (actual != nullptr && actual->siguiente != nullptr) {
                if (actual->dato > actual->siguiente->dato) {
                    // Intercambiar datos
                    TPrincipal temp = actual->dato;
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
        TPrincipal* arr = new TPrincipal[tamano];
        NodoMultilista* actual = cabeza;
        for (int i = 0; i < tamano; i++) {
            arr[i] = actual->dato;
            actual = actual->siguiente;
        }
        
        // Shell Sort
        for (int gap = tamano / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < tamano; i++) {
                TPrincipal temp = arr[i];
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

    void _ordenamientoQuick() {
        if (tamano <= 1) return;
        
        // Convertir lista a array temporal para Quick Sort
        TPrincipal* arr = new TPrincipal[tamano];
        NodoMultilista* actual = cabeza;
        for (int i = 0; i < tamano; i++) {
            arr[i] = actual->dato;
            actual = actual->siguiente;
        }
        
        // Quick Sort
        _quickSort(arr, 0, tamano - 1);
        
        // Copiar array ordenado de vuelta a la lista
        actual = cabeza;
        for (int i = 0; i < tamano; i++) {
            actual->dato = arr[i];
            actual = actual->siguiente;
        }
        
        delete[] arr;
        estaOrdenada = true;
        tipoOrdenamiento = 4;
    }

    void _quickSort(TPrincipal* arr, int bajo, int alto) {
        if (bajo < alto) {
            int pi = _particion(arr, bajo, alto);
            _quickSort(arr, bajo, pi - 1);
            _quickSort(arr, pi + 1, alto);
        }
    }

    int _particion(TPrincipal* arr, int bajo, int alto) {
        TPrincipal pivot = arr[alto];
        int i = (bajo - 1);
        
        for (int j = bajo; j <= alto - 1; j++) {
            if (arr[j] < pivot) {
                i++;
                TPrincipal temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        TPrincipal temp = arr[i + 1];
        arr[i + 1] = arr[alto];
        arr[alto] = temp;
        return (i + 1);
    }

    // Búsqueda binaria optimizada (solo si está ordenada)
    NodoMultilista* _busquedaBinaria(TPrincipal dato) const {
        if (!estaOrdenada || estaVacia()) return nullptr;
        
        // Convertir a array temporal para búsqueda binaria
        TPrincipal* arr = new TPrincipal[tamano];
        NodoMultilista** nodos = new NodoMultilista*[tamano];
        NodoMultilista* actual = cabeza;
        
        for (int i = 0; i < tamano; i++) {
            arr[i] = actual->dato;
            nodos[i] = actual;
            actual = actual->siguiente;
        }
        
        int izq = 0, der = tamano - 1;
        NodoMultilista* resultado = nullptr;
        
        while (izq <= der) {
            int medio = izq + (der - izq) / 2;
            if (arr[medio] == dato) {
                resultado = nodos[medio];
                break;
            }
            if (arr[medio] < dato) {
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
    NodoMultilista* _busquedaLineal(TPrincipal dato) const {
        if (estaVacia()) return nullptr;
        
        NodoMultilista* actual = cabeza;
        while (actual != nullptr) {
            if (actual->dato == dato) {
                return actual;
            }
            actual = actual->siguiente;
        }
        return nullptr;
    }

    void _marcarComoDesordenada() {
        estaOrdenada = false;
        tipoOrdenamiento = 0;
    }

    // Método auxiliar para buscar nodo - Mejorado con ordenamiento automático
    NodoMultilista* buscarNodo(TPrincipal dato) const {
        if (estaVacia()) return nullptr;
        
        // Ordenar la lista si no está ordenada para búsqueda óptima
        if (!estaOrdenada) {
            const_cast<Multilista*>(this)->_ordenarSegunTamano();
        }
        
        // Usar búsqueda binaria si está ordenada, lineal si no
        if (estaOrdenada) {
            return _busquedaBinaria(dato);
        } else {
            return _busquedaLineal(dato);
        }
    }

    // Método auxiliar para validar nodo encontrado
    bool validarNodo(NodoMultilista* nodo, TPrincipal dato) const {
        return nodo != nullptr && nodo->dato == dato;
    }

public:
    // Constructor
    Multilista() : cabeza(nullptr), cola(nullptr), tamano(0), estaOrdenada(false), tipoOrdenamiento(0) {}

    // Destructor
    ~Multilista() {
        limpiar();
    }

    // Método para limpiar toda la multilista
    void limpiar() {
        while (cabeza != nullptr) {
            NodoMultilista* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }
        cola = nullptr;
        tamano = 0;
        estaOrdenada = false;
        tipoOrdenamiento = 0;
        // indiceNodos.clear();
    }

    // Información básica
    int getTamano() const { 
        return tamano; 
    }

    bool estaVacia() const { 
        return cabeza == nullptr; 
    }

    // Nuevos métodos para información de ordenamiento
    bool getEstaOrdenada() const {
        return estaOrdenada;
    }

    int getTipoOrdenamiento() const {
        return tipoOrdenamiento;
    }

    string getNombreOrdenamiento() const {
        switch (tipoOrdenamiento) {
            case 1: return "Burbuja";
            case 2: return "Shell Sort";
            case 3: return "Merge Sort";
            case 4: return "Quick Sort";
            default: return "No ordenado";
        }
    }

    // Inserción en la multilista principal - Ahora marca como desordenada
    bool insertar(TPrincipal dato, bool alInicio = false) {
        try {
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
            _marcarComoDesordenada(); // Nueva funcionalidad
            // indiceNodos[dato] = nuevoNodo;
            return true;
            
        } catch (const bad_alloc& e) {
            cerr << "Error de memoria al insertar: " << e.what() << endl;
            return false;
        }
    }

    // Eliminación de la multilista principal
    bool eliminar(TPrincipal dato) {
        if (estaVacia()) return false;

        NodoMultilista* actual = buscarNodo(dato);
        if (actual == nullptr) return false;

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
        
        // indiceNodos.erase(dato);
        delete actual;
        tamano--;
        return true;
    }

    // Búsqueda en la multilista principal - Ahora optimizada
    TPrincipal* buscar(TPrincipal dato) const {
        NodoMultilista* nodo = buscarNodo(dato);
        return (nodo != nullptr) ? &nodo->dato : nullptr;
    }

    // Verificar si existe un nodo
    bool existe(TPrincipal dato) const {
        return buscarNodo(dato) != nullptr;
    }

    // OPERACIONES EN SUBLISTAS ===

    // Inserción en sublista 
    bool insertarEnSublista(TPrincipal datoNodo, TSublista datoSublista, bool alInicio = false) {
        NodoMultilista* nodo = buscarNodo(datoNodo);
        if (nodo == nullptr) return false;

        try {
            if (alInicio) {
                nodo->sublista->insertarInicio(datoSublista);
            } else {
                nodo->sublista->insertarFinal(datoSublista);
            }
            return true;
        } catch (const exception& e) {
            cerr << "Error al insertar en sublista: " << e.what() << endl;
            return false;
        }
    }

    // Eliminación de sublista 
    bool eliminarDeSublista(TPrincipal datoNodo, TSublista datoSublista) {
        NodoMultilista* nodo = buscarNodo(datoNodo);
        if (nodo == nullptr) return false;
        
        return nodo->sublista->eliminar(datoSublista);
    }

    // Búsqueda en sublista 
    bool buscarEnSublista(TPrincipal datoNodo, TSublista datoSublista) const {
        NodoMultilista* nodo = buscarNodo(datoNodo);
        if (nodo == nullptr) return false;
        
        return nodo->sublista->buscar(datoSublista) != nullptr;
    }

    // MÉTODOS DE INFORMACIÓN DE SUBLISTAS ===
    
    // Obtener tamaño de sublista 
    int getTamanoSublista(TPrincipal datoNodo) const {
        NodoMultilista* nodo = buscarNodo(datoNodo);
        return (nodo != nullptr) ? nodo->sublista->getTamano() : -1;
    }

    // Verificar si sublista está vacía 
    bool sublistaEstaVacia(TPrincipal datoNodo) const {
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
        cout << "============ MULTILISTA ============" << endl;
        cout << "Tamaño: " << tamano;
        if (estaOrdenada) {
            cout << " | Ordenada con: " << getNombreOrdenamiento();
        } else {
            cout << " | No ordenada";
        }
        cout << endl << endl;
        
        while (actual != nullptr) {
            cout << "Nodo principal: " << actual->dato << endl;
            cout << "  Sublista: ";
            
            if (actual->sublista->estaVacia()) {
                cout << "[vacía]" << endl;
            } else {
                actual->sublista->mostrar();
            }
            
            cout << endl;
            actual = actual->siguiente;
        }
        cout << "===================================" << endl;
    }

    // Mostrar solo una sublista específica
    void mostrarSublista(TPrincipal datoNodo) const {
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
        cout << "Lista principal: ";
        
        while (actual != nullptr) {
            cout << actual->dato;
            if (actual->siguiente != nullptr) {
                cout << " <-> ";
            }
            actual = actual->siguiente;
        }
        cout << endl;
        
        cout << "Estado: ";
        if (estaOrdenada) {
            cout << "Ordenada con " << getNombreOrdenamiento();
        } else {
            cout << "No ordenada";
        }
        cout << " | Tamaño: " << tamano << endl;
    }

    // MÉTODOS ADICIONALES DE UTILIDAD ===

    // Forzar ordenamiento manual
    void forzarOrdenamiento() {
        if (!estaVacia()) {
            _marcarComoDesordenada();
            _ordenarSegunTamano();
        }
    }

    // Obtener estadísticas de la multilista
    void mostrarEstadisticas() const {
        cout << "=== ESTADÍSTICAS DE LA MULTILISTA ===" << endl;
        cout << "Nodos principales: " << tamano << endl;
        cout << "Estado de ordenamiento: ";
        if (estaOrdenada) {
            cout << "Ordenada con " << getNombreOrdenamiento();
        } else {
            cout << "No ordenada";
        }
        cout << endl;
        
        if (!estaVacia()) {
            int totalSubnodos = 0;
            int sublistasVacias = 0;
            NodoMultilista* actual = cabeza;
            
            while (actual != nullptr) {
                int tamanoSub = actual->sublista->getTamano();
                totalSubnodos += tamanoSub;
                if (tamanoSub == 0) sublistasVacias++;
                actual = actual->siguiente;
            }
            
            cout << "Total de subnodos: " << totalSubnodos << endl;
            cout << "Sublistas vacías: " << sublistasVacias << endl;
            cout << "Promedio de elementos por sublista: " 
                 << (tamano > 0 ? (double)totalSubnodos / tamano : 0) << endl;
        }
        cout << "=====================================" << endl;
    }

    // Validar integridad de la estructura
    bool validarIntegridad() const {
        if (estaVacia()) return true;
        
        // Verificar enlaces hacia adelante
        NodoMultilista* actual = cabeza;
        int contador = 0;
        
        while (actual != nullptr) {
            contador++;
            if (actual->siguiente != nullptr && actual->siguiente->anterior != actual) {
                return false; // Enlaces inconsistentes
            }
            actual = actual->siguiente;
        }
        
        // Verificar que el contador coincida con el tamaño
        if (contador != tamano) return false;
        
        // Verificar que la cola sea correcta
        if (cola != nullptr) {
            actual = cola;
            while (actual->anterior != nullptr) {
                actual = actual->anterior;
            }
            if (actual != cabeza) return false;
        }
        
        return true;
    }
};

#endif // MULTILISTA_H