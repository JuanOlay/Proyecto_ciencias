#ifndef CONTROLOBRA_H
#define CONTROLOBRA_H

#include "Entidades.h"
#include <iostream>
#include "Lista.h"

class ControlObras {
private:
    Lista<Obra> obras;

public:
    void agregar(const Obra& o) { obras.insertarFinal(o); }

    bool eliminarPorNombre(const string& nombre) {
        for (int i = 0; i < obras.getTamano(); ++i) {
            Obra* o = obras.buscarEnPos(i);
            if (o != NULL && o->nombre == nombre) {
                obras.eliminar(*o);
                return true;
            }
        }
        return false;
    }

    Obra* buscarPorNombre(const string& nombre) {
        for (int i = 0; i < obras.getTamano(); ++i) {
            Obra* o = obras.buscarEnPos(i);
            if (o != NULL && o->nombre == nombre) return o;
        }
        return NULL;
    }

    void mostrarTodos() const {
        for (int i = 0; i < obras.getTamano(); ++i) {
            Obra* o = obras.buscarEnPos(i);
            if (o != NULL) {
                cout << o->nombre << " - " << o->tipoPoesia << endl;
            }
        }
    }

    Lista<Obra>& getObras() { return obras; }

    void setObras(const Lista<Obra>& lista) {
        obras = lista;
    }
        void guardarEnArchivo(const std::string& ruta) {
        std::ofstream archivo(ruta);
        for (int i = 0; i < obras.getTamano(); ++i) {
            const Obra& o = obras[i];
            archivo << o.nombre << ";" << o.tipoPoesia << ";" << o.idAutor << "\n";
        }
        archivo.close();
    }
};

#endif

