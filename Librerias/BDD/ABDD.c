#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ABDD.h"
#include "sqlite3.h"
#include "..\EstructurasDatos\Fecha.h"
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
	if (existeUsuario(us->dni)==0){
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
int existeUsuario(char *dni){
    char sql2[] = "select DNI from usuario where DNI = ?";
	int count = 0;
	sqlite3_prepare_v2(db, sql2, strlen(sql2), &stmt, NULL) ;
	sqlite3_bind_text(stmt, 1, dni, strlen(dni), SQLITE_STATIC);

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
void eliminarUsuario(char *dni){
	if (existeUsuario(dni)==1){
		char sql4[] = "delete from usuario where DNI = ?";
		sqlite3_prepare_v2(db, sql4, strlen(sql4) + 1, &stmt, NULL);
		sqlite3_bind_text(stmt, 1, dni, strlen(dni), SQLITE_STATIC);

		result = sqlite3_step(stmt);
		if (result != SQLITE_DONE) {
			printf("Error al eliminar el usuario\n");
		}else{
			printf("El usuario %s ha sido eliminado\n", dni);
		}

		sqlite3_finalize(stmt);
	}else{
		printf("El susuario no existe\n");
	}
}
Usuario obtenerUsuario(Usuario *usAux, char* dniUs){
	/*char sql3[] = "select * from usuario where DNI = ?";
	sqlite3_prepare_v2(db, sql3, strlen(sql3), &stmt, NULL) ;
	sqlite3_bind_text(stmt, 1, dniUs, strlen(dniUs), SQLITE_STATIC);
	
	result = sqlite3_step(stmt);
	usAux->dni = (char*) sqlite3_column_text(stmt, 0);
	usAux->nombre = (char*) sqlite3_column_text(stmt, 1);
	usAux->apellidos = (char*) sqlite3_column_text(stmt, 2);
	usAux->correo = (char*) sqlite3_column_text(stmt, 3);
*/
	char sql5[] = "select * from usuario where DNI = ?";
	sqlite3_prepare_v2(db, sql5, strlen(sql5), &stmt, NULL);
	sqlite3_bind_text(stmt, 1, dniUs, strlen(dniUs), SQLITE_STATIC);

	result = sqlite3_step(stmt) ;
	Usuario aux ={(char*)sqlite3_column_text(stmt, 0), (char*)sqlite3_column_text(stmt, 1), (char*)sqlite3_column_text(stmt, 2), (char*)sqlite3_column_text(stmt, 3)};
	sqlite3_finalize(stmt);
	*usAux = aux;
	return *usAux;
}
void imprimirListadoUsuarios(){
	char sql5[] = "select * from usuario";
	sqlite3_prepare_v2(db, sql5, strlen(sql5), &stmt, NULL);
	
	printf("///////////////////////\n");
	printf("//Listado de Usuarios//\n");
	printf("///////////////////////\n");
	do {
		result = sqlite3_step(stmt);
		if((char*)sqlite3_column_text(stmt, 0)!= NULL){
			printf("DNI: %s\nNombre: %s\nApellidos: %s\nCorreo electronico: %s\n",(char*)sqlite3_column_text(stmt, 0), (char*)sqlite3_column_text(stmt, 1), (char*)sqlite3_column_text(stmt, 2), (char*)sqlite3_column_text(stmt, 3));
			printf("----------------------------------------\n");
		}
	} while (result == SQLITE_ROW);
	sqlite3_finalize(stmt);
}

//Acciones con Libros
/* Faltan los autores y las editoriales*/
void insertarLibro(Libro *lib){
	if (existeLibro(lib->isbn)==0){
		char sql6[] = "insert into libro values (?, ?, ?);";
		sqlite3_prepare_v2(db, sql6, strlen(sql6) + 1, &stmt, NULL);
		sqlite3_bind_text(stmt, 1, lib->titulo, strlen(lib->titulo), SQLITE_STATIC);
		sqlite3_bind_text(stmt, 2, lib->isbn, strlen(lib->isbn), SQLITE_STATIC);
	    sqlite3_bind_int(stmt, 3, lib->anio);
		result = sqlite3_step(stmt);
		if (result != SQLITE_DONE) {
			printf("Error al insertar el libro\n");
		}else{
			printf("Libro registrado correctamente\n");
		}
		sqlite3_finalize(stmt);

		char sql2[] = "insert into autor values (?, ?);";
		sqlite3_prepare_v2(db, sql2, strlen(sql2) + 1, &stmt, NULL);
		sqlite3_bind_text(stmt, 1, lib->isbn, strlen(lib->titulo), SQLITE_STATIC);
		sqlite3_bind_int(stmt, 2, lib->autor.id);
		result = sqlite3_step(stmt);
		if (result != SQLITE_DONE) {
			printf("Error al insertar la relacio autor\n");
		}else{
			printf("Relacio autor registrada correctamente\n");
		}
		sqlite3_finalize(stmt);

		char sql3[] = "insert into pertenece values (?, ?);";
		sqlite3_prepare_v2(db, sql3, strlen(sql3) + 1, &stmt, NULL);
		sqlite3_bind_text(stmt, 1, lib->isbn, strlen(lib->titulo), SQLITE_STATIC);
		sqlite3_bind_int(stmt, 2, lib->editorial.id);
		result = sqlite3_step(stmt);
		if (result != SQLITE_DONE) {
			printf("Error al insertar la relacion pertenece\n");
		}else{
			printf("Relacion pertenece registrada correctamente\n");
		}
		sqlite3_finalize(stmt);
	}else{
		printf("El libro ya existe\n");
	}
}
void insertarLibrosFichero(char *ruta){
	//TODO
}
void eliminarLibro(char *isbn){
	if (existeLibro(isbn)==1){
		char sql8[] = "delete from libro where ISBN = ?";
		sqlite3_prepare_v2(db, sql8, strlen(sql8) + 1, &stmt, NULL);
		sqlite3_bind_text(stmt, 1, isbn, strlen(isbn), SQLITE_STATIC);
		result = sqlite3_step(stmt);
		if (result != SQLITE_DONE) {
			printf("Error al eliminar el libro\n");
		}else{
			printf("El libro %s ha sido eliminado\n", isbn);
		}
		sqlite3_finalize(stmt);

		char sql2[] = "delete from autor where ISBN = ?";
		sqlite3_prepare_v2(db, sql2, strlen(sql2) + 1, &stmt, NULL);
		sqlite3_bind_text(stmt, 1, isbn, strlen(isbn), SQLITE_STATIC);
		result = sqlite3_step(stmt);
		if (result != SQLITE_DONE) {
			printf("Error al eliminar la relacion autor\n");
		}else{
			printf("La relacion autor ha sido eliminado\n");
		}
		sqlite3_finalize(stmt);

		char sql3[] = "delete from pertenece where ISBN = ?";
		sqlite3_prepare_v2(db, sql3, strlen(sql3) + 1, &stmt, NULL);
		sqlite3_bind_text(stmt, 1, isbn, strlen(isbn), SQLITE_STATIC);
		result = sqlite3_step(stmt);
		if (result != SQLITE_DONE) {
			printf("Error al eliminar la relacion pertenece\n");
		}else{
			printf("La relacion pertenece ha sido eliminado\n");
		}
		sqlite3_finalize(stmt);
	}else{
		printf("El libro no existe\n");
	}
}
int existeLibro(char *isbn){
	char sql9[] = "select * from libro where ISBN = ?";
	int count = 0;
	sqlite3_prepare_v2(db, sql9, strlen(sql9), &stmt, NULL) ;
	sqlite3_bind_text(stmt, 1, isbn, strlen(isbn), SQLITE_STATIC);

	do {
		result = sqlite3_step(stmt);
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
Libro obtenerLibro(char* isbnLib){
	char sql1[] = "select * from libro where ISBN = ?";
	sqlite3_prepare_v2(db, sql1, strlen(sql1), &stmt, NULL) ;
	sqlite3_bind_text(stmt, 1, isbnLib, strlen(isbnLib), SQLITE_STATIC);
	Libro libAux;
	result = sqlite3_step(stmt) ;
	libAux.isbn = (char*) sqlite3_column_text(stmt, 0);
	libAux.titulo = (char*) sqlite3_column_text(stmt, 1);
	libAux.anio = sqlite3_column_int(stmt, 2);
	sqlite3_finalize(stmt);

	char sql2[] = "select * from autor where ISBN = ?";
	sqlite3_prepare_v2(db, sql2, strlen(sql2), &stmt, NULL) ;
	sqlite3_bind_text(stmt, 1, isbnLib, strlen(isbnLib), SQLITE_STATIC);
	libAux.autor = obtenerAutor(sqlite3_column_int(stmt, 1));
	sqlite3_finalize(stmt);

	char sql3[] = "select * from pertenece where ISBN = ?";
	sqlite3_prepare_v2(db, sql3, strlen(sql3), &stmt, NULL) ;
	sqlite3_bind_text(stmt, 1, isbnLib, strlen(isbnLib), SQLITE_STATIC);
	libAux.editorial = obtenerEditorial(sqlite3_column_int(stmt, 1));
	sqlite3_finalize(stmt);

	return libAux;
}

void imprimirListadoLibros(){
	char sql10[] = "select * from libro";
	sqlite3_prepare_v2(db, sql10, strlen(sql10), &stmt, NULL) ;

	printf("/////////////////////\n");
	printf("//Listado de Libros//\n");
	printf("/////////////////////\n");
	do {
		result = sqlite3_step(stmt);
		if((char*)sqlite3_column_text(stmt, 1)!= NULL){
			printf("ISBN: %s\nTitulo: %s\nAnyo de publicacion: %i\n",(char*)sqlite3_column_text(stmt, 1), (char*)sqlite3_column_text(stmt, 0), sqlite3_column_int(stmt, 2));
			printf("----------------------------------------\n");
		}
	} while (result == SQLITE_ROW);
	sqlite3_finalize(stmt);
}

//Acciones con Autores
void insertarAutor(Autor *au){
	if (existeAutor(au->id)==0){
		char sql6[] = "insert into escritor values (?, ?, ?);";

		sqlite3_prepare_v2(db, sql6, strlen(sql6) + 1, &stmt, NULL);
		sqlite3_bind_int(stmt, 1, au->id);
		sqlite3_bind_text(stmt, 2, au->nombre, strlen(au->nombre), SQLITE_STATIC);
	    sqlite3_bind_text(stmt, 3, au->apellidos, strlen(au->apellidos), SQLITE_STATIC);

		result = sqlite3_step(stmt);
		if (result != SQLITE_DONE) {
			printf("Error al insertar el autor\n");
		}else{
			printf("Autor registrado correctamente\n");
		}

		sqlite3_finalize(stmt);
	}else{
		printf("El autor ya existe\n");
	}
}
void insertarAutoresFichero(char *ruta){
	//TODO
}
void eliminarAutor(int idAu){
	if (existeAutor(idAu)==1){
		char sql8[] = "delete from escritor where ID = ?";
		sqlite3_prepare_v2(db, sql8, strlen(sql8) + 1, &stmt, NULL);
		sqlite3_bind_int(stmt, 1, idAu);

		result = sqlite3_step(stmt);
		if (result != SQLITE_DONE) {
			printf("Error al eliminar el autor\n");
		}else{
			printf("El autor %s ha sido eliminado\n", idAu);
		}

		sqlite3_finalize(stmt);
	}else{
		printf("El autor no existe\n");
	}
}
int existeAutor(int idAu){
	char sql9[] = "select * from escritor where ID = ?";
	int count = 0;
	sqlite3_prepare_v2(db, sql9, strlen(sql9), &stmt, NULL) ;
	sqlite3_bind_int(stmt, 1, idAu);

	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			count++;
			printf("%i\n", sqlite3_column_int(stmt, 0));
		}
	} while (result == SQLITE_ROW);

	sqlite3_finalize(stmt);
	printf("%i\n", count);
	if (count >= 1){
		return 1;
	}else{
		return 0;
	}
}
Autor obtenerAutor(int idAu){
	char sql3[] = "select * from escritor where ID = ?";
	sqlite3_prepare_v2(db, sql3, strlen(sql3), &stmt, NULL) ;
	sqlite3_bind_int(stmt, 1, idAu);
	Autor auAux;
	do {
		result = sqlite3_step(stmt) ;
		auAux.id = sqlite3_column_int(stmt, 0);
		auAux.nombre = (char*) sqlite3_column_text(stmt, 1);
		auAux.apellidos = (char*) sqlite3_column_text(stmt, 2);
	} while (result == SQLITE_ROW);
	return auAux;
}
Autor obtenerAutorPorLibro(char *isbn){
	Autor au;
	//TODO
	return au;
}
void imprimirListadoAutores(){
	char sql10[] = "select * from escritor";
	sqlite3_prepare_v2(db, sql10, strlen(sql10), &stmt, NULL) ;

	printf("//////////////////////\n");
	printf("//Listado de Autores//\n");
	printf("//////////////////////\n");
	do {
		result = sqlite3_step(stmt);
		if((char*)sqlite3_column_text(stmt, 0)!= NULL){
			printf("ID: %i\nNombre: %s\nApellidos: %s\n",sqlite3_column_int(stmt, 0), (char*)sqlite3_column_text(stmt, 1), (char*)sqlite3_column_text(stmt, 2));
			printf("----------------------------------------\n");
		}
	} while (result == SQLITE_ROW);
	sqlite3_finalize(stmt);
}

//Acciones con Editoriales
void insertarEditoriaL(Editorial *ed){
	if (existeEditorial(ed->id)==0){
		char sql6[] = "insert into editorial values (?, ?);";

		sqlite3_prepare_v2(db, sql6, strlen(sql6) + 1, &stmt, NULL);
		sqlite3_bind_int(stmt, 1, ed->id);
		sqlite3_bind_text(stmt, 2, ed->nombre, strlen(ed->nombre), SQLITE_STATIC);

		result = sqlite3_step(stmt);
		if (result != SQLITE_DONE) {
			printf("Error al insertar la editorial\n");
		}else{
			printf("Editorial registrada correctamente\n");
		}

		sqlite3_finalize(stmt);
	}else{
		printf("La editorial ya existe\n");
	}
}
void insertarEditorialesFichero(char *ruta){
	//TODO
}
void eliminarEditorial(int idEd){
	if (existeEditorial(idEd)==1){
		char sql8[] = "delete from editorial where ID = ?";
		sqlite3_prepare_v2(db, sql8, strlen(sql8) + 1, &stmt, NULL);
		sqlite3_bind_int(stmt, 1, idEd);

		result = sqlite3_step(stmt);
		if (result != SQLITE_DONE) {
			printf("Error al eliminar la editorial\n");
		}else{
			printf("La editorial %s ha sido eliminado\n", idEd);
		}

		sqlite3_finalize(stmt);
	}else{
		printf("La editorial no existe\n");
	}
}
int existeEditorial(int idEd){
	char sql9[] = "select * from editorial where ID = ?";
	int count = 0;
	sqlite3_prepare_v2(db, sql9, strlen(sql9), &stmt, NULL) ;
	sqlite3_bind_int(stmt, 1, idEd);

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
Editorial obtenerEditorial(int idEd){
	char sql3[] = "select * from editorial where ID = ?";
	sqlite3_prepare_v2(db, sql3, strlen(sql3), &stmt, NULL) ;
	sqlite3_bind_int(stmt, 1, idEd);
	Editorial edAux;
	do {
		result = sqlite3_step(stmt) ;
		edAux.id = sqlite3_column_int(stmt, 0);
		edAux.nombre = (char*) sqlite3_column_text(stmt, 1);
	} while (result == SQLITE_ROW);
	return edAux;
}
Editorial obtenerEditorialPorLibro(char *isbn){
	Editorial ed;
	//TODO
	return ed;
}
void imprimirListadoEditoriales(){
	char sql10[] = "select * from editorial";
	sqlite3_prepare_v2(db, sql10, strlen(sql10), &stmt, NULL) ;

	printf("//////////////////////////\n");
	printf("**Listado de Editoriales**\n");
	printf("//////////////////////////\n");
	do {
		result = sqlite3_step(stmt);
		if((char*)sqlite3_column_text(stmt, 0)!= NULL){
			printf("ID: %i\nNombre: %s\n",sqlite3_column_int(stmt, 0), (char*)sqlite3_column_text(stmt, 1));
			printf("----------------------------------------\n");
		}
	} while (result == SQLITE_ROW);
	sqlite3_finalize(stmt);
}

//Acciones con Reservas
void listadoReservas(Reserva **listaRes, int tamanyoLista, Usuario *us){
	/*
	char sql10[] = "select * from reserva where DNI = ?";
	sqlite3_prepare_v2(db, sql10, strlen(sql10), &stmt, NULL) ;
	sqlite3_bind_text(stmt, 1, us->dni, strlen(us->dni), SQLITE_STATIC);
	do {
		result = sqlite3_step(stmt);
		Usuario *us;
		Reserva aux ={obtenerLibro((char*)sqlite3_column_text(stmt, 0)), obtenerUsuario(us,(char*)sqlite3_column_text(stmt, 1)), obtenerFechaIni((char*)sqlite3_column_text(stmt, 2)), obtenerFechaFin((char*)sqlite3_column_text(stmt, 3))};
		anyadirReserva(listaRes, tamanyoLista, &aux);
		printf("%s\n", aux.libro.isbn);
	} while (result == SQLITE_ROW);
	*/
}

//Acciones con fechas
Fecha obtenerFechaIni(char *res){
	Fecha f1;
	return f1;
}
Fecha obtenerFechaFin(char *res){
	Fecha f1;
	return f1;
}