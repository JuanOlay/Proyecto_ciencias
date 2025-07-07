#ifndef CONTROLEDITORIALES_H
#define CONTROLEDITORIALES_H

#include "Entidades.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Lista.h"

class ControlEditoriales {
private:
    Lista<Editorial> editoriales;

public:
    void agregar(const Editorial& e) { 
        editoriales.insertarFinal(e); 
    }

    bool eliminarPorID(const std::string& id, const std::string& rutaArchivo) {
        for (int i = 0; i < editoriales.getTamano(); ++i) {
            Editorial* e = editoriales.buscarEnPos(i);
            if (e != NULL && e->id == id) {
                editoriales.eliminar(*e);
                return guardarEnArchivo(rutaArchivo); // Actualiza archivo completo
            }
        }
        return false;
    }

    Editorial* buscarPorID(const std::string& id) {
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
                std::cout << e->id << ": " << e->nombre << std::endl;
            }
        }
    }

    Lista<Editorial>& getEditoriales() { return editoriales; }

    void setEditoriales(const Lista<Editorial>& lista) {
        editoriales = lista;
    }

    // ?? Sobrescribe el archivo completo con los datos actuales en memoria
    bool guardarEnArchivo(const std::string& archivo) {
        std::ofstream file(archivo); // modo truncado, borra y reescribe
        if (!file.is_open()) return false;

        for (int i = 0; i < editoriales.getTamano(); ++i) {
            Editorial* e = editoriales.buscarEnPos(i);
            if (e != NULL) {
                file << e->id << ";" << e->nombre << ";" 
                     << e->ciudadPrincipal << ";" << e->paisPrincipal << "\n";
            }
        }

        file.close();
        return true;
    }
};

#endif // CONTROLEDITORIALES_H

