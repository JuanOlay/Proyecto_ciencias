#include <iostream>
#include <string>

using namespace std;

struct Libro
{
    string nombreDocumento;
    string tipoPoesia;
    int idAutor;
    //Listado autores
};

struct Edicion
{
    int numeroEdicion;
    int fechaPublicacion;
    int idEditorial;
    string ciudadPublicacion;
};

struct autor
{
    int idAutor;
    string nombre;
    string apellido;
    string sexo;
    int fechaNacimiento;
    string ciudadNacimiento;
    string paisNacimiento;
    string ciudadResiencia;
    string formacionBase;
    int anioInicioLiteratura;
    int anioPublicacionPrimeraObra;
};

struct editorial
{
    int idEditorial;
    string nombreEditorial;
    string ciudadOficinaP;
    string paisOficinaP;
};

void menu(){
    cout << "Que desea realizar?" << endl;
    cout << "1) Numero total de obras de un autor" << endl;
    cout << "2) Listado de los nombres de las obras de un autor" << endl;
    cout << "3) Autores a los cuales les ha publicado una editorial" << endl;
    cout << "4) Cantidad de editoriales que le han publicado a un numero de poetas" << endl;
    cout << "5) Obtener el numero de hombres y mujeres a los cuales les ha publicado una editorial" << endl;
    cout << "6) Mostrar lista de autores en rango de edad" << endl;
    cout << "7) Mostrar listado de autores por tipo de poesia y editorial"  << endl;
    cout << "0) Salir " << endl;
    int rtaUsuario;
    cin >> rtaUsuario;
    switch (rtaUsuario)
    {
    case 1:
        /* code */
        break;
    case 2:
        /* code */
        break;
    case 3:
        /* code */
        break;
    case 4:
        /* code */
        break;
    case 5:
        /* code */
        break;
    case 6:
        /* code */
        break;
    case 7:
        /* code */
        break;
    case 0:
        cout << "Saliendo.....";
        exit(0);
        break;
    
    default:
        cout << "Error, opcion no valida" << endl;
        menu();
        break;
    }
}

int main(){
    menu();
}