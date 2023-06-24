#include "Usuario.h"
#include<stdlib.h>

Usuario::Usuario()
{
	this->dni = new char[1];
	this->dni[0] = '\0';

	this->nombre = new char[1];
	this->nombre[0] = '\0';
    
	this->apellidos = new char[1];
	this->apellidos[0] = '\0';
    
	this->correo = new char[1];
	this->correo[0] = '\0';
}
Usuario::Usuario(const char* dni, const char* nombre, const char* apellido, const char* correo)
{
	this->dni = new char[strlen(dni) + 1];
	strcpy(this->dni, dni);
    
	this->nombre = new char[strlen(nombre) + 1];
	strcpy(this->nombre, nombre);
    
	this->apellidos = new char[strlen(apellido) + 1];
	strcpy(this->apellidos, apellido);
    
	this->correo = new char[strlen(correo) + 1];
	strcpy(this->correo, correo);
}
Usuario::~Usuario()
{
}

void Usuario::anyadirUsuario(Usuario **listaUs, int tamanyoLista, Usuario *us)
{
    Usuario **nuevaLista = new Usuario*[tamanyoLista + 1];
    for (int i = 0; i < tamanyoLista; i++)
    {
        nuevaLista[i] = listaUs[i];
    }
    nuevaLista[tamanyoLista] = us;
    delete[] listaUs;
    listaUs = nuevaLista;
    delete[] nuevaLista;
}