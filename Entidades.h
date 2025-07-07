/*
Entidades.h

Este archivo contiene las definiciones de las estructuras utilizadas en el sistema.

Autores:
Juan Felipe Guevara Olaya jfguevarao1211@udistrital.edu.co
Jean Pierre
Melissa
*/

#ifndef ENTIDADES_H
#define ENTIDADES_H

#include <iostream>
#include <string>
#include "Lista.h"

using namespace std;

struct Autor {
    /*
    Estructura que representa a un autor.
    Atributos:
    - id: Identificador único del autor.
    - nombre: Nombre del autor.
    - apellido: Apellido del autor.
    - sexo: Sexo del autor (M/F).
    - fechaNacimiento: Fecha de nacimiento del autor.
    - ciudadNacimiento: Ciudad de nacimiento del autor.
    - paisNacimiento: País de nacimiento del autor.
    - ciudadResidencia: Ciudad de residencia actual del autor.
    - formacionBase: Formación académica del autor.
    - anioInicioLiteratura: Año en que el autor comenzó a escribir literatura.
    - anioPrimeraObra: Año de publicación de la primera obra del autor.
    Métodos:
    - mostrarInformacion: Muestra la información del autor.
    - operator==: Sobrecarga del operador de igualdad para comparar autores por su ID.
    Descripción:
    Esta estructura almacena la información básica de un autor, incluyendo su identificación,
    nombre, apellido, sexo, fecha de nacimiento, lugar de nacimiento y residencia, formación
    */
    string id = "";
    string nombre = "";
    string apellido = "";
    char sexo = ' ';
    string fechaNacimiento = "";
    string ciudadNacimiento = "";
    string paisNacimiento = "";
    string ciudadResidencia = "";
    string formacionBase = "";
    int anioInicioLiteratura = 0;
    int anioPrimeraObra = 0;

    bool operator==(const Autor& otro) const {
        /*
        Sobrecarga del operador de igualdad para comparar autores por su ID.
        Parametros:
        - otro: Otro autor a comparar.
        Retorno:
        - true si los IDs son iguales, false en caso contrario.
        Descripción:
        Este método permite comparar dos autores para verificar si son el mismo
        basándose en su ID único.
        */
        return id == otro.id;
    }
};

struct Editorial {
    /*
    Estructura que representa a una editorial.
    Atributos:
    - id: Identificador único de la editorial.
    - nombre: Nombre de la editorial.
    - ciudadPrincipal: Ciudad donde se encuentra la sede principal de la editorial.
    - paisPrincipal: País donde se encuentra la sede principal de la editorial.
    Métodos:
    - operator==: Sobrecarga del operador de igualdad para comparar editoriales por su ID.
    Descripción:
    Esta estructura almacena la información básica de una editorial, incluyendo su identificación,
    nombre, ciudad y país de la sede principal.
    */
    string id;
    string nombre;
    string ciudadPrincipal;
    string paisPrincipal;

    bool operator==(const Editorial& otro) const {
        /*
        Sobrecarga del operador de igualdad para comparar editoriales por su ID.
        Parametros:
        - otro: Otra editorial a comparar.
        Retorno:
        - true si los IDs son iguales, false en caso contrario.
        Descripción:
        Este método permite comparar dos editoriales para verificar si son la misma
        basándose en su ID único.
        */
        return id == otro.id;
    }
};

struct Edicion {
    /*
    Estructura que representa una edición de una obra.
    Atributos:
    - numeroEdicion: Número de la edición.
    - fechaPublicacion: Fecha de publicación de la edición.
    - idEditorial: ID de la editorial que publicó la edición.
    - ciudadPublicacion: Ciudad donde se publicó la edición.
    Métodos:
    - operator==: Sobrecarga del operador de igualdad para comparar ediciones por su número.
    Descripción:
    Esta estructura almacena la información básica de una edición de una obra, incluyendo su número,
    fecha de publicación, editorial y ciudad de publicación.
    */

    int numeroEdicion;
    string fechaPublicacion;
    string idEditorial;
    string ciudadPublicacion;
    string idObra;

    bool operator==(const Edicion& otra) const {
        /*
        Sobrecarga del operador de igualdad para comparar ediciones por su número.
        Parametros:
        - otra: Otra edición a comparar.
        Retorno:
        - true si los números de edición son iguales, false en caso contrario.
        Descripción:
        Este método permite comparar dos ediciones para verificar si son la misma
        basándose en su número de edición.
        */
        return numeroEdicion == otra.numeroEdicion;
    }
};

struct Obra {
    /*
    Estructura que representa una obra literaria.
    Atributos:
    - nombre: Nombre de la obra.
    - tipoPoesia: Tipo de poesía (si aplica).
    - idAutor: ID del autor de la obra.
    - ediciones: Lista de ediciones de la obra.
    Métodos:
    - operator==: Sobrecarga del operador de igualdad para comparar obras por su nombre.
    Descripción:
    Esta estructura almacena la información básica de una obra literaria, incluyendo su nombre,
    tipo de poesía, autor y ediciones.
    */
    string nombre;
    string tipoPoesia;
    string idAutor;
    Lista<int> ediciones;
    bool operator==(const Obra& otra) const {
    return nombre == otra.nombre;
}

};

inline std::ostream& operator<<(std::ostream& os, const Obra& o) {
    /*
    Sobrecarga del operador de inserción para mostrar la información de una obra.
    Parametros:
    - os: Flujo de salida.
    - o: Obra a mostrar.
    Retorno:
    - Flujo de salida modificado.
    Descripción:
    Este método permite mostrar la información de una obra literaria en un formato legible.
    */
    os << "Nombre: " << o.nombre 
       << ", Tipo de poesía: " << o.tipoPoesia 
       << ", ID Autor: " << o.idAutor;
    return os;
}

#endif // ENTIDADES_H