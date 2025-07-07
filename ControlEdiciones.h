/*
ControlEdiciones.h

Este archivo contiene la clase ControlEdiciones, que se encarga de gestionar la lista de ediciones.

Autores:
Juan Felipe Guevara Olaya jfguevarao1211@udistrital.edu.co
Jean Pierre
Melissa
*/
#ifndef CONTROLEDICIONES_H
#define CONTROLEDICIONES_H

#include "Entidades.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Lista.h"

class ControlEdiciones {
    /**
     * Clase que gestiona la lista de ediciones.
     * Atributos:
     * - ediciones: Lista de objetos Edicion.
     *
     * Métodos:
     * - agregar: Agrega una nueva edición a la lista.
     * - eliminarPorNumero: Elimina una edición por su número y actualiza el archivo.
     * - buscarPorNumero: Busca una edición por su número.
     * - mostrarTodos: Muestra todas las ediciones en la lista.
     * - getEdiciones: Devuelve la lista de ediciones.
     * - setEdiciones: Establece la lista de ediciones.
     * - cargarDesdeArchivo: Carga las ediciones desde un archivo.
     * - guardarEnArchivo: Guarda las ediciones en un archivo.
     */
private:
    Lista<Edicion> ediciones;

public:
    void agregar(const Edicion& ed) {
        /*
        Agrega una nueva edición a la lista.
        Descripción:
        Este método se encarga de insertar una nueva edición al final de la lista de ediciones.
        Parámetros:
        - ed: Objeto Edicion que se va a agregar.
        Retorno:
        - Sin retorno.
        */
        ediciones.insertarFinal(ed);
    }

    bool eliminarPorNumero(int numero, const std::string& rutaArchivo) {
        /*
        Elimina una edición por su número y actualiza el archivo.
        Descripción:
        Este método busca una edición por su número en la lista de ediciones y la elimina.
        Si la edición es encontrada, se elimina de la lista y se actualiza el archivo
        indicado por rutaArchivo.
        Parámetros:
        - numero: Número de la edición a eliminar.
        - rutaArchivo: Ruta del archivo donde se guardará la lista actualizada de ediciones.
        Retorno:
        - true si la edición fue eliminada y el archivo actualizado correctamente, false en caso contrario.
        */
        for (int i = 0; i < ediciones.getTamano(); ++i) {
            Edicion* e = ediciones.buscarEnPos(i);
            if (e != NULL && e->numeroEdicion == numero) {
                ediciones.eliminar(*e);
                return guardarEnArchivo(rutaArchivo);
            }
        }
        return false;
    }

    Edicion* buscarPorNumero(int numero) {
        /*
        Busca una edición por su número.
        Descripción:
        Este método busca una edición en la lista de ediciones utilizando su número.
        Parámetros:
        - numero: Número de la edición a buscar.
        Retorno:
        - Puntero a la edición encontrada o NULL si no se encuentra.
        */
        for (int i = 0; i < ediciones.getTamano(); ++i) {
            Edicion* e = ediciones.buscarEnPos(i);
            if (e != NULL && e->numeroEdicion == numero) return e;
        }
        return NULL;
    }

    void mostrarTodos() const {
        /*
        Muestra todas las ediciones en la lista.
        Descripción:
        Este método itera sobre la lista de ediciones y muestra la información de cada una.
        Parámetros:
        - Ninguno.
        Retorno:
        - Sin retorno.
        */
        for (int i = 0; i < ediciones.getTamano(); ++i) {
            Edicion* e = ediciones.buscarEnPos(i);
            if (e != NULL) {
                std::cout << "Ed. #" << e->numeroEdicion << " - " << e->fechaPublicacion << std::endl;
            }
        }
    }

    Lista<Edicion>& getEdiciones() {
    /*
        Devuelve la lista de ediciones.
        Descripción:
        Este método devuelve una referencia a la lista de ediciones.
        Parámetros:
        - Ninguno.
        Retorno:
        - Referencia a la lista de ediciones.
    */
        return ediciones;
    }

    void setEdiciones(const Lista<Edicion>& lista) {
        /*
        Establece la lista de ediciones.
        Descripción:
        Este método asigna una nueva lista de ediciones.
        Parámetros:
        - lista: Referencia a la nueva lista de ediciones.
        Retorno:
        - Sin retorno.
        */
        ediciones = lista;
    }

    bool cargarDesdeArchivo(const std::string& archivo) {
        /*
        Carga todas las ediciones desde el archivo.
        Descripción:
        Este método lee un archivo de texto y carga todas las ediciones en la lista.
        Parámetros:
        - archivo: Ruta del archivo desde el cual se cargarán las ediciones.
        Retorno:
        - true si la operación fue exitosa, false en caso contrario.
        */
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
        /*
        Guarda todas las ediciones en el archivo.
        Descripción:
        Este método escribe la información de todas las ediciones en un archivo de texto.
        Parámetros:
        - archivo: Ruta del archivo donde se guardarán las ediciones.
        Retorno:
        - true si la operación fue exitosa, false en caso contrario.
        */
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

#endif // CONTROLEDICIONES_H