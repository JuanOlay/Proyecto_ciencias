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
    
    // Opcional: Índice hash para búsqueda O(1)
    // mutable unordered_map<TPrincipal, NodoMultilista*> indiceNodos;

    // Método auxiliar para buscar nodo - Mejorado con validación
    NodoMultilista* buscarNodo(TPrincipal dato) const {
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

    // Método auxiliar para validar nodo encontrado
    bool validarNodo(NodoMultilista* nodo, TPrincipal dato) const {
        return nodo != nullptr && nodo->dato == dato;
    }

public:
    // Constructor
    Multilista() : cabeza(nullptr), cola(nullptr), tamano(0) {}

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
        // indiceNodos.clear();
    }

    // Información básica
    int getTamano() const { 
        return tamano; 
    }

    bool estaVacia() const { 
        return cabeza == nullptr; 
    }

    // Inserción en la multilista principal
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

    // Búsqueda en la multilista principal
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
    }

    // MÉTODOS ADICIONALES DE UTILIDAD ===

    // Obtener estadísticas de la multilista
    void mostrarEstadisticas() const {
        cout << "=== ESTADÍSTICAS DE LA MULTILISTA ===" << endl;
        cout << "Nodos principales: " << tamano << endl;
        
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