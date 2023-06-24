#include "Usuario.h"
#include<stdlib.h>

Usuario::Usuario(/* args */)
{
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