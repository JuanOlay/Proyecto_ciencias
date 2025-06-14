#ifndef AUTOR_H
#define AUTOR_H

#include <iostream>
using namespace std;

class Autor {
public:
    int id;
    char nombre[50];
    char apellido[50];
    char sexo; // 'F' o 'M'
    int diaNacimiento;
    int mesNacimiento;
    int anioNacimiento;
    char ciudadNacimiento[50];
    char paisNacimiento[50];
    char ciudadResidencia[50];
    char formacion[30]; // literatura, artes, etc.
    int anioInicio;
    int anioPrimeraObra;

    Autor() {
        id = 0;
        nombre[0] = '\0';
        apellido[0] = '\0';
        sexo = ' ';
        diaNacimiento = 0;
        mesNacimiento = 0;
        anioNacimiento = 0;
        ciudadNacimiento[0] = '\0';
        paisNacimiento[0] = '\0';
        ciudadResidencia[0] = '\0';
        formacion[0] = '\0';
        anioInicio = 0;
        anioPrimeraObra = 0;
    }

    void mostrar() {
        cout << "ID: " << id << endl;
        cout << "Nombre: " << nombre << " " << apellido << endl;
        cout << "Sexo: " << sexo << endl;
        cout << "Fecha de nacimiento: " << diaNacimiento << "/" << mesNacimiento << "/" << anioNacimiento << endl;
        cout << "Ciudad de nacimiento: " << ciudadNacimiento << endl;
        cout << "Pais de nacimiento: " << paisNacimiento << endl;
        cout << "Ciudad de residencia: " << ciudadResidencia << endl;
        cout << "Formacion: " << formacion << endl;
        cout << "Año de inicio en la literatura: " << anioInicio << endl;
        cout << "Año de publicación de su primera obra: " << anioPrimeraObra << endl;
    }
};

#endif // AUTOR_H