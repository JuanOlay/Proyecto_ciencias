#ifndef MENUBIBLIOTECA_H
#define MENUBIBLIOTECA_H

#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include "Entidades.h"
#include "GestionBiblioteca.h"

class MenuBiblioteca {
private:
    GestionBiblioteca gestion;

    void limpiarBuffer() {
        std::cin.clear();
        while (std::cin.get() != '\n');
    }

    void pausar() {
        std::cout << "\nPresione Enter para continuar...";
        std::cin.get();
    }

    // Captura de datos
    Autor capturarDatosAutor() {
        Autor a;
        std::cout << "ID: "; std::cin >> a.id; limpiarBuffer();
        std::cout << "Nombre: "; getline(std::cin, a.nombre);
        std::cout << "Apellido: "; getline(std::cin, a.apellido);
        a.sexo = validarSexo();
        std::cout << "Fecha de nacimiento: "; getline(std::cin, a.fechaNacimiento);
        std::cout << "Ciudad de nacimiento: "; getline(std::cin, a.ciudadNacimiento);
        std::cout << "País de nacimiento: "; getline(std::cin, a.paisNacimiento);
        std::cout << "Ciudad de residencia: "; getline(std::cin, a.ciudadResidencia);
        a.formacionBase = validarFormacionBase();
        std::cout << "Año inicio literatura: "; std::cin >> a.anioInicioLiteratura;
        std::cout << "Año primera obra: "; std::cin >> a.anioPrimeraObra;
        limpiarBuffer();
        return a;
    }

    Editorial capturarDatosEditorial() {
        Editorial e;
        std::cout << "ID: "; std::cin >> e.id; limpiarBuffer();
        std::cout << "Nombre: "; getline(std::cin, e.nombre);
        std::cout << "Ciudad principal: "; getline(std::cin, e.ciudadPrincipal);
        std::cout << "País principal: "; getline(std::cin, e.paisPrincipal);
        return e;
    }

    Obra capturarDatosObra() {
        Obra o;
        std::cout << "Nombre: "; getline(std::cin, o.nombre);
        o.tipoPoesia = validarTipoPoesia();
        std::cout << "ID del autor: "; std::cin >> o.idAutor;
        limpiarBuffer();
        return o;
    }

    Edicion capturarDatosEdicion() {
        Edicion e;
        std::cout << "Número de edición: "; std::cin >> e.numeroEdicion; limpiarBuffer();
        std::cout << "Fecha de publicación: "; getline(std::cin, e.fechaPublicacion);
        std::cout << "ID editorial: "; std::cin >> e.idEditorial; limpiarBuffer();
        std::cout << "Ciudad de publicación: "; getline(std::cin, e.ciudadPublicacion);
        return e;
    }

    // Validaciones
    std::string validarTipoPoesia() {
        std::string tipo;
        do {
            std::cout << "Tipo de poesía (lírica, épica, dramática): ";
            getline(std::cin, tipo);
        } while (tipo != "lírica" && tipo != "épica" && tipo != "dramática");
        return tipo;
    }

    char validarSexo() {
        char s;
        do {
            std::cout << "Sexo (M/F): ";
            std::cin >> s;
            s = toupper(s);
            limpiarBuffer();
        } while (s != 'M' && s != 'F');
        return s;
    }

    std::string validarFormacionBase() {
        std::string formacion;
        do {
            std::cout << "Formación base (filología, filosofía, literatura, autodidacta): ";
            getline(std::cin, formacion);
        } while (formacion != "filología" && formacion != "filosofía" &&
                 formacion != "literatura" && formacion != "autodidacta");
        return formacion;
    }

    // Menús específicos
    void menuAutores() {
        int opcion;
        do {
            system("cls");
            std::cout << "\n--- MENÚ AUTORES ---\n";
            std::cout << "1. Agregar autor\n";
            std::cout << "2. Mostrar autores\n";
            std::cout << "3. Eliminar autor por ID\n";
            std::cout << "0. Volver\n";
            std::cout << "Seleccione una opción: ";
            std::cin >> opcion;
            limpiarBuffer();

            switch (opcion) {
                case 1: gestion.getControlAutores().agregar(capturarDatosAutor()); break;
                case 2: gestion.getControlAutores().mostrarTodos(); break;
                case 3: {
                    int id;
                    std::cout << "Ingrese ID del autor a eliminar: ";
                    std::cin >> id;
                    gestion.getControlAutores().eliminarPorID(to_string(id));
                    break;
                }
                case 0: break;
                default: std::cout << "Opción inválida.\n";
            }
            pausar();
        } while (opcion != 0);
    }

    void menuEditoriales() {
        int opcion;
        do {
            system("cls");
            std::cout << "\n--- MENÚ EDITORIALES ---\n";
            std::cout << "1. Agregar editorial\n";
            std::cout << "2. Mostrar editoriales\n";
            std::cout << "3. Eliminar editorial por ID\n";
            std::cout << "0. Volver\n";
            std::cout << "Seleccione una opción: ";
            std::cin >> opcion;
            limpiarBuffer();

            switch (opcion) {
                case 1: gestion.getControlEditoriales().agregar(capturarDatosEditorial()); break;
                case 2: gestion.getControlEditoriales().mostrarTodos(); break;
                case 3: {
                    int id;
                    std::cout << "Ingrese ID de la editorial a eliminar: ";
                    std::cin >> id;
                    gestion.getControlEditoriales().eliminarPorID(to_string(id));
                    break;
                }
                case 0: break;
                default: std::cout << "Opción inválida.\n";
            }
            pausar();
        } while (opcion != 0);
    }

    void menuObras() {
        int opcion;
        do {
            system("cls");
            std::cout << "\n--- MENÚ OBRAS ---\n";
            std::cout << "1. Agregar obra\n";
            std::cout << "2. Mostrar obras\n";
            std::cout << "3. Eliminar obra por nombre\n";
            std::cout << "0. Volver\n";
            std::cout << "Seleccione una opción: ";
            std::cin >> opcion;
            limpiarBuffer();

            switch (opcion) {
                case 1: gestion.getControlObras().agregar(capturarDatosObra()); break;
                case 2: gestion.getControlObras().mostrarTodos(); break;
                case 3: {
                    std::string nombre;
                    std::cout << "Ingrese nombre de la obra a eliminar: ";
                    getline(std::cin, nombre);
                    gestion.getControlObras().eliminarPorNombre(nombre);
                    break;
                }
                case 0: break;
                default: std::cout << "Opción inválida.\n";
            }
            pausar();
        } while (opcion != 0);
    }

    void menuConsultas() {
        system("cls");
        std::cout << "\n--- CONSULTAS (en construcción) ---\n";
        pausar();
    }

public:
    void mostrarMenuPrincipal() {
        std::cout << "\n=== MENÚ PRINCIPAL ===\n";
        std::cout << "1. Gestión de Autores\n";
        std::cout << "2. Gestión de Editoriales\n";
        std::cout << "3. Gestión de Obras\n";
        std::cout << "4. Consultas\n";
        std::cout << "0. Salir\n";
        std::cout << "Seleccione una opción: ";
    }

    void ejecutar() {
        gestion.cargarAutoresDesdeArchivo("autores.txt");
        gestion.cargarEditorialesDesdeArchivo("editoriales.txt");
        gestion.cargarObrasDesdeArchivo("obras.txt");
        gestion.cargarEdicionesDesdeArchivo("ediciones.txt");

        int opcion;
        do {
            system("cls");
            mostrarMenuPrincipal();
            std::cin >> opcion;
            limpiarBuffer();

            switch (opcion) {
                case 1: menuAutores(); break;
                case 2: menuEditoriales(); break;
                case 3: menuObras(); break;
                case 4: menuConsultas(); break;
                case 0:
                    gestion.guardarAutoresEnArchivo("autores.txt");
                    gestion.guardarEditorialesEnArchivo("editoriales.txt");
                    gestion.guardarObrasEnArchivo("obras.txt");
                    gestion.guardarEdicionesEnArchivo("ediciones.txt");
                    std::cout << "\n¡Gracias por usar el sistema!\n";
                    break;
                default:
                    std::cout << "Opción inválida. Intente nuevamente.\n";
                    pausar();
            }
        } while (opcion != 0);
    }
};

#endif
