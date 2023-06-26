#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <winsock2.h>
#include <string>
#include <windows.h> //necesario para el sleep();
#include "Librerias\CPP\logCPP.h"
extern "C"
{
    //#include "Librerias\log.h"
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
void listarLibros();
void preReserva();

WSADATA wsaData;
SOCKET s;
struct sockaddr_in server;
char sendBuff[512], recvBuff[512];
string presend;
string usuarioActual;

int main(int argc, char const *argv[])
{
    //Log
    Log *logCl = new Log;
    logCl = logCl->crear_log("Ficheros/Logs/LogCliente.txt");
    /*if (logCl != nullptr) {
        logCl->escribir_mensaje(logCl, TipoMensaje::INFO, "Este es un mensaje de información");
    } else {
        cout << endl << "ERROR" << endl;
    }*/

    cout << endl << "Initialising Winsock..." << endl;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		logCl->escribir_mensaje(logCl, TipoMensaje::ER, "Fallo al iniciar el Winsock");
		return -1;
	}

    logCl->escribir_mensaje(logCl, TipoMensaje::INFO, "Winsock iniciado correctamente");

	//SOCKET creation
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        logCl->escribir_mensaje(logCl, TipoMensaje::ER, "Fallo al Crear el Socket");
		WSACleanup();
		return -1;
	}

    logCl->escribir_mensaje(logCl, TipoMensaje::INFO, "Socket creado correctamente");

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
    logCl->escribir_mensaje(logCl, TipoMensaje::INFO, "Conexion establecida");

    mainMenuUser();
    logCl->cerrar_log(logCl);
    return 0;
}

//Menus del ususario
void mainMenuUser()
{
    //Log
    Log *logCl = new Log;
    logCl = logCl->crear_log("Ficheros/Logs/LogCliente.txt");

    system("cls"); //añadido para que la pantalla no se llene de mucha información
    char str[MAX_OPTN];
    bool active=true;

    while(active)
    {
        logCl->escribir_mensaje(logCl, TipoMensaje::INFO, "Menu biblioteca");
        cout << "---------------------"<< endl<<"BIBLIOTECA DEUSTO"<<endl<<"---------------------"<<endl;
        cout << "Bienvenido a la biblioteca"<<endl;
        cout << "1.Iniciar sesion"<< endl<<"2.Nuevo usuario"<<endl<<"3.Salir"<<endl;
        
        int result;
        cin>>result;
        
        switch (result)
        {
        case 1:
            logCl->escribir_mensaje(logCl, TipoMensaje::INFO, "Seleccionado Iniciar sesion");
            inicioSesion();
            active=false;
            break;
        case 2:
            logCl->escribir_mensaje(logCl, TipoMensaje::INFO, "Seleccionado Registrar usuario");
            registraUsuario();
            active=false;
            break;
        case 3:
            logCl->escribir_mensaje(logCl, TipoMensaje::INFO, "Seleccionado Salir");
            cout << "Has salido de la app"<<endl;
            active=false;
            send(s, "BYE", 3, 0);
            break;
        default:
            logCl->escribir_mensaje(logCl, TipoMensaje::INFO, "Seleccion Nula");
            cout << "Introduce un valor valido!"<<endl;
            Sleep(SECONDS_TO_CONTINUE);
            continue;
        }
    }
    logCl->cerrar_log(logCl);
    closesocket(s);
	WSACleanup();
}

void inicioSesion()
{
    //Log
    Log *logCl = new Log;
    logCl = logCl->crear_log("Ficheros/Logs/LogCliente.txt");

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
    logCl->escribir_mensaje(logCl, TipoMensaje::INFO, "Enviado Socket para inicio de sesion");
    //Espera la respuesta del Servidor
    recv(s, recvBuff, sizeof(recvBuff), 0);
    logCl->escribir_mensaje(logCl, TipoMensaje::INFO, "Recivido Socket con la respuesta al inicio de sesion");
    if(recvBuff[0]=='1')
    {
        usuarioActual = correo;
        logCl->escribir_mensaje(logCl, TipoMensaje::INFO, "Usuario valido");
        cout <<"Usuario valido"<<endl;
        Sleep(SECONDS_TO_CONTINUE); //esperamos 2 segundos antes de "cambiar de pantalla"
        menuBuscar();
    }else
    {
        logCl->escribir_mensaje(logCl, TipoMensaje::INFO, "Usuario NO valido");
        cout<<"Usuario NO valido."<<endl;
        inicioSesion();
    }
    
    logCl->cerrar_log(logCl);
}

void registraUsuario()
{
    //Log
    Log *logCl = new Log;
    logCl = logCl->crear_log("Ficheros/Logs/LogCliente.txt");

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
    logCl->escribir_mensaje(logCl, TipoMensaje::INFO, "Enviado Socket para registro de usuario");

    // Espera la respuesta del servidor
    memset(recvBuff, 0, sizeof(recvBuff));
    recv(s, recvBuff, sizeof(recvBuff), 0);
    logCl->escribir_mensaje(logCl, TipoMensaje::INFO, "Recivida respuesta del Socket registro de usuario");

    if (recvBuff[0] == '1') {
        logCl->escribir_mensaje(logCl, TipoMensaje::INFO, "Usuario creado correctamente");
        usuarioActual = correo;
        Sleep(SECONDS_TO_CONTINUE);
        menuBuscar();
    }
    else {
        logCl->escribir_mensaje(logCl, TipoMensaje::INFO, "Error al crear el usuario");
        cout << "Error al crear el usuario. Inténtalo de nuevo." << endl;
        registraUsuario();
    }

    logCl->cerrar_log(logCl);
}

int menuBuscar()
{
    //Log
    Log *logCl = new Log;
    logCl = logCl->crear_log("Ficheros/Logs/LogCliente.txt");

    bool active=true;

    while(active)
    {
        system("cls"); //añadido para que la pantalla no se llene de mucha información
        cout << "---------------------"<<endl<<"MENU BUSCAR"<<endl<<"---------------------"<<endl;
        cout << "1.Buscar libro por titulo"<<endl<<"2.Buscar libro por autor"<<endl<<"3.Listar todos los libros"<<endl<<"4.Volver menu principal"<<endl<<"5.Salir"<<endl;
        
        int result;
        cout << endl << "Seleccion: "<<endl;
        cin>>result;
        switch (result)
        {
        case 1:
            logCl->escribir_mensaje(logCl, TipoMensaje::INFO, "Seleccionado Buscar libro por titulo");
            buscarTitulo();
            active=false;
            break;
        case 2:
            logCl->escribir_mensaje(logCl, TipoMensaje::INFO, "Seleccionado Buscar libro por autor");
            buscarAutor();
            active=false;
            break;
        case 3:
            logCl->escribir_mensaje(logCl, TipoMensaje::INFO, "Seleccionado listar libros");
            listarLibros();
            active=false;
            break;
        case 4:
            logCl->escribir_mensaje(logCl, TipoMensaje::INFO, "Seleccionado Volver menu principal");
            cout << "Volviendo al menu principal..."<<endl;
            Sleep(SECONDS_TO_CONTINUE);
            mainMenuUser();
            active=false;
            break;
        case 5:
            logCl->escribir_mensaje(logCl, TipoMensaje::INFO, "Seleccionado Salir");
            cout << "Has salido de la app"<<endl;
            active=false;
            send(s, "BYE", 3, 0);
            break;
        default:
            cout<<"Introduce un valor valido!"<<endl;
            Sleep(SECONDS_TO_CONTINUE);
            continue;
        }

        return result;
    }
    
    logCl->cerrar_log(logCl);
}

void buscarTitulo()
{
    //Log
    Log *logCl = new Log;
    logCl = logCl->crear_log("Ficheros/Logs/LogCliente.txt");

    system("cls"); //añadido para que la pantalla no se llene de mucha información
    char titulo[30];
    string seleccion;

    cout << "---------------------"<<endl<<"BUSCAR LIBRO"<<endl<<"---------------------"<<endl;
    cout << "Titulo: "<<endl;
    cin.ignore();
    cin.getline(titulo, 30);
    // Enviar los datos al servidor
    string request = "BUS##";
    request.append(titulo);
    request.append("#");
    send(s, request.c_str(), request.size(), 0);
    logCl->escribir_mensaje(logCl, TipoMensaje::INFO, "Enviado Socket buscar libro por titulo");
    // Esperar la respuesta del servidor
    memset(recvBuff, 0, sizeof(recvBuff));
    recv(s, recvBuff, sizeof(recvBuff), 0);
    logCl->escribir_mensaje(logCl, TipoMensaje::INFO, "Recibida respuesta del Socket buscar libro por titulo");

    // Mostrar los libros encontrados
    cout << "Libros encontrados:" << endl;

    cout << recvBuff << endl;
    //buscar en la base de datos los títulos que coincidan; ej: si buscas "noche" puede salir "Las mil y una noches" y "Guardianes de la noche" etc
    preReserva();
    logCl->cerrar_log(logCl);
}

void buscarAutor()
{
    //Log
    Log *logCl = new Log;
    logCl = logCl->crear_log("Ficheros/Logs/LogCliente.txt");

    system("cls"); //añadido para que la pantalla no se llene de mucha información
    char str[MAX_LINE];
    char nombreAutor[20];
    char apellidoAutor[20];
    string seleccion;
    
    cout<<"---------------------"<<endl<<"BUSCAR AUTOR"<<endl<<"---------------------"<<endl;
    cout<<"Nombre del autor: "<<endl;
    cin.ignore();
    cin.getline(nombreAutor, 20);
    cout<<"Apellido del autor: "<<endl;
    cin.getline(apellidoAutor, 20);
    
    string request = "AUT##";
    request.append(nombreAutor);
    request.append("#");
    request.append(apellidoAutor);
    request.append("#");
    send(s, request.c_str(), request.size(), 0);
    logCl->escribir_mensaje(logCl, TipoMensaje::INFO, "Enviado Socket buscar libro por autor");
    // Esperar la respuesta del servidor
    memset(recvBuff, 0, sizeof(recvBuff));
    recv(s, recvBuff, sizeof(recvBuff), 0);
    logCl->escribir_mensaje(logCl, TipoMensaje::INFO, "Recibida respuesta del Socket buscar libro por autor");

   // Mostrar los libros encontrados
    cout << "Libros encontrados:" << endl;

    cout << recvBuff << endl;
    //buscar en la base de datos los títulos que coincidan; ej: si buscas "noche" puede salir "Las mil y una noches" y "Guardianes de la noche" etc
    preReserva();
    
    logCl->cerrar_log(logCl);
}

void listarLibros()
{
    //Log
    Log *logCl = new Log;
    logCl = logCl->crear_log("Ficheros/Logs/LogCliente.txt");

    system("cls"); //añadido para que la pantalla no se llene de mucha información
    char reservados[30];
    string seleccion;

    cout << "---------------------"<<endl<<"LISTA DE LIBROS"<<endl<<"---------------------"<<endl;
    cout << "1.Mostrar todos los libros: "<<endl<< "2.Mostrar solo libros NO reservados: "<<endl;
    cin.ignore();
    cin.getline(reservados, 30);
    // Enviar los datos al servidor
    string request = "LST##";
    request.append(reservados);
    request.append("#");
    send(s, request.c_str(), request.size(), 0);
    logCl->escribir_mensaje(logCl, TipoMensaje::INFO, "Enviado Socket listar libros");
    // Esperar la respuesta del servidor
    memset(recvBuff, 0, sizeof(recvBuff));
    recv(s, recvBuff, sizeof(recvBuff), 0);
    logCl->escribir_mensaje(logCl, TipoMensaje::INFO, "Recibida respuesta del Socket listar libros");

    // Mostrar los libros encontrados
    cout << "Libros:" << endl;

    cout << recvBuff << endl;
    //buscar en la base de datos los títulos que coincidan; ej: si buscas "noche" puede salir "Las mil y una noches" y "Guardianes de la noche" etc
    preReserva();
    
    logCl->cerrar_log(logCl);
}

void reservar(string isbn)
{
    //Log
    Log *logCl = new Log;
    logCl = logCl->crear_log("Ficheros/Logs/LogCliente.txt");

    bool active=true;

    while(active)
    {
        logCl->escribir_mensaje(logCl, TipoMensaje::INFO, "Reserva iniciada");
        cout<<"Desea reservar el libro "<< isbn<<"?"<<endl;
        cout<<"1.Si"<<endl<<"2.No"<<endl;
        
        int result;
        
        cin>>result;
        
        string dia;
        string mes;
        string anyo;

        switch (result)
        {
        case 1:
            cout << "Introduzca la fecha de inicio de la reserva" << endl;
            cout << "Dia: " << endl;
            cin >>dia;
            cout << "Mes: " << endl;
            cin >>mes;
            cout << "Anyo: " << endl;
            cin >>anyo;
        //Socket
            presend = "RES##" + isbn + "#" + usuarioActual + "#" + dia + "#" + mes + "#" + anyo + "#";
            send(s, presend.c_str(), presend.size(), 0);
            logCl->escribir_mensaje(logCl, TipoMensaje::INFO, "Reserva realizada");

             // Espera la respuesta del servidor
            memset(recvBuff, 0, sizeof(recvBuff));
            recv(s, recvBuff, sizeof(recvBuff), 0);
            logCl->escribir_mensaje(logCl, TipoMensaje::INFO, "Recivida respuesta del Socket realizar reserva");

            if (recvBuff[0] == '1') {
                logCl->escribir_mensaje(logCl, TipoMensaje::INFO, "Reserva realizada correctamente");
                Sleep(SECONDS_TO_CONTINUE);
                menuBuscar();
            }
            else {
                logCl->escribir_mensaje(logCl, TipoMensaje::INFO, "Error al realizar la reserva");
                cout << "Error al Realizar la Reserva." << endl;
                Sleep(SECONDS_TO_CONTINUE);
                menuBuscar();
            }

            cout<<"Reserva realizada, tiene X dias para devolverlo"<<endl;
            cout<<"Volviendo al menu anterior..."<<endl;
            Sleep(SECONDS_TO_CONTINUE);
            menuBuscar();
            active=false;
            break;
        case 2:
            logCl->escribir_mensaje(logCl, TipoMensaje::INFO, "Reserva cancelada");
            cout<<"Volviendo al menu busqueda"<<endl;
            Sleep(SECONDS_TO_CONTINUE);
            menuBuscar();
            active=false;
            break;
        default:
            logCl->escribir_mensaje(logCl, TipoMensaje::INFO, "Valor incorrecto");
            cout<<"Introduce un valor valido!"<<endl;
            Sleep(SECONDS_TO_CONTINUE);
            continue;
        }
    }
    
    logCl->cerrar_log(logCl);
}

void preReserva()
{
    Log *logCl = new Log;
    logCl = logCl->crear_log("Ficheros/Logs/LogCliente.txt");

    string seleccion;
    string isbn;
    cout << "------------------------------------------"<<endl;
    cout << "1. Reservar libro"<<endl<<"2. Volver al menu busqueda"<<endl<<"3. Salir"<<endl;
    //TODO for con print para cada libro que salga
    cin>>seleccion;
    cout << "Check1" << endl;
    if (seleccion == "1")
    {
        logCl->escribir_mensaje(logCl, TipoMensaje::INFO, "Seleccionado Reservar libro");
        cout << "Introduzca el ISBN:"<<endl;
        cin >> isbn;
        reservar(isbn);
        cout << "Operacion realizada, volviendo al menu anterior..."<<endl;
        Sleep(SECONDS_TO_CONTINUE);
        menuBuscar();
       
    }else if (seleccion == "2"){
        logCl->escribir_mensaje(logCl, TipoMensaje::INFO, "Seleccionado Volver al menu busqueda");
        Sleep(SECONDS_TO_CONTINUE);
        menuBuscar();
    }else if (seleccion == "3"){
        logCl->escribir_mensaje(logCl, TipoMensaje::INFO, "Seleccionado Salir");
        cout << "Has salido de la app"<<endl;
        send(s, "BYE", 3, 0);
    }
}