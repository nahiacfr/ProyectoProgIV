#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_OPTN 2
#define MAX_LINE 20

void inicioSesion();
void registraUsuario();
int menuBuscar();
void buscarTitulo();
void buscarAutor();
void reservar(char nombre);

//con fgets y sscanf no me salía bien
int main() //MainMenu añadido al main principal
{
    char str[MAX_OPTN];
    char select;

    printf("---------------------\nBIBLIOTECA DEUSTO\n---------------------\n");
    printf("Bienvenido a la biblioteca\n");
    printf("1.Iniciar sesion\n2.Nuevo usuario\n3.Salir\n");
    /*fgets(str, MAX_OPTN, stdin); //no me va
    sscanf(str, "%d", &select);*/
    
    scanf(" %c", &select);
            printf("Esto: %c\n", select);
    
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

    return 0;
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
    menuBuscar();

}

int menuBuscar()
{
    char str[MAX_OPTN];
    int select;
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
    //obtendremos el id del libro seleccionado y llamamos a reservar()
    reservar(seleccion); //o libro.nombre || libro->nombre
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
    printf("Pulse el numero del autor para continuar con la reserva\n");
    printf("Pulse 1 para volver al menu de busqueda\n");
    //for con print para cada libro que salga
    scanf(" %c", &seleccion);

}

void reservar(char nombre)
{
    char seleccion;
    printf("¿Desea reservar el libro %c?", nombre);
    printf("1.Si\n2.No\n");
    scanf(" %c", &seleccion);

    
    switch (seleccion)
    {
    case '1':
        printf("REserva realizada.");
        exit(0);
        //break;
    case '2':
        menuBuscar();
        break;
    }
}