#include <stdio.h>
#include <winsock2.h>
#include <iostream>
#include <string>
#include <vector>
#include <cstring>

//#include "Librerias\BDD\sqlite3.h
#include "Librerias\EstructurasDatos\Fecha.h"
#include "Librerias\EstructurasDatos\Usuario.h"
#include "Librerias\EstructurasDatos\Libro.h"
#include "Librerias\EstructurasDatos\Reserva.h"

using namespace std;

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8080

//BD
/*
sqlite3 *db;
sqlite3_stmt *stmt;
int result;

/*
	Inicializa la Base de Datos

void inicializarBDD(const char* nombre, sqlite3 *dbIni){
    db = dbIni;
	if (sqlite3_open(nombre, &db) == 0){
		printf("Conexion con la BDD exitosa\n");
	}else{
		printf("Error al conectar con la BDD\n");
	}
}
/*
	Cierra la conexion con la Base de Datos

void cerrarBDD(sqlite3 *dbM){
    sqlite3_close(dbM);
	sqlite3_close(db);
}
*/
int verifyUserFromSocket(char buffer[], int length);
int saveUserBD(char buffer[], int length);
int searchBooks(char buffer[], int length, SOCKET comm_socket);
int searchBooksAuthor(char buffer[], int length, SOCKET comm_socket);

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
                if (searchBooks(recvBuff, sizeof(recvBuff), comm_socket) == 1);
                sendBuff[0] = '1';
                printf("Sending asnwer...\n");
                send(comm_socket, sendBuff, sizeof(recvBuff), 0);
                printf("Answer sended\n");
            }
            if(recvBuff[0]=='A' && recvBuff[1]=='U' && recvBuff[2]=='T')
            {
               if (searchBooksAuthor(recvBuff, sizeof(recvBuff), comm_socket) == 1);
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
    // Usuario us;
    // us.correo = correo;
   /*char sql3[] = "select contraseña from usuario where correo = ?";
	int count = 0;
	sqlite3_prepare_v2(db, sql3, strlen(sql3), &stmt, NULL) ;
	sqlite3_bind_text(stmt, 1, us.correo, strlen(us.correo), SQLITE_STATIC);

	do {
        result = sqlite3_step(stmt);
        if (result == SQLITE_ROW) {
            // Compara las dos contraseñas
            // Si coinciden, devuelve 1; si son diferentes, devuelve 0
            if (strcmp((char*)sqlite3_column_text(stmt, 0), contrasenya) == 0) {
                sqlite3_finalize(stmt);
                printf("Contraseña correcta\n");
                return 1;
            } else {
                sqlite3_finalize(stmt);
                printf("Contraseña incorrecta\n");
                return 0;
            }
        }
    } while (result == SQLITE_ROW);
    */
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
    /*
    // Inicializar la base de datos
    sqlite3* db;
    inicializarBDD("BibliotecaDeusto.db", db);
    //datos
    char nombrel[50];  
    char apellidol[50];  
    char dnil[10];  
    char correol[100];  
    char contrasenyal[50];  
    // Insertar usuario en BD
    Usuario *us = new Usuario();;
    us->nombre = nombrel;
    us->apellidos = apellidol;
    us->dni = dnil;
    us->correo = contrasenyal;
    
    char sql1[] = "insert into usuario values (?, ?, ?, ?, ?);";
    sqlite3_stmt* stmt;
    
    sqlite3_prepare_v2(db, sql1, strlen(sql1) + 1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, us->dni, strlen(us->dni), SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, us->nombre, strlen(us->nombre), SQLITE_STATIC);
	sqlite3_bind_text(stmt, 3, us->apellidos, strlen(us->apellidos), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, us->correo, strlen(us->correo), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, contrasenya, strlen(contrasenya), SQLITE_STATIC);

    int result = sqlite3_step(stmt);
    if (result != SQLITE_DONE)
    {
        printf("Error al registrar el usuario\n");
    }
    else
    {
        printf("Felicidades %s ya estás registrado\n", us->nombre);
    }

    sqlite3_finalize(stmt);
    cerrarBDD(db);
    */
}
int searchBooks(char buffer[], int length, SOCKET comm_socket){
    string titulos;

    // Obtener el título del libro enviado desde el cliente
    string titulo = buffer + 3; // Ignorar los primeros 3 caracteres ("BUS")

    /*
    // Realizar la búsqueda en la base de datos
    
    string sql = "SELECT * FROM libro WHERE titulo LIKE '%" + titulo + "%';";
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    // Ejecutar la consulta y recopilar los resultados
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        //hacer lisat con los resultados
        const char* titulo = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        listaTitulos.push_back(titulo);
    }

    sqlite3_finalize(stmt);
    string response;
    for (const std::string& titulo : listaTitulos) {
    response += titulo + "#";
    }
    */
    // Enviar la respuesta al cliente
    //send(comm_socket, response.c_str(), response.size(), 0);

    // Crear manualmente la lista de libros
    vector<string> listaTitulos = {"IT", "Romeo y Julieta", "Harry Potter"};
    // Enviar la respuesta al cliente
    string response;
    for (const string& titulo : listaTitulos) {
        response += titulo + "#";
    }
    send(comm_socket, response.c_str(), response.size(), 0);
    return 1;
}


int searchBooksAuthor(char buffer[], int length, SOCKET comm_socket){
std::vector<std::string> titulos;

    // Obtener el autor del libro enviado desde el cliente
    string autor = buffer + 5; // Ignorar los primeros 5 caracteres ("BUS")

    /*
    // Realizar la búsqueda en la base de datos
    
    // Consultar la base de datos para obtener el ID del autor
    std::string sql1 = "SELECT id_autor FROM Escritor WHERE nombre_autor LIKE '%" + autor + "%';";
    sqlite3_prepare_v2(db, sql1.c_str(), -1, &stmt, nullptr);

    // Verificar si se encontró el autor
    if (sqlite3_step(stmt) != SQLITE_ROW) {
        sqlite3_finalize(stmt);
        return 0; // No se encontró el autor
    }
    // Obtener el ID del autor
    int idAutor = sqlite3_column_int(stmt, 0);

    // Liberar recursos
    sqlite3_finalize(stmt);

    // Consultar la base de datos para obtener los ISBN de los libros escritos por el autor
    std::string sql2 = "SELECT isbn FROM Autor WHERE id_autor = " + std::to_string(idAutor) + ";";
    sqlite3_prepare_v2(db, sql2.c_str(), -1, &stmt, nullptr);

    // Obtener los ISBN de los libros
    std::vector<std::string> isbnList;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::string isbn(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
        isbnList.push_back(isbn);
    }

    // Liberar recursos
    sqlite3_finalize(stmt);

    // Consultar la base de datos para obtener los títulos de los libros
    std::vector<std::string> tituloList;
    for (const std::string& isbn : isbnList) {
        std::string sql3 = "SELECT titulo FROM Libro WHERE isbn = '" + isbn + "';";
        sqlite3_prepare_v2(db, sql3.c_str(), -1, &stmt, nullptr);

        // Obtener el título del libro
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            std::string titulo(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
            tituloList.push_back(titulo);
        }

        // Liberar recursos
        sqlite3_finalize(stmt);
    }

    // Enviar los títulos al cliente a través del socket
    std::string response;
    for (const std::string& titulo : tituloList) {
        response += titulo + "#";
    }
    */
    // Enviar la respuesta al cliente
    //send(comm_socket, response.c_str(), response.size(), 0);
    //Imaginando que el autor introducido es Stephen King
     // Crear manualmente la lista de libros de Stephen King
    vector<string> listaTitulos = {"It", "The Shining", "Misery", "Pet Sematary", "The Stand"};

    // Enviar la respuesta al cliente
    string response;
    for (const string& titulo : listaTitulos) {
        response += titulo + "#";
    }
    send(comm_socket, response.c_str(), response.size(), 0);

    return 1;

}
