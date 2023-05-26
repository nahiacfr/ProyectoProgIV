
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <winsock2.h>
#include <string>
#include <windows.h> //necesario para el sleep();

extern "C"
{
    #include "Librerias\log.h"
    #include "Librerias\config.h"
}

using namespace std;

#define MAX_OPTN 2
#define MAX_LINE 50
#define SECONDS_TO_CONTINUE 2000

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8080

void mainMenuUser();
void inicioSesion();
void registraUsuario();
int menuBuscar();
void buscarTitulo();
void buscarAutor();
void reservar(char nombre);

WSADATA wsaData;
SOCKET s;
struct sockaddr_in server;
char sendBuff[512], recvBuff[512];
string presend;

int main(int argc, char const *argv[])
{
	cout << endl<<"Initialising Winsock..."<< endl;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		cout << "Failed. Error Code : "<< WSAGetLastError()<< endl;
		return -1;
	}

	cout << "Initialised."<< endl;

	//SOCKET creation
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		cout << "Could not create socket : "<<WSAGetLastError()<<endl;
		WSACleanup();
		return -1;
	}

	cout << "Socket created."<< endl;

	server.sin_addr.s_addr = inet_addr(SERVER_IP);
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	//CONNECT to remote server
	if (connect(s, (struct sockaddr*) &server, sizeof(server)) == SOCKET_ERROR) {
		cout << "Connection error: "<< WSAGetLastError()<< endl;
		closesocket(s);
		WSACleanup();
		return -1;
	}

	cout << "Connection stablished with: "<< inet_ntoa(server.sin_addr)<<"("<<ntohs(server.sin_port)<<")"<< endl;

	// SEND and RECEIVE data
	/*
    printf("Sending message 1... \n");
	strcpy(sendBuff, "Hello, server.");
	send(s, sendBuff, sizeof(sendBuff), 0);
    */

	// CLOSING the socket and cleaning Winsock...
	//closesocket(s);
	//WSACleanup();
    mainMenuUser();
    return 0;
}

//Menus del ususario
void mainMenuUser()
{
    system("cls"); //añadido para que la pantalla no se llene de mucha información
    char str[MAX_OPTN];
    bool active=true;

    while(active)
    {
        cout << "---------------------"<< endl<<"BIBLIOTECA DEUSTO"<<endl<<"---------------------"<<endl;
        cout << "Bienvenido a la biblioteca"<<endl;
        cout << "1.Iniciar sesion"<< endl<<"2.Nuevo usuario"<<endl<<"3.Salir"<<endl;
        
        int result;
        cin>>result;
        
        switch (result)
        {
        case 1:
            inicioSesion();
            active=false;
            break;
        case 2:
            registraUsuario();
            active=false;
            break;
        case 3:
            cout << "Has salido de la app"<<endl;
            active=false;
            break;
        default:
            cout << "Introduce un valor valido!"<<endl;
            Sleep(SECONDS_TO_CONTINUE);
            continue;
        }
    }
}

void inicioSesion()
{
    system("cls"); //añadido para que la pantalla no se llene de mucha información
    string correo;
    string password;

    cout << "---------------------"<< endl<<"INICIAR SESION"<<endl<<"---------------------"<<endl;
    cout << "Bienvenido a la biblioteca"<<endl;
    cout << "Correo electronico: "<<endl;
    cin>>correo;

    cout << "Contrasenya: "<<endl;
    cin>>password;

    //Envia el Socket para verificar el usuario
    presend = "INS##" + correo + "#" + password + "#";
    strcpy(sendBuff, presend.c_str());
	send(s, sendBuff, sizeof(sendBuff), 0);
    //Espera la respuesta del Servidor
    cout << "Esperando respuesta..."<<endl;
    recv(s, recvBuff, sizeof(recvBuff), 0);
    cout << "Respuesta obtenida"<<endl;
    if(recvBuff[0]=='1')
    {
        cout << "Conexion realizada con exito."<<endl;
        Sleep(SECONDS_TO_CONTINUE); //esperamos 2 segundos antes de "cambiar de pantalla"
        menuBuscar();
    }else
    {
        inicioSesion();
    }
    
    
}

void registraUsuario()
{
    system("cls"); //añadido para que la pantalla no se llene de mucha información
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

    // Construye la solicitud con los datos del cliente
    string request = "REG##" + nombre + "#" + apellido + "#" + dni + "#" + correo + "#" + password + "#";
    send(s, request.c_str(), request.size(), 0);


    // Espera la respuesta del servidor
    char recvBuff[256];
    memset(recvBuff, 0, sizeof(recvBuff));
    recv(s, recvBuff, sizeof(recvBuff), 0);


    if (recvBuff[0] == '1') {
        cout << "Usuario creado correctamente." << endl;
        Sleep(SECONDS_TO_CONTINUE);
        menuBuscar();
    }
    else {
        cout << "Error al crear el usuario. Inténtalo de nuevo." << endl;
        registraUsuario();
    }

}

int menuBuscar()
{
    bool active=true;

    while(active)
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
            active=false;
            break;
        case 2:
            buscarAutor();
            active=false;
            break;
        case 3:
            cout << "Volviendo al menu principal..."<<endl;
            Sleep(SECONDS_TO_CONTINUE);
            mainMenuUser();
            active=false;
            break;
        default:
            cout<<"Introduce un valor valido!"<<endl;
            Sleep(SECONDS_TO_CONTINUE);
            continue;
        }

        return result;
    }
}

void buscarTitulo()
{
    system("cls"); //añadido para que la pantalla no se llene de mucha información
    string titulo;
    int seleccion;

    cout << "---------------------"<<endl<<"BUSCAR LIBRO"<<endl<<"---------------------"<<endl;
    cout << "Titulo: "<<endl;
    cin>>titulo;
    // Enviar los datos al servidor
    string request = "BUS##" + titulo + "#";
    send(s, request.c_str(), request.size(), 0);
    // Esperar la respuesta del servidor
    char recvBuff[256];
    memset(recvBuff, 0, sizeof(recvBuff));
    recv(s, recvBuff, sizeof(recvBuff), 0);

    if (recvBuff[0] == '0') {
        cout << "No se encontraron libros con ese título." << endl;
        Sleep(SECONDS_TO_CONTINUE);
        menuBuscar();
        return;
    }

    // Mostrar los libros encontrados
    cout << "Libros encontrados:" << endl;


    // Iterar sobre los libros recibidos y mostrarlos con un número de selección
    int numLibro = 1;
    char* libro = strtok(recvBuff, "#");
    while (libro != NULL) {
        cout << numLibro << ". " << libro << endl;
        libro = strtok(NULL, "#");
        numLibro++;
    }

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
        //TO DO: obtendremos el id o nombre del libro seleccionado y llamamos a reservar(), ese dato es el que pasamos [hecho con un int por sólo para probar]
        reservar(seleccion); // seleccion.nombre || seleccion->nombre
        
        /*cout << "Operacion realizada, volviendo al menu anterior..."<<endl;
        Sleep(SECONDS_TO_CONTINUE);
        menuBuscar();*/
    }
}

void buscarAutor()
{
    system("cls"); //añadido para que la pantalla no se llene de mucha información
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
        // Convertir 'seleccion' a string
        string strSeleccion = to_string(seleccion);


        // Enviar los datos al servidor mediante sockets
        string presend = "AUT##" + autor + "#" + strSeleccion + "#";
        strcpy(sendBuff, presend.c_str());
        send(s, sendBuff, sizeof(sendBuff), 0);


        // Esperar la respuesta del Servidor
        printf("Esperando respuesta...");
        recv(s, recvBuff, sizeof(recvBuff), 0);
        printf("Respuesta obtenida");


        if (recvBuff[0] == '1')
        {
            cout << "Conexión realizada con éxito." << endl;
            Sleep(SECONDS_TO_CONTINUE); // esperamos 2 segundos antes de "cambiar de pantalla"
            menuBuscar();
        }
        else
        {
            buscarAutor();
        }

    }
}

void reservar(char nombre)
{
    bool active=true;

    while(active)
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
            active=false;
            break;
        case 2:
            cout<<"Volviendo al menu busqueda"<<endl;
            Sleep(SECONDS_TO_CONTINUE);
            menuBuscar();
            active=false;
            break;
        default:
            cout<<"Introduce un valor valido!"<<endl;
            Sleep(SECONDS_TO_CONTINUE);
            continue;
        }
    }
}