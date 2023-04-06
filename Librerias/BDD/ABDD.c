#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
		printf("Conexion con la BDD exitosa\n");
	}else{
		printf("Error al conectar con la BDD\n");
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
	char sql3[] = "select contraseña from usuario where DNI = ?";
	int count = 0;
	sqlite3_prepare_v2(db, sql3, strlen(sql3), &stmt, NULL) ;
	sqlite3_bind_text(stmt, 1, us->dni, strlen(us->dni), SQLITE_STATIC);

	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			if(strcmp((char*) sqlite3_column_text(stmt, 0), contrasenya) == 0){
				sqlite3_finalize(stmt);
				printf("Contrasena correcta\n");
				return 1;
			}else{
				sqlite3_finalize(stmt);
				printf("Contrasena incorrecta\n");
				return 0;
			}
		}
	} while (result == SQLITE_ROW);
}
void eliminarUsuario(Usuario *us){
	if (existeUsuario(us)==1){
		char sql4[] = "delete from usuario where DNI = ?";
		sqlite3_prepare_v2(db, sql4, strlen(sql4) + 1, &stmt, NULL);
		sqlite3_bind_text(stmt, 1, us->dni, strlen(us->dni), SQLITE_STATIC);

		result = sqlite3_step(stmt);
		if (result != SQLITE_DONE) {
			printf("Error al eliminar el usuario\n");
		}else{
			printf("El usuario %s ha sido eliminado\n", us->nombre);
		}

		sqlite3_finalize(stmt);
	}else{
		printf("El susuario no existe\n");
	}
}
void listadoUsuarios(Usuario **listaUs, int tamanyoLista){
	char sql5[] = "select * from usuario";
	sqlite3_prepare_v2(db, sql5, strlen(sql5), &stmt, NULL) ;

	do {
		result = sqlite3_step(stmt) ;
		Usuario aux ={(char*)sqlite3_column_text(stmt, 0), (char*)sqlite3_column_text(stmt, 1), (char*)sqlite3_column_text(stmt, 2), (char*)sqlite3_column_text(stmt, 3)};
		anyadirUsuario(listaUs, tamanyoLista, &aux);
	} while (result == SQLITE_ROW);
}

//Acciones con Libros
void insertarLibro(Libro *lib){
	if (existeLibro(lib)==0){
		char sql6[] = "insert into libro values (?, ?, ?);";

		sqlite3_prepare_v2(db, sql6, strlen(sql6) + 1, &stmt, NULL);
		sqlite3_bind_text(stmt, 1, lib->titulo, strlen(lib->titulo), SQLITE_STATIC);
		sqlite3_bind_text(stmt, 2, lib->isbn, strlen(lib->isbn), SQLITE_STATIC);
	    sqlite3_bind_int(stmt, 3, lib->anio);

		result = sqlite3_step(stmt);
		if (result != SQLITE_DONE) {
			printf("Error al insertar el libro\n");
		}else{
			printf("Libro registrado correctamente");
		}

		sqlite3_finalize(stmt);
	}else{
		printf("El libro ya existe\n");
	}
}
void insertarLibroFichero(char *ruta){

}
void eliminarLibro(Libro *lib){
	if (existeLibro(lib)==1){
		char sql8[] = "delete from libro where ISBN = ?";
		sqlite3_prepare_v2(db, sql8, strlen(sql8) + 1, &stmt, NULL);
		sqlite3_bind_text(stmt, 1, lib->isbn, strlen(lib->isbn), SQLITE_STATIC);

		result = sqlite3_step(stmt);
		if (result != SQLITE_DONE) {
			printf("Error al eliminar el libro\n");
		}else{
			printf("El libro %s ha sido eliminado\n", lib->titulo);
		}

		sqlite3_finalize(stmt);
	}else{
		printf("El susuario no libro\n");
	}
}
int existeLibro(Libro *lib){
	char sql9[] = "select ISBN from libro where ISBN = ?";
	int count = 0;
	sqlite3_prepare_v2(db, sql9, strlen(sql9), &stmt, NULL) ;
	sqlite3_bind_text(stmt, 1, lib->isbn, strlen(lib->isbn), SQLITE_STATIC);

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
void listadoLibros(Libro **listaLib, int tamanyoLista){
	char sql10[] = "select * from libro";
	sqlite3_prepare_v2(db, sql10, strlen(sql10), &stmt, NULL) ;

	do {
		result = sqlite3_step(stmt) ;
		Libro aux ={(char*)sqlite3_column_text(stmt, 0), (char*)sqlite3_column_text(stmt, 1), sqlite3_column_int(stmt, 2), NULL, NULL};
		anyadirLibro(listaLib, tamanyoLista, &aux);
		printf("%s\n", aux.isbn);
	} while (result == SQLITE_ROW);
}

//Acciones con Autores
void insertarAutor(Autor *au){
	//TODO
}
void insertarAutorFichero(char *ruta){
	//TODO
}
void eliminarAutor(Autor *au){
	//TODO
}
int existeAutor(Autor *au){
	//TODO
}
void listadoAutores(Autor **listaAu, int tamanyoLista){
	//TODO
}

//Acciones con Editoriales
void insertarEditoriaL(Editorial *ed){
	//TODO
}
void insertarEditorialFichero(char *ruta){
	//TODO
}
void eliminarEditorial(Editorial *ed){
	//TODO
}
int existeEditorial(Editorial *ed){
	//TODO
}
void listadoEditoriales(Editorial **listaEd, int tamanyoLista){
	//TODO
}

//Acciones con Reservas
void listadoReservas(Usuario *us, Reserva *res){

}
