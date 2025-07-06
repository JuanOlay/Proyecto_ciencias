#ifndef CONTROLEDITORIALES_H
#define CONTROLEDITORIALES_H

#include "Entidades.h"
#include <iostream>
#include "Lista.h"

class ControlEditoriales {
private:
    Lista<Editorial> editoriales;

public:
    void agregar(const Editorial& e) { editoriales.insertarFinal(e); }

    bool eliminarPorID(const string& id) {
        for (int i = 0; i < editoriales.getTamano(); ++i) {
            Editorial* e = editoriales.buscarEnPos(i);
            if (e != NULL && e->id == id) {
                editoriales.eliminar(*e);
                return true;
            }
        }
        return false;
    }

    Editorial* buscarPorID(const string& id) {
        for (int i = 0; i < editoriales.getTamano(); ++i) {
            Editorial* e = editoriales.buscarEnPos(i);
            if (e != NULL && e->id == id) return e;
        }
        return NULL;
    }

    void mostrarTodos() const {
        for (int i = 0; i < editoriales.getTamano(); ++i) {
            Editorial* e = editoriales.buscarEnPos(i);
            if (e != NULL) {
                cout << e->id << ": " << e->nombre << endl;
            }
        }
    }

    Lista<Editorial>& getEditoriales() { return editoriales; }

    void setEditoriales(const Lista<Editorial>& lista) {
        editoriales = lista;
    }
        void guardarEnArchivo(const std::string& ruta) {
        std::ofstream archivo(ruta);
        for (int i = 0; i < editoriales.getTamano(); ++i) {
            const Editorial& e = editoriales[i];
            archivo << e.id << ";" << e.nombre << ";" << e.ciudadPrincipal << ";" << e.paisPrincipal << "\n";
        }
        archivo.close();
    }
};

#endif
