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
    Usuario us2 = {"22767695V", "Josu", "Lopez", "josujon.l.a@opendeusto.es"};
    Usuario us3 = {"22767695Z", "Josu", "Lopez", "josujon.l.a@opendeusto.es"};
    inicializarBDD("BibliotecaDeusto.db", dbM);
    insertarUsuario(&us1, "123456");
    insertarUsuario(&us2, "123456");
    insertarUsuario(&us3, "123456");
    
    eliminarUsuario(us1.dni);

    verificarContrasenya(&us1, "123456");
    verificarContrasenya(&us1, "654321");
/*  Usuario *us2 = malloc(sizeof(Usuario));
    *us2 = obtenerUsuario(us2, "22767695V");

    if(strcmp("22767695V", us2->dni) == 0){
        printf("Verdadero\n");
    }
    printf("DNI: %s\nNombre: %s\n", us2->dni, us2->nombre);
    printf("DNI: %s\nNombre: %s\n", us1.dni, us1.nombre);

    free(us2);
*/

    imprimirListadoUsuarios();

    //Autores
    Autor au1 ={1, "Pedro", "de la Rosa"};
    Autor au2 ={2, "Alfredo", "Perez"};

    insertarAutor(&au1);
    insertarAutor(&au2);

    imprimirListadoAutores();
    eliminarAutor(au1.id);

    //Editoriales

    Editorial ed1 = {1, "Circulo"};

    insertarEditoriaL(&ed1);

    imprimirListadoEditoriales();

    eliminarEditorial(ed1.id);

    //Libros
    Libro lib ={"bJGDkbc682nk9", "libro1", 2021, au1, ed1};
    Libro lib2 ={"bJ3Drbcko2nl7", "libro2", 2018, au2, ed1};
    Libro lib3 ={"ajkDrbcko2nl7", "libro3", 2019, au1, ed1};

    insertarLibro(&lib);
    insertarLibro(&lib2);
    insertarLibro(&lib3);

    eliminarLibro(lib.isbn);

    imprimirListadoLibros();

    cerrarBDD(dbM);
/*Fin datos prueba*/

    printf("---------------------\nBIBLIOTECA DEUSTO\n---------------------\n");
    printf("Bienvenido\n");
    printf("Que eres?\n");
    printf("1.Usuario\n2.Administrador\n");
    char select;
    scanf(" %c", &select);
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
        Sleep(SECONDS_TO_CONTINUE);
        mainMenuAdmin();
    }
    else
    {
        printf("Acceso denegado.");
    }
}

void mainMenuAdmin()
{
    system("cls"); //añadido para que la pantalla no se llene de mucha información
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
    printf("1.Anyadir\n2.Eliminar\n3.Listado completo\n");
    
    char select;
    scanf(" %c", &select);
    
    switch (select)
    {
    case '1': //añadir

        printf("Nombre del libro: \n");
        char name[MAX_LINE];
        scanf(" %s", &name);

        printf("Codigo isbn del libro: \n");
        char isbn[10];
        scanf(" %s", &isbn);

        printf("Anyo de publicacion: \n");
        char year[4];
        int anyo;
        scanf(" %s", &year);
        sscanf(year, "%i", &anyo);

        imprimirListadoAutores();
        printf("Codigo del Autor: \n");
        char cAutor[4];
        int idAu;
        scanf(" %s", &cAutor);
        sscanf(cAutor, "%i", &idAu);
        Autor author=obtenerAutor(idAu);

        imprimirListadoEditoriales();
        printf("Codigo de la Editorial: \n");
        char cEditorial[4];
        int idEd;
        scanf(" %s", &cEditorial);
        sscanf(cEditorial, "%i", &idEd);
        Editorial editor=obtenerEditorial(idEd);
        
        Libro newBook={isbn, name, anyo, author, editor};
        insertarLibro(&newBook);

        printf("Operacion realizada, volviendo al menu anterior...");
        Sleep(SECONDS_TO_CONTINUE);
        mainMenuAdmin();

        break;
    case '2': //Eliminar
        imprimirListadoLibros();
        printf("Codigo isbn de libro a eliminar: \n");
        char isbnDel[10];
        scanf(" %s", &isbnDel);
        eliminarLibro(isbnDel);
        
        printf("Operacion realizada, volviendo al menu anterior...");
        Sleep(SECONDS_TO_CONTINUE);
        mainMenuAdmin();
        
        break;
    case '3': ;//Listado completo
        /*  leer de fichero
        FILE *f;
        char string[1000]="";
        f=fopen("Libro.txt","r");

        while (fgets(string, sizeof(string), f))
        {
            printf("%s\n",string);
        }
        fclose(f);
        */
        imprimirListadoLibros();
        
        printf("Operacion realizada, volviendo al menu anterior...");
        Sleep(SECONDS_TO_CONTINUE);
        mainMenuAdmin();

        break;
    default:
        printf("Choose again\n");
        break;
    }
}

void administrarAutores()
{
    printf("---------------------\nADMINISTRAR AUTORES\n---------------------\n");
    printf("Que desea hacer?\n");
    printf("1.Anyadir\n2.Eliminar\n3.Listado completo\n");
    
    char select;
    scanf(" %c", &select);
    
    switch (select)
    {
    case '1': //añadir

        printf("Nombre del autor: \n");
        char name[MAX_LINE];
        scanf(" %s", &name);

        printf("Apellido del autor: \n");
        char surname[MAX_LINE];
        scanf(" %s", &surname);

        printf("Codigo del Autor: \n");
        char cAutor[MAX_LINE];
        int id;
        scanf(" %s", &cAutor);
        sscanf(cAutor, "%i", &id);
        
        Autor newAuthor={id, name, surname};

        insertarAutor(&newAuthor);
        
        printf("Operacion realizada, volviendo al menu anterior...");
        Sleep(SECONDS_TO_CONTINUE);
        mainMenuAdmin();

        break;
    case '2': //Eliminar
        imprimirListadoAutores();
        printf("Codigo del autor a eliminar: \n");
        char cAutorDel[10];
        int codigo;
        scanf(" %s", &cAutorDel);
        sscanf(cAutor, "%i", &codigo);
        eliminarAutor(codigo);
        
        printf("Operacion realizada, volviendo al menu anterior...");
        Sleep(SECONDS_TO_CONTINUE);
        mainMenuAdmin();
        
        break;
    case '3': ;//Listado completo
       /* //leer de fichero
        FILE *f;
        char string[1000]="";
        f=fopen("Autor.txt","r");

        while (fgets(string, sizeof(string), f))
        {
            printf("%s\n",string);
        }
        fclose(f);
        */
        imprimirListadoAutores();
        
        printf("Operacion realizada, volviendo al menu anterior...");
        Sleep(SECONDS_TO_CONTINUE);
        mainMenuAdmin();
        
        break;
    default:
        printf("Choose again\n");
        break;
    }
}

void administrarEditoriales()
{
printf("---------------------\nADMINISTRAR EDITORIALES\n---------------------\n");
    printf("Que desea hacer?\n");
    printf("1.Anyadir\n2.Eliminar\n3.Listado completo\n");
    
    char select;
    scanf(" %c", &select);
    
    switch (select)
    {
    case '1': //añadir

        printf("Nombre de la editorial: \n");
        char name[MAX_LINE];
        scanf(" %s", &name);

        printf("Codigo de la editorial: \n");
        char cEd[4];
        int id;
        scanf(" %s", &cEd);
        sscanf(cEd, "%i", &id);
        
        Editorial newEditorial={id, name};
        insertarEditoriaL(&newEditorial);
        
        printf("Operacion realizada, volviendo al menu anterior...");
        Sleep(SECONDS_TO_CONTINUE);
        mainMenuAdmin();

        break;
    case '2': //Eliminar
        imprimirListadoEditoriales();
        printf("Codigo de la editorial a eliminar: \n");
        char cEdDel[10];
        int codigo;
        scanf(" %s", &cEdDel);
        sscanf(cEdDel, "%i", &codigo);
        eliminarEditorial(codigo);
        
        printf("Operacion realizada, volviendo al menu anterior...");
        Sleep(SECONDS_TO_CONTINUE);
        mainMenuAdmin();
        
        break;
    case '3': ;//Listado completo
        /*//leer de fichero
        FILE *f;
        char string[1000]="";
        f=fopen("Editorial.txt","r");

        while (fgets(string, sizeof(string), f))
        {
            printf("%s\n",string);
        }
        fclose(f);
        */
        imprimirListadoEditoriales();
        
        printf("Operacion realizada, volviendo al menu anterior...");
        Sleep(SECONDS_TO_CONTINUE);
        mainMenuAdmin();
        
        break;
    default:
        printf("Choose again\n");
        break;
    }
}

void administrarReservas()
{
printf("---------------------\nADMINISTRAR RESERVAS\n---------------------\n");
    printf("Que desea hacer?\n");
    printf("1.Anyadir\n2.Modificar\n3.Eliminar\n4.Listado completo\n");
    
    char select;
    scanf(" %c", &select);
    
    switch (select)
    {
    case '1': //añadir
        //añadir Reserva

        break;
    case '2': //Modificar
        //modificar Reserva

        break;
    case '3': //Eliminar
        //eliminar Reserva
        
        break;
    case '4': ;//Listado completo
        //leer de fichero
        FILE *f;
        char string[1000]="";
        f=fopen("Libros.txt","r"); //crear archivo de reservas?

        while (fgets(string, sizeof(string), f))
        {
            printf("%s\n",string);
        }
        fclose(f);
        //printf("Espere por favor \n");

        break;
    default:
        printf("Choose again\n");
        break;
    }
}


//Menus del ususario
void mainMenuUser()
{
    system("cls"); //añadido para que la pantalla no se llene de mucha información
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
        
        printf("Operacion realizada, volviendo al menu anterior...");
        Sleep(SECONDS_TO_CONTINUE);
        menuBuscar();
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

        printf("Operacion realizada, volviendo al menu anterior...");
        Sleep(SECONDS_TO_CONTINUE);
        menuBuscar();
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
        printf("Volviendo al menu anterior...");
        Sleep(SECONDS_TO_CONTINUE);
        menuBuscar();
        break;
    case '2':
        printf("Volviendo al menu busqueda");
        Sleep(SECONDS_TO_CONTINUE);
        menuBuscar();
        break;
    }
}

