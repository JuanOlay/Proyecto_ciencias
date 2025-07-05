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
            menuAgregarLibro();
            break;
        case 9:
            // Eliminar libro
            break;
        case 10:
            menuEscogerLibro();
            break;
        case 11:
            menuAgregarAutor();
            break;
        case 12:
            // Eliminar autor
            break;
        case 13:
            menuEscogerAutorModificacion();
            break;
        case 14:
            menuAgregarEditorial();
            break;
        case 15:
            // Eliminar editorial
            break;
        case 16:
            menuEscogerEditorialModificacion();
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

void Control::menuAgregarLibro(){
    cout << "Digite el nombre del libro" << endl;
    cin >> rtaUsuarioStr;
    libro.nombre = rtaUsuarioStr;
    libro.tipoPoesia = menuTipoPoesia();
    libro.idAutor = menuEscogerAutorInsercion();
    cout << "Cuantas ediciones desea agregar?" << endl;
    cin >> rtaUsuario;
    for (int i = 0; i < rtaUsuario; i++)
    {
        menuAgregarEdicion();
    }
    libros.insertarFinal(libro);
    imprimirListaLibros(libros);
    imprimirListaAutores(autores);
    imprimirListaEditoriales(editoriales);
};

void Control::menuModificarLibro() {
    cout << "Que informacion desea modificar?" << endl;
    cout << "1) Nombre \n2) Tipo \n3) IdAutor \n4) Listado de las ediciones \n0) Volver\n";
    cin >> rtaUsuario;

    switch (rtaUsuario) {
        case 1:
            cout << "Ingrese el nuevo nombre" << endl;
            cin >> rtaUsuarioStr;
            break;
        case 2:
            menuTipoPoesia();
            break;
        case 3:
            menuEscogerAutorModificacion();
            break;
        case 4:
            menuModificacionListadoEdiciones();
            break;
        case 0:
            menuPrincipal();
            break;
        default:
            cout << "Opcion invalida, intenta de nuevo." << endl;
            menuModificarLibro();
            break;
    }
}

string Control::menuTipoPoesia(){
    cout << "Cual tipo de poesia desea?" << endl;
    cout << "1) Decima \n2) Soneto \n3) Himno\n";
    cout << "4) Haiku \n5) Romance \n6) Octava real\n";
    cout << "7) Lira \n8) Verso libre \n0) Volver \n";
    cin >> rtaUsuario;
    switch (rtaUsuario)
    {
    case 1:
        return "Decima";
        break;
    case 2:
        return "Soneto";
        break;
    case 3:
        return "Himno";
        break;
    case 4:
        return "Haiku";
        break;
    case 5:
        return "Romance";
        break;
    case 6:
        return "Octava real";
        break;
    case 7:
        return "Lira";
        break;
    case 8:
        return "Verso libre";
        break;
    case 0:
        menuModificarLibro();
        break;
    default:
        cout << "Opcion invalida, intenta de nuevo." << endl;
        menuTipoPoesia();
        break;
    }
}

void Control::menuAgregarAutor(){
    cout << "Digite el id del autor" << endl;
    cin >> rtaUsuario;
    autor.idAutor = rtaUsuario;
    cout << "Escriba el nombre del autor" << endl;
    cin >> rtaUsuarioStr;
    autor.nombre = rtaUsuarioStr;
    cout << "Escriba el apellido del autor" << endl;
    cin >> rtaUsuarioStr;
    autor.apellido = rtaUsuarioStr;
    autor.sexo = menuSeleccionarSexoAutorInsercion();
    cout << "Digite la fecha de nacimiento" << endl;
    cin >> rtaUsuario;
    autor.fechaNacimiento = rtaUsuario;
    cout << "Escriba la ciudad de nacimiento del autor" << endl;
    cin >> rtaUsuarioStr;
    autor.ciudadNacimiento = rtaUsuarioStr;
    cout << "Escriba el pais de nacimiento del autor" << endl;
    cin >> rtaUsuarioStr;
    autor.paisNacimiento = rtaUsuarioStr;
    cout << "Escriba la ciudad de residencia del autor" << endl;
    cin >> rtaUsuarioStr;
    autor.ciudadResidencia = rtaUsuarioStr;
    autor.formacionBase = menuSeleccionarFormacionAutorInsercion();
    cout << "Digite el anio de inicio en la literatura" << endl;
    cin >> rtaUsuario;
    autor.anioInicioLiteratura = rtaUsuario;
    cout << "Digite el anio de publicacion de la primera obra" << endl;
    cin >> rtaUsuario;
    autor.anioPublicacionPrimeraObra = rtaUsuario;
    autores.insertarFinal(autor);
    menuPrincipal();
}

void Control::menuModificarAutor(){
    cout << "Que informacion desea modificar?" << endl;
    cout << "1) Id \n2) Nombre \n3) Apellido\n";
    cout << "4) Sexo \n5) Fecha de nacimiento \n6) Ciudad de nacimiento\n";
    cout << "7) Pais de nacimiento \n8) Ciudad de residencia \n9) Formacion base\n";
    cout << "10) Anio de inicio en la literatura \n11) Anio de publicacion de la primera obra\n";
    cout << "0) Volver" << endl;
    cin >> rtaUsuario;
    switch (rtaUsuario)
    {
    case 1:
        cout << "Escriba el nuevo Id" << endl;
        cin >> rtaUsuario;
        menuPrincipal();
        break;
    case 2:
        cout << "Escriba el nombre del autor" << endl;
        cin >> rtaUsuarioStr;
        menuPrincipal();
        break;
    case 3:
        cout << "Escriba el apellido del autor" << endl;
        cin >> rtaUsuarioStr;
        menuPrincipal();
        break;
    case 4:
        menuSeleccionarSexoAutorModificacion();
        break;
    case 5:
        cout << "Digite la fecha de nacimiento" << endl;
        cin >> rtaUsuario;
        menuPrincipal();
        break;
    case 6:
        cout << "Escriba la ciudad de nacimiento" << endl;
        cin >> rtaUsuarioStr;
        menuPrincipal();
        break;
    case 7:
        cout << "Escriba el pais de nacimiento" << endl;
        cin >> rtaUsuarioStr;
        menuPrincipal();
        break;
    case 8:
        cout << "Escriba la ciudad de residencia" << endl;
        cin >> rtaUsuarioStr;
        menuPrincipal();
        break;
    case 9:
        menuSeleccionarFormacionAutorModificacion();
        break;
    case 10:
        cout << "Digite el anio de inicio en la literatura" << endl;
        cin >> rtaUsuario;
        menuPrincipal();
        break;
    case 11:
        cout << "Digite el anio de publicacion de la primera obra" << endl;
        cin >> rtaUsuario;
        menuPrincipal();
        break;
    case 0:
        menuPrincipal();
        break;
    default:
        cout << "Opcion invalida, intenta de nuevo." << endl;
        menuModificarAutor();  
        break;
    }
}

void Control::menuAgregarEditorial(){
    cout << "Digite el id de la editorial" << endl;
    cin >> rtaUsuario;
    editorial.idEditorial = rtaUsuario;
    cout << "Escriba el nombre de la editorial" << endl;
    cin >> rtaUsuarioStr;
    editorial.nombreEditorial = rtaUsuarioStr;
    cout << "Escriba la ciudad de la oficina principal" << endl;
    cin >> rtaUsuarioStr;
    editorial.ciudadOficinaP = rtaUsuarioStr;
    cout << "Escriba el pais de la oficina principal" << endl;
    cin >> rtaUsuarioStr;
    editorial.paisOficinaP = rtaUsuarioStr;
    editoriales.insertarFinal(editorial);
    menuPrincipal();
}

void Control::menuModificarEditorial(){
    cout << "Que informacion desea modificar?" << endl;
    cout << "1) Id de la editorial \n2) Nombre de la editorial\n";
    cout << "3) Ciudad de la oficina principal \n4) Pais de la oficina principal\n";
    cout << "0) Volver" << endl;
    cin >> rtaUsuario;
    switch (rtaUsuario)
    {
    case 1:
        cout << "Digite la nueva id" << endl;
        cin >> rtaUsuario;
        //code
        menuPrincipal();
        break;
    case 2:
        cout << "Escriba el nombre de la editorial" << endl;
        cin >> rtaUsuarioStr;
        menuPrincipal();
        break;
    case 3:
        cout << "Escriba la ciudad de la oficina principal" << endl;
        cin >> rtaUsuarioStr;
        menuPrincipal();
        break;
    case 4:
        cout << "Escriba el pais de la oficina principal" << endl;
        cin >> rtaUsuarioStr;
        menuPrincipal();
        break;
    case 0:
        menuPrincipal();
        break;
    default:
        cout << "Opcion invalida, intenta de nuevo." << endl;
        menuModificarEditorial();
        break;
    }
}

void Control::menuAgregarEdicion(){
    cout << "Ingrese el numero de la edicion" << endl;
    cin >> rtaUsuarioStr;
    edicion.numeroEdicion = rtaUsuarioStr;
    cout << "Ingrese la fecha de publicacion" << endl;
    cin >> rtaUsuario;
    edicion.fechaPublicacion = rtaUsuario;
    menuEscogerEditorialInsercion();
    cout << "Ingrese ciudad de publicacion" << endl;
    cin >> rtaUsuarioStr;
    edicion.ciudadPublicacion = rtaUsuarioStr;
    libro.ediciones.insertarFinal(edicion);
}

void Control::menuModificarEdicion(){
    cout << "Que informacion desea modificar?" << endl;
    cout << "1) Numero de la edicion \n2) Fecha de publicacion\n";
    cout << "3) Id de la editorial \n4) Ciudad de publicacion\n";
    cout << "0) Volver" << endl;
    cin >> rtaUsuario;
    switch (rtaUsuario)
    {
    case 1:
        cout << "Ingrese el numero de la edicion" << endl;
        cin >> rtaUsuario;
        break;
    case 2:
        cout << "Ingrese la fecha de publicacion" << endl;
        cin >> rtaUsuario;
        break;
    case 3:
        menuEscogerEditorialModificacion();
        break;
    case 4:
        cout << "Ingrese ciudad de publicacion" << endl;
        cin >> rtaUsuarioStr;
        break;
    case 0:
        menuModificacionListadoEdiciones();
        break;
    default:
        cout << "Opcion invalida, intenta de nuevo." << endl;
        menuModificarEdicion();
        break;
    }
}

void Control::menuEscogerLibro(){
    cout << "Escoja el libro que desea modificar" << endl;
    //Se muestra el listado de libros
    cin >> rtaUsuario;
    menuModificarLibro();
}

int Control::menuEscogerAutorInsercion(){
    cout << "Escoja el autor" << endl;
    imprimirListaAutores(autores);
    cin >> rtaUsuario;
    autor = autores.buscarPos(rtaUsuario);
    return autor.idAutor;
}

int Control::menuEscogerAutorModificacion(){
    cout << "Escoja el autor" << endl;
    imprimirListaAutores(autores);
    cin >> rtaUsuario;
    autor = autores.buscarPos(rtaUsuario);
    menuPrincipal();
    return autor.idAutor;
}

void Control::menuEscogerEditorialInsercion(){
    cout << "Escoja la editorial" << endl;
    imprimirListaEditoriales(editoriales);
    cin >> rtaUsuario;
    edicion.idEditorial = editoriales.buscarPos(rtaUsuario).idEditorial;    
}

void Control::menuEscogerEditorialModificacion(){
    cout << "Escoja la editorial" << endl;
    //Se muestra el listado de las editoriales
    cin >> rtaUsuario;
    menuModificarEditorial();
}

void Control::menuModificacionListadoEdiciones(){
    cout << "Que operacion desea hacerle al listado de ediciones" << endl;
    cout << "1) Insetar nueva edicion \n2) Eliminar edicion \n";
    cout << "3) Modificar edicion \n0) Volver \n";
    cin >> rtaUsuario;
    switch (rtaUsuario)
    {
    case 1:
        /* code */
        break;
    case 2:
        menuEscogerEdicionEliminacion();
        break;
    case 3:
        menuEscogerEdicionModificacion();
        break;
    case 0:
        menuModificarLibro();
        break;
    default:
        cout << "Opcion invalida, intenta de nuevo." << endl;
        menuModificacionListadoEdiciones();
        break;
    }
}

void Control::menuEscogerEdicionEliminacion(){
    cout << "Cual edicion desea eliminar?" << endl;
    //Se muestra el listado de ediciones de dicho libro
    cin >> rtaUsuario;
}

void Control::menuEscogerEdicionModificacion(){
    cout << "Cual edicion desea modificar?" << endl;
    //Se muestra el listado de ediciones de dicho libro
    cin >> rtaUsuario;
    menuModificarEdicion();
}

string Control::menuSeleccionarSexoAutorInsercion(){
    cout << "Seleccione el sexo del autor" << endl;
        cout << "1) Masculino \n2) Femenino \n";
        cin >> rtaUsuario;
        switch (rtaUsuario)
        {
        case 1:
            return "Masculino";
            break;
        case 2:
            return "Femenino";
            break;
        default:
            cout << "Opcion invalida, intenta de nuevo." << endl;
            menuSeleccionarSexoAutorInsercion();
            break;
        }
}

void Control::menuSeleccionarSexoAutorModificacion(){
    cout << "Seleccione el sexo del autor" << endl;
        cout << "1) Masculino \n2) Femenino \n0) Volver \n";
        cin >> rtaUsuario;
        switch (rtaUsuario)
        {
        case 1:
            /* code */
            menuPrincipal();
            break;
        case 2:
            //code
            menuPrincipal();
            break;
        case 0:
            //code
            menuModificarAutor();
            break;
        default:
            cout << "Opcion invalida, intenta de nuevo." << endl;
            menuSeleccionarSexoAutorModificacion();
            break;
        }
}

string Control::menuSeleccionarFormacionAutorInsercion(){
    cout << "Seleccione la formacion base del autor" << endl;
    cout << "1) Literatura \n2) Artes \n3) Ciencias sociales \n";
    cout << "4) Ingenierias \n5) Areas de la salud \n6) Jurisprudencia\n";
    cout << "7) Otros \n";
    cin >> rtaUsuario;
    switch (rtaUsuario)
    {
    case 1:
        return "Literatura";
        break;
    case 2:
        return "Artes";
        break;
    case 3:
        return "Ciencias sociales";
        break;
    case 4:
        return "Ingenierias";
        break;
    case 5:
        return "Areas de la salud";
        break;
    case 6:
        return "Jurisprudencia";
        break;
    case 7:
        cout << "Escriba cual es la formacion base" << endl;
        cin >> rtaUsuarioStr;
        return rtaUsuarioStr;
        break;
    default:
        cout << "Opcion invalida, intenta de nuevo." << endl;
        menuSeleccionarFormacionAutorInsercion();
        break;
    }
}

void Control::menuSeleccionarFormacionAutorModificacion(){
    cout << "Seleccione la formacion base del autor" << endl;
    cout << "1) Literatura \n2) Artes \n3) Ciencias sociales \n";
    cout << "4) Ingenierias \n5) Areas de la salud \n6) Jurisprudencia\n";
    cout << "7) Otros\n0) Volver \n";
    cin >> rtaUsuario;
    switch (rtaUsuario)
    {
    case 1:
        /* code */
        menuPrincipal();
        break;
    case 2:
        /* code */
        menuPrincipal();
        break;
    case 3:
        /* code */
        menuPrincipal();
        break;
    case 4:
        /* code */
        menuPrincipal();
        break;
    case 5:
        /* code */
        menuPrincipal();
        break;
    case 6:
        /* code */
        menuPrincipal();
        break;
    case 7:
        cout << "Escriba cual es la formacion base" << endl;
        cin >> rtaUsuarioStr;
        menuPrincipal();
        break;
    case 0:
        /* code */
        menuModificarAutor();
        break;
    default:
        cout << "Opcion invalida, intenta de nuevo." << endl;
        menuSeleccionarFormacionAutorModificacion();
        break;
    }
}

void Control::imprimirListaLibros(Lista<Libro>& lista) {
    for (int i = 1; i <= lista.getNumElem(); i++) {
        Libro l = lista.buscarPos(i);
        cout << i <<") "<< l.nombre << " " << l.tipoPoesia << " " << l.idAutor << endl;
        for (int j = 1; j <= l.ediciones.getNumElem(); j++)
        {  
        Edicion ed = l.ediciones.buscarPos(j);
        cout << i <<") "<< ed.numeroEdicion << "\n";
        cout <<"Id ditorial: " << ed.idEditorial<< "\n";
        cout <<"Ciudad de publicacion: " << ed.idEditorial<< "\n";
        cout <<"Fecha de publicacion: " << ed.idEditorial<< "\n";
        }
    }
}

void Control::imprimirListaAutores(Lista<Autor>& lista) {
    for (int i = 1; i <= lista.getNumElem(); i++) {
        Autor a = lista.buscarPos(i);
        cout <<i<<") "<< a.nombre << " " << a.apellido << endl;
        cout <<"Sexo: " << a.sexo << endl;
        cout <<"Fecha de nacimiento: " << a.fechaNacimiento << endl;
        cout <<"Ciudad de nacimiento: " << a.ciudadNacimiento << endl;
        cout <<"Pais de nacimiento: " << a.paisNacimiento << endl;
        cout <<"Ciudad de residencia: " << a.ciudadResidencia << endl;
        cout <<"Id del autor: " << a.idAutor << endl;
        cout <<"Formacion base: " << a.formacionBase << endl;
        cout <<"Anio inicio en la literatura " << a.anioInicioLiteratura << endl;
        cout <<"Anio publicacion primera obra " << a.anioPublicacionPrimeraObra << endl;
    }
}
void Control::imprimirListaEditoriales(Lista<Editorial>& lista) {
    for (int i = 1; i <= lista.getNumElem(); i++) {
        Editorial e = lista.buscarPos(i);
        cout <<i<<") "<< e.nombreEditorial << endl;
        cout << e.nombreEditorial << endl;
        cout <<"Id: "<< e.idEditorial << endl;
        cout <<"Ciudad oficina principal: "<< e.ciudadOficinaP << endl;
        cout <<"Pais oficina principal: "<< e.paisOficinaP << endl;
    }
}

/*void Control::imprimirListaEdiciones(Lista<Edicion>& Lista){
    for (int i = 1; i <= Lista.getNumElem(); i++)
    {   
        Edicion ed = ediciones.buscarPos(i);
        cout << i <<") "<< ed.numeroEdicion << "\n";
        cout <<"Id ditorial: " << ed.idEditorial<< "\n";
        cout <<"Ciudad de publicacion: " << ed.idEditorial<< "\n";
        cout <<"Fecha de publicacion: " << ed.idEditorial<< "\n";
    }
}*/