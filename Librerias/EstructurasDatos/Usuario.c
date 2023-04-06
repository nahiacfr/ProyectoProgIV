#include "Usuario.h"
#include<stdlib.h>

void anyadirUsuario(Usuario **listaUs, int tamanyoLista, Usuario *us){
    Usuario **nuevaLista = (Usuario**)malloc(sizeof(Usuario*)* tamanyoLista + 1);
    for (int i = 0; i < tamanyoLista; i++)
    {
        nuevaLista[i] = listaUs[i];
    }
    nuevaLista[tamanyoLista] = us;
    free(listaUs);
    listaUs = nuevaLista;
    free(nuevaLista);
}