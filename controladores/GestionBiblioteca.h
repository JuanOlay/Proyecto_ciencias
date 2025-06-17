#ifndef GESTIONBIBLIOTECA_H
#define GESTIONBIBLIOTECA_H

#include <iostream>
#include <string>
#include "../clases/Autor.h"
#include "../clases/Editorial.h"
#include "../clases/Obra.h"
#include "../clases/Edicion.h"

#include "../estructuras/Lista.h"
#include "../estructuras/Multilista.h"
#include "../estructuras/ArbolAVL.h"

using namespace std;

class GestionBiblioteca {
private:
    ArbolAVL<Autor> arbolAutores;
    ArbolAVL<Editorial> arbolEditoriales;
    ArbolAVL<Obra> arbolObras;

    Multilista<Obra> multilistaObrasPorAutor;
    Multilista<Obra> multilistaObrasPorEditorial;
    Multilista<Obra> multilistaObrasPorTipo;
    Multilista<Edicion> multilistaEdicionesPorObra;

    Lista<Autor> listaAutoresPorEdad;
    Lista<Autor> listaAutoresPorFormacion;

    Autor* buscarAutorPorId(int idAutor) {
        return nullptr; // Implementar lógica de búsqueda
    }

    Editorial* buscarEditorialPorId(int idEditorial) {
        return nullptr; // Implementar lógica de búsqueda
    }

    Obra* buscarObraPorNombre(const string& nombreObra) {
        return nullptr; // Implementar lógica de búsqueda
    }

public:
    GestionBiblioteca() {
        // Constructor: inicializa estructuras si es necesario
    }

    ~GestionBiblioteca() {
        // Destructor: libera recursos si es necesario
    }

    void agregarAutor(const Autor& autor) {
        arbolAutores.insertar(autor);
    }

    bool eliminarAutor(int idAutor) {
        Autor* autorEncontrado = buscarAutorPorId(idAutor);
        if (autorEncontrado != nullptr) {
            arbolAutores.eliminar(*autorEncontrado);
            return true;
        }
        return false;
    }

    bool modificarAutor(int idAutor, const Autor& nuevoAutor) {
        if (eliminarAutor(idAutor)) {
            agregarAutor(nuevoAutor);
            return true;
        }
        return false;
    }

    void agregarEditorial(const Editorial& editorial) {
        arbolEditoriales.insertar(editorial);
    }

    bool eliminarEditorial(int idEditorial) {
        Editorial* editorialEncontrada = buscarEditorialPorId(idEditorial);
        if (editorialEncontrada != nullptr) {
            arbolEditoriales.eliminar(*editorialEncontrada);
            return true;
        }
        return false;
    }

    bool modificarEditorial(int idEditorial, const Editorial& nuevaEditorial) {
        if (eliminarEditorial(idEditorial)) {
            agregarEditorial(nuevaEditorial);
            return true;
        }
        return false;
    }

    void agregarObra(const Obra& obra) {
        arbolObras.insertar(obra);
    }

    bool eliminarObra(const string& nombreObra) {
        Obra* obraEncontrada = buscarObraPorNombre(nombreObra);
        if (obraEncontrada != nullptr) {
            arbolObras.eliminar(*obraEncontrada);
            return true;
        }
        return false;
    }

    bool modificarObra(const string& nombreObra, const Obra& nuevaObra) {
        if (eliminarObra(nombreObra)) {
            agregarObra(nuevaObra);
            return true;
        }
        return false;
    }

    Lista<Obra> consultarObrasPorAutor(int idAutor) {
        Lista<Obra> obrasEncontradas;
        // Implementar lógica para buscar obras por autor
        return obrasEncontradas;
    }

    Lista<Autor> consultarAutoresPorEditorial(int idEditorial) {
        Lista<Autor> autoresEncontrados;
        // Implementar lógica para buscar autores por editorial
        return autoresEncontrados;
    }

    Lista<Editorial> consultarEditorialesPorPoetas(int numeroPoetas) {
        Lista<Editorial> editorialesEncontradas;
        // Implementar lógica para buscar editoriales con cierto número de poetas
        return editorialesEncontradas;
    }
};

#endif // GESTIONBIBLIOTECA_H