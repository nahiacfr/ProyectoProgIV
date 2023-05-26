#include <stdio.h>
#include <winsock2.h>
#include <iostream>

using namespace std;

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8080

int verifyUserFromSocket(char buffer[], int length);

int main(int argc, char *argv[]) {

	WSADATA wsaData;
	SOCKET conn_socket;
	SOCKET comm_socket;
	struct sockaddr_in server;
	struct sockaddr_in client;
	char sendBuff[512], recvBuff[512];

	cout << "\nInitialising Winsock..."<<endl;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		cout << "Failed. Error Code : "<< WSAGetLastError()<<endl;
		return -1;
	}

	cout << "Initialised."<<endl;

	//SOCKET creation
	if ((conn_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		cout << "Could not create socket : "<<WSAGetLastError()<<endl;
		WSACleanup();
		return -1;
	}

	cout << "Socket created."<<endl;

	server.sin_addr.s_addr = inet_addr(SERVER_IP);
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	//BIND (the IP/port with socket)
	if (bind(conn_socket, (struct sockaddr*) &server,
			sizeof(server)) == SOCKET_ERROR) {
		cout << "Bind failed with error code: "<< WSAGetLastError()<<endl;
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}

	cout << "Bind done."<<endl;

	//LISTEN to incoming connections (socket server moves to listening mode)
	if (listen(conn_socket, 1) == SOCKET_ERROR) {
		cout << "Listen failed with error code: "<< WSAGetLastError()<<endl;
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}

	//ACCEPT incoming connections (server keeps waiting for them)
	cout << "Waiting for incoming connections..."<<endl;
	int stsize = sizeof(struct sockaddr);
	comm_socket = accept(conn_socket, (struct sockaddr*) &client, &stsize);
	// Using comm_socket is able to send/receive data to/from connected client
	if (comm_socket == INVALID_SOCKET) {
		cout << "accept failed with error code : "<< WSAGetLastError()<<endl;
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}
	cout << "Incomming connection from: "<< inet_ntoa(client.sin_addr) <<"("<< ntohs(client.sin_port)<<")"<<endl;

	// Closing the listening sockets (is not going to be used anymore)
	closesocket(conn_socket);

	//SEND and RECEIVE data
	cout << "Waiting for incoming messages from client... "<<endl;
    do {
        int bytes = recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
        if (bytes > 0) {
            cout << "Message recived"<<endl;
            if(recvBuff[0]=='I' && recvBuff[1]=='N' && recvBuff[2]=='S')
            {
                if(verifyUserFromSocket(recvBuff, sizeof(recvBuff))==1);
                sendBuff[0] = '1';
                cout << "Sending asnwer..."<<endl;
                send(comm_socket, sendBuff, sizeof(recvBuff), 0);
                cout << "Answer sended"<<endl;
            }
            if(recvBuff[0]=='R' && recvBuff[1]=='E' && recvBuff[2]=='G')
            {
                if(saveUserBD(recvBuff, sizeof(recvBuff))==1);
                sendBuff[0] = '1';
                printf("Sending asnwer...\n");
                send(comm_socket, sendBuff, sizeof(recvBuff), 0);
                printf("Answer sended\n");
            }
            if(recvBuff[0]=='B' && recvBuff[1]=='U' && recvBuff[2]=='S')
            {
                if(searchBooks(recvBuff, sizeof(recvBuff))==1);
                sendBuff[0] = '1';
                printf("Sending asnwer...\n");
                send(comm_socket, sendBuff, sizeof(recvBuff), 0);
                printf("Answer sended\n");
            }
            if(recvBuff[0]=='A' && recvBuff[1]=='U' && recvBuff[2]=='T')
            {
                if(searchBooksAuthor(recvBuff, sizeof(recvBuff))==1);
                sendBuff[0] = '1';
                printf("Sending asnwer...\n");
                send(comm_socket, sendBuff, sizeof(recvBuff), 0);
                printf("Answer sended\n");
            }


            if (strcmp(recvBuff, "Bye") == 0)
                break;
        }
    } while (1);


    // CLOSING the sockets and cleaning Winsock...
    closesocket(comm_socket);
    WSACleanup();


    return 0;
}


int verifyUserFromSocket(char buffer[], int length)
{
    char* correo;
    char* contrasenya;
    int pos;
    for (int i = 3; i < length; i++)
    {
        if(buffer[i]=='#')
        {
            pos = i;
            break;
        }
        correo += buffer[i];
    }
    for (int i = pos; i < length; i++)
    {
        if(buffer[i]=='#')
        {
            break;
        }
        contrasenya += buffer[i];
    }
    /*Comprobar si el usuario es correcto*/
    /*Devolver el resultado*/
    return 1;
}
int saveUserBD(char buffer[], int length) {
    char* nombre;
    char* apellido;
    char* dni;
    char* correo;
    char* contrasenya;
    int pos = 0;


    // Obtener los datos del buffer
    for (int i = 3; i < length; i++) {
        if (buffer[i] == '#') {
            pos = i;
            break;
        }
        correo += buffer[i];
    }


    for (int i = pos + 1; i < length; i++) {
        if (buffer[i] == '#') {
            pos = i;
            break;
        }
        contrasenya += buffer[i];
    }


    for (int i = pos + 1; i < length; i++) {
        if (buffer[i] == '#') {
            pos = i;
            break;
        }
        nombre += buffer[i];
    }


    for (int i = pos + 1; i < length; i++) {
        if (buffer[i] == '#') {
            pos = i;
            break;
        }
        apellido += buffer[i];
    }


    for (int i = pos + 1; i < length; i++) {
        if (buffer[i] == '#') {
            break;
        }
        dni += buffer[i];
    }
    // Registrar los datos en la base de datos
    // sqlite3 *db;
    // int result;


    // Inicializar la base de datos
    // inicializarBDD("BibliotecaDeusto.bd", db);
   
    //TO DO insertar usuario en BD  
}
int searchBooks(char buffer[], int length){


}


int searchBooksAuthor(char buffer[], int length){


}
