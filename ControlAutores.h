#ifndef CONTROLAUTORES_H
#define CONTROLAUTORES_H

#include "Entidades.h"
#include <iostream>
#include "Lista.h"

class ControlAutores {
private:
    Lista<Autor> autores;

public:
    void agregar(const Autor& a) { autores.insertarFinal(a); }

    bool eliminarPorID(const std::string& id, const std::string& rutaArchivo) {
	    for (int i = 0; i < autores.getTamano(); ++i) {
	        Autor* a = autores.buscarEnPos(i);
	        if (a != NULL && a->id == id) {
	            autores.eliminar(*a);
	            return guardarEnArchivo(rutaArchivo);  // Ahora sí actualiza el archivo
	        }
	    }
	    return false;
	}



    Autor* buscarPorID(const string& id) {
        for (int i = 0; i < autores.getTamano(); ++i) {
            Autor* a = autores.buscarEnPos(i);
            if (a != NULL && a->id == id) return a;
        }
        return NULL;
    }

   void mostrarTodos() const {
	    std::cout << "Mostrando autores (tamano = " << autores.getTamano() << "):\n";
	    for (int i = 0; i < autores.getTamano(); ++i) {
	        Autor* a = autores.buscarEnPos(i);
	        if (a != NULL) {
	            std::cout << "  [" << i << "] " << a->id << ": " << a->nombre << " " << a->apellido << std::endl;
	        } else {
	            std::cout << "  [" << i << "] NULL\n";
	        }
	    }
	}

    Lista<Autor>& getAutores() { return autores; }

    void setAutores(const Lista<Autor>& lista) {
        autores = lista;
    }
    
    bool guardarEnArchivo(const std::string& ruta) {
	    std::ofstream archivo(ruta);  // Sobrescribe el archivo completamente
	    if (!archivo.is_open()) return false;
	
	    for (int i = 0; i < autores.getTamano(); ++i) {
	        const Autor& a = autores[i];
	        archivo << a.id << ";" << a.nombre << ";" << a.apellido << ";" << a.sexo << ";"
	                << a.fechaNacimiento << ";" << a.ciudadNacimiento << ";" << a.paisNacimiento << ";"
	                << a.ciudadResidencia << ";" << a.formacionBase << ";" << a.anioInicioLiteratura << ";"
	                << a.anioPrimeraObra << "\n";
	    }
	
	    archivo.close();
	    return true;
	}
};

#endif
