#include <stdio.h>
#include <winsock2.h>
//#include <iostream>
#include <string.h>
#include <stdlib.h>
//#include <vector>
//#include <cstring>

#include "Librerias\BDD\ABDD.h"
#include "Librerias\BDD\sqlite3.h"
#include "Librerias\EstructurasDatos\Fecha.h"
#include "Librerias\EstructurasDatos\Usuario.h"
#include "Librerias\EstructurasDatos\Libro.h"
#include "Librerias\EstructurasDatos\Reserva.h"
#include "Librerias\log.h"

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8080

//BD
sqlite3 *db;
int saveUserBD(char buffer[], int length);

int main(int argc, char *argv[]) 
{
    //Log
    Log *logSer;
    logSer = crear_log("Ficheros/Logs/LogServidor.txt");

    inicializarBDD("BibliotecaDeusto.db", db);

	WSADATA wsaData;
	SOCKET conn_socket;
	SOCKET comm_socket;
	struct sockaddr_in server;
	struct sockaddr_in client;
	char sendBuff[512], recvBuff[512];

	printf("\nInitialising Winsock...\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		printf("Failed. Error Code : ");
        printf("\n");
        escribir_mensaje(logSer, ER, "Fallo al iniciar el Winsock");
		return -1;
	}

	printf("Initialised.\n");
    escribir_mensaje(logSer, INFO, "Winsock iniciado correctamente");

	//SOCKET creation
	if ((conn_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		printf("Could not create socket : "); 
        printf("\n");
        escribir_mensaje(logSer, ER, "Fallo al Crear el Socket");
		WSACleanup();
		return -1;
	}

	printf("Socket created."); 
    printf("\n");
    escribir_mensaje(logSer, INFO, "Socket creado correctamente");

	server.sin_addr.s_addr = inet_addr(SERVER_IP);
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	//BIND (the IP/port with socket)
	if (bind(conn_socket, (struct sockaddr*) &server,
			sizeof(server)) == SOCKET_ERROR) {
		printf( "Bind failed with error code: ");
        printf("\n");
        escribir_mensaje(logSer, ER, "Fallo al portear el Bind");
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}

	printf( "Bind done.");
    printf("\n");
    escribir_mensaje(logSer, INFO, "Bind porteado correctamente");

	//LISTEN to incoming connections (socket server moves to listening mode)
	if (listen(conn_socket, 1) == SOCKET_ERROR) {
		printf( "Listen failed with error code: ");
        printf("\n");
        escribir_mensaje(logSer, ER, "Fallo en el LISTEN de conexiones");
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}

	//ACCEPT incoming connections (server keeps waiting for them)
	printf( "Waiting for incoming connections...");
    printf("\n");
    escribir_mensaje(logSer, INFO, "Esperando conexiones");
	int stsize = sizeof(struct sockaddr);
	comm_socket = accept(conn_socket, (struct sockaddr*) &client, &stsize);
	// Using comm_socket is able to send/receive data to/from connected client
	if (comm_socket == INVALID_SOCKET) {
		printf( "accept failed with error code : ");
        printf("\n");
        escribir_mensaje(logSer, ER, "Fallo en la conexion");
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}
	printf( "Incomming connection from: ");
    printf("(");
    printf(")");
    printf("\n");
    escribir_mensaje(logSer, INFO, "Conexión recibida");

	// Closing the listening sockets (is not going to be used anymore)
	closesocket(conn_socket);

	//SEND and RECEIVE data
	printf( "Waiting for incoming messages from client... ");
    printf("\n");
    do {
        int bytes = recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
        if (bytes > 0) {
            printf( "Message recived");
            printf("\n");
            escribir_mensaje(logSer, INFO, "Mensaje de cliente recibido");
            if(recvBuff[0]=='I' && recvBuff[1]=='N' && recvBuff[2]=='S')
            {
                escribir_mensaje(logSer, INFO, "Mensaje de inicio de sesión recibido");
                if(verifyUserFromSocket(recvBuff, sizeof(recvBuff))==1)
                {
                    sendBuff[0] = '1';
                }else
                {
                    sendBuff[0] = '0';
                }
                printf( "Sending asnwer...");
                printf("\n");
                send(comm_socket, sendBuff, sizeof(recvBuff), 0);
                printf( "Answer sended");
                printf("\n");
                escribir_mensaje(logSer, INFO, "Respuesta enviada sobre inicio de sesión");
            }
            if(recvBuff[0]=='R' && recvBuff[1]=='E' && recvBuff[2]=='G')
            {
                escribir_mensaje(logSer, INFO, "Mensaje de registro de usuario recibido");
                if(saveUserBD(recvBuff, sizeof(recvBuff))==1)
                {
                    sendBuff[0] = '1';
                }else
                {
                    sendBuff[0] = '0';
                }
                printf("Sending asnwer...\n");
                send(comm_socket, sendBuff, sizeof(recvBuff), 0);
                printf("Answer sended\n");
                escribir_mensaje(logSer, INFO, "Respuesta enviada sobre registro de usuario");
            }
            if(recvBuff[0]=='B' && recvBuff[1]=='U' && recvBuff[2]=='S')
            {
                escribir_mensaje(logSer, INFO, "Mensaje de datos de busqueda de libro por titulo recibidos");
                strcpy(sendBuff, searchBooks(recvBuff, sizeof(recvBuff)));
                printf("Sending asnwer...\n");
                send(comm_socket, sendBuff, sizeof(sendBuff), 0);
                printf("Answer sended\n");
                escribir_mensaje(logSer, INFO, "Respuesta sobre datos de busqueda de libro por titulo enviada");
            }
            if(recvBuff[0]=='A' && recvBuff[1]=='U' && recvBuff[2]=='T')
            {
                escribir_mensaje(logSer, INFO, "Mensaje de datos de busqueda de libro por autor recibidos");
                strcpy(sendBuff, searchBooksAuthor(recvBuff, sizeof(recvBuff)));
                printf("Sending asnwer...\n");
                send(comm_socket, sendBuff, sizeof(sendBuff), 0);
                printf("Answer sended\n");
                escribir_mensaje(logSer, INFO, "Respuesta sobre datos de busqueda de libro por autor enviada");
            }
            if(recvBuff[0]=='R' && recvBuff[1]=='E' && recvBuff[2]=='S')
            {
                escribir_mensaje(logSer, INFO, "Mensaje de datos sobre reserva recibidos");
                if(reservarLibro(recvBuff, sizeof(recvBuff))==1)
                {
                    sendBuff[0] = '1';
                }else
                {
                    sendBuff[0] = '0';
                }
                printf("Sending asnwer...\n");
                send(comm_socket, sendBuff, sizeof(recvBuff), 0);
                printf("Answer sended\n");
                escribir_mensaje(logSer, INFO, "Respuesta sobre reserva enviada");
            }
            if(recvBuff[0]=='L' && recvBuff[1]=='S' && recvBuff[2]=='T')
            {
                escribir_mensaje(logSer, INFO, "Mensaje listado de libros recibido");
                strcpy(sendBuff, listBooks(recvBuff, sizeof(recvBuff)));
                printf("Sending asnwer...\n");
                send(comm_socket, sendBuff, sizeof(sendBuff), 0);
                printf("Answer sended\n");
                escribir_mensaje(logSer, INFO, "Respuesta sobre listado de libros enviada");
            }
            if(recvBuff[0]=='B' && recvBuff[1]=='Y' && recvBuff[2]=='E')
            {
                break;
            }  
        }
    } while (1);

    // CLOSING the sockets and cleaning Winsock...
    escribir_mensaje(logSer, INFO, "Cerrando sockets y limpliando Winsock");
    closesocket(comm_socket);
    WSACleanup();

    return 0;
}

int saveUserBD(char buffer[], int length) {
    char* nombre;
    char* apellido;
    char* dni;
    char* correo;
    char* contrasenya;
    int pos = 0;

   	strtok(buffer, "##");
	nombre = strtok(NULL, "#");
    apellido = strtok(NULL, "#");
    dni = strtok(NULL, "#");
    correo = strtok(NULL, "#");
	contrasenya = strtok(NULL, "#");

    printf("%s", nombre);
    printf("%s", apellido);
    printf("%s", dni);
    printf("%s", correo);
    printf("%s", contrasenya);
    
    Usuario aux = {dni, nombre, apellido, correo};
    return insertarUsuario(&aux, contrasenya); 
}