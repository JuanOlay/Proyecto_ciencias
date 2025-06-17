#ifndef OBRA_H
#define OBRA_H

#include <iostream>
#include <string>
#include <cstring> // para strcmp
#include "Edicion.h"
using namespace std;

struct Obra{
    char nombre_documento[100];
    string tipo_poesia; // decima,soneto,himno,haiku,romance,octava real,lira,verso libre.
    int id_autor;
    Edicion ediciones[10];
    int cantidad_ediciones;

    Obra() {
        nombre_documento[0] = '\0';
        tipo_poesia[0] = '\0';
        id_autor = 0;
        cantidad_ediciones = 0;
    }

};

inline bool operator<(const Obra& a, const Obra& b) {
    return strcmp(a.nombre_documento, b.nombre_documento) < 0;
}

inline bool operator>(const Obra& a, const Obra& b) {
    return strcmp(a.nombre_documento, b.nombre_documento) > 0;
}

#endif // OBRA_H