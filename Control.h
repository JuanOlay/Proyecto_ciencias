#ifndef CONTROL_H
#define CONTROL_H
#include <iostream>
#include <string>
using namespace std;

struct Libro {
    string nombre;
    string tipoPoesia;
    int idAutor;
};

struct Edicion {
    int numeroEdicion;
    int fechaPublicacion;
    int idEditorial;
    string ciudadPublicacion;
};

struct Autor {
    int idAutor;
    string nombre;
    string apellido;
    string sexo;
    int fechaNacimiento;
    string ciudadNacimiento;
    string paisNacimiento;
    string ciudadResidencia;
    string formacionBase;
    int anioInicioLiteratura;
    int anioPublicacionPrimeraObra;
};

struct Editorial {
    int idEditorial;
    string nombreEditorial;
    string ciudadOficinaP;
    string paisOficinaP;
};

class Control {
private:
    int rtaUsuario;
public:
    Control(); 
    void menuPrincipal();
    void menuAgregarLibro();
    void menuEliminarLibro();
    void menuModificarLibro();
    void menuAgregarAutor();
    void menuEliminarAutor();
    void menuModificarAutor();
    void menuAgregarEditorial();
    void menuEliminarEditorial();
    void menuModificarEditorial();
    void menuAgregarEdicion();
    void menuEliminarEdicion();
    void menuModificarEdicion();
};

#endif
