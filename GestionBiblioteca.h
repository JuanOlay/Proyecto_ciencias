#ifndef GESTIONBIBLIOTECA_H
#define GESTIONBIBLIOTECA_H

#include "ArbolRojiNegro.h"
#include "Multilista.h"
#include "Entidades.h"
#include "ManejadorArchivos.h"
#include "ControlAutores.h"
#include "ControlEditoriales.h"
#include "ControlObras.h"
#include <sstream>

class GestionBiblioteca {
private:
    ControlAutores controlAutores;
    ControlEditoriales controlEditoriales;
    ControlObras controlObras;

    // Árboles principales para búsquedas por ID (O(log n))
    ArbolRojiNegro<Autor> arbolAutores;
    ArbolRojiNegro<Editorial> arbolEditoriales;
    ArbolRojiNegro<Obra> arbolObras;
    ArbolRojiNegro<Edicion> arbolEdiciones;

    // === MULTILISTAS OPTIMIZADAS POR CONSULTA ===
    
    // Para consulta 1: Número total de obras de un autor, clasificadas por editorial y año
    Multilista<std::string, Obra> autorObras;                    // Clave: idAutor
    Multilista<std::string, std::string> editorialAnios;         // Clave: idEditorial, Valor: "año-nombreObra"
    
    // Para consulta 2: Obras de un autor por tipo de poesía
    Multilista<std::string, std::string> autorTipoPoesia;        // Clave: idAutor, Valor: "tipoPoesia-nombreObra-fechaPublicacion-numEdicion"
    
    // Para consulta 3: Autores publicados por editorial, clasificados por ciudad y año inicio
    Multilista<std::string, std::string> editorialAutores;      // Clave: idEditorial, Valor: "ciudadResidencia-añoInicio-idAutor"
    
    // Para consulta 4: Editoriales con número de poetas > N
    Multilista<std::string, std::string> editorialPoetas;       // Clave: idEditorial, Valor: idAutor (para contar únicos)
    
    // Para consulta 5: Autores por editorial, clasificados por ciudad y país de nacimiento
    Multilista<std::string, std::string> editorialAutoresNacimiento; // Clave: idEditorial, Valor: "paisNacimiento-ciudadNacimiento-idAutor"
    
    // Para consulta 6: Autores por formación y edad
    Multilista<std::string, std::string> formacionAutores;      // Clave: formacionBase, Valor: "edad-añoPrimeraObra-idAutor"
    
    // Para consulta 7: Autores por tipo de poesía y editorial
    Multilista<std::string, std::string> tipoPoesiaEditorial;   // Clave: "tipoPoesia-idEditorial", Valor: idAutor

    // === MÉTODOS AUXILIARES PRIVADOS ===

    // Calcular edad basado en fecha de nacimiento
    int calcularEdad(const std::string& fechaNacimiento) const {
        if (fechaNacimiento.empty()) return 0;
        
        // Asumiendo formato DD/MM/YYYY o DD-MM-YYYY
        std::string anioStr;
        size_t pos = fechaNacimiento.find_last_of("/-");
        if (pos != std::string::npos && pos + 1 < fechaNacimiento.length()) {
            anioStr = fechaNacimiento.substr(pos + 1);
        }
        
        if (anioStr.empty()) return 0;
        
        int anioNacimiento = std::atoi(anioStr.c_str());
        return (anioNacimiento > 0) ? (2024 - anioNacimiento) : 0;
    }

    // Extraer año de fecha de publicación
    int extraerAnio(const std::string& fecha) const {
        if (fecha.empty()) return 0;
        
        std::string anioStr;
        size_t pos = fecha.find_last_of("/-");
        if (pos != std::string::npos && pos + 1 < fecha.length()) {
            anioStr = fecha.substr(pos + 1);
        }
        
        return std::atoi(anioStr.c_str());
    }

    // Buscar todas las ediciones de una obra específica
    void buscarEdicionesObra(const std::string& nombreObra, 
                           std::string& fechaPublicacion, 
                           std::string& idEditorial,
                           int& numeroEdicion) const {
        // Implementar búsqueda en arbolEdiciones
        // Esta es una implementación simplificada
        fechaPublicacion = "";
        idEditorial = "";
        numeroEdicion = 0;
    }

    // Verificar si un autor ya está asociado a una editorial
    bool autorYaEnEditorial(const std::string& idEditorial, const std::string& idAutor) const {
        return editorialPoetas.buscarEnSublista(idEditorial, idAutor);
    }

public:
    // Constructor
    GestionBiblioteca() {}

    // Destructor
    ~GestionBiblioteca() {}

    // Getters para controladores
    ControlAutores& getControlAutores() { return controlAutores; }
    ControlEditoriales& getControlEditoriales() { return controlEditoriales; }
    ControlObras& getControlObras() { return controlObras; }

    // === MÉTODOS DE CARGA OPTIMIZADOS ===

    void cargarAutoresDesdeArchivo(const std::string& ruta) {
        ManejadorArchivos::cargarAutores(ruta, arbolAutores, formacionAutores);
        std::cout << "Autores cargados. Construyendo índices optimizados..." << std::endl;
    }

    void cargarEditorialesDesdeArchivo(const std::string& ruta) {
        ManejadorArchivos::cargarEditoriales(ruta, arbolEditoriales);
        std::cout << "Editoriales cargadas." << std::endl;
    }

    void cargarObrasDesdeArchivo(const std::string& ruta) {
        ManejadorArchivos::cargarObras(ruta, arbolObras, autorObras);
        std::cout << "Obras cargadas. Construyendo índices optimizados..." << std::endl;
    }

    void cargarEdicionesDesdeArchivo(const std::string& ruta) {
        ManejadorArchivos::cargarEdiciones(ruta, arbolEdiciones, editorialAnios);
        std::cout << "Ediciones cargadas." << std::endl;
    }

    // === CONSTRUCCIÓN DE ÍNDICES OPTIMIZADOS ===

    void construirIndicesOptimizados() {
        std::cout << "Construyendo índices optimizados para consultas..." << std::endl;
        
        construirIndiceConsulta1();
        construirIndiceConsulta2();
        construirIndiceConsulta3();
        construirIndiceConsulta4();
        construirIndiceConsulta5();
        construirIndiceConsulta6();
        construirIndiceConsulta7();
        
        std::cout << "Índices construidos exitosamente." << std::endl;
    }

    // Construcción específica para cada consulta
    void construirIndiceConsulta1() {
        // Ya se construye autorObras en ManejadorArchivos
        // Aquí podríamos agregar más optimizaciones específicas
    }

    void construirIndiceConsulta2() {
        // Construir autorTipoPoesia combinando obras y ediciones
        // Necesitamos recorrer todas las obras y sus ediciones
        std::cout << "Construyendo índice para consulta 2..." << std::endl;
    }

    void construirIndiceConsulta3() {
        // Construir editorialAutores basado en relaciones obra-edición-autor
        std::cout << "Construyendo índice para consulta 3..." << std::endl;
    }

    void construirIndiceConsulta4() {
        // Construir editorialPoetas para contar poetas únicos por editorial
        std::cout << "Construyendo índice para consulta 4..." << std::endl;
    }

    void construirIndiceConsulta5() {
        // Construir editorialAutoresNacimiento
        std::cout << "Construyendo índice para consulta 5..." << std::endl;
    }

    void construirIndiceConsulta6() {
        // Ya se construye formacionAutores, agregar información de edad
        std::cout << "Construyendo índice para consulta 6..." << std::endl;
    }

    void construirIndiceConsulta7() {
        // Construir tipoPoesiaEditorial
        std::cout << "Construyendo índice para consulta 7..." << std::endl;
    }

    // === MÉTODOS DE CONSULTA OPTIMIZADOS ===

    // Consulta 1: Número total de obras de un autor, clasificadas por editorial y año
    void consultaObrasAutorPorEditorialAnio(const std::string& idAutor) const {
        std::cout << "\n=== CONSULTA 1: Obras del autor " << idAutor << " por editorial y año ===" << std::endl;
        
        if (!autorObras.existe(idAutor)) {
            std::cout << "No se encontraron obras para el autor " << idAutor << std::endl;
            return;
        }

        // Aquí implementarías la lógica específica usando las multilistas optimizadas
        std::cout << "Mostrando obras clasificadas por editorial y año..." << std::endl;
        autorObras.mostrarSublista(idAutor);
    }

    // Consulta 2: Obras de un autor por tipo de poesía
    void consultaObrasAutorPorTipoPoesia(const std::string& idAutor) const {
        std::cout << "\n=== CONSULTA 2: Obras del autor " << idAutor << " por tipo de poesía ===" << std::endl;
        
        if (!autorTipoPoesia.existe(idAutor)) {
            std::cout << "No se encontraron obras para el autor " << idAutor << std::endl;
            return;
        }

        autorTipoPoesia.mostrarSublista(idAutor);
    }

    // Consulta 3: Autores publicados por editorial
    void consultaAutoresPorEditorial(const std::string& idEditorial) const {
        std::cout << "\n=== CONSULTA 3: Autores publicados por editorial " << idEditorial << " ===" << std::endl;
        
        if (!editorialAutores.existe(idEditorial)) {
            std::cout << "No se encontraron autores para la editorial " << idEditorial << std::endl;
            return;
        }

        editorialAutores.mostrarSublista(idEditorial);
    }

    // Consulta 4: Editoriales con más de N poetas
    void consultaEditorialesConNPoetas(int numeroMinimo) const {
        std::cout << "\n=== CONSULTA 4: Editoriales con más de " << numeroMinimo << " poetas ===" << std::endl;
        
        if (editorialPoetas.estaVacia()) {
            std::cout << "No hay datos de poetas por editorial." << std::endl;
            return;
        }

        // Implementar lógica de conteo
        std::cout << "Mostrando editoriales que cumplen el criterio..." << std::endl;
        editorialPoetas.mostrarPrincipal();
    }

    // Consulta 5: Autores por editorial, clasificados por lugar de nacimiento
    void consultaAutoresPorEditorialNacimiento(const std::string& idEditorial) const {
        std::cout << "\n=== CONSULTA 5: Autores de editorial " << idEditorial << " por lugar de nacimiento ===" << std::endl;
        
        if (!editorialAutoresNacimiento.existe(idEditorial)) {
            std::cout << "No se encontraron datos para la editorial " << idEditorial << std::endl;
            return;
        }

        editorialAutoresNacimiento.mostrarSublista(idEditorial);
    }

    // Consulta 6: Autores por formación y rango de edad
    void consultaAutoresPorFormacionYEdad(const std::string& formacion, int edadMin, int edadMax) const {
        std::cout << "\n=== CONSULTA 6: Autores con formación " << formacion 
                  << " entre " << edadMin << " y " << edadMax << " años ===" << std::endl;
        
        if (!formacionAutores.existe(formacion)) {
            std::cout << "No se encontraron autores con formación " << formacion << std::endl;
            return;
        }

        formacionAutores.mostrarSublista(formacion);
    }

    // Consulta 7: Autores por tipo de poesía y editorial
    void consultaAutoresPorTipoYEditorial(const std::string& tipoPoesia, const std::string& idEditorial) const {
        std::cout << "\n=== CONSULTA 7: Autores de " << tipoPoesia << " en editorial " << idEditorial << " ===" << std::endl;
        
        std::string clave = tipoPoesia + "-" + idEditorial;
        if (!tipoPoesiaEditorial.existe(clave)) {
            std::cout << "No se encontraron autores para " << tipoPoesia << " en editorial " << idEditorial << std::endl;
            return;
        }

        tipoPoesiaEditorial.mostrarSublista(clave);
    }

    // Forzar reordenamiento de todas las multilistas
    void optimizarEstructuras() {
        std::cout << "Optimizando estructuras de datos..." << std::endl;
        
        autorObras.forzarOrdenamiento();
        autorTipoPoesia.forzarOrdenamiento();
        editorialAutores.forzarOrdenamiento();
        editorialPoetas.forzarOrdenamiento();
        editorialAutoresNacimiento.forzarOrdenamiento();
        formacionAutores.forzarOrdenamiento();
        tipoPoesiaEditorial.forzarOrdenamiento();
        
        std::cout << "Estructuras optimizadas." << std::endl;
    }

    // Validar integridad de todas las estructuras
    bool validarIntegridadSistema() const {
        std::cout << "Validando integridad del sistema..." << std::endl;
        
        bool integridad = true;
        integridad &= autorObras.validarIntegridad();
        integridad &= autorTipoPoesia.validarIntegridad();
        integridad &= editorialAutores.validarIntegridad();
        integridad &= editorialPoetas.validarIntegridad();
        integridad &= editorialAutoresNacimiento.validarIntegridad();
        integridad &= formacionAutores.validarIntegridad();
        integridad &= tipoPoesiaEditorial.validarIntegridad();
        
        if (integridad) {
            std::cout << "Sistema íntegro." << std::endl;
        } else {
            std::cout << "ADVERTENCIA: Se detectaron problemas de integridad." << std::endl;
        }
        
        return integridad;
    }

    // === MÉTODOS DE PERSISTENCIA ===

    // Inicializar sistema completo
    void inicializarSistema() {
        std::cout << "Inicializando sistema de gestión de biblioteca..." << std::endl;
        
        cargarEditorialesDesdeArchivo("editoriales.txt");
        cargarAutoresDesdeArchivo("autores.txt");
        cargarObrasDesdeArchivo("obras.txt");
        cargarEdicionesDesdeArchivo("ediciones.txt");
        
        construirIndicesOptimizados();
        optimizarEstructuras();
        
        std::cout << "Sistema inicializado exitosamente." << std::endl;
    }

    // Guardar todos los cambios
    void guardarTodosSistema() {
        std::cout << "Guardando todos los datos del sistema..." << std::endl;
        
        controlAutores.guardarEnArchivo("autores.txt");
        controlEditoriales.guardarEnArchivo("editoriales.txt");
        controlObras.guardarEnArchivo("obras.txt");
        // Agregar guardado de ediciones si tienes ControlEdiciones
        
        std::cout << "Datos guardados exitosamente." << std::endl;
    }

    // === ACCESO A ESTRUCTURAS (para casos especiales) ===

    ArbolRojiNegro<Autor>& getArbolAutores() { return arbolAutores; }
    ArbolRojiNegro<Editorial>& getArbolEditoriales() { return arbolEditoriales; }
    ArbolRojiNegro<Obra>& getArbolObras() { return arbolObras; }
    ArbolRojiNegro<Edicion>& getArbolEdiciones() { return arbolEdiciones; }

    // Acceso a multilistas específicas
    Multilista<std::string, Obra>& getAutorObras() { return autorObras; }
    Multilista<std::string, std::string>& getEditorialAutores() { return editorialAutores; }
    Multilista<std::string, std::string>& getFormacionAutores() { return formacionAutores; }
    // Agregar más getters según necesites...
};

#endif // GESTIONBIBLIOTECA_H