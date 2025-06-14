#ifndef EDITORIAL_H
#define EDITORIAL_H

#include <iostream>
using namespace std;

class Editorial {
public:
    int idEditorial;
    char nombre[50];
    char ciudadPrincipal[50];
    char paisPrincipal[50];

    Editorial() {
        idEditorial = 0;
        nombre[0] = '\0';
        ciudadPrincipal[0] = '\0';
        paisPrincipal[0] = '\0';
    }

    void mostrar() {
        cout << "ID Editorial: " << idEditorial << endl;
        cout << "Nombre: " << nombre << endl;
        cout << "Ciudad principal: " << ciudadPrincipal << endl;
        cout << "País principal: " << paisPrincipal << endl;
    }
};

#endif
