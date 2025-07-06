#ifndef CONTROLEDICIONES_H
#define CONTROLEDICIONES_H

#include "Entidades.h"
#include <iostream>
#include "Lista.h"

class ControlEdiciones {
private:
    Lista<Edicion> ediciones;

public:
    void agregar(const Edicion& ed) { ediciones.insertarFinal(ed); }

    bool eliminarPorNumero(int numero) {
        for (int i = 0; i < ediciones.getTamano(); ++i) {
            Edicion* e = ediciones.buscarEnPos(i);
            if (e != NULL && e->numeroEdicion == numero) {
                ediciones.eliminar(*e);
                return true;
            }
        }
        return false;
    }

    Edicion* buscarPorNumero(int numero) {
        for (int i = 0; i < ediciones.getTamano(); ++i) {
            Edicion* e = ediciones.buscarEnPos(i);
            if (e != NULL && e->numeroEdicion == numero) return e;
        }
        return NULL;
    }

    void mostrarTodos() const {
        for (int i = 0; i < ediciones.getTamano(); ++i) {
            Edicion* e = ediciones.buscarEnPos(i);
            if (e != NULL) {
                cout << "Ed. #" << e->numeroEdicion << " - " << e->fechaPublicacion << endl;
            }
        }
    }

    Lista<Edicion>& getEdiciones() { return ediciones; }

    void setEdiciones(const Lista<Edicion>& lista) {
        ediciones = lista;
    }
};

#endif
