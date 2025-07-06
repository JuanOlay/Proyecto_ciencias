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

    static void cargarAutores(const std::string& ruta, 
                            ArbolRojiNegro<Autor>& arbolAutores, 
                            Multilista<std::string, std::string>& formacionAutores) {
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
            
            // Construir índice para consulta 6: formación y edad
            int edad = calcularEdad(a.fechaNacimiento);
            std::string valorFormacion = construirClaveEdadAnio(edad, a.anioPrimeraObra, a.id);
            formacionAutores.insertarEnSublista(a.formacionBase, valorFormacion);
        }

        archivo.close();
    }
    
 static void cargarAutores(const std::string& ruta, 
                          Lista<Autor>& listaAutores, 
                          Multilista<std::string, std::string>& formacionAutores) {
	    std::ifstream archivo(ruta);
	    if (!archivo.is_open()) {
	        std::cout << "Error al abrir archivo de autores." << std::endl;
	        return;
	    }
	
	    std::string linea;
	    int numLinea = 0;
	    while (getline(archivo, linea)) {
	        numLinea++;
	
	        if (linea.empty()) continue;  // ? L�nea vac�a
	
	        std::stringstream ssContador(linea);
	        std::string tempCampo;
	        int contadorCampos = 0;
	        while (getline(ssContador, tempCampo, ';')) {
	            contadorCampos++;
	        }
	
	        if (contadorCampos != 11) {
	            std::cout << "L�nea " << numLinea << " ignorada (campos inv�lidos): " << linea << "\n";
	            continue;  // ? L�nea mal formateada
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
	            std::cout << "L�nea " << numLinea << " ignorada (ID vac�o): " << linea << "\n";
	            continue;
	        }
	
	        listaAutores.insertarFinal(a);
	
	        // �ndice para consulta 6
	        int edad = calcularEdad(a.fechaNacimiento);
	        std::string valorFormacion = construirClaveEdadAnio(edad, a.anioPrimeraObra, a.id);
	        formacionAutores.insertarEnSublista(a.formacionBase, valorFormacion);
	    }
	
	    archivo.close();
	}


    static void cargarObras(const std::string& ruta, 
                          ArbolRojiNegro<Obra>& arbolObras, 
                          Multilista<std::string, Obra>& autorObras) {
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

    static void cargarEdiciones(const std::string& ruta, 
                              ArbolRojiNegro<Edicion>& arbolEdiciones, 
                              Multilista<std::string, std::string>& editorialAnios) {
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
            
            // Construir índice para consulta 1: editorial y años
            int anio = extraerAnio(e.fechaPublicacion);
            std::string valorAnio = construirClaveAnioEdicion(anio, e.numeroEdicion);
            editorialAnios.insertarEnSublista(e.idEditorial, valorAnio);
        }

        archivo.close();
    }

    // Método especializado para construir índices cruzados entre archivos
    static void construirIndicesRelacionados(
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
        
        // Recorrer todas las obras para construir las relaciones
        // Nota: Esta es una implementación simplificada que asume que tienes métodos
        // para recorrer los árboles. Ajusta según tu implementación específica.
        
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

    // Métodos auxiliares para construir índices cruzados
    static void construirIndiceAutorTipoPoesia(ArbolRojiNegro<Obra>& arbolObras,
                                              ArbolRojiNegro<Edicion>& arbolEdiciones,
                                              Multilista<std::string, std::string>& autorTipoPoesia) {
        // Implementación para relacionar obras con ediciones por tipo de poesía
        // Necesitarás implementar métodos para recorrer los árboles según tu implementación
        std::cout << "Construyendo índice autor-tipo poesía..." << std::endl;
    }

    static void construirIndiceEditorialAutores(ArbolRojiNegro<Autor>& arbolAutores,
                                               ArbolRojiNegro<Obra>& arbolObras,
                                               ArbolRojiNegro<Edicion>& arbolEdiciones,
                                               Multilista<std::string, std::string>& editorialAutores) {
        // Implementación para relacionar editoriales con autores por ciudad y año
        std::cout << "Construyendo índice editorial-autores..." << std::endl;
    }

    static void construirIndiceEditorialPoetas(ArbolRojiNegro<Autor>& arbolAutores,
                                              ArbolRojiNegro<Obra>& arbolObras,
                                              ArbolRojiNegro<Edicion>& arbolEdiciones,
                                              Multilista<std::string, std::string>& editorialPoetas) {
        // Implementación para contar poetas únicos por editorial
        std::cout << "Construyendo índice editorial-poetas..." << std::endl;
    }

    static void construirIndiceEditorialAutoresNacimiento(ArbolRojiNegro<Autor>& arbolAutores,
                                                         ArbolRojiNegro<Obra>& arbolObras,
                                                         ArbolRojiNegro<Edicion>& arbolEdiciones,
                                                         Multilista<std::string, std::string>& editorialAutoresNacimiento) {
        // Implementación para relacionar autores por lugar de nacimiento
        std::cout << "Construyendo índice editorial-autores-nacimiento..." << std::endl;
    }

    static void construirIndiceTipoPoesiaEditorial(ArbolRojiNegro<Obra>& arbolObras,
                                                  ArbolRojiNegro<Edicion>& arbolEdiciones,
                                                  Multilista<std::string, std::string>& tipoPoesiaEditorial) {
        // Implementación para relacionar tipo de poesía con editorial
        std::cout << "Construyendo índice tipo-poesía-editorial..." << std::endl;
    }

public:
    // Método para obtener información de un autor específico (útil para las consultas)
    static bool obtenerAutorPorId(const std::string& idAutor, 
                                 ArbolRojiNegro<Autor>& arbolAutores, 
                                 Autor& autorEncontrado) {
        // Implementar búsqueda en el árbol
        // Retorna true si encuentra el autor, false si no
        return false; // Placeholder - implementar según tu ArbolRojiNegro
    }

    // Método para obtener información de una editorial específica
    static bool obtenerEditorialPorId(const std::string& idEditorial, 
                                     ArbolRojiNegro<Editorial>& arbolEditoriales, 
                                     Editorial& editorialEncontrada) {
        // Implementar búsqueda en el árbol
        return false; // Placeholder - implementar según tu ArbolRojiNegro
    }

    // Método para validar consistencia de datos entre archivos
    static bool validarConsistenciaDatos(ArbolRojiNegro<Autor>& arbolAutores,
                                        ArbolRojiNegro<Editorial>& arbolEditoriales,
                                        ArbolRojiNegro<Obra>& arbolObras,
                                        ArbolRojiNegro<Edicion>& arbolEdiciones) {
        std::cout << "Validando consistencia de datos..." << std::endl;
        
        // Aquí podrías implementar validaciones como:
        // - Verificar que todos los idAutor en obras existan en autores
        // - Verificar que todos los idEditorial en ediciones existan en editoriales
        // - Etc.
        
        return true; // Placeholder
    }
};

#endif // MANEJADORARCHIVOS_H
