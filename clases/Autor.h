#ifndef AUTOR_H
#define AUTOR_H

#include <iostream>
#include <string>
using namespace std;

struct Autor {
    int id_autor;
    char nombre[50];
    char apellido[50];
    char sexo; // 'F' o 'M'
    char fecha_nacimiento[20]; // formato: ddmmaaaa
    char ciudad_nacimiento[50];
    char pais_nacimiento[50];
    char ciudad_residencia[50];
    string formacion; // literatura, artes,ciencias sociales,ingenierias,areas de salud,jurisprudencia,otros
    int anio_inicio_literatura;
    int anio_primera_obra;

    Autor() {
        id_autor = 0;
        nombre[0] = '\0';
        apellido[0] = '\0';
        sexo = ' ';
        fecha_nacimiento[0] = '\0';
        ciudad_nacimiento[0] = '\0';
        pais_nacimiento[0] = '\0';
        ciudad_residencia[0] = '\0';
        formacion[0] = '\0';
        anio_inicio_literatura = 0;
        anio_primera_obra = 0;
    }
    bool operator<(const Autor& otro) const {
        return id_autor < otro.id_autor; // o cualquier otro criterio
    }

    bool operator>(const Autor& otro) const {
        return id_autor > otro.id_autor;
    }

};

#endif // AUTOR_H 