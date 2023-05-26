#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h> //necesario para el sleep();
#include <stdbool.h>
#include "Librerias\BDD\ABDD.h"
#include "Librerias\BDD\sqlite3.h"
#include "Librerias\log.h"

#define MAX_OPTN 2
#define MAX_LINE 50
#define SECONDS_TO_CONTINUE 2000
#define SECONDS_TO_READ 5000

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
    bool active=true;
    int result;

    //do
    //{
        system("cls"); //añadido para que la pantalla no se llene de mucha información
        printf("---------------------\nMENU ADMINISTRADOR\n---------------------\n");
        printf("Que desea editar?\n");
        printf("1.Libros\n2.Autores\n3.Editoriales\n4.Reservas(Fuera de Servicio)\n");
        
        char select[2];
        fgets(select, 2, stdin);
        getchar(); // Limpiar el búfer (descartar el carácter de nueva línea)
        sscanf(select, "%d", &result);
    
        switch (result)
        {
        case 1:
            escribir_mensaje(logAd, INFO, "Seleccionado Administrar Libros");
            administrarLibros();
            active=false;
            break;
        case 2:
            escribir_mensaje(logAd, INFO, "Seleccionado Administrar Autores");
            administrarAutores();
            active=false;
            break;
        case 3:
            escribir_mensaje(logAd, INFO, "Seleccionado Administrar Editoriales");
            administrarEditoriales();
            active=false;
            break;
        /*case 4:
            //escribir_mensaje(logAd, INFO, "Seleccionado Administrar Reservas");   
            //administrarReservas();
            printf("Introduce un valor valido!\n");
            Sleep(SECONDS_TO_CONTINUE);
            break;*/
        default:
            escribir_mensaje(logAd, INFO, "Seleccion Nula");
            printf("Introduce un valor valido!\n");
            Sleep(SECONDS_TO_CONTINUE);
            //continue;
            break;
        }
    //} while (result<1||result>3);
    
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
    getchar(); // Limpiar el búfer (descartar el carácter de nueva línea)
    sscanf(select, "%d", &result);
    
    switch (result)
    {
    case 1: //añadir
        escribir_mensaje(logAd, INFO, "Seleccionado Anyadir");
        printf("Nombre del libro: \n");
        char name[MAX_LINE];
        char *nombre;
        fgets(name, MAX_LINE, stdin);
        getchar(); // Limpiar el búfer (descartar el carácter de nueva línea)
        sscanf(name, "%s", &nombre);

        printf("Codigo isbn del libro: \n");
        char isbn[10];
        char *codIsbn;
        fgets(isbn, 10, stdin);
        getchar(); // Limpiar el búfer (descartar el carácter de nueva línea)
        sscanf(isbn, "%s", &codIsbn);

        printf("Anyo de publicacion: \n");
        char year[4];
        int anyo;
        fgets(year, 4, stdin);
        getchar(); // Limpiar el búfer (descartar el carácter de nueva línea)
        sscanf(year, "%i", &anyo);

        imprimirListadoAutores();
        printf("Codigo del Autor: \n");
        char cAutor[4];
        int idAu;
        fgets(cAutor, 4, stdin);
        getchar(); // Limpiar el búfer (descartar el carácter de nueva línea)
        sscanf(cAutor, "%i", &idAu);
        Autor author=obtenerAutor(idAu);

        imprimirListadoEditoriales();
        printf("Codigo de la Editorial: \n");
        char cEditorial[4];
        int idEd;
        fgets(cEditorial, 4, stdin);
        getchar(); // Limpiar el búfer (descartar el carácter de nueva línea)
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
        char *codIsbnDel;
        fgets(isbnDel, 4, stdin);
        getchar(); // Limpiar el búfer (descartar el carácter de nueva línea)
        sscanf(isbnDel, "%s", &codIsbnDel);
        eliminarLibro(codIsbnDel);
        
        printf("Operacion realizada, volviendo al menu anterior...");
        Sleep(SECONDS_TO_CONTINUE);
        mainMenuAdmin();
        
        break;
    case 3: ;//Listado completo
        escribir_mensaje(logAd, INFO, "Seleccionado Mostrar Listado Completo");
        imprimirListadoLibros();
        
        printf("Operacion realizada, volviendo al menu anterior...");
        Sleep(SECONDS_TO_READ);
        mainMenuAdmin();

        break;
    default:
        escribir_mensaje(logAd, INFO, "Seleccion Nula");
        printf("Introduce un valor valido!\n");
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
    getchar(); // Limpiar el búfer (descartar el carácter de nueva línea)
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
        imprimirListadoAutores();
        
        printf("Operacion realizada, volviendo al menu anterior...");
        Sleep(SECONDS_TO_READ);
        mainMenuAdmin();
        
        break;
    default:
        escribir_mensaje(logAd, INFO, "Seleccion Nula");
        printf("Introduce un valor valido!\n");
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
    getchar(); // Limpiar el búfer (descartar el carácter de nueva línea)
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
        imprimirListadoEditoriales();
        
        printf("Operacion realizada, volviendo al menu anterior...");
        Sleep(SECONDS_TO_READ);
        mainMenuAdmin();
        
        break;
    default:
        escribir_mensaje(logAd, INFO, "Seleccion Nula");
        printf("Introduce un valor valido!\n");
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
    getchar(); // Limpiar el búfer (descartar el carácter de nueva línea)
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
        printf("Introduce un valor valido!\n");
        break;
    }
    cerrar_log(logAd);
}