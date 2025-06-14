#ifndef EDICION_H
#define EDICION_H

#include <iostream>
using namespace std;

class Edicion {
public:
    int numeroEdicion;
    char fechaPublicacion[20];
    int idEditorial;
    char ciudadPublicacion[50];

    Edicion() {
        numeroEdicion = 0;
        fechaPublicacion[0] = '\0';
        idEditorial = 0;
        ciudadPublicacion[0] = '\0';
    }

    void mostrar() {
        cout << "Número de edición: " << numeroEdicion << endl;
        cout << "Fecha de publicación: " << fechaPublicacion << endl;
        cout << "ID de la editorial: " << idEditorial << endl;
        cout << "Ciudad de publicación: " << ciudadPublicacion << endl;
    }
};

#endif
