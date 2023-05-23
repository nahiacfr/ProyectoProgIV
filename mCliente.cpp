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

void mainMenuUser();
void inicioSesion();
void registraUsuario();
int menuBuscar();
void buscarTitulo();
void reservar(char nombre);

int main(int argc, char const *argv[])
{
    mainMenuUser();
    return 0;
}

//Menus del ususario
void mainMenuUser()
{
    system("cls"); //añadido para que la pantalla no se llene de mucha información
    char str[MAX_OPTN];

    printf("---------------------\nBIBLIOTECA DEUSTO\n---------------------\n");
    printf("Bienvenido a la biblioteca\n");
    printf("1.Iniciar sesion\n2.Nuevo usuario\n3.Salir\n");
    /*fgets(str, MAX_OPTN, stdin); //no me va
    sscanf(str, "%d", &select);*/
    
    char select[2];
    int result;
    fgets(select, 2, stdin);
    sscanf(select, "%d", &result);
    
    switch (result)
    {
    case 1:
        inicioSesion();
        break;
    case 2:
        registraUsuario();
        break;
    case 3:
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
    printf("---------------------\nMENU BUSCAR\n---------------------\n");
    printf("1.Buscar libro por titulo\n2.Buscar libro por autor\n3.Volver menu principal\n");
    char select[2];
    int result;
    fgets(select, 2, stdin);
    sscanf(select, "%d", &result);
            printf("Seleccion: %c\n", select);
    
    switch (result)
    {
    case 1:
        buscarTitulo();
        break;
    case 2:
        buscarAutor();
        break;
    case 3:
        printf("Volviendo al menu principal\n");
        mainMenuUser();
        break;
    }

    return result;
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
    printf("¿Desea reservar el libro %c?\n", nombre);
    printf("1.Si\n2.No\n");
    
    char select[2];
    int result;
    fgets(select, 2, stdin);
    sscanf(select, "%d", &result);
    
    switch (result)
    {
    case 1:
        printf("Reserva realizada, tiene X dias para devolverlo.\n");
        printf("Volviendo al menu anterior...");
        Sleep(SECONDS_TO_CONTINUE);
        menuBuscar();
        break;
    case 2:
        printf("Volviendo al menu busqueda");
        Sleep(SECONDS_TO_CONTINUE);
        menuBuscar();
        break;
    }
}