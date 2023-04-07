#ifndef ABDD_H
#define ABDD_H

#include "sqlite3.h"
#include "..\EstructurasDatos\Fecha.h"
#include "..\EstructurasDatos\Usuario.h"
#include "..\EstructurasDatos\Libro.h"
#include "..\EstructurasDatos\Reserva.h"

void inicializarBDD(char *nombre, sqlite3 *db);
void cerrarBDD(sqlite3 *db);

//Acciones con Usuarios
void insertarUsuario(Usuario *us, char* contrasenya);
int existeUsuario(char *dni);
int verificarContrasenya(Usuario *us, char *contrasenya);
void eliminarUsuario(char *dni);
Usuario obtenerUsuario(Usuario *usAux, char* dniUs);
void listadoUsuarios(Usuario **listaUs, int tamanyoLista);

//Acciones con Libros
void insertarLibro(Libro *lib);
void insertarLibrosFichero(char *ruta);
void eliminarLibro(char *isbn);
int existeLibro(char *isbn);
Libro obtenerLibro(char* isbnLib);
void listadoLibros(Libro **listaLib, int tamanyoLista);

//Acciones con Autores
void insertarAutor(Autor *au);
void insertarAutoresFichero(char *ruta);
void eliminarAutor(int idAu);
int existeAutor(int idAu);
Autor obtenerAutor(int idAu);
Autor obtenerAutorPorLibro(char *isbn);
void listadoAutores(Autor **listaAu, int tamanyoLista);

//Acciones con Editoriales
void insertarEditoriaL(Editorial *ed);
void insertarEditorialesFichero(char *ruta);
void eliminarEditorial(int idEd);
int existeEditorial(int idEd);
Editorial obtenerEditorial(int idEd);
Editorial obtenerEditorialPorLibro(char *isbn);
void listadoEditoriales(Editorial **listaEd, int tamanyoLista);

//Acciones con Reservas
void listadoReservas(Reserva **listaRes, int tamanyoLista, Usuario *us);

//Acciones con Fechas
Fecha obtenerFechaIni(char *res);
Fecha obtenerFechaFin(char *res);

#endif