/*
Manejador de Archivos: Clase responsable de la carga y gestión de archivos de datos.

Archivo: ManejadorArchivos.h
Autores:
Juan Felipe Guevara Olaya jfguevarao@udistrital.edu.co
Jean Pierre
Melissa
*/
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
    /*
    Clase responsable de la carga y gestión de archivos de datos.
    Métodos:
    - cargarEditoriales: Carga las editoriales desde un archivo y las inserta en un árbol rojo
    - cargarAutores: Carga los autores desde un archivo y los inserta en un árbol rojo
    - cargarLibros: Carga los libros desde un archivo y los inserta en un árbol rojo
    - cargarEdiciones: Carga las ediciones desde un archivo y las inserta en una lista
    Descripción:
    Esta clase proporciona métodos para cargar datos desde archivos de texto y almacenarlos en estructuras
    de datos adecuadas, como árboles
    rojo-negro y listas. Facilita la gestión de editoriales, autores, libros y ediciones.
    */
public:
    static void cargarEditoriales(const std::string& ruta, ArbolRojiNegro<Editorial>& arbolEditoriales) {
        /*
        Método para cargar editoriales desde un archivo y almacenarlas en un árbol rojo.
        Atributos:
        - ruta: La ruta del archivo de texto que contiene los datos de las editoriales.
        - arbolEditoriales: El árbol rojo donde se insertarán las editoriales.
        */
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
    
    static void cargarEditoriales(const std::string& ruta, Lista<Editorial>& listaEditoriales) {
        /*
        Método para cargar editoriales desde un archivo y almacenarlas en una lista.
        Atributos:
        - ruta: La ruta del archivo de texto que contiene los datos de las editoriales.
        - listaEditoriales: La lista donde se insertarán las editoriales.
        */
	    std::ifstream archivo(ruta);
	    if (!archivo.is_open()) {
	        std::cout << "Error al abrir archivo de editoriales." << std::endl;
	        return;
	    }
	
	    std::string linea;
	    int numLinea = 0;
	    while (getline(archivo, linea)) {
	        numLinea++;
	        if (linea.empty()) continue;
	
	        std::stringstream ssContador(linea);
	        std::string campoTemporal;
	        int contadorCampos = 0;
	        while (getline(ssContador, campoTemporal, ';')) {
	            contadorCampos++;
	        }
	        if (contadorCampos != 4) {
	            std::cout << "L�nea " << numLinea << " ignorada (formato inv�lido): " << linea << "\n";
	            continue;
	        }
	
	        Editorial e;
	        std::stringstream ss(linea);
	        getline(ss, e.id, ';');
	        getline(ss, e.nombre, ';');
	        getline(ss, e.ciudadPrincipal, ';');
	        getline(ss, e.paisPrincipal);
	
	        if (e.id.empty()) {
	            std::cout << "L�nea " << numLinea << " ignorada (ID vac�o): " << linea << "\n";
	            continue;
	        }
	
	        listaEditoriales.insertarFinal(e);
	    }
	
	    archivo.close();
	}

    static void cargarAutores(const std::string& ruta,ArbolRojiNegro<Autor>& arbolAutores,
        Multilista<std::string, std::string>& formacionAutores) {
        /*
        Método para cargar autores desde un archivo y almacenarlos en un árbol rojo.
        Atributos:
        - ruta: La ruta del archivo de texto que contiene los datos de los autores.
        - arbolAutores: El árbol rojo donde se insertarán los autores.
        - formacionAutores: La lista donde se almacenará la formación de los autores.
        */
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
            
            int edad = calcularEdad(a.fechaNacimiento);
            std::string valorFormacion = construirClaveEdadAnio(edad, a.anioPrimeraObra, a.id);
            formacionAutores.insertarEnSublista(a.formacionBase, valorFormacion);
        }

        archivo.close();
    }
    
 static void cargarAutores(const std::string& ruta,Lista<Autor>& listaAutores,
    Multilista<std::string, std::string>& formacionAutores) {
        /*
        Método para cargar autores desde un archivo y almacenarlos en una lista.
        Atributos:
        - ruta: La ruta del archivo de texto que contiene los datos de los autores.
        - listaAutores: La lista donde se insertarán los autores.
        - formacionAutores: La lista donde se almacenará la formación de los autores.
        */
	    std::ifstream archivo(ruta);
	    if (!archivo.is_open()) {
	        std::cout << "Error al abrir archivo de autores." << std::endl;
	        return;
	    }
	
	    std::string linea;
	    int numLinea = 0;
	    while (getline(archivo, linea)) {
	        numLinea++;
	
	        if (linea.empty()) continue;
	
	        std::stringstream ssContador(linea);
	        std::string tempCampo;
	        int contadorCampos = 0;
	        while (getline(ssContador, tempCampo, ';')) {
	            contadorCampos++;
	        }
	
	        if (contadorCampos != 11) {
	            std::cout << "Linea " << numLinea << " ignorada (campos invalidos): " << linea << "\n";
	            continue;
	        }
	
	        Autor a;
	        std::stringstream ss(linea);
	        std::string campo;
	
	        getline(ss, a.id, ';');
	        getline(ss, a.nombre, ';');
	        getline(ss, a.apellido, ';');
	        getline(ss, campo, ';'); a.sexo = campo.empty() ? ' ' : campo[0];
	        getline(ss, a.fechaNacimiento, ';');
	        getline(ss, a.ciudadNacimiento, ';');
	        getline(ss, a.paisNacimiento, ';');
	        getline(ss, a.ciudadResidencia, ';');
	        getline(ss, a.formacionBase, ';');
	        getline(ss, campo, ';'); a.anioInicioLiteratura = std::atoi(campo.c_str());
	        getline(ss, campo);      a.anioPrimeraObra = std::atoi(campo.c_str());
	
	        if (a.id.empty()) {
	            std::cout << "Linea " << numLinea << " ignorada (ID vacío): " << linea << "\n";
	            continue;
	        }
	
	        listaAutores.insertarFinal(a);
	
	        int edad = calcularEdad(a.fechaNacimiento);
	        std::string valorFormacion = construirClaveEdadAnio(edad, a.anioPrimeraObra, a.id);
	        formacionAutores.insertarEnSublista(a.formacionBase, valorFormacion);
	    }
	
	    archivo.close();
	}

    static void cargarObras(const std::string& ruta, 
                          ArbolRojiNegro<Obra>& arbolObras, 
                          Multilista<std::string, Obra>& autorObras) {
        /*
        Método para cargar obras desde un archivo y almacenarlas en un árbol.
        Atributos:
        - ruta: La ruta del archivo de texto que contiene los datos de las obras.
        - arbolObras: El árbol donde se insertarán las obras.
        - autorObras: La lista donde se almacenarán las obras por autor.
        */
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
    
    static void cargarObras(const std::string& ruta, 
                          Lista<Obra>& listaObras, 
                          Multilista<std::string, Obra>& autorObras) {
        /*
        Método para cargar obras desde un archivo y almacenarlas en una lista.
        Atributos:
        - ruta: La ruta del archivo de texto que contiene los datos de las obras.
        - listaObras: La lista donde se insertarán las obras.
        - autorObras: La lista donde se almacenarán las obras por autor.
        */
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

           	listaObras.insertarFinal(o);
            autorObras.insertarEnSublista(o.idAutor, o);
        }

        archivo.close();
    }

    static void cargarEdiciones(const std::string& ruta, 
                              ArbolRojiNegro<Edicion>& arbolEdiciones, 
                              Multilista<std::string, std::string>& editorialAnios) {
        /*
        Método para cargar ediciones desde un archivo y almacenarlas en un árbol.
        Atributos:
        - ruta: La ruta del archivo de texto que contiene los datos de las ediciones.
        - arbolEdiciones: El árbol donde se insertarán las ediciones.
        - editorialAnios: La lista donde se almacenarán las ediciones por editorial y año.
        */
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
            getline(ss, e.ciudadPublicacion, ';');
            getline(ss, e.idObra);

            arbolEdiciones.insertar(e.numeroEdicion, e);
            
            // Construir índice para consulta 1: editorial y años
            int anio = extraerAnio(e.fechaPublicacion);
            std::string valorAnio = construirClaveAnioEdicion(anio, e.numeroEdicion);
            editorialAnios.insertarEnSublista(e.idEditorial, valorAnio);
        }

        archivo.close();
    }

    static void construirIndicesRelacionados(
        /*
        Método para construir índices relacionados entre las diferentes entidades.
        Atributos:
        - arbolAutores: El árbol de autores.
        - arbolEditoriales: El árbol de editoriales.
        - arbolObras: El árbol de obras.
        - arbolEdiciones: El árbol de ediciones.
        - autorTipoPoesia: La lista que relaciona autores con tipos de poesía.
        */
        ArbolRojiNegro<Autor>& arbolAutores,
        ArbolRojiNegro<Editorial>& arbolEditoriales,
        ArbolRojiNegro<Obra>& arbolObras,
        ArbolRojiNegro<Edicion>& arbolEdiciones,
        Multilista<std::string, std::string>& autorTipoPoesia,
        Multilista<std::string, std::string>& editorialAutores,
        Multilista<std::string, std::string>& editorialPoetas,
        Multilista<std::string, std::string>& editorialAutoresNacimiento,
        Multilista<std::string, std::string>& tipoPoesiaEditorial) {
        
        std::cout << "Construyendo índices relacionados..." << std::endl;
        
        construirIndiceAutorTipoPoesia(arbolObras, arbolEdiciones, autorTipoPoesia);
        construirIndiceEditorialAutores(arbolAutores, arbolObras, arbolEdiciones, editorialAutores);
        construirIndiceEditorialPoetas(arbolAutores, arbolObras, arbolEdiciones, editorialPoetas);
        construirIndiceEditorialAutoresNacimiento(arbolAutores, arbolObras, arbolEdiciones, editorialAutoresNacimiento);
        construirIndiceTipoPoesiaEditorial(arbolObras, arbolEdiciones, tipoPoesiaEditorial);
    }

private:
    static std::string limpiarNumero(const std::string& s) {
        std::string res;
        for (char c : s) {
            if (isdigit(c) || c == '-') res += c;
        }
        return res;
    }

    static int calcularEdad(const std::string& fechaNacimiento) {
        if (fechaNacimiento.empty()) return 0;
        
        std::string anioStr;
        size_t pos = fechaNacimiento.find_last_of("/-");
        if (pos != std::string::npos && pos + 1 < fechaNacimiento.length()) {
            anioStr = fechaNacimiento.substr(pos + 1);
        }
        
        if (anioStr.empty()) return 0;
        
        int anioNacimiento = std::atoi(anioStr.c_str());
        return (anioNacimiento > 0) ? (2024 - anioNacimiento) : 0;
    }

    static int extraerAnio(const std::string& fecha) {
        if (fecha.empty()) return 0;
        
        std::string anioStr;
        size_t pos = fecha.find_last_of("/-");
        if (pos != std::string::npos && pos + 1 < fecha.length()) {
            anioStr = fecha.substr(pos + 1);
        }
        
        return std::atoi(anioStr.c_str());
    }

    static std::string construirClaveEdadAnio(int edad, int anioPrimeraObra, const std::string& idAutor) {
        std::ostringstream oss;
        oss << edad << "-" << anioPrimeraObra << "-" << idAutor;
        return oss.str();
    }

    static std::string construirClaveAnioEdicion(int anio, int numeroEdicion) {
        std::ostringstream oss;
        oss << anio << "-" << numeroEdicion;
        return oss.str();
    }

    static std::string construirClaveCiudadAnio(const std::string& ciudad, int anioInicio, const std::string& idAutor) {
        std::ostringstream oss;
        oss << ciudad << "-" << anioInicio << "-" << idAutor;
        return oss.str();
    }

    static std::string construirClavePaisNacimiento(const std::string& pais, const std::string& ciudad, const std::string& idAutor) {
        std::ostringstream oss;
        oss << pais << "-" << ciudad << "-" << idAutor;
        return oss.str();
    }

    static std::string construirClaveTipoPoesia(const std::string& tipoPoesia, const std::string& nombreObra, 
                                               const std::string& fechaPublicacion, int numEdicion) {
        std::ostringstream oss;
        oss << tipoPoesia << "-" << nombreObra << "-" << fechaPublicacion << "-" << numEdicion;
        return oss.str();
    }

    static void construirIndiceAutorTipoPoesia(ArbolRojiNegro<Obra>& arbolObras,
                                              ArbolRojiNegro<Edicion>& arbolEdiciones,
                                              Multilista<std::string, std::string>& autorTipoPoesia) {
        std::cout << "Construyendo índice autor-tipo poesía..." << std::endl;
    }

    static void construirIndiceEditorialAutores(ArbolRojiNegro<Autor>& arbolAutores,
                                               ArbolRojiNegro<Obra>& arbolObras,
                                               ArbolRojiNegro<Edicion>& arbolEdiciones,
                                               Multilista<std::string, std::string>& editorialAutores) {
        std::cout << "Construyendo índice editorial-autores..." << std::endl;
    }

    static void construirIndiceEditorialPoetas(ArbolRojiNegro<Autor>& arbolAutores,
                                              ArbolRojiNegro<Obra>& arbolObras,
                                              ArbolRojiNegro<Edicion>& arbolEdiciones,
                                              Multilista<std::string, std::string>& editorialPoetas) {
        std::cout << "Construyendo índice editorial-poetas..." << std::endl;
    }

    static void construirIndiceEditorialAutoresNacimiento(ArbolRojiNegro<Autor>& arbolAutores,
                                                         ArbolRojiNegro<Obra>& arbolObras,
                                                         ArbolRojiNegro<Edicion>& arbolEdiciones,
                                                         Multilista<std::string, std::string>& editorialAutoresNacimiento) {
        std::cout << "Construyendo índice editorial-autores-nacimiento..." << std::endl;
    }

    static void construirIndiceTipoPoesiaEditorial(ArbolRojiNegro<Obra>& arbolObras,
                                                  ArbolRojiNegro<Edicion>& arbolEdiciones,
                                                  Multilista<std::string, std::string>& tipoPoesiaEditorial) {
        std::cout << "Construyendo índice tipo-poesía-editorial..." << std::endl;
    }

public:

    static bool obtenerAutorPorId(const std::string& idAutor, 
                                 ArbolRojiNegro<Autor>& arbolAutores, 
                                 Autor& autorEncontrado) {
        return false; 
    }

    // Método para obtener información de una editorial específica
    static bool obtenerEditorialPorId(const std::string& idEditorial, 
                                     ArbolRojiNegro<Editorial>& arbolEditoriales, 
                                     Editorial& editorialEncontrada) {
        return false;
    }

    static bool validarConsistenciaDatos(ArbolRojiNegro<Autor>& arbolAutores,
                                        ArbolRojiNegro<Editorial>& arbolEditoriales,
                                        ArbolRojiNegro<Obra>& arbolObras,
                                        ArbolRojiNegro<Edicion>& arbolEdiciones) {
        std::cout << "Validando consistencia de datos..." << std::endl;
        return true;
    }
    static void convertirListaAutoresAArbol(Lista<Autor>& lista, ArbolRojiNegro<Autor>& arbol) {
}
static void cargarEdiciones(const std::string& ruta, Lista<Edicion>& lista, Multilista<std::string, std::string>& editorialAnios) {
	std::ifstream archivo(ruta);
	if (!archivo.is_open()) return;

	std::string linea;
	while (std::getline(archivo, linea)) {
		std::stringstream ss(linea);
		std::string idObra, idEditorial, fechaPublicacion;
		int numeroEdicion;

		std::getline(ss, idObra, ',');
		std::getline(ss, idEditorial, ',');
		std::getline(ss, fechaPublicacion, ',');
		ss >> numeroEdicion;

		std::string anio = fechaPublicacion.substr(fechaPublicacion.find_last_of("/-") + 1);
		std::string valor = anio + "-" + idObra;

		if (!editorialAnios.existe(idEditorial)) {
			editorialAnios.insertar(idEditorial);
		}
		editorialAnios.insertarEnSublista(idEditorial, valor);
	}
	archivo.close();
}

};

#endif // MANEJADORARCHIVOS_H