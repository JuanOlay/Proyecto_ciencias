/*
Archivo: lotest.cpp
Propósito: Probar funciones de Lista simple sin multilistas
Autores:
Juan Felipe Guevara Olaya jfguevarao@udistrital.edu.co
*/

#include <iostream>
#include "../estructuras/Lista.h"

struct Obra {
    std::string nombre;

    // Constructor por conveniencia
    Obra(std::string n) : nombre(n) {}

    // Comparadores necesarios para Lista y AVL
    bool operator==(const Obra& otra) const {
        return nombre == otra.nombre;
    }

    bool operator!=(const Obra& otra) const {
        return !(*this == otra);
    }

    bool operator>(const Obra& otra) const {
        return nombre > otra.nombre;
    }

    // Opcional, para mostrar
    friend std::ostream& operator<<(std::ostream& os, const Obra& o) {
        return os << o.nombre;
    }
};

// Clase Obra para pruebas básicas
class Obra {
public:
    std::string nombre;
    std::string tipoPoesia;
    int idAutor;

    Obra() {}

    Obra(std::string nombre, std::string tipoPoesia, int idAutor) {
        this->nombre = nombre;
        this->tipoPoesia = tipoPoesia;
        this->idAutor = idAutor;
    }

    bool operator==(const Obra& otra) const {
        return nombre == otra.nombre && tipoPoesia == otra.tipoPoesia && idAutor == otra.idAutor;
    }

    bool operator<(const Obra& otra) const {
        return nombre < otra.nombre;
    }

    friend std::ostream& operator<<(std::ostream& os, const Obra& o) {
        os << "[Obra: " << o.nombre << ", Tipo: " << o.tipoPoesia << ", ID Autor: " << o.idAutor << "]";
        return os;
    }
};

int main() {
    Lista<Obra> lista;

    Obra o1("Cantos de vida", "soneto", 101);
    Obra o2("Versos libres", "verso libre", 102);
    Obra o3("Pájaros del alma", "haiku", 101);
    Obra o4("Sombras eternas", "romance", 103);

    std::cout << "Insertando obras...\n";
    lista.insertarInicio(o1);
    lista.insertarFinal(o2);
    lista.insertarFinal(o3);
    lista.insertarInicio(o4);

    std::cout << "\nMostrando lista en orden de inserción:\n";
    lista.mostrar();

    std::cout << "\nMostrando lista ordenada (AVL):\n";
    lista.mostrarOrdenado();

    std::cout << "\nBuscando obra 'Versos libres'...\n";
    if (lista.buscar(o2)) {
        std::cout << "Obra encontrada.\n";
    } else {
        std::cout << "Obra no encontrada.\n";
    }

    std::cout << "\nEliminando 'Cantos de vida'...\n";
    lista.eliminar(o1);
    lista.mostrar();

    std::cout << "\nTamaño actual de la lista: " << lista.getTamano() << "\n";

    return 0;
}
