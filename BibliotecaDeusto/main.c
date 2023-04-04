#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_OPTN 2
#define MAX_LINE 20

int mainMenu();
void inicioSesion();
void registraUsuario();
int menuBuscar();
void buscarTitulo();
void buscarAutor();

int main(void)
{
    /* code */
    //int seleccion;
    //printf("Seleccion: %i", mainMenu());
    mainMenu();
    
    return 0;
}


int mainMenu()
{
    char str[MAX_OPTN];
    int select;
    printf("---------------------\nBIBLIOTECA DEUSTO\n---------------------\n");
    printf("Bienvenido a la biblioteca\n");
    printf("1.Iniciar sesion\n2.Nuevo usuario\n3.Salir\n");
    fgets(str, MAX_OPTN, stdin);
    sscanf(str, "%d", &select);
    
    switch (select)
    {
    case '1':
        inicioSesion();
    case '2':
        registraUsuario();
    case '3':
        printf("Has salido de la app");
        break;
    }
    return select;
}

void inicioSesion()
{
    char str[MAX_LINE];
    char correo;
    char password;
    printf("---------------------\nINICIAR SESION\n---------------------\n");
    printf("Bienvenido a la biblioteca\n");
    printf("Correo electronico: ");
    fgets(str, MAX_OPTN, stdin);
    sscanf(str, "%d", &correo);
    printf("Contrasenya: ");
    fgets(str, MAX_OPTN, stdin);
    sscanf(str, "%d", &password);

    //TO DO: conectarlo con la base de datos, comparar correo y contraseña
    //En caso de que el correo no existe o la contraseña está mal: repetir el proceso

    //Añadir delay para leer el texto con más calma
    printf("Conexion realizada con exito.");
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
    printf("Nombre: ");
    fgets(str, MAX_OPTN, stdin);
    sscanf(str, "%d", &nombre);
    printf("Apellido: ");
    fgets(str, MAX_OPTN, stdin);
    sscanf(str, "%d", &apellido);
    printf("DNI: ");
    fgets(str, MAX_OPTN, stdin);
    sscanf(str, "%d", &dni);
    printf("Correo electronico: ");
    fgets(str, MAX_OPTN, stdin);
    sscanf(str, "%d", &correo);
    printf("Contrasenya: ");
    fgets(str, MAX_OPTN, stdin);
    sscanf(str, "%d", &password);

    //TO DO: conectarlo con la base de datos y añadir los datos nuevos
    //Añadir delay para leer el texto con más calma
    printf("Ususario creado correctamente.");
    menuBuscar();

}

int menuBuscar()
{
    char str[MAX_OPTN];
    int select;
    printf("---------------------\nMENU BUSCAR\n---------------------\n");
    printf("1.Buscar libro por titulo\n2.Buscar libro por autor\n3.Volver menu principal\n");
    fgets(str, MAX_OPTN, stdin);
    sscanf(str, "%d", &select);
    
    switch (select)
    {
    case '1':
        buscarTitulo();
    case '2':
        buscarAutor();
    case '3':
        printf("Volviendo al menu principal");
        mainMenu();
        break;
    }

    return select;
}

void buscarTitulo()
{
    char str[MAX_LINE];
    char titulo;
    printf("---------------------\nBUSCAR\n---------------------\n");
    printf("Titulo: ");
    fgets(str, MAX_OPTN, stdin);
    sscanf(str, "%d", &titulo);
    printf("Pulse el numero del libro para continuar con la reserva\n");

}

void buscarAutor()
{
    char str[MAX_LINE];
    char titulo;
    printf("---------------------\nBUSCAR\n---------------------\n");
    printf("Autor: ");
    fgets(str, MAX_OPTN, stdin);
    sscanf(str, "%d", &titulo);
    printf("Pulse el numero del autor para continuar con la reserva\n");

}
