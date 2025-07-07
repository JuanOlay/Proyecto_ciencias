/*
ControlObras.h
Este archivo contiene la clase ControlObras, que se encarga de gestionar la lista de obras.
Autores:
Juan Felipe Guevara Olaya jfguevarao1211@udistrital.edu.co
Jean Pierre
Melissa
*/

#ifndef CONTROLOBRA_H
#define CONTROLOBRA_H

#include "Entidades.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include "Lista.h"

class ControlObras {
    /*
    Clase que gestiona la lista de obras.
    Atributos:
    - obras: Lista de objetos Obra.
    Métodos:
    - agregar: Agrega una nueva obra a la lista.
    - eliminarPorNombre: Elimina una obra por su nombre y actualiza el archivo.
    - buscarPorNombre: Busca una obra por su nombre.
    - mostrarTodos: Muestra todas las obras en la lista.
    - getObras: Devuelve la lista de obras.
    - setObras: Establece la lista de obras.
    - cargarDesdeArchivo: Carga las obras desde un archivo.
    - guardarEnArchivo: Guarda las obras en un archivo.
    */
private:
    Lista<Obra> obras;

public:
    void agregar(const Obra& o) {
        /*
        Agrega una nueva obra a la lista.
        Descripción:
        Este método se encarga de insertar una nueva obra al final de la lista de obras.
        Parámetros:
        - o: Objeto Obra que se va a agregar.
        Retorno:
        - Sin retorno.
        */
        obras.insertarFinal(o);
    }

    bool eliminarPorNombre(const std::string& nombre, const std::string& rutaArchivo) {
        /*
        Elimina una obra por su nombre y actualiza el archivo.
        Descripción:
        Este método busca una obra por su nombre en la lista de obras y la elimina.
        Si la obra es encontrada, se elimina de la lista y se actualiza el archivo
        indicado por rutaArchivo.
        Parámetros:
        - nombre: Nombre de la obra a eliminar.
        - rutaArchivo: Ruta del archivo donde se guardará la lista actualizada de obras.
        Retorno:
        - true si la obra fue eliminada y el archivo actualizado correctamente, false en caso contrario.
        */
	    for (int i = 0; i < obras.getTamano(); ++i) {
	        Obra* o = obras.buscarEnPos(i);
	        if (o != NULL && o->nombre == nombre) {
	            obras.eliminar(*o);
	            guardarEnArchivo(rutaArchivo);
	            return true;
	        }
	    }
	    return false;
	}


    Obra* buscarPorNombre(const std::string& nombre) {
        /*
        Busca una obra por su nombre.
        Descripción:
        Este método busca una obra en la lista de obras utilizando su nombre.
        Parámetros:
        - nombre: Nombre de la obra a buscar.
        Retorno:
        - Puntero a la obra encontrada o NULL si no se encuentra.
        */
        for (int i = 0; i < obras.getTamano(); ++i) {
            Obra* o = obras.buscarEnPos(i);
            if (o != NULL && o->nombre == nombre) return o;
        }
        return NULL;
    }

    void mostrarTodos() const {
        /*
        Muestra todas las obras en la lista.
        Descripción:
        Este método itera sobre la lista de obras y muestra la información de cada una.
        Parámetros:
        - Ninguno.
        Retorno:
        - Sin retorno.
        */
        for (int i = 0; i < obras.getTamano(); ++i) {
            Obra* o = obras.buscarEnPos(i);
            if (o != NULL) {
                std::cout << o->nombre << " - " << o->tipoPoesia << std::endl;
            }
        }
    }

    Lista<Obra>& getObras() {
        /*
        Devuelve la lista de obras.
        Descripción:
        Este método devuelve una referencia a la lista de obras.
        Retorno:
        - Referencia a la lista de obras.
        */
        return obras;
    }

    void setObras(const Lista<Obra>& lista) {
        /*
        Establece la lista de obras.
        Descripción:
        Este método permite reemplazar la lista actual de obras por una nueva lista.
        Parámetros:
        - lista: Nueva lista de obras.
        Retorno:
        - Sin retorno.
        */
        obras = lista;
    }

    void guardarEnArchivo(const std::string& ruta) {
        /*
        Guarda la lista de obras en un archivo.
        Descripción:
        Este método se encarga de guardar la lista actual de obras en un archivo
        especificado por la ruta.
        Parámetros:
        - ruta: Ruta del archivo donde se guardarán las obras.
        Retorno:
        - Sin retorno.
        */
	    std::ofstream archivo(ruta);
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