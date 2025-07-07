/*
ControlAutores.h

Este archivo contiene la clase ControlAutores, que se encarga de gestionar la lista de autores.

Autores:
Juan Felipe Guevara Olaya jfguevarao1211@udistrital.edu.co
Jean Pierre
Melissa
*/

#ifndef CONTROLAUTORES_H
#define CONTROLAUTORES_H

#include "Entidades.h"
#include <iostream>
#include <fstream>
#include "Lista.h"

class ControlAutores {
	/*
	Clase que gestiona la lista de autores.
	Atributos:
	- autores: Lista de objetos Autor.
	
	Métodos:
	- agregar: Agrega un nuevo autor a la lista.
	- eliminarPorID: Elimina un autor por su ID y actualiza el archivo.
	- buscarPorID: Busca un autor por su ID.
	- mostrarTodos: Muestra todos los autores en la lista.
	- getAutores: Devuelve la lista de autores.
	- setAutores: Establece la lista de autores.
	- guardarEnArchivo: Guarda la lista de autores en un archivo.
	*/
private:
    Lista<Autor> autores;

public:
    void agregar(const Autor& a) {
		/*
		Agrega un nuevo autor a la lista.
		Descripción:
		Este método se encarga de insertar un nuevo autor al final de la lista de autores.
		Parámetros:
		- a: Objeto Autor que se va a agregar.
		Retorno:
		- Sin retorno.
		*/
		autores.insertarFinal(a);
	}

    bool eliminarPorID(const std::string& id, const std::string& rutaArchivo) {
		/*
		Elimina un autor por su ID y actualiza el archivo.	
		Descripción:
		Este método busca un autor por su ID en la lista de autores y lo elimina.
		Si el autor es encontrado, se elimina de la lista y se actualiza el archivo
		indicado por rutaArchivo.
		Parámetros:
		- id: ID del autor a eliminar.
		- rutaArchivo: Ruta del archivo donde se guardará la lista actualizada de autores
		Retorno:
		- true si el autor fue eliminado y el archivo actualizado correctamente, false en caso contrario
		*/
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
		/*
		Busca un autor por su ID.
		Descripción:
		Este método busca un autor en la lista de autores utilizando su ID.
		Parámetros:
		- id: ID del autor a buscar.
		Retorno:
		- Puntero al autor encontrado o NULL si no se encuentra.
		*/
        for (int i = 0; i < autores.getTamano(); ++i) {
            Autor* a = autores.buscarEnPos(i);
            if (a != NULL && a->id == id) return a;
        }
        return NULL;
    }

   void mostrarTodos() const {
	/*
	Muestra todos los autores en la lista.
	Descripción:
	Este método itera sobre la lista de autores y muestra la información de cada uno.
	Parámetros:
	- Ninguno.
	Retorno:
	- Sin retorno.
	*/
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

    Lista<Autor>& getAutores() {
		/*
		Devuelve la lista de autores.
		Descripción:
		Este método devuelve una referencia a la lista de autores.
		Parámetros:
		- Ninguno.
		Retorno:
		- Referencia a la lista de autores.
		*/
		return autores;
	}

    void setAutores(const Lista<Autor>& lista) {
		/*
		Establece la lista de autores.
		Descripción:
		Este método asigna una nueva lista de autores.
		Parámetros:
		- lista: Referencia a la nueva lista de autores.
		Retorno:
		- Sin retorno.
		*/
        autores = lista;
    }
    
    bool guardarEnArchivo(const std::string& ruta) {
		/*
		Guarda la lista de autores en un archivo.
		Descripción:
		Este método guarda la información de todos los autores en un archivo de texto.
		Parámetros:
		- ruta: Ruta del archivo donde se guardará la lista de autores.
		Retorno:
		- true si la operación fue exitosa, false en caso contrario.
		*/
	    std::ofstream archivo(ruta);
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

#endif // CONTROL_AUTORES_H