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
int existeUsuario(Usuario *us);
int verificarContrasenya(Usuario *us, char *contrasenya);
void eliminarUsuario(Usuario *us);
Usuario obtenerUsuario(Usuario *usAux, char* dniUs);
void listadoUsuarios(Usuario **listaUs, int tamanyoLista);

//Acciones con Libros
void insertarLibro(Libro *lib);
void insertarLibrosFichero(char *ruta);
void eliminarLibro(Libro *lib);
int existeLibro(Libro *lib);
Libro obtenerLibro(char* isbnLib);
void listadoLibros(Libro **listaLib, int tamanyoLista);

//Acciones con Autores
void insertarAutor(Autor *au);
void insertarAutoresFichero(char *ruta);
void eliminarAutor(Autor *au);
int existeAutor(Autor *au);
Autor obtenerAutor(int idAu);
Autor obtenerAutorPorLibro(char *isbn);
void listadoAutores(Autor **listaAu, int tamanyoLista);

//Acciones con Editoriales
void insertarEditoriaL(Editorial *ed);
void insertarEditorialesFichero(char *ruta);
void eliminarEditorial(Editorial *ed);
int existeEditorial(Editorial *ed);
Editorial obtenerEditorial(int idEd);
Editorial obtenerEditorialPorLibro(char *isbn);
void listadoEditoriales(Editorial **listaEd, int tamanyoLista);

//Acciones con Reservas
void listadoReservas(Reserva **listaRes, int tamanyoLista, Usuario *us);

//Acciones con Fechas
Fecha obtenerFechaIni(char *res);
Fecha obtenerFechaFin(char *res);

#endif