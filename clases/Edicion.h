#ifndef EDICION_H
#define EDICION_H

#include <iostream>
using namespace std;

struct Edicion {
    int numero_edicion;
    char fecha_publicacion[20];
    int id_editorial;
    char ciudad_publicacion[50];

    Edicion() {
        numero_edicion = 0;
        fecha_publicacion[0] = '\0';
        id_editorial = 0;
        ciudad_publicacion[0] = '\0';
    }
};

#endif // EDICION_H