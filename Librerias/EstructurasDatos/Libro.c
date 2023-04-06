#include <stdlib.h>

#include "Libro.h"

void anyadirLibro(Libro **listaLib, int tamanyoLista, Libro *lib){
    Libro **nuevaLista = (Libro**)malloc(sizeof(Libro*)* tamanyoLista + 1);
    for (int i = 0; i < tamanyoLista; i++)
    {
        nuevaLista[i] = listaLib[i];
    }
    nuevaLista[tamanyoLista] = lib;
    free(listaLib);
    listaLib = nuevaLista;
    free(nuevaLista);
}