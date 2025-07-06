#ifndef CONTROLAUTORES_H
#define CONTROLAUTORES_H

#include "Entidades.h"
#include <iostream>
#include "Lista.h"

class ControlAutores {
private:
    Lista<Autor> autores;

public:
    void agregar(const Autor& a) { autores.insertarFinal(a); }

    bool eliminarPorID(const string& id) {
        for (int i = 0; i < autores.getTamano(); ++i) {
            Autor* a = autores.buscarEnPos(i);
            if (a != NULL && a->id == id) {
                autores.eliminar(*a);
                return true;
            }
        }
        return false;
    }

    Autor* buscarPorID(const string& id) {
        for (int i = 0; i < autores.getTamano(); ++i) {
            Autor* a = autores.buscarEnPos(i);
            if (a != NULL && a->id == id) return a;
        }
        return NULL;
    }

    void mostrarTodos() const {
        for (int i = 0; i < autores.getTamano(); ++i) {
            Autor* a = autores.buscarEnPos(i);
            if (a != NULL) {
                cout << a->id << ": " << a->nombre << " " << a->apellido << endl;
            }
        }
    }

    Lista<Autor>& getAutores() { return autores; }

    void setAutores(const Lista<Autor>& lista) {
        autores = lista;
    }
        void guardarEnArchivo(const std::string& ruta) {
        std::ofstream archivo(ruta);
        for (int i = 0; i < autores.getTamano(); ++i) {
            const Autor& a = autores[i];
            archivo << a.id << ";" << a.nombre << ";" << a.apellido << ";" << a.sexo << ";"
                    << a.fechaNacimiento << ";" << a.ciudadNacimiento << ";" << a.paisNacimiento << ";"
                    << a.ciudadResidencia << ";" << a.formacionBase << ";" << a.anioInicioLiteratura << ";"
                    << a.anioPrimeraObra << "\n";
        }
        archivo.close();
    }
};

#endif
