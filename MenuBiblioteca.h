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
    bool sistemaInicializado;

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
	
	    // Validar que el ID no se repita
	    do {
	        std::cout << "ID (�nico): ";
	        std::cin >> a.id;
	        limpiarBuffer();
	
	        if (gestion.getControlAutores().buscarPorID(a.id) != nullptr) {
	            std::cout << "Error: Ya existe un autor con ese ID. Intente nuevamente.\n";
	        } else {
	            break;  // ID v�lido
	        }
	    } while (true);
	
	    std::cout << "Nombre: "; getline(std::cin, a.nombre);
	    std::cout << "Apellido: "; getline(std::cin, a.apellido);
	    a.sexo = validarSexo();
	    std::cout << "Fecha de nacimiento (DD/MM/YYYY): "; getline(std::cin, a.fechaNacimiento);
	    std::cout << "Ciudad de nacimiento: "; getline(std::cin, a.ciudadNacimiento);
	    std::cout << "Pais de nacimiento: "; getline(std::cin, a.paisNacimiento);
	    std::cout << "Ciudad de residencia: "; getline(std::cin, a.ciudadResidencia);
	    a.formacionBase = validarFormacionBase();
	    std::cout << "Anio inicio literatura: "; std::cin >> a.anioInicioLiteratura;
	    std::cout << "Anio primera obra: "; std::cin >> a.anioPrimeraObra;
	    limpiarBuffer();
	
	    return a;
	}


    Editorial capturarDatosEditorial() {
        Editorial e;
        std::cout << "ID: "; std::cin >> e.id; limpiarBuffer();
        std::cout << "Nombre: "; getline(std::cin, e.nombre);
        std::cout << "Ciudad principal: "; getline(std::cin, e.ciudadPrincipal);
        std::cout << "Pais principal: "; getline(std::cin, e.paisPrincipal);
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
        std::cout << "Numero de edicion: "; std::cin >> e.numeroEdicion; limpiarBuffer();
        std::cout << "Fecha de publicacion (DD/MM/YYYY): "; getline(std::cin, e.fechaPublicacion);
        std::cout << "ID editorial: "; std::cin >> e.idEditorial; limpiarBuffer();
        std::cout << "Ciudad de publicacion: "; getline(std::cin, e.ciudadPublicacion);
        return e;
    }

    // Validaciones
    std::string validarTipoPoesia() {
        std::string tipo;
        do {
            std::cout << "Tipo de poesia (decima, soneto, himno, haiku, romance, octava real, lira o verso libre): ";
            getline(std::cin, tipo);
            // Convertir a minúsculas para comparación
            for (char& c : tipo) c = std::tolower(c);
        } while (tipo != "decima" && tipo != "soneto" && tipo != "himno" && tipo != "haiku" && tipo != "romance" 
		&& tipo != "octava real" && tipo != "lira" && tipo != "verso libre");
        return tipo;
    }

    char validarSexo() {
        char s;
        do {
            std::cout << "Sexo (M/F): ";
            std::cin >> s;
            s = std::toupper(s);
            limpiarBuffer();
        } while (s != 'M' && s != 'F');
        return s;
    }

    std::string validarFormacionBase() {
        std::string formacion;
        do {
            std::cout << "Formacion base (literatura, artes, ciencias sociales, ingenieria, areas de salud, jurisprudencia, otros): ";
            getline(std::cin, formacion);
            // Convertir a minúsculas para comparación
            for (char& c : formacion) c = std::tolower(c);
        } while (formacion != "literatura" && formacion != "artes" && formacion != "ciencias sociales" &&
                 formacion != "ingenieria" && formacion != "areas de salud" && formacion != "jurisprudencia" && formacion != "otros");
        return formacion;
    }

    // Menús específicos
    void menuAutores() {
        int opcion;
        do {
            system("cls");
            std::cout << "\n--- MENU AUTORES ---\n";
            std::cout << "1. Agregar autor\n";
            std::cout << "2. Mostrar autores\n";
            std::cout << "3. Eliminar autor por ID\n";
            std::cout << "0. Volver\n";
            std::cout << "Seleccione una opcion: ";
            std::cin >> opcion;
            limpiarBuffer();

            switch (opcion) {
                case 1: {
                    Autor nuevoAutor = capturarDatosAutor();
                    gestion.getControlAutores().agregar(nuevoAutor);
                    std::cout << "Autor agregado exitosamente.\n";
                    break;
                }
                case 2: {
                    std::cout << "\n--- LISTADO DE AUTORES ---\n";
                    gestion.getControlAutores().mostrarTodos();
                    break;
                }
                case 3: {
                    std::string id;
                    std::cout << "Ingrese ID del autor a eliminar: ";
                    std::cin >> id;
                    gestion.getControlAutores().eliminarPorID(id);
                    std::cout << "Operacion completada.\n";
                    break;
                }
                case 0: break;
                default: std::cout << "Opcion invalida.\n";
            }
            if (opcion != 0) pausar();
        } while (opcion != 0);
    }

    void menuEditoriales() {
        int opcion;
        do {
            system("cls");
            std::cout << "\n--- MENU EDITORIALES ---\n";
            std::cout << "1. Agregar editorial\n";
            std::cout << "2. Mostrar editoriales\n";
            std::cout << "3. Eliminar editorial por ID\n";
            std::cout << "0. Volver\n";
            std::cout << "Seleccione una opcion: ";
            std::cin >> opcion;
            limpiarBuffer();

            switch (opcion) {
                case 1: {
                    Editorial nuevaEditorial = capturarDatosEditorial();
                    gestion.getControlEditoriales().agregar(nuevaEditorial);
                    std::cout << "Editorial agregada exitosamente.\n";
                    break;
                }
                case 2: {
                    std::cout << "\n--- LISTADO DE EDITORIALES ---\n";
                    gestion.getControlEditoriales().mostrarTodos();
                    break;
                }
                case 3: {
                    std::string id;
                    std::cout << "Ingrese ID de la editorial a eliminar: ";
                    std::cin >> id;
                    gestion.getControlEditoriales().eliminarPorID(id);
                    std::cout << "Operacion completada.\n";
                    break;
                }
                case 0: break;
                default: std::cout << "Opcion invalida.\n";
            }
            if (opcion != 0) pausar();
        } while (opcion != 0);
    }

    void menuObras() {
        int opcion;
        do {
            system("cls");
            std::cout << "\n--- MENU OBRAS ---\n";
            std::cout << "1. Agregar obra\n";
            std::cout << "2. Mostrar obras\n";
            std::cout << "3. Eliminar obra por nombre\n";
            std::cout << "0. Volver\n";
            std::cout << "Seleccione una opcion: ";
            std::cin >> opcion;
            limpiarBuffer();

            switch (opcion) {
                case 1: {
                    Obra nuevaObra = capturarDatosObra();
                    gestion.getControlObras().agregar(nuevaObra);
                    std::cout << "Obra agregada exitosamente.\n";
                    break;
                }
                case 2: {
                    std::cout << "\n--- LISTADO DE OBRAS ---\n";
                    gestion.getControlObras().mostrarTodos();
                    break;
                }
                case 3: {
                    std::string nombre;
                    std::cout << "Ingrese nombre de la obra a eliminar: ";
                    getline(std::cin, nombre);
                    gestion.getControlObras().eliminarPorNombre(nombre);
                    std::cout << "Operacion completada.\n";
                    break;
                }
                case 0: break;
                default: std::cout << "Opcion invalida.\n";
            }
            if (opcion != 0) pausar();
        } while (opcion != 0);
    }
    void menuEdiciones() {
    int opcion;
    do {
        system("cls");
        std::cout << "\n--- MENU EDICIONES ---\n";
        std::cout << "1. Agregar edicion\n";
        std::cout << "2. Mostrar ediciones\n";
        std::cout << "3. Eliminar edicion por numero\n";
        std::cout << "0. Volver\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;
        limpiarBuffer();

        switch (opcion) {
            case 1: {
                Edicion nuevaEdicion = capturarDatosEdicion();
                gestion.getControlEdiciones().agregar(nuevaEdicion);
                std::cout << "Edicion agregada exitosamente.\n";
                break;
            }
            case 2: {
                std::cout << "\n--- LISTADO DE EDICIONES ---\n";
                gestion.getControlEdiciones().mostrarTodos();
                break;
            }
            case 3: {
                int numero;
                std::cout << "Ingrese numero de edicion a eliminar: ";
                std::cin >> numero;
                gestion.getControlEdiciones().eliminarPorNumero(numero);
                std::cout << "Operacion completada.\n";
                break;
            }
            case 0: break;
            default: std::cout << "Opcion invalida.\n";
        }
        if (opcion != 0) pausar();
    } while (opcion != 0);
}

    void menuConsultas() {
        int opcion;
        do {
            system("cls");
            std::cout << "\n--- MENU CONSULTAS ---\n";
            std::cout << "1. Obras de un autor por editorial y anio\n";
            std::cout << "2. Obras de un autor por tipo de poesia\n";
            std::cout << "3. Autores publicados por editorial\n";
            std::cout << "4. Editoriales con mas de N poetas\n";
            std::cout << "5. Autores por editorial (lugar de nacimiento)\n";
            std::cout << "6. Autores por formacion y edad\n";
            std::cout << "7. Autores por tipo de poesia y editorial\n";
            std::cout << "8. Validar integridad del sistema\n";
            std::cout << "0. Volver\n";
            std::cout << "Seleccione una opcion: ";
            std::cin >> opcion;
            limpiarBuffer();

            switch (opcion) {
                case 1: {
                    std::string idAutor;
                    std::cout << "Ingrese ID del autor: ";
                    std::cin >> idAutor;
                    gestion.consultaObrasAutorPorEditorialAnio(idAutor);
                    break;
                }
                case 2: {
                    std::string idAutor;
                    std::cout << "Ingrese ID del autor: ";
                    std::cin >> idAutor;
                    gestion.consultaObrasAutorPorTipoPoesia(idAutor);
                    break;
                }
                case 3: {
                    std::string idEditorial;
                    std::cout << "Ingrese ID de la editorial: ";
                    std::cin >> idEditorial;
                    gestion.consultaAutoresPorEditorial(idEditorial);
                    break;
                }
                case 4: {
                    int numeroMinimo;
                    std::cout << "Ingrese numero minimo de poetas: ";
                    std::cin >> numeroMinimo;
                    gestion.consultaEditorialesConNPoetas(numeroMinimo);
                    break;
                }
                case 5: {
                    std::string idEditorial;
                    std::cout << "Ingrese ID de la editorial: ";
                    std::cin >> idEditorial;
                    gestion.consultaAutoresPorEditorialNacimiento(idEditorial);
                    break;
                }
                case 6: {
                    std::string formacion;
                    int edadMin, edadMax;
                    limpiarBuffer();
                    std::cout << "Ingrese formacion: ";
                    getline(std::cin, formacion);
                    std::cout << "Ingrese edad minima: ";
                    std::cin >> edadMin;
                    std::cout << "Ingrese edad maxima: ";
                    std::cin >> edadMax;
                    gestion.consultaAutoresPorFormacionYEdad(formacion, edadMin, edadMax);
                    break;
                }
                case 7: {
                    std::string tipoPoesia, idEditorial;
                    limpiarBuffer();
                    std::cout << "Ingrese tipo de poesia: ";
                    getline(std::cin, tipoPoesia);
                    std::cout << "Ingrese ID de la editorial: ";
                    std::cin >> idEditorial;
                    gestion.consultaAutoresPorTipoYEditorial(tipoPoesia, idEditorial);
                    break;
                }
                case 8: {
                    bool integridad = gestion.validarIntegridadSistema();
                    std::cout << "Estado de integridad: " << (integridad ? "OK" : "PROBLEMAS DETECTADOS") << std::endl;
                    break;
                }
                case 0: break;
                default: std::cout << "Opcion invalida.\n";
            }
            if (opcion != 0) pausar();
        } while (opcion != 0);
    }

    void menuSistema() {
        int opcion;
        do {
            system("cls");
            std::cout << "\n--- MENU SISTEMA ---\n";
            std::cout << "1. Inicializar sistema completo\n";
            std::cout << "2. Construir indices optimizados\n";
            std::cout << "3. Optimizar estructuras\n";
            std::cout << "4. Guardar todos los datos\n";
            std::cout << "0. Volver\n";
            std::cout << "Seleccione una opcion: ";
            std::cin >> opcion;
            limpiarBuffer();

            switch (opcion) {
                case 1: {
                    std::cout << "Inicializando sistema completo...\n";
                    gestion.inicializarSistema();
                    sistemaInicializado = true;
                    std::cout << "Sistema inicializado exitosamente.\n";
                    break;
                }
                case 2: {
                    std::cout << "Construyendo indices optimizados...\n";
                    gestion.construirIndicesOptimizados();
                    std::cout << "Indices construidos exitosamente.\n";
                    break;
                }
                case 3: {
                    std::cout << "Optimizando estructuras...\n";
                    gestion.optimizarEstructuras();
                    std::cout << "Estructuras optimizadas exitosamente.\n";
                    break;
                }
                case 4: {
                    std::cout << "Guardando todos los datos...\n";
                    gestion.guardarTodosSistema();
                    std::cout << "Datos guardados exitosamente.\n";
                    break;
                }
                case 0: break;
                default: std::cout << "Opcion invalida.\n";
            }
            if (opcion != 0) pausar();
        } while (opcion != 0);
    }

public:
    MenuBiblioteca() : sistemaInicializado(false) {}

    void mostrarMenuPrincipal() {
        std::cout << "\n=== SISTEMA DE GESTION DE BIBLIOTECA ===\n";
        if (!sistemaInicializado) {
            std::cout << "SISTEMA NO INICIALIZADO\n";
        }
        std::cout << "1. Gestion de Autores\n";
        std::cout << "2. Gestion de Editoriales\n";
        std::cout << "3. Gestion de Obras\n";
        std::cout << "4. Gestion de Ediciones\n";
        std::cout << "5. Consultas Optimizadas\n";
        std::cout << "6. Sistema y Configuracion\n";
        std::cout << "0. Salir\n";
    }

void mostrarBienvenida() {
    system("cls");
    std::cout << "============================================================\n";
    std::cout << "           SISTEMA DE GESTION DE BIBLIOTECA                 \n";
    std::cout << "============================================================\n";
    std::cout << " Sistema optimizado para consultas de literatura            \n";
    std::cout << " con estructuras de datos avanzadas                         \n";
    std::cout << "============================================================\n\n";

    char respuesta;
    std::cout << "�Desea inicializar el sistema automaticamente? (S/N): ";
    std::cin >> respuesta;
    limpiarBuffer();

    if (std::toupper(respuesta) == 'S') {
        std::cout << "\nInicializando sistema...\n";
        gestion.inicializarSistema();
        sistemaInicializado = true;
        pausar();
    } else {
        std::cout << "\nSistema no inicializado. Use la opcion 'Sistema y Configuracion' para inicializar.\n";
        pausar();
    }
}

    void ejecutar() {
        mostrarBienvenida();
        
        int opcion;
        do {
            system("cls");
            mostrarMenuPrincipal();
            std::cin >> opcion;
            limpiarBuffer();

            switch (opcion) {
                case 1: {
                    if (!sistemaInicializado) {
                        std::cout << "Debe inicializar el sistema primero (opcion 5).\n";
                        pausar();
                        break;
                    }
                    menuAutores();
                    break;
                }
                case 2: {
                    if (!sistemaInicializado) {
                        std::cout << "Debe inicializar el sistema primero (opcion 5).\n";
                        pausar();
                        break;
                    }
                    menuEditoriales();
                    break;
                }
                case 3: {
                    if (!sistemaInicializado) {
                        std::cout << "Debe inicializar el sistema primero (opcion 5).\n";
                        pausar();
                        break;
                    }
                    menuObras();
                    break;
                }
                case 4: {
                    if (!sistemaInicializado) {
                        std::cout << "Debe inicializar el sistema primero (opcion 6).\n";
                        pausar();
                        break;
                    }
                    menuEdiciones();
                    break;
                }
                case 5: {
                    if (!sistemaInicializado) {
                        std::cout << "Debe inicializar el sistema primero (opcion 5).\n";
                        pausar();
                        break;
                    }
                    menuConsultas();
                    break;
                }
                case 6: {
                    menuSistema();
                    break;
                }
                case 0: {
                    if (sistemaInicializado) {
                        char guardar;
                        std::cout << "�Desea guardar los cambios antes de salir? (S/N): ";
                        std::cin >> guardar;
                        if (std::toupper(guardar) == 'S') {
                            gestion.guardarTodosSistema();
                            std::cout << "Datos guardados exitosamente.\n";
                        }
                    }
                    std::cout << "\nGracias por usar el Sistema de Gestion de Biblioteca!\n";
                    pausar();
                    break;
                }
                default: {
                    std::cout << "Opcion invalida. Intente nuevamente.\n";
                    pausar();
                }
            }
        } while (opcion != 0);
    }
};

#endif // MENUBIBLIOTECA_H
