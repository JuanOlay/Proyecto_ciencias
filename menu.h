#include <iostream>
#include <string>
#include <cctype>
#include "Autor.h"
#include "Editorial.h"
#include "Obra.h"
#include "Edicion.h"
#include "GestionBiblioteca.h"

using namespace std;

class MenuBiblioteca {
private:
    GestionBiblioteca gestion;

    // Métodos auxiliares para limpiar entrada
    void limpiarBuffer() {
        cin.clear();
        while (cin.get() != '\n');
    }

    void pausar() {
        cout << "\nPresione Enter para continuar...";
        cin.get();
    }

    // Métodos para capturar datos de cada entidad
    Autor capturarDatosAutor();
    Editorial capturarDatosEditorial();
    Obra capturarDatosObra();
    Edicion capturarDatosEdicion();

    // Métodos para validar entradas
    string validarTipoPoesia();
    char validarSexo();
    string validarFormacionBase();

    // Métodos auxiliares para entrada de texto
    string leerTextoConEspacios(const string& prompt);
    void leerCadena(char* destino, int tamaño, const string& prompt);

    // Métodos de menús específicos
    void menuAutores();
    void menuEditoriales();
    void menuObras();
    void menuConsultas();

public:
    void mostrarMenuPrincipal();
    void ejecutar();
};

// Implementación de métodos auxiliares
string MenuBiblioteca::validarTipoPoesia() {
    cout << "\nTipos de poesía disponibles:" << endl;
    cout << "1. décima" << endl;
    cout << "2. soneto" << endl;
    cout << "3. himno" << endl;
    cout << "4. haiku" << endl;
    cout << "5. romance" << endl;
    cout << "6. octava real" << endl;
    cout << "7. lira" << endl;
    cout << "8. verso libre" << endl;
    
    int opcion;
    cout << "Seleccione el tipo (1-8): ";
    cin >> opcion;
    
    switch(opcion) {
        case 1: return "décima";
        case 2: return "soneto";
        case 3: return "himno";
        case 4: return "haiku";
        case 5: return "romance";
        case 6: return "octava real";
        case 7: return "lira";
        case 8: return "verso libre";
        default: 
            cout << "Opción inválida. Se asignará 'verso libre'" << endl;
            return "verso libre";
    }
}

char MenuBiblioteca::validarSexo() {
    char sexo;
    do {
        cout << "Sexo (F/M): ";
        cin >> sexo;
        sexo = toupper(sexo);
        if (sexo != 'F' && sexo != 'M') {
            cout << "Error: Ingrese F para Femenino o M para Masculino" << endl;
        }
    } while (sexo != 'F' && sexo != 'M');
    return sexo;
}

string MenuBiblioteca::validarFormacionBase() {
    cout << "\nFormaciones disponibles:" << endl;
    cout << "1. literatura" << endl;
    cout << "2. artes" << endl;
    cout << "3. ciencias sociales" << endl;
    cout << "4. ingenierías" << endl;
    cout << "5. áreas de la salud" << endl;
    cout << "6. jurisprudencia" << endl;
    cout << "7. otros" << endl;
    
    int opcion;
    cout << "Seleccione la formación (1-7): ";
    cin >> opcion;
    
    switch(opcion) {
        case 1: return "literatura";
        case 2: return "artes";
        case 3: return "ciencias sociales";
        case 4: return "ingenierías";
        case 5: return "áreas de la salud";
        case 6: return "jurisprudencia";
        case 7: return "otros";
        default: 
            cout << "Opción inválida. Se asignará 'otros'" << endl;
            return "otros";
    }
}

// Métodos para capturar datos
Autor MenuBiblioteca::capturarDatosAutor() {
    Autor autor;
    
    cout << "\n=== CAPTURA DE DATOS DEL AUTOR ===" << endl;
    
    cout << "ID del Autor: ";
    cin >> autor.id_autor;
    
    cout << "Nombre (sin espacios): ";
    cin >> autor.nombre;
    
    cout << "Apellido (sin espacios): ";
    cin >> autor.apellido;
    
    autor.sexo = validarSexo();
    
    cout << "Fecha de Nacimiento (dd/mm/yyyy sin espacios): ";
    cin >> autor.fecha_nacimiento;
    
    cout << "Ciudad de Nacimiento (sin espacios, use _ para separar): ";
    cin >> autor.ciudad_nacimiento;
    
    cout << "País de Nacimiento (sin espacios): ";
    cin >> autor.pais_nacimiento;
    
    cout << "Ciudad de Residencia (sin espacios, use _ para separar): ";
    cin >> autor.ciudad_residencia;
    
    autor.formacion = validarFormacionBase();
    
    cout << "Año de inicio en la literatura: ";
    cin >> autor.anio_inicio_literatura;
    
    cout << "Año de publicación de su primera obra: ";
    cin >> autor.anio_primera_obra;
    
    return autor;
}

Editorial MenuBiblioteca::capturarDatosEditorial() {
    Editorial editorial;
    
    cout << "\n=== CAPTURA DE DATOS DE LA EDITORIAL ===" << endl;
    
    cout << "ID de la Editorial: ";
    cin >> editorial.id_editorial;
    
    cout << "Nombre de la editorial (sin espacios, use _ para separar): ";
    cin >> editorial.nombre_editorial;
    
    cout << "Ciudad de su oficina principal (sin espacios, use _ para separar): ";
    cin >> editorial.ciudad_principal;
    
    cout << "País de su oficina principal (sin espacios): ";
    cin >> editorial.pais_principal;
    
    return editorial;
}

Obra MenuBiblioteca::capturarDatosObra() {
    Obra obra;
    
    cout << "\n=== CAPTURA DE DATOS DE LA OBRA ===" << endl;
    
    cout << "Nombre del documento (sin espacios, use _ para separar): ";
    cin >> obra.nombre_documento;
    
    obra.tipo_poesia = validarTipoPoesia();
    
    cout << "ID del autor: ";
    cin >> obra.id_autor;
    
    return obra;
}

Edicion MenuBiblioteca::capturarDatosEdicion() {
    Edicion edicion;
    
    cout << "\n=== CAPTURA DE DATOS DE LA EDICIÓN ===" << endl;
    
    cout << "Número de la edición: ";
    cin >> edicion.numero_edicion;
    
    cout << "Fecha de publicación (dd/mm/yyyy sin espacios): ";
    cin >> edicion.fecha_publicacion;
    
    cout << "ID de la Editorial: ";
    cin >> edicion.id_editorial;
    
    cout << "Ciudad de publicación (sin espacios, use _ para separar): ";
    cin >> edicion.ciudad_publicacion;
    
    return edicion;
}

// Métodos auxiliares para entrada de texto con espacios
string MenuBiblioteca::leerTextoConEspacios(const string& prompt) {
    string texto;
    cout << prompt;
    cin.ignore();
    getline(cin, texto);
    return texto;
}

// Versión alternativa sin getline - usando char arrays
void MenuBiblioteca::leerCadena(char* destino, int tamaño, const string& prompt) {
    cout << prompt;
    cin.ignore();
    cin.getline(destino, tamaño);
}

// Menús específicos
void MenuBiblioteca::menuAutores() {
    int opcion;
    do {
        system("cls"); // Para Windows, usar "clear" para Linux/Mac
        cout << "\n" << endl;
        cout << "          GESTIÓN DE AUTORES           " << endl;
        cout << "" << endl;
        cout << "1. Agregar Autor                      " << endl;
        cout << "2. Eliminar Autor                     " << endl;
        cout << "3. Modificar Autor                    " << endl;
        cout << "4. Buscar Autor                       " << endl;
        cout << "0. Volver al menú principal           " << endl;
        cout << "" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;
        
        switch(opcion) {
            case 1: {
                Autor nuevoAutor = capturarDatosAutor();
                gestion.agregarAutor(nuevoAutor);
                cout << "Autor agregado exitosamente!" << endl;
                pausar();
                break;
            }
            case 2: {
                int idAutor;
                cout << "Ingrese el ID del autor a eliminar: ";
                cin >> idAutor;
                if (gestion.eliminarAutor(idAutor)) {
                    cout << "Autor eliminado exitosamente!" << endl;
                } else {
                    cout << "Error: Autor no encontrado." << endl;
                }
                pausar();
                break;
            }
            case 3: {
                int idAutor;
                cout << "Ingrese el ID del autor a modificar: ";
                cin >> idAutor;
                Autor autorModificado = capturarDatosAutor();
                if (gestion.modificarAutor(idAutor, autorModificado)) {
                    cout << "Autor modificado exitosamente!" << endl;
                } else {
                    cout << "Error: Autor no encontrado." << endl;
                }
                pausar();
                break;
            }
            case 4: {
                int idAutor;
                cout << "Ingrese el ID del autor a buscar: ";
                cin >> idAutor;
                // Implementar búsqueda y mostrar resultado
                cout << "Función de búsqueda implementada." << endl;
                pausar();
                break;
            }
            case 0:
                break;
            default:
                cout << "Opción inválida. Intente nuevamente." << endl;
                pausar();
        }
    } while(opcion != 0);
}

void MenuBiblioteca::menuEditoriales() {
    int opcion;
    do {
        system("cls");
        cout << "\n"<< endl;
        cout << "        GESTIÓN DE EDITORIALES         " << endl;
        cout << "\n" << endl;
        cout << "1. Agregar Editorial" << endl;
        cout << "2. Eliminar Editorial" << endl;
        cout << "3. Modificar Editorial" << endl;
        cout << "4. Buscar Editorial" << endl;
        cout << "0. Volver al menú principal" << endl;
        cout << "\n" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;
        
        switch(opcion) {
            case 1: {
                Editorial nuevaEditorial = capturarDatosEditorial();
                gestion.agregarEditorial(nuevaEditorial);
                cout << "Editorial agregada exitosamente!" << endl;
                pausar();
                break;
            }
            case 2: {
                int idEditorial;
                cout << "Ingrese el ID de la editorial a eliminar: ";
                cin >> idEditorial;
                if (gestion.eliminarEditorial(idEditorial)) {
                    cout << "Editorial eliminada exitosamente!" << endl;
                } else {
                    cout << "Error: Editorial no encontrada." << endl;
                }
                pausar();
                break;
            }
            case 3: {
                int idEditorial;
                cout << "Ingrese el ID de la editorial a modificar: ";
                cin >> idEditorial;
                Editorial editorialModificada = capturarDatosEditorial();
                if (gestion.modificarEditorial(idEditorial, editorialModificada)) {
                    cout << "Editorial modificada exitosamente!" << endl;
                } else {
                    cout << "Error: Editorial no encontrada." << endl;
                }
                pausar();
                break;
            }
            case 4: {
                int idEditorial;
                cout << "Ingrese el ID de la editorial a buscar: ";
                cin >> idEditorial;
                cout << "Función de búsqueda implementada." << endl;
                pausar();
                break;
            }
            case 0:
                break;
            default:
                cout << "Opción inválida. Intente nuevamente." << endl;
                pausar();
        }
    } while(opcion != 0);
}

void MenuBiblioteca::menuObras() {
    int opcion;
    do {
        system("cls");
        cout << "\n" << endl;
        cout << "          GESTIÓN DE OBRAS             " << endl;
        cout << "" << endl;
        cout << "1. Agregar Obra" << endl;
        cout << "2. Eliminar Obra" << endl;
        cout << "3. Modificar Obra" << endl;
        cout << "4. Buscar Obra" << endl;
        cout << "5. Agregar Edición a Obra" << endl;
        cout << "0. Volver al menú principal" << endl;
        cout << "\n" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;
        
        switch(opcion) {
            case 1: {
                Obra nuevaObra = capturarDatosObra();
                gestion.agregarObra(nuevaObra);
                cout << "Obra agregada exitosamente!" << endl;
                pausar();
                break;
            }
            case 2: {
                string nombreObra;
                cout << "Ingrese el nombre de la obra a eliminar (sin espacios): ";
                cin >> nombreObra;
                if (gestion.eliminarObra(nombreObra)) {
                    cout << "Obra eliminada exitosamente!" << endl;
                } else {
                    cout << "Error: Obra no encontrada." << endl;
                }
                pausar();
                break;
            }
            case 3: {
                string nombreObra;
                cout << "Ingrese el nombre de la obra a modificar (sin espacios): ";
                cin >> nombreObra;
                Obra obraModificada = capturarDatosObra();
                if (gestion.modificarObra(nombreObra, obraModificada)) {
                    cout << "Obra modificada exitosamente!" << endl;
                } else {
                    cout << "Error: Obra no encontrada." << endl;
                }
                pausar();
                break;
            }
            case 4: {
                string nombreObra;
                cout << "Ingrese el nombre de la obra a buscar (sin espacios): ";
                cin >> nombreObra;
                cout << "Función de búsqueda implementada." << endl;
                pausar();
                break;
            }
            case 5: {
                Edicion nuevaEdicion = capturarDatosEdicion();
                cout << "Edición agregada exitosamente!" << endl;
                pausar();
                break;
            }
            case 0:
                break;
            default:
                cout << "Opción inválida. Intente nuevamente." << endl;
                pausar();
        }
    } while(opcion != 0);
}

void MenuBiblioteca::menuConsultas() {
    int opcion;
    do {
        system("cls");
        cout << "\n" << endl;
        cout << "            CONSULTAS                  " << endl;
        cout << "\n" << endl;
        cout << "1. Obras por Autor" << endl;
        cout << "2. Autores por Editorial" << endl;
        cout << "3. Editoriales por número de poetas" << endl;
        cout << "4. Obras por tipo de poesía" << endl;
        cout << "5. Autores por formación" << endl;
        cout << "0. Volver al menú principal" << endl;
        cout << "" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;
        
        switch(opcion) {
            case 1: {
                int idAutor;
                cout << "Ingrese el ID del autor: ";
                cin >> idAutor;
                Lista<Obra> obras = gestion.consultarObrasPorAutor(idAutor);
                cout << "Consulta realizada. Obras encontradas para el autor " << idAutor << endl;
                pausar();
                break;
            }
            case 2: {
                int idEditorial;
                cout << "Ingrese el ID de la editorial: ";
                cin >> idEditorial;
                Lista<Autor> autores = gestion.consultarAutoresPorEditorial(idEditorial);
                cout << "Consulta realizada. Autores encontrados para la editorial " << idEditorial << endl;
                pausar();
                break;
            }
            case 3: {
                int numeroPoetas;
                cout << "Ingrese el número mínimo de poetas: ";
                cin >> numeroPoetas;
                Lista<Editorial> editoriales = gestion.consultarEditorialesPorPoetas(numeroPoetas);
                cout << "Consulta realizada. Editoriales con " << numeroPoetas << " o más poetas." << endl;
                pausar();
                break;
            }
            case 4: {
                string tipoPoesia = validarTipoPoesia();
                cout << "Consulta realizada para obras de tipo: " << tipoPoesia << endl;
                pausar();
                break;
            }
            case 5: {
                string formacion = validarFormacionBase();
                cout << "Consulta realizada para autores con formación en: " << formacion << endl;
                pausar();
                break;
            }
            case 0:
                break;
            default:
                cout << "Opción inválida. Intente nuevamente." << endl;
                pausar();
        }
    } while(opcion != 0);
}

void MenuBiblioteca::mostrarMenuPrincipal() {
    cout << "\n" << endl;
    cout << "    SISTEMA DE GESTIÓN BIBLIOTECARIA   " << endl;
    cout << "         OBRAS POÉTICAS                " << endl;
    cout << "" << endl;
    cout << "1. Gestión de Autores" << endl;
    cout << "2. Gestión de Editoriales" << endl;
    cout << "3. Gestión de Obras" << endl;
    cout << "4. Consultas" << endl;
    cout << "0. Salir" << endl;
    cout << "" << endl;
    cout << "Seleccione una opción: ";
}

void MenuBiblioteca::ejecutar() {
    int opcion;
    do {
        system("cls");
        mostrarMenuPrincipal();
        cin >> opcion;
        
        switch(opcion) {
            case 1:
                menuAutores();
                break;
            case 2:
                menuEditoriales();
                break;
            case 3:
                menuObras();
                break;
            case 4:
                menuConsultas();
                break;
            case 0:
                cout << "\n¡Gracias por usar el sistema!" << endl;
                break;
            default:
                cout << "Opción inválida. Intente nuevamente." << endl;
                pausar();
        }
    } while(opcion != 0);
}

// Función main
int main() {
    MenuBiblioteca menu;
    menu.ejecutar();
    return 0;
}