#ifndef CONTROL_H
#define CONTROL_H
#include <iostream>
#include <string>
#include "Lista.h"
using namespace std;

struct Edicion {
    string numeroEdicion;
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

struct Libro {
    string nombre;
    string tipoPoesia;
    int idAutor;
    Lista<Edicion> ediciones;
};

class Control {
private:
    int rtaUsuario;
    string rtaUsuarioStr;
    Libro libro;
    Edicion edicion;
    Autor autor;
    Editorial editorial;
    Lista<Libro> libros; 
    Lista<Autor> autores;
    Lista<Editorial> editoriales;
public:
    Control(); 
    void menuPrincipal();
    void menuAgregarLibro();
    void menuEliminarLibro();
    void menuModificarLibro();
    string menuTipoPoesia();
    void menuAgregarAutor();
    void menuEliminarAutor();
    void menuModificarAutor();
    void menuAgregarEditorial();
    void menuEliminarEditorial();
    void menuModificarEditorial();
    void menuAgregarEdicion();
    void menuEliminarEdicion();
    void menuModificarEdicion();
    void menuEscogerLibro();
    int menuEscogerAutorInsercion();
    int menuEscogerAutorModificacion();
    void menuEscogerEditorialInsercion();
    void menuEscogerEditorialModificacion();
    void menuModificacionListadoEdiciones();
    void menuEscogerEdicionModificacion();
    void menuEscogerEdicionEliminacion();
    string menuSeleccionarSexoAutorInsercion();
    void menuSeleccionarSexoAutorModificacion();
    string menuSeleccionarFormacionAutorInsercion();
    void menuSeleccionarFormacionAutorModificacion();
    void imprimirListaLibros(Lista<Libro>& lista);
    void imprimirListaAutores(Lista<Autor>& lista);
    void imprimirListaEditoriales(Lista<Editorial>& lista);
    //void imprimirListaEdiciones(Lista<Edicion>& Lista);
};

#endif
