#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h> //necesario para el sleep();
#include "Librerias\BDD\ABDD.h"
#include "Librerias\BDD\sqlite3.h"
#include "Librerias\log.h"

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
    inicializarBDD("BibliotecaDeusto.db", dbM);
    mainMenuAdmin();
/*  printf("---------------------\nBIBLIOTECA DEUSTO\n---------------------\n");
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
*/    
    return 0;
}

//Menus del administrador
void verificarAdmin()
{
    //Log
    Log *logAd;
    logAd = crear_log("Ficheros/Logs/LogAdministrador.txt");

    printf("Inserte el codigo de verificacion: ");
    char code;
    scanf(" %c", &code);
    if (code=='1') //prueba
    {
        printf("Acceso permitido.");
        escribir_mensaje(logAd, INFO, "Acceso de administrador valido");
        Sleep(SECONDS_TO_CONTINUE);
        mainMenuAdmin();
    }
    else
    {
        printf("Acceso denegado.");
        escribir_mensaje(logAd, WARNING, "Acceso de administrador incorrecto");
    }
    cerrar_log(logAd);
}

void mainMenuAdmin()
{
    //Log
    Log *logAd;
    logAd = crear_log("Ficheros/Logs/LogAdministrador.txt");

    system("cls"); //añadido para que la pantalla no se llene de mucha información
    printf("---------------------\nMENU ADMINISTRADOR\n---------------------\n");
    printf("Que desea editar?\n");
    printf("1.Libros\n2.Autores\n3.Editoriales\n4.Reservas(Fuera de Servicio)\n");
    
    char select[2];
    int result;
    fgets(select, 2, stdin);
    sscanf(select, "%d", &result);
    
    switch (result)
    {
    case 1:
        escribir_mensaje(logAd, INFO, "Seleccionado Administrar Libros");
        administrarLibros();
        break;
    case 2:
        escribir_mensaje(logAd, INFO, "Seleccionado Administrar Autores");
        administrarAutores();
        break;
    case 3:
        escribir_mensaje(logAd, INFO, "Seleccionado Administrar Editoriales");
        administrarEditoriales();
        break;
    case 4:
        //escribir_mensaje(logAd, INFO, "Seleccionado Administrar Reservas");   
        //administrarReservas();
        printf("Choose again\n");
        Sleep(SECONDS_TO_CONTINUE);
        mainMenuAdmin();
        break;
    default:
        escribir_mensaje(logAd, INFO, "Seleccion Nula");
        printf("Choose again\n");
        Sleep(SECONDS_TO_CONTINUE);
        mainMenuAdmin();
        break;
    }
    cerrar_log(logAd);
}

void administrarLibros()
{
    //Log
    Log *logAd;
    logAd = crear_log("Ficheros/Logs/LogAdministrador.txt");

    printf("---------------------\nADMINISTRAR LIBROS\n---------------------\n");
    printf("Que desea hacer?\n");
    printf("1.Anyadir\n2.Eliminar\n3.Listado completo\n");
    
    char select[2];
    int result;
    fgets(select, 2, stdin);
    sscanf(select, "%d", &result);
    
    switch (result)
    {
    case 1: //añadir
        escribir_mensaje(logAd, INFO, "Seleccionado Anyadir");
        printf("Nombre del libro: \n");
        char name[MAX_LINE];
        //scanf(" %s", &name);
        char *result;
        fgets(select, MAX_LINE, stdin);
        sscanf(select, "%s", &result);

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
    case 2: //Eliminar
        escribir_mensaje(logAd, INFO, "Seleccionado Eliminar");
        imprimirListadoLibros();
        printf("Codigo isbn de libro a eliminar: \n");
        char isbnDel[10];
        scanf(" %s", &isbnDel);
        eliminarLibro(isbnDel);
        
        printf("Operacion realizada, volviendo al menu anterior...");
        Sleep(SECONDS_TO_CONTINUE);
        mainMenuAdmin();
        
        break;
    case 3: ;//Listado completo
        escribir_mensaje(logAd, INFO, "Seleccionado Mostrar Listado Completo");
        imprimirListadoLibros();
        
        printf("Operacion realizada, volviendo al menu anterior...");
        Sleep(SECONDS_TO_CONTINUE);
        mainMenuAdmin();

        break;
    default:
        escribir_mensaje(logAd, INFO, "Seleccion Nula");
        printf("Choose again\n");
        mainMenuAdmin();
        break;
    }
    cerrar_log(logAd);
}

void administrarAutores()
{
    //Log
    Log *logAd;
    logAd = crear_log("Ficheros/Logs/LogAdministrador.txt");

    printf("---------------------\nADMINISTRAR AUTORES\n---------------------\n");
    printf("Que desea hacer?\n");
    printf("1.Anyadir\n2.Eliminar\n3.Listado completo\n");
    
    char select[2];
    int result;
    fgets(select, 2, stdin);
    sscanf(select, "%d", &result);
    
    switch (result)
    {
    case 1: //añadir
        escribir_mensaje(logAd, INFO, "Seleccionado Anyadir");
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
    case 2: //Eliminar
        escribir_mensaje(logAd, INFO, "Seleccionado Eliminar");
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
    case 3: ;//Listado completo
        escribir_mensaje(logAd, INFO, "Seleccionado mostrar listado completo");
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
        escribir_mensaje(logAd, INFO, "Seleccion Nula");
        printf("Choose again\n");
        mainMenuAdmin();
        break;
    }
    cerrar_log(logAd);
}

void administrarEditoriales()
{
    //Log
    Log *logAd;
    logAd = crear_log("Ficheros/Logs/LogAdministrador.txt");

    printf("---------------------\nADMINISTRAR EDITORIALES\n---------------------\n");
    printf("Que desea hacer?\n");
    printf("1.Anyadir\n2.Eliminar\n3.Listado completo\n");
    
    char select[2];
    int result;
    fgets(select, 2, stdin);
    sscanf(select, "%d", &result);
    
    switch (result)
    {
    case 1: //añadir
        escribir_mensaje(logAd, INFO, "Seleccionado Anyadir");
        printf("Nombre de la editorial: \n");
        char name[MAX_LINE];
        scanf(" %s", &name);

        printf("Codigo de la editorial: \n");
        char cEd[4];
        int id;
        scanf(" %s", &cEd);
        sscanf(cEd, "%i", &id);
        
        Editorial newEditorial={id, name};
        insertarEditorial(&newEditorial);
        
        printf("Operacion realizada, volviendo al menu anterior...");
        Sleep(SECONDS_TO_CONTINUE);
        mainMenuAdmin();

        break;
    case 2: //Eliminar
        escribir_mensaje(logAd, INFO, "Seleccionado Eliminar");
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
    case 3: ;//Listado completo
        escribir_mensaje(logAd, INFO, "Seleccionado Mostrar listado completo");
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
        escribir_mensaje(logAd, INFO, "Seleccion Nula");
        printf("Choose again\n");
        mainMenuAdmin();
        break;
    }
    cerrar_log(logAd);
}

void administrarReservas()
{
    //Log
    Log *logAd;
    logAd = crear_log("Ficheros/Logs/LogAdministrador.txt");

    printf("---------------------\nADMINISTRAR RESERVAS\n---------------------\n");
    printf("Que desea hacer?\n");
    printf("1.Anyadir\n2.Modificar\n3.Eliminar\n4.Listado completo\n");
    
    char select[2];
    int result;
    fgets(select, 2, stdin);
    sscanf(select, "%d", &result);
    
    switch (result)
    {
    case 1: //añadir
        escribir_mensaje(logAd, INFO, "Seleccionado Anyadir");
        //añadir Reserva

        break;
    case 2: //Modificar
        escribir_mensaje(logAd, INFO, "Seleccionado Modificar");
        //modificar Reserva

        break;
    case 3: //Eliminar
        escribir_mensaje(logAd, INFO, "Seleccionado Eliminar");
        //eliminar Reserva
        
        break;
    case 4: ;//Listado completo
        escribir_mensaje(logAd, INFO, "Seleccionado Mostrar listado completo");
        //leer de fichero
    /*  FILE *f;
        char string[1000]="";
        f=fopen("Libros.txt","r"); //crear archivo de reservas?

        while (fgets(string, sizeof(string), f))
        {
            printf("%s\n",string);
        }
        fclose(f);
        //printf("Espere por favor \n");
    */
        break;
    default:
        escribir_mensaje(logAd, INFO, "Seleccion Nula");
        printf("Choose again\n");
        break;
    }
    cerrar_log(logAd);
}