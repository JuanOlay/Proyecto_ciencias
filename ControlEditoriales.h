/*
ControlEditoriales.h

Este archivo contiene la clase ControlEditoriales, que se encarga de gestionar la lista de editoriales.

Autores:
Juan Felipe Guevara Olaya jfguevarao1211@udistrital.edu.co
Jean Pierre
Melissa
*/
#ifndef CONTROLEDITORIALES_H
#define CONTROLEDITORIALES_H

#include "Entidades.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Lista.h"

class ControlEditoriales {
    /*
    Clase que gestiona la lista de editoriales.
    Atributos:
    - editoriales: Lista de objetos Editorial.
    Métodos:
    - agregar: Agrega una nueva editorial a la lista.
    - eliminarPorID: Elimina una editorial por su ID y actualiza el archivo.
    - buscarPorID: Busca una editorial por su ID.
    - mostrarTodos: Muestra todas las editoriales en la lista.
    - getEditoriales: Devuelve la lista de editoriales.
    - setEditoriales: Establece la lista de editoriales.
    - cargarDesdeArchivo: Carga las editoriales desde un archivo.
    - guardarEnArchivo: Guarda las editoriales en un archivo.
    */
private:
    Lista<Editorial> editoriales;

public:
    void agregar(const Editorial& e) {
        /*
        Agrega una nueva editorial a la lista.
        Descripción:
        Este método se encarga de insertar una nueva editorial al final de la lista de editoriales.
        Parámetros:
        - e: Objeto Editorial que se va a agregar.
        Retorno:
        - Sin retorno.
        */
        editoriales.insertarFinal(e); 
    }

    bool eliminarPorID(const std::string& id, const std::string& rutaArchivo) {
        /*
        Elimina una editorial por su ID y actualiza el archivo.
        Descripción:
        Este método busca una editorial por su ID en la lista de editoriales y la elimina.
        Si la editorial es encontrada, se elimina de la lista y se actualiza el archivo
        indicado por rutaArchivo.
        Parámetros:
        - id: ID de la editorial a eliminar.
        - rutaArchivo: Ruta del archivo donde se guardará la lista actualizada de editoriales.
        Retorno:
        - true si la editorial fue eliminada y el archivo actualizado correctamente, false en caso contrario.
        */
        for (int i = 0; i < editoriales.getTamano(); ++i) {
            Editorial* e = editoriales.buscarEnPos(i);
            if (e != NULL && e->id == id) {
                editoriales.eliminar(*e);
                return guardarEnArchivo(rutaArchivo);
            }
        }
        return false;
    }

    Editorial* buscarPorID(const std::string& id) {
        /*
        Busca una editorial por su ID.
        Descripción:
        Este método busca una editorial en la lista de editoriales utilizando su ID.
        Parámetros:
        - id: ID de la editorial a buscar.
        Retorno:
        - Puntero a la editorial encontrada o NULL si no se encuentra.
        */
        for (int i = 0; i < editoriales.getTamano(); ++i) {
            Editorial* e = editoriales.buscarEnPos(i);
            if (e != NULL && e->id == id) return e;
        }
        return NULL;
    }

    void mostrarTodos() const {
        /*
        Muestra todas las editoriales en la lista.
        Descripción:
        Este método itera sobre la lista de editoriales y muestra la información de cada una.
        Parámetros:
        - Ninguno.
        Retorno:
        - Sin retorno.
        */
        for (int i = 0; i < editoriales.getTamano(); ++i) {
            Editorial* e = editoriales.buscarEnPos(i);
            if (e != NULL) {
                std::cout << e->id << ": " << e->nombre << std::endl;
            }
        }
    }

    Lista<Editorial>& getEditoriales() {
        /*
        Devuelve la lista de editoriales.
        Descripción:
        Este método devuelve una referencia a la lista de editoriales.
        Parámetros:
        - Ninguno.
        Retorno:
        - Referencia a la lista de editoriales.
        */
        return editoriales;
    }

    void setEditoriales(const Lista<Editorial>& lista) {
        /*
        Establece la lista de editoriales.
        Descripción:
        Este método asigna una nueva lista de editoriales.
        Parámetros:
        - lista: Referencia a la nueva lista de editoriales.
        Retorno:
        - Sin retorno.
        */
        editoriales = lista;
    }

    bool guardarEnArchivo(const std::string& archivo) {
        /*
        Guarda todas las editoriales en el archivo.
        Descripción:
        Este método escribe la información de todas las editoriales en un archivo de texto.
        Parámetros:
        - archivo: Ruta del archivo donde se guardarán las editoriales.
        Retorno:
        - true si la operación fue exitosa, false en caso contrario.
        */
        std::ofstream file(archivo);
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