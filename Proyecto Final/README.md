# Proyecto_ciencias



Proyecto_Libros/
├── main.cpp
├── clases/
│   ├── Autor.h
│   ├── Obra.h
│   ├── Edicion.h
│   └── Editorial.h
├── estructuras/
│   ├── Nodo.h
│   ├── ArbolAVL.h
│   ├── Lista.h
│   └── Multilista.h
├── sistema/
│   ├── SistemaLibros.h
│   ├── ManejadorArchivos.h
│   └── Menu.h
└── datos/
    ├── autores.txt
    ├── obras.txt
    ├── ediciones.txt
    └── editoriales.txt

### Tarjeta CRC - Clase ArbolAVL

**Clase:** `ArbolAVL<T>`  

**Colaboradores:**  
- `NodoAVL` (estructura interna de nodo AVL)

---

**Atributos principales:**  
- `raiz`: puntero al nodo raíz del árbol  
- `NodoAVL`: estructura con `dato`, `izquierdo`, `derecho`, `altura`

**Métodos públicos clave:**  
- `insertar(const T)`  
- `eliminar(const T)`  
- `buscar(const T) -> bool`  
- `mostrarInOrden() const`  
- `estaVacio() const -> bool`  
- `~ArbolAVL()` (libera memoria)

**Métodos privados importantes (no repetibles):**  
- `insertar(NodoAVL*, const T) -> NodoAVL*`  
- `eliminar(NodoAVL*, const T) -> NodoAVL*`  
- `buscar(NodoAVL*, const T) -> NodoAVL*`  
- `rotacionIzquierda / rotacionDerecha`  
- `altura / balance / encontrarMinimo / inOrden / liberar`

### Tarjeta CRC - Clase Lista

**Clase:** `Lista<T>` 

**Colaboradores:**  
- `Nodo<T>` (estructura de nodo enlazado)

---

**Atributos principales:**  
- `cabeza`: puntero al primer nodo  
- `cola`: puntero al último nodo  
- `tamano`: entero con el tamaño de la lista

**Métodos públicos clave:**  
- `insertarInicio(T)`  
- `insertarFinal(T)`  
- `eliminar(T)`  
- `buscar(T) -> T*`  
- `mostrar() const`  
- `getTamano() const -> int`  
- `estaVacia() const -> bool`  
- `~Lista()` (destructor)
### Tarjeta CRC - Clase Multilista

**Clase:** `Multilista<T>`  
**Responsabilidades:**  
- Gestionar una multilista doblemente enlazada  
- Insertar, eliminar y buscar nodos principales  
- Manejar sublistas en cada nodo  
- Mostrar estructura principal y subestructuras  

**Colaboradores:**  
- `Lista<T>` (sublistas de cada nodo)  
- `NodoMultilista<T>` (estructura interna del nodo con sublista)

---

**Atributos principales:**  
- `cabeza`: primer nodo de la multilista  
- `cola`: último nodo de la multilista  
- `tamano`: cantidad de nodos en la multilista

**Estructura interna:**  
- `NodoMultilista`: contiene `dato`, `anterior`, `siguiente`, `Lista<T>* sublista`

---

**Métodos clave:**  
- `insertarInicio(T)`  
- `insertarFinal(T)`  
- `eliminar(T) -> bool`  
- `insertarEnSublista(T nodo, T dato) -> bool`  
- `eliminarDeSublista(T nodo, T dato) -> bool`  
- `buscar(T) -> T*`  
- `buscarEnSublista(T nodo, T dato) -> bool`  
- `mostrar() const`  
- `mostrarSublista(T nodo) const`  
- `mostrarPrincipal() const`  
- `getTamano() const -> int`  
- `getTamanoSublista(T nodo) const -> int`  
- `estaVacia() const -> bool`  
- `sublistaEstaVacia(T nodo) const -> bool`
