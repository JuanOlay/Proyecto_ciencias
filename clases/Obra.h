#ifndef OBRA_H
#define OBRA_H

#include <iostream>
#include "Edicion.h"
using namespace std;

class Obra {
public:
    char nombreDocumento[100];
    char tipoPoesia[30];
    int idAutor;
    Edicion ediciones[10]; // Se permite un máximo de 10 ediciones por obra
    int cantidadEdiciones;

    Obra() {
        nombreDocumento[0] = '\0';
        tipoPoesia[0] = '\0';
        idAutor = 0;
        cantidadEdiciones = 0;
    }

    void agregarEdicion(const Edicion& ed) {
        if (cantidadEdiciones < 10) {
            ediciones[cantidadEdiciones] = ed;
            cantidadEdiciones++;
        } else {
            cout << "No se pueden agregar más ediciones a esta obra." << endl;
        }
    }

    void mostrar() {
        cout << "Nombre del documento: " << nombreDocumento << endl;
        cout << "Tipo de poesía: " << tipoPoesia << endl;
        cout << "ID del autor: " << idAutor << endl;
        cout << "Ediciones:" << endl;
        for (int i = 0; i < cantidadEdiciones; i++) {
            cout << "  Edición " << (i + 1) << ":" << endl;
            ediciones[i].mostrar();
        }
    }
};

#endif
