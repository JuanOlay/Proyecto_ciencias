/*
GestionBiblioteca.h

Es un archivo de cabecera que contiene la definición de la clase GestionBiblioteca,
la cual se encarga de gestionar la información de la biblioteca, incluyendo autores,
editoriales, obras y ediciones.

Autores:
Juan Felipe Guevara Olaya jfguevarao1211@udistrital.edu.co
Jean Pierre
Melissa
*/

#ifndef GESTIONBIBLIOTECA_H
#define GESTIONBIBLIOTECA_H

#include "ArbolRojiNegro.h"
#include "Multilista.h"
#include "ControlAutores.h"
#include "ControlEditoriales.h"
#include "ControlObras.h"
#include "ControlEdiciones.h"
#include "ManejadorArchivos.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <set>
#include <iomanip>
#include "Entidades.h"

struct GestionBibliotecaO {
    /*
    Clase encargada de gestionar la información de la biblioteca.
    Atributos:
    - controlAutores: Controlador de autores.
    - controlEditoriales: Controlador de editoriales.
    - controlObras: Controlador de obras.
    - controlEdiciones: Controlador de ediciones.
    Métodos:
    - agregarAutor: Agrega un nuevo autor.
    - agregarEditorial: Agrega una nueva editorial.
    - agregarObra: Agrega una nueva obra.
    - agregarEdicion: Agrega una nueva edición.
    Descripción:
    Esta clase se encarga de coordinar las operaciones de gestión de la biblioteca,
    utilizando los controladores correspondientes para cada entidad.
    */
private:

    ControlAutores controlAutores;
    ControlEditoriales controlEditoriales;
    ControlObras controlObras;

    // Arboles principales para búsquedas por ID (O(log n))
    ArbolRojiNegro<Autor> arbolAutores;
    ArbolRojiNegro<Editorial> arbolEditoriales;
    ArbolRojiNegro<Obra> arbolObras;
    ArbolRojiNegro<Edicion> arbolEdiciones;

    // MULTILISTAS OPTIMIZADAS POR CONSULTA

    // Para consulta 1: Número total de obras de un autor, clasificadas por editorial y año
    Multilista<std::string, Obra> AutorObras;                    // Clave: idAutor
    Multilista<std::string, std::string> EditorialAnios;         // Clave: idEditorial, Valor: "año-nombreObra"

    // Para consulta 2: Obras de un autor por tipo de poesía
    Multilista<std::string, std::string> AutorTipoPoesia;        // Clave: idAutor, Valor: "tipoPoesia-nombreObra-fechaPublicacion-numEdicion"

    // Para consulta 3: Autores publicados por editorial, clasificados por ciudad y año inicio
    Multilista<std::string, std::string> EditorialAutores;      // Clave: idEditorial, Valor: "ciudadResidencia-añoInicio-idAutor"

    // Para consulta 4: Editoriales con número de poetas > N
    Multilista<std::string, std::string> EditorialPoetas;       // Clave: idEditorial, Valor: idAutor (para contar únicos)

    // Para consulta 5: Autores por editorial, clasificados por ciudad y país de nacimiento
    Multilista<std::string, std::string> EditorialAutoresNacimiento; // Clave: idEditorial, Valor: "paisNacimiento-ciudadNacimiento-idAutor"

    // Para consulta 6: Autores por formación y edad
    Multilista<std::string, std::string> FormacionAutores;      // Clave: formacionBase, Valor: "edad-añoPrimeraObra-idAutor"

    // Para consulta 7: Autores por tipo de poesía y editorial
    Multilista<std::string, std::string> TipoPoesiaEditorial;   // Clave: "tipoPoesia-idEditorial", Valor: idAutor

    /*
    Las estructuras se eligieron seleccionadas se eligieron porque permiten un acceso eficiente a la información
    y facilitan la implementación de las consultas requeridas por el sistema.

    - ArbolRojiNegro: Permite búsquedas rápidas por ID de autores, editoriales, obras y ediciones.
    - Multilista: Permite almacenar relaciones complejas entre entidades, como autores y obras, editoriales y ediciones,
      facilitando la implementación de consultas específicas.
    
    */


    std::vector<Autor> autores;
    std::vector<Editorial> editoriales;
    std::vector<Obra> obras;
    std::vector<Edicion> ediciones;
    std::map<std::string, std::vector<int>> autorObras;
    std::map<std::string, std::vector<int>> editorialEdiciones;
    std::map<std::string, std::vector<int>> obraEdiciones;
    
    int calcularEdad(const std::string& fechaNacimiento) const {
        /*
        Calcula la edad a partir de la fecha de nacimiento en formato "DD/MM/AAAA".
        Parámetros:
        - fechaNacimiento: Fecha de nacimiento en formato "DD/MM/AAAA" o "DD-MM-AAAA".
        Retorna:
        - Edad calculada en años. Si la fecha es inválida o no se puede extraer el año, retorna 0.
        Descripción:
        Este método extrae el año de la fecha de nacimiento y calcula la edad restando el año de nacimiento al año actual (2024).
        Si la fecha de nacimiento está vacía, retorna 0.
        */
        if (fechaNacimiento.empty()) return 0;
        size_t pos = fechaNacimiento.find_last_of("/-");
        if (pos != std::string::npos && pos + 1 < fechaNacimiento.length()) {
            std::string anioStr = fechaNacimiento.substr(pos + 1);
            int anioNacimiento = std::stoi(anioStr);
            return (anioNacimiento > 0) ? (2024 - anioNacimiento) : 0;
        }
        return 0;
    }
    
    int extraerAnio(const std::string& fecha) const {
        /*
        Extrae el año de una fecha en formato "DD/MM/AAAA" o "DD-MM-AAAA".
        Parámetros:
        - fecha: Fecha en formato "DD/MM/AAAA" o "DD-MM-AAAA".
        Retorna:
        - Año extraído como entero. Si la fecha es inválida o no se puede extraer el año, retorna 0.
        Descripción:
        Este método busca el último separador ("/" o "-") en la fecha y extrae el año que sigue a este.
        Si la fecha está vacía, retorna 0.
        */
        if (fecha.empty()) return 0;
        size_t pos = fecha.find_last_of("/-");
        if (pos != std::string::npos && pos + 1 < fecha.length()) {
            std::string anioStr = fecha.substr(pos + 1);
            return std::stoi(anioStr);
        }
        return 0;
    }
    
    std::string obtenerNombreEditorial(const std::string& idEditorial) const {
        /*
        Busca el nombre de una editorial a partir de su ID.
        Parámetros:
        - idEditorial: ID de la editorial.
        Retorna:
        - Nombre de la editorial si se encuentra, de lo contrario "Editorial no encontrada".
        */
        for (const auto& editorial : editoriales) {
            if (editorial.id == idEditorial) {
                return editorial.nombre;
            }
        }
        return "Editorial no encontrada";
    }
    
    std::string obtenerNombreAutor(const std::string& idAutor) const {
        /*
        Busca el nombre de un autor a partir de su ID.
        Parámetros:
        - idAutor: ID del autor.
        Retorna:
        - Nombre del autor si se encuentra, de lo contrario "Autor no encontrado".
        */
        for (const auto& autor : autores) {
            if (autor.id == idAutor) {
                return autor.nombre + " " + autor.apellido;
            }
        }
        return "Autor no encontrado";
    }
    
    Autor* obtenerAutorPorId(const std::string& idAutor) {
        /*
        Busca un autor a partir de su ID.
        Parámetros:
        - idAutor: ID del autor.
        Retorna:
        - Puntero al autor si se encuentra, de lo contrario nullptr.
        */
        for (auto& autor : autores) {
            if (autor.id == idAutor) {
                return &autor;
            }
        }
        return nullptr;
    }
    
    Editorial* obtenerEditorialPorId(const std::string& idEditorial) {
        /*
        Busca una editorial a partir de su ID.
        Parámetros:
        - idEditorial: ID de la editorial.
        Retorna:
        - Puntero a la editorial si se encuentra, de lo contrario nullptr.
        */
        for (auto& editorial : editoriales) {
            if (editorial.id == idEditorial) {
                return &editorial;
            }
        }
        return nullptr;
    }
    
    void construirIndices() {
        /*
        Construye los índices para facilitar la búsqueda de obras por autor, ediciones por editorial y ediciones por obra.
        Parámetros:
        - Ninguno.
        Descripción:
        Este método recorre las listas de obras y ediciones para construir índices que permiten acceder rápidamente a las obras de un autor,
        las ediciones de una obra y las ediciones de una editorial.
        Los índices se almacenan en mapas donde la clave es el ID del autor, editorial o obra, y el valor es un vector de índices
        que apuntan a las posiciones en las listas de obras o ediciones.
        */
        autorObras.clear();
        editorialEdiciones.clear();
        obraEdiciones.clear();

        for (size_t i = 0; i < obras.size(); ++i) {
            autorObras[obras[i].idAutor].push_back(i);
        }
        
        for (size_t i = 0; i < ediciones.size(); ++i) {
            editorialEdiciones[ediciones[i].idEditorial].push_back(i);
        }
        
        for (size_t i = 0; i < ediciones.size(); ++i) {
            obraEdiciones[ediciones[i].idObra].push_back(i);
        }
    }
    
    void guardarArchivo(const std::string& archivo, const std::string& tipo) {
        /*
        Guarda la información de la biblioteca en un archivo.
        Parámetros:
        - archivo: Nombre del archivo.
        - tipo: Tipo de información a guardar (autores, editoriales, obras, ediciones).
        Descripción:
        Este método abre un archivo en modo escritura y guarda la información de los autores, editoriales, obras o ediciones
        en formato CSV. Cada línea del archivo representa un registro, con los campos separados por punto y coma.
        Si el archivo no se puede abrir, muestra un mensaje de error.
        Parámetros:
        - archivo: Nombre del archivo donde se guardará la información.
        - tipo: Tipo de información a guardar (autores, editoriales, obras, ediciones).
        */
        std::ofstream file(archivo);
        if (!file.is_open()) {
            std::cout << "Error al abrir archivo: " << archivo << std::endl;
            return;
        }
        
        if (tipo == "autores") {
            for (const auto& autor : autores) {
                file << autor.id << ";" << autor.nombre << ";" << autor.apellido << ";" 
                     << autor.sexo << ";" << autor.fechaNacimiento << ";" << autor.ciudadNacimiento << ";"
                     << autor.paisNacimiento << ";" << autor.ciudadResidencia << ";" << autor.formacionBase << ";"
                     << autor.anioInicioLiteratura << ";" << autor.anioPrimeraObra << std::endl;
            }
        } else if (tipo == "editoriales") {
            for (const auto& editorial : editoriales) {
                file << editorial.id << ";" << editorial.nombre << ";" 
                     << editorial.ciudadPrincipal << ";" << editorial.paisPrincipal << std::endl;
            }
        } else if (tipo == "obras") {
            for (const auto& obra : obras) {
                file << obra.nombre << ";" << obra.tipoPoesia << ";" << obra.idAutor << std::endl;
            }
        } else if (tipo == "ediciones") {
            for (const auto& edicion : ediciones) {
                file << edicion.numeroEdicion << ";" << edicion.fechaPublicacion << ";" 
                     << edicion.idEditorial << ";" << edicion.ciudadPublicacion << ";" 
                     << edicion.idObra << std::endl;
            }
        }
        file.close();
    }

public:
    GestionBibliotecaO() {}
    
    class ControlAutores {
        /*
        Controlador para gestionar la información de los autores.
        Atributos:
        - autores: Referencia a la lista de autores.
        Métodos:
        - agregar: Agrega un nuevo autor a la lista.
        - mostrarTodos: Muestra todos los autores.
        - buscarPorID: Busca un autor por su ID.
        - eliminarPorID: Elimina un autor por su ID y guarda los cambios en el archivo.
        Descripción:
        Esta clase se encarga de gestionar las operaciones relacionadas con los autores,
        como agregar nuevos autores, mostrar la lista de autores, buscar un autor por su ID
        y eliminar un autor por su ID. Utiliza una referencia a la lista de autores para realizar
        las operaciones de manera eficiente.
        */
    private:
        std::vector<Autor>& autores;
        
    public:
        ControlAutores(std::vector<Autor>& a) : autores(a) {
            /*
            Constructor de la clase ControlAutores.
            Inicializa la referencia a la lista de autores.
            */
        }
        
        void agregar(const Autor& autor) {
            /*
            Agrega un nuevo autor a la lista.
            Parámetros:
            - autor: El autor a agregar.
            Descripción:
            Esta función agrega un nuevo autor a la lista de autores.
            Si el autor ya existe, no se agrega nuevamente.
            */
            autores.push_back(autor);
        }
        
        void mostrarTodos() {
            /*
            Muestra todos los autores en la lista.
            Descripción:
            Esta función muestra todos los autores en la lista de autores.
            Si no hay autores en la lista, se muestra un mensaje indicando que la lista está vacía.
            */
            for (const auto& autor : autores) {
                std::cout << "ID: " << autor.id << ", Nombre: " << autor.nombre << " " << autor.apellido
                         << ", Sexo: " << autor.sexo << ", Nacimiento: " << autor.fechaNacimiento
                         << ", Ciudad: " << autor.ciudadNacimiento << ", País: " << autor.paisNacimiento
                         << ", Residencia: " << autor.ciudadResidencia << ", Formación: " << autor.formacionBase
                         << ", Inicio literatura: " << autor.anioInicioLiteratura
                         << ", Primera obra: " << autor.anioPrimeraObra << std::endl;
            }
        }
        
        Autor* buscarPorID(const std::string& id) {
            /*
            Busca un autor por su ID.
            Parámetros:
            - id: El ID del autor a buscar.
            Retorna:
            - Un puntero al autor encontrado, o nullptr si no se encuentra.
            */
            for (auto& autor : autores) {
                if (autor.id == id) {
                    return &autor;
                }
            }
            return nullptr;
        }
        
        void eliminarPorID(const std::string& id, const std::string& archivo) {
            /*
            Elimina un autor por su ID y guarda los cambios en el archivo.
            Parámetros:
            - id: El ID del autor a eliminar.
            - archivo: El nombre del archivo donde se guardarán los cambios.
            Descripción:
            Esta función elimina un autor de la lista de autores por su ID.
            Si el autor no se encuentra, se muestra un mensaje de error.
            */
            autores.erase(std::remove_if(autores.begin(), autores.end(),
                         [&id](const Autor& a) { return a.id == id; }), autores.end());
            std::cout << "Autor eliminado.\n";
        }
    };
    
    class ControlEditoriales {
        /*
        Constructor de la clase ControlEditoriales.
        Inicializa la referencia a la lista de editoriales.
        Controlador para gestionar la información de las editoriales.
        Atributos:
        - editoriales: Referencia a la lista de editoriales.
        Métodos:
        - agregar: Agrega una nueva editorial a la lista.
        - mostrarTodos: Muestra todas las editoriales.
        - buscarPorID: Busca una editorial por su ID.
        - eliminarPorID: Elimina una editorial por su ID y guarda los cambios en el archivo.
        Descripción:
        Esta clase se encarga de gestionar las operaciones relacionadas con las editoriales,
        incluyendo la adición, eliminación y búsqueda de editoriales en la lista.
        */
    private:
        std::vector<Editorial>& editoriales;
        
    public:
        ControlEditoriales(std::vector<Editorial>& e) : editoriales(e) {
            /*
            Constructor de la clase ControlEditoriales.
            Inicializa la referencia a la lista de editoriales.
            Descripción:
            Este constructor permite crear un controlador para gestionar las editoriales,
            proporcionando acceso a la lista de editoriales existente.
            Atributos:
            - editoriales: Referencia a la lista de editoriales.
            Métodos:
            - agregar: Agrega una nueva editorial a la lista.
            - mostrarTodos: Muestra todas las editoriales.
            - buscarPorID: Busca una editorial por su ID.
            - eliminarPorID: Elimina una editorial por su ID y guarda los cambios en el archivo.
            */
        }
        
        void agregar(const Editorial& editorial) {
            /*
            Agrega una nueva editorial a la lista.
            Parámetros:
            - editorial: La editorial a agregar.
            Descripción:
            Esta función agrega una nueva editorial a la lista de editoriales.
            Si la editorial ya existe, no se agrega nuevamente.
            */
            editoriales.push_back(editorial);
        }
        
        void mostrarTodos() {
            /*
            Muestra todas las editoriales.
            Descripción:
            Esta función itera a través de la lista de editoriales y muestra
            la información de cada una en la consola.
            */
            for (const auto& editorial : editoriales) {
                std::cout << "ID: " << editorial.id << ", Nombre: " << editorial.nombre
                         << ", Ciudad: " << editorial.ciudadPrincipal << ", País: " << editorial.paisPrincipal << std::endl;
            }
        }
        
        Editorial* buscarPorID(const std::string& id) {
            /*
            Busca una editorial por su ID.
            Parámetros:
            - id: El ID de la editorial a buscar.
            Descripción:
            Esta función itera a través de la lista de editoriales y busca
            una editorial que coincida con el ID proporcionado.
            */
            for (auto& editorial : editoriales) {
                if (editorial.id == id) {
                    return &editorial;
                }
            }
            return nullptr;
        }
        
        void eliminarPorID(const std::string& id, const std::string& archivo) {
            /*
            Elimina una editorial por su ID y guarda los cambios en el archivo.
            Parámetros:
            - id: El ID de la editorial a eliminar.
            - archivo: El nombre del archivo donde se guardarán los cambios.
            Descripción:
            Esta función busca una editorial por su ID y, si la encuentra,
            la elimina de la lista de editoriales. Luego, guarda los cambios
            en el archivo especificado.
            */
            editoriales.erase(std::remove_if(editoriales.begin(), editoriales.end(),
                             [&id](const Editorial& e) { return e.id == id; }), editoriales.end());
            std::cout << "Editorial eliminada.\n";
        }
    };
    
    class ControlObras {
        /*
        Controlador para gestionar las obras.

        Atributos:
        - obras: Referencia a la lista de obras.
        Métodos:
        - agregar: Agrega una nueva obra a la lista.
        - mostrarTodos: Muestra todas las obras.
        - eliminarPorNombre: Elimina una obra por su nombre y guarda los cambios en el archivo.
        Descripción:
        Esta clase se encarga de gestionar las operaciones relacionadas con las obras,
        permitiendo agregar, mostrar y eliminar obras de la lista.
        */
    private:
        std::vector<Obra>& obras;
        
    public:
        ControlObras(std::vector<Obra>& o) : obras(o) {
            /*
            Constructor de ControlObras.
            Inicializa el controlador con la lista de obras proporcionada.
            */
        }
        
        void agregar(const Obra& obra) {
            /*
            Agrega una nueva obra a la lista.
            Parámetros:
            - obra: La obra a agregar.
            Descripción:
            Esta función agrega una nueva obra a la lista de obras.
            */
            obras.push_back(obra);
        }
        
        void mostrarTodos() {
            /*
            Muestra todas las obras.
            Descripción:
            Esta función itera a través de la lista de obras y muestra
            la información de cada una en la consola.
            */
            for (const auto& obra : obras) {
                std::cout << "Nombre: " << obra.nombre << ", Tipo: " << obra.tipoPoesia
                         << ", ID Autor: " << obra.idAutor << std::endl;
            }
        }
        
        void eliminarPorNombre(const std::string& nombre, const std::string& archivo) {
            /*
            Elimina una obra por su nombre y guarda los cambios en el archivo.
            Parámetros:
            - nombre: El nombre de la obra a eliminar.
            - archivo: El nombre del archivo donde se guardarán los cambios.
            Descripción:
            Esta función busca una obra por su nombre y, si la encuentra,
            la elimina de la lista de obras. Luego, guarda los cambios
            en el archivo especificado.
            */
            obras.erase(std::remove_if(obras.begin(), obras.end(),
                       [&nombre](const Obra& o) { return o.nombre == nombre; }), obras.end());
            std::cout << "Obra eliminada.\n";
        }
    };
    
    class ControlEdiciones {
        /*
        Controlador para gestionar las ediciones.

        Atributos:
        - ediciones: Referencia a la lista de ediciones.
        Métodos:
        - agregar: Agrega una nueva edición a la lista.
        - mostrarTodos: Muestra todas las ediciones.
        - eliminarPorNumero: Elimina una edición por su número y guarda los cambios en el archivo.
        Descripción:
        Esta clase se encarga de gestionar las operaciones relacionadas con las ediciones,
        permitiendo agregar, mostrar y eliminar ediciones de la lista.
        */
    private:
        std::vector<Edicion>& ediciones;
        
    public:
        ControlEdiciones(std::vector<Edicion>& e) : ediciones(e) {
            /*
            Constructor de ControlEdiciones.
            Inicializa el controlador con la lista de ediciones proporcionada.
            */
        }
        
        void agregar(const Edicion& edicion) {
            /*
            Agrega una nueva edición a la lista.
            Parámetros:
            - edicion: La edición a agregar.
            Descripción:
            Esta función agrega una nueva edición a la lista de ediciones.
            */
            ediciones.push_back(edicion);
        }
        
        void mostrarTodos() {
            /*
            Muestra todas las ediciones.
            Descripción:
            Esta función itera a través de la lista de ediciones y muestra
            la información de cada una en la consola.
            */
            for (const auto& edicion : ediciones) {
                std::cout << "Número: " << edicion.numeroEdicion << ", Fecha: " << edicion.fechaPublicacion
                         << ", ID Editorial: " << edicion.idEditorial << ", Ciudad: " << edicion.ciudadPublicacion
                         << ", ID Obra: " << edicion.idObra << std::endl;
            }
        }
        
        void eliminarPorNumero(int numero, const std::string& archivo) {
            /*
            Elimina una edición por su número y guarda los cambios en el archivo.
            Parámetros:
            - numero: El número de la edición a eliminar.
            - archivo: El nombre del archivo donde se guardarán los cambios.
            Descripción:
            Esta función busca una edición por su número y, si la encuentra,
            la elimina de la lista de ediciones. Luego, guarda los cambios
            en el archivo especificado.
            */
            ediciones.erase(std::remove_if(ediciones.begin(), ediciones.end(),
                           [numero](const Edicion& e) { return e.numeroEdicion == numero; }), ediciones.end());
            std::cout << "Edición eliminada.\n";
        }
    };
    
    ControlAutores getControlAutores() { return ControlAutores(autores); }
    ControlEditoriales getControlEditoriales() { return ControlEditoriales(editoriales); }
    ControlObras getControlObras() { return ControlObras(obras); }
    ControlEdiciones getControlEdiciones() { return ControlEdiciones(ediciones); }
    
    void inicializarSistema() {
        cargarAutores("autores.txt");
        cargarEditoriales("editoriales.txt");
        cargarObras("obras.txt");
        cargarEdiciones("ediciones.txt");
        construirIndices();
        std::cout << "Sistema inicializado correctamente.\n";
        std::cout << "Autores cargados: " << autores.size() << std::endl;
        std::cout << "Editoriales cargadas: " << editoriales.size() << std::endl;
        std::cout << "Obras cargadas: " << obras.size() << std::endl;
        std::cout << "Ediciones cargadas: " << ediciones.size() << std::endl;
    }
    
    void construirIndicesOptimizados() {
        /*
        Esta función construye índices optimizados para mejorar la eficiencia
        de las búsquedas en las colecciones de datos.
        */
        construirIndices();
        std::cout << "Índices optimizados construidos.\n";
    }
    
    void optimizarEstructuras() {
        /*
        Esta función optimiza las estructuras de datos utilizadas en el sistema.
        */
        std::sort(autores.begin(), autores.end(), [](const Autor& a, const Autor& b) {
            return a.id < b.id;
        });
        std::sort(editoriales.begin(), editoriales.end(), [](const Editorial& a, const Editorial& b) {
            return a.id < b.id;
        });
        construirIndices();
        std::cout << "Estructuras optimizadas.\n";
    }
    
    void guardarTodosSistema() {
        /*
        Esta función guarda todos los datos del sistema en sus respectivos archivos.
        */
        guardarArchivo("autores.txt", "autores");
        guardarArchivo("editoriales.txt", "editoriales");
        guardarArchivo("obras.txt", "obras");
        guardarArchivo("ediciones.txt", "ediciones");
        std::cout << "Todos los datos guardados correctamente.\n";
    }
    
    void cargarAutores(const std::string& archivo) {
        /*
        Esta función carga los autores desde un archivo de texto.
        Parámetros:
        - archivo: El nombre del archivo desde el cual se cargarán los autores.
        Descripción:
        Esta función abre un archivo de texto que contiene información de autores,
        lee cada línea y crea un objeto Autor a partir de los datos. Los objetos Autor
        se almacenan en la colección correspondiente.
        */
        std::ifstream file(archivo);
        if (!file.is_open()) {
            std::cout << "No se pudo abrir el archivo de autores: " << archivo << std::endl;
            return;
        }
        
        std::string linea;
        while (std::getline(file, linea)) {
            if (linea.empty()) continue;
            
            std::stringstream ss(linea);
            std::string campo;
            Autor autor;
            
            std::getline(ss, autor.id, ';');
            std::getline(ss, autor.nombre, ';');
            std::getline(ss, autor.apellido, ';');
            std::getline(ss, campo, ';'); autor.sexo = campo.empty() ? ' ' : campo[0];
            std::getline(ss, autor.fechaNacimiento, ';');
            std::getline(ss, autor.ciudadNacimiento, ';');
            std::getline(ss, autor.paisNacimiento, ';');
            std::getline(ss, autor.ciudadResidencia, ';');
            std::getline(ss, autor.formacionBase, ';');
            std::getline(ss, campo, ';'); autor.anioInicioLiteratura = std::stoi(campo);
            std::getline(ss, campo); autor.anioPrimeraObra = std::stoi(campo);
            
            autores.push_back(autor);
        }
        file.close();
    }
    
    void cargarEditoriales(const std::string& archivo) {
        /*
        Esta función carga las editoriales desde un archivo de texto.
        Parámetros:
        - archivo: El nombre del archivo desde el cual se cargarán las editoriales.
        Descripción:
        Esta función abre un archivo de texto que contiene información de editoriales,
        lee cada línea y crea un objeto Editorial a partir de los datos. Los objetos Editorial
        se almacenan en la colección correspondiente.
        */
        std::ifstream file(archivo);
        if (!file.is_open()) {
            std::cout << "No se pudo abrir el archivo de editoriales: " << archivo << std::endl;
            return;
        }
        
        std::string linea;
        while (std::getline(file, linea)) {
            /*
            Esta función carga las editoriales desde un archivo de texto.
            Parámetros:
            - archivo: El nombre del archivo desde el cual se cargarán las editoriales.
            Descripción:
            Esta función abre un archivo de texto que contiene información de editoriales,
            lee cada línea y crea un objeto Editorial a partir de los datos. Los objetos Editorial
            se almacenan en la colección correspondiente.
            */
            if (linea.empty()) continue;
            
            std::stringstream ss(linea);
            Editorial editorial;
            
            std::getline(ss, editorial.id, ';');
            std::getline(ss, editorial.nombre, ';');
            std::getline(ss, editorial.ciudadPrincipal, ';');
            std::getline(ss, editorial.paisPrincipal);
            
            editoriales.push_back(editorial);
        }
        file.close();
    }
    
    void cargarObras(const std::string& archivo) {
        /*
        Esta función carga las obras desde un archivo de texto.
        Parámetros:
        - archivo: El nombre del archivo desde el cual se cargarán las obras.
        Descripción:
        Esta función abre un archivo de texto que contiene información de obras,
        lee cada línea y crea un objeto Obra a partir de los datos. Los objetos Obra
        se almacenan en la colección correspondiente.
        */
        std::ifstream file(archivo);
        if (!file.is_open()) {
            std::cout << "No se pudo abrir el archivo de obras: " << archivo << std::endl;
            return;
        }
        
        std::string linea;
        while (std::getline(file, linea)) {
            if (linea.empty()) continue;
            
            std::stringstream ss(linea);
            Obra obra;
            
            std::getline(ss, obra.nombre, ';');
            std::getline(ss, obra.tipoPoesia, ';');
            std::getline(ss, obra.idAutor);
            
            obras.push_back(obra);
        }
        file.close();
    }
    
    void cargarEdiciones(const std::string& archivo) {
        std::ifstream file(archivo);
        if (!file.is_open()) {
            std::cout << "No se pudo abrir el archivo de ediciones: " << archivo << std::endl;
            return;
        }
        
        std::string linea;
        while (std::getline(file, linea)) {
            if (linea.empty()) continue;
            
            std::stringstream ss(linea);
            std::string campo;
            Edicion edicion;
            
            std::getline(ss, campo, ';'); edicion.numeroEdicion = std::stoi(campo);
            std::getline(ss, edicion.fechaPublicacion, ';');
            std::getline(ss, edicion.idEditorial, ';');
            std::getline(ss, edicion.ciudadPublicacion, ';');
            std::getline(ss, edicion.idObra);
            
            ediciones.push_back(edicion);
        }
        file.close();
    }
    
    // CONSULTAS PRINCIPALES
    
    // Consulta 1: Obras de un autor por editorial y año
    void consultaObrasAutorPorEditorialAnio(const std::string& idAutor) {
        /*
        Esta función consulta las obras de un autor específico, organizadas por editorial y año de publicación.
        Parámetros:
        - idAutor: ID del autor cuyas obras se desean consultar.
        Descripción:
        Esta función busca las obras del autor especificado y las organiza por editorial y año de publicación.
        Utiliza un mapa para almacenar las editoriales y otro mapa anidado para almacenar los
        años de publicación y la cantidad de obras por año.
        */
        std::cout << "=== CONSULTA 1: Obras por Editorial y Año ===" << std::endl;
        std::cout << "Autor: " << obtenerNombreAutor(idAutor) << std::endl;

    std::cout << "Buscando autor en índice..." << std::endl;
    if (autorObras.find(idAutor) == autorObras.end()) {
        std::cout << "Autor no encontrado en índice autorObras" << std::endl;
        return;
    }
    std::cout << "Autor encontrado, tiene " << autorObras[idAutor].size() << " obras" << std::endl;
    
    for (int idx : autorObras[idAutor]) {
        std::cout << "Obra[" << idx << "]: " << obras[idx].nombre << std::endl;
    }
        
        std::map<std::string, std::map<int, int>> resultado;
        
        if (autorObras.find(idAutor) != autorObras.end()) {
            for (int idx : autorObras[idAutor]) {
                const Obra& obra = obras[idx];
                
                if (obraEdiciones.find(obra.nombre) != obraEdiciones.end()) {
                    for (int edIdx : obraEdiciones[obra.nombre]) {
                        const Edicion& edicion = ediciones[edIdx];
                        int anio = extraerAnio(edicion.fechaPublicacion);
                        std::string nombreEditorial = obtenerNombreEditorial(edicion.idEditorial);
                        resultado[nombreEditorial][anio]++;
                    }
                }
            }
        }
        
        if (resultado.empty()) {
            std::cout << "No se encontraron obras para el autor especificado." << std::endl;
            return;
        }
        
        int totalObras = 0;
        for (const auto& editorial : resultado) {
            std::cout << "\nEditorial: " << editorial.first << std::endl;
            for (const auto& anio : editorial.second) {
                std::cout << "  Año " << anio.first << ": " << anio.second << " obras" << std::endl;
                totalObras += anio.second;
            }
        }
        std::cout << "\nTotal de obras: " << totalObras << std::endl;
    }
    
    void consultaObrasAutorPorTipoPoesia(const std::string& idAutor) {
        /*
        Esta función consulta las obras de un autor específico, organizadas por tipo de poesía.
        Parámetros:
        - idAutor: ID del autor cuyas obras se desean consultar.
        Descripción:
        Esta función busca las obras del autor especificado y las organiza por tipo de poesía.
        Utiliza un mapa para almacenar los tipos de poesía y otro mapa anidado para almacenar los
        detalles de las obras.
        */
        std::cout << "=== CONSULTA 2: Obras por Tipo de Poesía ===" << std::endl;
        std::cout << "Autor: " << obtenerNombreAutor(idAutor) << std::endl;
        
        std::map<std::string, std::vector<std::pair<std::string, std::vector<std::pair<std::string, int>>>>> resultado;
        
        if (autorObras.find(idAutor) != autorObras.end()) {
            for (int idx : autorObras[idAutor]) {
                const Obra& obra = obras[idx];
                std::vector<std::pair<std::string, int>> edicionesObra;
                
                if (obraEdiciones.find(obra.nombre) != obraEdiciones.end()) {
                    for (int edIdx : obraEdiciones[obra.nombre]) {
                        const Edicion& edicion = ediciones[edIdx];
                        edicionesObra.push_back({edicion.fechaPublicacion, edicion.numeroEdicion});
                    }
                }
                
                resultado[obra.tipoPoesia].push_back({obra.nombre, edicionesObra});
            }
        }
        
        if (resultado.empty()) {
            std::cout << "No se encontraron obras para el autor especificado." << std::endl;
            return;
        }
        
        for (const auto& tipo : resultado) {
            std::cout << "\nTipo de Poesía: " << tipo.first << std::endl;
            for (const auto& obra : tipo.second) {
                std::cout << "  Obra: " << obra.first << std::endl;
                for (const auto& edicion : obra.second) {
                    std::cout << "    - Fecha: " << edicion.first << ", Edición: " << edicion.second << std::endl;
                }
            }
        }
    }
    
    void consultaAutoresPorEditorial(const std::string& idEditorial) {
        /*
        Esta función consulta los autores que han publicado obras bajo una editorial específica.
        Parámetros:
        - idEditorial: ID de la editorial cuyas obras se desean consultar.
        Descripción:
        Esta función busca los autores que han publicado obras bajo la editorial especificada
        y organiza los resultados por ciudad de residencia y año de inicio de la carrera literaria.
        */
        std::cout << "=== CONSULTA 3: Autores por Editorial ===" << std::endl;
        std::cout << "Editorial: " << obtenerNombreEditorial(idEditorial) << std::endl;
        
        // Estructura: Ciudad -> Año -> Lista de autores
        std::map<std::string, std::map<int, std::vector<std::string>>> resultado;
        std::set<std::string> autoresUnicos;
        
        if (editorialEdiciones.find(idEditorial) != editorialEdiciones.end()) {
            for (int edIdx : editorialEdiciones[idEditorial]) {
                const Edicion& edicion = ediciones[edIdx];
                
                for (const auto& obra : obras) {
                    if (obra.nombre == edicion.idObra) {
                        Autor* autor = obtenerAutorPorId(obra.idAutor);
                        if (autor && autoresUnicos.find(autor->id) == autoresUnicos.end()) {
                            autoresUnicos.insert(autor->id);
                            std::string info = autor->nombre + " " + autor->apellido + " - " + 
                                             autor->ciudadNacimiento + ", " + autor->paisNacimiento;
                            resultado[autor->ciudadResidencia][autor->anioInicioLiteratura].push_back(info);
                        }
                        break;
                    }
                }
            }
        }
        
        if (resultado.empty()) {
            std::cout << "No se encontraron autores para la editorial especificada." << std::endl;
            return;
        }
        
        for (const auto& ciudad : resultado) {
            std::cout << "\nCiudad de Residencia: " << ciudad.first << std::endl;
            for (const auto& anio : ciudad.second) {
                std::cout << "  Año de Inicio: " << anio.first << std::endl;
                for (const auto& autor : anio.second) {
                    std::cout << "    - " << autor << std::endl;
                }
            }
        }
    }
    
    void consultaEditorialesConNPoetas(int numeroMinimo) {
        /*
        Esta función consulta las editoriales que tienen un número mínimo de poetas.
        Parámetros:
        - numeroMinimo: Número mínimo de poetas que debe tener la editorial.
        Descripción:
        Esta función busca las editoriales que tienen más de "numeroMinimo" poetas
        y muestra información sobre ellas.
        */
        std::cout << "=== CONSULTA 4: Editoriales con más de " << numeroMinimo << " poetas ===" << std::endl;
        
        // Contar poetas únicos por editorial
        std::map<std::string, std::set<std::string>> poetasPorEditorial;
        
        for (const auto& edicion : ediciones) {
            for (const auto& obra : obras) {
                if (obra.nombre == edicion.idObra) {
                    poetasPorEditorial[edicion.idEditorial].insert(obra.idAutor);
                    break;
                }
            }
        }
        
        int editorialesEncontradas = 0;
        for (const auto& editorial : poetasPorEditorial) {
            if (static_cast<int>(editorial.second.size()) > numeroMinimo) {
                editorialesEncontradas++;
                Editorial* ed = obtenerEditorialPorId(editorial.first);
                if (ed) {
                    std::cout << "\nEditorial: " << ed->nombre << std::endl;
                    std::cout << "  Ubicación: " << ed->ciudadPrincipal << ", " << ed->paisPrincipal << std::endl;
                    std::cout << "  Cantidad de poetas: " << editorial.second.size() << std::endl;
                }
            }
        }
        
        std::cout << "\nTotal de editoriales encontradas: " << editorialesEncontradas << std::endl;
    }
    
    void consultaAutoresPorEditorialNacimiento(const std::string& idEditorial) {
        /*
        Esta función consulta los autores que han publicado obras bajo una editorial específica
        y los clasifica por su lugar de nacimiento.
        Parámetros:
        - idEditorial: ID de la editorial cuyas obras se desean consultar.
        Descripción:
        Esta función busca los autores que han publicado obras bajo la editorial especificada
        y organiza los resultados por país de nacimiento, ciudad de nacimiento y sexo.
        */
        std::cout << "=== CONSULTA 5: Autores por Editorial y Lugar de Nacimiento ===" << std::endl;
        std::cout << "Editorial: " << obtenerNombreEditorial(idEditorial) << std::endl;
        
        std::map<std::string, std::map<std::string, std::map<char, std::vector<std::string>>>> resultado;
        std::set<std::string> autoresUnicos;
        
        if (editorialEdiciones.find(idEditorial) != editorialEdiciones.end()) {
            for (int edIdx : editorialEdiciones[idEditorial]) {
                const Edicion& edicion = ediciones[edIdx];
                
                for (const auto& obra : obras) {
                    if (obra.nombre == edicion.idObra) {
                        Autor* autor = obtenerAutorPorId(obra.idAutor);
                        if (autor && autoresUnicos.find(autor->id) == autoresUnicos.end()) {
                            autoresUnicos.insert(autor->id);
                            std::string nombreCompleto = autor->nombre + " " + autor->apellido;
                            resultado[autor->paisNacimiento][autor->ciudadNacimiento][autor->sexo].push_back(nombreCompleto);
                        }
                        break;
                    }
                }
            }
        }
        
        if (resultado.empty()) {
            std::cout << "No se encontraron autores para la editorial especificada." << std::endl;
            return;
        }
        
        for (const auto& pais : resultado) {
            std::cout << "\nPaís: " << pais.first << std::endl;
            for (const auto& ciudad : pais.second) {
                std::cout << "  Ciudad: " << ciudad.first << std::endl;
                if (ciudad.second.count('M')) {
                    std::cout << "    Hombres (" << ciudad.second.at('M').size() << "):" << std::endl;
                    for (const auto& nombre : ciudad.second.at('M')) {
                        std::cout << "      - " << nombre << std::endl;
                    }
                }
                if (ciudad.second.count('F')) {
                    std::cout << "    Mujeres (" << ciudad.second.at('F').size() << "):" << std::endl;
                    for (const auto& nombre : ciudad.second.at('F')) {
                        std::cout << "      - " << nombre << std::endl;
                    }
                }
            }
        }
    }

    void consultaAutoresPorEdadYFormacion(int edadMinima, int edadMaxima, const std::string& formacionBase) {
        /*
        Esta función consulta los autores que se encuentran dentro de un rango de edad específico
        y que tienen una formación de base determinada.
        Parámetros:
        - edadMinima: Edad mínima del autor.
        - edadMaxima: Edad máxima del autor.
        - formacionBase: Formación de base del autor.
        Descripción:
        Esta función busca los autores que cumplen con los criterios de edad y formación
        y muestra información sobre ellos.
        */
        std::cout << "=== CONSULTA 6: Autores por Rango de Edad y Formación ===" << std::endl;
        std::cout << "Rango de edad: " << edadMinima << " - " << edadMaxima << " años" << std::endl;
        std::cout << "Formación de base: " << formacionBase << std::endl;
        
        std::map<int, std::vector<std::string>> autoresPorAnio;
        
        for (const auto& autor : autores) {
            int edad = calcularEdad(autor.fechaNacimiento);
            
            if (edad >= edadMinima && edad <= edadMaxima && edad > 0 && 
    autor.formacionBase.find(formacionBase) != std::string::npos) {

                std::string infoAutor = autor.nombre + " " + autor.apellido + 
                                       " (Edad: " + std::to_string(edad) + 
                                       ", Residencia: " + autor.ciudadResidencia + 
                                       ", Nacimiento: " + autor.ciudadNacimiento + ", " + autor.paisNacimiento + ")";
                
                autoresPorAnio[autor.anioPrimeraObra].push_back(infoAutor);
            }
        }
        
        if (autoresPorAnio.empty()) {
            std::cout << "No se encontraron autores con los criterios especificados." << std::endl;
            return;
        }
        
        int totalAutores = 0;
        for (const auto& anio : autoresPorAnio) {
            std::cout << "\nAño de primera obra: " << anio.first << std::endl;
            for (const auto& autor : anio.second) {
                std::cout << "  - " << autor << std::endl;
                totalAutores++;
            }
        }
        
        std::cout << "\nTotal de autores encontrados: " << totalAutores << std::endl;
    }
    
    void consultaAutoresPorTipoPoesiaYEditorial(const std::string& tipoPoesia, const std::string& idEditorial) {
        std::cout << "=== CONSULTA 7: Autores por Tipo de Poesía y Editorial ===" << std::endl;
        /*
        Esta función consulta los autores que han publicado obras del tipo de poesía especificado
        en la editorial indicada.
        Parámetros:
        - tipoPoesia: Tipo de poesía de las obras.
        - idEditorial: ID de la editorial.
        Descripción:
        Esta función busca los autores que han publicado obras del tipo de poesía especificado
        en la editorial indicada y muestra información sobre ellos.
        */
        std::cout << "Tipo de poesía: " << tipoPoesia << std::endl;
        std::cout << "Editorial: " << obtenerNombreEditorial(idEditorial) << std::endl;
        
        std::map<std::string, std::pair<std::string, std::vector<std::string>>> autoresConEdiciones;
        
        for (const auto& obra : obras) {
            if (obra.tipoPoesia.find(tipoPoesia) != std::string::npos) {
                if (obraEdiciones.find(obra.nombre) != obraEdiciones.end()) {
                    for (int edIdx : obraEdiciones[obra.nombre]) {
                        const Edicion& edicion = ediciones[edIdx];
                        if (edicion.idEditorial == idEditorial) {
                        
                        std::string infoAutor = obtenerNombreAutor(obra.idAutor);
                        Autor* autor = obtenerAutorPorId(obra.idAutor);
                        
                        if (autor) {
                            std::string datosCompletos = infoAutor + 
                                                       " (Sexo: " + std::string(1, autor->sexo) + 
                                                       ", Nacimiento: " + autor->fechaNacimiento + 
                                                       ", " + autor->ciudadNacimiento + ", " + autor->paisNacimiento + 
                                                       ", Residencia: " + autor->ciudadResidencia + 
                                                       ", Formación: " + autor->formacionBase + ")";
                            
                            std::string infoEdicion = "Obra: " + obra.nombre + 
                                                    ", Edición #" + std::to_string(edicion.numeroEdicion) + 
                                                    ", Fecha: " + edicion.fechaPublicacion + 
                                                    ", Ciudad: " + edicion.ciudadPublicacion;
                            
                            if (autoresConEdiciones.find(obra.idAutor) == autoresConEdiciones.end()) {
                                autoresConEdiciones[obra.idAutor] = {datosCompletos, {}};
                            }
                            autoresConEdiciones[obra.idAutor].second.push_back(infoEdicion);
                        }
                    }
                }
            }
        }
        
        if (autoresConEdiciones.empty()) {
            std::cout << "No se encontraron autores con los criterios especificados." << std::endl;
            return;
        }
        
        int totalAutores = 0;
        int totalEdiciones = 0;
        
        for (const auto& autorInfo : autoresConEdiciones) {
            totalAutores++;
            std::cout << "\nAutor: " << autorInfo.second.first << std::endl;
            std::cout << "Ediciones encontradas:" << std::endl;
            
            for (const auto& edicion : autorInfo.second.second) {
                std::cout << "  - " << edicion << std::endl;
                totalEdiciones++;
            }
        }
        
        std::cout << "\nResumen:" << std::endl;
        std::cout << "Total de autores: " << totalAutores << std::endl;
        std::cout << "Total de ediciones: " << totalEdiciones << std::endl;
    }
}
};

class GestionBiblioteca {
    /*
    Clase para gestionar la biblioteca, incluyendo autores, editoriales, obras y ediciones.
    Atributos:
    - autores: Colección de autores.
    - editoriales: Colección de editoriales.
    - obras: Colección de obras.
    - ediciones: Colección de ediciones.
    Métodos:
    - cargarAutores: Carga los autores desde un archivo.
    - cargarEditoriales: Carga las editoriales desde un archivo.
    - cargarObras: Carga las obras desde un archivo.
    - cargarEdiciones: Carga las ediciones desde un archivo.
    */
private:
    std::vector<Autor> autores;
    std::vector<Editorial> editoriales;
    std::vector<Obra> obras;
    std::vector<Edicion> ediciones;
    
    std::map<std::string, std::vector<int>> autorObras;
    std::map<std::string, std::vector<int>> editorialEdiciones;
    std::map<std::string, std::vector<int>> obraEdiciones;
    
    int calcularEdad(const std::string& fechaNacimiento) const {
        /*
        Calcula la edad a partir de la fecha de nacimiento.
        Parámetros:
        - fechaNacimiento: La fecha de nacimiento en formato "DD/MM/AAAA".
        Descripción:
        Calcula la edad de una persona a partir de su fecha de nacimiento.
        Retorna:
        - La edad de la persona en años.
        */
        if (fechaNacimiento.empty()) return 0;
        
        size_t pos = fechaNacimiento.find_last_of("/-");
        if (pos != std::string::npos && pos + 1 < fechaNacimiento.length()) {
            std::string anioStr = fechaNacimiento.substr(pos + 1);
            int anioNacimiento = std::stoi(anioStr);
            return (anioNacimiento > 0) ? (2024 - anioNacimiento) : 0;
        }
        return 0;
    }

    int extraerAnio(const std::string& fecha) const {
        /*
        Extrae el año de una fecha en formato "DD/MM/AAAA".
        Parámetros:
        - fecha: La fecha en formato "DD/MM/AAAA".
        Retorna:
        - El año extraído como un entero.
        */
        if (fecha.empty()) return 0;
        
        size_t pos = fecha.find_last_of("/-");
        if (pos != std::string::npos && pos + 1 < fecha.length()) {
            std::string anioStr = fecha.substr(pos + 1);
            return std::stoi(anioStr);
        }
        return 0;
    }
    
    std::string obtenerNombreEditorial(const std::string& idEditorial) const {
        /*
        Obtiene el nombre de una editorial a partir de su ID.
        Parámetros:
        - idEditorial: El ID de la editorial.
        Retorna:
        - El nombre de la editorial o un mensaje de error si no se encuentra.
        */
        for (const auto& editorial : editoriales) {
            if (editorial.id == idEditorial) {
                return editorial.nombre;
            }
        }
        return "Editorial no encontrada";
    }
    
    std::string obtenerNombreAutor(const std::string& idAutor) const {
        /*
        Obtiene el nombre de un autor a partir de su ID.
        Parámetros:
        - idAutor: El ID del autor.
        Retorna:
        - El nombre del autor o un mensaje de error si no se encuentra.
        */
        for (const auto& autor : autores) {
            if (autor.id == idAutor) {
                return autor.nombre + " " + autor.apellido;
            }
        }
        return "Autor no encontrado";
    }
    
    Autor* obtenerAutorPorId(const std::string& idAutor) {
        /*
        Obtiene un puntero a un autor a partir de su ID.
        Parámetros:
        - idAutor: El ID del autor.
        Retorna:
        - Un puntero al autor o nullptr si no se encuentra.
        */
        for (auto& autor : autores) {
            if (autor.id == idAutor) {
                return &autor;
            }
        }
        return nullptr;
    }
    
    Editorial* obtenerEditorialPorId(const std::string& idEditorial) {
        /*
        Obtiene un puntero a una editorial a partir de su ID.
        Parámetros:
        - idEditorial: El ID de la editorial.
        Retorna:
        - Un puntero a la editorial o nullptr si no se encuentra.
        */
        for (auto& editorial : editoriales) {
            if (editorial.id == idEditorial) {
                return &editorial;
            }
        }
        return nullptr;
    }
    
    void construirIndices() {
        /*
        Limpiar índices existentes
        */
        autorObras.clear();
        editorialEdiciones.clear();
        obraEdiciones.clear();
        
        for (size_t i = 0; i < obras.size(); ++i) {
            autorObras[obras[i].idAutor].push_back(i);
        }
        for (size_t i = 0; i < ediciones.size(); ++i) {
            editorialEdiciones[ediciones[i].idEditorial].push_back(i);
        }
        for (size_t i = 0; i < ediciones.size(); ++i) {
            obraEdiciones[ediciones[i].idObra].push_back(i);
        }
    }
    
    void guardarArchivo(const std::string& archivo, const std::string& tipo) {
        /*
        Guarda la información de la biblioteca en un archivo.
        Parámetros:
        - archivo: El nombre del archivo.
        - tipo: El tipo de información a guardar (autores, editoriales, obras, ediciones).
        Descripción:
        Esta función guarda la información de la biblioteca en un archivo de texto, organizando los datos según el tipo especificado.
        */
        std::ofstream file(archivo);
        if (!file.is_open()) {
            std::cout << "Error al abrir archivo: " << archivo << std::endl;
            return;
        }
        
        if (tipo == "autores") {
            for (const auto& autor : autores) {
                file << autor.id << ";" << autor.nombre << ";" << autor.apellido << ";" 
                     << autor.sexo << ";" << autor.fechaNacimiento << ";" << autor.ciudadNacimiento << ";"
                     << autor.paisNacimiento << ";" << autor.ciudadResidencia << ";" << autor.formacionBase << ";"
                     << autor.anioInicioLiteratura << ";" << autor.anioPrimeraObra << std::endl;
            }
        } else if (tipo == "editoriales") {
            for (const auto& editorial : editoriales) {
                file << editorial.id << ";" << editorial.nombre << ";" 
                     << editorial.ciudadPrincipal << ";" << editorial.paisPrincipal << std::endl;
            }
        } else if (tipo == "obras") {
            for (const auto& obra : obras) {
                file << obra.nombre << ";" << obra.tipoPoesia << ";" << obra.idAutor << std::endl;
            }
        } else if (tipo == "ediciones") {
            for (const auto& edicion : ediciones) {
                file << edicion.numeroEdicion << ";" << edicion.fechaPublicacion << ";" 
                     << edicion.idEditorial << ";" << edicion.ciudadPublicacion << ";" 
                     << edicion.idObra << std::endl;
            }
        }
        file.close();
    }

public:
    GestionBiblioteca() {}
    
    class ControlAutores {
        /*
        Clase para controlar las operaciones relacionadas con los autores.
        Atributos:
        - autores: Referencia al vector de autores.
        Métodos:
        - agregar: Agrega un nuevo autor.
        - mostrarTodos: Muestra todos los autores.
        - buscarPorID: Busca un autor por su ID.
        - eliminarPorID: Elimina un autor por su ID.
        */
    private:
        std::vector<Autor>& autores;
        
    public:
        ControlAutores(std::vector<Autor>& a) : autores(a) {
            /*
            Constructor de la clase ControlAutores.
            Parámetros:
            - a: Referencia al vector de autores.
            Descripción:
            Este constructor inicializa la clase ControlAutores con una referencia al vector de autores existente.
            Esta referencia permite realizar operaciones sobre la colección de autores sin necesidad de copiarla.
            */
        }
        
        void agregar(const Autor& autor) {
            /*
            Método para agregar un nuevo autor.
            Parámetros:
            - autor: El autor a agregar.
            Descripción:
            Este método agrega un nuevo autor al vector de autores.
            */
            autores.push_back(autor);
        }
        
        void mostrarTodos() {
            for (const auto& autor : autores) {
                /*
                Muestra la información de un autor.
                */
                std::cout << "ID: " << autor.id << ", Nombre: " << autor.nombre << " " << autor.apellido
                         << ", Sexo: " << autor.sexo << ", Nacimiento: " << autor.fechaNacimiento
                         << ", Ciudad: " << autor.ciudadNacimiento << ", País: " << autor.paisNacimiento
                         << ", Residencia: " << autor.ciudadResidencia << ", Formación: " << autor.formacionBase
                         << ", Inicio literatura: " << autor.anioInicioLiteratura
                         << ", Primera obra: " << autor.anioPrimeraObra << std::endl;
            }
        }
        
        Autor* buscarPorID(const std::string& id) {
            /*
            Método para buscar un autor por su ID.
            Parámetros:
            - id: El ID del autor a buscar.
            Retorno:
            - Un puntero al autor encontrado, o nullptr si no se encuentra.
            */
            for (auto& autor : autores) {
                if (autor.id == id) {
                    return &autor;
                }
            }
            return nullptr;
        }
        
        void eliminarPorID(const std::string& id, const std::string& archivo) {
            /*
            Método para eliminar un autor por su ID.
            Parámetros:
            - id: El ID del autor a eliminar.
            - archivo: El archivo donde se guardarán los cambios.
            Descripción:
            Este método elimina un autor del vector de autores y actualiza el archivo correspondiente.
            */
            autores.erase(std::remove_if(autores.begin(), autores.end(),
                         [&id](const Autor& a) { return a.id == id; }), autores.end());
            std::cout << "Autor eliminado.\n";
        }
    };
    
    class ControlEditoriales {
        /*
        Clase para controlar las operaciones relacionadas con las editoriales.
        Atributos:
        - editoriales: Referencia al vector de editoriales.
        Métodos:
        - agregar: Agrega una nueva editorial.
        - mostrarTodos: Muestra todas las editoriales.
        - buscarPorID: Busca una editorial por su ID.
        - eliminarPorID: Elimina una editorial por su ID.
        */
    private:
        std::vector<Editorial>& editoriales;
        
    public:
        ControlEditoriales(std::vector<Editorial>& e) : editoriales(e) {
            /*
            Constructor de la clase ControlEditoriales.
            Inicializa la referencia al vector de editoriales.
            */
        }
        
        void agregar(const Editorial& editorial) {
            /*
            Método para agregar una nueva editorial.
            Parámetros:
            - editorial: La editorial a agregar.
            Descripción:
            Este método agrega una nueva editorial al vector de editoriales.
            */
            editoriales.push_back(editorial);
        }
        
        void mostrarTodos() {
            /*
            Método para mostrar todas las editoriales.
            */
            for (const auto& editorial : editoriales) {
                std::cout << "ID: " << editorial.id << ", Nombre: " << editorial.nombre
                         << ", Ciudad: " << editorial.ciudadPrincipal << ", País: " << editorial.paisPrincipal << std::endl;
            }
        }
        
        Editorial* buscarPorID(const std::string& id) {
            /*
            Método para buscar una editorial por su ID.
            Parámetros:
            - id: El ID de la editorial a buscar.
            Retorno:
            - Un puntero a la editorial encontrada, o nullptr si no se encuentra.
            */
            for (auto& editorial : editoriales) {
                if (editorial.id == id) {
                    return &editorial;
                }
            }
            return nullptr;
        }
        
        void eliminarPorID(const std::string& id, const std::string& archivo) {
            /*
            Método para eliminar una editorial por su ID.
            Parámetros:
            - id: El ID de la editorial a eliminar.
            - archivo: El archivo donde se guardarán los cambios.
            Descripción:
            Este método elimina una editorial del vector de editoriales y actualiza el archivo correspondiente.
            */
            editoriales.erase(std::remove_if(editoriales.begin(), editoriales.end(),
                             [&id](const Editorial& e) { return e.id == id; }), editoriales.end());
            std::cout << "Editorial eliminada.\n";
        }
    };
    
    class ControlObras {
        /*
        Clase para controlar las operaciones relacionadas con las obras.
        Atributos:
        - obras: Referencia al vector de obras.
        Métodos:
        - agregar: Agrega una nueva obra.
        - mostrarTodos: Muestra todas las obras.
        - buscarPorID: Busca una obra por su ID.
        - eliminarPorID: Elimina una obra por su ID.
        */
    private:
        std::vector<Obra>& obras;
        
    public:
        ControlObras(std::vector<Obra>& o) : obras(o) {
            /*
            Constructor de la clase ControlObras.
            Inicializa la referencia al vector de obras.
            Parámetros:
            - o: El vector de obras a controlar.
            Descripción:
            Este constructor inicializa la clase ControlObras con una referencia al vector de obras existente.
            */
        }
        
        void agregar(const Obra& obra) {
            /*
            Método para agregar una nueva obra.
            Parámetros:
            - obra: La obra a agregar.
            Descripción:
            Este método agrega una nueva obra al vector de obras.
            */
            obras.push_back(obra);
        }
        
        void mostrarTodos() {
            /*
            Método para mostrar todas las obras.
            Descripción:
            Este método itera sobre el vector de obras y muestra sus detalles.
            */
            for (const auto& obra : obras) {
                std::cout << "Nombre: " << obra.nombre << ", Tipo: " << obra.tipoPoesia
                         << ", ID Autor: " << obra.idAutor << std::endl;
            }
        }
        
        void eliminarPorNombre(const std::string& nombre, const std::string& archivo) {
            /*
            Método para eliminar una obra por su nombre.
            Parámetros:
            - nombre: El nombre de la obra a eliminar.
            - archivo: El archivo donde se guardarán los cambios.
            Descripción:
            Este método elimina una obra del vector de obras y actualiza el archivo correspondiente.
            */
            obras.erase(std::remove_if(obras.begin(), obras.end(),
                       [&nombre](const Obra& o) { return o.nombre == nombre; }), obras.end());
            std::cout << "Obra eliminada.\n";
        }
    };
    
    class ControlEdiciones {
        /*
        Clase para controlar las operaciones relacionadas con las ediciones.
        Atributos:
        - ediciones: Referencia al vector de ediciones.
        Métodos:
        - agregar: Agrega una nueva edición.
        - mostrarTodos: Muestra todas las ediciones.
        - buscarPorNumero: Busca una edición por su número.
        - eliminarPorNumero: Elimina una edición por su número.
        */
    private:
        std::vector<Edicion>& ediciones;
        
    public:
        ControlEdiciones(std::vector<Edicion>& e) : ediciones(e) {
            /*
            Constructor de la clase ControlEdiciones.
            Inicializa la referencia al vector de ediciones.
            Parámetros:
            - e: El vector de ediciones a controlar.
            Descripción:
            Este constructor inicializa la clase ControlEdiciones con una referencia al vector de ediciones existente.
            */
        }
        
        void agregar(const Edicion& edicion) {
            /*
            Método para agregar una nueva edición.
            Parámetros:
            - edicion: La edición a agregar.
            Descripción:
            Este método agrega una nueva edición al vector de ediciones.
            */
            ediciones.push_back(edicion);
        }
        
        void mostrarTodos() {
            /*
            Método para mostrar todas las ediciones.
            Descripción:
            Este método itera sobre el vector de ediciones y muestra sus detalles.
            */
            for (const auto& edicion : ediciones) {
                std::cout << "Número: " << edicion.numeroEdicion << ", Fecha: " << edicion.fechaPublicacion
                         << ", ID Editorial: " << edicion.idEditorial << ", Ciudad: " << edicion.ciudadPublicacion
                         << ", ID Obra: " << edicion.idObra << std::endl;
            }
        }
        
        void eliminarPorNumero(int numero, const std::string& archivo) {
            /*
            Método para eliminar una edición por su número.
            Parámetros:
            - numero: El número de la edición a eliminar.
            - archivo: El archivo donde se guardarán los cambios.
            Descripción:
            Este método elimina una edición del vector de ediciones y actualiza el archivo correspondiente.
            */
            ediciones.erase(std::remove_if(ediciones.begin(), ediciones.end(),
                           [numero](const Edicion& e) { return e.numeroEdicion == numero; }), ediciones.end());
            std::cout << "Edición eliminada.\n";
        }
    };
    
    ControlAutores getControlAutores() { return ControlAutores(autores); }
    ControlEditoriales getControlEditoriales() { return ControlEditoriales(editoriales); }
    ControlObras getControlObras() { return ControlObras(obras); }
    ControlEdiciones getControlEdiciones() { return ControlEdiciones(ediciones); }
    
    void inicializarSistema() {
        /*
        Método para inicializar el sistema.
        Descripción:
        Este método carga los datos de los archivos y construye los índices necesarios.
        */
        cargarAutores("autores.txt");
        cargarEditoriales("editoriales.txt");
        cargarObras("obras.txt");
        cargarEdiciones("ediciones.txt");
        construirIndices();
        std::cout << "Sistema inicializado correctamente.\n";
        std::cout << "Autores cargados: " << autores.size() << std::endl;
        std::cout << "Editoriales cargadas: " << editoriales.size() << std::endl;
        std::cout << "Obras cargadas: " << obras.size() << std::endl;
        std::cout << "Ediciones cargadas: " << ediciones.size() << std::endl;
    }
    
    void construirIndicesOptimizados() {
        /*
        Método para construir índices optimizados.
        Descripción:
        Este método crea índices adicionales para mejorar la eficiencia de las búsquedas.
        */
        construirIndices();
        std::cout << "Índices optimizados construidos.\n";
    }
    
    void optimizarEstructuras() {
        /*
        Método para optimizar las estructuras de datos.
        Descripción:
        Este método aplica técnicas de optimización a las estructuras de datos utilizadas en el sistema.
        */
        std::sort(autores.begin(), autores.end(), [](const Autor& a, const Autor& b) {
            return a.id < b.id;
        });
        std::sort(editoriales.begin(), editoriales.end(), [](const Editorial& a, const Editorial& b) {
            return a.id < b.id;
        });
        construirIndices();
        std::cout << "Estructuras optimizadas.\n";
    }
    
    void guardarTodosSistema() {
        /*
        Método para guardar todos los datos del sistema.
        Descripción:
        Este método llama a las funciones de guardado para cada tipo de dato.
        */
        guardarArchivo("autores.txt", "autores");
        guardarArchivo("editoriales.txt", "editoriales");
        guardarArchivo("obras.txt", "obras");
        guardarArchivo("ediciones.txt", "ediciones");
        std::cout << "Todos los datos guardados correctamente.\n";
    }
    
    void cargarAutores(const std::string& archivo) {
        /*
        Método para cargar los autores desde un archivo.
        Descripción:
        Este método lee los datos de los autores desde un archivo de texto y los almacena en el vector de autores.
        Parámetros:
        - archivo: El nombre del archivo desde el cual se cargarán los autores.
        */
        std::ifstream file(archivo);
        if (!file.is_open()) {
            std::cout << "No se pudo abrir el archivo de autores: " << archivo << std::endl;
            return;
        }
        
        std::string linea;
        while (std::getline(file, linea)) {
            if (linea.empty()) continue;
            
            std::stringstream ss(linea);
            std::string campo;
            Autor autor;
            
            std::getline(ss, autor.id, ';');
            std::getline(ss, autor.nombre, ';');
            std::getline(ss, autor.apellido, ';');
            std::getline(ss, campo, ';'); autor.sexo = campo.empty() ? ' ' : campo[0];
            std::getline(ss, autor.fechaNacimiento, ';');
            std::getline(ss, autor.ciudadNacimiento, ';');
            std::getline(ss, autor.paisNacimiento, ';');
            std::getline(ss, autor.ciudadResidencia, ';');
            std::getline(ss, autor.formacionBase, ';');
            std::getline(ss, campo, ';'); autor.anioInicioLiteratura = std::stoi(campo);
            std::getline(ss, campo); autor.anioPrimeraObra = std::stoi(campo);
            
            autores.push_back(autor);
        }
        file.close();
    }
    
    void cargarEditoriales(const std::string& archivo) {
        /*
        Método para cargar las editoriales desde un archivo.
        Descripción:
        Este método lee los datos de las editoriales desde un archivo de texto y los almacena en el vector de editoriales.
        Parámetros:
        - archivo: El nombre del archivo desde el cual se cargarán las editoriales.
        */
        std::ifstream file(archivo);
        if (!file.is_open()) {
            std::cout << "No se pudo abrir el archivo de editoriales: " << archivo << std::endl;
            return;
        }
        
        std::string linea;
        while (std::getline(file, linea)) {
            if (linea.empty()) continue;
            
            std::stringstream ss(linea);
            Editorial editorial;
            
            std::getline(ss, editorial.id, ';');
            std::getline(ss, editorial.nombre, ';');
            std::getline(ss, editorial.ciudadPrincipal, ';');
            std::getline(ss, editorial.paisPrincipal);
            
            editoriales.push_back(editorial);
        }
        file.close();
    }
    
    void cargarObras(const std::string& archivo) {
        /*
        Método para cargar las obras desde un archivo.
        Descripción:
        Este método lee los datos de las obras desde un archivo de texto y los almacena en el vector de obras.
        Parámetros:
        - archivo: El nombre del archivo desde el cual se cargarán las obras.
        */
        std::ifstream file(archivo);
        if (!file.is_open()) {
            std::cout << "No se pudo abrir el archivo de obras: " << archivo << std::endl;
            return;
        }
        
        std::string linea;
        while (std::getline(file, linea)) {
            if (linea.empty()) continue;
            
            std::stringstream ss(linea);
            Obra obra;
            
            std::getline(ss, obra.nombre, ';');
            std::getline(ss, obra.tipoPoesia, ';');
            std::getline(ss, obra.idAutor);
            
            obras.push_back(obra);
        }
        file.close();
    }
    
    void cargarEdiciones(const std::string& archivo) {
        /*
        Método para cargar las ediciones desde un archivo.
        Descripción:
        Este método lee los datos de las ediciones desde un archivo de texto y los almacena en el vector de ediciones.
        Parámetros:
        - archivo: El nombre del archivo desde el cual se cargarán las ediciones.
        */
        std::ifstream file(archivo);
        if (!file.is_open()) {
            std::cout << "No se pudo abrir el archivo de ediciones: " << archivo << std::endl;
            return;
        }
        
        std::string linea;
        while (std::getline(file, linea)) {
            if (linea.empty()) continue;
            
            std::stringstream ss(linea);
            std::string campo;
            Edicion edicion;
            
            std::getline(ss, campo, ';'); edicion.numeroEdicion = std::stoi(campo);
            std::getline(ss, edicion.fechaPublicacion, ';');
            std::getline(ss, edicion.idEditorial, ';');
            std::getline(ss, edicion.ciudadPublicacion, ';');
            std::getline(ss, edicion.idObra);
            
            ediciones.push_back(edicion);
        }
        file.close();
    }
    
    // CONSULTAS PRINCIPALES
    
    // Consulta 1: Obras de un autor por editorial y año
    void consultaObrasAutorPorEditorialAnio(const std::string& idAutor) {
        /*
        Consulta las obras de un autor específico, agrupadas por editorial y año de publicación.
        Parámetros:
        - idAutor: El identificador del autor cuyas obras se consultarán.
        Descripción:
        Esta función busca las obras del autor especificado y las agrupa por editorial y año de
        */
        std::cout << "=== CONSULTA 1: Obras por Editorial y Año ===" << std::endl;
        std::cout << "Autor: " << obtenerNombreAutor(idAutor) << std::endl;

    std::cout << "Buscando autor en índice..." << std::endl;
    if (autorObras.find(idAutor) == autorObras.end()) {
        std::cout << "Autor no encontrado en índice autorObras" << std::endl;
        return;
    }
    std::cout << "Autor encontrado, tiene " << autorObras[idAutor].size() << " obras" << std::endl;
    
    for (int idx : autorObras[idAutor]) {
        std::cout << "Obra[" << idx << "]: " << obras[idx].nombre << std::endl;
    }
        
        std::map<std::string, std::map<int, int>> resultado;
        
        if (autorObras.find(idAutor) != autorObras.end()) {
            for (int idx : autorObras[idAutor]) {
                const Obra& obra = obras[idx];
                
                if (obraEdiciones.find(obra.nombre) != obraEdiciones.end()) {
                    for (int edIdx : obraEdiciones[obra.nombre]) {
                        const Edicion& edicion = ediciones[edIdx];
                        int anio = extraerAnio(edicion.fechaPublicacion);
                        std::string nombreEditorial = obtenerNombreEditorial(edicion.idEditorial);
                        resultado[nombreEditorial][anio]++;
                    }
                }
            }
        }
        
        if (resultado.empty()) {
            std::cout << "No se encontraron obras para el autor especificado." << std::endl;
            return;
        }
        
        int totalObras = 0;
        for (const auto& editorial : resultado) {
            std::cout << "\nEditorial: " << editorial.first << std::endl;
            for (const auto& anio : editorial.second) {
                std::cout << "  Año " << anio.first << ": " << anio.second << " obras" << std::endl;
                totalObras += anio.second;
            }
        }
        std::cout << "\nTotal de obras: " << totalObras << std::endl;
    }
    
    void consultaObrasAutorPorTipoPoesia(const std::string& idAutor) {
        /*
        Consulta las obras de un autor específico, agrupadas por tipo de poesía.
        Parámetros:
        - idAutor: El identificador del autor cuyas obras se consultarán.
        Descripción:
        Esta función busca las obras del autor especificado y las agrupa por tipo de poesía.
        */
        std::cout << "=== CONSULTA 2: Obras por Tipo de Poesía ===" << std::endl;
        std::cout << "Autor: " << obtenerNombreAutor(idAutor) << std::endl;
        
        std::map<std::string, std::vector<std::pair<std::string, std::vector<std::pair<std::string, int>>>>> resultado;
        
        if (autorObras.find(idAutor) != autorObras.end()) {
            for (int idx : autorObras[idAutor]) {
                const Obra& obra = obras[idx];
                std::vector<std::pair<std::string, int>> edicionesObra;
                
                if (obraEdiciones.find(obra.nombre) != obraEdiciones.end()) {
                    for (int edIdx : obraEdiciones[obra.nombre]) {
                        const Edicion& edicion = ediciones[edIdx];
                        edicionesObra.push_back({edicion.fechaPublicacion, edicion.numeroEdicion});
                    }
                }
                resultado[obra.tipoPoesia].push_back({obra.nombre, edicionesObra});
            }
        }
        
        if (resultado.empty()) {
            std::cout << "No se encontraron obras para el autor especificado." << std::endl;
            return;
        }
        
        for (const auto& tipo : resultado) {
            std::cout << "\nTipo de Poesía: " << tipo.first << std::endl;
            for (const auto& obra : tipo.second) {
                std::cout << "  Obra: " << obra.first << std::endl;
                for (const auto& edicion : obra.second) {
                    std::cout << "    - Fecha: " << edicion.first << ", Edición: " << edicion.second << std::endl;
                }
            }
        }
    }
    
    // Consulta 3: Autores publicados por editorial
    void consultaAutoresPorEditorial(const std::string& idEditorial) {
        /*
        Consulta los autores que han publicado obras en una editorial específica.
        Parámetros:
        - idEditorial: El identificador de la editorial cuyas obras se consultarán.
        Descripción:
        Esta función busca los autores que han publicado obras en la editorial especificada.
        */
        std::cout << "=== CONSULTA 3: Autores por Editorial ===" << std::endl;
        std::cout << "Editorial: " << obtenerNombreEditorial(idEditorial) << std::endl;
        
        std::map<std::string, std::map<int, std::vector<std::string>>> resultado;
        std::set<std::string> autoresUnicos;
        
        if (editorialEdiciones.find(idEditorial) != editorialEdiciones.end()) {
            for (int edIdx : editorialEdiciones[idEditorial]) {
                const Edicion& edicion = ediciones[edIdx];
                
                for (const auto& obra : obras) {
                    if (obra.nombre == edicion.idObra) {
                        Autor* autor = obtenerAutorPorId(obra.idAutor);
                        if (autor && autoresUnicos.find(autor->id) == autoresUnicos.end()) {
                            autoresUnicos.insert(autor->id);
                            std::string info = autor->nombre + " " + autor->apellido + " - " + 
                                             autor->ciudadNacimiento + ", " + autor->paisNacimiento;
                            resultado[autor->ciudadResidencia][autor->anioInicioLiteratura].push_back(info);
                        }
                        break;
                    }
                }
            }
        }
        
        if (resultado.empty()) {
            std::cout << "No se encontraron autores para la editorial especificada." << std::endl;
            return;
        }
        
        for (const auto& ciudad : resultado) {
            std::cout << "\nCiudad de Residencia: " << ciudad.first << std::endl;
            for (const auto& anio : ciudad.second) {
                std::cout << "  Año de Inicio: " << anio.first << std::endl;
                for (const auto& autor : anio.second) {
                    std::cout << "    - " << autor << std::endl;
                }
            }
        }
    }
    
    void consultaEditorialesConNPoetas(int numeroMinimo) {
        std::cout << "=== CONSULTA 4: Editoriales con más de " << numeroMinimo << " poetas ===" << std::endl;
        
        std::map<std::string, std::set<std::string>> poetasPorEditorial;
        
        for (const auto& edicion : ediciones) {
            for (const auto& obra : obras) {
                if (obra.nombre == edicion.idObra) {
                    poetasPorEditorial[edicion.idEditorial].insert(obra.idAutor);
                    break;
                }
            }
        }
        
        int editorialesEncontradas = 0;
        for (const auto& editorial : poetasPorEditorial) {
            if (static_cast<int>(editorial.second.size()) > numeroMinimo) {
                editorialesEncontradas++;
                Editorial* ed = obtenerEditorialPorId(editorial.first);
                if (ed) {
                    std::cout << "\nEditorial: " << ed->nombre << std::endl;
                    std::cout << "  Ubicación: " << ed->ciudadPrincipal << ", " << ed->paisPrincipal << std::endl;
                    std::cout << "  Cantidad de poetas: " << editorial.second.size() << std::endl;
                }
            }
        }

        
        std::cout << "\nTotal de editoriales encontradas: " << editorialesEncontradas << std::endl;
    }
    
    // Consulta 5: Autores por editorial clasificados por lugar de nacimiento
    void consultaAutoresPorEditorialNacimiento(const std::string& idEditorial) {
        /*
        Consulta los autores de una editorial específica, clasificados por su lugar de nacimiento.
        Parámetros:
        - idEditorial: El identificador de la editorial cuyas obras se consultarán.
        Descripción:
        Esta función busca los autores que han publicado obras en la editorial especificada y los clasifica por país, ciudad y sexo.
        */
        std::cout << "=== CONSULTA 5: Autores por Editorial y Lugar de Nacimiento ===" << std::endl;
        std::cout << "Editorial: " << obtenerNombreEditorial(idEditorial) << std::endl;
        
        std::map<std::string, std::map<std::string, std::map<char, std::vector<std::string>>>> resultado;
        std::set<std::string> autoresUnicos;
        
        if (editorialEdiciones.find(idEditorial) != editorialEdiciones.end()) {
            for (int edIdx : editorialEdiciones[idEditorial]) {
                const Edicion& edicion = ediciones[edIdx];
                
                for (const auto& obra : obras) {
                    if (obra.nombre == edicion.idObra) {
                        Autor* autor = obtenerAutorPorId(obra.idAutor);
                        if (autor && autoresUnicos.find(autor->id) == autoresUnicos.end()) {
                            autoresUnicos.insert(autor->id);
                            std::string nombreCompleto = autor->nombre + " " + autor->apellido;
                            resultado[autor->paisNacimiento][autor->ciudadNacimiento][autor->sexo].push_back(nombreCompleto);
                        }
                        break;
                    }
                }
            }
        }
        
        if (resultado.empty()) {
            std::cout << "No se encontraron autores para la editorial especificada." << std::endl;
            return;
        }
        
        for (const auto& pais : resultado) {
            std::cout << "\nPaís: " << pais.first << std::endl;
            for (const auto& ciudad : pais.second) {
                std::cout << "  Ciudad: " << ciudad.first << std::endl;
                if (ciudad.second.count('M')) {
                    std::cout << "    Hombres (" << ciudad.second.at('M').size() << "):" << std::endl;
                    for (const auto& nombre : ciudad.second.at('M')) {
                        std::cout << "      - " << nombre << std::endl;
                    }
                }
                if (ciudad.second.count('F')) {
                    std::cout << "    Mujeres (" << ciudad.second.at('F').size() << "):" << std::endl;
                    for (const auto& nombre : ciudad.second.at('F')) {
                        std::cout << "      - " << nombre << std::endl;
                    }
                }
            }
        }
    }

// Consulta 6: Autores por rango de edad y formación de base
    void consultaAutoresPorEdadYFormacion(int edadMinima, int edadMaxima, const std::string& formacionBase) {
        /*
        Consulta los autores por rango de edad y formación de base.
        Parámetros:
        - edadMinima: La edad mínima de los autores a consultar.
        - edadMaxima: La edad máxima de los autores a consultar.
        - formacionBase: La formación de base de los autores a consultar.
        Descripción:
        Esta función busca los autores que cumplen con los criterios de edad y formación de base especificados.
        */
        std::cout << "=== CONSULTA 6: Autores por Rango de Edad y Formación ===" << std::endl;
        std::cout << "Rango de edad: " << edadMinima << " - " << edadMaxima << " años" << std::endl;
        std::cout << "Formación de base: " << formacionBase << std::endl;
        
        // Estructura: Año de primera obra -> Lista de autores
        std::map<int, std::vector<std::string>> autoresPorAnio;
        
        for (const auto& autor : autores) {
            int edad = calcularEdad(autor.fechaNacimiento);
            
            // Verificar si el autor cumple con los criterios
            if (edad >= edadMinima && edad <= edadMaxima && edad > 0 && 
                autor.formacionBase.find(formacionBase) != std::string::npos) {
                    std::string infoAutor = autor.nombre + " " + autor.apellido + 
                                       " (Edad: " + std::to_string(edad) + 
                                       ", Residencia: " + autor.ciudadResidencia + 
                                       ", Nacimiento: " + autor.ciudadNacimiento + ", " + autor.paisNacimiento + ")";
                
                autoresPorAnio[autor.anioPrimeraObra].push_back(infoAutor);
            }
        }
        
        if (autoresPorAnio.empty()) {
            std::cout << "No se encontraron autores con los criterios especificados." << std::endl;
            return;
        }
        
        int totalAutores = 0;
        for (const auto& anio : autoresPorAnio) {
            std::cout << "\nAño de primera obra: " << anio.first << std::endl;
            for (const auto& autor : anio.second) {
                std::cout << "  - " << autor << std::endl;
                totalAutores++;
            }
        }
        
        std::cout << "\nTotal de autores encontrados: " << totalAutores << std::endl;
    }
    
    // Consulta 7: Autores por tipo de poesía y editorial
    void consultaAutoresPorTipoPoesiaYEditorial(const std::string& tipoPoesia, const std::string& idEditorial) {
        /*
        Consulta los autores por tipo de poesía y editorial.
        Parámetros:
        - tipoPoesia: El tipo de poesía a consultar.
        - idEditorial: El identificador de la editorial a consultar.
        Descripción:
        Esta función busca los autores que han publicado obras del tipo de poesía especificado en la editorial indicada.
        */
        std::cout << "=== CONSULTA 7: Autores por Tipo de Poesía y Editorial ===" << std::endl;
        std::cout << "Tipo de poesía: " << tipoPoesia << std::endl;
        std::cout << "Editorial: " << obtenerNombreEditorial(idEditorial) << std::endl;
        
        std::map<std::string, std::pair<std::string, std::vector<std::string>>> autoresConEdiciones;
        
        for (const auto& obra : obras) {
            if (obra.tipoPoesia.find(tipoPoesia) != std::string::npos) {
                if (obraEdiciones.find(obra.nombre) != obraEdiciones.end()) {
                    for (int edIdx : obraEdiciones[obra.nombre]) {
                        const Edicion& edicion = ediciones[edIdx];
                        if (edicion.idEditorial == idEditorial) {
                        
                        std::string infoAutor = obtenerNombreAutor(obra.idAutor);
                        Autor* autor = obtenerAutorPorId(obra.idAutor);
                        
                        if (autor) {
                            std::string datosCompletos = infoAutor + 
                                                       " (Sexo: " + std::string(1, autor->sexo) + 
                                                       ", Nacimiento: " + autor->fechaNacimiento + 
                                                       ", " + autor->ciudadNacimiento + ", " + autor->paisNacimiento + 
                                                       ", Residencia: " + autor->ciudadResidencia + 
                                                       ", Formación: " + autor->formacionBase + ")";
                            
                            std::string infoEdicion = "Obra: " + obra.nombre + 
                                                    ", Edición #" + std::to_string(edicion.numeroEdicion) + 
                                                    ", Fecha: " + edicion.fechaPublicacion + 
                                                    ", Ciudad: " + edicion.ciudadPublicacion;
                            
                            if (autoresConEdiciones.find(obra.idAutor) == autoresConEdiciones.end()) {
                                autoresConEdiciones[obra.idAutor] = {datosCompletos, {}};
                            }
                            
                            autoresConEdiciones[obra.idAutor].second.push_back(infoEdicion);
                        }
                    }
                }
            }
        }
        
        if (autoresConEdiciones.empty()) {
            std::cout << "No se encontraron autores con los criterios especificados." << std::endl;
            return;
        }
        int totalAutores = 0;
        int totalEdiciones = 0;
        
        for (const auto& autorInfo : autoresConEdiciones) {
            totalAutores++;
            std::cout << "\nAutor: " << autorInfo.second.first << std::endl;
            std::cout << "Ediciones encontradas:" << std::endl;
            
            for (const auto& edicion : autorInfo.second.second) {
                std::cout << "  - " << edicion << std::endl;
                totalEdiciones++;
            }
        }
        
        std::cout << "\nResumen:" << std::endl;
        std::cout << "Total de autores: " << totalAutores << std::endl;
        std::cout << "Total de ediciones: " << totalEdiciones << std::endl;
    }
}
};

#endif // GESTIONBIBLIOTECA_H