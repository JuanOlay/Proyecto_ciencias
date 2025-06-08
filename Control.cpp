#include "Control.h"
#include <iostream>
using namespace std;

Control::Control() {
    
}

void Control::menuPrincipal() {
    cout << "Que desea realizar?" << endl;
    cout << "1) Numero total de obras de un autor" << endl;
    cout << "2) Listado de los nombres de las obras de un autor" << endl;
    cout << "3) Autores a los cuales les ha publicado una editorial" << endl;
    cout << "4) Cantidad de editoriales que le han publicado a un numero de poetas" << endl;
    cout << "5) Obtener el numero de hombres y mujeres a los cuales les ha publicado una editorial" << endl;
    cout << "6) Mostrar lista de autores en rango de edad" << endl;
    cout << "7) Mostrar listado de autores por tipo de poesia y editorial" << endl;
    cout << "8) Agregar libro" << endl;
    cout << "9) Eliminar libro" << endl;
    cout << "10) Modificar libro" << endl;
    cout << "11) Agregar autor" << endl;
    cout << "12) Eliminar autor" << endl;
    cout << "13) Modificar autor" << endl;
    cout << "14) Agregar editorial" << endl;
    cout << "15) Eliminar editorial" << endl;
    cout << "16) Modificar editorial" << endl;
    cout << "17) Agregar edicion" << endl;
    cout << "18) Eliminar edicion" << endl;
    cout << "19) Modificar edicion" << endl;
    cout << "0) Salir" << endl;
    cin >> rtaUsuario;

    switch (rtaUsuario) {
        case 1:
            // Numero total de obras de un autor
            break;
        case 2:
            //Listado de los nombres de las obras de un autor
            break;
        case 3:
            // Autores a los cuales les ha publicado una editorial
            break;
        case 4:
            // Cantidad de editoriales que le han publicado a un numero de poetas
            break;
        case 5:
            // Obtener el numero de hombres y mujeres a los cuales les ha publicado una editorial
            break;
        case 6:
            // Mostrar lista de autores en rango de edad
            break;
        case 7:
            // Mostrar listado de autores por tipo de poesia y editorial
            break;
        case 8:
            // Agregar libro
            break;
        case 9:
            // Eliminar libro
            break;
        case 10:
            menuModificarLibro();
            break;
        case 11:
            // Agregar autor
            break;
        case 12:
            // Eliminar autor
            break;
        case 13:
            menuModificarAutor();
            break;
        case 14:
            // Agregar editorial
            break;
        case 15:
            // Eliminar editorial
            break;
        case 16:
            menuModificarEditorial();
            break;
        case 17:
            // Agregar edicion
            break;
        case 18:
            // Eliminar edicion
            break;
        case 19:
            // Modificar edicion
            break;    
        case 0:
            cout << "Saliendo..." << endl;
            exit(0);
        default:
            cout << "Opcion invalida, intenta de nuevo." << endl;
            menuPrincipal();
            break;
    }
}

void Control::menuModificarLibro() {
    cout << "Que informacion desea modificar?" << endl;
    cout << "1) Nombre\n2) Tipo\n3) Autor\n";
    cin >> rtaUsuario;

    switch (rtaUsuario) {
        case 1:
            
            break;
        case 2:

            break;
        case 3:

            break;
        default:
            cout << "Opcion invalida, intenta de nuevo." << endl;
            menuModificarLibro();
            break;
    }
}

void Control::menuModificarAutor(){
    cout << "Que informacion desea modificar?" << endl;
    cout << "1) Id \n 2) Nombre \n 3) Apellido\n";
    cout << "4) Sexo \n 5) Fecha de nacimiento \n 6) Ciudad de nacimiento\n";
    cout << "7) Pais de nacimiento \n 8) Ciudad de residencia \n 9) formacionBase\n";
    cout << "10) Anio de inicio en la literatura \n 8) Anio de publicacion de la primera obra \n";
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
    case 8:
        /* code */
        break;
    case 9:
        /* code */
        break;
    case 10:
        /* code */
        break;
    default:
        cout << "Opcion invalida, intenta de nuevo." << endl;
        menuModificarAutor();  
        break;
    }
}

void Control::menuModificarEditorial(){
    cout << "Que informacion desea modificar?" << endl;
    cout << "1) Id de la editorial \n 2) nombre de la editorial\n";
    cout << "3) Ciudad de la oficina principal \n 4) Pais de la oficina principal\n";
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
        
    default:
        cout << "Opcion invalida, intenta de nuevo." << endl;
        menuModificarEditorial();
        break;
    }
}

void Control::menuModificarEdicion(){
    cout << "Que información desea modificar?" << endl;
    cout << "1) Numero de la edicion \n 2) Fecha de publicacion\n";
    cout << "1) Id de la editorial \n 2) Ciudad de publicacion\n";
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
    default:
        cout << "Opcion invalida, intenta de nuevo." << endl;
        menuModificarEdicion();
        break;
    }
}