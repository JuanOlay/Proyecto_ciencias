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

    bool eliminarPorID(const string& id) {
        for (int i = 0; i < autores.getTamano(); ++i) {
            Autor* a = autores.buscarEnPos(i);
            if (a != NULL && a->id == id) {
                autores.eliminar(*a);
                return true;
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
    
    void guardarEnArchivo(const std::string& ruta) {
	    for (int i = 0; i < autores.getTamano(); ++i) {
	        const Autor& a = autores[i];
	
	        // Verificar si ya existe en el archivo
	        bool existe = false;
	        std::ifstream archivoLectura(ruta);
	        std::string linea;
	        while (std::getline(archivoLectura, linea)) {
	            std::stringstream ss(linea);
	            std::string idArchivo;
	            std::getline(ss, idArchivo, ';');
	            if (idArchivo == a.id) {
	                existe = true;
	                break;
	            }
	        }
	        archivoLectura.close();
	
	        // Si no existe, lo agregamos en modo append
	        if (!existe) {
	            std::ofstream archivoEscritura(ruta, std::ios::app);
	            archivoEscritura << a.id << ";" << a.nombre << ";" << a.apellido << ";" << a.sexo << ";"
	                             << a.fechaNacimiento << ";" << a.ciudadNacimiento << ";" << a.paisNacimiento << ";"
	                             << a.ciudadResidencia << ";" << a.formacionBase << ";" << a.anioInicioLiteratura << ";"
	                             << a.anioPrimeraObra << "\n";
	            archivoEscritura.close();
	        }
	    }
	}
};

#endif
