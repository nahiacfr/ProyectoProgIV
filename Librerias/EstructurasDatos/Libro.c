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
void anyadirAutor(Autor **listaAu, int tamanyoLista, Autor *au){
        Autor **nuevaLista = (Autor**)malloc(sizeof(Autor*)* tamanyoLista + 1);
    for (int i = 0; i < tamanyoLista; i++)
    {
        nuevaLista[i] = listaAu[i];
    }
    nuevaLista[tamanyoLista] = au;
    free(listaAu);
    listaAu = nuevaLista;
    free(nuevaLista);
}
void anyadirEditorial(Editorial **listaEd, int tamanyoLista, Editorial *ed){
        Editorial **nuevaLista = (Editorial**)malloc(sizeof(Editorial*)* tamanyoLista + 1);
    for (int i = 0; i < tamanyoLista; i++)
    {
        nuevaLista[i] = listaEd[i];
    }
    nuevaLista[tamanyoLista] = ed;
    free(listaEd);
    listaEd = nuevaLista;
    free(nuevaLista);
}