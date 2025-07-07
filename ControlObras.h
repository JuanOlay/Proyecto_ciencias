#ifndef CONTROLOBRA_H
#define CONTROLOBRA_H

#include "Entidades.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include "Lista.h"

class ControlObras {
private:
    Lista<Obra> obras;

public:
    void agregar(const Obra& o) { obras.insertarFinal(o); }

    bool eliminarPorNombre(const std::string& nombre, const std::string& rutaArchivo) {
	    for (int i = 0; i < obras.getTamano(); ++i) {
	        Obra* o = obras.buscarEnPos(i);
	        if (o != NULL && o->nombre == nombre) {
	            obras.eliminar(*o);
	            guardarEnArchivo(rutaArchivo);  // Reescribe archivo con la nueva lista
	            return true;
	        }
	    }
	    return false;
	}


    Obra* buscarPorNombre(const std::string& nombre) {
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
                std::cout << o->nombre << " - " << o->tipoPoesia << std::endl;
            }
        }
    }

    Lista<Obra>& getObras() { return obras; }

    void setObras(const Lista<Obra>& lista) {
        obras = lista;
    }

    // ? Guarda solo obras nuevas (sin sobrescribir el archivo)
    void guardarEnArchivo(const std::string& ruta) {
	    std::ofstream archivo(ruta);  // modo truncado, sobrescribe todo
	    if (!archivo.is_open()) {
	        std::cout << "Error al abrir archivo de obras." << std::endl;
	        return;
	    }
	
	    for (int i = 0; i < obras.getTamano(); ++i) {
	        const Obra& o = obras[i];
	        archivo << o.nombre << ";" << o.tipoPoesia << ";" << o.idAutor << "\n";
	    }
	
	    archivo.close();
	}
};

#endif // CONTROLOBRA_H

