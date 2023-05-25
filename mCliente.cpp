
//#include <stdio.h>
//#include <stdlib.h>
#include <string>
#include <windows.h> //necesario para el sleep();

extern "C"
{
    #include "Librerias\BDD\ABDD.h"
    #include "Librerias\BDD\sqlite3.h"
    #include "Librerias\log.h"
}

#include <iostream>
using namespace std;

#define MAX_OPTN 2
#define MAX_LINE 50
#define SECONDS_TO_CONTINUE 2000

void mainMenuUser();
void inicioSesion();
void registraUsuario();
int menuBuscar();
void buscarTitulo();
void buscarAutor();
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

    cout << "---------------------"<< endl<<"BIBLIOTECA DEUSTO"<<endl<<"---------------------"<<endl;
    cout << "Bienvenido a la biblioteca"<<endl;
    cout << "1.Iniciar sesion"<< endl<<"2.Nuevo usuario"<<endl<<"3.Salir"<<endl;
    
    int result;
    cin>>result;
    
    switch (result)
    {
    case 1:
        inicioSesion();
        break;
    case 2:
        registraUsuario();
        break;
    case 3:
        cout << "Has salido de la app"<<endl;
        break;
    default:
        cout << "Choose again"<<endl;
        break;
    }
}

void inicioSesion()
{
    string correo;
    string password;

    cout << "---------------------"<< endl<<"INICIAR SESION"<<endl<<"---------------------"<<endl;
    cout << "Bienvenido a la biblioteca"<<endl;
    cout << "Correo electronico: "<<endl;
    cin>>correo;

    cout << "Contrasenya: "<<endl;
    cin>>password;

    //TO DO: conectarlo con la base de datos, comparar correo y contraseña
    //En caso de que el correo no existe o la contraseña está mal: repetir el proceso

    //Añadir delay para leer el texto con más calma
    cout << "Conexion realizada con exito."<<endl;
    Sleep(SECONDS_TO_CONTINUE); //esperamos 2 segundos antes de "cambiar de pantalla"
    menuBuscar();
}

void registraUsuario()
{
    string nombre;
    string apellido;
    string dni;
    string correo;
    string password;

    cout << "---------------------"<< endl<<"REGISTRO USUARIO"<<endl<<"---------------------"<<endl;
    cout << "Nombre: "<<endl;
    cin>>nombre;

    cout << "Apellido: "<<endl;
    cin>>apellido;

    cout << "DNI: "<<endl;
    cin>>dni;

    cout << "Correo electronico: "<<endl;
    cin>>correo;

    cout << "Contrasenya: "<<endl;
    cin>>password;

    //TO DO: conectarlo con la base de datos y añadir los datos nuevos
    //Añadir delay para leer el texto con más calma
    cout << "Ususario creado correctamente."<<endl;
    Sleep(SECONDS_TO_CONTINUE);
    menuBuscar();
}

int menuBuscar()
{
    system("cls"); //añadido para que la pantalla no se llene de mucha información
    cout << "---------------------"<<endl<<"MENU BUSCAR"<<endl<<"---------------------"<<endl;
    cout << "1.Buscar libro por titulo"<<endl<<"2.Buscar libro por autor"<<endl<<"3.Volver menu principal"<<endl;
    
    int result;
    cout << "Seleccion: "<<endl;
    cin>>result;
    
    switch (result)
    {
    case 1:
        buscarTitulo();
        break;
    case 2:
        buscarAutor();
        break;
    case 3:
        cout << "Volviendo al menu principal..."<<endl;
        Sleep(SECONDS_TO_CONTINUE);
        mainMenuUser();
        break;
    }

    return result;
}

void buscarTitulo()
{
    string titulo;
    int seleccion;

    cout << "---------------------"<<endl<<"BUSCAR LIBRO"<<endl<<"---------------------"<<endl;
    cout << "Titulo: "<<endl;
    cin>>titulo;

    //buscar en la base de datos los títulos que coincidan; ej: si buscas "noche" puede salir "Las mil y una noches" y "Guardianes de la noche" etc
    cout << "Pulse el numero del libro para continuar con la reserva."<<endl<<"Pulse 0 para volver al menu de busqueda"<<endl;
    //TODO for con print para cada libro que salga
    cin>>seleccion;

    if (seleccion==0)
    {
        cout << "Volviendo al menu busqueda."<<endl;
        Sleep(SECONDS_TO_CONTINUE);
        menuBuscar();
    }

    else
    {
        //obtendremos el id del libro seleccionado y llamamos a reservar()
        reservar(seleccion); // seleccion.nombre || seleccion->nombre
        
        /*cout << "Operacion realizada, volviendo al menu anterior..."<<endl;
        Sleep(SECONDS_TO_CONTINUE);
        menuBuscar();*/
    }
}

void buscarAutor()
{
    char str[MAX_LINE];
    string autor;
    int seleccion;
    
    cout<<"---------------------"<<endl<<"BUSCAR AUTOR"<<endl<<"---------------------"<<endl;
    cout<<"Autor: "<<endl;
    cin>>autor;

    //buscar en la base de datos los autores que coincidan;
    cout<<"Pulse el numero del libro para continuar con la reserva"<<endl;
    cout<<"Pulse 0 para volver al menu de busqueda"<<endl;
    cin>>seleccion;
    
    if (seleccion==0)
    {
        cout<<"Volviendo al menu busqueda."<<endl;
        Sleep(SECONDS_TO_CONTINUE);
        menuBuscar();
    }

    else
    {
        //obtendremos el id del libro seleccionado y llamamos a reservar()
        reservar(seleccion); // seleccion.nombre || seleccion->nombre

        /*cout<<"Operacion realizada, volviendo al menu anterior..."<<endl;
        Sleep(SECONDS_TO_CONTINUE);
        menuBuscar();*/
    }
}

void reservar(char nombre)
{
    cout<<"¿Desea reservar el libro "<< nombre<<endl;
    cout<<"1.Si"<<endl<<"2.No"<<endl;
    
    int result;
    cin>>result;
    
    switch (result)
    {
    case 1:
        cout<<"Reserva realizada, tiene X dias para devolverlo"<<endl;
        cout<<"Volviendo al menu anterior..."<<endl;
        Sleep(SECONDS_TO_CONTINUE);
        menuBuscar();
        break;
    case 2:
        cout<<"Volviendo al menu busqueda"<<endl;
        Sleep(SECONDS_TO_CONTINUE);
        menuBuscar();
        break;
    }
}