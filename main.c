#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h> //necesario para el sleep();
#include "Librerias\BDD\ABDD.h"
#include "Librerias\BDD\sqlite3.h"

#define MAX_OPTN 2
#define MAX_LINE 50
#define SECONDS_TO_CONTINUE 2000

//Administrador
void verificarAdmin();
void mainMenuAdmin();
void administrarLibros();
void administrarAutores();
void administrarEditoriales();
void administrarReservas();

//Ususario
void mainMenuUser();
void inicioSesion();
void registraUsuario();
int menuBuscar();
void buscarTitulo();
void buscarAutor();
void reservar(char nombre);

//Base de Datos
sqlite3 *dbM;

//con fgets y sscanf no me salía bien
int main() //MainMenu añadido al main principal
{
 
    system("cls"); //añadido para que la pantalla no se llene de mucha información
/*Datos prueba*/
    //Usuarios
    Usuario us1 = {"22767695X", "Josu", "Lopez", "josujon.l.a@opendeusto.es"};
    inicializarBDD("BibliotecaDeusto.db", dbM);
    insertarUsuario(&us1, "123456");
    
    eliminarUsuario(&us1);

    verificarContrasenya(&us1, "123456");
    verificarContrasenya(&us1, "654321");
    Usuario us2 = obtenerUsuario("22767695V");
    printf("DNI: %s\nNombre: %s\n", us2.dni, us2.nombre);

    Usuario **Lista1 = (Usuario**)malloc(sizeof(Usuario*));
    Lista1[0] = &us1;
    listadoUsuarios(Lista1, 1);
    free(Lista1);

    //Autores
    Autor au1 ={1, "Pedro", "de la Rosa"};
    Autor au2 ={2, "Alfredo", "Perez"};

    //Editoriales
    Editorial ed1 = {1, "Circulo"};

    //Libros
    Libro lib ={"bJGDkbc682nk9", "libro1", 2021, au1, ed1};
    Libro lib2 ={"bJ3Drbcko2nl7", "libro2", 2018, au2, ed1};
    Libro lib3 ={"ajkDrbcko2nl7", "libro3", 2019, au1, ed1};

    insertarLibro(&lib);
    insertarLibro(&lib2);
    insertarLibro(&lib3);

    eliminarLibro(&lib);

    Libro **Lista2 = (Libro**)malloc(sizeof(Libro*));
    Lista2[0] = &lib2;
    listadoLibros(Lista2, 1);
    free(Lista2);

    cerrarBDD(dbM);
/*Fin datos prueba*/

    printf("Que eres?\n");
    printf("1.Usuario\n2.Administrador\n");
    char select;
    scanf(" %c", &select);
            printf("Esto: %c\n", select);
    switch (select)
    {
    case '1':
        mainMenuUser();
        break;
    case '2':
        verificarAdmin();
        break;
    default:
        printf("Choose again\n");
        break;
    }
    
    return 0;
}


//Menus del administrador
void verificarAdmin()
{
    printf("Inserte el codigo de verificacion: ");
    char code;
    scanf(" %c", &code);
    if (code=='1') //prueba
    {
        printf("Acceso permitido.");
        mainMenuAdmin();
    }
    else
    {
        printf("Acceso denegado.");
    }
}

void mainMenuAdmin()
{
    //
    printf("---------------------\nMENU ADMINISTRADOR\n---------------------\n");
    printf("Que desea editar?\n");
    printf("1.Libros\n2.Autores\n3.Editoriales\n4.Reservas\n");
    
    char select;
    scanf(" %c", &select);
    
    switch (select)
    {
    case '1':
        administrarLibros();
        break;
    case '2':
        administrarAutores();
        break;
    case '3':
        administrarEditoriales();
        break;
    case '4':
        administrarReservas();
        break;
    default:
        printf("Choose again\n");
        break;
    }
    
}

void administrarLibros()
{
    printf("---------------------\nADMINISTRAR LIBROS\n---------------------\n");
    printf("Que desea hacer?\n");
    printf("1.Añadir\n2.Modificar\n3.Eliminar\n4.Listado completo\n");
    
    char select;
    scanf(" %c", &select);
    
    switch (select)
    {
    case '1':

        printf("Nombre del libro: \n");
        char name[MAX_LINE];
        scanf(" %s", &name);

        printf("Codigo isbn del libro: \n");
        char isbn[10];
        scanf(" %s", &isbn);

        printf("Anyo de publicacion: \n");
        char year[4];
        scanf(" %s", &year);

        printf("Codigo del Autor: \n");
        char cAutor[4];
        scanf(" %s", &cAutor);
        Autor author=obtenerAutor((int)cAutor);

        printf("Codigo de la Editorial: \n");
        char cEditorial[4];
        scanf(" %s", &cEditorial);
        Editorial editor=obtenerEditorial((int)cEditorial);
        
        Libro newBook={isbn, name, (int)year, author, editor};
        insertarLibro(&newBook);

        break;
    case '2':
        printf("Espere por favor \n");
        break;
    case '3':
        printf("Espere por favor \n");
        break;
    case '4':
        printf("Espere por favor \n");
        break;
    default:
        printf("Choose again\n");
        break;
    }
}

void administrarAutores()
{

}

void administrarEditoriales()
{

}

void administrarReservas()
{

}


//Menus del ususario
void mainMenuUser()
{
    char str[MAX_OPTN];
    char select;

    printf("---------------------\nBIBLIOTECA DEUSTO\n---------------------\n");
    printf("Bienvenido a la biblioteca\n");
    printf("1.Iniciar sesion\n2.Nuevo usuario\n3.Salir\n");
    /*fgets(str, MAX_OPTN, stdin); //no me va
    sscanf(str, "%d", &select);*/
    
    scanf(" %c", &select);
    
    switch (select)
    {
    case '1':
        inicioSesion();
        break;
    case '2':
        registraUsuario();
        break;
    case '3':
        printf("Has salido de la app\n");
        break;
    default:
        printf("Choose again\n");
        break;
    }
}

void inicioSesion()
{
    char str[MAX_LINE];
    char correo;
    char password;

    printf("---------------------\nINICIAR SESION\n---------------------\n");
    printf("Bienvenido a la biblioteca\n");
    printf("Correo electronico: \n");
    /*fgets(str, MAX_OPTN, stdin);
    sscanf(str, "%d", &correo);*/
    scanf(" %c", &correo);

    printf("Contrasenya: \n");
    /*fgets(str, MAX_OPTN, stdin);
    sscanf(str, "%d", &password);*/
    scanf(" %c", &password);

    //TO DO: conectarlo con la base de datos, comparar correo y contraseña
    //En caso de que el correo no existe o la contraseña está mal: repetir el proceso

    //Añadir delay para leer el texto con más calma
    printf("Conexion realizada con exito.\n");
    Sleep(SECONDS_TO_CONTINUE); //esperamos 2 segundos antes de "cambiar de pantalla"
    menuBuscar();

}

void registraUsuario()
{
    char str[MAX_LINE];
    char nombre;
    char apellido;
    char dni;
    char correo;
    char password;

    printf("---------------------\nREGISTRO USUARIO\n---------------------\n");
    printf("Nombre: \n");
    /*fgets(str, MAX_OPTN, stdin);
    sscanf(str, "%d", &nombre);*/
    scanf(" %c", &nombre);

    printf("Apellido: \n");
    /*fgets(str, MAX_OPTN, stdin);
    sscanf(str, "%d", &apellido);*/
    scanf(" %c", &apellido);

    printf("DNI: \n");
    /*fgets(str, MAX_OPTN, stdin);
    sscanf(str, "%d", &dni);*/
    scanf(" %c", &dni);

    printf("Correo electronico: \n");
    /*fgets(str, MAX_OPTN, stdin);
    sscanf(str, "%d", &correo);*/
    scanf(" %c", &correo);

    printf("Contrasenya: \n");
    /*fgets(str, MAX_OPTN, stdin);
    sscanf(str, "%d", &password);*/
    scanf(" %c", &password);

    //TO DO: conectarlo con la base de datos y añadir los datos nuevos
    //Añadir delay para leer el texto con más calma
    printf("Ususario creado correctamente.\n");
    Sleep(SECONDS_TO_CONTINUE);
    menuBuscar();

}

int menuBuscar()
{
    system("cls"); //añadido para que la pantalla no se llene de mucha información
    char str[MAX_OPTN];
    char select;
    printf("---------------------\nMENU BUSCAR\n---------------------\n");
    printf("1.Buscar libro por titulo\n2.Buscar libro por autor\n3.Volver menu principal\n");
    /*fgets(str, MAX_OPTN, stdin);
    sscanf(str, "%d", &select);*/
    scanf(" %c", &select);
            printf("Seleccion: %c\n", select);
    
    switch (select)
    {
    case '1':
        buscarTitulo();
        break;
    case '2':
        buscarAutor();
        break;
    case '3':
        printf("Volviendo al menu principal\n");
        main();
        break;
    }

    return select;
}

void buscarTitulo()
{
    char str[MAX_LINE];
    char titulo;
    char seleccion;

    printf("---------------------\nBUSCAR\n---------------------\n");
    printf("Titulo: ");
    /*fgets(str, MAX_OPTN, stdin);
    sscanf(str, "%d", &titulo);*/
    scanf(" %c", &titulo);

    //buscar en la base de datos los títulos que coincidan; ej: si buscas "noche" puede salir "Las mil y una noches" y "Guardianes de la noche" etc
    printf("Pulse el numero del libro para continuar con la reserva\n");
    printf("Pulse 1 para volver al menu de busqueda\n");
    //for con print para cada libro que salga
    scanf(" %c", &seleccion);

    if (seleccion=='1')
    {
        printf("Volviendo al menu busqueda.\n");
        Sleep(SECONDS_TO_CONTINUE);
        menuBuscar();
    }

    else
    {
        //obtendremos el id del libro seleccionado y llamamos a reservar()
        reservar(seleccion); //o libro.nombre || libro->nombre
    }
}

void buscarAutor()
{
    char str[MAX_LINE];
    char autor;
    char seleccion;
    
    printf("---------------------\nBUSCAR\n---------------------\n");
    printf("Autor: \n");
    /*fgets(str, MAX_OPTN, stdin);
    sscanf(str, "%d", &titulo);*/
    scanf(" %c", &autor);

    //buscar en la base de datos los autores que coincidan;
    printf("Pulse el numero del libro para continuar con la reserva\n");
    printf("Pulse 1 para volver al menu de busqueda\n");
    scanf(" %c", &seleccion);
    
    if (seleccion=='1')
    {
        printf("Volviendo al menu busqueda.\n");
        Sleep(SECONDS_TO_CONTINUE);
        menuBuscar();
    }

    else
    {
        //obtendremos el id del libro seleccionado y llamamos a reservar()
        reservar(seleccion); //o libro.nombre || libro->nombre
    }
}

void reservar(char nombre)
{
    char seleccion;
    printf("¿Desea reservar el libro %c?\n", nombre);
    printf("1.Si\n2.No\n");
    scanf(" %c", &seleccion);
    
    switch (seleccion)
    {
    case '1':
        printf("Reserva realizada, tiene X dias para devolverlo.\n");
        exit(0);//salimos de la app
    case '2':
        printf("Volviendo al menu busqueda");
        Sleep(SECONDS_TO_CONTINUE);
        menuBuscar();
        break;
    }
}

