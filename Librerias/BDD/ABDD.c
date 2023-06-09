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
/*
	Inicializa la Base de Datos
*/
void inicializarBDD(char *nombre, sqlite3 *dbIni){
    db = dbIni;
	if (sqlite3_open(nombre, &db) == 0){
		printf("Conexion con la BDD exitosa\n");
	}else{
		printf("Error al conectar con la BDD\n");
	}
}
/*
	Cierra la conexion con la Base de Datos
*/
void cerrarBDD(sqlite3 *dbM){
    sqlite3_close(dbM);
	sqlite3_close(db);
}

/*
	Inserta un usuario en la BDD
*/
int insertarUsuario(Usuario *us, char* contrasenya){
	//COmprueba si el usuario existe en la BDD
	if (existeUsuario(us->dni)==0){
		//Introduce el usuario en la BDD
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
			return 0;
		}else{
			printf("Felicidades %s yta estas registrado\n", us->nombre);
			return 1;
		}

		sqlite3_finalize(stmt);
	}else{
		printf("El susuario ya existe\n");
		return 0;
	}
	
}
/*
	Comprueba, a traves del DNI, si el usuario existe en la BDD
	Retorna:
		0 --> False
		1 --> True
*/
int existeUsuario(char *dni){
	//Obtiene los usuarios de la BDD
    char sql2[] = "select DNI from usuario where DNI = ?";
	int count = 0;
	sqlite3_prepare_v2(db, sql2, strlen(sql2), &stmt, NULL) ;
	sqlite3_bind_text(stmt, 1, dni, strlen(dni), SQLITE_STATIC);
	//Cuenta cuantos usuarios se han obtenido
	//Solo deberian ser 1 o 0
	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			count++;
		}
	} while (result == SQLITE_ROW);

	sqlite3_finalize(stmt);
	//Si hay un usuario devuelve 1,  si no hay ninguno devuleve 0
	if (count >= 1){
		return 1;
	}else{
		return 0;
	}
}
/*
	Comprueba si la contraseña concuerda con la del usuario
*/
int verificarContrasenya(Usuario *us, char *contrasenya){
	//Obtiene la contraseña del usuario
	char sql3[] = "select contraseña from usuario where DNI = ?";
	int count = 0;
	sqlite3_prepare_v2(db, sql3, strlen(sql3), &stmt, NULL) ;
	sqlite3_bind_text(stmt, 1, us->dni, strlen(us->dni), SQLITE_STATIC);

	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			//Compara las dos contraseña
			//Si son coinciden devuelve 1, si son diferentes devuelve 0
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
/*
	Elimina un usuario de la BDD
*/
void eliminarUsuario(char *dni){
	//Comprueba si el usuario existe en la BDD
	if (existeUsuario(dni)==1){
		//Elimina el usuario de la BDD
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
/*
	Devuelve un usuario con los datos del usuario obtenidos de la BDD
*/
Usuario obtenerUsuario(Usuario *usAux, char* dniUs){
	//Obtiene los datos del usuario 
	char sql5[] = "select * from usuario where DNI = ?";
	sqlite3_prepare_v2(db, sql5, strlen(sql5), &stmt, NULL);
	sqlite3_bind_text(stmt, 1, dniUs, strlen(dniUs), SQLITE_STATIC);

	result = sqlite3_step(stmt);
	//Crea un usuario con los datos de la BDD
	Usuario aux ={(char*)sqlite3_column_text(stmt, 0), (char*)sqlite3_column_text(stmt, 1), (char*)sqlite3_column_text(stmt, 2), (char*)sqlite3_column_text(stmt, 3)};
	sqlite3_finalize(stmt);
	/*DUDA
		Se asigna a *usAux el usuario con los datos de la BDD
		Se retorna *usAux
		Pero *usAux ya lo pasas como parametro
		La modificacion y el rotorno no son repetitivos?
	*/
	*usAux = aux;
	return *usAux;
}
/*
	Imprime por consola una lista con todos los usuarios en la BDD
*/
void imprimirListadoUsuarios(){
	//Obtenemos los usuarios de la BDD
	char sql5[] = "select * from usuario";
	sqlite3_prepare_v2(db, sql5, strlen(sql5), &stmt, NULL);
	//Imprime la cabecera
	printf("///////////////////////\n");
	printf("//Listado de Usuarios//\n");
	printf("///////////////////////\n");
	//Imprime los datos de los ususarios
	do {
		result = sqlite3_step(stmt);
		if((char*)sqlite3_column_text(stmt, 0)!= NULL){
			printf("DNI: %s\nNombre: %s\nApellidos: %s\nCorreo electronico: %s\n",(char*)sqlite3_column_text(stmt, 0), (char*)sqlite3_column_text(stmt, 1), (char*)sqlite3_column_text(stmt, 2), (char*)sqlite3_column_text(stmt, 3));
			printf("----------------------------------------\n");
		}
	} while (result == SQLITE_ROW);
	sqlite3_finalize(stmt);
}

/*
	Introduce un libro nuevo en la BDD
*/
void insertarLibro(Libro *lib){ //Faltan los autores y las editoriales
	//Comprueba si ya existe el libro en la BDD
	if (existeLibro(lib->isbn)==0){
		//Inserta el libro en la BDD
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
		//Inserta la relacion Autor en la BDD
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
		//Inserta la relacion Pertenece en la BDD
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
/*
	Inserta multiples libros en la base de datos leyendo los datos desde un fichero
*/
void insertarLibrosFichero(char *ruta){
	//TODO
}
/*
	Elimina un libro de la BDD
*/
void eliminarLibro(char *isbn){
	//Comprueba si existe el libro en la BDD
	if (existeLibro(isbn)==1){
		//Elimina el libro de la BDD
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
		//Elimina la relacion autor de la BDD
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
		//Elimina la relacion pertenece de la BDD
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
/*
	Comprueba si el libro existe en la BDD
	Retorna:
		0 --> False
		1 --> True
*/
int existeLibro(char *isbn){
	//Obtiene los libros con ese ISBN
	char sql9[] = "select * from libro where ISBN = ?";
	int count = 0;
	sqlite3_prepare_v2(db, sql9, strlen(sql9), &stmt, NULL) ;
	sqlite3_bind_text(stmt, 1, isbn, strlen(isbn), SQLITE_STATIC);
	//Cuenta cuantos libros Hay con ese ISBN en la BDD
	//Solo deberia haber 1 o 0
	do {
		result = sqlite3_step(stmt);
		if (result == SQLITE_ROW) {
			count++;
		}
	} while (result == SQLITE_ROW);

	sqlite3_finalize(stmt);
	//Si hay 1 retorna 1, si no hay retorna 0
	if (count >= 1){
		return 1;
	}else{
		return 0;
	}
}
/*
	Obtiene un libro de la BDD a traves de su ISBN
	Retorna:
		Libro
*/
Libro obtenerLibro(char* isbnLib){
	//Obtiene los datos del libro de la BDD
	char sql1[] = "select * from libro where ISBN = ?";
	sqlite3_prepare_v2(db, sql1, strlen(sql1), &stmt, NULL) ;
	sqlite3_bind_text(stmt, 1, isbnLib, strlen(isbnLib), SQLITE_STATIC);
	//Crea un Libro vacio
	Libro libAux;
	//Introducimos los datos obtenidos de la BDD en el libro vacio
	result = sqlite3_step(stmt) ;
	libAux.isbn = (char*) sqlite3_column_text(stmt, 0);
	libAux.titulo = (char*) sqlite3_column_text(stmt, 1);
	libAux.anio = sqlite3_column_int(stmt, 2);
	sqlite3_finalize(stmt);
	//Obtenemos el autor de la relacion "autor"
	char sql2[] = "select * from autor where ISBN = ?";
	sqlite3_prepare_v2(db, sql2, strlen(sql2), &stmt, NULL) ;
	sqlite3_bind_text(stmt, 1, isbnLib, strlen(isbnLib), SQLITE_STATIC);
	libAux.autor = obtenerAutor(sqlite3_column_int(stmt, 1));
	sqlite3_finalize(stmt);
	//Obtenemos la editorial de la relacion "pertenece"
	char sql3[] = "select * from pertenece where ISBN = ?";
	sqlite3_prepare_v2(db, sql3, strlen(sql3), &stmt, NULL) ;
	sqlite3_bind_text(stmt, 1, isbnLib, strlen(isbnLib), SQLITE_STATIC);
	libAux.editorial = obtenerEditorial(sqlite3_column_int(stmt, 1));
	sqlite3_finalize(stmt);
	
	return libAux;
}
/*
	Imprime por consola el listado completo de los libros que hay en la BDD
*/
void imprimirListadoLibros(){
	//Obtiene todos los libros de la BDD
	char sql10[] = "select * from libro";
	sqlite3_prepare_v2(db, sql10, strlen(sql10), &stmt, NULL) ;
	//Imprime la cabecera
	printf("/////////////////////\n");
	printf("//Listado de Libros//\n");
	printf("/////////////////////\n");
	//Imprime los datos de los libros
	do {
		result = sqlite3_step(stmt);
		if((char*)sqlite3_column_text(stmt, 1)!= NULL){
			printf("ISBN: %s\nTitulo: %s\nAnyo de publicacion: %i\n",(char*)sqlite3_column_text(stmt, 1), (char*)sqlite3_column_text(stmt, 0), sqlite3_column_int(stmt, 2));
			printf("----------------------------------------\n");
		}
	} while (result == SQLITE_ROW);
	sqlite3_finalize(stmt);
}

/*
	Inserta un autor en la BDD
*/
void insertarAutor(Autor *au){
	//Comprueba que el autor no exista en la BDD
	if (existeAutor(au->id)==0){
		//Introduce el autor en la BDD
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
/*
	Inserta multiples autores en la base de datos leyendo los datos desde un fichero
*/
void insertarAutoresFichero(char *ruta){
	FILE *archivo = fopen(ruta, "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo\n");
        return;
    }
	char linea[100];
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        // extraer nombre, apellidos id 
        char *token = strtok(linea, ";");
        char *nombre = token;
        token = strtok(NULL, ";");
        char *apellidos = token;
        token = strtok(NULL, ";");
        int id = atoi(token);

        // crear nuevo autor para meter en bd
        Autor *au = (Autor *)malloc(sizeof(Autor));
        au->id = id;
        au->nombre = nombre; 
        au->apellidos = apellidos; 
        insertarAutor(au);
        free(au->nombre);
        free(au->apellidos);
        free(au);
    }

    fclose(archivo);
}
/*
	Elimina una autor de la BDD
*/
void eliminarAutor(int idAu){
	//Comprueba si el autor existe en la BDD
	if (existeAutor(idAu)==1){
		//Comprueba que el autor no tenga libros asignados
		//Obtiene las relaciones del autor y sus libros 
		char sql9[] = "select * from autor where ID = ?";
		int count = 0;
		sqlite3_prepare_v2(db, sql9, strlen(sql9), &stmt, NULL) ;
		sqlite3_bind_int(stmt, 1, idAu);
		//Cuenta las relaciones obtenidas
		do {
			result = sqlite3_step(stmt) ;
			if (result == SQLITE_ROW) {
				count++;
			}
		} while (result == SQLITE_ROW);
		sqlite3_finalize(stmt);	
		//Si existe alguna relacion da error y no permite eliminar el autor
		if(count>=1){
			printf("No se puede eliminar el autor, todfavia tiene libros asignados\nElimine todos los libros pertenecientes a este autor y vuelva a intentarlo\n");
		}else{
			//Elimina de la BDD el autor
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
		}
		
	}else{
		printf("El autor no existe\n");
	}
}
/*
	Comprueba, a traves del id, si el autor existe en la BDD
	Retorna:
		0 --> False
		1 --> True
*/
int existeAutor(int idAu){
	//Obtiene los escritores con ese id en la BDD
	char sql9[] = "select * from escritor where ID = ?";
	int count = 0;
	sqlite3_prepare_v2(db, sql9, strlen(sql9), &stmt, NULL) ;
	sqlite3_bind_int(stmt, 1, idAu);
	//Cuenta cuantos escritores hay
	//Solo deberia haber 1 o 0
	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			count++;
		}
	} while (result == SQLITE_ROW);
	//Si hay 1 retorna 1, si no hay ninguna retorna 0
	sqlite3_finalize(stmt);
	if (count >= 1){
		return 1;
	}else{
		return 0;
	}
}
/*
	Devuelve un Autor con la informacion de la BDD del autor con ese id 
*/
Autor obtenerAutor(int idAu){
	//Se obtiene los datos del escritor de la BDD
	char sql3[] = "select * from escritor where ID = ?";
	sqlite3_prepare_v2(db, sql3, strlen(sql3), &stmt, NULL) ;
	sqlite3_bind_int(stmt, 1, idAu);
	//Se crea un autor vacio
	Autor auAux;
	//Se rellenan los datos del autor vacio con los datos de la BDD
	do {
		result = sqlite3_step(stmt) ;
		auAux.id = sqlite3_column_int(stmt, 0);
		auAux.nombre = (char*) sqlite3_column_text(stmt, 1);
		auAux.apellidos = (char*) sqlite3_column_text(stmt, 2);
	} while (result == SQLITE_ROW);
	return auAux;
}
/*
	Devuelve un autor a partir del ISBN de uno de sus libros
*/
Autor obtenerAutorPorLibro(char *isbn){
	//obtiene el autor 
	char sql20[] = "SELECT * FROM autor WHERE ISBN = ?";
    sqlite3_prepare_v2(db, sql20, strlen(sql20), &stmt, NULL);
    sqlite3_bind_text(stmt, 1, isbn, strlen(isbn), SQLITE_STATIC);
	result = sqlite3_step(stmt);
	int idAutor = sqlite3_column_int(stmt, 1);
	//devuelve un autor con el id obtenido
	Autor au = obtenerAutor(idAutor);
	return au;
	
}
/*
	Imprime por consola el listado de los autores
*/
void imprimirListadoAutores(){
	//Obtiene los datos de todos los autores en la BDD
	char sql10[] = "select * from escritor";
	sqlite3_prepare_v2(db, sql10, strlen(sql10), &stmt, NULL) ;
	//Imprime la cabecera
	printf("//////////////////////\n");
	printf("//Listado de Autores//\n");
	printf("//////////////////////\n");
	//Imprime la informacion de los autores
	do {
		result = sqlite3_step(stmt);
		if((char*)sqlite3_column_text(stmt, 0)!= NULL){
			printf("ID: %i\nNombre: %s\nApellidos: %s\n",sqlite3_column_int(stmt, 0), (char*)sqlite3_column_text(stmt, 1), (char*)sqlite3_column_text(stmt, 2));
			printf("----------------------------------------\n");
		}
	} while (result == SQLITE_ROW);
	sqlite3_finalize(stmt);
}

/*
	Inserta una nueva editorial en la BDD
*/
void insertarEditorial(Editorial *ed){
	//Comprueba si la editorial exite en la BDD
	if (existeEditorial(ed->id)==0){
		//Introduce la editorial en la BDD
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
/*
	Inserta multiples editoriales en la base de datos leyendo los datos desde un fichero
*/
void insertarEditorialesFichero(char *ruta){
	
	FILE *archivo = fopen(ruta, "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo\n");
        return;
    }
	char linea[100];
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
    // nombre y el id línea
        char *token = strtok(linea, ";");
        char *nombre = token;
        token = strtok(NULL, ";");
        int id = atoi(token);
	//nueva ed para guardar en bd
        Editorial *ed = (Editorial *)malloc(sizeof(Editorial));
        ed->id = id;
        ed->nombre = nombre; 
        insertarEditorial(ed);

        free(ed->nombre);
        free(ed);
    }

    fclose(archivo);
}
/*
	Elimina una editorial de la BDD
*/
void eliminarEditorial(int idEd){
	//Comprueba si la editorial existe en la BDD
	if (existeEditorial(idEd)==1){
		//Comprueba si la editorial tiene libros asignados
		//Obtiene las relaciones de la editorial y sus libros
		char sql1[] = "select * from pertenece where ID = ?";
		int count = 0;
		sqlite3_prepare_v2(db, sql1, strlen(sql1), &stmt, NULL) ;
		sqlite3_bind_int(stmt, 1, idEd);
		//Cuenta cuentas relaciones existen
		do {
			result = sqlite3_step(stmt) ;
			if (result == SQLITE_ROW) {
				count++;
			}
		} while (result == SQLITE_ROW);
		sqlite3_finalize(stmt);	
		//Si existe alguna relacion, da error y no permite eliminar la editorial
		if(count>=1){
			printf("No se puede eliminar la editorial, todfavia tiene libros asignados\nElimine todos los libros pertenecientes a esta editorial y vuelva a intentarlo\n");
		}else{
			//Elimina la editorial de la BDD
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
		}
	}else{
		printf("La editorial no existe\n");
	}
}
/*
	Comprueba si la editorial existe en la BDD
	Retorna:
		0 --> False
		1 --> True
*/
int existeEditorial(int idEd){
	//Obtiene las editoriales con ese id en la BDD
	char sql9[] = "select * from editorial where ID = ?";
	int count = 0;
	sqlite3_prepare_v2(db, sql9, strlen(sql9), &stmt, NULL) ;
	sqlite3_bind_int(stmt, 1, idEd);
	//Cuenta el numero de editoriales obtenidas
	//Solo deberia haber 1 o 0
	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			count++;
		}
	} while (result == SQLITE_ROW);

	sqlite3_finalize(stmt);
	//Si existe 1 retorna 1, si no hay ninguna retorna 0
	if (count >= 1){
		return 1;
	}else{
		return 0;
	}
}
/*
	Devuelve una Editorial a partir de su id 
*/
Editorial obtenerEditorial(int idEd){
	//Obtiene la informacion de la BDD
	char sql3[] = "select * from editorial where ID = ?";
	sqlite3_prepare_v2(db, sql3, strlen(sql3), &stmt, NULL) ;
	sqlite3_bind_int(stmt, 1, idEd);
	//Crea una editorial vacia
	Editorial edAux;
	//Rellena los datos de la editorial
	do {
		result = sqlite3_step(stmt) ;
		edAux.id = sqlite3_column_int(stmt, 0);
		edAux.nombre = (char*) sqlite3_column_text(stmt, 1);
	} while (result == SQLITE_ROW);
	return edAux;
}
/*
	Devuelve una editorial a traves del ISBN de uno de sus libros
*/
Editorial obtenerEditorialPorLibro(char *isbn){
	Editorial ed;
	char sql[] = "SELECT ID FROM pertenece WHERE ISBN = ?";

    sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL);
    sqlite3_bind_text(stmt, 1, isbn, strlen(isbn), SQLITE_STATIC);
	int idEditorial;
	if (sqlite3_step(stmt) == SQLITE_ROW) {
       
	   idEditorial = sqlite3_column_int(stmt, 0);

    }

	return obtenerEditorial(idEditorial);
}
/*
	Imprime por consola el listado de Editoriales
*/
void imprimirListadoEditoriales(){
	//Obtiene la informacion de todas las editoriales de la BDD
	char sql10[] = "select * from editorial";
	sqlite3_prepare_v2(db, sql10, strlen(sql10), &stmt, NULL) ;
	//Imprime la cabecera
	printf("//////////////////////////\n");
	printf("**Listado de Editoriales**\n");
	printf("//////////////////////////\n");
	//Imprime la informacion de las editoriales
	do {
		result = sqlite3_step(stmt);
		if((char*)sqlite3_column_text(stmt, 0)!= NULL){
			printf("ID: %i\nNombre: %s\n",sqlite3_column_int(stmt, 0), (char*)sqlite3_column_text(stmt, 1));
			printf("----------------------------------------\n");
		}
	} while (result == SQLITE_ROW);
	sqlite3_finalize(stmt);
}

/*
	Devuelve un listado de las reservas de un usuario concreto
*/
void listadoReservas(Reserva **listaRes, int tamanyoLista, Usuario *us){
	
        char sql[] = "SELECT * FROM reserva WHERE DNI = ?";
		
      if (sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, us->dni, strlen(us->dni), SQLITE_STATIC);

            // Recorrer los resultados de la consulta
            while ((result = sqlite3_step(stmt)) == SQLITE_ROW) {
				Usuario *us;
                Reserva *reserva = (Reserva *)malloc(sizeof(Reserva));
                reserva->libro = obtenerLibro((char *)sqlite3_column_text(stmt, 0));
                reserva->usuario = obtenerUsuario(us,(char *)sqlite3_column_text(stmt, 1));
                reserva->fechaIni = obtenerFechaIni((char *)sqlite3_column_text(stmt, 2));
                reserva->fechaFin = obtenerFechaFin((char *)sqlite3_column_text(stmt, 3));

                // Añadir la reserva a la lista
                anyadirReserva(listaRes, tamanyoLista, reserva);

                printf("ISBN: %s, DNI: %s, Fecha Inicio: %d/%d/%d, Fecha Fin: %d/%d/%d\n",
                       reserva->libro, reserva->usuario,
                       reserva->fechaIni.dia, reserva->fechaIni.mes, reserva->fechaIni.anyo,
                       reserva->fechaFin.dia, reserva->fechaFin.mes, reserva->fechaFin.anyo);
            }

            // Liberar recursos
            sqlite3_finalize(stmt);
        }
}

Fecha obtenerFechaIni(char *res){
	Fecha f1;
	int dia, mes, anio;
    sscanf(res, "%d/%d/%d", &dia, &mes, &anio);
    f1.dia = dia;
    f1.mes = mes;
    f1.anyo = anio;
	return f1;
}
Fecha obtenerFechaFin(char *res){
	Fecha f1;
	int dia, mes, anio;
    sscanf(res, "%d/%d/%d", &dia, &mes, &anio);
    f1.dia = dia;
    f1.mes = mes;
    f1.anyo = anio;
	return f1;
}

int verifyUserFromSocket(char buffer[], int length)
{
	char *token;	

    char* correo;
    char* contrasenya;

	strtok(buffer, "##");
	correo = strtok(NULL, "#");
	contrasenya = strtok(NULL, "#");

    /*Comprobar si el usuario es correcto*/
    char sql3[] = "select contraseña from usuario where correo = ?";
	int count = 0;

	sqlite3_prepare_v2(db, sql3, strlen(sql3), &stmt, NULL) ;
	sqlite3_bind_text(stmt, 1, correo, strlen(correo), SQLITE_STATIC);

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
    
    /*Devolver el resultado*/
    return 0;
}

char* searchBooks(char buffer[], int length){
	char *token;
    // Obtener el título del libro enviado desde el cliente
    char *titulo;
	
	token = strtok(buffer, "##");
	titulo = strtok(NULL, "#");
    // Realizar la búsqueda en la base de datos
    char sql[] = "Select l.titulo,l.isbn,r.dni From libro l Left Join reserva As r On r.isbn=l.isbn Where l.titulo = ?";
    sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, titulo, strlen(titulo), SQLITE_STATIC);
	
    char *response = "";
    // Ejecutar la consulta y recopilar los resultados
	int j = 0;
    while(sqlite3_step(stmt) == SQLITE_ROW)
	{ 
		j = 1;
		//hacer lisat con los resultados
		char *nuevoChurro = malloc(sizeof(sqlite3_column_text(stmt, 0)) + sizeof(sqlite3_column_text(stmt, 1))+5);
		strcpy(nuevoChurro, "Titulo: ");
		strcat(nuevoChurro, sqlite3_column_text(stmt, 0));
		strcat(nuevoChurro, "\nISBN: ");
        strcat(nuevoChurro, sqlite3_column_text(stmt, 1));
		if(sqlite3_column_text(stmt, 2)!= NULL)
		{
			strcat(nuevoChurro, " *RESERVADO");
		}
        char *nuevaLista = malloc(sizeof(response) + sizeof(nuevoChurro)+5);
		strcpy(nuevaLista, response);
		strcat(nuevaLista, "\n");
        strcat(nuevaLista, nuevoChurro);   
		strcat(nuevaLista, "\n");    
		
		response = nuevaLista;
		free(nuevoChurro);
		free(nuevaLista);
		
    }
	strcat(response, "\0");
	sqlite3_finalize(stmt);
    
	if(j == 0)
	{
		return "No se han encontrado libros con ese titulo\n";
	}else{
		return response;
	}	
}

char* searchBooksAuthor(char buffer[], int length){

    char *token;
    // Obtener el título del libro enviado desde el cliente
    char *nombreAutor; 
	char *apellidoAutor;
	
	token = strtok(buffer, "##");
	nombreAutor = strtok(NULL, "#");
	apellidoAutor = strtok(NULL, "#");
    // Realizar la búsqueda en la base de datos
    char sql[] = "select l.titulo, l.isbn from libro l inner join autor as a on l.isbn=a.isbn inner join escritor as e on a.id=e.id WHERE e.nombre = ? AND e.apellidos = ?";
    sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, nombreAutor, strlen(nombreAutor), SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, apellidoAutor, strlen(apellidoAutor), SQLITE_STATIC);
	
    char *response = "";
    // Ejecutar la consulta y recopilar los resultados
	int j = 0;
    while(sqlite3_step(stmt) == SQLITE_ROW)
	{ 
		j = 1;
		//hacer lisat con los resultados
		char *nuevoChurro = malloc(sizeof(sqlite3_column_text(stmt, 0)) + sizeof(sqlite3_column_text(stmt, 1))+5);
		strcpy(nuevoChurro, sqlite3_column_text(stmt, 0));
		strcat(nuevoChurro, "----");
        strcat(nuevoChurro, sqlite3_column_text(stmt, 1));
        char *nuevaLista = malloc(sizeof(response) + sizeof(nuevoChurro)+5);
		strcpy(nuevaLista, response);
		strcat(nuevaLista, "\n");
        strcat(nuevaLista, nuevoChurro);   
		strcat(nuevaLista, "\n");    
		
		response = nuevaLista;
		free(nuevoChurro);
		free(nuevaLista);
		
    }
	strcat(response, "\0");
	sqlite3_finalize(stmt);
    
	if(j == 0)
	{
		return "No se han encontrado libros con ese autor\n";
	}else{
		return response;
	}
}

int reservarLibro(char buffer[], int length)
{
	char *token;
    // Obtener el título del libro enviado desde el cliente
    char *isbn, *correo, *dia, *mes, *anyo; 
	char *dni = malloc(sizeof(char)*20);
	token = strtok(buffer, "##");
	isbn = strtok(NULL, "#");
	correo = strtok(NULL, "#");
	dia = strtok(NULL, "#");
	mes = strtok(NULL, "#");
	anyo = strtok(NULL, "#");

	Fecha *fechaIni = crearFecha(strtol(dia, NULL, 10),strtol(mes, NULL, 10),strtol(anyo, NULL, 10));
	Fecha *fechaFin = calcularFecha(fechaIni, 15);
	
	char sql[] = "Select dni from usuario where correo = ?";
    sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, correo, strlen(correo), SQLITE_STATIC);
	if (sqlite3_step(stmt) == SQLITE_ROW)
	{
		strcpy(dni, (char*)sqlite3_column_text(stmt, 0));
	}
	sqlite3_finalize(stmt);
	char sql2[] = "Insert into reserva values (?,?,?,?)";
    sqlite3_prepare_v2(db, sql2, strlen(sql2) + 1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, isbn, strlen(isbn), SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, dni, strlen(dni), SQLITE_STATIC);
	sqlite3_bind_text(stmt, 3, getFecha(fechaIni), strlen(getFecha(fechaIni)), SQLITE_STATIC);
	sqlite3_bind_text(stmt, 4, getFecha(fechaFin), strlen(getFecha(fechaFin)), SQLITE_STATIC);
	if (sqlite3_step(stmt) == SQLITE_DONE)
	{
		sqlite3_finalize(stmt);
        printf("Reservar exitosa\n");
        return 1;
    } else {
        sqlite3_finalize(stmt);
        printf("Reserva Fallida\n");

        return 0;
	}
}

char* listBooks(char buffer[], int length)
{
	char *token;
    // Obtener el título del libro enviado desde el cliente
    char *reservados;

	token = strtok(buffer, "##");
	reservados = strtok(NULL, "#");
    // Realizar la búsqueda en la base de datos
	if (strcmp (reservados, "1")==0)
	{
		char sql[] = "Select l.titulo,l.isbn,r.dni From libro l Left Join reserva As r On r.isbn=l.isbn";
		sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	}else if (strcmp (reservados, "2")==0)
	{
		char sql[] = "Select l.titulo,l.isbn,r.dni From libro l Left Join reserva As r On r.isbn=l.isbn where r.dni is null";
		sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	}else
	{
		char sql[] = "Select l.titulo,l.isbn,r.dni From libro l Left Join reserva As r On r.isbn=l.isbn";
		sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	}
    char *response = "";
    // Ejecutar la consulta y recopilar los resultados
	int j = 0;
    while(sqlite3_step(stmt) == SQLITE_ROW)
	{ 
		j = 1;
		//hacer lisat con los resultados
		char *nuevoChurro = malloc(sizeof(sqlite3_column_text(stmt, 0)) + sizeof(sqlite3_column_text(stmt, 1))+5);
		strcpy(nuevoChurro, "Titulo: ");
		strcat(nuevoChurro, sqlite3_column_text(stmt, 0));
		strcat(nuevoChurro, "\nISBN: ");
        strcat(nuevoChurro, sqlite3_column_text(stmt, 1));
		if(sqlite3_column_text(stmt, 2)!= NULL)
		{
			strcat(nuevoChurro, " *RESERVADO");
		}
        char *nuevaLista = malloc(sizeof(response) + sizeof(nuevoChurro)+5);
		strcpy(nuevaLista, response);
		strcat(nuevaLista, "\n");
        strcat(nuevaLista, nuevoChurro);   
		strcat(nuevaLista, "\n");    
		
		response = nuevaLista;
		free(nuevoChurro);
		free(nuevaLista);
		
    }
	strcat(response, "\0");
	sqlite3_finalize(stmt);

	if(j == 0)
	{
		return "No se han encontrado libros con ese titulo\n";
	}else{
		return response;
	}
}