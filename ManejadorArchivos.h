#ifndef MANEJADORARCHIVOS_H
#define MANEJADORARCHIVOS_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include "Entidades.h"
#include "ArbolRojiNegro.h"
#include "Multilista.h"

class ManejadorArchivos {
public:
    static void cargarEditoriales(const std::string& ruta, ArbolRojiNegro<Editorial>& arbolEditoriales) {
        std::ifstream archivo(ruta);
        if (!archivo.is_open()) {
            std::cout << "Error al abrir archivo de editoriales." << std::endl;
            return;
        }

        std::string linea;
        while (getline(archivo, linea)) {
            Editorial e;
            std::stringstream ss(linea);
            getline(ss, e.id, ';');
            getline(ss, e.nombre, ';');
            getline(ss, e.ciudadPrincipal, ';');
            getline(ss, e.paisPrincipal);
            arbolEditoriales.insertar(atoi(limpiarNumero(e.id).c_str()), e);

        }

        archivo.close();
    }

    static void cargarAutores(const std::string& ruta, ArbolRojiNegro<Autor>& arbolAutores, Multilista<std::string, Autor>& editorialAutores) {
        std::ifstream archivo(ruta);
        if (!archivo.is_open()) {
            std::cout << "Error al abrir archivo de autores." << std::endl;
            return;
        }

        std::string linea;
        while (getline(archivo, linea)) {
            Autor a;
            std::string campo;
            std::stringstream ss(linea);

            getline(ss, a.id, ';');
            getline(ss, a.nombre, ';');
            getline(ss, a.apellido, ';');
            getline(ss, campo, ';'); a.sexo = campo.empty() ? ' ' : campo[0];
            getline(ss, a.fechaNacimiento, ';');
            getline(ss, a.ciudadNacimiento, ';');
            getline(ss, a.paisNacimiento, ';');
            getline(ss, a.ciudadResidencia, ';');
            getline(ss, a.formacionBase, ';');
            getline(ss, campo, ';'); a.anioInicioLiteratura = std::atoi(limpiarNumero(campo).c_str());
            getline(ss, campo); a.anioPrimeraObra = std::atoi(limpiarNumero(campo).c_str());

            arbolAutores.insertar(atoi(limpiarNumero(a.id).c_str()), a);
            editorialAutores.insertarEnSublista(a.paisNacimiento, a);
        }

        archivo.close();
    }

    static void cargarObras(const std::string& ruta, ArbolRojiNegro<Obra>& arbolObras, Multilista<std::string, Obra>& autorObras) {
        std::ifstream archivo(ruta);
        if (!archivo.is_open()) {
            std::cout << "Error al abrir archivo de obras." << std::endl;
            return;
        }

        std::string linea;
        while (getline(archivo, linea)) {
            Obra o;
            std::stringstream ss(linea);

            getline(ss, o.nombre, ';');
            getline(ss, o.tipoPoesia, ';');
            getline(ss, o.idAutor);

            arbolObras.insertar(o.nombre.length(), o);
            autorObras.insertarEnSublista(o.idAutor, o);
        }

        archivo.close();
    }

    static void cargarEdiciones(const std::string& ruta, ArbolRojiNegro<Edicion>& arbolEdiciones, Multilista<std::string, Edicion>& obraEdiciones) {
        std::ifstream archivo(ruta);
        if (!archivo.is_open()) {
            std::cout << "Error al abrir archivo de ediciones." << std::endl;
            return;
        }

        std::string linea;
        while (getline(archivo, linea)) {
            Edicion e;
            std::stringstream ss(linea);
            std::string campo;

            getline(ss, campo, ';'); e.numeroEdicion = std::atoi(limpiarNumero(campo).c_str());
            getline(ss, e.fechaPublicacion, ';');
            getline(ss, e.idEditorial, ';');
            getline(ss, e.ciudadPublicacion);

            arbolEdiciones.insertar(e.numeroEdicion, e);
            obraEdiciones.insertarEnSublista(e.idEditorial, e);
        }

        archivo.close();
    }

private:
    static std::string limpiarNumero(const std::string& s) {
        std::string res;
        for (char c : s) {
            if (isdigit(c) || c == '-') res += c;
        }
        return res;
    }
};

#endif // MANEJADORARCHIVOS_H
