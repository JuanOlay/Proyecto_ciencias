#ifndef GESTIONBIBLIOTECA_H
#define GESTIONBIBLIOTECA_H

#include "ArbolRojiNegro.h"
#include "Multilista.h"
#include "Entidades.h"
#include "ManejadorArchivos.h"
#include "ControlAutores.h"
#include "ControlEditoriales.h"
#include "ControlObras.h"

class GestionBiblioteca {
private:
    ControlAutores controlAutores;
    ControlEditoriales controlEditoriales;
    ControlObras controlObras;

    ArbolRojiNegro<Autor> arbolAutores;
    ArbolRojiNegro<Editorial> arbolEditoriales;
    ArbolRojiNegro<Obra> arbolObras;
    ArbolRojiNegro<Edicion> arbolEdiciones;

    Multilista<std::string, Autor> paisAutores;
    Multilista<std::string, Obra> autorObras;
    Multilista<std::string, Edicion> obraEdiciones;

public:
    // Getters para controladores
    ControlAutores& getControlAutores() { return controlAutores; }
    ControlEditoriales& getControlEditoriales() { return controlEditoriales; }
    ControlObras& getControlObras() { return controlObras; }

    // Cargar desde archivo
    void cargarAutoresDesdeArchivo(const std::string& ruta) {
        ManejadorArchivos::cargarAutores(ruta, arbolAutores, paisAutores);
    }

    void cargarEditorialesDesdeArchivo(const std::string& ruta) {
        ManejadorArchivos::cargarEditoriales(ruta, arbolEditoriales);
    }

    void cargarObrasDesdeArchivo(const std::string& ruta) {
        ManejadorArchivos::cargarObras(ruta, arbolObras, autorObras);
    }

    void cargarEdicionesDesdeArchivo(const std::string& ruta) {
        ManejadorArchivos::cargarEdiciones(ruta, arbolEdiciones, obraEdiciones);
    }

    // Guardar en archivo (simulación, aún sin implementar)
    void guardarAutoresEnArchivo(const std::string& ruta) {
        controlAutores.guardarEnArchivo(ruta);
    }

    void guardarEditorialesEnArchivo(const std::string& ruta) {
        controlEditoriales.guardarEnArchivo(ruta);
    }

    void guardarObrasEnArchivo(const std::string& ruta) {
        controlObras.guardarEnArchivo(ruta);
    }

    void guardarEdicionesEnArchivo(const std::string& /*ruta*/) {
        // Aquí deberías implementar si tienes ControlEdiciones o similar.
    }

    // Acceso a estructuras por si se necesita en consultas
    ArbolRojiNegro<Autor>& getArbolAutores() { return arbolAutores; }
    ArbolRojiNegro<Editorial>& getArbolEditoriales() { return arbolEditoriales; }
    ArbolRojiNegro<Obra>& getArbolObras() { return arbolObras; }
    ArbolRojiNegro<Edicion>& getArbolEdiciones() { return arbolEdiciones; }

    Multilista<std::string, Autor>& getPaisAutores() { return paisAutores; }
    Multilista<std::string, Obra>& getAutorObras() { return autorObras; }
    Multilista<std::string, Edicion>& getObraEdiciones() { return obraEdiciones; }
};

#endif
