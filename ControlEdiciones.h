#ifndef CONTROLEDICIONES_H
#define CONTROLEDICIONES_H

#include "Entidades.h"
#include <iostream>
#include <fstream>
#include <sstream>
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

    bool cargarDesdeArchivo(const std::string& archivo) {
    std::ifstream file(archivo);
    if (!file.is_open()) return false;
    
    std::string linea;
    while (getline(file, linea)) {
        if (linea.empty()) continue;
        
        std::stringstream ss(linea);
        std::string campo;
        Edicion e;
        
        getline(ss, campo, ';'); e.numeroEdicion = std::atoi(campo.c_str());
        getline(ss, e.fechaPublicacion, ';');
        getline(ss, e.idEditorial, ';');
        getline(ss, e.ciudadPublicacion);
        
        ediciones.insertarFinal(e);
    }
    
    file.close();
    return true;
}

bool guardarEnArchivo(const std::string& archivo) {
    std::ofstream file(archivo);
    if (!file.is_open()) return false;
    
    for (int i = 0; i < ediciones.getTamano(); ++i) {
        Edicion* e = ediciones.buscarEnPos(i);
        if (e != NULL) {
            file << e->numeroEdicion << ";" << e->fechaPublicacion << ";" 
                 << e->idEditorial << ";" << e->ciudadPublicacion << "\n";
        }
    }
    
    file.close();
    return true;
}
};

#endif
