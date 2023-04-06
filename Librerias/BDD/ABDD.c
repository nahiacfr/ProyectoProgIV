#include<stdio.h>
#include <string.h>

#include "ABDD.h"
#include "sqlite3.h"
#include "..\EstructurasDatos\Usuario.h"
#include "..\EstructurasDatos\Libro.h"
#include "..\EstructurasDatos\Reserva.h"

sqlite3 *db;
sqlite3_stmt *stmt;
int result;

void inicializarBDD(char *nombre, sqlite3 *dbIni){
    db = dbIni;
	if (sqlite3_open(nombre, &db) == 0){
		printf("Conexion con la BDD exitosa");
	}else{
		printf("Error al conectar con la BDD");
	}
}

void cerrarBDD(sqlite3 *dbM){
    sqlite3_close(dbM);
	sqlite3_close(db);
}

//Acciones con Usuarios
void insertarNuevoUsuario(Usuario *us, char* contrasenya){
	if (existeUsuario(us)==0){
		char sql1[] = "insert into usuario values (?, ?, ?, ?, ?);";

		sqlite3_prepare_v2(db, sql1, strlen(sql1) + 1, &stmt, NULL);
		sqlite3_bind_text(stmt, 1, us->dni, strlen(us->dni), SQLITE_STATIC);
		sqlite3_bind_text(stmt, 2, us->nombre, strlen(us->nombre), SQLITE_STATIC);
	    sqlite3_bind_text(stmt, 3, us->apellidos, strlen(us->apellidos), SQLITE_STATIC);
    	sqlite3_bind_text(stmt, 4, us->correo, strlen(us->correo), SQLITE_STATIC);
    	sqlite3_bind_text(stmt, 5, contrasenya, strlen(contrasenya), SQLITE_STATIC);

		result = sqlite3_step(stmt);
		if (result != SQLITE_DONE) {
			printf("Error al registrar el usuario\n");
		}else{
			printf("Felicidades %s yta estas registrado\n", us->nombre);
		}

		sqlite3_finalize(stmt);
	}else{
		printf("El susuario ya existe\n");
	}
	
}
int existeUsuario(Usuario *us){
    char sql2[] = "select DNI from usuario where DNI = ?";
	int count = 0;
	sqlite3_prepare_v2(db, sql2, strlen(sql2), &stmt, NULL) ;
	sqlite3_bind_text(stmt, 1, us->dni, strlen(us->dni), SQLITE_STATIC);

	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			count++;
		}
	} while (result == SQLITE_ROW);

	sqlite3_finalize(stmt);

	if (count >= 1){
		return 1;
	}else{
		return 0;
	}
}
int verificarContrasenya(Usuario *us, char *contrasenya){

}
void eliminarUsuario(Usuario *us){

}
void listadoUsuarios(Usuario *us){

}

//Acciones con Libros
void insertarLibro(Libro *lib){

}
void insertarLibroFichero(char *ruta){

}
void eliminarLibro(Libro *lib){

}
int existeLibro(Libro *lib){

}
void listadoLibros(Libro *lib){

}

//Acciones con Reservas
void listadoReservas(Usuario *us, Reserva *res){

}
