#ifndef ABDD_H
#define ABDD_H

#include "sqlite3.h"
#include "..\EstructurasDatos\Usuario.h"
#include "..\EstructurasDatos\Libro.h"
#include "..\EstructurasDatos\Reserva.h"

void inicializarBDD(char *nombre, sqlite3 *db);
void cerrarBDD(sqlite3 *db);

//Acciones con Usuarios
void insertarNuevoUsuario(Usuario *us, char* contrasenya);
int existeUsuario(Usuario *us);
int verificarContrasenya(Usuario *us, char *contrasenya);
void eliminarUsuario(Usuario *us);
void listadoUsuarios(Usuario *us);

//Acciones con Libros
void insertarLibro(Libro *lib);
void insertarLibroFichero(char *ruta);
void eliminarLibro(Libro *lib);
int existeLibro(Libro *lib);
void listadoLibros(Libro *lib);

//Acciones con Reservas
void listadoReservas(Usuario *us, Reserva *res);

#endif