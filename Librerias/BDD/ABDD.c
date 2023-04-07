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
void insertarUsuario(Usuario *us, char* contrasenya){
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
void obtenerUsuario(char* dniUs){
	//TODO
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
/* Faltan los autores y las editoriales*/
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
void insertarLibrosFichero(char *ruta){
	//TODO
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
void obtenerLibro(char* isbnLib){
	//TODO
}
/* Faltan los autores y las editoriales*/
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
	if (existeAutor(au)==0){
		char sql6[] = "insert into autor values (?, ?, ?);";

		sqlite3_prepare_v2(db, sql6, strlen(sql6) + 1, &stmt, NULL);
		sqlite3_bind_text(stmt, 1, au->id, strlen(au->id), SQLITE_STATIC);
		sqlite3_bind_text(stmt, 2, au->nombre, strlen(au->nombre), SQLITE_STATIC);
	    sqlite3_bind_text(stmt, 3, au->apellidos, strlen(au->apellidos), SQLITE_STATIC);

		result = sqlite3_step(stmt);
		if (result != SQLITE_DONE) {
			printf("Error al insertar el autor\n");
		}else{
			printf("Autor registrado correctamente");
		}

		sqlite3_finalize(stmt);
	}else{
		printf("El autor ya existe\n");
	}
}
void insertarAutoresFichero(char *ruta){
	//TODO
}
void eliminarAutor(Autor *au){
	if (existeAutor(au)==1){
		char sql8[] = "delete from autor where ID = ?";
		sqlite3_prepare_v2(db, sql8, strlen(sql8) + 1, &stmt, NULL);
		sqlite3_bind_text(stmt, 1, au->id, strlen(au->id), SQLITE_STATIC);

		result = sqlite3_step(stmt);
		if (result != SQLITE_DONE) {
			printf("Error al eliminar el autor\n");
		}else{
			printf("El autor %s ha sido eliminado\n", au->nombre);
		}

		sqlite3_finalize(stmt);
	}else{
		printf("El autor no existe\n");
	}
}
int existeAutor(Autor *au){
	char sql9[] = "select * from autor where ID = ?";
	int count = 0;
	sqlite3_prepare_v2(db, sql9, strlen(sql9), &stmt, NULL) ;
	sqlite3_bind_text(stmt, 1, au->id, strlen(au->id), SQLITE_STATIC);

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
void obtenerAutor(int idAu){
	//TODO
}
void listadoAutores(Autor **listaAu, int tamanyoLista){
	char sql10[] = "select * from autor";
	sqlite3_prepare_v2(db, sql10, strlen(sql10), &stmt, NULL) ;

	do {
		result = sqlite3_step(stmt) ;
		Autor aux ={sqlite3_column_int(stmt, 0), (char*)sqlite3_column_text(stmt, 1), sqlite3_column_int(stmt, 2)};
		anyadirAutor(listaAu, tamanyoLista, &aux);
		printf("%s\n", aux.id);
	} while (result == SQLITE_ROW);
}

//Acciones con Editoriales
void insertarEditoriaL(Editorial *ed){
	if (existeEditorial(ed)==0){
		char sql6[] = "insert into editorial values (?, ?);";

		sqlite3_prepare_v2(db, sql6, strlen(sql6) + 1, &stmt, NULL);
		sqlite3_bind_int(stmt, 1, ed->id);
		sqlite3_bind_text(stmt, 2, ed->nombre, strlen(ed->nombre), SQLITE_STATIC);

		result = sqlite3_step(stmt);
		if (result != SQLITE_DONE) {
			printf("Error al insertar la editorial\n");
		}else{
			printf("Editorial registrada correctamente");
		}

		sqlite3_finalize(stmt);
	}else{
		printf("La editorial ya existe\n");
	}
}
void insertarEditorialesFichero(char *ruta){
	//TODO
}
void eliminarEditorial(Editorial *ed){
	if (existeEditorial(ed)==1){
		char sql8[] = "delete from editorial where ID = ?";
		sqlite3_prepare_v2(db, sql8, strlen(sql8) + 1, &stmt, NULL);
		sqlite3_bind_text(stmt, 1, ed->id, strlen(ed->id), SQLITE_STATIC);

		result = sqlite3_step(stmt);
		if (result != SQLITE_DONE) {
			printf("Error al eliminar la editorial\n");
		}else{
			printf("La editorial %s ha sido eliminado\n", ed->nombre);
		}

		sqlite3_finalize(stmt);
	}else{
		printf("La editorial no existe\n");
	}
}
int existeEditorial(Editorial *ed){
	char sql9[] = "select * from editorial where ID = ?";
	int count = 0;
	sqlite3_prepare_v2(db, sql9, strlen(sql9), &stmt, NULL) ;
	sqlite3_bind_text(stmt, 1, ed->id, strlen(ed->id), SQLITE_STATIC);

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
void obtenerEditorial(int idEd){
	//TODO
}
void listadoEditoriales(Editorial **listaEd, int tamanyoLista){
	char sql10[] = "select * from editorial";
	sqlite3_prepare_v2(db, sql10, strlen(sql10), &stmt, NULL) ;

	do {
		result = sqlite3_step(stmt) ;
		Editorial aux ={sqlite3_column_int(stmt, 0), (char*)sqlite3_column_text(stmt, 1)};
		anyadirEditorial(listaEd, tamanyoLista, &aux);
		printf("%s\n", aux.id);
	} while (result == SQLITE_ROW);
}

//Acciones con Reservas
void listadoReservas(Reserva **listaRes, int tamanyoLista, Usuario *us){
	//DOING
	char sql10[] = "select * from reserva where DNI = ?";
	sqlite3_prepare_v2(db, sql10, strlen(sql10), &stmt, NULL) ;
	sqlite3_bind_text(stmt, 1, us->dni, strlen(us->dni), SQLITE_STATIC);

	do {
		result = sqlite3_step(stmt) ;
		Reserva aux ={(char*)sqlite3_column_text(stmt, 0), sqlite3_column_int(stmt, 1),  NULL, NULL};
		anyadirReserva(listaRes, tamanyoLista, &aux);
		printf("%s\n", aux.libro.isbn);
	} while (result == SQLITE_ROW);
}
