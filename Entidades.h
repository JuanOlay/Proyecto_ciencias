#ifndef ENTIDADES_H
#define ENTIDADES_H

#include <iostream>
#include <string>
#include "Lista.h"

using namespace std;

struct Autor {
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
        return id == otro.id;
    }
};

struct Editorial {
    string id;
    string nombre;
    string ciudadPrincipal;
    string paisPrincipal;

    bool operator==(const Editorial& otro) const {
        return id == otro.id;
    }
};

struct Edicion {
    int numeroEdicion;
    string fechaPublicacion;
    string idEditorial;
    string ciudadPublicacion;

    bool operator==(const Edicion& otra) const {
        return numeroEdicion == otra.numeroEdicion;
    }
};

struct Obra {
    string nombre;
    string tipoPoesia;
    string idAutor;
    Lista<int> ediciones;
    bool operator==(const Obra& otra) const {
    return nombre == otra.nombre;
}

};

inline std::ostream& operator<<(std::ostream& os, const Obra& o) {
    os << "Nombre: " << o.nombre 
       << ", Tipo de poesía: " << o.tipoPoesia 
       << ", ID Autor: " << o.idAutor;
    return os;
}
#endif

