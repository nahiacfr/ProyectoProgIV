
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
void reservar(string nombre);

WSADATA wsaData;
SOCKET s;
struct sockaddr_in server;
char sendBuff[512], recvBuff[512];
string presend;

int main(int argc, char const *argv[])
{
    //Log
    Log *logCl;
    logCl = crear_log((const char*)"Ficheros/Logs/LogCliente.txt");

	cout << endl<<"Initialising Winsock..."<< endl;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        escribir_mensaje(logCl, ER, "Fallo al iniciar el Winsock");
		return -1;
	}

    escribir_mensaje(logCl, INFO, "Winsock iniciado correctamente");

	//SOCKET creation
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        escribir_mensaje(logCl, ER, "Fallo al Crear el Socket");
		WSACleanup();
		return -1;
	}

    escribir_mensaje(logCl, INFO, "Socket creado correctamente");

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
    escribir_mensaje(logCl, INFO, "Conexion establecida");

    mainMenuUser();
    return 0;
}

//Menus del ususario
void mainMenuUser()
{
    //Log
    Log *logCl;
    logCl = crear_log("Ficheros/Logs/LogCliente.txt");

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
            escribir_mensaje(logCl, INFO, "Seleccionado Iniciar sesion");
            inicioSesion();
            active=false;
            break;
        case 2:
            escribir_mensaje(logCl, INFO, "Seleccionado Registrar usuario");
            registraUsuario();
            active=false;
            break;
        case 3:
            escribir_mensaje(logCl, INFO, "Seleccionado Salir");
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
    //Log
    Log *logCl;
    logCl = crear_log("Ficheros/Logs/LogCliente.txt");

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
    escribir_mensaje(logCl, INFO, "Enviado Socket para inicio de sesion");
    //Espera la respuesta del Servidor
    recv(s, recvBuff, sizeof(recvBuff), 0);
    escribir_mensaje(logCl, INFO, "Recivido Socket con la respuesta al inicio de sesion");
    if(recvBuff[0]=='1')
    {
        escribir_mensaje(logCl, INFO, "Usuario valido");
        Sleep(SECONDS_TO_CONTINUE); //esperamos 2 segundos antes de "cambiar de pantalla"
        menuBuscar();
    }else
    {
        escribir_mensaje(logCl, INFO, "Usuario NO valido");
        cout<<"Usuario NO valido."<<endl;
        inicioSesion();
    }
    
    
}

void registraUsuario()
{
    //Log
    Log *logCl;
    logCl = crear_log("Ficheros/Logs/LogCliente.txt");

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
    escribir_mensaje(logCl, INFO, "Enviado Socket para registro de usuario");

    // Espera la respuesta del servidor
    char recvBuff[256];
    memset(recvBuff, 0, sizeof(recvBuff));
    recv(s, recvBuff, sizeof(recvBuff), 0);
    escribir_mensaje(logCl, INFO, "Recivida respuesta del Socket registro de usuario");

    if (recvBuff[0] == '1') {
        escribir_mensaje(logCl, INFO, "Usuario creado correctamente");
        Sleep(SECONDS_TO_CONTINUE);
        menuBuscar();
    }
    else {
        escribir_mensaje(logCl, INFO, "Error al crear el usuario");
        cout << "Error al crear el usuario. Inténtalo de nuevo." << endl;
        registraUsuario();
    }

}

int menuBuscar()
{
    //Log
    Log *logCl;
    logCl = crear_log("Ficheros/Logs/LogCliente.txt");

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
            escribir_mensaje(logCl, INFO, "Seleccionado Buscar libro por titulo");
            buscarTitulo();
            active=false;
            break;
        case 2:
            escribir_mensaje(logCl, INFO, "Seleccionado Buscar libro por autor");
            buscarAutor();
            active=false;
            break;
        case 3:
            escribir_mensaje(logCl, INFO, "Seleccionado Volver menu principal");
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
    //Log
    Log *logCl;
    logCl = crear_log("Ficheros/Logs/LogCliente.txt");

    system("cls"); //añadido para que la pantalla no se llene de mucha información
    string titulo;
    string seleccion;

    cout << "---------------------"<<endl<<"BUSCAR LIBRO"<<endl<<"---------------------"<<endl;
    cout << "Titulo: "<<endl;
    cin>>titulo;
    // Enviar los datos al servidor
    string request = "BUS##" + titulo + "#";
    send(s, request.c_str(), request.size(), 0);
    escribir_mensaje(logCl, INFO, "Enviado Socket buscar libro por titulo");
    // Esperar la respuesta del servidor
    char recvBuff[256];
    memset(recvBuff, 0, sizeof(recvBuff));
    recv(s, recvBuff, sizeof(recvBuff), 0);
    escribir_mensaje(logCl, INFO, "Recivida respuesta del Socket buscar libro por titulo");

    if (recvBuff[0] == '0') {
        escribir_mensaje(logCl, INFO, "NO hay libros con ese titulo");
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
    cout << "Introduzca el ISBN del libro para continuar con la reserva."<<endl<<"Introduzca 0 para volver al menu de busqueda"<<endl;
    //TODO for con print para cada libro que salga
    cin>>seleccion;

    if (seleccion=="0")
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

void reservar(string isbn)
{
    bool active=true;

    while(active)
    {
        cout<<"¿Desea reservar el libro "<< isbn<<endl;
        cout<<"1.Si"<<endl<<"2.No"<<endl;
        
        int result;
        cin>>result;
        
        switch (result)
        {
        case 1:
        //Socket
            presend = "RES##" + isbn + "#";
            send(s, presend.c_str(), presend.size(), 0);
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