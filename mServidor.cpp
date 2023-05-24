
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <winsock2.h>

#define PORT 8080 //numero de puerto utilizado para las conex

int main() {
    WSADATA wsaData;
    SOCKET serverSocket, clientSocket;
    struct sockaddr_in serverAddress, clientAddress;
    char buffer[1024];
    int addrLen, bytesReceived;

    // Inicializar Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("\n error de inicialización \n");
        return 1;
    }

    // Crear el socket
    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("\n error de creación del socket \n");
        return 1;
    }

    // Configurar la dirección del servidor
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(PORT);

    // Vincular el socket a la dirección del servidor
    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        printf("\n error al vincular el socket \n");
        closesocket(serverSocket);
        return 1;
    }

    // Escuchar nuevas conexiones entrantes
    if (listen(serverSocket, 1) == SOCKET_ERROR) {
        printf("\n error al escuchar conexiones \n");
        closesocket(serverSocket);
        return 1;
    }

    printf("\n servidor en espera \n");

    // Aceptar una conexión entrante
    addrLen = sizeof(clientAddress);
    if ((clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &addrLen)) == INVALID_SOCKET) {
        printf("\n error al aceptar conexion entrante \n");
        closesocket(serverSocket);
        return 1;
    }

    printf("\n cliente conectado \n");

    // Recibir datos del cliente
    while ((bytesReceived = recv(clientSocket, buffer, 1040, 0)) > 0) {
        

        
    }

    // Cerrar el socket del cliente
    closesocket(clientSocket);

    // Cerrar el socket del servidor
    closesocket(serverSocket);

    // Finalizar Winsock
    WSACleanup();

    return 0;
}