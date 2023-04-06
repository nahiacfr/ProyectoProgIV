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
void listadoUsuarios(Usuario **listaUs, int tamanyoLista);

//Acciones con Libros
void insertarLibro(Libro *lib);
void insertarLibroFichero(char *ruta);
void eliminarLibro(Libro *lib);
int existeLibro(Libro *lib);
void listadoLibros(Libro **listaLib, int tamanyoLista);

//Acciones con Autores
void insertarAutor(Autor *au);
void insertarAutorFichero(char *ruta);
void eliminarAutor(Autor *au);
int existeAutor(Autor *au);
void listadoAutores(Autor **listaAu, int tamanyoLista);

//Acciones con Editoriales
void insertarEditoriaL(Editorial *ed);
void insertarEditorialFichero(char *ruta);
void eliminarEditorial(Editorial *ed);
int existeEditorial(Editorial *ed);
void listadoEditoriales(Editorial **listaEd, int tamanyoLista);

//Acciones con Reservas
void listadoReservas(Usuario *us, Reserva *res);

#endif