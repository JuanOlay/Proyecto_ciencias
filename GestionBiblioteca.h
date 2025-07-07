#ifndef GESTIONBIBLIOTECA_H
#define GESTIONBIBLIOTECA_H

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

class GestionBiblioteca {
private:
    std::vector<Autor> autores;
    std::vector<Editorial> editoriales;
    std::vector<Obra> obras;
    std::vector<Edicion> ediciones;
    
    // Índices para optimizar consultas
    std::map<std::string, std::vector<int>> autorObras;        // ID autor -> índices de obras
    std::map<std::string, std::vector<int>> editorialEdiciones; // ID editorial -> índices de ediciones
    std::map<std::string, std::vector<int>> obraEdiciones;     // nombre obra -> índices de ediciones
    
    // Métodos auxiliares
    int calcularEdad(const std::string& fechaNacimiento) const {
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
        if (fecha.empty()) return 0;
        
        size_t pos = fecha.find_last_of("/-");
        if (pos != std::string::npos && pos + 1 < fecha.length()) {
            std::string anioStr = fecha.substr(pos + 1);
            return std::stoi(anioStr);
        }
        return 0;
    }
    
    std::string obtenerNombreEditorial(const std::string& idEditorial) const {
        for (const auto& editorial : editoriales) {
            if (editorial.id == idEditorial) {
                return editorial.nombre;
            }
        }
        return "Editorial no encontrada";
    }
    
    std::string obtenerNombreAutor(const std::string& idAutor) const {
        for (const auto& autor : autores) {
            if (autor.id == idAutor) {
                return autor.nombre + " " + autor.apellido;
            }
        }
        return "Autor no encontrado";
    }
    
    Autor* obtenerAutorPorId(const std::string& idAutor) {
        for (auto& autor : autores) {
            if (autor.id == idAutor) {
                return &autor;
            }
        }
        return nullptr;
    }
    
    Editorial* obtenerEditorialPorId(const std::string& idEditorial) {
        for (auto& editorial : editoriales) {
            if (editorial.id == idEditorial) {
                return &editorial;
            }
        }
        return nullptr;
    }
    
    void construirIndices() {
        // Limpiar índices existentes
        autorObras.clear();
        editorialEdiciones.clear();
        obraEdiciones.clear();
        
        // Construir índice autor-obras
        for (size_t i = 0; i < obras.size(); ++i) {
            autorObras[obras[i].idAutor].push_back(i);
        }
        
        // Construir índice editorial-ediciones
        for (size_t i = 0; i < ediciones.size(); ++i) {
            editorialEdiciones[ediciones[i].idEditorial].push_back(i);
        }
        
        // Construir índice obra-ediciones
        for (size_t i = 0; i < ediciones.size(); ++i) {
            obraEdiciones[ediciones[i].idObra].push_back(i);
        }
    }
    
    void guardarArchivo(const std::string& archivo, const std::string& tipo) {
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
    
    // Controladores para compatibilidad con el menú
    class ControlAutores {
    private:
        std::vector<Autor>& autores;
        
    public:
        ControlAutores(std::vector<Autor>& a) : autores(a) {}
        
        void agregar(const Autor& autor) {
            autores.push_back(autor);
        }
        
        void mostrarTodos() {
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
            for (auto& autor : autores) {
                if (autor.id == id) {
                    return &autor;
                }
            }
            return nullptr;
        }
        
        void eliminarPorID(const std::string& id, const std::string& archivo) {
            autores.erase(std::remove_if(autores.begin(), autores.end(),
                         [&id](const Autor& a) { return a.id == id; }), autores.end());
            std::cout << "Autor eliminado.\n";
        }
    };
    
    class ControlEditoriales {
    private:
        std::vector<Editorial>& editoriales;
        
    public:
        ControlEditoriales(std::vector<Editorial>& e) : editoriales(e) {}
        
        void agregar(const Editorial& editorial) {
            editoriales.push_back(editorial);
        }
        
        void mostrarTodos() {
            for (const auto& editorial : editoriales) {
                std::cout << "ID: " << editorial.id << ", Nombre: " << editorial.nombre
                         << ", Ciudad: " << editorial.ciudadPrincipal << ", País: " << editorial.paisPrincipal << std::endl;
            }
        }
        
        Editorial* buscarPorID(const std::string& id) {
            for (auto& editorial : editoriales) {
                if (editorial.id == id) {
                    return &editorial;
                }
            }
            return nullptr;
        }
        
        void eliminarPorID(const std::string& id, const std::string& archivo) {
            editoriales.erase(std::remove_if(editoriales.begin(), editoriales.end(),
                             [&id](const Editorial& e) { return e.id == id; }), editoriales.end());
            std::cout << "Editorial eliminada.\n";
        }
    };
    
    class ControlObras {
    private:
        std::vector<Obra>& obras;
        
    public:
        ControlObras(std::vector<Obra>& o) : obras(o) {}
        
        void agregar(const Obra& obra) {
            obras.push_back(obra);
        }
        
        void mostrarTodos() {
            for (const auto& obra : obras) {
                std::cout << "Nombre: " << obra.nombre << ", Tipo: " << obra.tipoPoesia
                         << ", ID Autor: " << obra.idAutor << std::endl;
            }
        }
        
        void eliminarPorNombre(const std::string& nombre, const std::string& archivo) {
            obras.erase(std::remove_if(obras.begin(), obras.end(),
                       [&nombre](const Obra& o) { return o.nombre == nombre; }), obras.end());
            std::cout << "Obra eliminada.\n";
        }
    };
    
    class ControlEdiciones {
    private:
        std::vector<Edicion>& ediciones;
        
    public:
        ControlEdiciones(std::vector<Edicion>& e) : ediciones(e) {}
        
        void agregar(const Edicion& edicion) {
            ediciones.push_back(edicion);
        }
        
        void mostrarTodos() {
            for (const auto& edicion : ediciones) {
                std::cout << "Número: " << edicion.numeroEdicion << ", Fecha: " << edicion.fechaPublicacion
                         << ", ID Editorial: " << edicion.idEditorial << ", Ciudad: " << edicion.ciudadPublicacion
                         << ", ID Obra: " << edicion.idObra << std::endl;
            }
        }
        
        void eliminarPorNumero(int numero, const std::string& archivo) {
            ediciones.erase(std::remove_if(ediciones.begin(), ediciones.end(),
                           [numero](const Edicion& e) { return e.numeroEdicion == numero; }), ediciones.end());
            std::cout << "Edición eliminada.\n";
        }
    };
    
    // Getters para los controladores
    ControlAutores getControlAutores() { return ControlAutores(autores); }
    ControlEditoriales getControlEditoriales() { return ControlEditoriales(editoriales); }
    ControlObras getControlObras() { return ControlObras(obras); }
    ControlEdiciones getControlEdiciones() { return ControlEdiciones(ediciones); }
    
    // Métodos de inicialización del sistema
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
        construirIndices();
        std::cout << "Índices optimizados construidos.\n";
    }
    
    void optimizarEstructuras() {
        // Ordenar por ID para búsquedas más eficientes
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
        guardarArchivo("autores.txt", "autores");
        guardarArchivo("editoriales.txt", "editoriales");
        guardarArchivo("obras.txt", "obras");
        guardarArchivo("ediciones.txt", "ediciones");
        std::cout << "Todos los datos guardados correctamente.\n";
    }
    
    // Métodos de carga de datos
    void cargarAutores(const std::string& archivo) {
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
        std::cout << "=== CONSULTA 1: Obras por Editorial y Año ===" << std::endl;
        std::cout << "Autor: " << obtenerNombreAutor(idAutor) << std::endl;

		    // DEBUG: Verificar si el autor existe en el índice
    std::cout << "DEBUG: Buscando autor en índice..." << std::endl;
    if (autorObras.find(idAutor) == autorObras.end()) {
        std::cout << "DEBUG: Autor no encontrado en índice autorObras" << std::endl;
        return;
    }
    std::cout << "DEBUG: Autor encontrado, tiene " << autorObras[idAutor].size() << " obras" << std::endl;
    
    // DEBUG: Mostrar las obras del autor
    for (int idx : autorObras[idAutor]) {
        std::cout << "DEBUG: Obra[" << idx << "]: " << obras[idx].nombre << std::endl;
    }
        
        // Estructura: Editorial -> Año -> Contador de obras
        std::map<std::string, std::map<int, int>> resultado;
        
        // Buscar obras del autor
        if (autorObras.find(idAutor) != autorObras.end()) {
            for (int idx : autorObras[idAutor]) {
                const Obra& obra = obras[idx];
                
                // Buscar ediciones de esta obra
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
        
        // Mostrar resultados
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
    
    // Consulta 2: Obras de un autor por tipo de poesía
    void consultaObrasAutorPorTipoPoesia(const std::string& idAutor) {
        std::cout << "=== CONSULTA 2: Obras por Tipo de Poesía ===" << std::endl;
        std::cout << "Autor: " << obtenerNombreAutor(idAutor) << std::endl;
        
        // Estructura: Tipo -> Lista de obras con detalles
        std::map<std::string, std::vector<std::pair<std::string, std::vector<std::pair<std::string, int>>>>> resultado;
        
        if (autorObras.find(idAutor) != autorObras.end()) {
            for (int idx : autorObras[idAutor]) {
                const Obra& obra = obras[idx];
                std::vector<std::pair<std::string, int>> edicionesObra;
                
                // Buscar ediciones de esta obra
                if (obraEdiciones.find(obra.nombre) != obraEdiciones.end()) {
                    for (int edIdx : obraEdiciones[obra.nombre]) {
                        const Edicion& edicion = ediciones[edIdx];
                        edicionesObra.push_back({edicion.fechaPublicacion, edicion.numeroEdicion});
                    }
                }
                
                resultado[obra.tipoPoesia].push_back({obra.nombre, edicionesObra});
            }
        }
        
        // Mostrar resultados
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
        std::cout << "=== CONSULTA 3: Autores por Editorial ===" << std::endl;
        std::cout << "Editorial: " << obtenerNombreEditorial(idEditorial) << std::endl;
        
        // Estructura: Ciudad -> Año -> Lista de autores
        std::map<std::string, std::map<int, std::vector<std::string>>> resultado;
        std::set<std::string> autoresUnicos;
        
        if (editorialEdiciones.find(idEditorial) != editorialEdiciones.end()) {
            for (int edIdx : editorialEdiciones[idEditorial]) {
                const Edicion& edicion = ediciones[edIdx];
                
                // Buscar obra y autor
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
        
        // Mostrar resultados
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
    
    // Consulta 4: Editoriales con más de N poetas
    void consultaEditorialesConNPoetas(int numeroMinimo) {
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
    
    // Consulta 5: Autores por editorial clasificados por lugar de nacimiento
    void consultaAutoresPorEditorialNacimiento(const std::string& idEditorial) {
        std::cout << "=== CONSULTA 5: Autores por Editorial y Lugar de Nacimiento ===" << std::endl;
        std::cout << "Editorial: " << obtenerNombreEditorial(idEditorial) << std::endl;
        
        // Estructura: País -> Ciudad -> Sexo -> Contador
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
        
        // Mostrar resultados
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
        
        // Mostrar resultados
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
        std::cout << "=== CONSULTA 7: Autores por Tipo de Poesía y Editorial ===" << std::endl;
        std::cout << "Tipo de poesía: " << tipoPoesia << std::endl;
        std::cout << "Editorial: " << obtenerNombreEditorial(idEditorial) << std::endl;
        
        // Estructura: ID Autor -> Información del autor y sus ediciones
        std::map<std::string, std::pair<std::string, std::vector<std::string>>> autoresConEdiciones;
        
        // Buscar obras del tipo de poesía especificado
        for (const auto& obra : obras) {
            if (obra.tipoPoesia.find(tipoPoesia) != std::string::npos) {
                // Buscar ediciones de esta obra en la editorial especificada
                if (obraEdiciones.find(obra.nombre) != obraEdiciones.end()) {
                    for (int edIdx : obraEdiciones[obra.nombre]) {
                        const Edicion& edicion = ediciones[edIdx];
                        if (edicion.idEditorial == idEditorial) {
                        
                        // Obtener información del autor
                        std::string infoAutor = obtenerNombreAutor(obra.idAutor);
                        Autor* autor = obtenerAutorPorId(obra.idAutor);
                        
                        if (autor) {
                            std::string datosCompletos = infoAutor + 
                                                       " (Sexo: " + std::string(1, autor->sexo) + 
                                                       ", Nacimiento: " + autor->fechaNacimiento + 
                                                       ", " + autor->ciudadNacimiento + ", " + autor->paisNacimiento + 
                                                       ", Residencia: " + autor->ciudadResidencia + 
                                                       ", Formación: " + autor->formacionBase + ")";
                            
                            // Información de la edición
                            std::string infoEdicion = "Obra: " + obra.nombre + 
                                                    ", Edición #" + std::to_string(edicion.numeroEdicion) + 
                                                    ", Fecha: " + edicion.fechaPublicacion + 
                                                    ", Ciudad: " + edicion.ciudadPublicacion;
                            
                            // Si es la primera vez que vemos este autor, guardar sus datos
                            if (autoresConEdiciones.find(obra.idAutor) == autoresConEdiciones.end()) {
                                autoresConEdiciones[obra.idAutor] = {datosCompletos, {}};
                            }
                            
                            // Agregar información de la edición
                            autoresConEdiciones[obra.idAutor].second.push_back(infoEdicion);
                        }
                    }
                }
            }
        }
        
        // Mostrar resultados
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