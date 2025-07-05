#ifndef LISTA_H
#define LISTA_H

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

template <class T>
struct nodo {
    T dato;
    nodo<T>* sig;
};

template <class T>
class Lista {
    int numElem;
    nodo<T>* cab;

public:
    Lista() : numElem(0) {
        cab = new nodo<T>; 
        cab->sig = nullptr;
    }

    bool listaVacia() {
        return cab->sig == nullptr;
    }

    void insertarInicio(T info);
    void insertarFinal(T info);
    string insertarPos(T info, int pos);
    bool borrarPos(int pos);
    string modificarPos(T info, int pos);
    T buscarPos(int pos);
    int getNumElem() {
        return numElem;
    }

    ~Lista() {
        while (!listaVacia()) {
            borrarPos(1);
        }
        delete cab;  
    }
};

// Insertar en la posición 1
template <class T>
void Lista<T>::insertarInicio(T info) {
    nodo<T>* aux = new nodo<T>;
    aux->dato = info;
    aux->sig = cab->sig;
    cab->sig = aux;
    numElem++;
}

template <class T>
void Lista<T>::insertarFinal(T info) {
    nodo<T>* aux = new nodo<T>;
    aux->dato = info;
    aux->sig = nullptr;

    nodo<T>* temp = cab;
    while (temp->sig != nullptr) {
        temp = temp->sig;
    }
    temp->sig = aux;
    numElem++;
}

template <class T>
string Lista<T>::insertarPos(T info, int pos) {
    if (pos < 1 || pos > numElem + 1) {
        return "Error: Posicion invalida.";
    }

    nodo<T>* aux = new nodo<T>;
    aux->dato = info;

    nodo<T>* temp = cab;
    for (int i = 1; i < pos; ++i) {
        temp = temp->sig;
    }

    aux->sig = temp->sig;
    temp->sig = aux;
    numElem++;

    return "Hecho";
}

template <class T>
bool Lista<T>::borrarPos(int pos) {
    if (pos < 1 || pos > numElem || listaVacia()) {
        return false;
    }

    nodo<T>* prev = cab;
    for (int i = 1; i < pos; ++i) {
        prev = prev->sig;
    }

    nodo<T>* temp = prev->sig;
    prev->sig = temp->sig;
    delete temp;
    numElem--;
    return true;
}

template <class T>
string Lista<T>::modificarPos(T info, int pos) {
    if (pos < 1 || pos > numElem || listaVacia()) {
        return "Error: Posicion invalida.";
    }

    nodo<T>* temp = cab->sig;
    for (int i = 1; i < pos; ++i) {
        temp = temp->sig;
    }

    temp->dato = info;
    return "Hecho";
}

template <class T>
T Lista<T>::buscarPos(int pos) {
    if (pos < 1 || pos > numElem || listaVacia()) {
        throw std::out_of_range("Posicion invalida");
    }

    nodo<T>* temp = cab->sig;
    for (int i = 1; i < pos; ++i) {
        temp = temp->sig;
    }

    return temp->dato;
}

#endif
