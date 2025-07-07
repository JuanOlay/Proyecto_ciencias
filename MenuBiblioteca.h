/*
MenuBiblioteca.h

Autores:
Juan Felipe Guevara Olaya jfguevarao@udistrital.edu.co
Jean Pierre
Melissa
*/
#ifndef MENUBIBLIOTECA_H
#define MENUBIBLIOTECA_H

#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include "Entidades.h"
#include "GestionBiblioteca.h"

class MenuBiblioteca {
    /*
    Clase que representa el menú principal de la biblioteca.
    Permite interactuar con el sistema de gestión de la biblioteca.
    Atributos:
    - gestion: Objeto de la clase GestionBiblioteca que maneja las operaciones de la
    biblioteca.
    - sistemaInicializado: Indica si el sistema ha sido inicializado correctamente.
    Métodos:
    - MenuBiblioteca: Constructor que inicializa el sistema de gestión de la biblioteca.
    - mostrarMenu: Muestra el menú principal y gestiona las opciones seleccionadas por el
    usuario.
    - capturarDatosAutor: Captura los datos de un autor y los agrega al sistema
    - capturarDatosEditorial: Captura los datos de una editorial y los agrega al sistema
    - capturarDatosObra: Captura los datos de una obra y los agrega al
    sistema
    - capturarDatosEdicion: Captura los datos de una edición y los agrega al
    sistema
    - validarTipoPoesia: Valida el tipo de poesía ingresado por el usuario
    - validarSexo: Valida el sexo ingresado por el usuario
    - validarFormacionBase: Valida la formación base ingresada por el usuario
    - limpiarBuffer: Limpia el buffer de entrada para evitar problemas con la lectura de datos
    - pausar: Pausa la ejecución del programa hasta que el usuario presione Enter
    Descripción:
    Esta clase proporciona un menú interactivo para gestionar los datos de una biblioteca,
    permitiendo al usuario agregar autores, editoriales, obras y ediciones. También incluye
    validaciones para asegurar que los datos ingresados sean correctos y únicos.
    */
private:
    GestionBiblioteca gestion;
    bool sistemaInicializado;

    void limpiarBuffer() {
        /*
        Limpia el buffer de entrada para evitar problemas con la lectura de datos.
        */
        std::cin.clear();
        while (std::cin.get() != '\n');
    }

    void pausar() {
        /*
        Pausa la ejecución del programa hasta que el usuario presione Enter.
        */
        std::cout << "\nPresione Enter para continuar...";
        std::cin.get();
    }

    Autor capturarDatosAutor() {
        /*
        Captura los datos de un autor y los agrega al sistema.
        */
	    Autor a;
	
	    do {
	        std::cout << "ID (único): ";
	        std::cin >> a.id;
	        limpiarBuffer();
	
	        if (gestion.getControlAutores().buscarPorID(a.id) != nullptr) {
	            std::cout << "Error: Ya existe un autor con ese ID. Intente nuevamente.\n";
	        } else {
	            break;
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
        /*
        Captura los datos de una editorial y los agrega al sistema.
        Asegura que el ID sea único y no exista previamente en el sistema.
        Parámetros:
        - gestion: Objeto de la clase GestionBiblioteca que maneja las operaciones de la
        biblioteca.
        Retorno:
        - Un objeto Editorial con los datos capturados.
        Descripción:
        Esta función solicita al usuario que ingrese los datos de una editorial, asegurándose de que
        el ID sea único. Si el ID ya existe, solicita al usuario que ingrese un
        nuevo ID.
        */
        Editorial e;
        
        do {
            std::cout << "ID (único): ";
            std::cin >> e.id;
            limpiarBuffer();
            
            if (gestion.getControlEditoriales().buscarPorID(e.id) != nullptr) {
                std::cout << "Error: Ya existe una editorial con ese ID. Intente nuevamente.\n";
            } else {
                break;
            }
        } while (true);
        
        std::cout << "Nombre: "; getline(std::cin, e.nombre);
        std::cout << "Ciudad principal: "; getline(std::cin, e.ciudadPrincipal);
        std::cout << "Pais principal: "; getline(std::cin, e.paisPrincipal);
        return e;
    }

    Obra capturarDatosObra() {
        /*
        Captura los datos de una obra y los agrega al sistema.
        Asegura que el ID del autor sea válido y exista en el sistema.
        Parámetros:
        - gestion: Objeto de la clase GestionBiblioteca que maneja las operaciones de la
        biblioteca.
        Retorno:
        - Un objeto Obra con los datos capturados.
        Descripción:
        Esta función solicita al usuario que ingrese los datos de una obra, asegurándose de que
        el ID del autor sea válido y exista en el sistema. Si el ID del autor no
        existe, solicita al usuario que ingrese un nuevo ID.
        Si el tipo de poesía no es válido, solicita al usuario que ingrese un nuevo tipo
        de poesía.
        */
        Obra o;
        std::cout << "Nombre: "; getline(std::cin, o.nombre);
        o.tipoPoesia = validarTipoPoesia();
        std::cout << "ID del autor: "; std::cin >> o.idAutor;
        limpiarBuffer();
        return o;
    }

    Edicion capturarDatosEdicion() {
        /*
        Captura los datos de una edición y los agrega al sistema.
        Asegura que el ID de la editorial sea válido y exista en el sistema.
        Parámetros:
        - gestion: Objeto de la clase GestionBiblioteca que maneja las operaciones de la
        biblioteca.
        Retorno:
        - Un objeto Edicion con los datos capturados.
        Descripción:
        Esta función solicita al usuario que ingrese los datos de una edición, asegurándose de que
        el ID de la editorial sea válido y exista en el sistema. Si el ID de la editorial no
        existe, solicita al usuario que ingrese un nuevo ID.
        */
        Edicion e;
        std::cout << "Numero de edicion: "; std::cin >> e.numeroEdicion; limpiarBuffer();
        std::cout << "Fecha de publicacion (DD/MM/YYYY): "; getline(std::cin, e.fechaPublicacion);
        std::cout << "ID editorial: "; std::cin >> e.idEditorial; limpiarBuffer();
        std::cout << "Ciudad de publicacion: "; getline(std::cin, e.ciudadPublicacion);
        std::cout << "Nombre de la obra: "; getline(std::cin, e.idObra);
        return e;
    }

    std::string validarTipoPoesia() {
        /*
        Valida el tipo de poesía ingresado por el usuario.
        Parámetros:
        - tipo: El tipo de poesía a validar.
        Retorno:
        - El tipo de poesía validado.
        */
        std::string tipo;
        do {
            std::cout << "Tipo de poesia (decima, soneto, himno, haiku, romance, octava real, lira o verso libre): ";
            getline(std::cin, tipo);
            for (char& c : tipo) c = std::tolower(c);
        } while (tipo != "decima" && tipo != "soneto" && tipo != "himno" && tipo != "haiku" && tipo != "romance" 
		&& tipo != "octava real" && tipo != "lira" && tipo != "verso libre");
        return tipo;
    }
    char validarSexo() {
        /*
        Valida el sexo ingresado por el usuario.
        Parámetros:
        - sexo: El sexo a validar.
        Retorno:
        - El sexo validado.
        */
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
        /*
        Valida la formación base ingresada por el usuario.
        Parámetros:
        - formacion: La formación base a validar.
        Retorno:
        - La formación base validada.
        */
        std::string formacion;
        do {
            std::cout << "Formacion base (literatura, artes, ciencias sociales, ingenieria, areas de salud, jurisprudencia, otros): ";
            getline(std::cin, formacion);
            for (char& c : formacion) c = std::tolower(c);
        } while (formacion != "literatura" && formacion != "artes" && formacion != "ciencias sociales" &&
                 formacion != "ingenieria" && formacion != "areas de salud" && formacion != "jurisprudencia" && formacion != "otros");
        return formacion;
    }

    void menuAutores() {
        /*
        Muestra el menú de autores y gestiona las opciones seleccionadas.
        Permite agregar, mostrar y eliminar autores.
        Parámetros:
        - gestion: Objeto de la clase GestionBiblioteca que maneja las operaciones de la
        biblioteca.
        Descripción:
        Este método muestra un menú interactivo para gestionar los autores de la biblioteca.
        */
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
                    pausar();
                    break;
                }
                case 2: {
                    std::cout << "\n--- LISTADO DE AUTORES ---\n";
                    gestion.getControlAutores().mostrarTodos();
                    pausar();
                    break;
                }
                case 3: {
                    std::string id;
                    std::cout << "Ingrese ID del autor a eliminar: ";
                    std::cin >> id;
                    gestion.getControlAutores().eliminarPorID(id, "autores.txt");
                    std::cout << "Operacion completada.\n";
                    pausar();
                    break;
                }
                case 0: break;
                default: 
                    std::cout << "Opcion invalida.\n";
                    pausar();
            }
        } while (opcion != 0);
    }

    void menuEditoriales() {
        /*
        Muestra el menú de editoriales y gestiona las opciones seleccionadas.
        Permite agregar, mostrar y eliminar editoriales.
        Parámetros:
        - gestion: Objeto de la clase GestionBiblioteca que maneja las operaciones de la
        biblioteca.
        Descripción:
        Este método muestra un menú interactivo para gestionar las editoriales de la biblioteca.
        */
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
                    pausar();
                    break;
                }
                case 2: {
                    std::cout << "\n--- LISTADO DE EDITORIALES ---\n";
                    gestion.getControlEditoriales().mostrarTodos();
                    pausar();
                    break;
                }
                case 3: {
                    std::string id;
                    std::cout << "Ingrese ID de la editorial a eliminar: ";
                    std::cin >> id;
                    gestion.getControlEditoriales().eliminarPorID(id,"editoriales.txt");
                    std::cout << "Operacion completada.\n";
                    pausar();
                    break;
                }
                case 0: break;
                default: 
                    std::cout << "Opcion invalida.\n";
                    pausar();
            }
        } while (opcion != 0);
    }

    void menuObras() {
        /*
        Muestra el menú de obras y gestiona las opciones seleccionadas.
        Permite agregar, mostrar y eliminar obras.
        Parámetros:
        - gestion: Objeto de la clase GestionBiblioteca que maneja las operaciones de la
        biblioteca.
        Descripción:
        Este método muestra un menú interactivo para gestionar las obras de la biblioteca.
        */
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
                    pausar();
                    break;
                }
                case 2: {
                    std::cout << "\n--- LISTADO DE OBRAS ---\n";
                    gestion.getControlObras().mostrarTodos();
                    pausar();
                    break;
                }
                case 3: {
                    std::string nombre;
                    std::cout << "Ingrese nombre de la obra a eliminar: ";
                    getline(std::cin, nombre);
                    gestion.getControlObras().eliminarPorNombre(nombre,"obras.txt");
                    std::cout << "Operacion completada.\n";
                    pausar();
                    break;
                }
                case 0: break;
                default: 
                    std::cout << "Opcion invalida.\n";
                    pausar();
            }
        } while (opcion != 0);
    }

    void menuEdiciones() {
        /*
        Muestra el menú de ediciones y gestiona las opciones seleccionadas.
        Permite agregar, mostrar y eliminar ediciones.
        Parámetros:
        - gestion: Objeto de la clase GestionBiblioteca que maneja las operaciones de la
        biblioteca.
        Descripción:
        Este método muestra un menú interactivo para gestionar las ediciones de la biblioteca.
        */
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
                    pausar();
                    break;
                }
                case 2: {
                    std::cout << "\n--- LISTADO DE EDICIONES ---\n";
                    gestion.getControlEdiciones().mostrarTodos();
                    pausar();
                    break;
                }
                case 3: {
                    int numero;
                    std::cout << "Ingrese numero de edicion a eliminar: ";
                    std::cin >> numero;
                    gestion.getControlEdiciones().eliminarPorNumero(numero,"ediciones.txt");
                    std::cout << "Operacion completada.\n";
                    pausar();
                    break;
                }
                case 0: break;
                default: 
                    std::cout << "Opcion invalida.\n";
                    pausar();
            }
        } while (opcion != 0);
    }

    void menuConsultas() {
        /*
        Muestra el menú de consultas y gestiona las opciones seleccionadas.
        Permite realizar diversas consultas sobre la biblioteca.
        Parámetros:
        - gestion: Objeto de la clase GestionBiblioteca que maneja las operaciones de la
        biblioteca.
        Descripción:
        Este método muestra un menú interactivo para realizar consultas sobre la biblioteca.
        */
        int opcion;
        do {
            system("cls");
            std::cout << "\n--- MENU CONSULTAS ---\n";
            std::cout << "1. Obras de un autor por editorial y año\n";
            std::cout << "2. Obras de un autor por tipo de poesia\n";
            std::cout << "3. Autores publicados por editorial\n";
            std::cout << "4. Editoriales con mas de N poetas\n";
            std::cout << "5. Autores por editorial (lugar de nacimiento)\n";
            std::cout << "6. Autores por formacion y edad\n";
            std::cout << "7. Autores por tipo de poesia y editorial\n";
            std::cout << "0. Volver\n";
            std::cout << "Seleccione una opcion: ";
            std::cin >> opcion;
            limpiarBuffer();

            switch (opcion) {
                case 1: {
                    std::string idAutor;
                    std::cout << "Ingrese ID del autor: ";
                    std::cin >> idAutor;
                    limpiarBuffer();
                    std::cout << "\n--- RESULTADO DE LA CONSULTA ---\n";
                    gestion.consultaObrasAutorPorEditorialAnio(idAutor);
                    pausar();
                    break;
                }
                case 2: {
                    std::string idAutor;
                    std::cout << "Ingrese ID del autor: ";
                    std::cin >> idAutor;
                    limpiarBuffer();
                    std::cout << "\n--- RESULTADO DE LA CONSULTA ---\n";
                    gestion.consultaObrasAutorPorTipoPoesia(idAutor);
                    pausar();
                    break;
                }
                case 3: {
                    std::string idEditorial;
                    std::cout << "Ingrese ID de la editorial: ";
                    std::cin >> idEditorial;
                    limpiarBuffer();
                    std::cout << "\n--- RESULTADO DE LA CONSULTA ---\n";
                    gestion.consultaAutoresPorEditorial(idEditorial);
                    pausar();
                    break;
                }
                case 4: {
                    int numeroMinimo;
                    std::cout << "Ingrese numero minimo de poetas: ";
                    std::cin >> numeroMinimo;
                    limpiarBuffer();
                    std::cout << "\n--- RESULTADO DE LA CONSULTA ---\n";
                    gestion.consultaEditorialesConNPoetas(numeroMinimo);
                    pausar();
                    break;
                }
                case 5: {
                    std::string idEditorial;
                    std::cout << "Ingrese ID de la editorial: ";
                    std::cin >> idEditorial;
                    limpiarBuffer();
                    std::cout << "\n--- RESULTADO DE LA CONSULTA ---\n";
                    gestion.consultaAutoresPorEditorialNacimiento(idEditorial);
                    pausar();
                    break;
                }
				case 6: {
				    std::string formacion;
				    int edadMin, edadMax;
				
				    std::cout << "Ingrese formación: ";
				    std::getline(std::cin, formacion);
				
				    std::cout << "Ingrese edad mínima: ";
				    std::cin >> edadMin;
				
				    std::cout << "Ingrese edad máxima: ";
				    std::cin >> edadMax;
				    limpiarBuffer();
				
				    std::cout << "\n--- RESULTADO DE LA CONSULTA ---\n";
				
				    gestion.consultaAutoresPorEdadYFormacion(edadMin, edadMax, formacion);
				    pausar();
                    break;
				}
                case 7: {
                    std::string tipoPoesia, idEditorial;
                    std::cout << "Ingrese tipo de poesia: ";
                    getline(std::cin, tipoPoesia);
                    std::cout << "Ingrese ID de la editorial: ";
                    std::cin >> idEditorial;
                    limpiarBuffer();
                    std::cout << "\n--- RESULTADO DE LA CONSULTA ---\n";
                    gestion.consultaAutoresPorTipoPoesiaYEditorial(tipoPoesia, idEditorial);
                    pausar();
                    break;
                }
                case 0: break;
                default: 
                    std::cout << "Opcion invalida.\n";
                    pausar();
            }
        } while (opcion != 0);
    }

    void menuSistema() {
        /*
        Muestra el menú del sistema y gestiona las opciones seleccionadas.
        Permite inicializar el sistema, construir índices, optimizar estructuras y guardar datos.
        Parámetros:
        - gestion: Objeto de la clase GestionBiblioteca que maneja las operaciones de la
        biblioteca.
        Descripción:
        Este método muestra un menú interactivo para gestionar el sistema de la biblioteca.
        */
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
                    pausar();
                    break;
                }
                case 2: {
                    std::cout << "Construyendo indices optimizados...\n";
                    gestion.construirIndicesOptimizados();
                    std::cout << "Indices construidos exitosamente.\n";
                    pausar();
                    break;
                }
                case 3: {
                    std::cout << "Optimizando estructuras...\n";
                    gestion.optimizarEstructuras();
                    std::cout << "Estructuras optimizadas exitosamente.\n";
                    pausar();
                    break;
                }
                case 4: {
                    std::cout << "Guardando todos los datos...\n";
                    gestion.guardarTodosSistema();
                    std::cout << "Datos guardados exitosamente.\n";
                    pausar();
                    break;
                }
                case 0: break;
                default: 
                    std::cout << "Opcion invalida.\n";
                    pausar();
            }
        } while (opcion != 0);
    }

public:
    MenuBiblioteca() : sistemaInicializado(false) {}

    void mostrarMenuPrincipal() {
        /*
        Muestra el menú principal y gestiona las opciones seleccionadas.
        Permite acceder a las diferentes secciones del sistema.
        Parámetros:
        - gestion: Objeto de la clase GestionBiblioteca que maneja las operaciones de la
        biblioteca.
        Descripción:
        Este método muestra un menú interactivo para navegar por las diferentes secciones
        del sistema de gestión de la biblioteca.
        */
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
        std::cout << "Seleccione una opcion: ";
    }

    void mostrarBienvenida() {
        /*
        Muestra la pantalla de bienvenida del sistema.
        */
        system("cls");
        std::cout << "============================================================\n";
        std::cout << "           SISTEMA DE GESTION DE BIBLIOTECA                 \n";
        std::cout << "============================================================\n";
        std::cout << " Sistema optimizado para consultas de literatura            \n";
        std::cout << " con estructuras de datos avanzadas                         \n";
        std::cout << "============================================================\n\n";

        char respuesta;
        std::cout << "¿Desea inicializar el sistema automaticamente? (S/N): ";
        std::cin >> respuesta;
        limpiarBuffer();

        if (std::toupper(respuesta) == 'S') {
            std::cout << "\nInicializando sistema...\n";
            gestion.inicializarSistema();
            sistemaInicializado = true;
            std::cout << "Sistema inicializado exitosamente.\n";
            pausar();
        } else {
            std::cout << "\nSistema no inicializado. Use la opcion 'Sistema y Configuracion' para inicializar.\n";
            pausar();
        }
    }

    void ejecutar() {
        /*
        Método principal que ejecuta el menú del sistema.
        */
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
                        std::cout << "Debe inicializar el sistema primero (opcion 6).\n";
                        pausar();
                        break;
                    }
                    menuAutores();
                    break;
                }
                case 2: {
                    if (!sistemaInicializado) {
                        std::cout << "Debe inicializar el sistema primero (opcion 6).\n";
                        pausar();
                        break;
                    }
                    menuEditoriales();
                    break;
                }
                case 3: {
                    if (!sistemaInicializado) {
                        std::cout << "Debe inicializar el sistema primero (opcion 6).\n";
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
                        std::cout << "Debe inicializar el sistema primero (opcion 6).\n";
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
                        std::cout << "¿Desea guardar los cambios antes de salir? (S/N): ";
                        std::cin >> guardar;
                        if (std::toupper(guardar) == 'S') {
                            std::cout << "Guardando datos...\n";
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