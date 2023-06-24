#include <iostream>
#include <string.h>
#include <stdlib.h>
#include "LibroCPP.h"

using namespace std;

//autor
Autor::Autor(/* args */)
{
    this->id=0;

	this->nombre = new char[1];
	this->nombre[0] = '\0';
    
	this->apellidos = new char[1];
	this->apellidos[0] = '\0';
}
Autor::Autor(int id, const char* nombre, const char* apellido)
{
    this->id=id;

	this->nombre = new char[strlen(nombre) + 1];
	strcpy(this->nombre, nombre);
    
	this->apellidos = new char[strlen(apellido) + 1];
	strcpy(this->apellidos, apellido);
}
Autor::~Autor()
{
    delete[] this->nombre;
    delete[] this->apellidos;
}

//editorial
Editorial::Editorial(/* args */)
{
    this->id=0;

	this->nombre = new char[1];
	this->nombre[0] = '\0';
}
Editorial::Editorial(int id, const char* nombre)
{
    this->id=id;

	this->nombre = new char[strlen(nombre) + 1];
	strcpy(this->nombre, nombre);
}
Editorial::~Editorial()
{
    delete[] this->nombre;
}


//libro
Libro::Libro(/* args */)
{
	this->isbn = new char[1];
	this->isbn[0] = '\0';
    
	this->titulo = new char[1];
	this->titulo[0] = '\0';

    this->anio=0;

    this->autor=NULL;

    this->editorial=NULL;
}
Libro::Libro(const char *isbn, const char *titulo, int anio, Autor *autor, Editorial *editorial)
{
	this->isbn = new char[strlen(isbn) + 1];
	strcpy(this->isbn, isbn);
    
	this->titulo = new char[strlen(titulo) + 1];
	strcpy(this->titulo, titulo);

    this->anio=anio;

    this->autor=autor;

    this->editorial=editorial;
}
Libro::~Libro()
{
    delete[] this->isbn;
    delete[] this->titulo;
}

//////////////////////////
void Libro::anyadirLibro(Libro **listaLib, int tamanyoLista, Libro *lib)
{
    Libro **nuevaLista = new Libro*[tamanyoLista + 1];
    for (int i = 0; i < tamanyoLista; i++)
    {
        nuevaLista[i] = listaLib[i];
    }
    nuevaLista[tamanyoLista] = lib;
    delete[] listaLib;
    listaLib = nuevaLista;
    delete[] nuevaLista;
}

void Autor::anyadirAutor(Autor **listaAu, int tamanyoLista, Autor *au)
{
    Autor **nuevaLista = new Autor*[tamanyoLista +1];
    for (int i = 0; i < tamanyoLista; i++)
    {
        nuevaLista[i] = listaAu[i];
    }
    nuevaLista[tamanyoLista] = au;
    delete[] listaAu;
    listaAu = nuevaLista;
    delete[] nuevaLista;
}

void Editorial::anyadirEditorial(Editorial **listaEd, int tamanyoLista, Editorial *ed)
{
    Editorial **nuevaLista = new Editorial*[tamanyoLista+1];
    for (int i = 0; i < tamanyoLista; i++)
    {
        nuevaLista[i] = listaEd[i];
    }
    nuevaLista[tamanyoLista] = ed;
    delete[] listaEd;
    listaEd = nuevaLista;
    delete[] nuevaLista;
}