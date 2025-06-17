#ifndef EDITORIAL_H
#define EDITORIAL_H

#include <iostream>
#include <cstring> // para strcmp
using namespace std;

struct Editorial{
    int id_editorial;
    char nombre_editorial[50];
    char ciudad_principal[50];
    char pais_principal[50];

    Editorial() {
        id_editorial = 0;
        nombre_editorial[0] = '\0';
        ciudad_principal[0] = '\0';
        pais_principal[0] = '\0';
    }

    void mostrar() {
        cout << "ID Editorial: " << id_editorial << endl;
        cout << "Nombre: " << nombre_editorial << endl;
        cout << "Ciudad principal: " << ciudad_principal << endl;
        cout << "País principal: " << pais_principal << endl;
    }
};

inline bool operator<(const Editorial& a, const Editorial& b) {
    return strcmp(a.nombre_editorial, b.nombre_editorial) < 0;
}

inline bool operator>(const Editorial& a, const Editorial& b) {
    return strcmp(a.nombre_editorial, b.nombre_editorial) > 0;
}

#endif // EDITORIAL_H