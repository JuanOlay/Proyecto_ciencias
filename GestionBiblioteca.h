#ifndef GESTIONBIBLIOTECA_H
#define GESTIONBIBLIOTECA_H

#include "ArbolRojiNegro.h"
#include "Multilista.h"
#include "Entidades.h"
#include "ManejadorArchivos.h"
#include "ControlAutores.h"
#include "ControlEditoriales.h"
#include "ControlObras.h"
#include "ControlEdiciones.h"
#include <sstream>
#include <map>
#include <vector>
#include <string>

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

		ControlEdiciones controlEdiciones;
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
		void buscarEdicionesObra(
		    std::string& fechaPublicacion,
		    std::string& idEditorial,
		    int& numeroEdicion,
		    const std::string& idObra) const {
			// Implementar búsqueda en arbolEdiciones
			// Esta es una implementación simplificada
			fechaPublicacion = "";
			idEditorial = "";
			numeroEdicion = 0;
		}
		// Método auxiliar para obtener información completa de una obra
		bool obtenerInfoObra(const std::string& nombreObra, std::string& idAutor,
		                     std::string& tipoPoesia, std::string& fechaPublicacion,
		                     std::string& idEditorial, int& numeroEdicion) const {

			// Buscar la obra en el árbol
			std::queue<Obra> obras = arbolObras.recorridoInOrden();
			while (!obras.empty()) {
				Obra obra = obras.front();
				obras.pop();

				if (obra.nombre == nombreObra) {
					idAutor = obra.idAutor;
					tipoPoesia = obra.tipoPoesia;

					// Buscar la edición correspondiente usando obra.nombre
					std::queue<Edicion> ediciones = arbolEdiciones.recorridoInOrden();
					while (!ediciones.empty()) {
						Edicion edicion = ediciones.front();
						ediciones.pop();

						if (edicion.idObra == obra.nombre) {  // CORREGIDO: usar obra.nombre
							fechaPublicacion = edicion.fechaPublicacion;
							idEditorial = edicion.idEditorial;
							numeroEdicion = edicion.numeroEdicion;
							return true;
						}
					}
					return false;
				}
			}
			return false;
		}

// Método auxiliar para obtener información del autor
		bool obtenerInfoAutor(const std::string& idAutor, std::string& nombre,
		                      std::string& ciudadResidencia, std::string& paisNacimiento,
		                      std::string& ciudadNacimiento, std::string& fechaNacimiento,
		                      std::string& formacionBase, int& anioInicio) const {

			std::queue<Autor> autores = arbolAutores.recorridoInOrden();
			while (!autores.empty()) {
				Autor autor = autores.front();
				autores.pop();

				if (autor.id == idAutor) {
					nombre = autor.nombre;
					ciudadResidencia = autor.ciudadResidencia;
					paisNacimiento = autor.paisNacimiento;
					ciudadNacimiento = autor.ciudadNacimiento;
					fechaNacimiento = autor.fechaNacimiento;
					formacionBase = autor.formacionBase;
					anioInicio = autor.anioInicioLiteratura;
					return true;
				}
			}
			return false;
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
		ControlAutores& getControlAutores() {
			return controlAutores;
		}
		ControlEditoriales& getControlEditoriales() {
			return controlEditoriales;
		}
		ControlObras& getControlObras() {
			return controlObras;
		}

		ControlEdiciones& getControlEdiciones() {
			return controlEdiciones;
		}

		// === MÉTODOS DE CARGA OPTIMIZADOS ===

		void cargarAutoresDesdeArchivo(const std::string& ruta) {
			ManejadorArchivos::cargarAutores(ruta, arbolAutores, formacionAutores);
			Lista<Autor> listaAutores;
			ManejadorArchivos::cargarAutores(ruta, listaAutores, formacionAutores);
			controlAutores.setAutores(listaAutores);
			std::cout << "Autores cargados. Construyendo indices optimizados..." << std::endl;
		}

		void cargarEditorialesDesdeArchivo(const std::string& ruta) {
			ManejadorArchivos::cargarEditoriales(ruta, arbolEditoriales);
			Lista<Editorial> listaEditoriales;
			ManejadorArchivos::cargarEditoriales(ruta, listaEditoriales);
			controlEditoriales.setEditoriales(listaEditoriales);
			std::cout << "Editoriales cargadas." << std::endl;
		}

		void cargarObrasDesdeArchivo(const std::string& ruta) {
			ManejadorArchivos::cargarObras(ruta, arbolObras, autorObras);
			Lista<Obra> listaObras;
			ManejadorArchivos::cargarObras(ruta, listaObras, autorObras);
			controlObras.setObras(listaObras);
			std::cout << "Obras cargadas. Construyendo indices optimizados..." << std::endl;
		}

		void cargarEdicionesDesdeArchivo(const std::string& ruta) {
			ManejadorArchivos::cargarEdiciones(ruta, arbolEdiciones, editorialAnios);
			Lista<Edicion> listaEdiciones;
			ManejadorArchivos::cargarEdiciones(ruta, listaEdiciones, editorialAnios);
			controlEdiciones.setEdiciones(listaEdiciones);
			std::cout << "Ediciones cargadas." << std::endl;
		}

		// === CONSTRUCCIÓN DE ÍNDICES OPTIMIZADOS ===

		void construirIndicesOptimizados() {
			std::cout << "Construyendo indices optimizados para consultas..." << std::endl;

			construirIndiceConsulta1();
			construirIndiceConsulta2();
			construirIndiceConsulta3();
			construirIndiceConsulta4();
			construirIndiceConsulta5();
			construirIndiceConsulta6();
			construirIndiceConsulta7();

			std::cout << "Indices construidos exitosamente." << std::endl;
		}
		void construirIndiceConsulta1() {
			std::cout << "Construyendo indice para consulta 1..." << std::endl;

			// Recorrer todas las obras y agrupar por autor
			std::queue<Obra> obras = arbolObras.recorridoInOrden();
			while (!obras.empty()) {
				Obra obra = obras.front();
				obras.pop();

				std::string idAutor = obra.idAutor;

				// Crear nodo principal si no existe
				if (!autorObras.existe(idAutor)) {
					autorObras.insertar(idAutor);
				}

				// Insertar la obra completa en la sublista
				autorObras.insertarEnSublista(idAutor, obra);
			}
		}

		void construirIndiceConsulta2() {
			std::cout << "Construyendo indice para consulta 2..." << std::endl;

			// Recorrer todas las obras
			std::queue<Obra> obras = arbolObras.recorridoInOrden();
			while (!obras.empty()) {
				Obra obra = obras.front();
				obras.pop();

				std::string idAutor = obra.idAutor;
				std::string tipoPoesia = obra.tipoPoesia;
				std::string nombreObra = obra.nombre;

				// Buscar información de la edición usando obra.nombre
				std::queue<Edicion> ediciones = arbolEdiciones.recorridoInOrden();
				while (!ediciones.empty()) {
					Edicion edicion = ediciones.front();
					ediciones.pop();

					if (edicion.idObra == obra.nombre) {  // CORREGIDO: usar obra.nombre
						std::string fechaPublicacion = edicion.fechaPublicacion;
						int numeroEdicion = edicion.numeroEdicion;

						std::string valorSublista = tipoPoesia + "-" + nombreObra + "-" +
						                            fechaPublicacion + "-" + std::to_string(numeroEdicion);

						// Crear nodo principal si no existe
						if (!autorTipoPoesia.existe(idAutor)) {
							autorTipoPoesia.insertar(idAutor);
						}

						autorTipoPoesia.insertarEnSublista(idAutor, valorSublista);
						break;  // Solo necesitamos una edición por obra
					}
				}
			}
		}

		void construirIndiceConsulta3() {
			std::cout << "Construyendo indice para consulta 3..." << std::endl;

			// Recorrer todas las ediciones
			std::queue<Edicion> ediciones = arbolEdiciones.recorridoInOrden();
			while (!ediciones.empty()) {
				Edicion edicion = ediciones.front();
				ediciones.pop();

				std::string idEditorial = edicion.idEditorial;
				std::string idObra = edicion.idObra;

				// Buscar el autor de esta obra usando idObra
				std::queue<Obra> obras = arbolObras.recorridoInOrden();
				while (!obras.empty()) {
					Obra obra = obras.front();
					obras.pop();

					if (obra.nombre == idObra) {  // CORREGIDO: usar obra.nombre
						std::string idAutor = obra.idAutor;

						// Obtener información del autor
						std::string nombre, ciudadResidencia, paisNacimiento, ciudadNacimiento,
						    fechaNacimiento, formacionBase;
						int anioInicio;

						if (obtenerInfoAutor(idAutor, nombre, ciudadResidencia, paisNacimiento,
						                     ciudadNacimiento, fechaNacimiento, formacionBase, anioInicio)) {

							std::string valorSublista = ciudadResidencia + "-" +
							                            std::to_string(anioInicio) + "-" + idAutor;

							// Crear nodo principal si no existe
							if (!editorialAutores.existe(idEditorial)) {
								editorialAutores.insertar(idEditorial);
							}

							// Verificar si ya existe para evitar duplicados
							if (!editorialAutores.buscarEnSublista(idEditorial, valorSublista)) {
								editorialAutores.insertarEnSublista(idEditorial, valorSublista);
							}
						}
						break;
					}
				}
			}
		}

		void construirIndiceConsulta4() {
			std::cout << "Construyendo indice para consulta 4..." << std::endl;

			// Recorrer todas las ediciones
			std::queue<Edicion> ediciones = arbolEdiciones.recorridoInOrden();
			while (!ediciones.empty()) {
				Edicion edicion = ediciones.front();
				ediciones.pop();

				std::string idEditorial = edicion.idEditorial;
				std::string idObra = edicion.idObra;

				// Buscar el autor de esta obra
				std::queue<Obra> obras = arbolObras.recorridoInOrden();
				while (!obras.empty()) {
					Obra obra = obras.front();
					obras.pop();

					if (obra.nombre == idObra) {  // CORREGIDO: usar obra.nombre
						std::string idAutor = obra.idAutor;

						// Crear nodo principal si no existe
						if (!editorialPoetas.existe(idEditorial)) {
							editorialPoetas.insertar(idEditorial);
						}

						// Agregar autor si no existe ya (evitar duplicados)
						if (!editorialPoetas.buscarEnSublista(idEditorial, idAutor)) {
							editorialPoetas.insertarEnSublista(idEditorial, idAutor);
						}
						break;
					}
				}
			}
		}

		void construirIndiceConsulta5() {
			std::cout << "Construyendo indice para consulta 5..." << std::endl;

			std::queue<Edicion> ediciones = arbolEdiciones.recorridoInOrden();
			while (!ediciones.empty()) {
				Edicion edicion = ediciones.front();
				ediciones.pop();

				std::string idEditorial = edicion.idEditorial;
				std::string idObra = edicion.idObra;

				// Buscar el autor de esta obra
				std::queue<Obra> obras = arbolObras.recorridoInOrden();
				while (!obras.empty()) {
					Obra obra = obras.front();
					obras.pop();

					if (obra.nombre == idObra) {  // CORREGIDO: usar obra.nombre
						std::string idAutor = obra.idAutor;

						// Obtener información del autor
						std::string nombre, ciudadResidencia, paisNacimiento, ciudadNacimiento,
						    fechaNacimiento, formacionBase;
						int anioInicio;

						if (obtenerInfoAutor(idAutor, nombre, ciudadResidencia, paisNacimiento,
						                     ciudadNacimiento, fechaNacimiento, formacionBase, anioInicio)) {

							std::string valorSublista = paisNacimiento + "-" + ciudadNacimiento + "-" + idAutor;

							// Crear nodo principal si no existe
							if (!editorialAutoresNacimiento.existe(idEditorial)) {
								editorialAutoresNacimiento.insertar(idEditorial);
							}

							// Verificar si ya existe para evitar duplicados
							if (!editorialAutoresNacimiento.buscarEnSublista(idEditorial, valorSublista)) {
								editorialAutoresNacimiento.insertarEnSublista(idEditorial, valorSublista);
							}
						}
						break;
					}
				}
			}
		}

		void construirIndiceConsulta6() {
			std::cout << "Construyendo indice para consulta 6..." << std::endl;

			// El índice formacionAutores ya se construye en ManejadorArchivos
			// Aquí agregamos información adicional de edad
			std::queue<Autor> autores = arbolAutores.recorridoInOrden();
			while (!autores.empty()) {
				Autor autor = autores.front();
				autores.pop();

				std::string formacion = autor.formacionBase;
				std::string idAutor = autor.id;
				int edad = calcularEdad(autor.fechaNacimiento);
				int anioInicio = autor.anioInicioLiteratura;

				std::string valorSublista = std::to_string(edad) + "-" +
				                            std::to_string(anioInicio) + "-" + idAutor;

				// Crear nodo principal si no existe
				if (!formacionAutores.existe(formacion)) {
					formacionAutores.insertar(formacion);
				}

				formacionAutores.insertarEnSublista(formacion, valorSublista);
			}
		}

		void construirIndiceConsulta7() {
			std::cout << "Construyendo indice para consulta 7..." << std::endl;

			// Recorrer todas las obras
			std::queue<Obra> obras = arbolObras.recorridoInOrden();
			while (!obras.empty()) {
				Obra obra = obras.front();
				obras.pop();

				std::string idAutor = obra.idAutor;
				std::string tipoPoesia = obra.tipoPoesia;
				std::string idObra = obra.nombre;  // CORREGIDO: usar obra.nombre

				// Buscar la editorial de esta obra
				std::queue<Edicion> ediciones = arbolEdiciones.recorridoInOrden();
				while (!ediciones.empty()) {
					Edicion edicion = ediciones.front();
					ediciones.pop();

					if (edicion.idObra == idObra) {  // Ahora idObra está correctamente definido
						std::string idEditorial = edicion.idEditorial;
						std::string clave = tipoPoesia + "-" + idEditorial;

						// Crear nodo principal si no existe
						if (!tipoPoesiaEditorial.existe(clave)) {
							tipoPoesiaEditorial.insertar(clave);
						}

						// Agregar autor si no existe ya (evitar duplicados)
						if (!tipoPoesiaEditorial.buscarEnSublista(clave, idAutor)) {
							tipoPoesiaEditorial.insertarEnSublista(clave, idAutor);
						}
						break;
					}
				}
			}
		}

		// === MÉTODOS DE CONSULTA OPTIMIZADOS ===

		// Consulta 1: Número total de obras de un autor, clasificadas por editorial y año
		void consultaObrasAutorPorEditorialAnio(const std::string& idAutor) const {
			std::cout << "\n=== CONSULTA 1: Obras del autor " << idAutor << " por editorial y anio ===" << std::endl;

			if (!autorObras.existe(idAutor)) {
				std::cout << "No se encontraron obras para el autor " << idAutor << std::endl;
				return;
			}

			// Obtener información del autor
			std::string nombreAutor, ciudadResidencia, paisNacimiento, ciudadNacimiento,
			    fechaNacimiento, formacionBase;
			int anioInicio;

			if (obtenerInfoAutor(idAutor, nombreAutor, ciudadResidencia, paisNacimiento,
			                     ciudadNacimiento, fechaNacimiento, formacionBase, anioInicio)) {
				std::cout << "Autor: " << nombreAutor << " (ID: " << idAutor << ")" << std::endl;
			}

			// Contar obras y organizarlas por editorial y año
			std::map<std::string, std::map<int, std::vector<std::string>>> editorialAnioObras;
			int totalObras = 0;

			// Recorrer todas las obras del autor
			std::queue<Obra> obras = arbolObras.recorridoInOrden();
			while (!obras.empty()) {
				Obra obra = obras.front();
				obras.pop();

				if (obra.idAutor == idAutor) {
					totalObras++;

					// Buscar edición correspondiente
					std::queue<Edicion> ediciones = arbolEdiciones.recorridoInOrden();
					while (!ediciones.empty()) {
						Edicion edicion = ediciones.front();
						ediciones.pop();

						if (edicion.idObra == obra.nombre) {
							std::string idEditorial = edicion.idEditorial;
							int anio = extraerAnio(edicion.fechaPublicacion);

							editorialAnioObras[idEditorial][anio].push_back(obra.nombre);
							break;
						}
					}
				}
			}

			std::cout << "\nTotal de obras: " << totalObras << std::endl;
			std::cout << "\nObras clasificadas por editorial y año:" << std::endl;
			std::cout << "----------------------------------------" << std::endl;

			// Mostrar organizadamente
			for (const auto& editorial : editorialAnioObras) {
				std::cout << "\nEditorial: " << editorial.first << std::endl;
				for (const auto& anio : editorial.second) {
					std::cout << "  Año " << anio.first << ":" << std::endl;
					for (const auto& obra : anio.second) {
						std::cout << "    - " << obra << std::endl;
					}
				}
			}
		}


		// Consulta 2: Obras de un autor por tipo de poesía
		void consultaObrasAutorPorTipoPoesia(const std::string& idAutor) const {
			std::cout << "\n=== CONSULTA 2: Obras del autor " << idAutor << " por tipo de poesia ===" << std::endl;

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

		void consultaEditorialesConNPoetas(int numeroMinimo) const {
			std::cout << "\n=== CONSULTA 4: Editoriales con mas de " << numeroMinimo << " poetas ===" << std::endl;

			if (editorialPoetas.estaVacia()) {
				std::cout << "No hay datos de poetas por editorial." << std::endl;
				return;
			}

			std::cout << "Editoriales que cumplen el criterio:" << std::endl;
			std::cout << "-----------------------------------" << std::endl;

			// Recorrer todas las editoriales y contar poetas
			std::queue<Editorial> editoriales = arbolEditoriales.recorridoInOrden();
			bool encontrado = false;

			while (!editoriales.empty()) {
				Editorial editorial = editoriales.front();
				editoriales.pop();

				std::string idEditorial = editorial.id;
				int cantidadPoetas = editorialPoetas.getTamanoSublista(idEditorial);

				if (cantidadPoetas > numeroMinimo) {
					std::cout << "Editorial: " << editorial.nombre
					          << " (ID: " << idEditorial << ")" << std::endl;
					std::cout << "Cantidad de poetas: " << cantidadPoetas << std::endl;
					std::cout << "Poetas: ";
					editorialPoetas.mostrarSublista(idEditorial);
					std::cout << std::endl;
					encontrado = true;
				}
			}

			if (!encontrado) {
				std::cout << "No se encontraron editoriales con más de " << numeroMinimo << " poetas." << std::endl;
			}
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

		void consultaAutoresPorFormacionYEdad(const std::string& formacion, int edadMin, int edadMax) const {
			std::cout << "\n=== CONSULTA 6: Autores con formacion " << formacion
			          << " entre " << edadMin << " y " << edadMax << " años ===" << std::endl;

			if (!formacionAutores.existe(formacion)) {
				std::cout << "No se encontraron autores con formación " << formacion << std::endl;
				return;
			}

			std::cout << "Autores que cumplen el criterio:" << std::endl;
			std::cout << "-------------------------------" << std::endl;

			bool encontrado = false;

			// Recorrer todos los autores con esa formación
			std::queue<Autor> autores = arbolAutores.recorridoInOrden();
			while (!autores.empty()) {
				Autor autor = autores.front();
				autores.pop();

				if (autor.formacionBase == formacion) {
					int edad = calcularEdad(autor.fechaNacimiento);

					if (edad >= edadMin && edad <= edadMax) {
						std::cout << "- " << autor.nombre << " (ID: " << autor.id
						          << ", Edad: " << edad << " años)" << std::endl;
						std::cout << "  Año inicio literatura: " << autor.anioInicioLiteratura << std::endl;
						encontrado = true;
					}
				}
			}

			if (!encontrado) {
				std::cout << "No se encontraron autores con formación " << formacion
				          << " entre " << edadMin << " y " << edadMax << " años." << std::endl;
			}
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
				std::cout << "Sistema integro." << std::endl;
			} else {
				std::cout << "ADVERTENCIA: Se detectaron problemas de integridad." << std::endl;
			}

			return integridad;
		}

		// === MÉTODOS DE PERSISTENCIA ===

		// Inicializar sistema completo
		void inicializarSistema() {
			std::cout << "Inicializando sistema de gestion de biblioteca..." << std::endl;

			cargarEditorialesDesdeArchivo("editoriales.txt");
			cargarAutoresDesdeArchivo("autores.txt");
			cargarObrasDesdeArchivo("obras.txt");
			cargarEdicionesDesdeArchivo("ediciones.txt");

			construirIndicesOptimizados();
			optimizarEstructuras();
		}

		// Guardar todos los cambios
		void guardarTodosSistema() {
			std::cout << "Guardando todos los datos del sistema..." << std::endl;

			controlAutores.guardarEnArchivo("autores.txt");
			controlEditoriales.guardarEnArchivo("editoriales.txt");
			controlObras.guardarEnArchivo("obras.txt");
			controlEdiciones.guardarEnArchivo("ediciones.txt");
			// Agregar guardado de ediciones si tienes ControlEdiciones

			std::cout << "Datos guardados exitosamente." << std::endl;
		}

		// === ACCESO A ESTRUCTURAS (para casos especiales) ===

		ArbolRojiNegro<Autor>& getArbolAutores() {
			return arbolAutores;
		}
		ArbolRojiNegro<Editorial>& getArbolEditoriales() {
			return arbolEditoriales;
		}
		ArbolRojiNegro<Obra>& getArbolObras() {
			return arbolObras;
		}
		ArbolRojiNegro<Edicion>& getArbolEdiciones() {
			return arbolEdiciones;
		}

		// Acceso a multilistas específicas
		Multilista<std::string, Obra>& getAutorObras() {
			return autorObras;
		}
		Multilista<std::string, std::string>& getEditorialAutores() {
			return editorialAutores;
		}
		Multilista<std::string, std::string>& getFormacionAutores() {
			return formacionAutores;
		}
		// Agregar más getters según necesites...
};

#endif // GESTIONBIBLIOTECA_H
